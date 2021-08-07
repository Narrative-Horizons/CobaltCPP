#pragma once

#include <type_traits>

#define COBALT_NO_COPY(cls)                                                    \
    cls(const cls&) = delete;                                                  \
    cls& operator=(const cls&) = delete;

#define COBALT_NO_MOVE(cls)                                                    \
    cls(cls&&) noexcept = delete;                                              \
    cls& operator=(cls&&) noexcept = delete;

#define COBALT_NO_COPY_MOVE(cls)                                               \
    COBALT_NO_COPY(cls)                                                        \
    COBALT_NO_MOVE(cls)

#define COBALT_NO_DISCARD [[nodiscard]]

template <typename EnumType>
using _UNDERLYING_ENUM_T = typename std::underlying_type<EnumType>::type;

#    define COBALT_DEFINE_FLAG_ENUM_OPERATORS(ENUMTYPE)                                                                                                                                                                      \
        extern "C++"                                                                                                                                                                                                  \
        {                                                                                                                                                                                                             \
            inline ENUMTYPE&          operator|=(ENUMTYPE& a, ENUMTYPE b) { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) |= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline ENUMTYPE&          operator&=(ENUMTYPE& a, ENUMTYPE b) { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) &= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline ENUMTYPE&          operator^=(ENUMTYPE& a, ENUMTYPE b) { return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<_UNDERLYING_ENUM_T<ENUMTYPE>&>(a) ^= static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); } \
            inline constexpr ENUMTYPE operator|(ENUMTYPE a, ENUMTYPE b) { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) | static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator&(ENUMTYPE a, ENUMTYPE b) { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) & static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator^(ENUMTYPE a, ENUMTYPE b) { return static_cast<ENUMTYPE>(static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a) ^ static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(b)); }                \
            inline constexpr ENUMTYPE operator~(ENUMTYPE a) { return static_cast<ENUMTYPE>(~static_cast<_UNDERLYING_ENUM_T<ENUMTYPE>>(a)); }                                                                          \
        }

#define COBALT_SCOPE_GUARD(content) { content }

#define ENTRYPOINT(application) \
    int main(int argc, char** argv) \
    { \
        static_assert(std::is_base_of_v<cobalt::BaseApplication, application>); \
        cobalt::UniquePtr<application> app = cobalt::MakeUnique<application>(); \
        cobalt::Engine<application>::initialize(cobalt::move(app)); \
        cobalt::Engine<application>::instance().run(); \
        cobalt::Engine<application>::destruct(); \
        return 0; \
    }