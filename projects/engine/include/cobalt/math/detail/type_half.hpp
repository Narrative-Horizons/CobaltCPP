#pragma once

#include "setup.hpp"

namespace cobalt::math{
namespace detail
{
	typedef short hdata;

	COBALT_FUNC_DECL float toFloat32(hdata value);
	COBALT_FUNC_DECL hdata toFloat16(float const& value);

}//namespace detail
}//namespace cobalt::math

#include "type_half.inl"
