#pragma once
#ifdef __linux__
#    include <sys/socket.h>
#    include <sys/ioctl.h>
#    include <net/if.h>
#else
#    include <boost/dll/import.hpp>
#endif
#include <boost/algorithm/string.hpp>
#include <cstdint>
#include "node_defs.hpp"

namespace nc::detail
{
#ifdef __linux__
static const char* getenv_uni(const char* name)
{
    return getenv(name);
}
#else
static const char* getenv_uni(const char* name)
{
    static thread_local char result[1024]{};
    std::memset(result, 0, sizeof(result));
    size_t size = sizeof(result);
    getenv_s(&size, result, size, name);
    if (size == 0)
    {
        return nullptr;
    }
    return result;
}
#endif
struct iprow
{
    address_t address;
    address_t netmask;
};
static std::vector<address_t> ip_ignored_interfaces()
{
    std::vector<address_t> result;
    const char* ignore_list = getenv_uni("NC3_IGNORE_INTERFACE");
    if (!ignore_list)
    {
        return {};
    }
    std::vector<std::string> ignore_ifs;
    boost::split(ignore_ifs, ignore_list, boost::is_any_of(";:"));
    for (const auto& ignore_if : ignore_ifs)
    {
        boost::system::error_code errc;
        auto addr = boost::asio::ip::address_v4::from_string(ignore_if, errc);

        if (errc)
            continue;

        address_t ignore_if_addr = addr.to_ulong();
        result.push_back(ignore_if_addr);
    }
    return result;
}
}  // namespace nc::detail

#ifdef __linux__
namespace nc::detail
{
typedef int native_type;
static bool set_keepalive_interval(native_type socket, unsigned int interval_ms)
{
    int keepalive_time = interval_ms / 1000;
    int keepalive_count = 4;
    int keepalive_interval = interval_ms / 1000;
    int user_timeout = interval_ms * keepalive_count;
    if (setsockopt(socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepalive_time,
                   sizeof(keepalive_time))
        != 0)
    {
        return false;
    }
    if (setsockopt(socket, IPPROTO_TCP, TCP_KEEPCNT, &keepalive_count,
                   sizeof(keepalive_count))
        != 0)
    {
        return false;
    }
    if (setsockopt(socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepalive_interval,
                   sizeof(keepalive_interval))
        != 0)
    {
        return false;
    }
    if (setsockopt(socket, IPPROTO_TCP, TCP_USER_TIMEOUT, &user_timeout,
                   sizeof(user_timeout))
        != 0)
    {
        return false;
    }

    return true;
}

static std::vector<iprow> get_ip_addr_table()
{
    auto fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        return {};
    }
    ifconf ifc{};
    ioctl(fd, SIOCGIFCONF, &ifc);
    std::vector<char> buff(ifc.ifc_len);
    ifc.ifc_buf = buff.data();
    std::vector<iprow> result;
    if (ioctl(fd, SIOCGIFCONF, &ifc) == 0)
    {
        size_t if_count = ifc.ifc_len / sizeof(ifreq);

        ifreq* req = reinterpret_cast<ifreq*>(buff.data());
        for (size_t i = 0; i < if_count; i++)
        {
            if (req[i].ifr_addr.sa_family != AF_INET)
            {
                continue;
            }
            auto* addr = reinterpret_cast<sockaddr_in*>(&req[i].ifr_addr);
            iprow row;
            row.address = ntohl(addr->sin_addr.s_addr);

            ifreq maskreq{};
            std::memcpy(maskreq.ifr_name, req[i].ifr_name, IFNAMSIZ);

            if (ioctl(fd, SIOCGIFNETMASK, &maskreq) == 0)
            {
                auto* mask =
                    reinterpret_cast<sockaddr_in*>(&maskreq.ifr_netmask);
                row.netmask = ntohl(mask->sin_addr.s_addr);
                result.push_back(row);
            }
        }
    }
    close(fd);
    return result;
}
}  // namespace nc::detail
#else
namespace nc::detail
{
typedef size_t native_type;

typedef int(__stdcall WSAIoctlLoad)(native_type s, uint32_t dwIoControlCode,
                                    const void* lpvInBuffer,
                                    uint32_t cbInBuffer, void* lpvOutBuffer,
                                    uint32_t cbOutBuffer,
                                    uint32_t* lpcbBytesReturned,
                                    const void* lpOverlapped,
                                    const void* lpCompletionRoutine);
#    pragma pack(push, 1)

struct mib_ipaddrrow
{
    uint32_t dwAddr;
    uint32_t dwIndex;
    uint32_t dwMask;
    uint32_t dwBCastAddr;
    uint32_t dwReasmSize;
    uint32_t dwReserved;
};
struct mib_ipaddrtable
{
    uint32_t dwNumEntries;
    mib_ipaddrrow table[1];
};
#    pragma pack(pop)

typedef int(__stdcall GetIpAddrTableLoad)(mib_ipaddrtable* pIpAddrTable,
                                          uint32_t* pdwSize, bool bOrder);

#    pragma pack(push, 1)
struct tcp_keepalive_load
{
    uint32_t onoff;
    uint32_t keepalivetime;
    uint32_t keepaliveinterval;
};
#    pragma pack(pop)
//нужно установить параметры keepalive
//чтобы не подключать windows.h сделаем так
static bool set_keepalive_interval(native_type socket, unsigned int interval_ms)
{
    try
    {
        static auto wsa_ioctl = boost::dll::import<WSAIoctlLoad>(
            "WS2_32.dll", "WSAIoctl",
            boost::dll::load_mode::search_system_folders);

        constexpr uint32_t sio_keepalive_vals = 0x98000004;
        uint32_t dwBytes = 0;

        tcp_keepalive_load kaSettings{}, sReturned{};
        kaSettings.onoff = 1;
        kaSettings.keepalivetime = interval_ms;
        kaSettings.keepaliveinterval = interval_ms;

        return (wsa_ioctl(socket, sio_keepalive_vals, &kaSettings,
                          uint32_t(sizeof(kaSettings)), &sReturned,
                          uint32_t(sizeof(sReturned)), &dwBytes, nullptr,
                          nullptr)
                == 0);
    }
    catch (...)
    {
        return false;
    }
}
static std::vector<iprow> get_ip_addr_table()
{
    try
    {
        static auto get_ip_addr_table = boost::dll::import<GetIpAddrTableLoad>(
            "Iphlpapi.dll", "GetIpAddrTable",
            boost::dll::load_mode::search_system_folders);
        uint32_t dwSize = 0;
        std::vector<iprow> result;
        if (get_ip_addr_table(nullptr, &dwSize, 0) != 0)
        {
            // на случай добавления интерфейса между вызовами
            dwSize += sizeof(mib_ipaddrrow);
            std::vector<char> data(dwSize);
            mib_ipaddrtable* table =
                reinterpret_cast<mib_ipaddrtable*>(data.data());
            if (get_ip_addr_table(table, &dwSize, 0) == 0)
            {
                for (uint32_t i = 0; i < table->dwNumEntries; i++)
                {
                    iprow row;
                    row.address = ntohl(table->table[i].dwAddr);
                    row.netmask = ntohl(table->table[i].dwMask);
                    result.push_back(row);
                }
            }
        }
        return result;
    }
    catch (...)
    {
        return {};
    }
}
}  // namespace nc::detail

#endif

namespace nc::detail
{
inline bool ip_ignored(address_t address)
{
    for (const auto& ignore_if_addr : ip_ignored_interfaces())
    {
        for (const auto& row : get_ip_addr_table())
        {
            auto local = row.address;
            if (local == ignore_if_addr)
            {
                auto mask = row.netmask;
                if ((local & mask) == (address & mask))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
inline std::vector<address_t> get_local_ips()
{
    std::vector<address_t> result;
    for (const auto& row : get_ip_addr_table())
    {
        result.push_back(row.address);
    }
    return result;
}
inline bool is_log_enabled()
{
    const char* enable_log_var = getenv_uni("NC3_ENABLE_LOG");
    if (!enable_log_var)
    {
        return false;
    }
    return std::strcmp(enable_log_var, "1") == 0;
}

}  // namespace nc::detail
