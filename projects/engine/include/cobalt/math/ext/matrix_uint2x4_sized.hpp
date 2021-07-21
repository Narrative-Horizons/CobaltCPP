/// @ref ext_matrix_uint2x4_sized
/// @file glm/ext/matrixu_uint2x4_sized.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint2x4_sized COBALT_EXT_matrix_uint2x4_sized
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint2x4_sized.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat2x4.hpp"
#include "../ext/scalar_uint_sized.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint2x4_sized extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint2x4_sized
	/// @{

	/// 8 bit unsigned integer 2x4 matrix.
	///
	/// @see ext_matrix_uint2x4_sized
	typedef mat<2, 4, uint8, defaultp>				u8mat2x4;

	/// 16 bit unsigned integer 2x4 matrix.
	///
	/// @see ext_matrix_uint2x4_sized
	typedef mat<2, 4, uint16, defaultp>				u16mat2x4;

	/// 32 bit unsigned integer 2x4 matrix.
	///
	/// @see ext_matrix_uint2x4_sized
	typedef mat<2, 4, uint32, defaultp>				u32mat2x4;

	/// 64 bit unsigned integer 2x4 matrix.
	///
	/// @see ext_matrix_uint2x4_sized
	typedef mat<2, 4, uint64, defaultp>				u64mat2x4;

	/// @}
}//namespace cobalt::math
