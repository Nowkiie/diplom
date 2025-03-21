#pragma once
#include "node_defs.hpp"
#include <boost/asio/ip/address_v4.hpp>
#include <string>

namespace nc
{
inline std::string address_to_string(address_t address)
{
    boost::asio::ip::address_v4 addr(address);
    boost::system::error_code errc;
    return addr.to_string(errc);
}

}  // namespace nc
