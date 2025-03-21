#pragma once

// (c) Copyright Dmitriy Shikhov 2021

#include <memory>
#include <utils/propagate_const.hpp>

namespace utils
{
//
// unique
//

template <typename Impl>
using unique_impl_ptr = utils::propagate_const<std::unique_ptr<Impl>>;

template <typename Impl, typename... Args>
auto make_unique_impl(Args&&... args)
{
    return std::make_unique<Impl>(std::forward<Args>(args)...);
}

//
// shared
//

template <typename Impl>
using shared_impl_ptr = utils::propagate_const<std::shared_ptr<Impl>>;

template <typename Impl, typename... Args>
auto make_shared_impl(Args&&... args)
{
    return std::make_shared<Impl>(std::forward<Args>(args)...);
}

}  // namespace utils
