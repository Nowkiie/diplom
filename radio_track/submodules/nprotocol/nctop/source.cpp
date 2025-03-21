#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include <boost/asio.hpp>

//максимальный размер строки имени узла
constexpr int max_name_size = 255;
constexpr uint32_t packet_tag = 0x4B414E5A;
constexpr uint16_t resolver_service_port = 781;

enum node_category
{
    node_local = 0,   // локальный узел
    node_global = 1,  // глобальный узел
    node_remote = 2,  // удалённый узел
};

#pragma pack(push, 1)
struct enumerator_packet
{
    uint32_t tag;         //тег
    uint64_t record_key;  //уникальный ключ записи
    uint16_t port;        //номер порта
    char point_name[max_name_size];  // имя узла
    uint8_t category;                // тип узла
};
#pragma pack(pop)

struct table_record
{
    std::string remote;
    uint16_t port;
    bool server;
    uint8_t category;
    int counter;
    std::string point_name;
    uint64_t record_key;
};

class table_builder
{
public:
    table_builder(size_t column = 0)
        : column{column}
    {
    }
    table_builder& operator<<(const std::string& str)
    {
        items.push_back(str);
        width = std::max(width, str.length());
        if (!next)
        {
            next = std::make_unique<table_builder>();
        }
        return *next;
    }
    size_t size() const
    {
        return items.size();
    }
    std::string string(size_t row)
    {
        if (row >= items.size())
            return {};
        std::string result = items[row];
        for (size_t i = result.size(); i <= width; i++)
        {
            result += " ";
        }
        if (next)
        {
            result += next->string(row);
        }
        return result;
    }

private:
    size_t column{};
    size_t width{};
    std::unique_ptr<table_builder> next;
    std::vector<std::string> items;
};

class nctop
{
public:
    void run()
    {
        run_nctop();
    }

private:
    void run_nctop()
    {
        boost::asio::io_service service;
        boost::asio::ip::udp::socket socket(service);
        boost::system::error_code errc;
        socket.open(boost::asio::ip::udp::v4(), errc);
        socket.set_option(boost::asio::socket_base::broadcast(true), errc);
        //разрешаем использовать сокет нескольким программам
        socket.set_option(boost::asio::socket_base::reuse_address(true), errc);
        socket.bind(
            boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(),
                                           resolver_service_port),
            errc);

        if (errc)
        {
            std::cerr << "bind error: " << errc.message() << std::endl;
            return;
        }
        while (true)
        {
            std::vector<char> packet_data(sizeof(enumerator_packet));
            std::memset(packet_data.data(), 0, packet_data.size());
            boost::asio::ip::udp::endpoint endpoint;

            socket.receive_from(boost::asio::mutable_buffer(packet_data.data(),
                                                            packet_data.size()),
                                endpoint, {}, errc);

            auto* packet =
                reinterpret_cast<const enumerator_packet*>(packet_data.data());

            if (packet->tag != packet_tag)
                continue;

            if (errc)
            {
                break;
            }

            add_item(packet->port != 0, packet->point_name,
                     endpoint.address().to_string(), packet->category,
                     packet->port, packet->record_key);

            cls();
            print_map();
        }
    }
    void cls() const
    {
        std::cout << "\033[2J\033[1;1H";
    }
    void set_inverted() const
    {
        std::cout << "\033[7m";
    }
    void set_normal() const
    {
        std::cout << "\033[0m";
    }
    void add_item(bool server, const std::string& point_name,
                  const std::string& remote, uint8_t category,
                  unsigned short port, unsigned long long record_key)
    {
        std::string string_tag = record_key ? key_to_string(record_key) : "";

        std::string table_id =
            point_name + "!" + string_tag + "!" + remote + "$";

        auto iter = table_.find(table_id);

        if (iter == table_.end())
        {
            table_record item{};
            item.category = category;
            item.counter = 1;
            item.point_name = point_name;
            item.port = port;
            item.remote = remote;
            item.server = server;
            item.record_key = record_key;
            table_.insert({table_id, item});
        }
        else
        {
            iter->second.counter++;
        }
    }
    void print_map()
    {
        table_builder builder;
        builder << "ID"
                << "IP"
                << "Port"
                << "Type"
                << "Category"
                << "Requests"
                << "Name";

        for (const auto& [id, item] : table_)
        {
            std::string string_tag =
                item.record_key ? key_to_string(item.record_key) : "";

            std::string category_name;
            switch (item.category)
            {
                case node_local:
                    category_name = "Local";
                    break;
                case node_global:
                    category_name = "Global";
                    break;
                case node_remote:
                    category_name = "Remote";
            }
            std::string record_type;
            if (item.server)
                record_type = "Server";
            else
                record_type = "Client";

            std::string port_string;
            if (item.port)
                port_string = std::to_string(item.port);

            builder << string_tag << item.remote << port_string << record_type
                    << category_name << std::to_string(item.counter)
                    << item.point_name;
        }
        for (size_t i = 0; i < builder.size(); i++)
        {
            if (i == 0)
                set_inverted();
            if (i == 1)
                set_normal();
            std::cout << builder.string(i) << std::endl;
        }
        set_normal();
    }
    std::string key_to_string(uint64_t key) const
    {
        std::stringstream ss_tag;
        ss_tag << std::hex << std::setfill('0') << std::setw(16) << key;
        return ss_tag.str();
    }
    std::map<std::string, table_record> table_;
};

int main(int argc, char* argv[])
{
    nctop n;
    n.run();
}
