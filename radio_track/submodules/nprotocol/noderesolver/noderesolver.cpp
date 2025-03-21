#include <node_base.hpp>
#include <vector>
#include <signal.h>
#include <thread>
#ifdef __linux__
#include <unistd.h>
#endif


//структура хранения записи в памяти
struct message_record
{
    std::string node_name;
    std::string node_info;
    unsigned short port;
};
//клиентское подключение
struct client_connection
{
    std::vector<message_record> records;
};

//максимальный размер возврашаемой строки
const int max_name_size = 256;

#pragma pack(push, 1)
//структура обмена со службой (запрос)
struct message_command
{
    enum
    {
        type = 0x0f101
    };
    unsigned int flags;
    char node_name[max_name_size];  //имя узла (без пути)
    char node_info[max_name_size];  //информация, предоставленная узлом
    unsigned short port;            //номер порта
    unsigned int user_data;  //пользовательские данные - переносятся в ответ
};
struct message_answer_record
{
    char node_name[max_name_size];
    char node_info[max_name_size];
    unsigned short port;
};
struct message_answer
{
    enum
    {
        type = 0x0f103
    };
    unsigned int result;
    unsigned int records_count;
    unsigned int user_data;
    //message_answer_record records[records_count];
};
#pragma pack(pop)
//структура для хранения в памяти
struct memory_command
{
    unsigned int flags;
    std::string node_name;
    std::string node_info;
    unsigned short port;
    unsigned int user_data;
};
struct memory_answer_record
{
    std::string node_name;
    std::string node_info;
    unsigned short port;
};
struct memory_answer
{
    unsigned int result;
    unsigned int user_data;
    std::vector<memory_answer_record> records;
};
//коды ошибок
namespace result
{
enum resolver_result_codes
{
    success = 0,
    bad_request = 1,
    already_registred = 2,
    not_found = 3
};

}  //namespace result

//флаги запроса
namespace flags
{
enum resolver_message_flags
{
    command_test_port = 1,  //проверять на соответствие порт
    command_test_name = 2,  //проверять на соответствие имя узла

    command_query = 4,       //сообщение - запрос
    command_register = 8,    //регистрация узла
    command_unregister = 16  //разрегистрация узла

};

}  //namespace flags

class resover_service : public nc::node_base
{
public:
    resover_service() {}
    ~resover_service()
    {
        stop();
    }

private:
    virtual void connected(nc::point_id_t id, nc::address_t /*address*/,
                           nc::port_t /*port*/) final
    {
        client_connection cc{};
        if (clients_.count(id))
            return;
        clients_[id] = cc;
    }
    virtual void disconnected(nc::point_id_t id) final
    {
        clients_.erase(id);
    }
    virtual void message(nc::point_id_t id, nc::message_type_t msg_type,
                         nc::queue_buffer_t store) final
    {
        if (msg_type != message_command::type)
            return;
        auto data_size = store->size();

        //проверка на размер сообщения
        if (data_size != sizeof(message_command))
            return;
        message_command command =
            *reinterpret_cast<const message_command*>(store->data());
        //предотвращаем переполнение буфера
        command.node_info[sizeof(command.node_info) - 1] = '\0';
        command.node_name[sizeof(command.node_name) - 1] = '\0';

        //может быть установлен только один флаг
        int flag_count = 0;
        flag_count += command.flags & flags::command_query ? 1 : 0;
        flag_count += command.flags & flags::command_register ? 1 : 0;
        flag_count += command.flags & flags::command_unregister ? 1 : 0;
        if (flag_count != 1)
        {
            send_result(id, command.user_data, result::bad_request);
            return;
        }
        auto test_record_with_flags = [&](const message_record& record) -> bool
        {
            bool result = true;
            if (command.flags & flags::command_test_port)
                result &= record.port == command.port;
            if (command.flags & flags::command_test_name)
                result &= record.node_name == command.node_name;
            return result;
        };
        auto query_result = query_by(test_record_with_flags);

        if (command.flags & flags::command_query)
        {
            send_result(
                id, command.user_data,
                query_result.size() > 0 ? result::success : result::not_found,
                query_result);
        }
        else if (command.flags & flags::command_register)
        {
            if (query_result.size()
                > 0)  //отказ в регистрации, если узел уже существует
            {
                send_result(id, command.user_data, result::already_registred,
                            query_result);
            }
            else
            {
                message_record new_record;
                new_record.node_name = command.node_name;
                new_record.node_info = command.node_info;
                new_record.port = command.port;
                clients_[id].records.push_back(new_record);
                send_result(id, command.user_data, result::success);
            }
        }
        else if (command.flags & flags::command_unregister)
        {
            if (query_result.size() == 0)  //ошибка - узел не зарегистрирован
            {
                send_result(id, command.user_data, result::not_found,
                            query_result);
            }
            else
            {
                for (auto& client : clients_)
                {
                    auto remove_iter = std::remove_if(
                        client.second.records.begin(),
                        client.second.records.end(), test_record_with_flags);
                    if (remove_iter != client.second.records.end())
                    {
                        client.second.records.erase(
                            remove_iter, client.second.records.end());
                    }
                }
                send_result(id, command.user_data, result::success);
            }
        }
        else
            send_result(id, command.user_data, result::bad_request);
    }
    virtual void init() final
    {
        nc::port_t port = acceptor_init(nc::detail::resolver_service_port);
        if (port == 0)
        {
            return;
        }
        start_accept();
    }
    virtual void deinit() final {}

    template <typename C>
    std::vector<message_record> query_by(C pred)
    {
        std::vector<message_record> result;
        for (auto const& client : clients_)
        {
            for (auto const& record : client.second.records)
            {
                if (pred(record))
                    result.push_back(record);
            }
        }
        return result;
    }
    void send_result(nc::point_id_t sock_id, unsigned int user_data,
                     unsigned int result,
                     const std::vector<message_record>& results =
                         std::vector<message_record>())
    {
        //размер сообщения
        uint32_t message_answer_size = sizeof(message_answer)
                                       + static_cast<uint32_t>(results.size())
                                             * sizeof(message_answer_record);

        nc::queue_buffer_t data =
            std::make_shared<std::vector<char>>(message_answer_size);
        message_answer* answer =
            reinterpret_cast<message_answer*>(data->data());

        answer->records_count = static_cast<unsigned int>(results.size());
        answer->result = result;
        answer->user_data = user_data;
        message_answer_record* records_array =
            reinterpret_cast<message_answer_record*>(data->data()
                                                     + sizeof(message_answer));
        for (size_t i = 0; i < results.size(); i++)
        {
            //очищаем, чтобы не было мусора после сток
            std::memset(records_array[i].node_info, 0,
                        sizeof(records_array[i].node_info));
            std::memset(records_array[i].node_name, 0,
                        sizeof(records_array[i].node_name));
            //копируем строку с ограничениями
            std::memcpy(records_array[i].node_info,
                        results[i].node_info.c_str(),
                        std::min(sizeof(records_array[i].node_info) - 1,
                                 results[i].node_info.size() + 1));
            std::memcpy(records_array[i].node_name,
                        results[i].node_name.c_str(),
                        std::min(sizeof(records_array[i].node_name) - 1,
                                 results[i].node_name.size() + 1));
            records_array[i].port = results[i].port;
        }
        start_send(sock_id, message_answer::type, data);
    }

private:
    std::map<nc::point_id_t, client_connection> clients_;
};

static bool interrupt = false;

void sigkill(int)
{
    interrupt = true;
}
void sigint(int)
{
    interrupt = true;
}

#ifdef __linux__
int main()
{

    signal(SIGINT, sigint);
    signal(SIGKILL, sigkill);

    resover_service service;
    service.start();

    while (!interrupt)
    {
        sleep(60);
    }
}
#else
int main()
{
    resover_service service;
    service.start();

    while (!interrupt)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
#endif


