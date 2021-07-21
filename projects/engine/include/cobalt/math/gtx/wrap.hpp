/// @ref gtx_wrap
/// @file glm/gtx/wrap.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_wrap COBALT_GTX_wrap
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/wrap.hpp> to use the features of this extension.
///
/// Wrapping mode of texture coordinates.

#pragma once

// Dependency:
#include "../math.hpp"
#include "../ext/scalar_common.hpp"
#include "../ext/vector_common.hpp"
#include "../gtc/vec1.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_wrap is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_wrap extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_wrap
	/// @{

	/// @}
}// namespace cobalt::math

#include "wrap.inl"
