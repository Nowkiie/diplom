#pragma once

// (c) Copyright Dmitriy Shikhov 2015, 2016

namespace utils
{
template <typename ToPtr, typename From>
ToPtr pointer_cast(const From* ptr)
{
    return static_cast<ToPtr>(static_cast<const void*>(ptr));
}

template <typename ToPtr, typename From>
ToPtr pointer_cast(From* ptr)
{
    return static_cast<ToPtr>(static_cast<void*>(ptr));
}

}  // namespace utils
