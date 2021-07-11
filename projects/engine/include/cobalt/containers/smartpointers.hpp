#pragma once

#include <cobalt/assertions.hpp>
#include <cobalt/containers/utility.hpp>

namespace cobalt
{
	using NullPtr = decltype(nullptr);

	template <typename T>
	class UniquePtr
	{
		public:
			UniquePtr() noexcept;
			UniquePtr(NullPtr) noexcept;
			UniquePtr(T* ptr) noexcept;
			UniquePtr(const UniquePtr&) = delete;
			UniquePtr(UniquePtr&& ptr) noexcept;
			~UniquePtr();

			UniquePtr& operator=(const UniquePtr&) = delete;
			UniquePtr& operator=(UniquePtr&& ptr) noexcept;
			UniquePtr& operator=(NullPtr) noexcept;

			T* release();
			void reset();
			void swap(UniquePtr& ptr) noexcept;

			T* get() const noexcept;
			operator bool() const noexcept;

			T& operator*() const;
			T* operator->() const noexcept;
		private:
			T* _payload;
	};

	template <typename T, typename U>
	inline bool operator==(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) noexcept
	{
		return lhs.get() == rhs.get();
	}

	template <typename T>
	inline bool operator==(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() == nullptr;
	}
	
	template <typename T>
	inline bool operator==(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr == rhs.get();
	}

	template <typename T, typename U>
	inline bool operator!=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() != rhs.get();
	}

	template <typename T>
	inline bool operator!=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() != nullptr;
	}

	template <typename T>
	inline bool operator!=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr != rhs.get();
	}

	template <typename T, typename U>
	inline bool operator<(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() < rhs.get();
	}

	template <typename T>
	inline bool operator<(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() < nullptr;
	}

	template <typename T>
	inline bool operator<(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr < rhs.get();
	}

	template <typename T, typename U>
	inline bool operator<=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() <= rhs.get();
	}

	template <typename T>
	inline bool operator<=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() <= nullptr;
	}

	template <typename T>
	inline bool operator<=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr <= rhs.get();
	}

	template <typename T, typename U>
	inline bool operator>(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() > rhs.get();
	}

	template <typename T>
	inline bool operator>(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() > nullptr;
	}

	template <typename T>
	inline bool operator>(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr > rhs.get();
	}

	template <typename T, typename U>
	inline bool operator>=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() >= rhs.get();
	}

	template <typename T>
	inline bool operator>=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() >= nullptr;
	}

	template <typename T>
	inline bool operator>=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr >= rhs.get();
	}

	template<typename T, typename ...Arguments>
	inline UniquePtr<T> make_unique(Arguments && ...args)
	{
		UniquePtr<T> value(new T(forward<Arguments>(args)...));
		return value;
	}
	
	template<typename T>
	inline UniquePtr<T>::UniquePtr() noexcept
		: UniquePtr(nullptr)
	{
	}
	
	template<typename T>
	inline UniquePtr<T>::UniquePtr(NullPtr) noexcept
		: UniquePtr(static_cast<T*>(nullptr))
	{
	}
	
	template<typename T>
	inline UniquePtr<T>::UniquePtr(T* ptr) noexcept
		: _payload(ptr)
	{
	}
	
	template<typename T>
	inline UniquePtr<T>::UniquePtr(UniquePtr&& ptr) noexcept
		: _payload(ptr._payload)
	{
		_payload = nullptr;
	}

	template<typename T>
	inline UniquePtr<T>::~UniquePtr()
	{
		reset();
	}
	
	template<typename T>
	inline UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& ptr) noexcept
	{
		delete _payload;
		_payload = ptr._payload;
		ptr._payload = nullptr;

		return *this;
	}
	
	template<typename T>
	inline UniquePtr<T>& UniquePtr<T>::operator=(NullPtr) noexcept
	{
		delete _payload;
		_payload = nullptr;
		return *this;
	}
	
	template<typename T>
	inline T* UniquePtr<T>::release()
	{
		T* result = _payload;
		_payload = nullptr;
		return result;
	}
	
	template<typename T>
	inline void UniquePtr<T>::reset()
	{
		delete _payload;
		_payload = nullptr;
	}
	
	template<typename T>
	inline void UniquePtr<T>::swap(UniquePtr& ptr) noexcept
	{
		T* tmp = ptr._payload;
		ptr._payload = _payload;
		_payload = tmp;
	}
	
	template<typename T>
	inline T* UniquePtr<T>::get() const noexcept
	{
		return _payload;
	}
	
	template<typename T>
	inline UniquePtr<T>::operator bool() const noexcept
	{
		return _payload != nullptr;
	}
	
	template<typename T>
	inline T& UniquePtr<T>::operator*() const
	{
		return *RequireNotNull(_payload);
	}
	
	template<typename T>
	inline T* UniquePtr<T>::operator->() const noexcept
	{
		return _payload;
	}
}