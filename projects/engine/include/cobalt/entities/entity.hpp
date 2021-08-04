#pragma once

#include <cobalt/entities/identifier.hpp>
#include <cobalt/entities/sparsepool.hpp>
#include <cobalt/entities/traits.hpp>
#include <cobalt/events/event.hpp>
#include <cobalt/events/eventmanager.hpp>
#include <cobalt/macros.hpp>

#include <cstdint>
#include <cstddef>
#include <vector>

namespace cobalt
{
	class Registry;

	class Entity
	{
		public:
			Entity() = default;
			Entity(Registry* registry, Identifier id);
			
			bool operator==(const Entity& rhs) noexcept;
			bool operator!=(const Entity& rhs) noexcept;
			bool operator<(const Entity& rhs) noexcept;
			bool operator<=(const Entity& rhs) noexcept;
			bool operator>(const Entity& rhs) noexcept;
			bool operator>=(const Entity& rhs) noexcept;

			operator bool() const noexcept;
			Identifier id() const noexcept;
			bool valid() const noexcept;
			
			void invalidate();
			void release();

			template <typename T>
			Entity& assign(const T& value);

			template <typename T, typename ... Ts>
			bool contains() const noexcept;

			template <typename T>
			T& get() const noexcept;

			template <typename T>
			T* tryGet() const noexcept;

			template <typename T>
			Entity& remove();

			template <typename T>
			Entity& replace(const T& value);

		private:
			Identifier _id;
			Registry* _reg;
	};

	template <typename T, std::size_t PageSize>
	class ComponentView
	{
		public:
			auto begin() noexcept;
			const auto begin() const noexcept;
			const auto cbegin() const noexcept;

			auto end() noexcept;
			const auto end() const noexcept;
			const auto cend() const noexcept;
		private:
			friend class Registry;

			ComponentView(SparsePool<T, traits<T>::poolSize()>* pool);

			SparsePool<T>* _pool;
	};

	template <typename ... Ts>
	class EntityView
	{
			class ForwardIterator
			{
				public:
					ForwardIterator(Registry* reg, long long index) noexcept;
					Entity operator*() noexcept;
					const Entity operator*() const noexcept;

					ForwardIterator& operator++() noexcept;
					ForwardIterator operator++(int) noexcept;

					bool operator==(const ForwardIterator& rhs) const noexcept;
					bool operator!=(const ForwardIterator& rhs) const noexcept;
				
				private:
					Registry* _reg;
					long long _index;
			};
		public:
			auto begin() noexcept;
			const auto begin() const noexcept;
			const auto cbegin() const noexcept;

			auto end() noexcept;
			const auto end() const noexcept;
			const auto cend() const noexcept;
		private:
			friend class Registry;

			explicit EntityView(Registry* reg) noexcept;

			Registry* _reg;
	};

	class Registry
	{
		public:
			Registry() = default;
			COBALT_NO_COPY_MOVE(Registry);

			~Registry();
			Entity create();
			void release(const Identifier id);
			bool valid(const Identifier id) const noexcept;

			template<typename T>
			void assign(const Identifier id, const T& value);

			template <typename T, typename ... Ts>
			bool contains(const Identifier id) const noexcept;

			template <typename T>
			T& get(const Identifier id) const noexcept;

			template <typename T>
			T* tryGet(const Identifier id) const noexcept;

			template <typename T>
			void remove(const Identifier id) const noexcept;

			template <typename T>
			void replace(const Identifier id, const T& value) const noexcept;

			template <typename T>
			ComponentView<T, traits<T>::poolSize()> view() noexcept;

			template <typename ... Ts>
			EntityView<Ts...> entities() noexcept;

			EventManager& events() noexcept;
			
		private:
			template <typename ... Ts>
			friend class EntityView;

			template <typename ... Ts>
			friend class EntityView<Ts...>::ForwardIterator;

			Identifier _createNewId();
			Identifier _recycleId();

			std::vector<Identifier> _entities;
			std::vector<BaseSparsePool*> _memPools;
			Identifier _nextAvailable = Identifier::Invalid;

			template <typename T>
			SparsePool<T>& _assure();

			EventManager _events;
	};

	struct EntityCreatedEvent : Event<EntityCreatedEvent>
	{
		const Entity entity;

		EntityCreatedEvent() = default;
		explicit EntityCreatedEvent(const Entity entity);
	};

	struct EntityDestroyedEvent : Event<EntityDestroyedEvent>
	{
		const Entity entity;

		EntityDestroyedEvent() = default;
		explicit EntityDestroyedEvent(const Entity entity);
	};

	template <typename Type>
	struct ComponentAddedEvent : Event<ComponentAddedEvent<Type>>
	{
		const Entity entity;
		const Type& component;

		ComponentAddedEvent(const Entity entity, const Type& component);
	};

	template <typename Type>
	struct ComponentRemovedEvent : Event<ComponentRemovedEvent<Type>>
	{
		const Entity entity;
		const Type& component;

		ComponentRemovedEvent(const Entity entity, const Type& component);
	};

	template <typename Type>
	struct ComponentReplacedEvent : Event<ComponentAddedEvent<Type>>
	{
		const Entity entity;
		const Type& oldValue;
		const Type& newValue;

		ComponentReplacedEvent(const Entity entity, const Type& oldValue, const Type& newValue);
	};

	template <typename T, std::size_t PageSize>
	ComponentView<T, PageSize>::ComponentView(SparsePool<T, traits<T>::poolSize()>* pool)
		: _pool(pool)
	{
	}

	template <typename T, std::size_t PageSize>
	inline auto ComponentView<T, PageSize>::begin() noexcept
	{
		return _pool->begin();
	}

	template <typename T, std::size_t PageSize>
	inline const auto ComponentView<T, PageSize>::begin() const noexcept
	{
		return _pool->begin();
	}

	template <typename T, std::size_t PageSize>
	inline const auto ComponentView<T, PageSize>::cbegin() const noexcept
	{
		return _pool->cbegin();
	}

	template <typename T, std::size_t PageSize>
	inline auto ComponentView<T, PageSize>::end() noexcept
	{
		return _pool->end();
	}

	template <typename T, std::size_t PageSize>
	inline const auto ComponentView<T, PageSize>::end() const noexcept
	{
		return _pool->end();
	}

	template <typename T, std::size_t PageSize>
	inline const auto ComponentView<T, PageSize>::cend() const noexcept
	{
		return _pool->cend();
	}

	template <typename ... Ts>
	inline EntityView<Ts...>::ForwardIterator::ForwardIterator(Registry* reg, long long index) noexcept
		: _reg(reg), _index(index)
	{
		while (_index < static_cast<long long>(_reg->_entities.size()) && !_reg->contains<Ts...>(_reg->_entities[_index]))
		{
			++_index;
		}
	}

	template <typename ... Ts>
	inline Entity EntityView<Ts...>::ForwardIterator::operator*() noexcept
	{
		return Entity(_reg, *(_reg->_entities.data() + _index));
	}

	template <typename ... Ts>
	inline const Entity EntityView<Ts...>::ForwardIterator::operator*() const noexcept
	{
		return Entity(_reg, *(_reg->_entities.data() + _index));
	}

	template <typename ... Ts>
	inline typename EntityView<Ts...>::ForwardIterator& EntityView<Ts...>::ForwardIterator::operator++() noexcept
	{
		++_index;
		while (_index < static_cast<long long>(_reg->_entities.size()) && !_reg->contains<Ts...>(_reg->_entities[_index]))
		{
			++_index;
		}
		return *this;
	}

	template <typename ... Ts>
	inline typename EntityView<Ts...>::ForwardIterator EntityView<Ts...>::ForwardIterator::operator++(int) noexcept
	{
		auto tmp = *this;
		++_index;
		while (index < static_cast<long long>(_reg->_entities.size()) && !_reg->contains<Ts...>(_reg->_entities[_index]))
		{
			++_index;
		}
		return tmp;;
	}

	template <typename ... Ts>
	bool EntityView<Ts...>::ForwardIterator::operator==(const ForwardIterator& rhs) const noexcept
	{
		return _index == rhs._index;
	}

	template <typename ... Ts>
	bool EntityView<Ts...>::ForwardIterator::operator!=(const ForwardIterator& rhs) const noexcept
	{
		return _index != rhs._index;
	}

	template <typename ... Ts>
	inline EntityView<Ts...>::EntityView(Registry* reg) noexcept
		: _reg(reg)
	{
	}

	template <typename ... Ts>
	inline auto EntityView<Ts...>::begin() noexcept
	{
		return ForwardIterator(_reg, 0);
	}

	template <typename ... Ts>
	inline const auto EntityView<Ts...>::begin() const noexcept
	{
		return ForwardIterator(_reg, 0);
	}

	template <typename ... Ts>
	inline const auto EntityView<Ts...>::cbegin() const noexcept
	{
		return ForwardIterator(_reg, 0);
	}

	template <typename ... Ts>
	inline auto EntityView<Ts...>::end() noexcept
	{
		return ForwardIterator(_reg, static_cast<long long>(_reg->_entities.size()));
	}

	template <typename ... Ts>
	inline const auto EntityView<Ts...>::end() const noexcept
	{
		return ForwardIterator(_reg, static_cast<long long>(_reg->_entities.size()));
	}

	template <typename ... Ts>
	inline const auto EntityView<Ts...>::cend() const noexcept
	{
		return ForwardIterator(_reg, static_cast<long long>(_reg->_entities.size()));
	}

	template <typename T>
	inline void Registry::assign(const Identifier id, const T& value)
	{
		SparsePool<T>& pool = _assure<T>();
		const T& comp = pool.assign(id, value);
		_events.send<ComponentAddedEvent<T>>(Entity(this, id), comp);
	}

	template <typename T, typename ... Ts>
	inline bool Registry::contains(const Identifier id) const noexcept
	{
		static T family = traits<T>::identifier();
		constexpr size_t poolSize = traits<T>::poolSize();
		const bool res = _memPools.size() > family && _memPools[family] != nullptr ? ((SparsePool<T, poolSize>*) _memPools[family])->contains(id) : false;
		if constexpr (sizeof...(Ts) > 0)
		{
			return res & contains<Ts...>(id);
		}
		else
		{
			return res;
		}
	}

	template <typename T>
	T& Registry::get(const Identifier id) const noexcept
	{
		static T family = traits<T>::identifier();
		constexpr size_t poolSize = traits<T>::poolSize();
		return ((SparsePool<T, poolSize>*) _memPools[family])->get(id);
	}

	template <typename T>
	T* Registry::tryGet(const Identifier id) const noexcept
	{
		static T family = traits<T>::identifier();
		constexpr size_t poolSize = traits<T>::poolSize();
		const auto res = _memPools.size() > family && _memPools[family] != nullptr ? ((SparsePool<T, poolSize>*) _memPools[family])->tryGet(id) : nullptr;
		return res;
	}

	template <typename T>
	inline void Registry::remove(const Identifier id) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		T& value = get<T>(id);
		_events.send<ComponentRemovedEvent<T>>(Entity(this, id), value);
		pool.remove(id);
	}

	template <typename T>
	inline void Registry::replace(const Identifier id, const T& value) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		const std::optional<T> res = pool.replace(id, value);
		if (res.has_value())
		{
			_events.send<ComponentReplacedEvent<T>>(Entity(this, id), res.value(), value);
		}
		else
		{
			_events.send<ComponentAddedEvent<T>>(Entity(this, id), value);
		}
	}

	template <typename T>
	inline ComponentView<T, traits<T>::poolSize()> Registry::view() noexcept
	{
		return ComponentView<T, traits<T>::poolSize()>(&_assure<T>());
	}

	template <typename ... Ts>
	inline EntityView<Ts...> Registry::entities() noexcept
	{
		return EntityView<Ts...>(this);
	}

	template <typename T>
	inline SparsePool<T>& Registry::_assure()
	{
		const auto id = traits<T>::identifier();
		_memPools.resize(static_cast<std::size_t>(id) + 1ull);
		auto pool = _memPools[id];
		if (pool == nullptr)
		{
			constexpr size_t poolSize = traits<T>::poolSize();
			pool = new SparsePool<T, poolSize>();
			_memPools[id] = pool;
		}
		return *((SparsePool<T>*)pool);
	}

	template<typename Type>
	inline ComponentAddedEvent<Type>::ComponentAddedEvent(const Entity entity, const Type& component)
		: entity(entity), component(component)
	{
	}

	template<typename Type>
	inline ComponentRemovedEvent<Type>::ComponentRemovedEvent(const Entity entity, const Type& component)
		: entity(entity), component(component)
	{
	}

	template<typename Type>
	inline ComponentReplacedEvent<Type>::ComponentReplacedEvent(const Entity entity, const Type& oldValue, const Type& newValue)
		: entity(entity), oldValue(oldValue), newValue(newValue)
	{
	}

	template<typename T>
	inline Entity& Entity::assign(const T& value)
	{
		_reg->assign(id(), value);
		return *this;
	}

	template<typename T, typename ...Ts>
	inline bool Entity::contains() const noexcept
	{
		if constexpr (sizeof...(Ts) > 0)
		{
			return _reg->contains<T, Ts...>(id())
		}
		return _reg->contains<T>(id());
	}

	template<typename T>
	inline T& Entity::get() const noexcept
	{
		return _reg->get<T>(id());
	}

	template<typename T>
	inline T* Entity::tryGet() const noexcept
	{
		return _reg->tryGet<T>(id());
	}

	template<typename T>
	inline Entity& Entity::remove()
	{
		_reg->remove<T>(id());
		return *this;
	}

	template<typename T>
	inline Entity& Entity::replace(const T& value)
	{
		_reg->replace<T>(id(), value);
		return *this;
	}

}
