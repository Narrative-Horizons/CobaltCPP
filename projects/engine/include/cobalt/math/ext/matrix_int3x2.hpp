/// @ref ext_matrix_int3x2
/// @file glm/ext/matrix_int3x2.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_int3x2 COBALT_EXT_matrix_int3x2
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_int3x2.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat3x2.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_int3x2 extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_int3x2
	/// @{

	/// Signed integer 3x2 matrix.
	///
	/// @see ext_matrix_int3x2
	typedef mat<3, 2, int, defaultp>	imat3x2;

	/// @}
}//namespace cobalt::math
