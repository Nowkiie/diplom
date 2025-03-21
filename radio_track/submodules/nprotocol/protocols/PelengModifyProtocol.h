#pragma once
#include "serializable.hpp"
#include <string>
#include <vector>


namespace PelengModify
{
    const char * const protocolName = "PelengModify";
    const unsigned short protocolCode = 9;

#define CURRENT_PROTOCOL protocolCode

    enum PelengatorControlMessages
    {
        CLIENT_MODIFY_REQUEST, //изменить команду (команды) (РПА -> СУ)
        CLIENT_MODIFY_ANSWER //ответ с результатом
    };

    typedef long long ns_time_t;

    SERIALIZABLE_STRUCT(Peleng,
        (float, angle),  // угол пеленга
        (unsigned short, quality), // (accuracy) оценка пеленга
        (unsigned short, range),    // дальность (в км)    (для ДАС)
        (bool, isShort),  // ближний/дальний 
        (ns_time_t, timeFrom),  // время начала пеленгования пеленгатором (в нс) UTC
        (ns_time_t, timeTo),  // время окончания пеленгования пеленгатором (в нс) UTC
        (int, freqNegDelta),    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
        (int, freqPosDelta),    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
        (std::vector<unsigned short>, placeAngles),  // углы места
        (std::string, iri) //идентификатор радиоизлучения (заполняется при демодуляции на пеленгаторе)
        );

    SERIALIZABLE_STRUCT(Command,
        (unsigned int, idNk),    // идентификатор команды в СУ (должен быть для внешней и локальной команды)
        (int, idRo),        // идентификатор радиоотряда
        (int, idClient),    // идентификатор клиента в СУ
        (unsigned long long, uniqueId),
        (unsigned int, idPelengator)
        );

    SERIALIZABLE_STRUCT_MESSAGE(CommandModifyRequest, CLIENT_MODIFY_REQUEST,
        (Command, command),
        (std::vector<Peleng>, pelengs)
        );
    SERIALIZABLE_STRUCT_MESSAGE(CommandModifyAnswer, CLIENT_MODIFY_ANSWER,
        (unsigned long long, uniqueId),
        (bool, isSuccess)
        );

#undef CURRENT_PROTOCOL
}
