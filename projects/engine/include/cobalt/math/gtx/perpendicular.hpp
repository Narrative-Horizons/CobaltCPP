/// @ref gtx_perpendicular
/// @file glm/gtx/perpendicular.hpp
///
/// @see core (dependence)
/// @see gtx_projection (dependence)
///
/// @defgroup gtx_perpendicular COBALT_GTX_perpendicular
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/perpendicular.hpp> to use the features of this extension.
///
/// Perpendicular of a vector from other one

#pragma once

// Dependency:
#include "../math.hpp"
#include "../gtx/projection.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_perpendicular is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_perpendicular extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_perpendicular
	/// @{

	//! Projects x a perpendicular axis of Normal.
	//! From COBALT_GTX_perpendicular extension.
	template<typename genType>
	COBALT_FUNC_DECL genType perp(genType const& x, genType const& Normal);

	/// @}
}//namespace cobalt::math

#include "perpendicular.inl"
