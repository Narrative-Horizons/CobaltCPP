/// @ref gtx_projection

namespace cobalt::math
{
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType proj(genType const& x, genType const& Normal)
	{
		return cobalt::math::dot(x, Normal) / cobalt::math::dot(Normal, Normal) * Normal;
	}
}//namespace cobalt::math
