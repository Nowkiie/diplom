#pragma once

// (c) Copyright Dmitriy Shikhov 2020

#define UTILS_GENERATE_HAS_MEMBER(member)                                 \
                                                                          \
    namespace detail::generated_by_macros                                 \
    {                                                                     \
    template <typename T>                                                 \
    class has_##member##_impl                                             \
    {                                                                     \
    private:                                                              \
        using no_t = bool;                                                \
        using yes_t = no_t[2];                                            \
                                                                          \
        struct fallback                                                   \
        {                                                                 \
            int member;                                                   \
        };                                                                \
        struct derived                                                    \
            : T                                                           \
            , fallback                                                    \
        {                                                                 \
        };                                                                \
                                                                          \
        template <typename U>                                             \
        static no_t& test(decltype(U::member)*);                          \
        template <typename U>                                             \
        static yes_t& test(U*);                                           \
                                                                          \
    public:                                                               \
        static constexpr bool value =                                     \
            sizeof(test<derived>(nullptr)) == sizeof(yes_t);              \
    };                                                                    \
    }                                                                     \
                                                                          \
    template <typename T>                                                 \
    struct has_##member                                                   \
        : public std::bool_constant<                                      \
              detail::generated_by_macros::has_##member##_impl<T>::value> \
    {                                                                     \
    };                                                                    \
                                                                          \
    template <typename T>                                                 \
    inline constexpr bool has_##member##_v = has_##member<T>::value;      \
    /**/
