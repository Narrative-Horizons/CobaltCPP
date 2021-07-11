#pragma once

namespace cobalt
{
    template <class T>
    struct type_identity
    {
        using type = T;
    };

    template <typename T, T v>
    struct integral_constant
    {
        using value_type = T;
        using type = integral_constant<T, v>;
        static constexpr T value = v;

        inline constexpr operator value_type() const noexcept
        {
            return value;
        }

        inline constexpr value_type operator()() const noexcept
        {
            return value;
        }
    };

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    template <typename T1, typename T2>
    struct is_same : false_type
    {
    };

    template <typename T>
    struct is_same<T, T> : true_type
    {
    };

    template <typename T1, typename T2>
    constexpr bool is_same_v = is_same<T1, T2>::value;

    template <typename T>
    struct remove_reference
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_const
    {
        using type = T;
    };

    template <typename T>
    struct remove_const<const T>
    {
        using type = T;
    };

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

    template <typename T>
    struct remove_volatile
    {
        using type = T;
    };

    template <typename T>
    struct remove_volatile<volatile T>
    {
        using type = T;
    };

    template <typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template <typename T>
    struct remove_cv
    {
        using type = T;
    };

    template <typename T>
    struct remove_cv<const T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_cv<volatile T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_cv<const volatile T>
    {
        using type = T;
    };

    template <typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template< class T >
    struct is_void : is_same<void, typename remove_cv<T>::type> 
    {
    };

    template <typename T>
    struct is_lvalue_reference : false_type
    {
    };

    template <typename T>
    struct is_lvalue_reference<T&> : true_type
    {
    };

    namespace detail {
        template <class T>
        auto try_add_lvalue_reference(int) -> type_identity<T&>;
        template <class T>
        auto try_add_lvalue_reference(...) -> type_identity<T>;

        template <class T>
        auto try_add_rvalue_reference(int) -> type_identity<T&&>;
        template <class T>
        auto try_add_rvalue_reference(...) -> type_identity<T>;
    }

    template <class T>
    struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) {};

    template <class T>
    struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {};

    template <typename T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template<bool B, typename T = void>
    struct enable_if 
    {
    };

    template<typename T>
    struct enable_if<true, T>
    {
        using type = T; 
    };

    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template <bool B, typename T, typename F>
    struct conditional
    {
        using type = T;
    };

    template <typename T, typename F>
    struct conditional<false, T, F>
    {
        using type = F;
    };

    template <bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;

    template<typename...> struct conjunction : true_type
    {
    };

    template<typename B1> struct conjunction<B1> : B1
    {
    };

    template<typename B1, typename... Bn>
    struct conjunction<B1, Bn...> : conditional_t<bool(B1::value), conjunction<Bn...>, B1>
    {
    };

    template<typename... B>
    inline constexpr bool conjunction_v = conjunction<B...>::value;

    template<class From, class To>
    struct is_nothrow_convertible : std::conjunction<std::is_void<From>, std::is_void<To>> {};

    template<class T>
    typename add_rvalue_reference<T>::type declval() noexcept;

    namespace detail {
        template<class T>
        auto test_returnable(int) -> decltype(
            void(static_cast<T(*)()>(nullptr)), true_type{}
        );
        template<class>
        auto test_returnable(...) -> false_type;

        template<class From, class To>
        auto test_implicitly_convertible(int) -> decltype(
            void(cobalt::declval<void(&)(To)>()(cobalt::declval<From>())), true_type{}
        );
        template<class, class>
        auto test_implicitly_convertible(...) -> false_type;
    }

    template<class From, class To>
    struct is_convertible : integral_constant<bool,
        (decltype(detail::test_returnable<To>(0))::value&&
            decltype(detail::test_implicitly_convertible<From, To>(0))::value) ||
        (is_void<From>::value && is_void<To>::value)> 
    {
    };
}