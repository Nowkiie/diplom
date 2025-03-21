#pragma once

// (c) Copyright Stanislav Lyalin 2019

#include <map>
#include <optional>
#include <string>
#include <vector>
#include <boost/rational.hpp>
#include <serdem/handler.hpp>

namespace serdem_protocol
{
const char* const protocol_name = "serdem";
const int protocol_code = 26;

#define SERDEM_MESSAGE(m)         \
    enum                          \
    {                             \
        message = m,              \
        protocol = protocol_code, \
    };

enum message_type
{
    // TODO: при переделке протокола упорядочить значения ниже
    ask_capability_msg,
    capability_msg,
    task_msg,
    cancel_task_msg,
    task_answer_msg,
    resource_available_msg,
    signal_msg,
    confirm_signal_msg,
    finish_signal_msg,
    status_demod_msg,
    parameter_demod_msg,
    spectrogram_msg,
    bitstream_msg,
    bitstream_err_msg,
    morse_dotdash_msg,
    phase_msg,
    phase_autocorr_msg,
    photogramm_msg,
    radiodata_msg,
    text_msg,
    videostream_msg,
    voice_msg,
    // voice_stream_msg, перенесено в конец, чтобы не ломать совместимость
    workflow_msg,
    stream_decoder_msg,
    status_decoder_msg,
    parameter_decoder_msg,

    completed_msg,

    voice_stream_msg,
    name_decoder_msg,
    begin_time_msg,
};

enum class setup_status
{
    ok,
    channels_busy,
    signal_source_not_found,
    fit_signal_type_not_found,
    unsupported_parameters,
    incomplete_parameters,
    setup_exception,
    insufficient_memory,
};

static std::string setup_status_str(setup_status status)
{
    switch (status)
    {
        case setup_status::ok:
            return "ok";
        case setup_status::channels_busy:
            return "channels busy";
        case setup_status::signal_source_not_found:
            return "signal source not found";
        case setup_status::fit_signal_type_not_found:
            return "fit signal type not found";
        case setup_status::unsupported_parameters:
            return "unsupported parameters";
        case setup_status::incomplete_parameters:
            return "incomplete parameters";
        case setup_status::setup_exception:
            return "setup exception";
        default:
            return {};
    }
}

enum class completed_status
{
    ok,
    abnormal_terminated,
    cancelled_by_client,
    urs_disconnected,
    server_disconnected,
};

// TODO(LyalinS): дублирование типов. Переделать
using byte_data_t = std::vector<uint8_t>;
using id_t = serdem::handler::id_t;
using entity_t = serdem::entity;
using status_t = serdem::status;
using decoder_status_t = serdem::decoder_status;
using task_id_t = uint32_t;
using sample_count_t = uint64_t;

using frequency_t = boost::rational<uint64_t>;
using parameters_t = std::map<std::string, std::string>;
using ns_time_t = int64_t;
using parameter_t = std::variant<int, float, std::string>;

// спросить возможности сервера (клиент -> сервер)
struct ask_capability
{
    SERDEM_MESSAGE(message_type::ask_capability_msg)
};

// получить возможности сервера (сервер -> клиент)
struct capability
{
    SERDEM_MESSAGE(message_type::capability_msg)

    std::vector<std::string> demodulators_xml;
    std::vector<std::string> decoders;
};

// выполнить задачу на сервере (клиент -> сервер)
struct task
{
    SERDEM_MESSAGE(message_type::task_msg)

    task_id_t id;
    ns_time_t setup_time;
    std::optional<frequency_t> frequency;
    std::optional<frequency_t> sample_rate;
    std::string demodulator;
    parameters_t parameters;
    std::optional<uint32_t> urs_id;

    // параметры времени

    // TODO: при переделке протокола изменить тип на std::optiolal
    ns_time_t begin_time;  // если 0, считается, что задача реального времени

    std::optional<ns_time_t> end_time;

    // длительность ожидания первого сеанса
    std::optional<ns_time_t> tracking_interval;

    // длительность ожидания повторного сеанса
    std::optional<ns_time_t> reentry_interval;

    // максимальная длительность сеанса
    std::optional<ns_time_t> session_duration;
};

// отменить задачу (клиент -> сервер)
struct cancel_task
{
    SERDEM_MESSAGE(message_type::cancel_task_msg)

    task_id_t id;
};

// задача принята в обработку (сервер -> клиент)
struct task_answer
{
    SERDEM_MESSAGE(message_type::task_answer_msg)

    task_id_t id;
    std::optional<frequency_t> sample_rate;
    setup_status status;
};

// начальная метка времени приёма сигнала с УРС (сервер -> клиент)
// отправляется один раз на задачу. Только для задач на УРС
struct begin_time
{
    SERDEM_MESSAGE(message_type::begin_time_msg)

    task_id_t id;
    ns_time_t begin_time;
};

// ресурс demodulator освободился (сервер -> клиент)
struct resource_available
{
    SERDEM_MESSAGE(message_type::resource_available_msg)

    std::string demodulator;
};

// передача сигнала (клиент -> сервер)
struct signal
{
    SERDEM_MESSAGE(message_type::signal_msg)

    task_id_t id;
    std::vector<float> samples;
};

// подтверждение приёма сигнала сервером (сервер -> клиент)
struct confirm_signal
{
    SERDEM_MESSAGE(message_type::confirm_signal_msg)

    task_id_t id;
    sample_count_t sample_count;
    bool task_in_progress;
};

// окончание передачи сигнала (клиент -> сервер)
struct finish_signal
{
    SERDEM_MESSAGE(message_type::finish_signal_msg)

    task_id_t id;
};

// получить промежуточные результаты (сервер -> клиент)
struct status_demod
{
    SERDEM_MESSAGE(message_type::status_demod_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    uint64_t sample_num;
    status_t status;
};

struct parameter_demod
{
    SERDEM_MESSAGE(message_type::parameter_demod_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::string name;
    parameter_t value;
};

struct spectrogram
{
    SERDEM_MESSAGE(message_type::spectrogram_msg)

    task_id_t id;

    std::vector<std::vector<float>> data;
};

struct bitstream
{
    SERDEM_MESSAGE(message_type::bitstream_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
};

struct bitstream_err
{
    SERDEM_MESSAGE(message_type::bitstream_err_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
};

struct morse_dotdash
{
    SERDEM_MESSAGE(message_type::morse_dotdash_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
};

struct phase
{
    SERDEM_MESSAGE(message_type::phase_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;

    // данные из Ipp64fc перепакованы в Ipp64f
    // Фактически значений в 2 раза меньше, чем data.size()
    std::vector<Ipp64f> data;
};

struct phase_autocorr
{
    SERDEM_MESSAGE(message_type::phase_autocorr_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;

    // данные из Ipp64fc перепакованы в Ipp64f
    // Фактически значений в 2 раза меньше, чем data.size()
    std::vector<Ipp64f> data;
};

struct photogramm
{
    SERDEM_MESSAGE(message_type::photogramm_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
};

struct radiodata
{
    SERDEM_MESSAGE(message_type::radiodata_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::string name;
    std::string value;
};

struct text
{
    SERDEM_MESSAGE(message_type::text_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::string data;
};

struct videostream
{
    SERDEM_MESSAGE(message_type::videostream_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
};

struct voice
{
    SERDEM_MESSAGE(message_type::voice_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::vector<float> data;
    uint32_t sample_rate;
};

struct voice_stream
{
    SERDEM_MESSAGE(message_type::voice_stream_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::string stream;
    std::vector<float> data;
    uint32_t sample_rate;
};

struct workflow
{
    SERDEM_MESSAGE(message_type::workflow_msg)

    task_id_t id;
    entity_t entity;
    id_t session_id;
    id_t block_id;
    std::vector<char> data;
};

struct stream_decoder
{
    SERDEM_MESSAGE(message_type::stream_decoder_msg)

    task_id_t id;
    id_t session_id;
    id_t block_id;
    byte_data_t data;
    std::string stream_name;
    entity_t entity;
};

struct status_decoder
{
    SERDEM_MESSAGE(message_type::status_decoder_msg)

    task_id_t id;
    id_t session_id;
    id_t block_id;
    decoder_status_t status;
    std::string stream_type;
    bool is_packed;
    std::string stream_name;
    std::string stream_name_ui;
    entity_t entity;
};

struct parameter_decoder
{
    SERDEM_MESSAGE(message_type::parameter_decoder_msg)

    task_id_t id;
    id_t session_id;
    id_t block_id;
    std::string path;
    std::string path_ui;
    std::string value;
    unsigned int block_number;
    std::string decoder_name;
    std::string decoder_name_ui;
    std::string parameter_name;
    std::string parameter_name_ui;
    entity_t entity;
};

struct name_decoder
{
    SERDEM_MESSAGE(message_type::name_decoder_msg)

    task_id_t id;
    id_t session_id;
    id_t block_id;
    std::string decoder_name;
    std::string decoder_name_ui;
    entity_t entity;
};

// результат выполнено (сервер -> клиент):
struct completed
{
    SERDEM_MESSAGE(message_type::completed_msg)

    task_id_t id;
    completed_status status;
};

#undef SERDEM_MESSAGE

}  // namespace serdem_protocol
