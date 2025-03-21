#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <optional>
#include <array>

namespace urs_monitor_protocol
{
const uint16_t protocol_code = 32;
const char * const protocol_name = "UrsMonitorProtocolV2";

using string_t = std::string;
using urs_time_t = int64_t;
using urs_adc_t = std::array<uint16_t, 32>;

struct urs_drsp_client
{
    uint32_t id;
    uint32_t ip;
    uint32_t pid;
    uint32_t active_orders;
    uint32_t executed_orders;
    uint32_t miss_count;
    uint64_t control_packet_count;
    uint64_t num_bytes;
    urs_time_t time_create;  //время в секундах
    string_t process_name;
};

struct urs_drsp_server
{
    uint32_t ip;
    uint32_t link;
    string_t description;
    std::vector<urs_drsp_client> clients;
};

struct urs_hdd_info
{
    uint64_t disk_size; //размер диска в байтах
    string_t description; //текстовое описание диска (модель, серийный номер)
};

struct urs_hdd
{
    uint32_t disk_index; //номер диска
    uint32_t temperature; //температура
    uint32_t bad_sectors_count; //количество плохих секторов
    uint32_t power_on_hours; //время работы диска в часах (с момента изготовления)
    uint64_t read_queue_usage; //использование(размер) очереди чтения в запросах
    uint64_t write_queue_usage; //использование очереди записи
    uint64_t write_queue_size; //размер очереди записи
    uint64_t write_drop_count; //количество пропусков записи
    uint64_t write_block_count; //количество записанных блоков
    uint64_t read_block_count; //количество считанных блоков
    uint64_t average_write_time; //среднее время записи блока
    uint64_t average_read_time; //среднее время чтения блока
    uint64_t write_time; //время нахождения в режиме записи
    uint64_t read_time; //время нахождения в режиме чтения
    uint64_t idle_time; //время нахождения в режиме простоя
    uint32_t max_temperature;
    urs_hdd_info disk_info;
};

struct urs_ssd
{
    uint32_t error_read;
    uint32_t error_write;
    uint32_t drop_write;
    uint32_t error_crc;
};

enum urs_plugin_exec_type : uint32_t
{
    exec_gpu = 0,
    exec_cpu = 1,
    exec_void = 2,
    exec_aru = 3,
    exec_gpu_mutable = 4,
    exec_unset = 255
};

struct urs_buf
{
    uint32_t miss_count;
    uint32_t full_part_in_perc;
    uint64_t call_count;
};

enum urs_signal_level : uint32_t
{
    low = 0,
    normal,
    perfect,
    overflow
};

enum urs_adc_status : uint32_t
{
    adc_normal = 0,
    no_signal
};




struct urs_rpu_adc
{
    uint32_t low_bit_count;
    uint32_t max_samples_count;
    uint32_t total_bits_count;
    urs_adc_t adc;
    urs_adc_status status;
};

struct urs_rpu_agc
{
    urs_signal_level ovf;
    int32_t att;
    int32_t fpga_agc;
    int32_t min_att;
    int32_t max_att;
};


struct urs_rpu
{
    string_t description;
    uint32_t miss_count;  //Пропуски на РПУ
    std::vector<urs_rpu_adc> adc;
    urs_rpu_agc agc;
};

struct urs_plugin
{
    string_t description;
    urs_plugin_exec_type ptr_type;
    uint64_t call_count;
    uint64_t exec_count;
    uint64_t avg_exec_time;
    uint32_t error;
    uint64_t max_exec_time;
    uint64_t miss_count;
    uint64_t srv_exec_time;
};

struct urs_consumer
{
    string_t description;
    std::optional<urs_buf> input;
    std::optional<urs_drsp_server> network_stat;
    std::vector<urs_hdd> hdd_stat;
    std::optional<urs_ssd> ssd_stat;
};

struct urs_sub_server
{
    string_t description;
    std::optional<urs_buf> gpu;
    std::vector<urs_consumer> consumers;
};

enum urs_sdr_status : uint32_t
{
    online,
    offline,
    error
};


struct urs_rssi
{
    string_t description;
    int32_t value;
    int32_t min_level;
    int32_t max_level;
    std::optional<int32_t> bound_no_signal;
    std::optional<int32_t> bound_ovf;
};

struct urs_sdr_element
{
    string_t description;
    string_t client;
    urs_sdr_status status;
    urs_buf buf;
    float native_rate;
    float client_rate;
    uint8_t num;  //позиция в корзине с приемниками: от 1 до 16
    uint8_t dev;  //номер устройства для группировки по устройствам
    urs_rpu_agc agc;
    std::vector<urs_rssi> rssi;
};

struct urs_sdr
{
    std::vector<urs_sdr_element> sdr;
    uint32_t sdr_min_count;
};

struct urs_ku_agc
{
    int in_level;
    int out_level;
};

enum urs_ku_board_status : uint32_t
{
    ku_ok,
    ku_broken,     //неисправен
    ku_short_circ, //КЗ
    ku_open_circ  //обрыв
};

enum urs_ku_signal_status : uint32_t
{
    ku_rssi_ok,    //rssi получен, все ок
    ku_no_signal,  //низний уровень сигнала
    ku_no_antenna, //экстремально низкий уровень сигнала, по сути антенна неисправна
    ku_high_signal //подозрительно высокий уровень сигнала по сравнению с другими антеннами
};



struct urs_ku_board
{
   urs_ku_board_status board_status;
   std::optional<uint32_t> signal_level;
   std::optional<urs_ku_signal_status> signal_status;
};

struct urs_ku
{
    string_t description;
    string_t fpga;
    uint64_t freq_start;
    uint64_t freq_step;
    std::vector<urs_ku_board> boards;
    std::vector<urs_ku_agc> peleng_agc;
    std::vector<urs_ku_agc> voice_agc;
    std::vector<int> agc_levels;
};


struct urs_event
{
    urs_time_t time;
    uint32_t code;
    string_t module;
    string_t message;
};

enum message_type
{
    msg_info = 1,
    msg_dynamic_stat,
    msg_notify,
    msg_status,
};

struct urs_server_info
{
    enum
    {
        message = msg_info,
        protocol = protocol_code,
    };
    uint32_t id;
    std::string name;
    urs_time_t start_time;
    std::string uuid;
};

struct urs_dynamic_stat
{
    enum
    {
        message = msg_dynamic_stat,
        protocol = protocol_code,
    };

    std::optional<urs_rpu> rpu_stat;
    std::vector<urs_sub_server> sub_servers_stat;
    std::optional<urs_sdr> sdr_stat;
    std::optional<urs_ku> ku_stat;
    std::vector<urs_plugin> plugins;
};

struct urs_notify
{
    enum
    {
        message = msg_notify,
        protocol = protocol_code,
    };
    urs_event what;
};

struct urs_status
{
    enum
    {
        message = msg_status,
        protocol = protocol_code,
    };
    bool started;
    std::optional<urs_event> last_error;
};
}
