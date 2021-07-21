/// @ref simd
/// @file glm/simd/geometric.h

#pragma once

#include "common.h"

#if COBALT_ARCH & COBALT_ARCH_SSE2_BIT

COBALT_FUNC_DECL cobalt_vec4 cobalt_vec4_dot(cobalt_vec4 v1, cobalt_vec4 v2);
COBALT_FUNC_DECL cobalt_vec4 cobalt_vec1_dot(cobalt_vec4 v1, cobalt_vec4 v2);

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_length(cobalt_vec4 x)
{
	cobalt_vec4 const dot0 = cobalt_vec4_dot(x, x);
	cobalt_vec4 const sqt0 = _mm_sqrt_ps(dot0);
	return sqt0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_distance(cobalt_vec4 p0, cobalt_vec4 p1)
{
	cobalt_vec4 const sub0 = _mm_sub_ps(p0, p1);
	cobalt_vec4 const len0 = cobalt_vec4_length(sub0);
	return len0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_dot(cobalt_vec4 v1, cobalt_vec4 v2)
{
#	if COBALT_ARCH & COBALT_ARCH_AVX_BIT
		return _mm_dp_ps(v1, v2, 0xff);
#	elif COBALT_ARCH & COBALT_ARCH_SSE3_BIT
		cobalt_vec4 const mul0 = _mm_mul_ps(v1, v2);
		cobalt_vec4 const hadd0 = _mm_hadd_ps(mul0, mul0);
		cobalt_vec4 const hadd1 = _mm_hadd_ps(hadd0, hadd0);
		return hadd1;
#	else
		cobalt_vec4 const mul0 = _mm_mul_ps(v1, v2);
		cobalt_vec4 const swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
		cobalt_vec4 const add0 = _mm_add_ps(mul0, swp0);
		cobalt_vec4 const swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
		cobalt_vec4 const add1 = _mm_add_ps(add0, swp1);
		return add1;
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec1_dot(cobalt_vec4 v1, cobalt_vec4 v2)
{
#	if COBALT_ARCH & COBALT_ARCH_AVX_BIT
		return _mm_dp_ps(v1, v2, 0xff);
#	elif COBALT_ARCH & COBALT_ARCH_SSE3_BIT
		cobalt_vec4 const mul0 = _mm_mul_ps(v1, v2);
		cobalt_vec4 const had0 = _mm_hadd_ps(mul0, mul0);
		cobalt_vec4 const had1 = _mm_hadd_ps(had0, had0);
		return had1;
#	else
		cobalt_vec4 const mul0 = _mm_mul_ps(v1, v2);
		cobalt_vec4 const mov0 = _mm_movehl_ps(mul0, mul0);
		cobalt_vec4 const add0 = _mm_add_ps(mov0, mul0);
		cobalt_vec4 const swp1 = _mm_shuffle_ps(add0, add0, 1);
		cobalt_vec4 const add1 = _mm_add_ss(add0, swp1);
		return add1;
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_cross(cobalt_vec4 v1, cobalt_vec4 v2)
{
	cobalt_vec4 const swp0 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1));
	cobalt_vec4 const swp1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 1, 0, 2));
	cobalt_vec4 const swp2 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 0, 2, 1));
	cobalt_vec4 const swp3 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 1, 0, 2));
	cobalt_vec4 const mul0 = _mm_mul_ps(swp0, swp3);
	cobalt_vec4 const mul1 = _mm_mul_ps(swp1, swp2);
	cobalt_vec4 const sub0 = _mm_sub_ps(mul0, mul1);
	return sub0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_normalize(cobalt_vec4 v)
{
	cobalt_vec4 const dot0 = cobalt_vec4_dot(v, v);
	cobalt_vec4 const isr0 = _mm_rsqrt_ps(dot0);
	cobalt_vec4 const mul0 = _mm_mul_ps(v, isr0);
	return mul0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_faceforward(cobalt_vec4 N, cobalt_vec4 I, cobalt_vec4 Nref)
{
	cobalt_vec4 const dot0 = cobalt_vec4_dot(Nref, I);
	cobalt_vec4 const sgn0 = cobalt_vec4_sign(dot0);
	cobalt_vec4 const mul0 = _mm_mul_ps(sgn0, _mm_set1_ps(-1.0f));
	cobalt_vec4 const mul1 = _mm_mul_ps(N, mul0);
	return mul1;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_reflect(cobalt_vec4 I, cobalt_vec4 N)
{
	cobalt_vec4 const dot0 = cobalt_vec4_dot(N, I);
	cobalt_vec4 const mul0 = _mm_mul_ps(N, dot0);
	cobalt_vec4 const mul1 = _mm_mul_ps(mul0, _mm_set1_ps(2.0f));
	cobalt_vec4 const sub0 = _mm_sub_ps(I, mul1);
	return sub0;
}

COBALT_FUNC_QUALIFIER __m128 cobalt_vec4_refract(cobalt_vec4 I, cobalt_vec4 N, cobalt_vec4 eta)
{
	cobalt_vec4 const dot0 = cobalt_vec4_dot(N, I);
	cobalt_vec4 const mul0 = _mm_mul_ps(eta, eta);
	cobalt_vec4 const mul1 = _mm_mul_ps(dot0, dot0);
	cobalt_vec4 const sub0 = _mm_sub_ps(_mm_set1_ps(1.0f), mul0);
	cobalt_vec4 const sub1 = _mm_sub_ps(_mm_set1_ps(1.0f), mul1);
	cobalt_vec4 const mul2 = _mm_mul_ps(sub0, sub1);

	if(_mm_movemask_ps(_mm_cmplt_ss(mul2, _mm_set1_ps(0.0f))) == 0)
		return _mm_set1_ps(0.0f);

	cobalt_vec4 const sqt0 = _mm_sqrt_ps(mul2);
	cobalt_vec4 const mad0 = cobalt_vec4_fma(eta, dot0, sqt0);
	cobalt_vec4 const mul4 = _mm_mul_ps(mad0, N);
	cobalt_vec4 const mul5 = _mm_mul_ps(eta, I);
	cobalt_vec4 const sub2 = _mm_sub_ps(mul5, mul4);

	return sub2;
}

#endif//COBALT_ARCH & COBALT_ARCH_SSE2_BIT
