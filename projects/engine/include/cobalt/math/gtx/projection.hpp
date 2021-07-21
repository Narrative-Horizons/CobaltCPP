/// @ref gtx_projection
/// @file glm/gtx/projection.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_projection COBALT_GTX_projection
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/projection.hpp> to use the features of this extension.
///
/// Projection of a vector to other one

#pragma once

// Dependency:
#include "../geometric.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_projection is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_projection extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_projection
	/// @{

	/// Projects x on Normal.
	///
	/// @param[in] x A vector to project
	/// @param[in] Normal A normal that doesn't need to be of unit length.
	///
	/// @see gtx_projection
	template<typename genType>
	COBALT_FUNC_DECL genType proj(genType const& x, genType const& Normal);

	/// @}
}//namespace cobalt::math

#include "projection.inl"
