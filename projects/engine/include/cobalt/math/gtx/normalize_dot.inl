/// @ref gtx_normalize_dot

namespace cobalt::math
{
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER T normalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		return cobalt::math::dot(x, y) * cobalt::math::inversesqrt(cobalt::math::dot(x, x) * cobalt::math::dot(y, y));
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER T fastNormalizeDot(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		return cobalt::math::dot(x, y) * cobalt::math::fastInverseSqrt(cobalt::math::dot(x, x) * cobalt::math::dot(y, y));
	}
}//namespace cobalt::math
