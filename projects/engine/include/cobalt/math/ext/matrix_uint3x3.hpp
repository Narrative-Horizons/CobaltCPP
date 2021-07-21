/// @ref ext_matrix_uint3x3
/// @file glm/ext/matrix_uint3x3.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint3x3 COBALT_EXT_matrix_uint3x3
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint3x3.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat3x3.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint3x3 extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint3x3
	/// @{

	/// Unsigned integer 3x3 matrix.
	///
	/// @see ext_matrix_uint3x3
	typedef mat<3, 3, uint, defaultp>	umat3x3;

	/// Unsigned integer 3x3 matrix.
	///
	/// @see ext_matrix_uint3x3
	typedef mat<3, 3, uint, defaultp>	umat3;

	/// @}
}//namespace cobalt::math
