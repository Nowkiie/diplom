#pragma once

// (c) Copyright Andrei Bakulin 2022

#include <string>
#include <map>
#include <optional>
#include <vector>

namespace iri_bindings_protocol
{
// Протокол взаимодействия c привязками ИРИ

const char* const protocol_name = "IriBindings";
const int protocol_code = 46;

#define IRI_BINDINGS_PROTOCOL_MESSAGE(MSG) \
    enum                                   \
    {                                      \
        message = message_type::MSG,       \
        protocol = protocol_code,          \
    };

enum message_type
{
    event_changed_msg,
    event_removed_msg,
    command_write_msg,
    command_remove_msg,
    subscription_msg,
    handshake_msg
};

using id_t = int64_t;

struct binding
{
    std::map<std::string, std::string> tags;  // тэги
    std::optional<int> priority;  // приоритет (чем меньше, тем выше)
    int64_t date;        // дата (секунд с начала эпохи)
    std::string source;  // имя источника
    std::map<std::string, std::string> object;  // данные объекта
    std::string author;                         // автор
    id_t id;  // идентификатор (при добавлении новый привязки заполняется 0)
};

struct priority
{
    int priority_value;             // приоритет
    std::vector<std::string> tags;  // тэги
};

// Событие чтения
// Отправляется сервером подписанным на сервер клиентам
struct event_changed
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(event_changed_msg)

    std::vector<binding> bindings;  // массив привязок
};

// Событие удаления
// Отправляется сервером подписанным клиентам при удалении привязки
struct event_removed
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(event_removed_msg)

    std::vector<id_t> ids;  // массив иднетификаторов
};

// Команда записи
// Отправляется клиентами серверу, на который клиент подписан
struct command_write
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(command_write_msg)

    std::vector<binding>
        bindings;  // массив привязок (только измененные записи)
};

// Команда удаления
// Отправляется клиентом на сервер для удаления привязки
struct command_remove
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(command_remove_msg)

    std::vector<id_t> ids;  // массив привязок для удаления
};

// Handshake
// Отправляется сервером клиенту при подключении клиента
struct handshake
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(handshake_msg)

    std::string name;
    std::vector<priority>
        tags2priority;  // массив соответствия тэгов их приоритету
};

// Подписка
// Отправялется клиентом серверу для возможности получения привязок с указанного сервера
struct subscription
{
    IRI_BINDINGS_PROTOCOL_MESSAGE(subscription_msg)
};

#undef IRI_BINDINGS_PROTOCOL_MESSAGE

}  // namespace iri_bindings_protocol
