/// @ref ext_vector_bool1_precision
/// @file glm/ext/vector_bool1_precision.hpp
///
/// @defgroup ext_vector_bool1_precision COBALT_EXT_vector_bool1_precision
/// @ingroup ext
///
/// Exposes highp_bvec1, mediump_bvec1 and lowp_bvec1 types.
///
/// Include <cobalt/math/ext/vector_bool1_precision.hpp> to use the features of this extension.

#pragma once

#include "../detail/type_vec1.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_vector_bool1_precision extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_vector_bool1_precision
	/// @{

	/// 1 component vector of bool values.
	typedef vec<1, bool, highp>			highp_bvec1;

	/// 1 component vector of bool values.
	typedef vec<1, bool, mediump>		mediump_bvec1;

	/// 1 component vector of bool values.
	typedef vec<1, bool, lowp>			lowp_bvec1;

	/// @}
}//namespace cobalt::math
