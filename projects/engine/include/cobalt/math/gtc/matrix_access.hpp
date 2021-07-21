/// @ref gtc_matrix_access
/// @file glm/gtc/matrix_access.hpp
///
/// @see core (dependence)
///
/// @defgroup gtc_matrix_access COBALT_GTC_matrix_access
/// @ingroup gtc
///
/// Include <cobalt/math/gtc/matrix_access.hpp> to use the features of this extension.
///
/// Defines functions to access rows or columns of a matrix easily.

#pragma once

// Dependency:
#include "../detail/setup.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	pragma message("COBALT: COBALT_GTC_matrix_access extension included")
#endif

namespace cobalt::math
{
	/// @addtogroup gtc_matrix_access
	/// @{

	/// Get a specific row of a matrix.
	/// @see gtc_matrix_access
	template<typename genType>
	COBALT_FUNC_DECL typename genType::row_type row(
		genType const& m,
		length_t index);

	/// Set a specific row to a matrix.
	/// @see gtc_matrix_access
	template<typename genType>
	COBALT_FUNC_DECL genType row(
		genType const& m,
		length_t index,
		typename genType::row_type const& x);

	/// Get a specific column of a matrix.
	/// @see gtc_matrix_access
	template<typename genType>
	COBALT_FUNC_DECL typename genType::col_type column(
		genType const& m,
		length_t index);

	/// Set a specific column to a matrix.
	/// @see gtc_matrix_access
	template<typename genType>
	COBALT_FUNC_DECL genType column(
		genType const& m,
		length_t index,
		typename genType::col_type const& x);

	/// @}
}//namespace cobalt::math

#include "matrix_access.inl"
