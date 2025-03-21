#pragma once

#include <string>
#include <vector>

const unsigned short test_protocol_code = 1;

const char* const test_procol_name = "test_protocol";

enum test_protocol_messages
{
    client_to_server_message = 1,
    server_to_client_message
};

struct child_object
{
    int x = 1;
    std::vector<std::vector<std::string>> names[2];
    std::vector<int> namew;
};

struct client_to_server_structure
{
    enum
    {
        protocol = test_protocol_code,
        message = client_to_server_message
    };
    child_object child;
    std::string echo;
    int array[4];
    std::vector<child_object> childs;
};

struct server_to_client_structure
{
    enum
    {
        protocol = test_protocol_code,
        message = server_to_client_message
    };
    std::string echo;
};
