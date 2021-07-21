/// @ref gtx_normalize_dot
/// @file glm/gtx/normalize_dot.hpp
///
/// @see core (dependence)
/// @see gtx_fast_square_root (dependence)
///
/// @defgroup gtx_normalize_dot COBALT_GTX_normalize_dot
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/normalized_dot.hpp> to use the features of this extension.
///
/// Dot product of vectors that need to be normalize with a single square root.

#pragma once

// Dependency:
#include "../gtx/fast_square_root.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_normalize_dot is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_normalize_dot extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_normalize_dot
	/// @{

	/// Normalize parameters and returns the dot product of x and y.
	/// It's faster that dot(normalize(x), normalize(y)).
	///
	/// @see gtx_normalize_dot extension.
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL T normalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Normalize parameters and returns the dot product of x and y.
	/// Faster that dot(fastNormalize(x), fastNormalize(y)).
	///
	/// @see gtx_normalize_dot extension.
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL T fastNormalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// @}
}//namespace cobalt::math

#include "normalize_dot.inl"
