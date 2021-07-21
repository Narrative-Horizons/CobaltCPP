/// @ref gtx_component_wise
/// @file glm/gtx/component_wise.hpp
/// @date 2007-05-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_component_wise COBALT_GTX_component_wise
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/component_wise.hpp> to use the features of this extension.
///
/// Operations between components of a type

#pragma once

// Dependencies
#include "../detail/setup.hpp"
#include "../detail/qualifier.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_component_wise is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_component_wise extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_component_wise
	/// @{

	/// Convert an integer vector to a normalized float vector.
	/// If the parameter value type is already a floating qualifier type, the value is passed through.
	/// @see gtx_component_wise
	template<typename floatType, length_t L, typename T, qualifier Q>
	COBALT_FUNC_DECL vec<L, floatType, Q> compNormalize(vec<L, T, Q> const& v);

	/// Convert a normalized float vector to an integer vector.
	/// If the parameter value type is already a floating qualifier type, the value is passed through.
	/// @see gtx_component_wise
	template<length_t L, typename T, typename floatType, qualifier Q>
	COBALT_FUNC_DECL vec<L, T, Q> compScale(vec<L, floatType, Q> const& v);

	/// Add all vector components together.
	/// @see gtx_component_wise
	template<typename genType>
	COBALT_FUNC_DECL typename genType::value_type compAdd(genType const& v);

	/// Multiply all vector components together.
	/// @see gtx_component_wise
	template<typename genType>
	COBALT_FUNC_DECL typename genType::value_type compMul(genType const& v);

	/// Find the minimum value between single vector components.
	/// @see gtx_component_wise
	template<typename genType>
	COBALT_FUNC_DECL typename genType::value_type compMin(genType const& v);

	/// Find the maximum value between single vector components.
	/// @see gtx_component_wise
	template<typename genType>
	COBALT_FUNC_DECL typename genType::value_type compMax(genType const& v);

	/// @}
}//namespace cobalt::math

#include "component_wise.inl"
