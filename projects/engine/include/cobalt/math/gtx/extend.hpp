/// @ref gtx_extend
/// @file glm/gtx/extend.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_extend COBALT_GTX_extend
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/extend.hpp> to use the features of this extension.
///
/// Extend a position from a source to a position at a defined length.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_extend is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_extend extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_extend
	/// @{

	/// Extends of Length the Origin position using the (Source - Origin) direction.
	/// @see gtx_extend
	template<typename genType>
	COBALT_FUNC_DECL genType extend(
		genType const& Origin,
		genType const& Source,
		typename genType::value_type const Length);

	/// @}
}//namespace cobalt::math

#include "extend.inl"
