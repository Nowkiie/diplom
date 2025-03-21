#pragma once
#include "module_functional.hpp"

namespace earth_math
{
template <size_t ModDegree>
class degree_module : public degree<module_functional<ModDegree>>
{
public:
    static degree_module from_seconds(int64_t seconds);
    static degree_module from_degree(double degree_value);

private:
    degree_module(const degree<module_functional<ModDegree>>& deg)
        : degree<module_functional<ModDegree>>(deg)
    {
    }
    degree_module(degree<module_functional<ModDegree>>&& deg) noexcept
        : degree<module_functional<ModDegree>>(deg)
    {
    }
    friend std::ostream& operator<<(std::ostream& stream, const degree_module<ModDegree>& deg)
    {
        stream << deg.to_string();
        return stream;
    }
};

template <size_t ModDegree>
degree_module<ModDegree> degree_module<ModDegree>::from_seconds(int64_t seconds)
{
    auto ms = seconds * milli_in_second;
    ms = module_functional<ModDegree>::normalize(ms);
    return degree<module_functional<ModDegree>>::from_milliseconds(ms);
}

template <size_t ModDegree>
degree_module<ModDegree> degree_module<ModDegree>::from_degree(
    double degree_value)
{
    int32_t sign;
    if (degree_value < -eps)
        sign = -1;
    else
        sign = 1;
    degree_value = fabs(degree_value);
    int64_t ms =
        sign * (int64_t((degree_value + eps) / one_millisecond_ + eps));
    ms = module_functional<ModDegree>::normalize(ms);
    return degree<module_functional<ModDegree>>::from_milliseconds(ms);
}
}  // namespace earth_math
