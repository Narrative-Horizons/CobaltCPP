/// @ref ext_matrix_uint4x3
/// @file glm/ext/matrix_uint4x3.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint4x3 COBALT_EXT_matrix_uint4x3
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint4x3.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat4x3.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint4x3 extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint4x3
	/// @{

	/// Unsigned integer 4x3 matrix.
	///
	/// @see ext_matrix_uint4x3
	typedef mat<4, 3, uint, defaultp>	umat4x3;

	/// @}
}//namespace cobalt::math
