#ifndef COBALT_SETUP_INCLUDED

#include <cassert>
#include <cstddef>

#define COBALT_VERSION_MAJOR			0
#define COBALT_VERSION_MINOR			9
#define COBALT_VERSION_PATCH			9
#define COBALT_VERSION_REVISION		8
#define COBALT_VERSION					998
#define COBALT_VERSION_MESSAGE			"COBALT: version 0.9.9.8"

#define COBALT_SETUP_INCLUDED			COBALT_VERSION

///////////////////////////////////////////////////////////////////////////////////
// Active states

#define COBALT_DISABLE		0
#define COBALT_ENABLE		1

///////////////////////////////////////////////////////////////////////////////////
// Messages

#if defined(COBALT_FORCE_MESSAGES)
#	define COBALT_MESSAGES COBALT_ENABLE
#else
#	define COBALT_MESSAGES COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Detect the platform

#include "../simd/platform.h"

///////////////////////////////////////////////////////////////////////////////////
// Build model

#if defined(_M_ARM64) || defined(__LP64__) || defined(_M_X64) || defined(__ppc64__) || defined(__x86_64__)
#	define COBALT_MODEL	COBALT_MODEL_64
#elif defined(__i386__) || defined(__ppc__) || defined(__ILP32__) || defined(_M_ARM)
#	define COBALT_MODEL	COBALT_MODEL_32
#else
#	define COBALT_MODEL	COBALT_MODEL_32
#endif//

#if !defined(COBALT_MODEL) && COBALT_COMPILER != 0
#	error "COBALT_MODEL undefined, your compiler may not be supported by COBALT. Add #define COBALT_MODEL 0 to ignore this message."
#endif//COBALT_MODEL

///////////////////////////////////////////////////////////////////////////////////
// C++ Version

// User defines: COBALT_FORCE_CXX98, COBALT_FORCE_CXX03, COBALT_FORCE_CXX11, COBALT_FORCE_CXX14, COBALT_FORCE_CXX17, COBALT_FORCE_CXX2A

#define COBALT_LANG_CXX98_FLAG			(1 << 1)
#define COBALT_LANG_CXX03_FLAG			(1 << 2)
#define COBALT_LANG_CXX0X_FLAG			(1 << 3)
#define COBALT_LANG_CXX11_FLAG			(1 << 4)
#define COBALT_LANG_CXX14_FLAG			(1 << 5)
#define COBALT_LANG_CXX17_FLAG			(1 << 6)
#define COBALT_LANG_CXX2A_FLAG			(1 << 7)
#define COBALT_LANG_CXXMS_FLAG			(1 << 8)
#define COBALT_LANG_CXXGNU_FLAG		(1 << 9)

#define COBALT_LANG_CXX98			COBALT_LANG_CXX98_FLAG
#define COBALT_LANG_CXX03			(COBALT_LANG_CXX98 | COBALT_LANG_CXX03_FLAG)
#define COBALT_LANG_CXX0X			(COBALT_LANG_CXX03 | COBALT_LANG_CXX0X_FLAG)
#define COBALT_LANG_CXX11			(COBALT_LANG_CXX0X | COBALT_LANG_CXX11_FLAG)
#define COBALT_LANG_CXX14			(COBALT_LANG_CXX11 | COBALT_LANG_CXX14_FLAG)
#define COBALT_LANG_CXX17			(COBALT_LANG_CXX14 | COBALT_LANG_CXX17_FLAG)
#define COBALT_LANG_CXX2A			(COBALT_LANG_CXX17 | COBALT_LANG_CXX2A_FLAG)
#define COBALT_LANG_CXXMS			COBALT_LANG_CXXMS_FLAG
#define COBALT_LANG_CXXGNU			COBALT_LANG_CXXGNU_FLAG

#if (defined(_MSC_EXTENSIONS))
#	define COBALT_LANG_EXT COBALT_LANG_CXXMS_FLAG
#elif ((COBALT_COMPILER & (COBALT_COMPILER_CLANG | COBALT_COMPILER_GCC)) && (COBALT_ARCH & COBALT_ARCH_SIMD_BIT))
#	define COBALT_LANG_EXT COBALT_LANG_CXXMS_FLAG
#else
#	define COBALT_LANG_EXT 0
#endif

#if (defined(COBALT_FORCE_CXX_UNKNOWN))
#	define COBALT_LANG 0
#elif defined(COBALT_FORCE_CXX2A)
#	define COBALT_LANG (COBALT_LANG_CXX2A | COBALT_LANG_EXT)
#	define COBALT_LANG_STL11_FORCED
#elif defined(COBALT_FORCE_CXX17)
#	define COBALT_LANG (COBALT_LANG_CXX17 | COBALT_LANG_EXT)
#	define COBALT_LANG_STL11_FORCED
#elif defined(COBALT_FORCE_CXX14)
#	define COBALT_LANG (COBALT_LANG_CXX14 | COBALT_LANG_EXT)
#	define COBALT_LANG_STL11_FORCED
#elif defined(COBALT_FORCE_CXX11)
#	define COBALT_LANG (COBALT_LANG_CXX11 | COBALT_LANG_EXT)
#	define COBALT_LANG_STL11_FORCED
#elif defined(COBALT_FORCE_CXX03)
#	define COBALT_LANG (COBALT_LANG_CXX03 | COBALT_LANG_EXT)
#elif defined(COBALT_FORCE_CXX98)
#	define COBALT_LANG (COBALT_LANG_CXX98 | COBALT_LANG_EXT)
#else
#	if COBALT_COMPILER & COBALT_COMPILER_VC && defined(_MSVC_LANG)
#		if COBALT_COMPILER >= COBALT_COMPILER_VC15_7
#			define COBALT_LANG_PLATFORM _MSVC_LANG
#		elif COBALT_COMPILER >= COBALT_COMPILER_VC15
#			if _MSVC_LANG > 201402L
#				define COBALT_LANG_PLATFORM 201402L
#			else
#				define COBALT_LANG_PLATFORM _MSVC_LANG
#			endif
#		else
#			define COBALT_LANG_PLATFORM 0
#		endif
#	else
#		define COBALT_LANG_PLATFORM 0
#	endif

#	if __cplusplus > 201703L || COBALT_LANG_PLATFORM > 201703L
#		define COBALT_LANG (COBALT_LANG_CXX2A | COBALT_LANG_EXT)
#	elif __cplusplus == 201703L || COBALT_LANG_PLATFORM == 201703L
#		define COBALT_LANG (COBALT_LANG_CXX17 | COBALT_LANG_EXT)
#	elif __cplusplus == 201402L || __cplusplus == 201500L || COBALT_LANG_PLATFORM == 201402L
#		define COBALT_LANG (COBALT_LANG_CXX14 | COBALT_LANG_EXT)
#	elif __cplusplus == 201103L || COBALT_LANG_PLATFORM == 201103L
#		define COBALT_LANG (COBALT_LANG_CXX11 | COBALT_LANG_EXT)
#	elif defined(__INTEL_CXX11_MODE__) || defined(_MSC_VER) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#		define COBALT_LANG (COBALT_LANG_CXX0X | COBALT_LANG_EXT)
#	elif __cplusplus == 199711L
#		define COBALT_LANG (COBALT_LANG_CXX98 | COBALT_LANG_EXT)
#	else
#		define COBALT_LANG (0 | COBALT_LANG_EXT)
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Has of C++ features

// http://clang.llvm.org/cxx_status.html
// http://gcc.gnu.org/projects/cxx0x.html
// http://msdn.microsoft.com/en-us/library/vstudio/hh567368(v=vs.120).aspx

// Android has multiple STLs but C++11 STL detection doesn't always work #284 #564
#if COBALT_PLATFORM == COBALT_PLATFORM_ANDROID && !defined(COBALT_LANG_STL11_FORCED)
#	define COBALT_HAS_CXX11_STL 0
#elif COBALT_COMPILER & COBALT_COMPILER_CLANG
#	if (defined(_LIBCPP_VERSION) || (COBALT_LANG & COBALT_LANG_CXX11_FLAG) || defined(COBALT_LANG_STL11_FORCED))
#		define COBALT_HAS_CXX11_STL 1
#	else
#		define COBALT_HAS_CXX11_STL 0
#	endif
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_CXX11_STL 1
#else
#	define COBALT_HAS_CXX11_STL ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_GCC) && (COBALT_COMPILER >= COBALT_COMPILER_GCC48)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC12)) || \
		((COBALT_PLATFORM != COBALT_PLATFORM_WINDOWS) && (COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_COMPILER >= COBALT_COMPILER_INTEL15))))
#endif

// N1720
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_STATIC_ASSERT __has_feature(cxx_static_assert)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_STATIC_ASSERT 1
#else
#	define COBALT_HAS_STATIC_ASSERT ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_CUDA)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC))))
#endif

// N1988
#if COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_EXTENDED_INTEGER_TYPE 1
#else
#	define COBALT_HAS_EXTENDED_INTEGER_TYPE (\
		((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (COBALT_COMPILER & COBALT_COMPILER_VC)) || \
		((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (COBALT_COMPILER & COBALT_COMPILER_CUDA)) || \
		((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (COBALT_COMPILER & COBALT_COMPILER_CLANG)))
#endif

// N2672 Initializer lists http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2672.htm
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_INITIALIZER_LISTS __has_feature(cxx_generalized_initializers)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_INITIALIZER_LISTS 1
#else
#	define COBALT_HAS_INITIALIZER_LISTS ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC15)) || \
		((COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_COMPILER >= COBALT_COMPILER_INTEL14)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2544 Unrestricted unions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2544.pdf
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_UNRESTRICTED_UNIONS __has_feature(cxx_unrestricted_unions)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_UNRESTRICTED_UNIONS 1
#else
#	define COBALT_HAS_UNRESTRICTED_UNIONS (COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		(COBALT_COMPILER & COBALT_COMPILER_VC) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA)))
#endif

// N2346
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_DEFAULTED_FUNCTIONS __has_feature(cxx_defaulted_functions)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_DEFAULTED_FUNCTIONS 1
#else
#	define COBALT_HAS_DEFAULTED_FUNCTIONS ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC12)) || \
		((COBALT_COMPILER & COBALT_COMPILER_INTEL)) || \
		(COBALT_COMPILER & COBALT_COMPILER_CUDA)))
#endif

// N2118
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_RVALUE_REFERENCES 1
#else
#	define COBALT_HAS_RVALUE_REFERENCES ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_VC)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2437 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2437.pdf
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_EXPLICIT_CONVERSION_OPERATORS __has_feature(cxx_explicit_conversions)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_EXPLICIT_CONVERSION_OPERATORS 1
#else
#	define COBALT_HAS_EXPLICIT_CONVERSION_OPERATORS ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_COMPILER >= COBALT_COMPILER_INTEL14)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC12)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2258 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2258.pdf
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_TEMPLATE_ALIASES __has_feature(cxx_alias_templates)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_TEMPLATE_ALIASES 1
#else
#	define COBALT_HAS_TEMPLATE_ALIASES ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC12)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2930 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2930.html
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_RANGE_FOR __has_feature(cxx_range_for)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_RANGE_FOR 1
#else
#	define COBALT_HAS_RANGE_FOR ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2341 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2341.pdf
#if COBALT_COMPILER & COBALT_COMPILER_CLANG
#	define COBALT_HAS_ALIGNOF __has_feature(cxx_alignas)
#elif COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_ALIGNOF 1
#else
#	define COBALT_HAS_ALIGNOF ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_COMPILER >= COBALT_COMPILER_INTEL15)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC14)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

// N2235 Generalized Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
// N3652 Extended Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#if (COBALT_ARCH & COBALT_ARCH_SIMD_BIT) // Compiler SIMD intrinsics don't support constexpr...
#	define COBALT_HAS_CONSTEXPR 0
#elif (COBALT_COMPILER & COBALT_COMPILER_CLANG)
#	define COBALT_HAS_CONSTEXPR __has_feature(cxx_relaxed_constexpr)
#elif (COBALT_LANG & COBALT_LANG_CXX14_FLAG)
#	define COBALT_HAS_CONSTEXPR 1
#else
#	define COBALT_HAS_CONSTEXPR ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && COBALT_HAS_INITIALIZER_LISTS && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_COMPILER >= COBALT_COMPILER_INTEL17)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC15))))
#endif

#if COBALT_HAS_CONSTEXPR
#	define COBALT_CONSTEXPR constexpr
#else
#	define COBALT_CONSTEXPR
#endif

//
#if COBALT_HAS_CONSTEXPR
# if (COBALT_COMPILER & COBALT_COMPILER_CLANG)
#	if __has_feature(cxx_if_constexpr)
#		define COBALT_HAS_IF_CONSTEXPR 1
#	else
# 		define COBALT_HAS_IF_CONSTEXPR 0
#	endif
# elif (COBALT_LANG & COBALT_LANG_CXX17_FLAG)
# 	define COBALT_HAS_IF_CONSTEXPR 1
# else
# 	define COBALT_HAS_IF_CONSTEXPR 0
# endif
#else
#	define COBALT_HAS_IF_CONSTEXPR 0
#endif

#if COBALT_HAS_IF_CONSTEXPR
# 	define COBALT_IF_CONSTEXPR if constexpr
#else
#	define COBALT_IF_CONSTEXPR if
#endif

//
#if COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_ASSIGNABLE 1
#else
#	define COBALT_HAS_ASSIGNABLE ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC15)) || \
		((COBALT_COMPILER & COBALT_COMPILER_GCC) && (COBALT_COMPILER >= COBALT_COMPILER_GCC49))))
#endif

//
#define COBALT_HAS_TRIVIAL_QUERIES 0

//
#if COBALT_LANG & COBALT_LANG_CXX11_FLAG
#	define COBALT_HAS_MAKE_SIGNED 1
#else
#	define COBALT_HAS_MAKE_SIGNED ((COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (\
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC12)) || \
		((COBALT_COMPILER & COBALT_COMPILER_CUDA))))
#endif

//
#if defined(COBALT_FORCE_INTRINSICS)
#	define COBALT_HAS_BITSCAN_WINDOWS ((COBALT_PLATFORM & COBALT_PLATFORM_WINDOWS) && (\
		((COBALT_COMPILER & COBALT_COMPILER_INTEL)) || \
		((COBALT_COMPILER & COBALT_COMPILER_VC) && (COBALT_COMPILER >= COBALT_COMPILER_VC14) && (COBALT_ARCH & COBALT_ARCH_X86_BIT))))
#else
#	define COBALT_HAS_BITSCAN_WINDOWS 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// OpenMP
#ifdef _OPENMP
#	if COBALT_COMPILER & COBALT_COMPILER_GCC
#		if COBALT_COMPILER >= COBALT_COMPILER_GCC61
#			define COBALT_HAS_OPENMP 45
#		elif COBALT_COMPILER >= COBALT_COMPILER_GCC49
#			define COBALT_HAS_OPENMP 40
#		elif COBALT_COMPILER >= COBALT_COMPILER_GCC47
#			define COBALT_HAS_OPENMP 31
#		else
#			define COBALT_HAS_OPENMP 0
#		endif
#	elif COBALT_COMPILER & COBALT_COMPILER_CLANG
#		if COBALT_COMPILER >= COBALT_COMPILER_CLANG38
#			define COBALT_HAS_OPENMP 31
#		else
#			define COBALT_HAS_OPENMP 0
#		endif
#	elif COBALT_COMPILER & COBALT_COMPILER_VC
#		define COBALT_HAS_OPENMP 20
#	elif COBALT_COMPILER & COBALT_COMPILER_INTEL
#		if COBALT_COMPILER >= COBALT_COMPILER_INTEL16
#			define COBALT_HAS_OPENMP 40
#		else
#			define COBALT_HAS_OPENMP 0
#		endif
#	else
#		define COBALT_HAS_OPENMP 0
#	endif
#else
#	define COBALT_HAS_OPENMP 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// nullptr

#if COBALT_LANG & COBALT_LANG_CXX0X_FLAG
#	define COBALT_CONFIG_NULLPTR COBALT_ENABLE
#else
#	define COBALT_CONFIG_NULLPTR COBALT_DISABLE
#endif

#if COBALT_CONFIG_NULLPTR == COBALT_ENABLE
#	define COBALT_NULLPTR nullptr
#else
#	define COBALT_NULLPTR 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// Static assert

#if COBALT_HAS_STATIC_ASSERT
#	define COBALT_STATIC_ASSERT(x, message) static_assert(x, message)
#elif COBALT_COMPILER & COBALT_COMPILER_VC
#	define COBALT_STATIC_ASSERT(x, message) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#else
#	define COBALT_STATIC_ASSERT(x, message) assert(x)
#endif//COBALT_LANG

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

#if COBALT_COMPILER & COBALT_COMPILER_CUDA
#	define COBALT_CUDA_FUNC_DEF __device__ __host__
#	define COBALT_CUDA_FUNC_DECL __device__ __host__
#else
#	define COBALT_CUDA_FUNC_DEF
#	define COBALT_CUDA_FUNC_DECL
#endif

#if defined(COBALT_FORCE_INLINE)
#	if COBALT_COMPILER & COBALT_COMPILER_VC
#		define COBALT_INLINE __forceinline
#		define COBALT_NEVER_INLINE __declspec((noinline))
#	elif COBALT_COMPILER & (COBALT_COMPILER_GCC | COBALT_COMPILER_CLANG)
#		define COBALT_INLINE inline __attribute__((__always_inline__))
#		define COBALT_NEVER_INLINE __attribute__((__noinline__))
#	elif COBALT_COMPILER & COBALT_COMPILER_CUDA
#		define COBALT_INLINE __forceinline__
#		define COBALT_NEVER_INLINE __noinline__
#	else
#		define COBALT_INLINE inline
#		define COBALT_NEVER_INLINE
#	endif//COBALT_COMPILER
#else
#	define COBALT_INLINE inline
#	define COBALT_NEVER_INLINE
#endif//defined(COBALT_FORCE_INLINE)

#define COBALT_FUNC_DECL COBALT_CUDA_FUNC_DECL
#define COBALT_FUNC_QUALIFIER COBALT_CUDA_FUNC_DEF COBALT_INLINE

///////////////////////////////////////////////////////////////////////////////////
// Swizzle operators

// User defines: COBALT_FORCE_SWIZZLE

#define COBALT_SWIZZLE_DISABLED		0
#define COBALT_SWIZZLE_OPERATOR		1
#define COBALT_SWIZZLE_FUNCTION		2

#if defined(COBALT_FORCE_XYZW_ONLY)
#	undef COBALT_FORCE_SWIZZLE
#endif

#if defined(COBALT_SWIZZLE)
#	pragma message("COBALT: COBALT_SWIZZLE is deprecated, use COBALT_FORCE_SWIZZLE instead.")
#	define COBALT_FORCE_SWIZZLE
#endif

#if defined(COBALT_FORCE_SWIZZLE) && (COBALT_LANG & COBALT_LANG_CXXMS_FLAG)
#	define COBALT_CONFIG_SWIZZLE COBALT_SWIZZLE_OPERATOR
#elif defined(COBALT_FORCE_SWIZZLE)
#	define COBALT_CONFIG_SWIZZLE COBALT_SWIZZLE_FUNCTION
#else
#	define COBALT_CONFIG_SWIZZLE COBALT_SWIZZLE_DISABLED
#endif

///////////////////////////////////////////////////////////////////////////////////
// Allows using not basic types as genType

// #define COBALT_FORCE_UNRESTRICTED_GENTYPE

#ifdef COBALT_FORCE_UNRESTRICTED_GENTYPE
#	define COBALT_CONFIG_UNRESTRICTED_GENTYPE COBALT_ENABLE
#else
#	define COBALT_CONFIG_UNRESTRICTED_GENTYPE COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Clip control, define COBALT_FORCE_DEPTH_ZERO_TO_ONE before including COBALT
// to use a clip space between 0 to 1.
// Coordinate system, define COBALT_FORCE_LEFT_HANDED before including COBALT
// to use left handed coordinate system by default.

#define COBALT_CLIP_CONTROL_ZO_BIT		(1 << 0) // ZERO_TO_ONE
#define COBALT_CLIP_CONTROL_NO_BIT		(1 << 1) // NEGATIVE_ONE_TO_ONE
#define COBALT_CLIP_CONTROL_LH_BIT		(1 << 2) // LEFT_HANDED, For DirectX, Metal, Vulkan
#define COBALT_CLIP_CONTROL_RH_BIT		(1 << 3) // RIGHT_HANDED, For OpenGL, default in COBALT

#define COBALT_CLIP_CONTROL_LH_ZO (COBALT_CLIP_CONTROL_LH_BIT | COBALT_CLIP_CONTROL_ZO_BIT)
#define COBALT_CLIP_CONTROL_LH_NO (COBALT_CLIP_CONTROL_LH_BIT | COBALT_CLIP_CONTROL_NO_BIT)
#define COBALT_CLIP_CONTROL_RH_ZO (COBALT_CLIP_CONTROL_RH_BIT | COBALT_CLIP_CONTROL_ZO_BIT)
#define COBALT_CLIP_CONTROL_RH_NO (COBALT_CLIP_CONTROL_RH_BIT | COBALT_CLIP_CONTROL_NO_BIT)

#ifdef COBALT_FORCE_DEPTH_ZERO_TO_ONE
#	ifdef COBALT_FORCE_LEFT_HANDED
#		define COBALT_CONFIG_CLIP_CONTROL COBALT_CLIP_CONTROL_LH_ZO
#	else
#		define COBALT_CONFIG_CLIP_CONTROL COBALT_CLIP_CONTROL_RH_ZO
#	endif
#else
#	ifdef COBALT_FORCE_LEFT_HANDED
#		define COBALT_CONFIG_CLIP_CONTROL COBALT_CLIP_CONTROL_LH_NO
#	else
#		define COBALT_CONFIG_CLIP_CONTROL COBALT_CLIP_CONTROL_RH_NO
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

#if (COBALT_COMPILER & COBALT_COMPILER_VC) || ((COBALT_COMPILER & COBALT_COMPILER_INTEL) && (COBALT_PLATFORM & COBALT_PLATFORM_WINDOWS))
#	define COBALT_DEPRECATED __declspec(deprecated)
#	define COBALT_ALIGNED_TYPEDEF(type, name, alignment) typedef __declspec(align(alignment)) type name
#elif COBALT_COMPILER & (COBALT_COMPILER_GCC | COBALT_COMPILER_CLANG | COBALT_COMPILER_INTEL)
#	define COBALT_DEPRECATED __attribute__((__deprecated__))
#	define COBALT_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __attribute__((aligned(alignment)))
#elif COBALT_COMPILER & COBALT_COMPILER_CUDA
#	define COBALT_DEPRECATED
#	define COBALT_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __align__(x)
#else
#	define COBALT_DEPRECATED
#	define COBALT_ALIGNED_TYPEDEF(type, name, alignment) typedef type name
#endif

///////////////////////////////////////////////////////////////////////////////////

#ifdef COBALT_FORCE_EXPLICIT_CTOR
#	define COBALT_EXPLICIT explicit
#else
#	define COBALT_EXPLICIT
#endif

///////////////////////////////////////////////////////////////////////////////////
// SYCL

#if COBALT_COMPILER==COBALT_COMPILER_SYCL

#include <CL/sycl.hpp>
#include <limits>

namespace cobalt::math {
namespace std {
	// Import SYCL's functions into the namespace cobalt::math::std to force their usages.
	// It's important to use the math built-in function (sin, exp, ...)
	// of SYCL instead the std ones.
	using namespace cl::sycl;

	///////////////////////////////////////////////////////////////////////////////
	// Import some "harmless" std's stuffs used by glm into
	// the new cobalt::math::std namespace.
	template<typename T>
	using numeric_limits = ::std::numeric_limits<T>;

	using ::std::size_t;

	using ::std::uint8_t;
	using ::std::uint16_t;
	using ::std::uint32_t;
	using ::std::uint64_t;

	using ::std::int8_t;
	using ::std::int16_t;
	using ::std::int32_t;
	using ::std::int64_t;

	using ::std::make_unsigned;
	///////////////////////////////////////////////////////////////////////////////
} //namespace std
} //namespace cobalt::math

#endif

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// Length type: all length functions returns a length_t type.
// When COBALT_FORCE_SIZE_T_LENGTH is defined, length_t is a typedef of size_t otherwise
// length_t is a typedef of int like GLSL defines it.

#define COBALT_LENGTH_INT		1
#define COBALT_LENGTH_SIZE_T	2

#ifdef COBALT_FORCE_SIZE_T_LENGTH
#	define COBALT_CONFIG_LENGTH_TYPE		COBALT_LENGTH_SIZE_T
#else
#	define COBALT_CONFIG_LENGTH_TYPE		COBALT_LENGTH_INT
#endif

namespace cobalt::math
{
	using std::size_t;
#	if COBALT_CONFIG_LENGTH_TYPE == COBALT_LENGTH_SIZE_T
		typedef size_t length_t;
#	else
		typedef int length_t;
#	endif
}//namespace cobalt::math

///////////////////////////////////////////////////////////////////////////////////
// constexpr

#if COBALT_HAS_CONSTEXPR
#	define COBALT_CONFIG_CONSTEXP COBALT_ENABLE

	namespace cobalt::math
	{
		template<typename T, std::size_t N>
		constexpr std::size_t countof(T const (&)[N])
		{
			return N;
		}
	}//namespace cobalt::math
#	define COBALT_COUNTOF(arr) cobalt::math::countof(arr)
#elif defined(_MSC_VER)
#	define COBALT_CONFIG_CONSTEXP COBALT_DISABLE

#	define COBALT_COUNTOF(arr) _countof(arr)
#else
#	define COBALT_CONFIG_CONSTEXP COBALT_DISABLE

#	define COBALT_COUNTOF(arr) sizeof(arr) / sizeof(arr[0])
#endif

///////////////////////////////////////////////////////////////////////////////////
// uint

namespace cobalt::math{
namespace detail
{
	template<typename T>
	struct is_int
	{
		enum test {value = 0};
	};

	template<>
	struct is_int<unsigned int>
	{
		enum test {value = ~0};
	};

	template<>
	struct is_int<signed int>
	{
		enum test {value = ~0};
	};
}//namespace detail

	typedef unsigned int	uint;
}//namespace cobalt::math

///////////////////////////////////////////////////////////////////////////////////
// 64-bit int

#if COBALT_HAS_EXTENDED_INTEGER_TYPE
#	include <cstdint>
#endif

namespace cobalt::math{
namespace detail
{
#	if COBALT_HAS_EXTENDED_INTEGER_TYPE
		typedef std::uint64_t						uint64;
		typedef std::int64_t						int64;
#	elif (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) // C99 detected, 64 bit types available
		typedef uint64_t							uint64;
		typedef int64_t								int64;
#	elif COBALT_COMPILER & COBALT_COMPILER_VC
		typedef unsigned __int64					uint64;
		typedef signed __int64						int64;
#	elif COBALT_COMPILER & COBALT_COMPILER_GCC
#		pragma GCC diagnostic ignored "-Wlong-long"
		__extension__ typedef unsigned long long	uint64;
		__extension__ typedef signed long long		int64;
#	elif (COBALT_COMPILER & COBALT_COMPILER_CLANG)
#		pragma clang diagnostic ignored "-Wc++11-long-long"
		typedef unsigned long long					uint64;
		typedef signed long long					int64;
#	else//unknown compiler
		typedef unsigned long long					uint64;
		typedef signed long long					int64;
#	endif
}//namespace detail
}//namespace cobalt::math

///////////////////////////////////////////////////////////////////////////////////
// make_unsigned

#if COBALT_HAS_MAKE_SIGNED
#	include <type_traits>

namespace cobalt::math{
namespace detail
{
	using std::make_unsigned;
}//namespace detail
}//namespace cobalt::math

#else

namespace cobalt::math{
namespace detail
{
	template<typename genType>
	struct make_unsigned
	{};

	template<>
	struct make_unsigned<char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<signed char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<short>
	{
		typedef unsigned short type;
	};

	template<>
	struct make_unsigned<int>
	{
		typedef unsigned int type;
	};

	template<>
	struct make_unsigned<long>
	{
		typedef unsigned long type;
	};

	template<>
	struct make_unsigned<int64>
	{
		typedef uint64 type;
	};

	template<>
	struct make_unsigned<unsigned char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<unsigned short>
	{
		typedef unsigned short type;
	};

	template<>
	struct make_unsigned<unsigned int>
	{
		typedef unsigned int type;
	};

	template<>
	struct make_unsigned<unsigned long>
	{
		typedef unsigned long type;
	};

	template<>
	struct make_unsigned<uint64>
	{
		typedef uint64 type;
	};
}//namespace detail
}//namespace cobalt::math
#endif

///////////////////////////////////////////////////////////////////////////////////
// Only use x, y, z, w as vector type components

#ifdef COBALT_FORCE_XYZW_ONLY
#	define COBALT_CONFIG_XYZW_ONLY COBALT_ENABLE
#else
#	define COBALT_CONFIG_XYZW_ONLY COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of defaulted initialized types

#define COBALT_CTOR_INIT_DISABLE		0
#define COBALT_CTOR_INITIALIZER_LIST	1
#define COBALT_CTOR_INITIALISATION		2

#if defined(COBALT_FORCE_CTOR_INIT) && COBALT_HAS_INITIALIZER_LISTS
#	define COBALT_CONFIG_CTOR_INIT COBALT_CTOR_INITIALIZER_LIST
#elif defined(COBALT_FORCE_CTOR_INIT) && !COBALT_HAS_INITIALIZER_LISTS
#	define COBALT_CONFIG_CTOR_INIT COBALT_CTOR_INITIALISATION
#else
#	define COBALT_CONFIG_CTOR_INIT COBALT_CTOR_INIT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Use SIMD instruction sets

#if COBALT_HAS_ALIGNOF && (COBALT_LANG & COBALT_LANG_CXXMS_FLAG) && (COBALT_ARCH & COBALT_ARCH_SIMD_BIT)
#	define COBALT_CONFIG_SIMD COBALT_ENABLE
#else
#	define COBALT_CONFIG_SIMD COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of defaulted function

#if COBALT_HAS_DEFAULTED_FUNCTIONS && COBALT_CONFIG_CTOR_INIT == COBALT_CTOR_INIT_DISABLE
#	define COBALT_CONFIG_DEFAULTED_FUNCTIONS COBALT_ENABLE
#	define COBALT_DEFAULT = default
#else
#	define COBALT_CONFIG_DEFAULTED_FUNCTIONS COBALT_DISABLE
#	define COBALT_DEFAULT
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of aligned gentypes

#ifdef COBALT_FORCE_ALIGNED // Legacy define
#	define COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES
#endif

#ifdef COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES
#	define COBALT_FORCE_ALIGNED_GENTYPES
#endif

#if COBALT_HAS_ALIGNOF && (COBALT_LANG & COBALT_LANG_CXXMS_FLAG) && (defined(COBALT_FORCE_ALIGNED_GENTYPES) || (COBALT_CONFIG_SIMD == COBALT_ENABLE))
#	define COBALT_CONFIG_ALIGNED_GENTYPES COBALT_ENABLE
#else
#	define COBALT_CONFIG_ALIGNED_GENTYPES COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of anonymous structure as implementation detail

#if ((COBALT_CONFIG_SIMD == COBALT_ENABLE) || (COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR) || (COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_ENABLE))
#	define COBALT_CONFIG_ANONYMOUS_STRUCT COBALT_ENABLE
#else
#	define COBALT_CONFIG_ANONYMOUS_STRUCT COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Silent warnings

#ifdef COBALT_FORCE_SILENT_WARNINGS
#	define COBALT_SILENT_WARNINGS COBALT_ENABLE
#else
#	define COBALT_SILENT_WARNINGS COBALT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Precision

#define COBALT_HIGHP		1
#define COBALT_MEDIUMP		2
#define COBALT_LOWP		3

#if defined(COBALT_FORCE_PRECISION_HIGHP_BOOL) || defined(COBALT_PRECISION_HIGHP_BOOL)
#	define COBALT_CONFIG_PRECISION_BOOL		COBALT_HIGHP
#elif defined(COBALT_FORCE_PRECISION_MEDIUMP_BOOL) || defined(COBALT_PRECISION_MEDIUMP_BOOL)
#	define COBALT_CONFIG_PRECISION_BOOL		COBALT_MEDIUMP
#elif defined(COBALT_FORCE_PRECISION_LOWP_BOOL) || defined(COBALT_PRECISION_LOWP_BOOL)
#	define COBALT_CONFIG_PRECISION_BOOL		COBALT_LOWP
#else
#	define COBALT_CONFIG_PRECISION_BOOL		COBALT_HIGHP
#endif

#if defined(COBALT_FORCE_PRECISION_HIGHP_INT) || defined(COBALT_PRECISION_HIGHP_INT)
#	define COBALT_CONFIG_PRECISION_INT			COBALT_HIGHP
#elif defined(COBALT_FORCE_PRECISION_MEDIUMP_INT) || defined(COBALT_PRECISION_MEDIUMP_INT)
#	define COBALT_CONFIG_PRECISION_INT			COBALT_MEDIUMP
#elif defined(COBALT_FORCE_PRECISION_LOWP_INT) || defined(COBALT_PRECISION_LOWP_INT)
#	define COBALT_CONFIG_PRECISION_INT			COBALT_LOWP
#else
#	define COBALT_CONFIG_PRECISION_INT			COBALT_HIGHP
#endif

#if defined(COBALT_FORCE_PRECISION_HIGHP_UINT) || defined(COBALT_PRECISION_HIGHP_UINT)
#	define COBALT_CONFIG_PRECISION_UINT		COBALT_HIGHP
#elif defined(COBALT_FORCE_PRECISION_MEDIUMP_UINT) || defined(COBALT_PRECISION_MEDIUMP_UINT)
#	define COBALT_CONFIG_PRECISION_UINT		COBALT_MEDIUMP
#elif defined(COBALT_FORCE_PRECISION_LOWP_UINT) || defined(COBALT_PRECISION_LOWP_UINT)
#	define COBALT_CONFIG_PRECISION_UINT		COBALT_LOWP
#else
#	define COBALT_CONFIG_PRECISION_UINT		COBALT_HIGHP
#endif

#if defined(COBALT_FORCE_PRECISION_HIGHP_FLOAT) || defined(COBALT_PRECISION_HIGHP_FLOAT)
#	define COBALT_CONFIG_PRECISION_FLOAT		COBALT_HIGHP
#elif defined(COBALT_FORCE_PRECISION_MEDIUMP_FLOAT) || defined(COBALT_PRECISION_MEDIUMP_FLOAT)
#	define COBALT_CONFIG_PRECISION_FLOAT		COBALT_MEDIUMP
#elif defined(COBALT_FORCE_PRECISION_LOWP_FLOAT) || defined(COBALT_PRECISION_LOWP_FLOAT)
#	define COBALT_CONFIG_PRECISION_FLOAT		COBALT_LOWP
#else
#	define COBALT_CONFIG_PRECISION_FLOAT		COBALT_HIGHP
#endif

#if defined(COBALT_FORCE_PRECISION_HIGHP_DOUBLE) || defined(COBALT_PRECISION_HIGHP_DOUBLE)
#	define COBALT_CONFIG_PRECISION_DOUBLE		COBALT_HIGHP
#elif defined(COBALT_FORCE_PRECISION_MEDIUMP_DOUBLE) || defined(COBALT_PRECISION_MEDIUMP_DOUBLE)
#	define COBALT_CONFIG_PRECISION_DOUBLE		COBALT_MEDIUMP
#elif defined(COBALT_FORCE_PRECISION_LOWP_DOUBLE) || defined(COBALT_PRECISION_LOWP_DOUBLE)
#	define COBALT_CONFIG_PRECISION_DOUBLE		COBALT_LOWP
#else
#	define COBALT_CONFIG_PRECISION_DOUBLE		COBALT_HIGHP
#endif

///////////////////////////////////////////////////////////////////////////////////
// Check inclusions of different versions of COBALT

#elif ((COBALT_SETUP_INCLUDED != COBALT_VERSION) && !defined(COBALT_FORCE_IGNORE_VERSION))
#	error "COBALT error: A different version of COBALT is already included. Define COBALT_FORCE_IGNORE_VERSION before including COBALT headers to ignore this error."
#elif COBALT_SETUP_INCLUDED == COBALT_VERSION

///////////////////////////////////////////////////////////////////////////////////
// Messages

#if COBALT_MESSAGES == COBALT_ENABLE && !defined(COBALT_MESSAGE_DISPLAYED)
#	define COBALT_MESSAGE_DISPLAYED
#		define COBALT_STR_HELPER(x) #x
#		define COBALT_STR(x) COBALT_STR_HELPER(x)

	// Report COBALT version
#		pragma message (COBALT_STR(COBALT_VERSION_MESSAGE))

	// Report C++ language
#	if (COBALT_LANG & COBALT_LANG_CXX2A_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 2A with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX2A_FLAG)
#		pragma message("COBALT: C++ 2A")
#	elif (COBALT_LANG & COBALT_LANG_CXX17_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 17 with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX17_FLAG)
#		pragma message("COBALT: C++ 17")
#	elif (COBALT_LANG & COBALT_LANG_CXX14_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 14 with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX14_FLAG)
#		pragma message("COBALT: C++ 14")
#	elif (COBALT_LANG & COBALT_LANG_CXX11_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 11 with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX11_FLAG)
#		pragma message("COBALT: C++ 11")
#	elif (COBALT_LANG & COBALT_LANG_CXX0X_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 0x with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX0X_FLAG)
#		pragma message("COBALT: C++ 0x")
#	elif (COBALT_LANG & COBALT_LANG_CXX03_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 03 with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX03_FLAG)
#		pragma message("COBALT: C++ 03")
#	elif (COBALT_LANG & COBALT_LANG_CXX98_FLAG) && (COBALT_LANG & COBALT_LANG_EXT)
#		pragma message("COBALT: C++ 98 with extensions")
#	elif (COBALT_LANG & COBALT_LANG_CXX98_FLAG)
#		pragma message("COBALT: C++ 98")
#	else
#		pragma message("COBALT: C++ language undetected")
#	endif//COBALT_LANG

	// Report compiler detection
#	if COBALT_COMPILER & COBALT_COMPILER_CUDA
#		pragma message("COBALT: CUDA compiler detected")
#	elif COBALT_COMPILER & COBALT_COMPILER_VC
#		pragma message("COBALT: Visual C++ compiler detected")
#	elif COBALT_COMPILER & COBALT_COMPILER_CLANG
#		pragma message("COBALT: Clang compiler detected")
#	elif COBALT_COMPILER & COBALT_COMPILER_INTEL
#		pragma message("COBALT: Intel Compiler detected")
#	elif COBALT_COMPILER & COBALT_COMPILER_GCC
#		pragma message("COBALT: GCC compiler detected")
#	else
#		pragma message("COBALT: Compiler not detected")
#	endif

	// Report build target
#	if (COBALT_ARCH & COBALT_ARCH_AVX2_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with AVX2 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_AVX2_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with AVX2 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_AVX_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with AVX instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_AVX_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with AVX instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_SSE42_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with SSE4.2 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_SSE42_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with SSE4.2 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_SSE41_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with SSE4.1 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_SSE41_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with SSE4.1 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_SSSE3_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with SSSE3 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_SSSE3_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with SSSE3 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_SSE3_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with SSE3 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_SSE3_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with SSE3 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_SSE2_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits with SSE2 instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_SSE2_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits with SSE2 instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_X86_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: x86 64 bits build target")
#	elif (COBALT_ARCH & COBALT_ARCH_X86_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: x86 32 bits build target")

#	elif (COBALT_ARCH & COBALT_ARCH_NEON_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: ARM 64 bits with Neon instruction set build target")
#	elif (COBALT_ARCH & COBALT_ARCH_NEON_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: ARM 32 bits with Neon instruction set build target")

#	elif (COBALT_ARCH & COBALT_ARCH_ARM_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: ARM 64 bits build target")
#	elif (COBALT_ARCH & COBALT_ARCH_ARM_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: ARM 32 bits build target")

#	elif (COBALT_ARCH & COBALT_ARCH_MIPS_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: MIPS 64 bits build target")
#	elif (COBALT_ARCH & COBALT_ARCH_MIPS_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: MIPS 32 bits build target")

#	elif (COBALT_ARCH & COBALT_ARCH_PPC_BIT) && (COBALT_MODEL == COBALT_MODEL_64)
#		pragma message("COBALT: PowerPC 64 bits build target")
#	elif (COBALT_ARCH & COBALT_ARCH_PPC_BIT) && (COBALT_MODEL == COBALT_MODEL_32)
#		pragma message("COBALT: PowerPC 32 bits build target")
#	else
#		pragma message("COBALT: Unknown build target")
#	endif//COBALT_ARCH

	// Report platform name
#	if(COBALT_PLATFORM & COBALT_PLATFORM_QNXNTO)
#		pragma message("COBALT: QNX platform detected")
//#	elif(COBALT_PLATFORM & COBALT_PLATFORM_IOS)
//#		pragma message("COBALT: iOS platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_APPLE)
#		pragma message("COBALT: Apple platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_WINCE)
#		pragma message("COBALT: WinCE platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_WINDOWS)
#		pragma message("COBALT: Windows platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_CHROME_NACL)
#		pragma message("COBALT: Native Client detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_ANDROID)
#		pragma message("COBALT: Android platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_LINUX)
#		pragma message("COBALT: Linux platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_UNIX)
#		pragma message("COBALT: UNIX platform detected")
#	elif(COBALT_PLATFORM & COBALT_PLATFORM_UNKNOWN)
#		pragma message("COBALT: platform unknown")
#	else
#		pragma message("COBALT: platform not detected")
#	endif

	// Report whether only xyzw component are used
#	if defined COBALT_FORCE_XYZW_ONLY
#		pragma message("COBALT: COBALT_FORCE_XYZW_ONLY is defined. Only x, y, z and w component are available in vector type. This define disables swizzle operators and SIMD instruction sets.")
#	endif

	// Report swizzle operator support
#	if COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_OPERATOR
#		pragma message("COBALT: COBALT_FORCE_SWIZZLE is defined, swizzling operators enabled.")
#	elif COBALT_CONFIG_SWIZZLE == COBALT_SWIZZLE_FUNCTION
#		pragma message("COBALT: COBALT_FORCE_SWIZZLE is defined, swizzling functions enabled. Enable compiler C++ language extensions to enable swizzle operators.")
#	else
#		pragma message("COBALT: COBALT_FORCE_SWIZZLE is undefined. swizzling functions or operators are disabled.")
#	endif

	// Report .length() type
#	if COBALT_CONFIG_LENGTH_TYPE == COBALT_LENGTH_SIZE_T
#		pragma message("COBALT: COBALT_FORCE_SIZE_T_LENGTH is defined. .length() returns a cobalt::math::length_t, a typedef of std::size_t.")
#	else
#		pragma message("COBALT: COBALT_FORCE_SIZE_T_LENGTH is undefined. .length() returns a cobalt::math::length_t, a typedef of int following GLSL.")
#	endif

#	if COBALT_CONFIG_UNRESTRICTED_GENTYPE == COBALT_ENABLE
#		pragma message("COBALT: COBALT_FORCE_UNRESTRICTED_GENTYPE is defined. Removes GLSL restrictions on valid function genTypes.")
#	else
#		pragma message("COBALT: COBALT_FORCE_UNRESTRICTED_GENTYPE is undefined. Follows strictly GLSL on valid function genTypes.")
#	endif

#	if COBALT_SILENT_WARNINGS == COBALT_ENABLE
#		pragma message("COBALT: COBALT_FORCE_SILENT_WARNINGS is defined. Ignores C++ warnings from using C++ language extensions.")
#	else
#		pragma message("COBALT: COBALT_FORCE_SILENT_WARNINGS is undefined. Shows C++ warnings from using C++ language extensions.")
#	endif

#	ifdef COBALT_FORCE_SINGLE_ONLY
#		pragma message("COBALT: COBALT_FORCE_SINGLE_ONLY is defined. Using only single precision floating-point types.")
#	endif

#	if defined(COBALT_FORCE_ALIGNED_GENTYPES) && (COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_ENABLE)
#		undef COBALT_FORCE_ALIGNED_GENTYPES
#		pragma message("COBALT: COBALT_FORCE_ALIGNED_GENTYPES is defined, allowing aligned types. This prevents the use of C++ constexpr.")
#	elif defined(COBALT_FORCE_ALIGNED_GENTYPES) && (COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_DISABLE)
#		undef COBALT_FORCE_ALIGNED_GENTYPES
#		pragma message("COBALT: COBALT_FORCE_ALIGNED_GENTYPES is defined but is disabled. It requires C++11 and language extensions.")
#	endif

#	if defined(COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES)
#		if COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_DISABLE
#			undef COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES
#			pragma message("COBALT: COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES is defined but is disabled. It requires C++11 and language extensions.")
#		elif COBALT_CONFIG_ALIGNED_GENTYPES == COBALT_ENABLE
#			pragma message("COBALT: COBALT_FORCE_DEFAULT_ALIGNED_GENTYPES is defined. All gentypes (e.g. vec3) will be aligned and padded by default.")
#		endif
#	endif

#	if COBALT_CONFIG_CLIP_CONTROL & COBALT_CLIP_CONTROL_ZO_BIT
#		pragma message("COBALT: COBALT_FORCE_DEPTH_ZERO_TO_ONE is defined. Using zero to one depth clip space.")
#	else
#		pragma message("COBALT: COBALT_FORCE_DEPTH_ZERO_TO_ONE is undefined. Using negative one to one depth clip space.")
#	endif

#	if COBALT_CONFIG_CLIP_CONTROL & COBALT_CLIP_CONTROL_LH_BIT
#		pragma message("COBALT: COBALT_FORCE_LEFT_HANDED is defined. Using left handed coordinate system.")
#	else
#		pragma message("COBALT: COBALT_FORCE_LEFT_HANDED is undefined. Using right handed coordinate system.")
#	endif
#endif//COBALT_MESSAGES

#endif//COBALT_SETUP_INCLUDED
