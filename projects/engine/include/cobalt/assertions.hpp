#pragma once

namespace cobalt
{
	namespace detail
	{
		void* RequireNotNullImpl(void* ptr);
		bool RequireTrueImpl(const bool value);
	}

	void Require(bool condition);

	template <typename T>
	T* RequireNotNull(T* ptr)
	{
		return static_cast<T*>(detail::RequireNotNullImpl(ptr));
	}

	template <typename T>
	bool RequireLessThan(const T& left, const T& right)
	{
		return detail::RequireTrueImpl(left < right);
	}
}