/// @ref gtx_transform
/// @file glm/gtx/transform.hpp
///
/// @see core (dependence)
/// @see gtc_matrix_transform (dependence)
/// @see gtx_transform
/// @see gtx_transform2
///
/// @defgroup gtx_transform COBALT_GTX_transform
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/transform.hpp> to use the features of this extension.
///
/// Add transformation matrices

#pragma once

// Dependency:
#include "../math.hpp"
#include "../gtc/matrix_transform.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_transform is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_transform extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_transform
	/// @{

	/// Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> translate(
		vec<3, T, Q> const& v);

	/// Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in radians.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> rotate(
		T angle,
		vec<3, T, Q> const& v);

	/// Transforms a matrix with a scale 4 * 4 matrix created from a vector of 3 components.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> scale(
		vec<3, T, Q> const& v);

	/// @}
}// namespace cobalt::math

#include "transform.inl"
