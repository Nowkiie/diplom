#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace nc
{
using port_t = uint16_t;
using address_t = uint32_t;
using message_type_t = uint32_t;
using point_id_t = uint64_t;

using queue_buffer_t = std::shared_ptr<std::vector<char>>;
}  // namespace nc
