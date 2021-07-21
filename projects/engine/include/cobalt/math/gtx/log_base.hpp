/// @ref gtx_log_base
/// @file glm/gtx/log_base.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_log_base COBALT_GTX_log_base
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/log_base.hpp> to use the features of this extension.
///
/// Logarithm for any base. base can be a vector or a scalar.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_log_base is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_log_base extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_log_base
	/// @{

	/// Logarithm for any base.
	/// From COBALT_GTX_log_base.
	template<typename genType>
	COBALT_FUNC_DECL genType log(
		genType const& x,
		genType const& base);

	/// Logarithm for any base.
	/// From COBALT_GTX_log_base.
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> sign(
		vec<L, T, Q> const& x,
		vec<L, T, Q> const& base);

	/// @}
}//namespace cobalt::math

#include "log_base.inl"
