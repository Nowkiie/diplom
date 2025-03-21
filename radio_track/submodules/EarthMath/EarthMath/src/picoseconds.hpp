#pragma once
#include <chrono>
#include <cstdint>

using picoseconds_t =
    std::chrono::duration<int64_t, std::ratio<1ll, 1000000000000ll>>;
