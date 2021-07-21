/// @ref gtx_log_base

namespace cobalt::math
{
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType log(genType const& x, genType const& base)
	{
		return cobalt::math::log(x) / cobalt::math::log(base);
	}

	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, T, Q> log(vec<L, T, Q> const& x, vec<L, T, Q> const& base)
	{
		return cobalt::math::log(x) / cobalt::math::log(base);
	}
}//namespace cobalt::math
