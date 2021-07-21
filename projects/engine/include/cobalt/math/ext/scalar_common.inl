namespace cobalt::math
{
	template<typename T>
	COBALT_FUNC_QUALIFIER T min(T a, T b, T c)
	{
		return cobalt::math::min(cobalt::math::min(a, b), c);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T min(T a, T b, T c, T d)
	{
		return cobalt::math::min(cobalt::math::min(a, b), cobalt::math::min(c, d));
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T max(T a, T b, T c)
	{
		return cobalt::math::max(cobalt::math::max(a, b), c);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T max(T a, T b, T c, T d)
	{
		return cobalt::math::max(cobalt::math::max(a, b), cobalt::math::max(c, d));
	}

#	if COBALT_HAS_CXX11_STL
		using std::fmin;
#	else
		template<typename T>
		COBALT_FUNC_QUALIFIER T fmin(T a, T b)
		{
			COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

			if (isnan(a))
				return b;
			return min(a, b);
		}
#	endif

	template<typename T>
	COBALT_FUNC_QUALIFIER T fmin(T a, T b, T c)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

		if (isnan(a))
			return fmin(b, c);
		if (isnan(b))
			return fmin(a, c);
		if (isnan(c))
			return min(a, b);
		return min(a, b, c);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T fmin(T a, T b, T c, T d)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

		if (isnan(a))
			return fmin(b, c, d);
		if (isnan(b))
			return min(a, fmin(c, d));
		if (isnan(c))
			return fmin(min(a, b), d);
		if (isnan(d))
			return min(a, b, c);
		return min(a, b, c, d);
	}


#	if COBALT_HAS_CXX11_STL
		using std::fmax;
#	else
		template<typename T>
		COBALT_FUNC_QUALIFIER T fmax(T a, T b)
		{
			COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

			if (isnan(a))
				return b;
			return max(a, b);
		}
#	endif

	template<typename T>
	COBALT_FUNC_QUALIFIER T fmax(T a, T b, T c)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

		if (isnan(a))
			return fmax(b, c);
		if (isnan(b))
			return fmax(a, c);
		if (isnan(c))
			return max(a, b);
		return max(a, b, c);
	}

	template<typename T>
	COBALT_FUNC_QUALIFIER T fmax(T a, T b, T c, T d)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

		if (isnan(a))
			return fmax(b, c, d);
		if (isnan(b))
			return max(a, fmax(c, d));
		if (isnan(c))
			return fmax(max(a, b), d);
		if (isnan(d))
			return max(a, b, c);
		return max(a, b, c, d);
	}

	// fclamp
	template<typename genType>
	COBALT_FUNC_QUALIFIER genType fclamp(genType x, genType minVal, genType maxVal)
	{
		COBALT_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fclamp' only accept floating-point or integer inputs");
		return fmin(fmax(x, minVal), maxVal);
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER genType clamp(genType const& Texcoord)
	{
		return cobalt::math::clamp(Texcoord, static_cast<genType>(0), static_cast<genType>(1));
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER genType repeat(genType const& Texcoord)
	{
		return cobalt::math::fract(Texcoord);
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER genType mirrorClamp(genType const& Texcoord)
	{
		return cobalt::math::fract(cobalt::math::abs(Texcoord));
	}

	template<typename genType>
	COBALT_FUNC_QUALIFIER genType mirrorRepeat(genType const& Texcoord)
	{
		genType const Abs = cobalt::math::abs(Texcoord);
		genType const Clamp = cobalt::math::mod(cobalt::math::floor(Abs), static_cast<genType>(2));
		genType const Floor = cobalt::math::floor(Abs);
		genType const Rest = Abs - Floor;
		genType const Mirror = Clamp + Rest;
		return mix(Rest, static_cast<genType>(1) - Rest, Mirror >= static_cast<genType>(1));
	}
}//namespace cobalt::math
