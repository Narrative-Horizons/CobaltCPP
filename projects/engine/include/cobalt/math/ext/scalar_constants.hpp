/// @ref ext_scalar_constants
/// @file glm/ext/scalar_constants.hpp
///
/// @defgroup ext_scalar_constants COBALT_EXT_scalar_constants
/// @ingroup ext
///
/// Provides a list of constants and precomputed useful values.
///
/// Include <cobalt/math/ext/scalar_constants.hpp> to use the features of this extension.

#pragma once

// Dependencies
#include "../detail/setup.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_EXT_scalar_constants extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup ext_scalar_constants
	/// @{

	/// Return the epsilon constant for floating point types.
	template<typename genType>
	COBALT_FUNC_DECL COBALT_CONSTEXPR genType epsilon();

	/// Return the pi constant for floating point types.
	template<typename genType>
	COBALT_FUNC_DECL COBALT_CONSTEXPR genType pi();

	/// Return the value of cos(1 / 2) for floating point types.
	template<typename genType>
	COBALT_FUNC_DECL COBALT_CONSTEXPR genType cos_one_over_two();

	/// @}
} //namespace cobalt::math

#include "scalar_constants.inl"
