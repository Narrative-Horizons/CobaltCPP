/// @ref gtx_integer
/// @file glm/gtx/integer.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_integer COBALT_GTX_integer
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/integer.hpp> to use the features of this extension.
///
/// Add support for integer for core functions

#pragma once

// Dependency:
#include "../math.hpp"
#include "../gtc/integer.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_integer is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_integer extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_integer
	/// @{

	//! Returns x raised to the y power.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL int pow(int x, uint y);

	//! Returns the positive square root of x.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL int sqrt(int x);

	//! Returns the floor log2 of x.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL unsigned int floor_log2(unsigned int x);

	//! Modulus. Returns x - y * floor(x / y) for each component in x using the floating point value y.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL int mod(int x, int y);

	//! Return the factorial value of a number (!12 max, integer only)
	//! From COBALT_GTX_integer extension.
	template<typename genType>
	COBALT_FUNC_DECL genType factorial(genType const& x);

	//! 32bit signed integer.
	//! From COBALT_GTX_integer extension.
	typedef signed int					sint;

	//! Returns x raised to the y power.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL uint pow(uint x, uint y);

	//! Returns the positive square root of x.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL uint sqrt(uint x);

	//! Modulus. Returns x - y * floor(x / y) for each component in x using the floating point value y.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL uint mod(uint x, uint y);

	//! Returns the number of leading zeros.
	//! From COBALT_GTX_integer extension.
	COBALT_FUNC_DECL uint nlz(uint x);

	/// @}
}//namespace cobalt::math

#include "integer.inl"
