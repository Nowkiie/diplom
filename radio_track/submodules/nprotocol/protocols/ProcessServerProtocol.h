#pragma once

#include <cstdint>
#include <vector>

namespace process_server_protocol
{
const char* const protocol_name = "process_server";
const int protocol_code = 35;
using task_id_t = uint64_t;
using ns_time_t = uint64_t;  // nanoseconds since epoch

#define PROCESS_MESSAGE(m)        \
    enum                          \
    {                             \
        message = m,              \
        protocol = protocol_code, \
    };

enum message_type
{
    task_msg,
    task_failed_msg,
    task_result_msg,
    thread_count_msg,
    task_count_msg,
};

// клиент -> сервер
struct task
{
    PROCESS_MESSAGE(message_type::task_msg)

    task_id_t task_id;
    uint64_t sample_rate;
    uint64_t freq;
    ns_time_t start_time;
    int vp{37};
    std::vector<float> samples;
};

// клиент <- сервер
struct task_failed
{
    PROCESS_MESSAGE(message_type::task_failed_msg)

    task_id_t task_id;
};

struct detected_signal
{
    int vp;
    float freq_shift;
};

// клиент <- сервер
struct task_result
{
    PROCESS_MESSAGE(message_type::task_result_msg)

    task_id_t task_id;
    std::vector<detected_signal> results;
};

// клиент <- сервер
struct thread_count
{
    PROCESS_MESSAGE(message_type::thread_count_msg)

    uint32_t thread_count;
};

// клиент <- сервер
struct task_count
{
    PROCESS_MESSAGE(message_type::task_count_msg)

    uint32_t task_count;
};

#undef PROCESS_MESSAGE

}  // namespace process_server_protocol
