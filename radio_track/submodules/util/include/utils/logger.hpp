#pragma once

// (c) Copyright Dmitriy Shikhov 2021

#include <cstdint>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <sstream>

#ifdef UTILS_LOGGER_ENABLE_FUNCTION_NAME
#    include <boost/current_function.hpp>
#    define UTILS_LOGGER_FUNCTION_NAME BOOST_CURRENT_FUNCTION
#else
#    define UTILS_LOGGER_FUNCTION_NAME "(?)"
#endif

#define UTILS_LOG(PATH, ...) utils::logging(PATH, __VA_ARGS__)
#define UTILS_LOGF(PATH, ...) \
    UTILS_LOG(PATH, UTILS_LOGGER_FUNCTION_NAME ": ", __VA_ARGS__)

namespace utils
{
namespace logger::detail
{
template <typename T>
auto format(T value)
{
    return value;
}

template <typename T>
auto format(T* value)
    -> std::enable_if_t<!std::is_same_v<std::decay_t<T>, char>, std::string>
{
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T*) * 2) << std::hex
           << reinterpret_cast<std::intptr_t>(value);
    return stream.str();
}

}  // namespace logger::detail

template <typename... Ts>
void logging(std::filesystem::path path, Ts&&... args)
{
    create_directories(path.parent_path());

    std::ofstream stream{path, std::ios::app};
    (stream << ... << logger::detail::format(args)) << std::endl;
}

}  // namespace utils
