#pragma once

#include "shared/PelengEnums.h"

#include <vector>

namespace rpp_channel_state {

const int protocol_code = 52;
const char* const protocol_name = "rpp_channel_state";

struct rpp_unique_description  // уникальное описание РПП
{
    uint32_t id;                            // идентификатор РПП
    std::string name_ui;                    // имя РПП
    peleng_enums::rpp_formation formation;  // исполнение РПП
};

struct rpp_sprut_description {
    std::string ip;
    uint32_t port;
};

struct rpp_description {
    rpp_unique_description description;
    rpp_sprut_description sprut_description;
};

enum rpp_channel_status
{
    active,
    inactive,
    warning,
};

struct rpp_channel_status_description {
    rpp_channel_status status;
    std::string text;
};

struct rpp_channel_description {
    uint32_t channel_id;
    uint32_t src_rpp_id;
    uint32_t dst_rpp_id;
    rpp_channel_status_description status_description;
};

enum protocol_codes
{
    rpp_channel_declaration_update_msg,
    rpp_channel_update_msg,
};

// список рпп и каналов между ними
// сервер -> клиент
struct rpp_channel_declaration_update {
    enum
    {
        message = rpp_channel_declaration_update_msg,
        protocol = protocol_code,
    };

    uint32_t local_rpp_id;
    std::vector<rpp_description> rpp_descriptions;
    std::vector<rpp_channel_description> rpp_channel_descriptions;
};

// обновление статуса канала с рпп
// сервер -> клиент
struct rpp_channel_update {
    enum
    {
        message = rpp_channel_update_msg,
        protocol = protocol_code,
    };

    uint32_t channel_id;
    rpp_channel_status_description status_description;
};

}  // namespace rpp_channel_state
