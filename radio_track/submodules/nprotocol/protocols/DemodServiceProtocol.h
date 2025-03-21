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
* \brief ��������� ��������� �������� �� �����������
*/
enum RequestResultType : unsigned char
{
    RequestSuccess,   //< �������� ������� �����������
    RequestFail,      //< �������� �������������
    WrongParameters,  //< ������� �������� ���������
    TaskProcessed,
    //    ServerHang        //< ������ ����� ������
};
/**
* \brief ������ ��������� �������
*/
enum ServerReadyType : unsigned char
{
    ReadyForProcess,  //< ����� � ���������

};

/**
* \brief ������ ������������
*/
enum PelengType : unsigned char
{
    pelTypeRps = 0,  //< ����� ���
    pelTypeExpress,  //< ��������� ������
    pelTypeNone,     //< ��������� ������

};
/**
* \brief ������ ������
*/
enum SessionStatysType : unsigned char
{
    sessionStart = 0,
    sessionStop,

};
/**
* \brief ����� ��������� ��������
*/
enum ReceiveMode : unsigned char
{
    amMode = 0,  //����� �������
    usbMode,
    lsbMode

};
// clang-format off

//! ������ ���������� � ��������
typedef std::map<std::string, std::string> ParamsArray;
//���������� �����

//! �������� �� �����������
SERIALIZABLE_STRUCT_MESSAGE(
    Request, DEMOD_REQUEST, (id_t, taskId),  //< ���������� ����� ��������
    (std::string, demodulator),              //< ��� ������������
    (ParamsArray, demodParams),              //< ��������� ������������
    (std::string, radionet),                 //< ��� ������������
    (frequency_t, frequency),                //< �������
    (id_t, ursId),                           //<id-������� ���
    (ns_time_t, startTime, = 0),             //< ����� ������
    (PelengType, pelengType, = pelTypeRps),  //< ��� ������������
    (ns_time_t, pelengInterval, = 100 * second_ns),  //< �������� ������������
    (ns_time_t, monitoringTime, = second_ns),        //< �������� ��������
    (ns_time_t, rollbackTime, = second_ns),       //< �������� ������ � �������
    (ns_time_t, waitForRepeatTime, = second_ns),  //< �������� �������
    (ns_time_t, interceptTime, = second_ns * 60 * 60),  //< �������� ���������
    (ReceiveMode, receiveMode, = amMode)                //< �������� ���������
);

// ��������� �����

//! ����������� ��������� ���������� � ����
SERIALIZABLE_STRUCT_MESSAGE(ServerInfo, DEMOD_SERVER_INFO,
                            (std::vector<std::string>, demodulators),
                            (std::string, name));

//! ����������� �������� � ���������� ����������
SERIALIZABLE_STRUCT_MESSAGE(ServerReady, DEMOD_STATUS,
                            (ServerReadyType, ready,
                             = ReadyForProcess));  //< �������� �� ������

//! ����� �� ������� �� ������� ���������� �������� �� �����������
SERIALIZABLE_STRUCT_MESSAGE(RequestResult, DEMOD_REQUEST_RESULT,
                            (id_t, taskId),  //< ���������� ����� ��������
                            (RequestResultType,
                             result));  //< ��������� ���������� �������

//! ����� �� ������� �� ������� ���������� �������� �� �����������
SERIALIZABLE_STRUCT_MESSAGE(SpectrData, DEMOD_SPECTR,
                            (id_t, task_id),  //< ���������� ����� ��������
                            (std::vector<unsigned char>,
                             spectr));  //< ��������� ���������� �������

//! ����� �� ������� �� ������� ���������� �������� �� �����������
SERIALIZABLE_STRUCT_MESSAGE(SessionStatus, DEMOD_SESSION_STATUS,
                            (id_t, task_id),  //< ���������� ����� ��������
                            (SessionStatysType,
                             status));  //< ��������� ���������� �������

// clang-format on

#undef CURRENT_PROTOCOL
}  // namespace DemodServiceProtocol
