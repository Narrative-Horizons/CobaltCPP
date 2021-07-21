/// @ref gtx_fast_trigonometry
/// @file glm/gtx/fast_trigonometry.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_fast_trigonometry COBALT_GTX_fast_trigonometry
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/fast_trigonometry.hpp> to use the features of this extension.
///
/// Fast but less accurate implementations of trigonometric functions.

#pragma once

// Dependency:
#include "../gtc/constants.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_fast_trigonometry is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_fast_trigonometry extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_fast_trigonometry
	/// @{

	/// Wrap an angle to [0 2pi[
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T wrapAngle(T angle);

	/// Faster than the common sin function but less accurate.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastSin(T angle);

	/// Faster than the common cos function but less accurate.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastCos(T angle);

	/// Faster than the common tan function but less accurate.
	/// Defined between -2pi and 2pi.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastTan(T angle);

	/// Faster than the common asin function but less accurate.
	/// Defined between -2pi and 2pi.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastAsin(T angle);

	/// Faster than the common acos function but less accurate.
	/// Defined between -2pi and 2pi.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastAcos(T angle);

	/// Faster than the common atan function but less accurate.
	/// Defined between -2pi and 2pi.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastAtan(T y, T x);

	/// Faster than the common atan function but less accurate.
	/// Defined between -2pi and 2pi.
	/// From COBALT_GTX_fast_trigonometry extension.
	template<typename T>
	COBALT_FUNC_DECL T fastAtan(T angle);

	/// @}
}//namespace cobalt::math

#include "fast_trigonometry.inl"
