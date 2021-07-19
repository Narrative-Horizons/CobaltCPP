#pragma once

#include <cobalt/entities/identifier.hpp>
#include <cobalt/entities/sparsepool.hpp>
#include <cobalt/entities/traits.hpp>
#include <cobalt/macros.hpp>

#include <cstdint>
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

			template <typename T>
			bool contains(const Identifier id) const noexcept;

			template <typename T1, typename T2, typename ... Ts>
			bool contains(const Identifier id) const noexcept;

			template <typename T>
			void remove(const Identifier id) const noexcept;

			template <typename T>
			void replace(const Identifier id, const T& value) const noexcept;

			template <typename T>
			ComponentView<T, traits<T>::poolSize()> view() noexcept;
			
		private:
			Identifier _createNewId();
			Identifier _recycleId();

			std::vector<Identifier> _entities;
			std::vector<BaseSparsePool*> _memPools;
			Identifier _nextAvailable = Identifier::Invalid;

			template <typename T>
			SparsePool<T>& _assure();
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

	template <typename T>
	inline void Registry::assign(const Identifier id, const T& value)
	{
		SparsePool<T>& pool = _assure<T>();
		pool.assign(id, value);
	}

	template <typename T>
	inline bool Registry::contains(const Identifier id) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		return pool.contains(id);
	}

	template <typename T1, typename T2, typename ... Ts>
	inline bool Registry::contains(const Identifier id) const noexcept
	{
		if constexpr (sizeof...(Ts) == 0)
		{
			return contains<T1>(id) && contains<T2>(id);
		}
	}

	template <typename T>
	inline void Registry::remove(const Identifier id) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		pool.remove(id);
	}

	template <typename T>
	inline void Registry::replace(const Identifier id, const T& value) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		pool.replace(id, value);
	}

	template<typename T>
	inline ComponentView<T, traits<T>::poolSize()> Registry::view() noexcept
	{
		return ComponentView<T, traits<T>::poolSize()>(&_assure<T>());
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

}
