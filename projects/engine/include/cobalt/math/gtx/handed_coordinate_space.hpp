/// @ref gtx_handed_coordinate_space
/// @file glm/gtx/handed_coordinate_space.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_handed_coordinate_space COBALT_GTX_handed_coordinate_space
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/handed_coordinate_system.hpp> to use the features of this extension.
///
/// To know if a set of three basis vectors defines a right or left-handed coordinate system.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_handed_coordinate_space is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_handed_coordinate_space extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_handed_coordinate_space
	/// @{

	//! Return if a trihedron right handed or not.
	//! From COBALT_GTX_handed_coordinate_space extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL bool rightHanded(
		vec<3, T, Q> const& tangent,
		vec<3, T, Q> const& binormal,
		vec<3, T, Q> const& normal);

	//! Return if a trihedron left handed or not.
	//! From COBALT_GTX_handed_coordinate_space extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL bool leftHanded(
		vec<3, T, Q> const& tangent,
		vec<3, T, Q> const& binormal,
		vec<3, T, Q> const& normal);

	/// @}
}// namespace cobalt::math

#include "handed_coordinate_space.inl"
