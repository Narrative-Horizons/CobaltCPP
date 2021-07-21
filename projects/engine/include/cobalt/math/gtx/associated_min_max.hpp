/// @ref gtx_associated_min_max
/// @file glm/gtx/associated_min_max.hpp
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_associated_min_max COBALT_GTX_associated_min_max
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/associated_min_max.hpp> to use the features of this extension.
///
/// @brief Min and max functions that return associated values not the compared onces.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_associated_min_max is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_associated_min_max extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_associated_min_max
	/// @{

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL U associatedMin(T x, U a, T y, U b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<2, U, Q> associatedMin(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		T x, const vec<L, U, Q>& a,
		T y, const vec<L, U, Q>& b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, T, Q> const& x, U a,
		vec<L, T, Q> const& y, U b);

	/// Minimum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U>
	COBALT_FUNC_DECL U associatedMin(
		T x, U a,
		T y, U b,
		T z, U c);

	/// Minimum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b,
		vec<L, T, Q> const& z, vec<L, U, Q> const& c);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U>
	COBALT_FUNC_DECL U associatedMin(
		T x, U a,
		T y, U b,
		T z, U c,
		T w, U d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b,
		vec<L, T, Q> const& z, vec<L, U, Q> const& c,
		vec<L, T, Q> const& w, vec<L, U, Q> const& d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		T x, vec<L, U, Q> const& a,
		T y, vec<L, U, Q> const& b,
		T z, vec<L, U, Q> const& c,
		T w, vec<L, U, Q> const& d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, T, Q> const& x, U a,
		vec<L, T, Q> const& y, U b,
		vec<L, T, Q> const& z, U c,
		vec<L, T, Q> const& w, U d);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U>
	COBALT_FUNC_DECL U associatedMax(T x, U a, T y, U b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<2, U, Q> associatedMax(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> associatedMax(
		T x, vec<L, U, Q> const& a,
		T y, vec<L, U, Q> const& b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, T, Q> const& x, U a,
		vec<L, T, Q> const& y, U b);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U>
	COBALT_FUNC_DECL U associatedMax(
		T x, U a,
		T y, U b,
		T z, U c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b,
		vec<L, T, Q> const& z, vec<L, U, Q> const& c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> associatedMax(
		T x, vec<L, U, Q> const& a,
		T y, vec<L, U, Q> const& b,
		T z, vec<L, U, Q> const& c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, T, Q> const& x, U a,
		vec<L, T, Q> const& y, U b,
		vec<L, T, Q> const& z, U c);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<typename T, typename U>
	COBALT_FUNC_DECL U associatedMax(
		T x, U a,
		T y, U b,
		T z, U c,
		T w, U d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, T, Q> const& x, vec<L, U, Q> const& a,
		vec<L, T, Q> const& y, vec<L, U, Q> const& b,
		vec<L, T, Q> const& z, vec<L, U, Q> const& c,
		vec<L, T, Q> const& w, vec<L, U, Q> const& d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		T x, vec<L, U, Q> const& a,
		T y, vec<L, U, Q> const& b,
		T z, vec<L, U, Q> const& c,
		T w, vec<L, U, Q> const& d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename T, typename U, qualifier Q>
	COBALT_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, T, Q> const& x, U a,
		vec<L, T, Q> const& y, U b,
		vec<L, T, Q> const& z, U c,
		vec<L, T, Q> const& w, U d);

	/// @}
} //namespace cobalt::math

#include "associated_min_max.inl"
