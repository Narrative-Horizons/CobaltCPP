/// @ref ext_matrix_uint2x3_sized
/// @file glm/ext/matrix_uint2x3_sized.hpp
///
/// @see core (dependence)
///
/// @defgroup ext_matrix_uint2x3_sized COBALT_EXT_matrix_uint2x3_sized
/// @ingroup ext
///
/// Include <cobalt/math/ext/matrix_uint2x3_sized.hpp> to use the features of this extension.
///
/// Defines a number of matrices with integer types.

#pragma once

// Dependency:
#include "../mat2x3.hpp"
#include "../ext/scalar_uint_sized.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_matrix_uint2x3_sized extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_matrix_uint2x3_sized
	/// @{

	/// 8 bit unsigned integer 2x3 matrix.
	///
	/// @see ext_matrix_uint2x3_sized
	typedef mat<2, 3, uint8, defaultp>				u8mat2x3;

	/// 16 bit unsigned integer 2x3 matrix.
	///
	/// @see ext_matrix_uint2x3_sized
	typedef mat<2, 3, uint16, defaultp>				u16mat2x3;

	/// 32 bit unsigned integer 2x3 matrix.
	///
	/// @see ext_matrix_uint2x3_sized
	typedef mat<2, 3, uint32, defaultp>				u32mat2x3;

	/// 64 bit unsigned integer 2x3 matrix.
	///
	/// @see ext_matrix_uint2x3_sized
	typedef mat<2, 3, uint64, defaultp>				u64mat2x3;

	/// @}
}//namespace cobalt::math
