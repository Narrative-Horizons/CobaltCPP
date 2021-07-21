/// @ref gtx_spline
/// @file glm/gtx/spline.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_spline COBALT_GTX_spline
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/spline.hpp> to use the features of this extension.
///
/// Spline functions

#pragma once

// Dependency:
#include "../math.hpp"
#include "../gtx/optimum_pow.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_spline is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_spline extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_spline
	/// @{

	/// Return a point from a catmull rom curve.
	/// @see gtx_spline extension.
	template<typename genType>
	COBALT_FUNC_DECL genType catmullRom(
		genType const& v1,
		genType const& v2,
		genType const& v3,
		genType const& v4,
		typename genType::value_type const& s);

	/// Return a point from a hermite curve.
	/// @see gtx_spline extension.
	template<typename genType>
	COBALT_FUNC_DECL genType hermite(
		genType const& v1,
		genType const& t1,
		genType const& v2,
		genType const& t2,
		typename genType::value_type const& s);

	/// Return a point from a cubic curve.
	/// @see gtx_spline extension.
	template<typename genType>
	COBALT_FUNC_DECL genType cubic(
		genType const& v1,
		genType const& v2,
		genType const& v3,
		genType const& v4,
		typename genType::value_type const& s);

	/// @}
}//namespace cobalt::math

#include "spline.inl"
