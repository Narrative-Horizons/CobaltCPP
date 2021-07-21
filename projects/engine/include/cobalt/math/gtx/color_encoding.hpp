/// @ref gtx_color_encoding
/// @file glm/gtx/color_encoding.hpp
///
/// @see core (dependence)
/// @see gtx_color_encoding (dependence)
///
/// @defgroup gtx_color_encoding COBALT_GTX_color_encoding
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/color_encoding.hpp> to use the features of this extension.
///
/// @brief Allow to perform bit operations on integer values

#pragma once

// Dependencies
#include "../detail/setup.hpp"
#include "../detail/qualifier.hpp"
#include "../vec3.hpp"
#include <limits>

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTC_color_encoding is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTC_color_encoding extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_color_encoding
	/// @{

	/// Convert a linear sRGB color to D65 YUV.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL vec<3, T, Q> convertLinearSRGBToD65XYZ(vec<3, T, Q> const& ColorLinearSRGB);

	/// Convert a linear sRGB color to D50 YUV.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL vec<3, T, Q> convertLinearSRGBToD50XYZ(vec<3, T, Q> const& ColorLinearSRGB);

	/// Convert a D65 YUV color to linear sRGB.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL vec<3, T, Q> convertD65XYZToLinearSRGB(vec<3, T, Q> const& ColorD65XYZ);

	/// Convert a D65 YUV color to D50 YUV.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL vec<3, T, Q> convertD65XYZToD50XYZ(vec<3, T, Q> const& ColorD65XYZ);

	/// @}
} //namespace cobalt::math

#include "color_encoding.inl"
