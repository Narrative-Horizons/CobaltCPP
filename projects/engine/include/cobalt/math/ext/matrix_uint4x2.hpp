/// @ref ext_matrix_uint4x2
/// @file glm/ext/matrix_uint4x2.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint4x2 COBALT_EXT_matrix_uint4x2
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint4x2.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat4x2.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint4x2 extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint4x2
	/// @{

	/// Unsigned integer 4x2 matrix.
	///
	/// @see ext_matrix_uint4x2
	typedef mat<4, 2, uint, defaultp>	umat4x2;

	/// @}
}//namespace cobalt::math