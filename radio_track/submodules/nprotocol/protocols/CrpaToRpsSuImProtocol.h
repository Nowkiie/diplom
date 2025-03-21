#pragma once

#include <string>
#include <vector>
#include "serializable.hpp"

namespace CrpaToRpsSuImProtocol
{
    const char * const crpaToRpsSuImProtocolName = "CrpaToRpsSuImProtocol";
    const unsigned short crpaToRpsSuImProtocolCode = 8;

#define CURRENT_PROTOCOL crpaToRpsSuImProtocolCode

    enum CrpaToRpsSuImMessages
    {
        PELENG,  // Отправка пеленга
    };

    SERIALIZABLE_STRUCT(OnePeleng,
        (int, peleng), // Пеленг
        (int, anglePlace) // угол-место
    );

    SERIALIZABLE_STRUCT_MESSAGE(Peleng, PELENG,
        (int, sCom)  ,   // суточный номер команды
        (int, idNk)  ,   // идентификационный номер команды
        (int, idRo)  ,   // идентификатор РПП источника команды
        (int, freq) ,    // частота
        (int, pi)    ,    // ПИ
        (std::vector<OnePeleng>, pelengs)     //список пеленгов
    );
}

#undef CURRENT_PROTOCOL
