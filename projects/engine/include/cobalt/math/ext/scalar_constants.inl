#include <limits>

namespace cobalt::math
{
	template<typename genType>
	COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR genType epsilon()
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'epsilon' only accepts floating-point inputs");
		return std::numeric_limits<genType>::epsilon();
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR genType pi()
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'pi' only accepts floating-point inputs");
		return static_cast<genType>(3.14159265358979323846264338327950288);
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER COBALT_CONSTEXPR genType cos_one_over_two()
	{
		return genType(0.877582561890372716130286068203503191);
	}
} //namespace cobalt::math
