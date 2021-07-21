/// @ref ext_matrix_uint3x2_sized
/// @file glm/ext/matrix_uint3x2_sized.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint3x2_sized COBALT_EXT_matrix_uint3x2_sized
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint3x2_sized.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat3x2.hpp"
#include "../ext/scalar_uint_sized.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint3x2_sized extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint3x2_sized
	/// @{

	/// 8 bit signed integer 3x2 matrix.
	///
	/// @see ext_matrix_uint3x2_sized
	typedef mat<3, 2, uint8, defaultp>				u8mat3x2;

	/// 16 bit signed integer 3x2 matrix.
	///
	/// @see ext_matrix_uint3x2_sized
	typedef mat<3, 2, uint16, defaultp>				u16mat3x2;

	/// 32 bit signed integer 3x2 matrix.
	///
	/// @see ext_matrix_uint3x2_sized
	typedef mat<3, 2, uint32, defaultp>				u32mat3x2;

	/// 64 bit signed integer 3x2 matrix.
	///
	/// @see ext_matrix_uint3x2_sized
	typedef mat<3, 2, uint64, defaultp>				u64mat3x2;

	/// @}
}//namespace cobalt::math
