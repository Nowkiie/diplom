#pragma once

#include <cstdint>
#include <string>
#include <limits>
#include <vector>
#include "serializable.hpp"

/*
 * All strings in current protocol using utf8 cp
 */
namespace PelengCommandBufferProtocol
{
using NSTime = int64_t;
using Frequency = int64_t;
using Angle = int;  //angle*10

const unsigned short protocolCode = 19;
const char* const protocolName = "PelengCommandBufferProtocol";

#define CURRENT_PROTOCOL protocolCode

enum MessageType : int
{
    REGISTER,
    REGISTER_TICKET,

    COMMANDLIST_NOTIFY,

    CALC_PLACE,
    CALC_PLACE_TICKET,

    LOCK_COMMAND,
    LOCK_COMMAND_TICKET,

    APPLY_COMMAND,
    UNLOCK_COMMAND,
    SEND_COMMAND_TO_RPN
};

enum ExtBlockStatus : int
{
    ExtBlockStatus_Success = 0,
    ExtBlockStatus_AlreadyBlocked,
    ExtBlockStatus_BufferTimeout,  //таймаут ожидания обработки в буфере
};

enum BlockStatus : int
{
    BlockStatus_Success = 0,
    BlockStatus_Failed,
};

// clang-format off
SERIALIZABLE_STRUCT(PI, 
                    (uint32_t, idPi),
                    (std::string, code));

SERIALIZABLE_STRUCT(RPP,
                    (uint32_t, idRpp),
                    (std::string, rppName));

/*совокупность idRpp + id = Уникальный ключ для всех операции с командой*/
SERIALIZABLE_STRUCT(CommandKey,
                    (uint32_t, idRpp),
                    (int, id));

SERIALIZABLE_STRUCT(Coordinates, 
                    (int, longitude), 
                    (int, latitude));

SERIALIZABLE_STRUCT(PelengsInfo, 
                    (std::vector<Angle>, pelengs),
                    (Coordinates, rppCoords),
                    (uint32_t, idRpp));

SERIALIZABLE_STRUCT(SinglePelengInfo,
                    (Angle, peleng),
                    (Coordinates, rppCoords),
                    (uint32_t, idRpp));

SERIALIZABLE_STRUCT(PlaceInfo, 
                    (Coordinates, coordinate),
                    (std::vector<SinglePelengInfo>, pelengs));

SERIALIZABLE_STRUCT(Command, 
                    (CommandKey, commandId),
                    (Frequency, freq),
                    (Frequency, freqNegDelta),
                    (Frequency, freqPosDelta),
                    (NSTime, timeFrom), 
                    (NSTime, timeTo),
                    (unsigned short, idPi),
                    (std::vector<PlaceInfo>, places),
                    (std::vector<PelengsInfo>, pelengs),
                    (NSTime, stopWaitingTime), /*смещение относительно начала эпохи*/
                    (std::string, blockHost), /*возможно стоит убрать оба поля и отдавать клиентам только свободные команды*/
                    (std::string, blockName));

//сообщения
//клиент->сервер команд
SERIALIZABLE_STRUCT_MESSAGE(ClientRegistrationMessage, REGISTER,
                            (std::string, host),
                            (std::string, name)); //имя клиента

SERIALIZABLE_STRUCT_MESSAGE(BlockCommandMessage, LOCK_COMMAND,
                            (CommandKey, commandId));

SERIALIZABLE_STRUCT_MESSAGE(CancelBlockCommandMessage, UNLOCK_COMMAND,
                            (CommandKey, commandId));

SERIALIZABLE_STRUCT_MESSAGE(ApplyBlockCommandMessage, APPLY_COMMAND,
                            (CommandKey, commandId),
                            (std::vector<Angle>, pelengs));

SERIALIZABLE_STRUCT_MESSAGE(CalcPlaceRequestMessage, CALC_PLACE,
                            (int, requestPlaceId),
                            (std::vector<PelengsInfo>, pelengs));

//сервер команд->клиент
SERIALIZABLE_STRUCT_MESSAGE(ClientRegistrationResultMessage, REGISTER_TICKET,
                            (uint32_t, idLocalRpp),
                            (int, maxPelengCountFromSingleRpp),
                            (std::vector<RPP>, rpps),
                            (std::vector<PI>, pis )); 

SERIALIZABLE_STRUCT_MESSAGE(CommandListMessage, COMMANDLIST_NOTIFY,
                            (std::vector<Command>, commands));

SERIALIZABLE_STRUCT_MESSAGE(BlockCommandResultMessage, LOCK_COMMAND_TICKET,
                            (CommandKey, commandId),
                            (int, status),
                            (int, code));/*int потому что возникает Internal Compiler Error в VS2013 Up5*/

SERIALIZABLE_STRUCT_MESSAGE(CalcPlaceResultMessage, CALC_PLACE_TICKET,
                            (int, requestPlaceId),
                            (std::vector<PlaceInfo>, places));

SERIALIZABLE_STRUCT_MESSAGE(RpnCommandMessage, SEND_COMMAND_TO_RPN,
                            (CommandKey, commandId),
                            (Frequency, freq),
                            (Frequency, freqNegDelta),
                            (Frequency, freqPosDelta),
                            (NSTime, timeFrom),
                            (NSTime, timeTo),
                            (unsigned short, idPi));

// clang-format on
}  // namespace PelengCommandBufferProtocol

#undef CURRENT_PROTOCOL
