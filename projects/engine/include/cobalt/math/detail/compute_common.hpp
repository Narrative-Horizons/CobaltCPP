#pragma once

#include "setup.hpp"
#include <limits>

namespace cobalt::math{
namespace detail
{
	template<typename genFIType, bool /*signed*/>
	struct compute_abs
	{};

	template<typename genFIType>
	struct compute_abs<genFIType, true>
	{
		COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR static genFIType call(genFIType x)
		{
			COBALT_STATIC_ASSERT(
				std::numeric_limits<genFIType>::is_iec559 || std::numeric_limits<genFIType>::is_signed,
				"'abs' only accept floating-point and integer scalar or vector inputs");

			return x >= genFIType(0) ? x : -x;
			// TODO, perf comp with: *(((int *) &x) + 1) &= 0x7fffffff;
		}
	};

#if COBALT_COMPILER & COBALT_COMPILER_CUDA
	template<>
	struct compute_abs<float, true>
	{
		COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR static float call(float x)
		{
			return fabsf(x);
		}
	};
#endif

	template<typename genFIType>
	struct compute_abs<genFIType, false>
	{
		COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR static genFIType call(genFIType x)
		{
			COBALT_STATIC_ASSERT(
				(!std::numeric_limits<genFIType>::is_signed && std::numeric_limits<genFIType>::is_integer),
				"'abs' only accept floating-point and integer scalar or vector inputs");
			return x;
		}
	};
}//namespace detail
}//namespace cobalt::math
