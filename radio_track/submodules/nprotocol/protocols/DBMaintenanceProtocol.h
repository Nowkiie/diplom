#pragma once

#include <vector>
#include <string>
#include <set>
#include <optional>

namespace db_maintenance_protocol {

const unsigned short protocol_code = 50;
const char* const protocol_name = "db_maintenance_protocol";

using id_t = uint32_t;
using ns_time_t = uint64_t;

#define PROTOCOL_MESSAGE(m)       \
    enum                          \
    {                             \
        message = m,              \
        protocol = protocol_code, \
    };

enum db_maintenance_protocol_codes
{
    client_initialization_msg,

    common_task_state_changed_msg,
    common_task_append_output_msg,
    manual_task_append_msg,
    manual_task_state_changed_msg,
    manual_task_append_output_msg,

    update_backup_config_msg,

    run_common_task_query_msg,
    fix_common_task_query_msg,
    check_all_common_tasks_query_msg,
    fix_all_common_tasks_query_msg,
    create_backup_query_msg,
    restore_backup_query_msg,
    update_database_query_msg,
    create_and_update_database_query_msg,
    database_version_query_msg,
    online_database_query_msg,
    shutdown_database_query_msg,
    optimize_database_space_query_msg,
    optimize_database_indexes_query_msg,
    backup_and_restore_database_query_msg,
    validate_database_query_msg,

    database_version_answer_msg,
};

struct backup_file {
    std::string name;
    uint64_t size;
    ns_time_t modified_date_time;
};

struct backup_config {
    std::string name;
    std::vector<backup_file> files;
};

struct manual_config {
    std::string database;
    std::string create_script_path;
    std::string update_script_path;
    std::string migrate_script_path;

    std::vector<backup_config> backup_configs;
};

enum class common_task_type : int32_t
{
    status = 0,
    check,
};

enum class common_task_state : int32_t
{
    undefined = 0,
    scheduled,
    running,
    success,
    error,
};

enum class manual_task_state : int32_t
{
    undefined = 0,
    running,
    success,
    error,
};

enum class output_type : int32_t
{
    text = 0,
    error,
};

enum class dbms_type : int32_t
{
    firebird = 0,
    postgres,
};

enum class manual_operation : int32_t
{
    make_online = 0,
    make_shutdown,
    optimize_space,
    optimize_index,
    backup_and_restore,
    validate,
};

struct output_item {
    output_type type;
    ns_time_t date_time;
    std::string text;
};

struct timer_item {
    std::set<int32_t> days_of_week;
    std::optional<ns_time_t> time_start;  // время от начала дня
    uint32_t repeat_interval_seconds;
};

struct common_task {
    id_t id;
    common_task_type type;
    common_task_state state;
    std::string name;
    std::string target;
    std::string description;
    timer_item timer;
};

struct manual_task {
    id_t id;
    manual_task_state state;
    std::string name;
    ns_time_t date_time_start;
    std::string target;
};

struct common_task_with_output {
    common_task task;
    std::vector<output_item> output;
};

struct manual_task_with_output {
    manual_task task;
    std::vector<output_item> output;
};

// инициализация клиента
// сервер -> клиент
struct client_initialization {
    PROTOCOL_MESSAGE(client_initialization_msg);

    dbms_type type;
    std::vector<manual_operation> available_manual_operations;
    std::vector<std::string> loadErrors;

    std::vector<common_task_with_output> common_tasks;
    std::vector<manual_task_with_output> manual_tasks;
    std::vector<manual_config> manual_configs;
};

// изменение состояния общей задачи
// сервер -> клиент
struct common_task_state_changed {
    PROTOCOL_MESSAGE(common_task_state_changed_msg);

    id_t id;
    common_task_state new_state;
    std::string new_description;
};

// добавление потока вывода общей задачи
// сервер -> клиент
struct common_task_append_output {
    PROTOCOL_MESSAGE(common_task_append_output_msg);

    id_t id;
    output_item output;
};

// добавление ручной задачи
// сервер -> клиент
struct manual_task_append {
    PROTOCOL_MESSAGE(manual_task_append_msg);

    manual_task task;
};

// изменение состояния ручной задачи
// сервер -> клиент
struct manual_task_state_changed {
    PROTOCOL_MESSAGE(manual_task_state_changed_msg);

    id_t id;
    manual_task_state new_state;
};

// добавление потока вывода ручной задачи
// сервер -> клиент
struct manual_task_append_output {
    PROTOCOL_MESSAGE(manual_task_append_output_msg);

    id_t id;
    output_item output;
};

// обновление списка файлов бекапов, для конкретной конфигурации
// сервер -> клиент
struct update_backup_config {
    PROTOCOL_MESSAGE(update_backup_config_msg);

    int manual_config_index;
    int manual_backup_config_index;
    std::vector<backup_file> backup_files;
};

// запрос на выполнение общей задачи
// сервер <- клиент
struct run_common_task_query {
    PROTOCOL_MESSAGE(run_common_task_query_msg);

    id_t id;
};

// запрос на исправление общей задачи
// сервер <- клиент
struct fix_common_task_query {
    PROTOCOL_MESSAGE(fix_common_task_query_msg);

    id_t id;
};

// запрос на проверку всех общих задач
// сервер <- клиент
struct check_all_common_tasks_query {
    PROTOCOL_MESSAGE(check_all_common_tasks_query_msg);
};

// запрос на исправление всех общих задач
// сервер <- клиент
struct fix_all_common_tasks_query {
    PROTOCOL_MESSAGE(fix_all_common_tasks_query_msg);
};

// запрос на создание бекапа
// сервер <- клиент
struct create_backup_query {
    PROTOCOL_MESSAGE(create_backup_query_msg);

    int manual_config_index;
    int manual_backup_config_index;
};

// запрос на создание восстановление из бекапа
// сервер <- клиент
struct restore_backup_query {
    PROTOCOL_MESSAGE(restore_backup_query_msg);

    int manual_config_index;
    int manual_backup_config_index;
    std::string file_name;
};

// запрос на обновление БД
// сервер <- клиент
struct update_database_query {
    PROTOCOL_MESSAGE(update_database_query_msg);

    int manual_config_index;
};

// запрос на создание и обновление БД
// сервер <- клиент
struct create_and_update_database_query {
    PROTOCOL_MESSAGE(create_and_update_database_query_msg);

    int manual_config_index;
};

// запрос версии БД
// сервер <- клиент
struct database_version_query {
    PROTOCOL_MESSAGE(database_version_query_msg);

    int manual_config_index;
};

// запрос на запуск БД
// сервер <- клиент
struct online_database_query {
    PROTOCOL_MESSAGE(online_database_query_msg);

    int manual_config_index;
};

// запрос на остановку БД
// сервер <- клиент
struct shutdown_database_query {
    PROTOCOL_MESSAGE(shutdown_database_query_msg);

    int manual_config_index;
};

// запрос на оптимизацию БД
// сервер <- клиент
struct optimize_database_space_query {
    PROTOCOL_MESSAGE(optimize_database_space_query_msg);

    int manual_config_index;
};

// запрос на оптимизацию индексов БД
// сервер <- клиент
struct optimize_database_indexes_query {
    PROTOCOL_MESSAGE(optimize_database_indexes_query_msg);

    int manual_config_index;
};

// запрос на дефрагментацию БД (создание бекапа и восстановление из него)
// сервер <- клиент
struct backup_and_restore_database_query {
    PROTOCOL_MESSAGE(backup_and_restore_database_query_msg);

    int manual_config_index;
};

// запрос на проверку структуры БД
// сервер <- клиент
struct validate_database_query {
    PROTOCOL_MESSAGE(validate_database_query_msg);

    int manual_config_index;
};

// ответ на запрос версии БД
// сервер -> клиент
struct database_version_answer {
    PROTOCOL_MESSAGE(database_version_answer_msg);

    int manual_config_index;
    std::string version;
};

}  // namespace db_maintenance_protocol
