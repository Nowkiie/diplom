#pragma once
#include "serializable.hpp"
#include <string>
#include <vector>
#include <map>

namespace DemodServiceProtocol
{
const char* const protocolName = "DemodService";
const unsigned short protocolCode = 11;
typedef int64_t ns_time_t;
typedef int64_t frequency_t;
const ns_time_t second_ns = 1000000000ll;
#define CURRENT_PROTOCOL protocolCode

typedef long long id_t;

enum DemodServiceMessages
{
    DEMOD_REQUEST,
    DEMOD_REQUEST_RESULT,
    DEMOD_SERVER_INFO,
    DEMOD_STATUS,
    DEMOD_SPECTR,
    DEMOD_SESSION_STATUS,

};

/**
* \brief Результат установки указания на демодуляцию
*/
enum RequestResultType : unsigned char
{
    RequestSuccess,   //< Указание успешно установлено
    RequestFail,      //< Указанеи неустановлено
    WrongParameters,  //< Указаны неверные параметры
    TaskProcessed,
    //    ServerHang        //< Сервер повис похоже
};
/**
* \brief Статус обработки сервера
*/
enum ServerReadyType : unsigned char
{
    ReadyForProcess,  //< Готов к обработке

};

/**
* \brief способ пеленгования
*/
enum PelengType : unsigned char
{
    pelTypeRps = 0,  //< через РПС
    pelTypeExpress,  //< локальный пеленг
    pelTypeNone,     //< локальный пеленг

};
/**
* \brief статус сессии
*/
enum SessionStatysType : unsigned char
{
    sessionStart = 0,
    sessionStop,

};
/**
* \brief Режим установки номинала
*/
enum ReceiveMode : unsigned char
{
    amMode = 0,  //центр спектра
    usbMode,
    lsbMode

};
// clang-format off

//! массив папаметров и значений
typedef std::map<std::string, std::string> ParamsArray;
//Клиентская часть

//! Указание на демодуляцию
SERIALIZABLE_STRUCT_MESSAGE(
    Request, DEMOD_REQUEST, (id_t, taskId),  //< Уникальный номер указания
    (std::string, demodulator),              //< Имя демодулятора
    (ParamsArray, demodParams),              //< Параметры демодулятора
    (std::string, radionet),                 //< Имя демодулятора
    (frequency_t, frequency),                //< Частота
    (id_t, ursId),                           //<id-Сервера УРС
    (ns_time_t, startTime, = 0),             //< время начала
    (PelengType, pelengType, = pelTypeRps),  //< тип пеленгования
    (ns_time_t, pelengInterval, = 100 * second_ns),  //< Интервал пеленгования
    (ns_time_t, monitoringTime, = second_ns),        //< Интервал слежения
    (ns_time_t, rollbackTime, = second_ns),       //< Интервал отката в историю
    (ns_time_t, waitForRepeatTime, = second_ns),  //< Ожидание повтора
    (ns_time_t, interceptTime, = second_ns * 60 * 60),  //< Интервал перехвата
    (ReceiveMode, receiveMode, = amMode)                //< Интервал перехвата
);

// серверная часть

//! Уведомление сообщение информации о себе
SERIALIZABLE_STRUCT_MESSAGE(ServerInfo, DEMOD_SERVER_INFO,
                            (std::vector<std::string>, demodulators),
                            (std::string, name));

//! Уведомление клиентов о готовности поработать
SERIALIZABLE_STRUCT_MESSAGE(ServerReady, DEMOD_STATUS,
                            (ServerReadyType, ready,
                             = ReadyForProcess));  //< Свободен ли сервер

//! Ответ от сервера на попытку установить указание на демодуляцию
SERIALIZABLE_STRUCT_MESSAGE(RequestResult, DEMOD_REQUEST_RESULT,
                            (id_t, taskId),  //< Уникальный номер указания
                            (RequestResultType,
                             result));  //< Результат постановки задания

//! Ответ от сервера на попытку установить указание на демодуляцию
SERIALIZABLE_STRUCT_MESSAGE(SpectrData, DEMOD_SPECTR,
                            (id_t, task_id),  //< Уникальный номер указания
                            (std::vector<unsigned char>,
                             spectr));  //< Результат постановки задания

//! Ответ от сервера на попытку установить указание на демодуляцию
SERIALIZABLE_STRUCT_MESSAGE(SessionStatus, DEMOD_SESSION_STATUS,
                            (id_t, task_id),  //< Уникальный номер указания
                            (SessionStatysType,
                             status));  //< Результат постановки задания

// clang-format on

#undef CURRENT_PROTOCOL
}  // namespace DemodServiceProtocol
