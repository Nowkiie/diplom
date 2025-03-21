#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>

namespace task_protocol
{
enum task_protocol_codes
{
    register_client_msg,
    register_answer_msg,

    client_update_query_msg,
    client_update_answer_msg,
    client_remove_query_msg,
    client_remove_answer_msg,
    client_update_event_msg,
    client_remove_event_msg,

    signal_type_update_query_msg,
    signal_type_update_answer_msg,
    signal_type_remove_query_msg,
    signal_type_remove_answer_msg,
    signal_type_update_event_msg,
    signal_type_remove_event_msg,

    task_update_query_msg,
    task_update_answer_msg,
    task_remove_query_msg,
    task_remove_answer_msg,
    task_update_event_msg,
    task_remove_event_msg,

    link_update_query_msg,
    link_update_answer_msg,
    link_remove_query_msg,
    link_remove_answer_msg,
    link_update_event_msg,
    link_remove_event_msg,

    radiodata_remove_query_msg,
    radiodata_remove_answer_msg,
    radiodata_update_query_msg,
    radiodata_update_answer_msg,
    radiodata_update_event_msg,
    radiodata_remove_event_msg,

    client_state_event_msg,
    receive_flags_update_msg,

    server_information_msg,

};

const char* const protocol_name = "task_protocol";

const int protocol_code = 20;

using ns_time_t = uint64_t;
using id_t = uint32_t;
using query_id_t = uint64_t;

using param_t = std::variant<bool, int64_t, double, ns_time_t, std::string>;

#define TASK_MESSAGE(m)           \
    enum                          \
    {                             \
        message = m,              \
        protocol = protocol_code, \
    };

namespace frequency_control_mode
{
enum frequency_control_mode
{
    tracking = 0,   // слежение
    intercept = 1,  // перехват
    ignore = 2,     // игнорирование
};
}

namespace range_control_mode
{
enum range_control_mode
{
    all = 0,             // все излучения
    excude_ignored = 1,  // все кроме ингорируемых
    excude_known = 2,    // все кроме известных
    ignore = 3,          // диапазон игнорирования
    only_known = 4,      // только известные
};
}

namespace record_results
{
enum record_results
{
    all,         // без ограничений
    radio_data,  // только радиоданные
    ignore,      // без параметров радиоперехвата
};
}

namespace search_mode
{
enum search_mode
{
    all,           // все
    not_disliked,  // все кроме игнорируемых
    liked,         // полезные
    unknown,       // неизвестные
};
}

namespace receive_mode
{
enum receive_mode
{
    none,
    usb,
    lsb,
    am,
    fm,
};
}

namespace peleng_mode
{
enum peleng_mode
{
    disable,  // не пеленговать
    express,  // пеленговать
    place,    // местоопределение
};
}

namespace fixed_parameter_code
{
const char* const frequency_control_mode = "frequency_control_mode";  // реж. ч.
const char* const range_control_mode = "range_control_mode";  // режим диапазона
const char* const record_results = "record_results";  // регистрация результатов
const char* const tracking_interval = "tracking_interval";  // интервал слежения
const char* const search_mode = "search_mode";              // режим поиска
const char* const register_interval = "register_interval";  // прод. рег-ии (с)
const char* const receive_mode = "receive_mode";            // режим приёмника
const char* const peleng_mode = "peleng_mode";          // режим пеленгования
const char* const peleng_interval = "peleng_interval";  // интервал пеленг. (с)
const char* const frequency = "frequency";              // частота
const char* const frequency_begin = "frequency_begin";  // начало диапазона
const char* const frequency_end = "frequency_end";      // конец диапазона
const char* const frequency_up = "frequency_up";  // частота восход. луча (ссс)
const char* const rejecting_flag = "rejecting_flag";  // флаг запрета
const char* const item_name = "item_name";            // имя объекта
const char* const schedule_begin = "schedule_begin";  // время начала работы
const char* const schedule_end = "schedule_end";      // время окончания работы
};  // namespace fixed_parameter_code

// описание вида передачи
struct signal_type_item
{
    id_t signal_type_id;
    int id_pi;                // идентификатор пеленгуемого излучения
    int signal_width;         // ширина полосы сигнала
    int signal_shift;         // смещение несущей относительно центра спектра
    std::string code;         // код вида передачи
    std::string name;         // имя вида передачи для пользователя
    std::string description;  // описание вида передачи
    int id_vp;                // глобальный идентификатор вида передачи
};

enum task_type : uint32_t
{
    task_frequency = 1,  // обработка частот
    task_range = 2,      // обработка диапазона
    task_sat = 4,        // обработка пар частот (ccc)
};

// описание всех клиентов
struct client_item
{
    id_t client_id;
    std::string host_name;                 // имя машины
    std::string program_name;              // имя программы
    std::string post_name;                 // имя поста
    uint32_t task_type;                    // тип задания (флаги task_type)
    std::vector<id_t> signal_type_ids;     // обрабатываемые вп
    std::vector<uint32_t> signal_servers;  // сервера УРС
};

enum receive_flags
{
    receive_signal_type = 1,    // получать список видов передач
    receive_client = 2,         // получать список клиентов
    receive_task = 4,           // получать формуляр
    receive_link = 8,           // получать связи клиентов и формуляра
    receive_radiodata = 16,     // получать радиоданные
    receive_client_state = 32,  //получать состояние клиентов
};

// запрос на регистрацию
// клиент -> сервер

struct register_client
{
    TASK_MESSAGE(register_client_msg);

    std::string host_name;     // имя машины
    std::string program_name;  // имя программы
    uint32_t task_type;        // тип задания (флаги task_type)
    std::vector<signal_type_item> signal_types;  // обрабатываемые  виды передач
    uint32_t receive_flags;                      // флаги receive_flags
    std::vector<uint32_t> signal_servers;      // список серверов УРС
};

// ответ на регистрацию
// сервер -> клиент
struct register_answer
{
    TASK_MESSAGE(register_answer_msg);
    id_t self_client_id;  // свой идентификатор клиента
};

enum class remove_type : int
{
    normal, // удаление с клиента
    recursuve, // удаление сервером связанной записи
};

struct remove_declaration
{
    id_t id; // удентификатор удаляемой записи
    remove_type type; // тип удаления
};

// запрос на измененеие клиента
// клиент -> сервер
struct client_update_query
{
    TASK_MESSAGE(client_update_query_msg);

    query_id_t query_id;  // идентификатор запроса (будет отправлен в ответе)
    client_item item;     // изменяемый клиент
};

// ответ на завпрос изменения клиента
// сервер -> клиент
struct client_update_answer
{
    TASK_MESSAGE(client_update_answer_msg);

    query_id_t query_id;  // идентификатор запроса
    id_t item_id;         // идентификатор клиента
    bool result;          // результат операции
};

// запрос на удаление клиента
// клиент -> сервер
struct client_remove_query
{
    TASK_MESSAGE(client_remove_query_msg);

    query_id_t query_id;  // идентификатор запроса (будет отправлен в ответе)
    id_t item_id;         // идентификатор клиента
};

// ответ на завпрос удаления клиента
// сервер -> клиент
struct client_remove_answer
{
    TASK_MESSAGE(client_remove_answer_msg);

    query_id_t query_id;  // идентификатор запроса
    bool result;          // результат операции
};

// событие обновления списка клиентов
// сервер -> клиент
struct client_update_event
{
    TASK_MESSAGE(client_update_event_msg);

    std::vector<client_item> items;
};

// событие удаления списка клиентов
// сервер -> клиент
struct client_remove_event
{
    TASK_MESSAGE(client_remove_event_msg);

    std::vector<remove_declaration> item_ids;
};

// запрос на измененеие вида передачи
// клиент -> сервер
struct signal_type_update_query
{
    TASK_MESSAGE(signal_type_update_query_msg);

    query_id_t query_id;    // идентификатор запроса (будет отправлен в ответе)
    signal_type_item item;  // изменяемый вид передачи
};

// ответ на завпрос изменения вида передачи
// сервер -> клиент
struct signal_type_update_answer
{
    TASK_MESSAGE(signal_type_update_answer_msg);

    query_id_t query_id;  // идентификатор запроса
    id_t item_id;         // идентификатор вида передачи
    bool result;          // результат операции
};

// запрос на удаление вида передачи
// клиент -> сервер
struct signal_type_remove_query
{
    TASK_MESSAGE(signal_type_remove_query_msg)

    query_id_t query_id;  // идентификатор запроса (будет отправлен в ответе)
    id_t item_id;         // идентификатор вида передачи
};

// ответ на завпрос удаления вида передачи
// сервер -> клиент
struct signal_type_remove_answer
{
    TASK_MESSAGE(signal_type_remove_answer_msg);

    query_id_t query_id;  // идентификатор запроса
    bool result;          // результат операции
};

// событие обновления списка видов передач
// сервер -> клиент
struct signal_type_update_event
{
    TASK_MESSAGE(signal_type_update_event_msg);

    std::vector<signal_type_item> items;
};

// событие удалени списка видов передач
// сервер -> клиент
struct signal_type_remove_event
{
    TASK_MESSAGE(signal_type_remove_event_msg);

    std::vector<remove_declaration> item_ids;
};

enum class item_class_t
{
    root_item,           // корневой элемент задания
    signal_rule,         // правила видов передач
    radionet_class,      // вид радиосети
    radionet_node,       // радиосеть
    frequency_item,      // запись задания с частотой
    range_item,          // запись задания с диапазоном
    temp_radionet_node,  //временная редиосеть
};

enum class link_type : int
{
    link_on,
    link_off
};

// связь клиента с заданием
struct link_item
{
    id_t link_id; // идентификатор связи
    id_t task_id; // идентификатор задания
    id_t client_id; // идентификатор клинта
    uint32_t server_id; // идентификатор сервера УРС
    link_type type; // тип связи
    std::string owner; // создвтель-владелец связи
};

// структура записи задания
struct task_item
{
    id_t item_id;             // идентификатор записи
    id_t parent_id;           // идентификатор родительского элемента
    item_class_t item_class;  // тип узла
    id_t signal_type_id;      // вид передачи
    std::map<std::string, param_t> fixed_parameters; // параметры из списка fixed_parameter_code
    std::map<std::string, param_t> demodulator_parameters; // параметры демодулятора
    std::string owner; // создвтель-владелец задания
};

/*
    изменение объектов
*/

// клиент -> сервер
struct task_remove_query
{
    TASK_MESSAGE(task_remove_query_msg);

    query_id_t query_id;
    id_t item_id;
};
// сервер -> клиент
struct task_remove_answer
{
    TASK_MESSAGE(task_remove_answer_msg);

    query_id_t query_id;
    bool result;
};

// клиент -> сервер
struct task_update_query
{
    TASK_MESSAGE(task_update_query_msg);

    query_id_t query_id;
    task_item item;
};
// сервер -> клиент
struct task_update_answer
{
    TASK_MESSAGE(task_update_answer_msg);

    query_id_t query_id;
    id_t item_id;
    bool result;
};

// событие обновления задания
struct task_update_event
{
    TASK_MESSAGE(task_update_event_msg);

    std::vector<task_item> items;
};

// событие обновления задания
struct task_remove_event
{
    TASK_MESSAGE(task_remove_event_msg);

    std::vector<remove_declaration> item_ids;
};

/*
  изменение связей
*/

// клиент -> сервер
struct link_remove_query
{
    TASK_MESSAGE(link_remove_query_msg);

    query_id_t query_id;
    id_t item_id;
};
// сервер -> клиент
struct link_remove_answer
{
    TASK_MESSAGE(link_remove_answer_msg);

    query_id_t query_id;
    bool result;
};

// клиент -> сервер
struct link_update_query
{
    TASK_MESSAGE(link_update_query_msg);

    query_id_t query_id;
    link_item item;
};
// сервер -> клиент
struct link_update_answer
{
    TASK_MESSAGE(link_update_answer_msg);

    query_id_t query_id;
    id_t item_id;
    bool result;
};

// событие обновления задания
struct link_update_event
{
    TASK_MESSAGE(link_update_event_msg);

    std::vector<link_item> items;
};

// событие обновления задания
struct link_remove_event
{
    TASK_MESSAGE(link_remove_event_msg);

    std::vector<remove_declaration> item_ids;
};

enum class interest_type : int
{
    disliked = -1, // игнорируемый
    normal = 0, // нормальный
    liked = 1, // важный
};

// запись справочника радиоданных
struct radiodata_item
{
    id_t radiodata_id;       // идентификатор записи
    std::string type;        // тип данных
    std::string value;       // значение (сементика определяется полем type)
    std::string iri;         // идентификатор радиоизлучения
    std::string comment;     // комментарий
    interest_type interest;  // интерес
};

// клиент -> сервер
struct radiodata_remove_query
{
    TASK_MESSAGE(radiodata_remove_query_msg);

    query_id_t query_id;
    id_t item_id;
};
// сервер -> клиент
struct radiodata_remove_answer
{
    TASK_MESSAGE(radiodata_remove_answer_msg);

    query_id_t query_id;
    bool result;
};

// клиент -> сервер
struct radiodata_update_query
{
    TASK_MESSAGE(radiodata_update_query_msg);

    query_id_t query_id;
    radiodata_item item;
};
// сервер -> клиент
struct radiodata_update_answer
{
    TASK_MESSAGE(radiodata_update_answer_msg);

    query_id_t query_id;
    id_t item_id;
    bool result;
};

// сервер -> клиент
struct radiodata_update_event
{
    TASK_MESSAGE(radiodata_update_event_msg);

    std::vector<radiodata_item> items;
};

// сервер -> клиент
struct radiodata_remove_event
{
    TASK_MESSAGE(radiodata_remove_event_msg);

    std::vector<remove_declaration> item_ids;
};

struct client_state_item
{
    id_t client_id;
    bool connected;
};

// сервер -> клиент
struct client_state_event
{
    TASK_MESSAGE(client_state_event_msg);

    std::vector<client_state_item> client_states;
};

//  клиент -> сервер
struct receive_flags_update
{
    TASK_MESSAGE(receive_flags_update_msg);

    uint32_t receive_flags;  // флаги receive_falgs
};

//  сервер -> клиент
// информация о сервере (отправляется после подключения)
struct server_information
{
    TASK_MESSAGE(server_information_msg);
    uint32_t id_rpp;          // идентификатор рпп
    std::string rpp_name_ui;  // имя рпп для пользователя
};

#undef TASK_MESSAGE

}  // namespace task_protocol
