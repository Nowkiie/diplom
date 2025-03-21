#pragma once

#include <memory>
#include <vector>
#include <optional>

namespace RPSMailProtocol
{
const char* const protocolName = "RPS_Mail_Protocol";
const unsigned short protocolCode = 22;

// все строки в протоколе в utf8

enum MessageType
{
    CLIENT_REGISTER = 0,
    RPS_MESSAGE,
    RPS_FILE_READY,
    RPS_FILE_QUERY,
    RPS_FILE_SENT,
    RPS_MESSAGE_COMMIT,
    RPS_FILE_FAULT,
    RPS_FILE_FAULT_COMMIT,
    RPS_MESSAGE_READ,
    RPS_MESSAGE_READ_COMMIT,
};

// сообщение с информацией клиента
struct AbonentRegister
{
    enum
    {
        message = CLIENT_REGISTER,
        protocol = protocolCode,
    };

    std::string id;    //id машины ("номер рпп":"имя компьютера")
    std::string rpp;   //имя рпп
    std::string name;  //данное пользователем имя поста
};

// сообщение с текстом сообщения
struct RPSMessage
{
    enum
    {
        message = RPS_MESSAGE,
        protocol = protocolCode,
    };
    int64_t id;        //id сообщения
    std::string text;  //текст сообщения
};

// сообщение о доставке
struct RPSMessageCommit
{
    enum
    {
        message = RPS_MESSAGE_COMMIT,
        protocol = protocolCode,
    };
    int64_t id;  //id сообщения
};

// готовность передачи файла
struct RPSFileReady
{
    enum
    {
        message = RPS_FILE_READY,
        protocol = protocolCode,
    };
    int64_t id;            //id сообщения
    std::string filename;  //имя файла
    int64_t fileSize;      //Размер всего файла
};

// запрос на получение части файла
struct RPSFileQuery
{
    enum
    {
        message = RPS_FILE_QUERY,
        protocol = protocolCode,
    };
    int64_t id;          //id сообщения
    int64_t fileOffset;  //смещение в файле (существующий размер)
    int64_t partSize;    //размер необходимого блока (под вопросом)
};

// передача части файла
struct RPSFileSent
{
    enum
    {
        message = RPS_FILE_SENT,
        protocol = protocolCode,
    };
    int64_t id;                    //id сообщения
    int64_t fileOffset;            //смещение в файле (существующий размер)
    std::vector<char> fileVector;  //вектор для передачи файла
};

// отмена передача файла
struct RPSFileFault
{
    enum
    {
        message = RPS_FILE_FAULT,
        protocol = protocolCode,
    };
    int64_t id;                    //id сообщения
};

// сообщение о доставке отмены передачи файла
struct RPSFileFaultCommit
{
    enum
    {
        message = RPS_FILE_FAULT_COMMIT,
        protocol = protocolCode,
    };
    int64_t id;                    //id сообщения
};

// сообщение прочитано
struct RPSMessageRead
{
    enum
    {
        message = RPS_MESSAGE_READ,
        protocol = protocolCode,
    };
    int64_t id;                    //id сообщения
};

// подтверждение о принятии информации что сообщение прочитано
struct RPSMessageReadCommit
{
    enum
    {
        message = RPS_MESSAGE_READ_COMMIT,
        protocol = protocolCode,
    };
    int64_t id;                    //id сообщения
};

}  // namespace RPSMailProtocol
