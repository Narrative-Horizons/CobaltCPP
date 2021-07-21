/// @ref core
/// @file glm/detail/type_vec3.hpp

#pragma once

#include "qualifier.hpp"
#if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
#	include "_swizzle.hpp"
#elif COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_FUNCTION
#	include "_swizzle_func.hpp"
#endif
#include <cstddef>

namespace cobalt::math
{
	template<typename T, qualifier Q>
	struct vec<3, T, Q>
	{
		// -- Implementation detail --

		typedef T value_type;
		typedef vec<3, T, Q> type;
		typedef vec<3, bool, Q> bool_type;

		// -- Data --

#		if COBALT_SILENT_WARNINGS == COBALT_ENABLE
#			if COBALT_COMPILER & COBALT_COMPILER_GCC
#				pragma GCC diagnostic push
#				pragma GCC diagnostic ignored "-Wpedantic"
#			elif COBALT_COMPILER & COBALT_COMPILER_CLANG
#				pragma clang diagnostic push
#				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#				pragma clang diagnostic ignored "-Wnested-anon-types"
#			elif COBALT_COMPILER & COBALT_COMPILER_VC
#				pragma warning(push)
#				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#				if COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_ENABLE
#					pragma warning(disable: 4324)  // structure was padded due to alignment specifier
#				endif
#			endif
#		endif

#		if COBALT_CONFIG_XYZW_ONLY
			T x, y, z;
#		elif COBALT_CONFIG_ANONYMOUS_STRUCT == COBALT_ENABLE
			union
			{
				struct{ T x, y, z; };
				struct{ T r, g, b; };
				struct{ T s, t, p; };

				typename detail::storage<3, T, detail::is_aligned<Q>::value>::type data;

#				if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
					COBALT_SWIZZLE3_2_MEMBERS(T, Q, x, y, z)
					COBALT_SWIZZLE3_2_MEMBERS(T, Q, r, g, b)
					COBALT_SWIZZLE3_2_MEMBERS(T, Q, s, t, p)
					COBALT_SWIZZLE3_3_MEMBERS(T, Q, x, y, z)
					COBALT_SWIZZLE3_3_MEMBERS(T, Q, r, g, b)
					COBALT_SWIZZLE3_3_MEMBERS(T, Q, s, t, p)
					COBALT_SWIZZLE3_4_MEMBERS(T, Q, x, y, z)
					COBALT_SWIZZLE3_4_MEMBERS(T, Q, r, g, b)
					COBALT_SWIZZLE3_4_MEMBERS(T, Q, s, t, p)
#				endif
			};
#		else
			union { T x, r, s; };
			union { T y, g, t; };
			union { T z, b, p; };

#			if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_FUNCTION
				COBALT_SWIZZLE_GEN_VEC_FROM_VEC3(T, Q)
#			endif//COBALT_CONFIG_SWIZZLE
#		endif//COBALT_LANG

#		if COBALT_SILENT_WARNINGS == COBALT_ENABLE
#			if COBALT_COMPILER & COBALT_COMPILER_CLANG
#				pragma clang diagnostic pop
#			elif COBALT_COMPILER & COBALT_COMPILER_GCC
#				pragma GCC diagnostic pop
#			elif COBALT_COMPILER & COBALT_COMPILER_VC
#				pragma warning(pop)
#			endif
#		endif

		// -- Component accesses --

		/// Return the count of components of the vector
		typedef length_t length_type;
		COBALT_FUNC_DECL static COBALT_CONSTEXPR length_type length(){return 3;}

		COBALT_FUNC_DECL COBALT_CONSTEXPR T & operator[](length_type i);
		COBALT_FUNC_DECL COBALT_CONSTEXPR T const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec() COBALT_DEFAULT;
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec const& v) COBALT_DEFAULT;
		template<qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<3, T, P> const& v);

		// -- Explicit basic constructors --

		COBALT_FUNC_DECL COBALT_CONSTEXPR explicit vec(T scalar);
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(T a, T b, T c);

		// -- Conversion scalar constructors --

		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR explicit vec(vec<1, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(X x, Y y, Z z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, Z _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, Z _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(X _x, Y _y, vec<1, Z, Q> const& _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z);
		template<typename X, typename Y, typename Z>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z);

		// -- Conversion vector constructors --

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<2, A, P> const& _xy, B _z);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(A _x, vec<2, B, P> const& _yz);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<4, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<3, U, P> const& v);

		// -- Swizzle constructors --
#		if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
			template<int E0, int E1, int E2>
			COBALT_FUNC_DECL COBALT_CONSTEXPR vec(detail::_swizzle<3, T, Q, E0, E1, E2, -1> const& that)
			{
				*this = that();
			}

			template<int E0, int E1>
			COBALT_FUNC_DECL COBALT_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v, T const& scalar)
			{
				*this = vec(v(), scalar);
			}

			template<int E0, int E1>
			COBALT_FUNC_DECL COBALT_CONSTEXPR vec(T const& scalar, detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v)
			{
				*this = vec(scalar, v());
			}
#		endif//COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR

		// -- Unary arithmetic operators --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q>& operator=(vec<3, T, Q> const& v) COBALT_DEFAULT;

		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator+=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator+=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator+=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator-=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator-=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator-=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator*=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator*=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator*=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator/=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator/=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator/=(vec<3, U, Q> const& v);

		// -- Increment and decrement operators --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator++();
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator--();
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator++(int);
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator--(int);

		// -- Unary bit operators --

		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator%=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator%=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator%=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator&=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator&=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator&=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator|=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator|=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator|=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator^=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator^=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator^=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator<<=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator<<=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator<<=(vec<3, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator>>=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator>>=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> & operator>>=(vec<3, U, Q> const& v);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v);

	// -- Binary operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator*(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator*(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator/(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator/(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator%(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator%(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator&(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator&(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator|(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator|(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator^(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator^(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator<<(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator<<(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator>>(T scalar, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator>>(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, T, Q> operator~(vec<3, T, Q> const& v);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR bool operator==(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR bool operator!=(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

	template<qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, bool, Q> operator&&(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2);

	template<qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<3, bool, Q> operator||(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2);
}//namespace cobalt::math

#ifndef COBALT_EXTERNAL_TEMPLATE
#include "type_vec3.inl"
#endif//COBALT_EXTERNAL_TEMPLATE
