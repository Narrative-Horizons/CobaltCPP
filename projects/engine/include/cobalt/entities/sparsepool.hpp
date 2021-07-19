#pragma once

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/entities/identifier.hpp>
#include <cobalt/macros.hpp>

#include <cstddef>
#include <optional>
#include <vector>

namespace cobalt
{
	class BaseSparsePool
	{
		public:
			virtual ~BaseSparsePool() = default;
			virtual void remove(const Identifier id) = 0;
	};

	template <typename T>
	class NoOpSparsePool final : public BaseSparsePool
	{
		public:
			NoOpSparsePool();
			COBALT_NO_COPY_MOVE(NoOpSparsePool);

			void reserve(const std::size_t capacity);
			void shrinkToFit();
			T& assign(const Identifier id, const T& value);
			T& assign(const Identifier id, T&& value);
			COBALT_NO_DISCARD bool contains(const Identifier id) const noexcept;
			Identifier identityAt(const std::size_t index) const noexcept;
			T& get(const Identifier id) const noexcept;
			T* tryGet(const Identifier id) const noexcept;
			std::optional<T> replace(const Identifier id, const T& value);
			std::optional<T> replace(const Identifier id, T&& value);
			void remove(const Identifier id) override;
	};

	template <typename T, std::size_t PageSize = 4096>
	class SparsePool final : public BaseSparsePool
	{
		public:
			using size_type = std::size_t;
			using page_type = UniquePtr<Identifier[]>;

		private:
			COBALT_NO_DISCARD static constexpr size_type _page(const Identifier id) noexcept
			{
				return id.index / PageSize;
			}

			COBALT_NO_DISCARD static constexpr size_t _offset(const Identifier id) noexcept
			{
				return id.index & (PageSize - 1);
			}

			COBALT_NO_DISCARD page_type& _assure(const std::size_t page);

		public:
			SparsePool() = default;
			COBALT_NO_COPY_MOVE(SparsePool);

			void reserve(const std::size_t capacity);
			void shrinkToFit();
			T& assign(const Identifier id, const T& value);
			T& assign(const Identifier id, T&& value);
			COBALT_NO_DISCARD bool contains(const Identifier id) const noexcept;
			Identifier identityAt(const std::size_t index) const noexcept;
			T& get(const Identifier id) const noexcept;
			T* tryGet(const Identifier id) const noexcept;
			std::optional<T> replace(const Identifier id, const T& value);
			std::optional<T> replace(const Identifier id, T&& value);
			void remove(const Identifier id) override;

			auto begin() noexcept;
			const auto begin() const noexcept;
			const auto cbegin() const noexcept;

			auto end() noexcept;
			const auto end() const noexcept;
			const auto cend() const noexcept;
			
		private:
			std::vector<UniquePtr<Identifier[]>> _sparse;
			std::vector<Identifier> _packed;
			std::vector<T> _components;
	};

	template <typename T>
	void NoOpSparsePool<T>::reserve(const std::size_t capacity)
	{
	}

	template <typename T>
	void NoOpSparsePool<T>::shrinkToFit()
	{
	}

	template <typename T>
	T& NoOpSparsePool<T>::assign(const Identifier id, const T& value)
	{
		return value;
	}

	template <typename T>
	T& NoOpSparsePool<T>::assign(const Identifier id, T&& value)
	{
		return value;
	}

	template <typename T>
	bool NoOpSparsePool<T>::contains(const Identifier id) const noexcept
	{
		return false;
	}

	template <typename T>
	Identifier NoOpSparsePool<T>::identityAt(const std::size_t index) const noexcept
	{
		return Identifier::Invalid;
	}

	template <typename T>
	T& NoOpSparsePool<T>::get(const Identifier id) const noexcept
	{
		return *get();
	}

	template <typename T>
	T* NoOpSparsePool<T>::tryGet(const Identifier id) const noexcept
	{
		return nullptr;
	}

	template <typename T>
	std::optional<T> NoOpSparsePool<T>::replace(const Identifier id, const T& value)
	{
		return std::optional<T>();
	}

	template <typename T>
	std::optional<T> NoOpSparsePool<T>::replace(const Identifier id, T&& value)
	{
		return std::optional<T>();
	}

	template <typename T>
	void NoOpSparsePool<T>::remove(const Identifier id)
	{
	}

	template <typename T, std::size_t PageSize>
	typename SparsePool<T, PageSize>::page_type& SparsePool<T, PageSize>::_assure(const std::size_t page)
	{
		if (page >= _sparse.size())
		{
			_sparse.reserve(page + 1);
		}

		while (page >= _sparse.size())
		{
			UniquePtr<Identifier[]> pg = MakeUnique<Identifier[]>(PageSize);
			for (size_t i = 0; i < PageSize; ++i)
			{
				pg[i] = Identifier::Invalid;
			}
			_sparse.push_back(cobalt::move(pg));
		}

		return _sparse[page];
	}

	template <typename T, std::size_t PageSize>
	void SparsePool<T, PageSize>::reserve(const std::size_t capacity)
	{
		// Assure that there are enough sparse pages
		const auto page = capacity / PageSize;
		_assure(page);
		
		// Reserve memory in the packed and value payloads
		_payload.reserve(capacity);
		_packed.reserve(capacity);
	}

	template <typename T, std::size_t PageSize>
	void SparsePool<T, PageSize>::shrinkToFit()
	{
		if (_packed.empty())
		{
			_sparse.clear();
		}
		else
		{
			_sparse.shrink_to_fit();
			_packed.shrink_to_fit();
			_components.shrink_to_fit();
		}
	}

	template <typename T, std::size_t PageSize>
	T& SparsePool<T, PageSize>::assign(const Identifier id, const T& value)
	{
		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		page_type& page = _assure(pg);

		if (page[offset] == Identifier::Invalid)
		{
			Identifier i = { static_cast<std::uint32_t>(_components.size()), 0u };
			page[offset] = i;
			_packed.emplace_back(id);
			return _components.emplace_back(value);
		}
		else
		{
			Identifier i = page[offset];
			_components[i.index] = value;
			return _components[i.index];
		}
	}

	template <typename T, std::size_t PageSize>
	T& SparsePool<T, PageSize>::assign(const Identifier id, T&& value)
	{
		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		page_type& page = _assure(pg);
		
		if (page[offset] == Identifier::Invalid)
		{
			Identifier i = { static_cast<std::uint32_t>(_components.size()), 0u };
			page[offset] = i;
			_packed.emplace_back(id);
			return _components.emplace_back(forward<T>(value));
		}
		else
		{
			Identifier i = page[offset];
			_components[i.index] = forward<T>(value);
			return _components[i.index];
		}
	}

	template <typename T, std::size_t PageSize>
	bool SparsePool<T, PageSize>::contains(const Identifier id) const noexcept
	{
		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		return pg < _sparse.size() ? _sparse[pg][offset] != Identifier::Invalid : false;
	}

	template <typename T, std::size_t PageSize>
	Identifier SparsePool<T, PageSize>::identityAt(const std::size_t index) const noexcept
	{
		return index < _packed.size() ? _packed[index] : Identifier::Invalid;
	}

	template <typename T, std::size_t PageSize>
	T& SparsePool<T, PageSize>::get(const Identifier id) const noexcept
	{
		return *tryGet(id);
	}

	template <typename T, std::size_t PageSize>
	T* SparsePool<T, PageSize>::tryGet(const Identifier id) const noexcept
	{
		T* result = nullptr;

		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		if (pg < _sparse.size())
		{
			Identifier sparseId = _sparse[pg][offset];
			if (sparseId != Identifier::Invalid)
			{
				return _components.data() + sparseId.index;
			}
		};

		return result;
	}

	template <typename T, std::size_t PageSize>
	std::optional<T> SparsePool<T, PageSize>::replace(const Identifier id, const T& value)
	{
		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		page_type& page = _assure(pg);

		if (page[offset] == Identifier::Invalid)
		{
			return std::optional<T>();
		}
		else
		{
			Identifier i = page[offset];
			std::optional<T> prev(_components[i.index]);
			_components[i.index] = value;
			return prev;
		}
	}

	template <typename T, std::size_t PageSize>
	std::optional<T> SparsePool<T, PageSize>::replace(const Identifier id, T&& value)
	{
		const size_t pg = _page(id);
		const size_t offset = _offset(id);

		page_type& page = _assure(pg);

		if (page[offset] == Identifier::Invalid)
		{
			return std::optional<T>();
		}
		else
		{
			Identifier i = page[offset];
			std::optional<T> prev(_components[i.index]);
			_components[i.index] = forward<T>(value);
			return prev;
		}
	}

	template <typename T, std::size_t PageSize>
	void SparsePool<T, PageSize>::remove(const Identifier id)
	{
		const auto pg = _page(id);
		const auto offset = _offset(id);
		if (pg < _sparse.size())
		{
			const auto& sparseId = _sparse[pg][offset];
			if (sparseId != Identifier::Invalid)
			{
				const auto packedIdx = sparseId.index;
				const auto& last = _components.back();
				_components[packedIdx] = last;
				_components.pop_back();

				const auto back = _packed.back();
				const auto backPg = _page(back);
				const auto backOffset = _offset(back);
				_packed[_packed.size() - 1] = id;
				_sparse[backPg][backOffset] = sparseId;
				_sparse[pg][offset] = Identifier::Invalid;
				_packed.pop_back();
			}
		}
	}

	template <typename T, std::size_t PageSize>
	auto SparsePool<T, PageSize>::begin() noexcept
	{
		return _components.begin();
	}

	template <typename T, std::size_t PageSize>
	const auto SparsePool<T, PageSize>::begin() const noexcept
	{
		return _components.begin();
	}

	template <typename T, std::size_t PageSize>
	const auto SparsePool<T, PageSize>::cbegin() const noexcept
	{
		return _components.cbegin();
	}

	template <typename T, std::size_t PageSize>
	auto SparsePool<T, PageSize>::end() noexcept
	{
		return _components.end();
	}

	template <typename T, std::size_t PageSize>
	const auto SparsePool<T, PageSize>::end() const noexcept
	{
		return _components.end();
	}

	template <typename T, std::size_t PageSize>
	const auto SparsePool<T, PageSize>::cend() const noexcept
	{
		return _components.cend();
	}
}