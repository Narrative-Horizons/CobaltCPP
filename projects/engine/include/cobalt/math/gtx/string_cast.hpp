/// @ref gtx_string_cast
/// @file glm/gtx/string_cast.hpp
///
/// @see core (dependence)
/// @see gtx_integer (dependence)
/// @see gtx_quaternion (dependence)
///
/// @defgroup gtx_string_cast COBALT_GTX_string_cast
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/string_cast.hpp> to use the features of this extension.
///
/// Setup strings for COBALT type values
///
/// This extension is not supported with CUDA

#pragma once

// Dependency:
#include "../math.hpp"
#include "../gtc/type_precision.hpp"
#include "../gtc/quaternion.hpp"
#include "../gtx/dual_quaternion.hpp"
#include <string>
#include <cmath>

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_string_cast is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_string_cast extension included")
#	endif
#endif

#if(COBALT_COMPILER & COBALT_COMPILER_CUDA)
#	error "COBALT_GTX_string_cast is not supported on CUDA compiler"
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_string_cast
	/// @{

	/// Create a string from a COBALT vector or matrix typed variable.
	/// @see gtx_string_cast extension.
	template<typename genType>
	COBALT_FUNC_DECL std::string to_string(genType const& x);

	/// @}
}//namespace cobalt::math

#include "string_cast.inl"
