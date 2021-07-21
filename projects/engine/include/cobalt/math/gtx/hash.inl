/// @ref gtx_hash
///
/// @see core (dependence)
///
/// @defgroup gtx_hash COBALT_GTX_hash
/// @ingroup gtx
///
/// @brief Add std::hash support for glm types
///
/// <cobalt/math/gtx/hash.inl> need to be included to use the features of this extension.

namespace cobalt::math {
namespace detail
{
	COBALT_INLINE void hash_combine(size_t &seed, size_t hash)
	{
		hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hash;
	}
}}

namespace std
{
	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::vec<1, T, Q>>::operator()(cobalt::math::vec<1, T, Q> const& v) const
	{
		hash<T> hasher;
		return hasher(v.x);
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::vec<2, T, Q>>::operator()(cobalt::math::vec<2, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(v.x));
		cobalt::math::detail::hash_combine(seed, hasher(v.y));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::vec<3, T, Q>>::operator()(cobalt::math::vec<3, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(v.x));
		cobalt::math::detail::hash_combine(seed, hasher(v.y));
		cobalt::math::detail::hash_combine(seed, hasher(v.z));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::vec<4, T, Q>>::operator()(cobalt::math::vec<4, T, Q> const& v) const
	{
		size_t seed = 0;
		hash<T> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(v.x));
		cobalt::math::detail::hash_combine(seed, hasher(v.y));
		cobalt::math::detail::hash_combine(seed, hasher(v.z));
		cobalt::math::detail::hash_combine(seed, hasher(v.w));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::qua<T, Q>>::operator()(cobalt::math::qua<T,Q> const& q) const
	{
		size_t seed = 0;
		hash<T> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(q.x));
		cobalt::math::detail::hash_combine(seed, hasher(q.y));
		cobalt::math::detail::hash_combine(seed, hasher(q.z));
		cobalt::math::detail::hash_combine(seed, hasher(q.w));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::tdualquat<T, Q>>::operator()(cobalt::math::tdualquat<T, Q> const& q) const
	{
		size_t seed = 0;
		hash<cobalt::math::qua<T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(q.real));
		cobalt::math::detail::hash_combine(seed, hasher(q.dual));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<2, 2, T, Q>>::operator()(cobalt::math::mat<2, 2, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<2, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<2, 3, T, Q>>::operator()(cobalt::math::mat<2, 3, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<3, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<2, 4, T, Q>>::operator()(cobalt::math::mat<2, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<4, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<3, 2, T, Q>>::operator()(cobalt::math::mat<3, 2, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<2, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<3, 3, T, Q>>::operator()(cobalt::math::mat<3, 3, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<3, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<3, 4, T, Q>>::operator()(cobalt::math::mat<3, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<4, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<4, 2, T,Q>>::operator()(cobalt::math::mat<4, 2, T,Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<2, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		cobalt::math::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<4, 3, T,Q>>::operator()(cobalt::math::mat<4, 3, T,Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<3, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		cobalt::math::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename T, cobalt::math::qualifier Q>
	COBALT_FUNC_QUALIFIER size_t hash<cobalt::math::mat<4, 4, T,Q>>::operator()(cobalt::math::mat<4, 4, T, Q> const& m) const
	{
		size_t seed = 0;
		hash<cobalt::math::vec<4, T, Q>> hasher;
		cobalt::math::detail::hash_combine(seed, hasher(m[0]));
		cobalt::math::detail::hash_combine(seed, hasher(m[1]));
		cobalt::math::detail::hash_combine(seed, hasher(m[2]));
		cobalt::math::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}
}
