#pragma once

// (c) Copyright Dmitriy Shikhov 2024

namespace utils
{
class interface
{
public:
    interface() = default;
    virtual ~interface() = default;

    interface(const interface&) = default;
    interface& operator=(const interface&) = default;
    interface(interface&&) = default;
    interface& operator=(interface&&) = default;
};

}  // namespace utils
