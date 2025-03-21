#pragma once
#include "stringizer.hpp"
#include "node_defs.hpp"
#include "node_address.hpp"
#include <string>
#include <fstream>
#include <chrono>
#include <mutex>
#include <sstream>

namespace nc
{
class node_logger
{
    enum class direction
    {
        incoming,
        outgoing,
        connected,
        disconnected,
    };

public:
    node_logger(const std::string& node_name)
    {
        int file_index{};
        std::string file_name;
        while (true)
        {
            file_name = node_name + "_" + std::to_string(file_index++) + ".log";
            if (!exists_test(file_name))
                break;
        }
        file_.open(file_name);
    }
    template <typename T>
    void incoming(point_id_t id, uint32_t message, const T& item)
    {
        log_struct(id, direction::incoming, message, item);
    }
    void incoming(point_id_t id, uint32_t message, const void* data,
                  size_t size)
    {
        log_raw(id, direction::incoming, message, data, size);
    }
    template <typename T>
    void outgoing(point_id_t id, uint32_t message, const T& item)
    {
        log_struct(id, direction::outgoing, message, item);
    }
    void outgoing(point_id_t id, uint32_t message, const void* data,
                  size_t size)
    {
        log_raw(id, direction::outgoing, message, data, size);
    }
    void connected(point_id_t id, address_t address)
    {
        log_string(id, direction::connected, address_to_string(address));
    }
    void disconnected(point_id_t id)
    {
        log_string(id, direction::disconnected, "");
    }

private:
    inline bool exists_test(const std::string& name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }
    void log_string(point_id_t id, direction type, const std::string& message)
    {
        std::lock_guard lg(lock_);
        auto now = std::chrono::system_clock::now().time_since_epoch();
        auto ms_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        time_t in_time_t = ms_time / 1000;

        file_ << std::put_time(std::localtime(&in_time_t),
                               "%d.%m.%Y %H:%M:%S.");
        file_ << std::dec << std::setw(3) << std::setfill('0')
              << (ms_time % 1000);

        switch (type)
        {
            case direction::incoming:
                file_ << " <- ";
                break;
            case direction::outgoing:
                file_ << " -> ";
                break;
            case direction::connected:
                file_ << " ++ ";
                break;
            case direction::disconnected:
                file_ << " -- ";
                break;
            default:
                file_ << " --- ";
                break;
        }

        file_ << std::hex << std::setw(16) << std::setfill('0') << id << " ";
        file_ << message;
        file_ << std::endl;
    }
    template <typename T>
    void log_struct(point_id_t id, direction type, uint32_t message,
                    const T& item)
    {
        std::string msg_string = "$" + std::to_string(message) + " ";
        log_string(id, type, msg_string + stringizer::to_string(item));
    }
    void log_raw(point_id_t id, direction type, uint32_t message,
                 const void* data, size_t size)
    {
        std::string msg_string = "$" + std::to_string(message) + " ";
        std::stringstream ss;
        for (size_t i = 0; i < size; i++)
        {
            uint32_t cc = static_cast<const uint8_t*>(data)[i];
            ss << std::hex << std::setw(2) << std::setfill('0') << cc;
        }
        log_string(id, type, msg_string + ss.str());
    }
    std::mutex lock_;
    std::ofstream file_;
};
}  // namespace nc
