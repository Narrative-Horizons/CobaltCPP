/// @ref core
/// @file glm/detail/func_exponential_simd.inl

#include "../simd/exponential.h"

#if COBALT_ARCH & COBALT_ARCH_SSE2_BIT

namespace cobalt::math{
namespace detail
{
	template<qualifier Q>
	struct compute_sqrt<4, float, Q, true>
	{
		COBALT_FUNC_QUALIFIER static vec<4, float, Q> call(vec<4, float, Q> const& v)
		{
			vec<4, float, Q> Result;
			Result.data = _mm_sqrt_ps(v.data);
			return Result;
		}
	};

#	if COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_ENABLE
	template<>
	struct compute_sqrt<4, float, aligned_lowp, true>
	{
		COBALT_FUNC_QUALIFIER static vec<4, float, aligned_lowp> call(vec<4, float, aligned_lowp> const& v)
		{
			vec<4, float, aligned_lowp> Result;
			Result.data = cobalt_vec4_sqrt_lowp(v.data);
			return Result;
		}
	};
#	endif
}//namespace detail
}//namespace cobalt::math

#endif//COBALT_ARCH & COBALT_ARCH_SSE2_BIT
