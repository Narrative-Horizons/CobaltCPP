/// @ref ext_matrix_uint2x3
/// @file glm/ext/matrix_uint2x3.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_int2x3 COBALT_EXT_matrix_uint2x3
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint2x3.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat2x3.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint2x3 extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint2x3
	/// @{

	/// Unsigned integer 2x3 matrix.
	///
	/// @see ext_matrix_uint2x3
	typedef mat<2, 3, uint, defaultp>	umat2x3;

	/// @}
}//namespace cobalt::math
