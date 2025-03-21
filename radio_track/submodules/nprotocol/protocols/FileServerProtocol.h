#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include <boost/uuid/uuid.hpp>


namespace file_server_protocol
{
    const char* const protocol_name = "file_server_protocol";
    const int protocol_code = 1;

    using id_t = boost::uuids::uuid;

    enum file_server_protocol_codes
    {
        write_file_query_msg,
        write_file_answer_msg,
        read_file_query_msg,
        read_file_answer_msg,
    }

    struct write_file_query
    {
        enum
        {
            message = write_file_query_msg,
            protocol = protocol_code,
        };
        id_t file_id;
        uint64_t query_id;
        uint64_t offset;
        std::vector<char> data;
    };

    struct write_file_answer
    {
        enum
        {
            message = write_file_answer_msg,
            protocol = protocol_code,
        };
        uint64_t query_id;
        bool status;
    };

    struct read_file_query
    {
        enum
        {
            message = read_file_query_msg,
            protocol = protocol_code,
        };
        id_t file_id;
        uint64_t query_id;
        uint64_t offset;
        uint32_t size;
    };

    struct read_file_answer
    {
        enum
        {
            message = read_file_answer_msg,
            protocol = protocol_code,
        };
        uint64_t query_id;
        bool status;
        std::vector<char> data;
    };
}

