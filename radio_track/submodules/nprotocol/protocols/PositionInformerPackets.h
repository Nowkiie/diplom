#pragma once

#include "serializable.hpp"
#include <string>
#include <vector>

namespace LANProtocol
{
    namespace Navigation
    {
        const char * const positionInformerProtocolName = "ManagerNS";
        const unsigned short positionInformerProtocolCode = 2;

#define CURRENT_PROTOCOL positionInformerProtocolCode

        enum EPositionInformerMessages
        {
            NAVIGATION_REGISTER,
            NAVIGATION_REGISTER_ANSWER,
            NAVIGATION_QUERY,
            NAVIGATION_ANSWER,
        };


        //информация о курсе
        SERIALIZABLE_STRUCT(NavigationCource,
            (long long, timeFrom), //время изменения (в мс) UTC
            (int, cource) //курс в секундах, для получения градусов поделить на 3600
            );
        //информация о координатах
        SERIALIZABLE_STRUCT(NavigationCoordinate,
            (long long, timeFrom), //время изменения (в мс) UTC
            (int, longitude),//долгота
            (int, latitude) //широта
            );

        //регистрация
        SERIALIZABLE_STRUCT_MESSAGE(Register, NAVIGATION_REGISTER,
            (std::u16string, name), //имя приложения
            (std::string, host) //имя компьютера клиента навигации
            );

        //ответ на запрос регистрации
        SERIALIZABLE_STRUCT_MESSAGE(RegisterAnswer, NAVIGATION_REGISTER_ANSWER,
            (std::string, host), //имя компьютера сервера навигации
            (bool, isOk)
            );

        //запрос истории навигации
        //на запрос нужно вернуть все события в интервале [timeFrom, timeTo)
        SERIALIZABLE_STRUCT_MESSAGE(NavigationQuery, NAVIGATION_QUERY,
            (long long, timeFrom),    // время начала запроса исторри (в мс) UTC
            (long long, timeTo)        // время окончания запроса истории (в см) UTC
            );
  
        //ответ на запрос истории навигации(отправляется на запрос) и текущие изменения курса и координат (отправляются при изменении)
        SERIALIZABLE_STRUCT_MESSAGE(NavigationAnswer, NAVIGATION_ANSWER,
            (std::vector<NavigationCource>, cources), //история курса
            (std::vector<NavigationCoordinate>, coordinates) //история координат
            );

    }
}

#undef CURRENT_PROTOCOL