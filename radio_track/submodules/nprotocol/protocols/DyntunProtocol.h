#pragma once
#include <cstdint>
#include <vector>

namespace dyntun_protocol
{
const char* const protocol_name = "dyntun_protocol";
const unsigned short protocol_code = 42;

enum dyntun_protocol_protocol_codes
{
    current_settings_msg,
    update_settings_msg,
    peer_state_msg,
    route_table_msg,

};

using proto_address_t = uint32_t;
using proto_point_t = uint16_t;
using proto_ms_time_t = int64_t;

static const uint8_t metric_unreachable = 255;

struct peer_state_item
{
    proto_point_t point;
    proto_address_t address;
    proto_ms_time_t connect_time;
    uint64_t tx_bytes;
    uint64_t rx_bytes;
    uint64_t route_updates;
    uint8_t metric;
    bool connected;
    uint32_t control_dropped;
    uint32_t control_sended;
    uint32_t current_rtt;
};

struct peer_settings
{
    proto_address_t address;
    uint8_t metric;
};

struct current_settings
{
    enum
    {
        message = current_settings_msg,
        protocol = protocol_code,
    };
    uint16_t local_point;
    std::vector<peer_settings> peers;
};

struct update_settings
{
    enum
    {
        message = update_settings_msg,
        protocol = protocol_code,
    };
    uint16_t local_point;
    std::vector<peer_settings> peers;
};

struct peer_state
{
    enum
    {
        message = peer_state_msg,
        protocol = protocol_code,
    };
    std::vector<peer_state_item> items;
};

struct route_table_item
{
    proto_point_t router;
    proto_point_t peer;
    uint8_t metric;
    uint16_t age;
    uint8_t sequence;
};

struct route_table
{
    enum
    {
        message = route_table_msg,
        protocol = protocol_code,
    };
    std::vector<route_table_item> items;
};


}  // namespace dyntun_protocol
