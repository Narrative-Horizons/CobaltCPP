#pragma once

#include <cobalt/assertions.hpp>
#include <cobalt/containers/utility.hpp>
#include <cobalt/macros.hpp>

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

	namespace detail
	{
		template <typename T>
		struct RefCountPtrControlBlock
		{
			T* ptr;
			long owningReferenceCount;
			long weakReferenceCount;
		};
	}

	template <typename T>
	class WeakPtr;

	template <typename T>
	class SharedPtr
	{
	public:
		SharedPtr() noexcept;
		explicit SharedPtr(NullPtr) noexcept;
		explicit SharedPtr(T* ptr) noexcept;
		SharedPtr(const SharedPtr& ptr);
		SharedPtr(SharedPtr&& ptr) noexcept;
		~SharedPtr();

		SharedPtr& operator=(const SharedPtr& ptr);
		SharedPtr& operator=(SharedPtr&& ptr) noexcept;
		SharedPtr& operator=(NullPtr) noexcept;

		void reset();
		void swap(SharedPtr& ptr) noexcept;

		T* get() const noexcept;
		explicit operator bool() const noexcept;

		T& operator*() const;
		T* operator->() const noexcept;

		COBALT_NO_DISCARD long useCount() const noexcept;

	private:
		friend class WeakPtr<T>;

		detail::RefCountPtrControlBlock<T>* _payload;
	};

	template <typename T>
	class WeakPtr
	{
	public:
		WeakPtr();
		WeakPtr(const WeakPtr& ptr);
		WeakPtr(WeakPtr&& ptr) noexcept;
		explicit WeakPtr(const SharedPtr<T>& ptr);
		~WeakPtr();

		WeakPtr& operator=(const WeakPtr& ptr);
		WeakPtr& operator=(WeakPtr&& ptr) noexcept;
		WeakPtr& operator=(const SharedPtr<T>& ptr);
		WeakPtr& operator=(NullPtr);

		void reset();
		void swap(WeakPtr& ptr) noexcept;

		COBALT_NO_DISCARD long useCount() const noexcept;
		COBALT_NO_DISCARD bool expired() const noexcept;
		SharedPtr<T> lock();
	private:
		detail::RefCountPtrControlBlock<T>* _payload;
	};

	// Implementation

	template <typename T, typename U>
	bool operator==(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) noexcept
	{
		return lhs.get() == rhs.get();
	}

	template <typename T>
	bool operator==(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() == nullptr;
	}

	template <typename T>
	bool operator==(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr == rhs.get();
	}

	template <typename T, typename U>
	bool operator!=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() != rhs.get();
	}

	template <typename T>
	bool operator!=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() != nullptr;
	}

	template <typename T>
	bool operator!=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr != rhs.get();
	}

	template <typename T, typename U>
	bool operator<(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() < rhs.get();
	}

	template <typename T>
	bool operator<(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() < nullptr;
	}

	template <typename T>
	bool operator<(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr < rhs.get();
	}

	template <typename T, typename U>
	bool operator<=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() <= rhs.get();
	}

	template <typename T>
	bool operator<=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() <= nullptr;
	}

	template <typename T>
	bool operator<=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr <= rhs.get();
	}

	template <typename T, typename U>
	bool operator>(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() > rhs.get();
	}

	template <typename T>
	bool operator>(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() > nullptr;
	}

	template <typename T>
	bool operator>(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr > rhs.get();
	}

	template <typename T, typename U>
	bool operator>=(const UniquePtr<T>& lhs, const UniquePtr<U>& rhs)
	{
		return lhs.get() >= rhs.get();
	}

	template <typename T>
	bool operator>=(const UniquePtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() >= nullptr;
	}

	template <typename T>
	bool operator>=(NullPtr, const UniquePtr<T>& rhs) noexcept
	{
		return nullptr >= rhs.get();
	}

	template <typename T, typename ...Arguments>
	UniquePtr<T> MakeUnique(Arguments&& ...args)
	{
		UniquePtr<T> value(new T(forward<Arguments>(args)...));
		return value;
	}

	template <typename T>
	UniquePtr<T>::UniquePtr() noexcept
		: UniquePtr(nullptr)
	{
	}

	template <typename T>
	UniquePtr<T>::UniquePtr(NullPtr) noexcept
		: UniquePtr(static_cast<T*>(nullptr))
	{
	}

	template <typename T>
	UniquePtr<T>::UniquePtr(T* ptr) noexcept
		: _payload(ptr)
	{
	}

	template <typename T>
	UniquePtr<T>::UniquePtr(UniquePtr&& ptr) noexcept
		: _payload(ptr._payload)
	{
		ptr._payload = nullptr;
	}

	template <typename T>
	UniquePtr<T>::~UniquePtr()
	{
		reset();
	}

	template <typename T>
	UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& ptr) noexcept
	{
		delete _payload;
		_payload = ptr._payload;
		ptr._payload = nullptr;

		return *this;
	}

	template <typename T>
	UniquePtr<T>& UniquePtr<T>::operator=(NullPtr) noexcept
	{
		delete _payload;
		_payload = nullptr;
		return *this;
	}

	template <typename T>
	T* UniquePtr<T>::release()
	{
		T* result = _payload;
		_payload = nullptr;
		return result;
	}

	template <typename T>
	void UniquePtr<T>::reset()
	{
		delete _payload;
		_payload = nullptr;
	}

	template <typename T>
	void UniquePtr<T>::swap(UniquePtr& ptr) noexcept
	{
		T* tmp = ptr._payload;
		ptr._payload = _payload;
		_payload = tmp;
	}

	template <typename T>
	T* UniquePtr<T>::get() const noexcept
	{
		return _payload;
	}

	template <typename T>
	UniquePtr<T>::operator bool() const noexcept
	{
		return _payload != nullptr;
	}

	template <typename T>
	T& UniquePtr<T>::operator*() const
	{
		return *RequireNotNull(_payload);
	}

	template <typename T>
	T* UniquePtr<T>::operator->() const noexcept
	{
		return _payload;
	}

	template <typename T, typename U>
	bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) noexcept
	{
		return lhs.get() == rhs.get();
	}

	template <typename T>
	bool operator==(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() == nullptr;
	}

	template <typename T>
	bool operator==(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr == rhs.get();
	}

	template <typename T, typename U>
	bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
	{
		return lhs.get() != rhs.get();
	}

	template <typename T>
	bool operator!=(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() != nullptr;
	}

	template <typename T>
	bool operator!=(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr != rhs.get();
	}

	template <typename T, typename U>
	bool operator<(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
	{
		return lhs.get() < rhs.get();
	}

	template <typename T>
	bool operator<(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() < nullptr;
	}

	template <typename T>
	bool operator<(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr < rhs.get();
	}

	template <typename T, typename U>
	bool operator<=(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
	{
		return lhs.get() <= rhs.get();
	}

	template <typename T>
	bool operator<=(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() <= nullptr;
	}

	template <typename T>
	bool operator<=(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr <= rhs.get();
	}

	template <typename T, typename U>
	bool operator>(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
	{
		return lhs.get() > rhs.get();
	}

	template <typename T>
	bool operator>(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() > nullptr;
	}

	template <typename T>
	bool operator>(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr > rhs.get();
	}

	template <typename T, typename U>
	bool operator>=(const SharedPtr<T>& lhs, const SharedPtr<U>& rhs)
	{
		return lhs.get() >= rhs.get();
	}

	template <typename T>
	bool operator>=(const SharedPtr<T>& lhs, NullPtr) noexcept
	{
		return lhs.get() >= nullptr;
	}

	template <typename T>
	bool operator>=(NullPtr, const SharedPtr<T>& rhs) noexcept
	{
		return nullptr >= rhs.get();
	}

	template <typename T, typename ...Arguments>
	SharedPtr<T> MakeShared(Arguments&& ...args)
	{
		SharedPtr<T> value(new T(forward<Arguments>(args)...));
		return value;
	}

	template <typename T>
	SharedPtr<T>::SharedPtr() noexcept
		: SharedPtr(nullptr)
	{
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(NullPtr) noexcept
		: SharedPtr(static_cast<T*>(nullptr))
	{
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(T* ptr) noexcept
	{
		if (ptr == nullptr)
		{
			_payload = nullptr;
		}
		else
		{
			_payload = new detail::RefCountPtrControlBlock<T>();
			_payload->ptr = ptr;
			_payload->owningReferenceCount = 1;
			_payload->weakReferenceCount = 0;
		}
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr& ptr)
		: _payload(ptr._payload)
	{
		if (_payload && _payload->ptr != nullptr)
		{
			_payload->owningReferenceCount += 1;
		}
	}

	template <typename T>
	SharedPtr<T>::SharedPtr(SharedPtr&& ptr) noexcept
		: _payload(ptr._payload)
	{
		ptr._payload = nullptr;
	}

	template <typename T>
	SharedPtr<T>::~SharedPtr()
	{
		reset();
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& ptr)
	{
		if (this == &ptr)
			return *this;

		reset();

		_payload = ptr._payload;

		// If an object is owned, increase the owning reference count
		if (_payload && _payload->ptr != nullptr)
		{
			_payload->owningReferenceCount += 1;
		}

		return *this;
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& ptr) noexcept
	{
		reset();

		_payload = ptr._payload;
		ptr._payload = nullptr;

		return *this;
	}

	template <typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(NullPtr) noexcept
	{
		reset();

		_payload = nullptr;

		return *this;
	}

	template <typename T>
	void SharedPtr<T>::reset()
	{
		if (_payload != nullptr)
		{
			_payload->owningReferenceCount -= 1;

			// release the owned pointer if the owning reference count is 0
			if (_payload->owningReferenceCount == 0)
			{
				delete _payload->ptr;
				_payload->ptr = nullptr;

				if (_payload->weakReferenceCount == 0)
				{
					delete _payload;
				}
			}
		}

		_payload = nullptr;
	}

	template <typename T>
	void SharedPtr<T>::swap(SharedPtr& ptr) noexcept
	{
		auto control = _payload;
		_payload = ptr._payload;
		ptr._payload = control;
	}

	template <typename T>
	T* SharedPtr<T>::get() const noexcept
	{
		return _payload ? _payload->ptr : nullptr;
	}

	template <typename T>
	SharedPtr<T>::operator bool() const noexcept
	{
		return get() != nullptr;
	}

	template <typename T>
	T& SharedPtr<T>::operator*() const
	{
		return *RequireNotNull(get());
	}

	template <typename T>
	T* SharedPtr<T>::operator->() const noexcept
	{
		return get();
	}

	template <typename T>
	long SharedPtr<T>::useCount() const noexcept
	{
		return _payload ? _payload->owningReferenceCount : 0;
	}

	template <typename T>
	WeakPtr<T>::WeakPtr()
	{
		_payload = nullptr;
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(const WeakPtr& ptr)
		: _payload(ptr._payload)
	{
		if (_payload != nullptr && _payload->ptr != nullptr)
		{
			_payload->weakReferenceCount += 1;
		}
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(WeakPtr&& ptr) noexcept
		: _payload(ptr._payload)
	{
		ptr._payload = nullptr;
	}

	template <typename T>
	WeakPtr<T>::WeakPtr(const SharedPtr<T>& ptr)
		: _payload(ptr._payload)
	{
	}

	template <typename T>
	WeakPtr<T>::~WeakPtr()
	{
		reset();
	}

	template <typename T>
	WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& ptr)
	{
		if (this == &ptr)
			return *this;

		reset();

		_payload = ptr._payload;

		if (_payload != nullptr)
		{
			_payload->weakReferenceCount += 1;
		}

		return *this;
	}

	template <typename T>
	WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& ptr) noexcept
	{
		reset();

		_payload = ptr._payload;
		ptr._payload = nullptr;

		return *this;
	}

	template <typename T>
	WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& ptr)
	{
		reset();

		_payload = ptr._payload;
		if (_payload != nullptr)
		{
			_payload->weakReferenceCount += 1;
		}

		return *this;
	}

	template <typename T>
	WeakPtr<T>& WeakPtr<T>::operator=(NullPtr)
	{
		reset();
		_payload = nullptr;
		return *this;
	}

	template <typename T>
	void WeakPtr<T>::reset()
	{
		if (_payload)
		{
			_payload->weakReferenceCount -= 1;
			if (_payload->owningReferenceCount == 0 && _payload->weakReferenceCount == 0)
			{
				delete _payload;
			}
		}
	}

	template <typename T>
	void WeakPtr<T>::swap(WeakPtr& ptr) noexcept
	{
		auto tmp = ptr._payload;
		ptr._payload = _payload;
		_payload = tmp;
	}

	template <typename T>
	long WeakPtr<T>::useCount() const noexcept
	{
		return _payload ? _payload->owningReferenceCount : 0;
	}

	template <typename T>
	bool WeakPtr<T>::expired() const noexcept
	{
		return useCount() == 0;
	}

	template <typename T>
	SharedPtr<T> WeakPtr<T>::lock()
	{
		SharedPtr<T> res;
		if (_payload != nullptr && _payload->ptr != nullptr)
		{
			res._payload = _payload;
			res._payload->owningReferenceCount += 1;
		}
		return res;
	}
}
