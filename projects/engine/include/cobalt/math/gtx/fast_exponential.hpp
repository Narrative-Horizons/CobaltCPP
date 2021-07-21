/// @ref gtx_fast_exponential
/// @file glm/gtx/fast_exponential.hpp
///
/// @see core (dependence)
/// @see gtx_half_float (dependence)
///
/// @defgroup gtx_fast_exponential COBALT_GTX_fast_exponential
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/fast_exponential.hpp> to use the features of this extension.
///
/// Fast but less accurate implementations of exponential based functions.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_fast_exponential is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_fast_exponential extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_fast_exponential
	/// @{

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template<typename genType>
	COBALT_FUNC_DECL genType fastPow(genType x, genType y);

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastPow(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template<typename genTypeT, typename genTypeU>
	COBALT_FUNC_DECL genTypeT fastPow(genTypeT x, genTypeU y);

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastPow(vec<L, T, Q> const& x);

	/// Faster than the common exp function but less accurate.
	/// @see gtx_fast_exponential
	template<typename T>
	COBALT_FUNC_DECL T fastExp(T x);

	/// Faster than the common exp function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastExp(vec<L, T, Q> const& x);

	/// Faster than the common log function but less accurate.
	/// @see gtx_fast_exponential
	template<typename T>
	COBALT_FUNC_DECL T fastLog(T x);

	/// Faster than the common exp2 function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastLog(vec<L, T, Q> const& x);

	/// Faster than the common exp2 function but less accurate.
	/// @see gtx_fast_exponential
	template<typename T>
	COBALT_FUNC_DECL T fastExp2(T x);

	/// Faster than the common exp2 function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastExp2(vec<L, T, Q> const& x);

	/// Faster than the common log2 function but less accurate.
	/// @see gtx_fast_exponential
	template<typename T>
	COBALT_FUNC_DECL T fastLog2(T x);

	/// Faster than the common log2 function but less accurate.
	/// @see gtx_fast_exponential
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> fastLog2(vec<L, T, Q> const& x);

	/// @}
}//namespace cobalt::math

#include "fast_exponential.inl"
