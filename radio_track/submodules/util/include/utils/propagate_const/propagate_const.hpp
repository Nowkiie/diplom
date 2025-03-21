// clang-format off
// -*- C++ -*-
//===------------------------ propagate_const -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#pragma once

// (c) Copyright Dmitriy Shikhov 2016
// (adaptation to Microsoft C++ Compiler)

#ifndef INCLUDE_GUARD_7BCD0361_E97A_4481_BA74_D9BFFDC21773
#define INCLUDE_GUARD_7BCD0361_E97A_4481_BA74_D9BFFDC21773

#include <type_traits>
#include <utility>
#include <functional>

namespace utils {

template <class T>
class propagate_const;

template <class U>
inline const U& get_underlying(const propagate_const<U>& u) noexcept;

template <class U>
inline U& get_underlying(propagate_const<U>& u) noexcept;

template <class T>
class propagate_const
{
public:
    typedef std::remove_reference_t<decltype(*std::declval<T&>())> element_type;

    static_assert(!std::is_array<T>::value,
        "Instantiation of propagate_const with an array type "
        "is ill-formed.");
    static_assert(!std::is_reference<T>::value,
        "Instantiation of propagate_const with a reference type "
        "is ill-formed.");
    static_assert(!(std::is_pointer<T>::value &&
        std::is_function<typename std::remove_pointer<T>::type>::value),
        "Instantiation of propagate_const with a function-pointer type "
        "is ill-formed.");
    static_assert(!(std::is_pointer<T>::value &&
        std::is_same<typename std::remove_cv<
            typename std::remove_pointer<T>::type>::type, void>::value),
        "Instantiation of propagate_const with a pointer to "
        "(possibly cv-qualified) void is ill-formed.");

private:
    template <class U>
    static element_type* get_pointer_(U* u)
    {
        return u;
    }

    template <class U>
    static element_type* get_pointer_(U& u)
    {
        return get_pointer_(u.get());
    }

    template <class U>
    static const element_type* get_pointer_(const U* u)
    {
        return u;
    }

    template <class U>
    static const element_type* get_pointer_(const U& u)
    {
        return get_pointer_(u.get());
    }

    template <class U>
    struct is_propagate_const_ : std::false_type
    {
    };

    template <class U>
    struct is_propagate_const_<propagate_const<U>> : std::true_type
    {
    };

    T p_;

public:

    template <class U>
    friend const U& get_underlying(const propagate_const<U>& u) noexcept;

    template <class U>
    friend U& get_underlying(propagate_const<U>& u) noexcept;

    propagate_const() = default;

    propagate_const(const propagate_const&) = delete;

    propagate_const(propagate_const&&) = default;

    template <class U, std::enable_if_t<!std::is_convertible<U, T>::value &&
        std::is_constructible<T, U&&>::value, bool> = true>
    explicit propagate_const(propagate_const<U>&& u)
        : p_(std::move(get_underlying(u)))
    {
    }

    template <class U, std::enable_if_t<std::is_convertible<U&&, T>::value &&
        std::is_constructible<T, U&&>::value, bool> = false>
    propagate_const(propagate_const<U>&& u)
        : p_(std::move(get_underlying(u)))
    {
    }

    template <class U, std::enable_if_t<!std::is_convertible<U&&, T>::value &&
        std::is_constructible<T, U&&>::value &&
        !is_propagate_const_<std::decay_t<U>>::value, bool> = true>
    explicit  propagate_const(U&& u)
        : p_(std::forward<U>(u))
    {
    }

    template <class U, std::enable_if_t<std::is_convertible<U&&, T>::value &&
        std::is_constructible<T, U&&>::value &&
        !is_propagate_const_<std::decay_t<U>>::value, bool> = false>
    propagate_const(U&& u)
        : p_(std::forward<U>(u))
    {
    }

    propagate_const& operator=(const propagate_const&) = delete;

    propagate_const& operator=(propagate_const&&) = default;

    template <class U>
    propagate_const& operator=(propagate_const<U>&& u)
    {
        p_ = std::move(get_underlying(u));
        return *this;
    }

    template <class U, class V = std::enable_if_t<
        !is_propagate_const_<std::decay_t<U>>::value>>
    propagate_const& operator=(U&& u)
    {
        p_ = std::forward<U>(u);
        return *this;
    }

    const element_type* get() const
    {
        return get_pointer_(p_);
    }

    element_type* get()
    {
        return get_pointer_(p_);
    }

    explicit operator bool() const
    {
        return get() != nullptr;
    }

    const element_type* operator->() const
    {
        return get();
    }

    template <class T_ = T, class U = std::enable_if_t<std::is_convertible<
        const T_, const element_type *>::value>>
    operator const element_type *() const {
        return get();
    }

    const element_type& operator*() const
    {
        return *get();
    }

    element_type* operator->()
    {
        return get();
    }

    template <class T_ = T, class U = std::enable_if_t<
        std::is_convertible<T_, element_type *>::value>>
    operator element_type *() {
        return get();
    }

    element_type& operator*()
    {
        return *get();
    }

    void swap(propagate_const& p)
    {
        using std::swap;
        swap(p_, p.p_);
    }
};


template <class T>
bool operator==(const propagate_const<T>& p, std::nullptr_t)
{
    return get_underlying(p) == nullptr;
}

template <class T>
bool operator==(std::nullptr_t, const propagate_const<T>& p)
{
    return nullptr == get_underlying(p);
}

template <class T>
bool operator!=(const propagate_const<T>& p, std::nullptr_t)
{
    return get_underlying(p) != nullptr;
}

template <class T>
bool operator!=(std::nullptr_t, const propagate_const<T>& p)
{
    return nullptr != get_underlying(p);
}

template <class T, class U>
bool operator==(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) == get_underlying(u);
}

template <class T, class U>
bool operator!=(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) != get_underlying(u);
}

template <class T, class U>
bool operator<(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) < get_underlying(u);
}

template <class T, class U>
bool operator>(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) > get_underlying(u);
}

template <class T, class U>
bool operator<=(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) <= get_underlying(u);
}

template <class T, class U>
bool operator>=(const propagate_const<T>& p, const propagate_const<U>& u)
{
    return get_underlying(p) >= get_underlying(u);
}

template <class T, class U>
bool operator==(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) == u;
}

template <class T, class U>
bool operator!=(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) != u;
}

template <class T, class U>
bool operator<(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) < u;
}

template <class T, class U>
bool operator>(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) > u;
}

template <class T, class U>
bool operator<=(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) <= u;
}

template <class T, class U>
bool operator>=(const propagate_const<T>& p, const U& u)
{
    return get_underlying(p) >= u;
}

template <class T, class U>
bool operator==(const T& p, const propagate_const<U>& u)
{
    return p == get_underlying(u);
}

template <class T, class U>
bool operator!=(const T& p, const propagate_const<U>& u)
{
    return p != get_underlying(u);
}

template <class T, class U>
bool operator<(const T& p, const propagate_const<U>& u)
{
    return p < get_underlying(u);
}

template <class T, class U>
bool operator>(const T& p, const propagate_const<U>& u)
{
    return p > get_underlying(u);
}

template <class T, class U>
bool operator<=(const T& p, const propagate_const<U>& u)
{
    return p <= get_underlying(u);
}

template <class T, class U>
bool operator>=(const T& p, const propagate_const<U>& u)
{
    return p >= get_underlying(u);
}

template <class T>
void swap(propagate_const<T>& p1, propagate_const<T>& p2)
{
    using std::swap;
    swap(get_underlying(p1), get_underlying(p2));
}

template <class T>
const T& get_underlying(const propagate_const<T>& p) noexcept
{
    return p.p_;
}

template <class T>
T& get_underlying(propagate_const<T>& p) noexcept
{
    return p.p_;
}

} // namespace utils

#endif
// INCLUDE_GUARD_7BCD0361_E97A_4481_BA74_D9BFFDC21773
// clang-format on
