/// @ref gtx_orthonormalize
/// @file glm/gtx/orthonormalize.hpp
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_orthonormalize COBALT_GTX_orthonormalize
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/orthonormalize.hpp> to use the features of this extension.
///
/// Orthonormalize matrices.

#pragma once

// Dependency:
#include "../vec3.hpp"
#include "../mat3x3.hpp"
#include "../geometric.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_orthonormalize is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_orthonormalize extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_orthonormalize
	/// @{

	/// Returns the orthonormalized matrix of m.
	///
	/// @see gtx_orthonormalize
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 3, T, Q> orthonormalize(mat<3, 3, T, Q> const& m);

	/// Orthonormalizes x according y.
	///
	/// @see gtx_orthonormalize
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL vec<3, T, Q> orthonormalize(vec<3, T, Q> const& x, vec<3, T, Q> const& y);

	/// @}
}//namespace cobalt::math

#include "orthonormalize.inl"
