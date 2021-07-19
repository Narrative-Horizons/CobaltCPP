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

	template <typename T>
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

			ComponentView(SparsePool<T>* pool);

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
			
		private:
			Identifier _createNewId();
			Identifier _recycleId();

			std::vector<Identifier> _entities;
			std::vector<BaseSparsePool*> _memPools;
			Identifier _nextAvailable = Identifier::Invalid;

			template <typename T>
			SparsePool<T>& _assure();
	};

	template <typename T>
	auto ComponentView<T>::begin() noexcept
	{
		return _pool->begin();
	}

	template <typename T>
	const auto ComponentView<T>::begin() const noexcept
	{
		return _pool->begin();
	}

	template <typename T>
	const auto ComponentView<T>::cbegin() const noexcept
	{
		return _pool->cbegin();
	}

	template <typename T>
	auto ComponentView<T>::end() noexcept
	{
		return _pool->end();
	}

	template <typename T>
	const auto ComponentView<T>::end() const noexcept
	{
		return _pool->end();
	}

	template <typename T>
	const auto ComponentView<T>::cend() const noexcept
	{
		return _pool->cend();
	}

	template <typename T>
	void Registry::assign(const Identifier id, const T& value)
	{
		SparsePool<T>& pool = _assure<T>();
		pool.assign(id, value);
	}

	template <typename T>
	bool Registry::contains(const Identifier id) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		return pool.contains(id);
	}

	template <typename T1, typename T2, typename ... Ts>
	bool Registry::contains(const Identifier id) const noexcept
	{
		if constexpr (sizeof...(Ts) == 0)
		{
			return contains<T1>(id) && contains<T2>(id);
		}
	}

	template <typename T>
	void Registry::remove(const Identifier id) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		pool.remove(id);
	}

	template <typename T>
	void Registry::replace(const Identifier id, const T& value) const noexcept
	{
		SparsePool<T>& pool = _assure<T>();
		pool.replace(id, value);
	}

	template <typename T>
	SparsePool<T>& Registry::_assure()
	{
		const auto id = traits<T>::identifier();
		_memPools.reserve(id + 1);
		auto pool = _memPools[id]
		if (pool != nullptr)
		{
			constexpr size_t poolSize = traits<T>::poolSize();
			pool = new SparsePool<T, poolSize>();
			_memPools[id] = pool;
		}
		return *pool;
	}

}
