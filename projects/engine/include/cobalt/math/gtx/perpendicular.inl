/// @ref gtx_perpendicular

namespace cobalt::math
{
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType perp(genType const& x, genType const& Normal)
	{
		return x - proj(x, Normal);
	}
}//namespace cobalt::math
