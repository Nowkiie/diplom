#pragma once

#include <memory>
#include <vector>
#include "serializable.hpp"


/*
    Список открытых вопросов:
    1) нужно ли привязывать пеленг к конкретному пеленгатору
        или достаточно к типу

        под типом понимается совокупность параметров:
        - дальность
        - точность ? (раньше была характеристикой РПП)
        - приоритет ? (раньше была характеристикой РПП)

        * вероятна сиутация, когда один пеленгатор может выдавать пеленга,
            характеристика "дальность" которых различается
          в результате для расчета места можно передавать дальность
            или тип пеленгатора

        Если выбираем привязку к пеленгатору, то необходима система
        синхранизации подключенных пеленгаторов на смежных РПП

        Если выбираем привязку к типу, то необходимо продумать различия
        характеристик разных типов пеленгаторов и при регистрации пеенгатор
        должен оповещать о возможных типах результатов

    2) если к пеленгу будет привязываться конекретный пеленгатор, а не тип,
        то должен быть способ уникально идентифицировать пеленгатор в рамках РПП,
        иначе будет трудно сопоставить пеелнгаторы на разных РПП
        (нужно для привязки пеленга к пеленгатору)
        При этом открывается негативный момент: все РПП будут знать о наборе
        пеленгаторов, работающих на внешних РПП
*/



namespace LANProtocol
{

    const unsigned short cyyProtocolCode = 3; //номер протокола
    const char * const cyyProtocolName = "cyyRpaConnectionNode";

    #define CURRENT_PROTOCOL cyyProtocolCode

    enum MessageType
    {
        PELENGATOR_REGISTER,
        PELENGATOR_REGISTER_ANSWER,
        PELENGATOR_UPDATE_FREQ_RANGES,
        PELENGATOR_UPDATE_PIS,
        PELENGATOR_UPDATE_NAME,
        PELENGATOR_COMMAND,
        PELENGATOR_ANSWER,
        PELENGATOR_VP_LIST,
        PELENGATOR_RPP_LIST,
        PELENGATOR_CLIENT_LIST,
        PELENGATOR_STATUS,
        PELENGATOR_EVENT,
        PELENGATOR_TIME_QUERY,
        PELENGATOR_TIME_ANSWER,
    };


    namespace Pelengator
    {
        // тип пеленгатора
        namespace PelengatorType
        {
            enum Code : int
            {
                rpkBase, //тип не задан
                kvBaseAuto,
                kvMobAuto,
                kvMarArAuto,
                kvMarNarAuto,
                kvMarArManual,
                kvMarNarManual,
                ukvArNarAuto,
                ukvArWideAuto,
                sssArNarAuto,
                dasAuto,
                rpkMax, //максимальное недопустимое значение
            };
        }

        // статус обработки команд

        namespace ResultStatus
        {
            enum Code : int
            {
                Success,            //все хорошо
                UnknownError,       //неизвестная ошибка
                SignalGetError,     //не смогли получить сигнал
                SignalTypeError,    //отсутствует источник сигнала для данной команды
                SignalTimeout,      //превышено время ожидания в очереди - проверяется по таймеру
                CalcPelengError     //ошибка расчета пеленга

            };
        }

        // статус пеленгатора
        //    (может выдаваться асинхронно - без пердварительной отправки команды на пеленгование)
        namespace StatusCode
        {
            enum Code : int
            {
                Success,
                Warning,
                Error,
            };
        }

        //**************************** общие структуры, напрямую не передаются ********************************

        SERIALIZABLE_STRUCT(FreqRange,
            (unsigned long long, from), //начало частотного интервала
            (unsigned long long, to), //конец частотного интервала
            (bool, hasHistory) //флаг наличия истории на этом частотном интервале
            );


        // описание пеленгуемого излучения
        SERIALIZABLE_STRUCT(PI,
            (unsigned short, idPi),   // идентификатор пеленгуемого излучения
            (std::u16string, code),    // уникальный символьный код
            (std::u16string, description)    // дополнительное описание
            );

        // описание вида передачи
        SERIALIZABLE_STRUCT(VP,
            (unsigned short, idVp),    // идентификатор вида передачи
            (unsigned short, idPi),  // идентификатор пеленгуемого излучения
            (std::u16string, code),    // уникальный символьный код
            (std::u16string, description)   // дополнительное описание
            );



        // одиночный результат пеленгования
        SERIALIZABLE_STRUCT(Peleng,
            (float, angle),  // угол пеленга
            (unsigned short, probability), // вероятность попадания в допустимый интервал ошибки, в %
            (unsigned short, range),    // дальность (в км)    (для ДАС)
            (bool, isShort),  // ближний/дальний
            (long long, timeFrom),  // время начала пеленгования пеленгатором (в нс) UTC
            (long long, timeTo),  // время окончания пеленгования пеленгатором (в нс) UTC
            (int, freqNegDelta),    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
            (int, freqPosDelta),    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
            (std::vector<unsigned short>, placeAngles),  // углы места, *10
            (std::string, iri), //идентификатор радиоизлучения (заполняется при демодуляции на пеленгаторе)
            (float, forecastedError) //предсказанная ошибка, в градусах
            );


        // описание рпп
        SERIALIZABLE_STRUCT(Rpp,            // отправляется при подключении и при изменении
            (unsigned int, idRpp), //идентификатор РПП
            (std::u16string, code), //сокращённое (кодовое) название
            (std::u16string, name)  //полное имя РПП
            );

        // описание клиента
        SERIALIZABLE_STRUCT(Client,
            (unsigned int, idClient),
            (std::u16string, name),            // Название приложения (отображать не желательно)
            (std::u16string, source),            // Источник (группировка приложений под одним "правильным" названием
            (std::u16string, post)            // Боевой пост
            );


        //**************************** cообщения РПА -> СУ-У ********************************

        // регистрация пеленгатора в СУ
        SERIALIZABLE_STRUCT_MESSAGE(Register, PELENGATOR_REGISTER,
            (PelengatorType::Code, type),        // тип пеленгатора
            (std::string, host),           // имя машины
            (unsigned short, range)        // дальность пеленгатора (определяется типом)
            );

        SERIALIZABLE_STRUCT_MESSAGE(UpdateFreqRanges, PELENGATOR_UPDATE_FREQ_RANGES,
            (std::vector<FreqRange>, freqRanges)    // список диапазонов частот
            );

        SERIALIZABLE_STRUCT_MESSAGE(UpdatePis, PELENGATOR_UPDATE_PIS,
            (std::vector<unsigned short>, pis)        // список поддерживаемых пеленгуемых излучений
            );

        SERIALIZABLE_STRUCT_MESSAGE(UpdateName, PELENGATOR_UPDATE_NAME,
            (std::u16string, name)        // отображаемое имя
            );

        // результат выполнения команды //для КПР - отдельный протокол, (+возврат idPelengator)
        SERIALIZABLE_STRUCT_MESSAGE(Answer, PELENGATOR_ANSWER,
            // информация для однозначной привязки пеленга к команде
            (unsigned int, idNk),        // идентификатор команды в СУ (должен быть для внешней и локальной команды)
            (int, idRo),        // идентификатор радиоотряда (источник команды)
            (ResultStatus::Code, status),
            (std::vector<Peleng>, pelengs)    // список пеленгов
            );

        SERIALIZABLE_STRUCT_MESSAGE(Status, PELENGATOR_STATUS, //отправляется при подключении и изменении  статуса
            (StatusCode::Code, status, = StatusCode::Success) // статус пеленгатора
            );

        // важное событие на пеленгаторе
        SERIALIZABLE_STRUCT_MESSAGE(Event, PELENGATOR_EVENT,
            (StatusCode::Code, eventType),    //тип события
            (unsigned int, eventCode),    //код события
            (std::u16string, logText)    //текст для вывода пользователю
            );

        // пакет ответа на запрос времени
        SERIALIZABLE_STRUCT_MESSAGE(TimeAnswer, PELENGATOR_TIME_ANSWER,
            (long long, nowTimeDelta) //отклонение времени (local.nowTime - remote.nowTime)
            );

        //**************************** cообщения СУ-У -> РПА ********************************

        //ответ на регистрацию
        SERIALIZABLE_STRUCT_MESSAGE(RegisterAnswer, PELENGATOR_REGISTER_ANSWER,
            (std::string, cyyHost),          // сетевое имя машины СУ-У
            (unsigned int, idPelengator), //идентификатор пеленгатора, сохраняется в файл накопления для изменения пеленга
            (unsigned int, idCurrentRpp), //текущий РПП
            (bool, isOk)
            );


        // отправка команды на пеленгатор
        SERIALIZABLE_STRUCT_MESSAGE(Command, PELENGATOR_COMMAND,
            (unsigned long long, freq),        // центральная частота (Гц)
            (long long, timeFrom),    // время начала пеленгования (в нс) UTC
            (long long, timeTo),        // время окончания пеленгования (в нс) UTC
            (unsigned short, idVp),        // идентификатор видов передач
            (short, sectorFrom),    // начало сектора пеленгования    (от 0)
            (short, sectorTo),    // конец сектора пеленгования    (до 360)
            (int, priority),    // приоритет - чем больше, тем приоритетнее (может быть отрицательный)
            (int, freqNegDelta),    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
            (int, freqPosDelta),    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)

            // информация для однозначной привязки команды
            (unsigned int, idNk),    // идентификатор команды в СУ (должен быть для внешней и локальной команды)
            (int, idRo),        // идентификатор радиоотряда

            // информация для расширения возможностей отображения пеленгатора
            (int, idClient),    // идентификатор клиента в СУ
            (unsigned int, sCom),        // суточный номер команды
            (bool, hide)       // скрывать ли ### результаты и команду на пеленгаторе
            );


        // список видов передач
        SERIALIZABLE_STRUCT_MESSAGE(VPPIList, PELENGATOR_VP_LIST,      // отправляется при подключении и при изменении
            (std::vector<VP>, vps),    // список видов передач
            (std::vector<PI>, pis)    // список пеленгуемых излучений
            );

        SERIALIZABLE_STRUCT_MESSAGE(ClientList, PELENGATOR_CLIENT_LIST,    // отправляется при подключении и при изменении
            (std::vector<Client>, clients)
            );


        SERIALIZABLE_STRUCT_MESSAGE(RppList, PELENGATOR_RPP_LIST,   // отправляется при подключении и при изменении
            (std::vector<Rpp>, rpps) //список всех РПП
            );

        // пакет запроса времени
        SERIALIZABLE_STRUCT_MESSAGE(TimeQuery, PELENGATOR_TIME_QUERY,
            (long long, nowTime) //текущее время отправителя пакета в UTC в НС
            );
    }
}

#undef CURRENT_PROTOCOL
