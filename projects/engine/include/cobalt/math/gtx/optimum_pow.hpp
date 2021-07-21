/// @ref gtx_optimum_pow
/// @file glm/gtx/optimum_pow.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_optimum_pow COBALT_GTX_optimum_pow
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/optimum_pow.hpp> to use the features of this extension.
///
/// Integer exponentiation of power functions.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_optimum_pow is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_optimum_pow extension included")
#	endif
#endif

namespace cobalt::math{
namespace gtx
{
	/// @addtogroup gtx_optimum_pow
	/// @{

	/// Returns x raised to the power of 2.
	///
	/// @see gtx_optimum_pow
	template<typename genType>
	COBALT_FUNC_DECL genType pow2(genType const& x);

	/// Returns x raised to the power of 3.
	///
	/// @see gtx_optimum_pow
	template<typename genType>
	COBALT_FUNC_DECL genType pow3(genType const& x);

	/// Returns x raised to the power of 4.
	///
	/// @see gtx_optimum_pow
	template<typename genType>
	COBALT_FUNC_DECL genType pow4(genType const& x);

	/// @}
}//namespace gtx
}//namespace cobalt::math

#include "optimum_pow.inl"
