/// @ref gtc_reciprocal

#include "../trigonometric.hpp"
#include <limits>

namespace cobalt::math
{
	// sec
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType sec(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'sec' only accept floating-point values");
		return genType(1) / cobalt::math::cos(angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> sec(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'sec' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(sec, x);
	}

	// csc
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType csc(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'csc' only accept floating-point values");
		return genType(1) / cobalt::math::sin(angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> csc(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'csc' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(csc, x);
	}

	// cot
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType cot(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'cot' only accept floating-point values");

		genType const pi_over_2 = genType(3.1415926535897932384626433832795 / 2.0);
		return cobalt::math::tan(pi_over_2 - angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> cot(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'cot' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(cot, x);
	}

	// asec
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType asec(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'asec' only accept floating-point values");
		return acos(genType(1) / x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> asec(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'asec' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(asec, x);
	}

	// acsc
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType acsc(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'acsc' only accept floating-point values");
		return asin(genType(1) / x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> acsc(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'acsc' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(acsc, x);
	}

	// acot
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType acot(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'acot' only accept floating-point values");

		genType const pi_over_2 = genType(3.1415926535897932384626433832795 / 2.0);
		return pi_over_2 - atan(x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> acot(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'acot' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(acot, x);
	}

	// sech
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType sech(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'sech' only accept floating-point values");
		return genType(1) / cobalt::math::cosh(angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> sech(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'sech' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(sech, x);
	}

	// csch
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType csch(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'csch' only accept floating-point values");
		return genType(1) / cobalt::math::sinh(angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> csch(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'csch' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(csch, x);
	}

	// coth
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType coth(genType angle)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'coth' only accept floating-point values");
		return cobalt::math::cosh(angle) / cobalt::math::sinh(angle);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> coth(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'coth' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(coth, x);
	}

	// asech
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType asech(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'asech' only accept floating-point values");
		return acosh(genType(1) / x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> asech(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'asech' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(asech, x);
	}

	// acsch
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType acsch(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'acsch' only accept floating-point values");
		return asinh(genType(1) / x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> acsch(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'acsch' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(acsch, x);
	}

	// acoth
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType acoth(genType x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'acoth' only accept floating-point values");
		return atanh(genType(1) / x);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> acoth(vec<L, T, Q> const& x)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'acoth' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(acoth, x);
	}
}//namespace cobalt::math
