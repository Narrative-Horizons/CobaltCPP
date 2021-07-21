/// @ref simd
/// @file glm/simd/common.h

#pragma once

#include "platform.h"

#if COBALT_ARCH & COBALT_ARCH_SSE2_BIT

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_add(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_add_ps(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_add(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_add_ss(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_sub(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_sub_ps(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_sub(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_sub_ss(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_mul(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_mul_ps(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_mul(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_mul_ss(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_div(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_div_ps(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_div(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return _mm_div_ss(a, b);
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_div_lowp(cobalt_f32vec4 a, cobalt_f32vec4 b)
{
	return cobalt_vec4_mul(a, _mm_rcp_ps(b));
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_swizzle_xyzw(cobalt_f32vec4 a)
{
#	if COBALT_ARCH & COBALT_ARCH_AVX2_BIT
		return _mm_permute_ps(a, _MM_SHUFFLE(3, 2, 1, 0));
#	else
		return _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 2, 1, 0));
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec1_fma(cobalt_f32vec4 a, cobalt_f32vec4 b, cobalt_f32vec4 c)
{
#	if (COBALT_ARCH & COBALT_ARCH_AVX2_BIT) && !(COBALT_COMPILER & COBALT_COMPILER_CLANG)
		return _mm_fmadd_ss(a, b, c);
#	else
		return _mm_add_ss(_mm_mul_ss(a, b), c);
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_fma(cobalt_f32vec4 a, cobalt_f32vec4 b, cobalt_f32vec4 c)
{
#	if (COBALT_ARCH & COBALT_ARCH_AVX2_BIT) && !(COBALT_COMPILER & COBALT_COMPILER_CLANG)
		return _mm_fmadd_ps(a, b, c);
#	else
		return cobalt_vec4_add(cobalt_vec4_mul(a, b), c);
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_f32vec4 cobalt_vec4_abs(cobalt_f32vec4 x)
{
	return _mm_and_ps(x, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
}

COBALT_FUNC_QUALIFIER cobalt_ivec4 cobalt_ivec4_abs(cobalt_ivec4 x)
{
#	if COBALT_ARCH & COBALT_ARCH_SSSE3_BIT
		return _mm_sign_epi32(x, x);
#	else
		cobalt_ivec4 const sgn0 = _mm_srai_epi32(x, 31);
		cobalt_ivec4 const inv0 = _mm_xor_si128(x, sgn0);
		cobalt_ivec4 const sub0 = _mm_sub_epi32(inv0, sgn0);
		return sub0;
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_sign(cobalt_vec4 x)
{
	cobalt_vec4 const zro0 = _mm_setzero_ps();
	cobalt_vec4 const cmp0 = _mm_cmplt_ps(x, zro0);
	cobalt_vec4 const cmp1 = _mm_cmpgt_ps(x, zro0);
	cobalt_vec4 const and0 = _mm_and_ps(cmp0, _mm_set1_ps(-1.0f));
	cobalt_vec4 const and1 = _mm_and_ps(cmp1, _mm_set1_ps(1.0f));
	cobalt_vec4 const or0 = _mm_or_ps(and0, and1);
	return or0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_round(cobalt_vec4 x)
{
#	if COBALT_ARCH & COBALT_ARCH_SSE41_BIT
		return _mm_round_ps(x, _MM_FROUND_TO_NEAREST_INT);
#	else
		cobalt_vec4 const sgn0 = _mm_castsi128_ps(_mm_set1_epi32(int(0x80000000)));
		cobalt_vec4 const and0 = _mm_and_ps(sgn0, x);
		cobalt_vec4 const or0 = _mm_or_ps(and0, _mm_set_ps1(8388608.0f));
		cobalt_vec4 const add0 = cobalt_vec4_add(x, or0);
		cobalt_vec4 const sub0 = cobalt_vec4_sub(add0, or0);
		return sub0;
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_floor(cobalt_vec4 x)
{
#	if COBALT_ARCH & COBALT_ARCH_SSE41_BIT
		return _mm_floor_ps(x);
#	else
		cobalt_vec4 const rnd0 = cobalt_vec4_round(x);
		cobalt_vec4 const cmp0 = _mm_cmplt_ps(x, rnd0);
		cobalt_vec4 const and0 = _mm_and_ps(cmp0, _mm_set1_ps(1.0f));
		cobalt_vec4 const sub0 = cobalt_vec4_sub(rnd0, and0);
		return sub0;
#	endif
}

/* trunc TODO
COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_trunc(cobalt_vec4 x)
{
	return cobalt_vec4();
}
*/

//roundEven
COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_roundEven(cobalt_vec4 x)
{
	cobalt_vec4 const sgn0 = _mm_castsi128_ps(_mm_set1_epi32(int(0x80000000)));
	cobalt_vec4 const and0 = _mm_and_ps(sgn0, x);
	cobalt_vec4 const or0 = _mm_or_ps(and0, _mm_set_ps1(8388608.0f));
	cobalt_vec4 const add0 = cobalt_vec4_add(x, or0);
	cobalt_vec4 const sub0 = cobalt_vec4_sub(add0, or0);
	return sub0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_ceil(cobalt_vec4 x)
{
#	if COBALT_ARCH & COBALT_ARCH_SSE41_BIT
		return _mm_ceil_ps(x);
#	else
		cobalt_vec4 const rnd0 = cobalt_vec4_round(x);
		cobalt_vec4 const cmp0 = _mm_cmpgt_ps(x, rnd0);
		cobalt_vec4 const and0 = _mm_and_ps(cmp0, _mm_set1_ps(1.0f));
		cobalt_vec4 const add0 = cobalt_vec4_add(rnd0, and0);
		return add0;
#	endif
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_fract(cobalt_vec4 x)
{
	cobalt_vec4 const flr0 = cobalt_vec4_floor(x);
	cobalt_vec4 const sub0 = cobalt_vec4_sub(x, flr0);
	return sub0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_mod(cobalt_vec4 x, cobalt_vec4 y)
{
	cobalt_vec4 const div0 = cobalt_vec4_div(x, y);
	cobalt_vec4 const flr0 = cobalt_vec4_floor(div0);
	cobalt_vec4 const mul0 = cobalt_vec4_mul(y, flr0);
	cobalt_vec4 const sub0 = cobalt_vec4_sub(x, mul0);
	return sub0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_clamp(cobalt_vec4 v, cobalt_vec4 minVal, cobalt_vec4 maxVal)
{
	cobalt_vec4 const min0 = _mm_min_ps(v, maxVal);
	cobalt_vec4 const max0 = _mm_max_ps(min0, minVal);
	return max0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_mix(cobalt_vec4 v1, cobalt_vec4 v2, cobalt_vec4 a)
{
	cobalt_vec4 const sub0 = cobalt_vec4_sub(_mm_set1_ps(1.0f), a);
	cobalt_vec4 const mul0 = cobalt_vec4_mul(v1, sub0);
	cobalt_vec4 const mad0 = cobalt_vec4_fma(v2, a, mul0);
	return mad0;
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_step(cobalt_vec4 edge, cobalt_vec4 x)
{
	cobalt_vec4 const cmp = _mm_cmple_ps(x, edge);
	return _mm_movemask_ps(cmp) == 0 ? _mm_set1_ps(1.0f) : _mm_setzero_ps();
}

COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_smoothstep(cobalt_vec4 edge0, cobalt_vec4 edge1, cobalt_vec4 x)
{
	cobalt_vec4 const sub0 = cobalt_vec4_sub(x, edge0);
	cobalt_vec4 const sub1 = cobalt_vec4_sub(edge1, edge0);
	cobalt_vec4 const div0 = cobalt_vec4_sub(sub0, sub1);
	cobalt_vec4 const clp0 = cobalt_vec4_clamp(div0, _mm_setzero_ps(), _mm_set1_ps(1.0f));
	cobalt_vec4 const mul0 = cobalt_vec4_mul(_mm_set1_ps(2.0f), clp0);
	cobalt_vec4 const sub2 = cobalt_vec4_sub(_mm_set1_ps(3.0f), mul0);
	cobalt_vec4 const mul1 = cobalt_vec4_mul(clp0, clp0);
	cobalt_vec4 const mul2 = cobalt_vec4_mul(mul1, sub2);
	return mul2;
}

// Agner Fog method
COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_nan(cobalt_vec4 x)
{
	cobalt_ivec4 const t1 = _mm_castps_si128(x);						// reinterpret as 32-bit integer
	cobalt_ivec4 const t2 = _mm_sll_epi32(t1, _mm_cvtsi32_si128(1));	// shift out sign bit
	cobalt_ivec4 const t3 = _mm_set1_epi32(int(0xFF000000));				// exponent mask
	cobalt_ivec4 const t4 = _mm_and_si128(t2, t3);						// exponent
	cobalt_ivec4 const t5 = _mm_andnot_si128(t3, t2);					// fraction
	cobalt_ivec4 const Equal = _mm_cmpeq_epi32(t3, t4);
	cobalt_ivec4 const Nequal = _mm_cmpeq_epi32(t5, _mm_setzero_si128());
	cobalt_ivec4 const And = _mm_and_si128(Equal, Nequal);
	return _mm_castsi128_ps(And);									// exponent = all 1s and fraction != 0
}

// Agner Fog method
COBALT_FUNC_QUALIFIER cobalt_vec4 cobalt_vec4_inf(cobalt_vec4 x)
{
	cobalt_ivec4 const t1 = _mm_castps_si128(x);										// reinterpret as 32-bit integer
	cobalt_ivec4 const t2 = _mm_sll_epi32(t1, _mm_cvtsi32_si128(1));					// shift out sign bit
	return _mm_castsi128_ps(_mm_cmpeq_epi32(t2, _mm_set1_epi32(int(0xFF000000))));		// exponent is all 1s, fraction is 0
}

#endif//COBALT_ARCH & COBALT_ARCH_SSE2_BIT
