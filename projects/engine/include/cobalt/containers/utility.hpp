#pragma once

#include "typetraits.hpp"

namespace cobalt
{
    template <class T, class U,
        class = typename enable_if<
        (is_lvalue_reference<T>::value ?
            is_lvalue_reference<U>::value :
            true) &&
        is_convertible<typename remove_reference<U>::type*,
        typename remove_reference<T>::type*>::value
    >::type>
        inline
        T&&
        forward(U&& u)
    {
        return static_cast<T&&>(u);
    }

    template <typename Type>
    inline constexpr remove_reference_t<Type>&& move(Type&& t) noexcept
    {
        return static_cast<remove_reference_t<Type>&&>(t);
    }
}