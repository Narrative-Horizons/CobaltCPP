/// @ref core
/// @file glm/detail/type_vec1.hpp

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
	struct vec<1, T, Q>
	{
		// -- Implementation detail --

		typedef T value_type;
		typedef vec<1, T, Q> type;
		typedef vec<1, bool, Q> bool_type;

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
#			endif
#		endif

#		if COBALT_CONFIG_XYZW_ONLY
			T x;
#		elif COBALT_CONFIG_ANONYMOUS_STRUCT == COBALT_ENABLE
			union
			{
				T x;
				T r;
				T s;

				typename detail::storage<1, T, detail::is_aligned<Q>::value>::type data;
/*
#				if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
					_COBALT_SWIZZLE1_2_MEMBERS(T, Q, x)
					_COBALT_SWIZZLE1_2_MEMBERS(T, Q, r)
					_COBALT_SWIZZLE1_2_MEMBERS(T, Q, s)
					_COBALT_SWIZZLE1_3_MEMBERS(T, Q, x)
					_COBALT_SWIZZLE1_3_MEMBERS(T, Q, r)
					_COBALT_SWIZZLE1_3_MEMBERS(T, Q, s)
					_COBALT_SWIZZLE1_4_MEMBERS(T, Q, x)
					_COBALT_SWIZZLE1_4_MEMBERS(T, Q, r)
					_COBALT_SWIZZLE1_4_MEMBERS(T, Q, s)
#				endif
*/
			};
#		else
			union {T x, r, s;};
/*
#			if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_FUNCTION
				COBALT_SWIZZLE_GEN_VEC_FROM_VEC1(T, Q)
#			endif
*/
#		endif

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
		COBALT_FUNC_DECL static COBALT_CONSTEXPR length_type length(){return 1;}

		COBALT_FUNC_DECL COBALT_CONSTEXPR T & operator[](length_type i);
		COBALT_FUNC_DECL COBALT_CONSTEXPR T const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec() COBALT_DEFAULT;
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec const& v) COBALT_DEFAULT;
		template<qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec(vec<1, T, P> const& v);

		// -- Explicit basic constructors --

		COBALT_FUNC_DECL COBALT_CONSTEXPR explicit vec(T scalar);

		// -- Conversion vector constructors --

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<2, U, P> const& v);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<3, U, P> const& v);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<4, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		COBALT_FUNC_DECL COBALT_CONSTEXPR COBALT_EXPLICIT vec(vec<1, U, P> const& v);

		// -- Swizzle constructors --
/*
#		if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
			template<int E0>
			COBALT_FUNC_DECL COBALT_CONSTEXPR vec(detail::_swizzle<1, T, Q, E0, -1,-2,-3> const& that)
			{
				*this = that();
			}
#		endif//COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
*/
		// -- Unary arithmetic operators --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator=(vec const& v) COBALT_DEFAULT;

		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator+=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator+=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator-=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator-=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator*=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator*=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator/=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator/=(vec<1, U, Q> const& v);

		// -- Increment and decrement operators --

		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator++();
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator--();
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator++(int);
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator--(int);

		// -- Unary bit operators --

		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator%=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator%=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator&=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator&=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator|=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator|=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator^=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator^=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator<<=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator<<=(vec<1, U, Q> const& v);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator>>=(U scalar);
		template<typename U>
		COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> & operator>>=(vec<1, U, Q> const& v);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v);

	// -- Binary operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator+(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator-(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator*(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator/(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator%(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator&(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator|(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator^(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator<<(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator>>(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, T, Q> operator~(vec<1, T, Q> const& v);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR bool operator==(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR bool operator!=(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, bool, Q> operator&&(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2);

	template<qualifier Q>
	COBALT_FUNC_DECL COBALT_CONSTEXPR vec<1, bool, Q> operator||(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2);
}//namespace cobalt::math

#ifndef COBALT_EXTERNAL_TEMPLATE
#include "type_vec1.inl"
#endif//COBALT_EXTERNAL_TEMPLATE
