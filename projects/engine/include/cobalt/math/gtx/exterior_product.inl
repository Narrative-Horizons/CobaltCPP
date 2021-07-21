/// @ref gtx_exterior_product

#include <limits>

namespace cobalt::math {
namespace detail
{
	template<typename T, qualifier Q, bool Aligned>
	struct compute_cross_vec2
	{
		COBALT_FUNC_QUALIFIER static T call(vec<2, T, Q> const& v, vec<2, T, Q> const& u)
		{
			COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'cross' accepts only floating-point inputs");

			return v.x * u.y - u.x * v.y;
		}
	};
}//namespace detail

	template<typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER T cross(vec<2, T, Q> const& x, vec<2, T, Q> const& y)
	{
		return detail::compute_cross_vec2<T, Q, detail::is_aligned<Q>::value>::call(x, y);
	}
}//namespace cobalt::math

