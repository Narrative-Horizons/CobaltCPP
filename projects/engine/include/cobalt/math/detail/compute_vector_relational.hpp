#pragma once

//#include "compute_common.hpp"
#include "setup.hpp"
#include <limits>

namespace cobalt::math{
namespace detail
{
	template <typename T, bool isFloat>
	struct compute_equal
	{
		COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR static bool call(T a, T b)
		{
			return a == b;
		}
	};
/*
	template <typename T>
	struct compute_equal<T, true>
	{
		COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR static bool call(T a, T b)
		{
			return detail::compute_abs<T, std::numeric_limits<T>::is_signed>::call(b - a) <= static_cast<T>(0);
			//return std::memcmp(&a, &b, sizeof(T)) == 0;
		}
	};
*/
}//namespace detail
}//namespace cobalt::math