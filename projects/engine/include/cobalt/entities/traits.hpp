#pragma once

#include <cstdint>

namespace cobalt
{
    namespace detail
    {
        struct traits_impl
        {
            static std::uint32_t identifier;
        };
    }

    template <typename T>
    struct traits
    {
        static auto identifier()
        {
            static auto id = detail::traits_impl::identifier++;
            return id;
        }

        static constexpr auto poolSize()
        {
            return 4096u;
        }
    };
}