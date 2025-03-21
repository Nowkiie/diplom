#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace dmr_crack_protocol
{
const char* const protocol_name = "dmr_crack_protocol";
const int protocol_code = 48;

enum message_types
{
    msg_start,
    msg_progress,
    msg_error,
    msg_success,
    msg_abort,
    msg_queue,
};

struct dmr_frame
{
    uint8_t iv[4];
    uint8_t data[18][7];
};

enum class crypo_mode
{
    arc4,
    aes128,
    aes256,
};
enum class vocoder_type
{
    ambe,
    selp,
    nvoc,
    comm,
};

// клиент -> сервер
// запуск подбора ключа
struct command_start
{
    enum
    {
        protocol = protocol_code,
        message = msg_start
    };
    uint64_t task_id;
    std::vector<dmr_frame> frames;
    crypo_mode crypto;
    vocoder_type vocoder;
    int work_frame; // -1 для всех фреймов

};
// сервер -> клиент
// статус обработки
struct message_progress
{
    enum
    {
        protocol = protocol_code,
        message = msg_progress
    };
    uint64_t task_id;
    uint32_t key_processed;  // количество обработанных ключей
    uint32_t key_total;  // общее количество ключей
};
// сервер -> клиент
// ошибка обработки
struct message_error
{
    enum
    {
        protocol = protocol_code,
        message = msg_error
    };
    uint64_t task_id;
    std::string error_text;  // сообщение об ошибке
};
// сервер -> клиент
// успешный статус обработки
struct message_success
{
    enum
    {
        protocol = protocol_code,
        message = msg_success
    };
    uint64_t task_id;
    std::string key;  // найденный ключ
};
// клиент -> сервер
// отмена обработки
struct command_abort
{
    enum
    {
        protocol = protocol_code,
        message = msg_abort
    };
    uint64_t task_id;
};
// сервер -> клиент
// размер очереди
struct queue_length
{
    enum
    {
        protocol = protocol_code,
        message = msg_queue
    };
    uint64_t queue_length;
};

}  // namespace dmr_crack_protocol
