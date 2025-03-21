#pragma once

// (c) Copyright Krasheninnikov 2022

#include <string>
#include <map>
#include <set>
#include <vector>
#include <optional>

namespace demodulation_keys_protocol
{
// Протокол ключей демодуляции (DMR,TETRA и т.д.)

const char* const protocol_name = "demodulation_keys_protocol";
const int protocol_code = 47;

#define DEMODULATION_KEYS_PROTOCOL_MESSAGE(MSG) \
    enum                                        \
    {                                           \
        message = message_type::MSG,            \
        protocol = protocol_code,               \
    };

enum message_type
{
    data_changed_msg,
    insert_msg,
    update_msg,
    remove_msg,
    data_removed_msg
};
enum class key_type_t : int
{
    dmr_mask,
    dmr_key,
    ale3g_bw5,
    harris_citadel,
    harris_aes,
};
using id_t = uint64_t;
using ns_time_t = int64_t;
struct key_t
{
    key_type_t type;
    std::string key;
    std::optional<int64_t> freq;
    ns_time_t last_detect_time;
    bool enabled;
    std::string comment;
};

// сервер->клиент
struct data_changed
{
    DEMODULATION_KEYS_PROTOCOL_MESSAGE(data_changed_msg)
    std::map<id_t, key_t> keys;
};

// сервер->клиент
struct data_removed
{
    DEMODULATION_KEYS_PROTOCOL_MESSAGE(data_removed_msg)
    std::set<id_t> keys;
};

// клиент->сервер
struct insert
{
    DEMODULATION_KEYS_PROTOCOL_MESSAGE(insert_msg)

    std::vector<key_t> keys;
};
// клиент->сервер
struct update
{
    DEMODULATION_KEYS_PROTOCOL_MESSAGE(update_msg)

    std::map<id_t, key_t> keys;
};

// клиент->сервер
struct remove
{
    DEMODULATION_KEYS_PROTOCOL_MESSAGE(remove_msg)

    std::set<id_t> keys;
};

#undef DEMODULATION_KEYS_PROTOCOL_MESSAGE

}  // namespace demodulation_keys_protocol
