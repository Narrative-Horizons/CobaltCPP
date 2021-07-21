/// @ref gtx_string_cast

#include <cstdarg>
#include <cstdio>

namespace cobalt::math{
namespace detail
{
	template <typename T>
	struct cast
	{
		typedef T value_type;
	};

	template <>
	struct cast<float>
	{
		typedef double value_type;
	};

	COBALT_FUNC_QUALIFIER std::string format(const char* msg, ...)
	{
		std::size_t const STRING_BUFFER(4096);
		char text[STRING_BUFFER];
		va_list list;

		if(msg == COBALT_NULLPTR)
			return std::string();

		va_start(list, msg);
#		if (COBALT_COMPILER & COBALT_COMPILER_VC)
			vsprintf_s(text, STRING_BUFFER, msg, list);
#		else//
			std::vsprintf(text, msg, list);
#		endif//
		va_end(list);

		return std::string(text);
	}

	static const char* LabelTrue = "true";
	static const char* LabelFalse = "false";

	template<typename T, bool isFloat = false>
	struct literal
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "%d";}
	};

	template<typename T>
	struct literal<T, true>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "%f";}
	};

#	if COBALT_MODEL == COBALT_MODEL_32 && COBALT_COMPILER && COBALT_COMPILER_VC
	template<>
	struct literal<uint64_t, false>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "%lld";}
	};

	template<>
	struct literal<int64_t, false>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "%lld";}
	};
#	endif//COBALT_MODEL == COBALT_MODEL_32 && COBALT_COMPILER && COBALT_COMPILER_VC

	template<typename T>
	struct prefix{};

	template<>
	struct prefix<float>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "";}
	};

	template<>
	struct prefix<double>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "d";}
	};

	template<>
	struct prefix<bool>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "b";}
	};

	template<>
	struct prefix<uint8_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "u8";}
	};

	template<>
	struct prefix<int8_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "i8";}
	};

	template<>
	struct prefix<uint16_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "u16";}
	};

	template<>
	struct prefix<int16_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "i16";}
	};

	template<>
	struct prefix<uint32_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "u";}
	};

	template<>
	struct prefix<int32_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "i";}
	};

	template<>
	struct prefix<uint64_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "u64";}
	};

	template<>
	struct prefix<int64_t>
	{
		COBALT_FUNC_QUALIFIER static char const * value() {return "i64";}
	};

	template<typename matType>
	struct compute_to_string
	{};

	template<qualifier Q>
	struct compute_to_string<vec<1, bool, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<1, bool, Q> const& x)
		{
			return detail::format("bvec1(%s)",
				x[0] ? detail::LabelTrue : detail::LabelFalse);
		}
	};

	template<qualifier Q>
	struct compute_to_string<vec<2, bool, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<2, bool, Q> const& x)
		{
			return detail::format("bvec2(%s, %s)",
				x[0] ? detail::LabelTrue : detail::LabelFalse,
				x[1] ? detail::LabelTrue : detail::LabelFalse);
		}
	};

	template<qualifier Q>
	struct compute_to_string<vec<3, bool, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<3, bool, Q> const& x)
		{
			return detail::format("bvec3(%s, %s, %s)",
				x[0] ? detail::LabelTrue : detail::LabelFalse,
				x[1] ? detail::LabelTrue : detail::LabelFalse,
				x[2] ? detail::LabelTrue : detail::LabelFalse);
		}
	};

	template<qualifier Q>
	struct compute_to_string<vec<4, bool, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<4, bool, Q> const& x)
		{
			return detail::format("bvec4(%s, %s, %s, %s)",
				x[0] ? detail::LabelTrue : detail::LabelFalse,
				x[1] ? detail::LabelTrue : detail::LabelFalse,
				x[2] ? detail::LabelTrue : detail::LabelFalse,
				x[3] ? detail::LabelTrue : detail::LabelFalse);
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<vec<1, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<1, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%svec1(%s)",
				PrefixStr,
				LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<vec<2, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<2, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%svec2(%s, %s)",
				PrefixStr,
				LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0]),
				static_cast<typename cast<T>::value_type>(x[1]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<vec<3, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<3, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%svec3(%s, %s, %s)",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0]),
				static_cast<typename cast<T>::value_type>(x[1]),
				static_cast<typename cast<T>::value_type>(x[2]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<vec<4, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(vec<4, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%svec4(%s, %s, %s, %s)",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0]),
				static_cast<typename cast<T>::value_type>(x[1]),
				static_cast<typename cast<T>::value_type>(x[2]),
				static_cast<typename cast<T>::value_type>(x[3]));
		}
	};


	template<typename T, qualifier Q>
	struct compute_to_string<mat<2, 2, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<2, 2, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat2x2((%s, %s), (%s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<2, 3, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<2, 3, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat2x3((%s, %s, %s), (%s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<2, 4, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<2, 4, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat2x4((%s, %s, %s, %s), (%s, %s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]), static_cast<typename cast<T>::value_type>(x[0][3]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]), static_cast<typename cast<T>::value_type>(x[1][3]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<3, 2, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<3, 2, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat3x2((%s, %s), (%s, %s), (%s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<3, 3, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<3, 3, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat3x3((%s, %s, %s), (%s, %s, %s), (%s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]), static_cast<typename cast<T>::value_type>(x[2][2]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<3, 4, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<3, 4, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat3x4((%s, %s, %s, %s), (%s, %s, %s, %s), (%s, %s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]), static_cast<typename cast<T>::value_type>(x[0][3]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]), static_cast<typename cast<T>::value_type>(x[1][3]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]), static_cast<typename cast<T>::value_type>(x[2][2]), static_cast<typename cast<T>::value_type>(x[2][3]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<4, 2, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<4, 2, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat4x2((%s, %s), (%s, %s), (%s, %s), (%s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr,
				LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]),
				static_cast<typename cast<T>::value_type>(x[3][0]), static_cast<typename cast<T>::value_type>(x[3][1]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<4, 3, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<4, 3, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat4x3((%s, %s, %s), (%s, %s, %s), (%s, %s, %s), (%s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]), static_cast<typename cast<T>::value_type>(x[2][2]),
				static_cast<typename cast<T>::value_type>(x[3][0]), static_cast<typename cast<T>::value_type>(x[3][1]), static_cast<typename cast<T>::value_type>(x[3][2]));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<mat<4, 4, T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(mat<4, 4, T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%smat4x4((%s, %s, %s, %s), (%s, %s, %s, %s), (%s, %s, %s, %s), (%s, %s, %s, %s))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x[0][0]), static_cast<typename cast<T>::value_type>(x[0][1]), static_cast<typename cast<T>::value_type>(x[0][2]), static_cast<typename cast<T>::value_type>(x[0][3]),
				static_cast<typename cast<T>::value_type>(x[1][0]), static_cast<typename cast<T>::value_type>(x[1][1]), static_cast<typename cast<T>::value_type>(x[1][2]), static_cast<typename cast<T>::value_type>(x[1][3]),
				static_cast<typename cast<T>::value_type>(x[2][0]), static_cast<typename cast<T>::value_type>(x[2][1]), static_cast<typename cast<T>::value_type>(x[2][2]), static_cast<typename cast<T>::value_type>(x[2][3]),
				static_cast<typename cast<T>::value_type>(x[3][0]), static_cast<typename cast<T>::value_type>(x[3][1]), static_cast<typename cast<T>::value_type>(x[3][2]), static_cast<typename cast<T>::value_type>(x[3][3]));
		}
	};


	template<typename T, qualifier Q>
	struct compute_to_string<qua<T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(qua<T, Q> const& q)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%squat(%s, {%s, %s, %s})",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(q.w),
				static_cast<typename cast<T>::value_type>(q.x),
				static_cast<typename cast<T>::value_type>(q.y),
				static_cast<typename cast<T>::value_type>(q.z));
		}
	};

	template<typename T, qualifier Q>
	struct compute_to_string<tdualquat<T, Q> >
	{
		COBALT_FUNC_QUALIFIER static std::string call(tdualquat<T, Q> const& x)
		{
			char const * PrefixStr = prefix<T>::value();
			char const * LiteralStr = literal<T, std::numeric_limits<T>::is_iec559>::value();
			std::string FormatStr(detail::format("%sdualquat((%s, {%s, %s, %s}), (%s, {%s, %s, %s}))",
				PrefixStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr,
				LiteralStr, LiteralStr, LiteralStr, LiteralStr));

			return detail::format(FormatStr.c_str(),
				static_cast<typename cast<T>::value_type>(x.real.w),
				static_cast<typename cast<T>::value_type>(x.real.x),
				static_cast<typename cast<T>::value_type>(x.real.y),
				static_cast<typename cast<T>::value_type>(x.real.z),
				static_cast<typename cast<T>::value_type>(x.dual.w),
				static_cast<typename cast<T>::value_type>(x.dual.x),
				static_cast<typename cast<T>::value_type>(x.dual.y),
				static_cast<typename cast<T>::value_type>(x.dual.z));
		}
	};

}//namespace detail

template<class matType>
COBALT_FUNC_QUALIFIER std::string to_string(matType const& x)
{
	return detail::compute_to_string<matType>::call(x);
}

}//namespace cobalt::math
