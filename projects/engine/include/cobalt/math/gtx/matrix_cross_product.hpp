/// @ref gtx_matrix_cross_product
/// @file glm/gtx/matrix_cross_product.hpp
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_matrix_cross_product COBALT_GTX_matrix_cross_product
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/matrix_cross_product.hpp> to use the features of this extension.
///
/// Build cross product matrices

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_matrix_cross_product is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_matrix_cross_product extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_matrix_cross_product
	/// @{

	//! Build a cross product matrix.
	//! From COBALT_GTX_matrix_cross_product extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 3, T, Q> matrixCross3(
		vec<3, T, Q> const& x);

	//! Build a cross product matrix.
	//! From COBALT_GTX_matrix_cross_product extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> matrixCross4(
		vec<3, T, Q> const& x);

	/// @}
}//namespace cobalt::math

#include "matrix_cross_product.inl"
