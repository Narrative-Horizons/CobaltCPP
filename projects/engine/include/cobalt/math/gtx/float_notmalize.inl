/// @ref gtx_float_normalize

#include <limits>

namespace cobalt::math
{
	template<length_t L, typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER vec<L, float, Q> floatNormalize(vec<L, T, Q> const& v)
	{
		return vec<L, float, Q>(v) / static_cast<float>(std::numeric_limits<T>::max());
	}

}//namespace cobalt::math
