/// @ref gtx_raw_data
/// @file glm/gtx/raw_data.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_raw_data COBALT_GTX_raw_data
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/raw_data.hpp> to use the features of this extension.
///
/// Projection of a vector to other one

#pragma once

// Dependencies
#include "../ext/scalar_uint_sized.hpp"
#include "../detail/setup.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_raw_data is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_raw_data extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_raw_data
	/// @{

	//! Type for byte numbers.
	//! From COBALT_GTX_raw_data extension.
	typedef detail::uint8		byte;

	//! Type for word numbers.
	//! From COBALT_GTX_raw_data extension.
	typedef detail::uint16		word;

	//! Type for dword numbers.
	//! From COBALT_GTX_raw_data extension.
	typedef detail::uint32		dword;

	//! Type for qword numbers.
	//! From COBALT_GTX_raw_data extension.
	typedef detail::uint64		qword;

	/// @}
}// namespace cobalt::math

#include "raw_data.inl"
