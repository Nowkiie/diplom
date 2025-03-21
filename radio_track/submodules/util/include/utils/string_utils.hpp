#pragma once

// (c) Copyright Dmitriy Shikhov 2023

#include <cctype>
#include <algorithm>
#include <string>

namespace utils
{
namespace detail
{
static bool not_isspace(char c)
{
    return !std::isspace(c);
}
}  // namespace detail

inline std::string& ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), detail::not_isspace));
    return s;
}

inline std::string& rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), detail::not_isspace).base(),
            s.end());
    return s;
}

inline std::string& trim(std::string& s)
{
    return ltrim(rtrim(s));
}

}  // namespace utils
