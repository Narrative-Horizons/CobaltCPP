/// @ref simd
/// @file glm/simd/experimental.h

#pragma once

#include "platform.h"

#if COBALT_ARCH & COBALT_ARCH_SSE2_BIT

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_sqrt_lowp(cobalt_f32vec4 x)
{
	return _mm_mul_ss(_mm_rsqrt_ss(x), x);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_sqrt_lowp(cobalt_f32vec4 x)
{
	return _mm_mul_ps(_mm_rsqrt_ps(x), x);
}

#endif//COBALT_ARCH & COBALT_ARCH_SSE2_BIT
