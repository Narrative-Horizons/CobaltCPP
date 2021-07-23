/// @ref gtx_hash
/// @file glm/gtx/hash.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_hash COBALT_GTX_hash
/// @ingroup gtx
///
/// Include <cobalt/math/gtx/hash.hpp> to use the features of this extension.
///
/// Add std::hash support for glm types

#pragma once

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_EXT_INCLUDED)
#	ifndef COBALT_ENABLE_EXPERIMENTAL
#		pragma message("COBALT: COBALT_GTX_hash is an experimental extension and may change in the future. Use #define COBALT_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("COBALT: COBALT_GTX_hash extension included")
#	endif
#endif

#include <functional>

#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../vec4.hpp"
#include "../gtc/vec1.hpp"

#include "../gtc/quaternion.hpp"
#include "../gtx/dual_quaternion.hpp"

#include "../mat2x2.hpp"
#include "../mat2x3.hpp"
#include "../mat2x4.hpp"

#include "../mat3x2.hpp"
#include "../mat3x3.hpp"
#include "../mat3x4.hpp"

#include "../mat4x2.hpp"
#include "../mat4x3.hpp"
#include "../mat4x4.hpp"

#if !COBALT_HAS_CXX11_STL
#	error "COBALT_GTX_hash requires C++11 standard library support"
#endif

namespace std
{
	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::vec<1, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::vec<1, T, Q> const& v) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::vec<2, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::vec<2, T, Q> const& v) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::vec<3, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::vec<3, T, Q> const& v) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::vec<4, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::vec<4, T, Q> const& v) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::qua<T,Q>>
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::qua<T, Q> const& q) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::tdualquat<T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::tdualquat<T,Q> const& q) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<2, 2, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<2, 2, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<2, 3, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<2, 3, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<2, 4, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<2, 4, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<3, 2, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<3, 2, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<3, 3, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<3, 3, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<3, 4, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<3, 4, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<4, 2, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<4, 2, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<4, 3, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<4, 3, T,Q> const& m) const;
	};

	template<typename T, cobalt::math::qualifier Q>
	struct hash<cobalt::math::mat<4, 4, T,Q> >
	{
		COBALT_FUNC_DECL size_t operator()(cobalt::math::mat<4, 4, T,Q> const& m) const;
	};
} // namespace std

#include "hash.inl"