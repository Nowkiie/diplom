#pragma once
#include <cstdint>
#include <list>
#include <string>
#include <vector>

namespace URS_mix_protocol
{
const char* const protocol_name = "URS_mix_protocol";
const uint16_t protocol_code = 23;

struct wav_load_info
{
    std::string path;
    bool is_used;
    float freq_signal;
    float freq_BOI;
    float gain;
    int64_t time_start;
    int64_t time_interval;
    int64_t exec_count;
    float angle_azimut;
    float angle_elevation;
    uint64_t crc;
    uint64_t size;
};

enum message_type
{
    msg_list = 1,
    msg_file_query,
    msg_file_answer,
    msg_hello
};

struct hello_query
{
    enum
    {
        message = msg_hello,
        protocol = protocol_code,
    };
    uint32_t id; //ID URS
    std::string name;
};

struct mix_list
{
    enum
    {
        message = msg_list,
        protocol = protocol_code,
    };
    std::list<wav_load_info> wav_list;
};

struct file_query
{
    enum
    {
        message = msg_file_query,
        protocol = protocol_code,
    };
    uint64_t size;
    uint64_t crc;
};

struct file_answer
{
    enum
    {
        message = msg_file_answer,
        protocol = protocol_code,
    };
    uint64_t crc;
    uint64_t pos;
    std::vector<char> data;
};
};  // namespace URS_mix_protocol
