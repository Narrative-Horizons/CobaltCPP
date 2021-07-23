/// @ref gtx_handed_coordinate_space

namespace cobalt::math
{
	template<typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER bool rightHanded
	(
		vec<3, T, Q> const& tangent,
		vec<3, T, Q> const& binormal,
		vec<3, T, Q> const& normal
	)
	{
		return dot(cross(normal, tangent), binormal) > T(0);
	}

	template<typename T, qualifier Q>
	COBALT_FUNC_QUALIFIER bool leftHanded
	(
		vec<3, T, Q> const& tangent,
		vec<3, T, Q> const& binormal,
		vec<3, T, Q> const& normal
	)
	{
		return dot(cross(normal, tangent), binormal) < T(0);
	}
}//namespace cobalt::math