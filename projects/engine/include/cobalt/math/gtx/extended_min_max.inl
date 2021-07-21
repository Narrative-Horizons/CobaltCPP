/// @ref gtx_extended_min_max

namespace cobalt::math
{
	template<typename T>
	COBALT_FUNC_QUALIFIER T min(
		T const& x,
		T const& y,
		T const& z)
	{
		return cobalt::math::min(cobalt::math::min(x, y), z);
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z
	)
	{
		return cobalt::math::min(cobalt::math::min(x, y), z);
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z
	)
	{
		return cobalt::math::min(cobalt::math::min(x, y), z);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T min
	(
		T const& x,
		T const& y,
		T const& z,
		T const& w
	)
	{
		return cobalt::math::min(cobalt::math::min(x, y), cobalt::math::min(z, w));
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z,
		typename C<T>::T const& w
	)
	{
		return cobalt::math::min(cobalt::math::min(x, y), cobalt::math::min(z, w));
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z,
		C<T> const& w
	)
	{
		return cobalt::math::min(cobalt::math::min(x, y), cobalt::math::min(z, w));
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T max(
		T const& x,
		T const& y,
		T const& z)
	{
		return cobalt::math::max(cobalt::math::max(x, y), z);
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z
	)
	{
		return cobalt::math::max(cobalt::math::max(x, y), z);
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z
	)
	{
		return cobalt::math::max(cobalt::math::max(x, y), z);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T max
	(
		T const& x,
		T const& y,
		T const& z,
		T const& w
	)
	{
		return cobalt::math::max(cobalt::math::max(x, y), cobalt::math::max(z, w));
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z,
		typename C<T>::T const& w
	)
	{
		return cobalt::math::max(cobalt::math::max(x, y), cobalt::math::max(z, w));
	}

	template<typename T, template<typename> class C>
	COBALT_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z,
		C<T> const& w
	)
	{
		return cobalt::math::max(cobalt::math::max(x, y), cobalt::math::max(z, w));
	}
}//namespace cobalt::math
