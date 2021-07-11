#pragma once

namespace cobalt
{
	namespace detail
	{
		void* RequireNotNullImpl(void* ptr);
	}

	template <typename T>
	T* RequireNotNull(T* ptr)
	{
		return static_cast<T*>(detail::RequireNotNullImpl(ptr));
	}
}