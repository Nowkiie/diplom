#pragma once

#include "shared/PelengEnums.h"

#include <string>
#include <vector>

namespace data_transfer_protocol {

const char* const protocol_name = "data_transfer_protocol_2";
const unsigned short protocol_code = 34;

using id_t = uint64_t; // идентификатор сообщения

enum data_transfer_protocol_codes {
    register_message_msg = 0,
    register_message_answer_msg,

    data_msg,

    commit_msg,
    error_msg,
};

// уникальное описание
struct source_description {
    std::string name_ui;    // имя
};

// пакеты обмена клиент<->сервер

//------------------------------------
// регистрация
// клиент <- сервер
//  Формируется при установке соединения
//------------------------------------
struct register_message {
    enum {
        message = register_message_msg,
        protocol = protocol_code,
    };

    source_description description; // описание источника
};

//------------------------------------
// регистрация клиента
// клиент -> сервер
//  Формируется при установке соединения
//------------------------------------
struct register_message_answer {
    enum {
        message = register_message_answer_msg,
        protocol = protocol_code,
    };

    source_description description; // описание источника
};

//------------------------------------
// отправка данных
// клиент <- сервер
//------------------------------------
struct data_message {
    enum {
        message = data_msg,
        protocol = protocol_code,
    };

    id_t id; // идентификатор сообщения

    std::string data_name;  // имя файла
    std::vector<char> data; // содержимое файла
};

//------------------------------------
// результат: отправка завершена успешно
// клиент -> сервер
//------------------------------------
struct commit_message {
    enum {
        message = commit_msg,
        protocol = protocol_code,
    };

    id_t id; // идентификатор сообщения
};

//------------------------------------
// результат: ошибка отправки
// клиент -> сервер
//------------------------------------
struct error_message {
    enum {
        message = error_msg,
        protocol = protocol_code,
    };

    id_t id; // идентификатор сообщения

    int32_t code;                   // код ошибки
    std::string error_description;  // описание ошибки
};

} // namespace DataTransferProtocol
