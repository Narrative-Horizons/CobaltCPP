/// @ref gtx_matrix_operation
/// @file glm/gtx/matrix_operation.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_matrix_operation COBALT_GTX_matrix_operation
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/matrix_operation.hpp> to use the features of this extension.
///
/// Build diagonal matrices from vectors.

#pragma once

// Dependency:
#include "../math.hpp"

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_matrix_operation is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_matrix_operation extension included")
#	endif
#endif

namespace cobalt::math
{
	/// @addtogroup gtx_matrix_operation
	/// @{

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<2, 2, T, Q> diagonal2x2(
		vec<2, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<2, 3, T, Q> diagonal2x3(
		vec<2, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<2, 4, T, Q> diagonal2x4(
		vec<2, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 2, T, Q> diagonal3x2(
		vec<2, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 3, T, Q> diagonal3x3(
		vec<3, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 4, T, Q> diagonal3x4(
		vec<3, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 2, T, Q> diagonal4x2(
		vec<2, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 3, T, Q> diagonal4x3(
		vec<3, T, Q> const& v);

	//! Build a diagonal matrix.
	//! From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> diagonal4x4(
		vec<4, T, Q> const& v);

	/// Build an adjugate  matrix.
	/// From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<2, 2, T, Q> adjugate(mat<2, 2, T, Q> const& m);

	/// Build an adjugate  matrix.
	/// From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<3, 3, T, Q> adjugate(mat<3, 3, T, Q> const& m);

	/// Build an adjugate  matrix.
	/// From COBALT_GTX_matrix_operation extension.
	template<typename T, qualifier Q>
	COBALT_FUNC_DECL mat<4, 4, T, Q> adjugate(mat<4, 4, T, Q> const& m);

	/// @}
}//namespace cobalt::math

#include "matrix_operation.inl"
