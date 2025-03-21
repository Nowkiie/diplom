#pragma once
#include "serializable.hpp"
#include <string>
#include <vector>
#include <optional>

namespace PelengatorControl
{
    const char * const protocolName = "PelengatorControl";
    const unsigned short protocolCode = 4;

#define CURRENT_PROTOCOL protocolCode

    enum PelengatorControlMessages
    {
        PELENGATOR_REGISTER, //информация о пеленгаторе (для выбора) (РПА -> КРП)
        PELENGATOR_LIST_INSERT, //добавить записи в список файлов (РПА -> КРП)
        PELENGATOR_LIST_REMOVE, //удалить записи из списка файлов (РПА -> КРП)
        PELENGATOR_LIST_UPDATE, //изменить записи в списке файлов (РПА -> КРП)
        PELENGATOR_FILE_GET, //запрос файла (КРП -> РПА)
        PELENGATOR_FILE_ANSWER, //ответ с файлом (РПА -> КРП)
        PELENGATOR_VP_LIST, //список видов передач (РПА -> КРП)
        PELENGATOR_RPP_LIST, //список РПП (РПА -> КРП)
        PELENGATOR_MODIFY, //изменить команду (команды) (КРП -> РПА)
        PELENGATOR_LIST_SUBSCRIBE, //подписка на список файлов (КРП -> РПА)
        PELENGATOR_SEARCH_QUERY, // запрос поиска файла (КРП -> РПА)
        PELENGATOR_SEARCH_ANSWER, // ответ на поиск файла (РПА -> КРП)
    };

    typedef long long ns_time_t;

    SERIALIZABLE_STRUCT(Peleng,
        (float, angle),  // угол пеленга
        (unsigned short, probability), // вероятность попадания в допустимый интервал ошибки, в %
        (unsigned short, range),    // дальность (в км)    (для ДАС)
        (bool, isShort),  // ближний/дальний 
        (ns_time_t, timeFrom),  // время начала пеленгования пеленгатором (в нс) UTC
        (ns_time_t, timeTo),  // время окончания пеленгования пеленгатором (в нс) UTC
        (int, freqNegDelta),    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
        (int, freqPosDelta),    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
        (std::vector<unsigned short>, placeAngles),  // углы места
        (std::string, iri), //идентификатор радиоизлучения (заполняется при демодуляции на пеленгаторе)
        (float, forecastedError) //предсказанная ошибка, в градусах
        );

    SERIALIZABLE_STRUCT(Command,
        (unsigned long long, freq),        // центральная частота (Гц)
        (ns_time_t, timeFrom),    // время начала пеленгования (в нс) UTC
        (ns_time_t, timeTo),        // время окончания пеленгования (в нс) UTC
        (unsigned short, idVp),        // идентификатор видов передач
        (short, sectorFrom),    // начало сектора пеленгования    (от 0)
        (short, sectorTo),    // конец сектора пеленгования    (до 360)
        (int, freqNegDelta),    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
        (int, freqPosDelta),    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)

                                // информация для однозначной привязки команды
        (unsigned int, idNk),    // идентификатор команды в СУ (должен быть для внешней и локальной команды)
        (int, idRo),        // идентификатор радиоотряда

                            // информация для расширения возможностей отображения пеленгатора
        (int, idClient),    // идентификатор клиента в СУ
        (unsigned int, sCom),        // суточный номер команды
        (unsigned long long, uniqueId),
        (unsigned int, idPelengator)
        );

    SERIALIZABLE_STRUCT(ListEntry,
        (Command, command),
        (std::vector<Peleng>, pelengs),
        (std::string, fileName) 
        );


    // описание вида передачи
    SERIALIZABLE_STRUCT(VP,
        (unsigned short, idVp),    // идентификатор вида передачи
        (unsigned short, idPi),  // идентификатор пеленгуемого излучения
        (std::u16string, code),    // уникальный символьный код
        (std::u16string, description)   // дополнительное описание
    );

    // описание рпп
    SERIALIZABLE_STRUCT(Rpp,            // отправляется при подключении и при изменении
        (unsigned int, idRpp), //идентификатор РПП
        (std::u16string, code), //сокращённое (кодовое) название
        (std::u16string, name)  //полное имя РПП
    );


    SERIALIZABLE_STRUCT_MESSAGE(Register, PELENGATOR_REGISTER,
        (std::string, hostName),
        (std::u16string, pelengatorName),
        (int, idCurrentRpp)
        );

    SERIALIZABLE_STRUCT_MESSAGE(ListAnswerInsert, PELENGATOR_LIST_INSERT,
        (std::vector<ListEntry>, fileList)
    );

    SERIALIZABLE_STRUCT_MESSAGE(ListAnswerRemove, PELENGATOR_LIST_REMOVE,
        (std::vector<ListEntry>, fileList)
    );

    SERIALIZABLE_STRUCT_MESSAGE(ListAnswerUpdate, PELENGATOR_LIST_UPDATE,
        (std::vector<ListEntry>, fileList)
    );

    SERIALIZABLE_STRUCT_MESSAGE(FileGet, PELENGATOR_FILE_GET,
        (std::string, fileName)
    );

    SERIALIZABLE_STRUCT_MESSAGE(FileAnswer, PELENGATOR_FILE_ANSWER,
        (std::string, fileName),
        (std::vector<char>, fileData)
    );
    // список видов передач
    SERIALIZABLE_STRUCT_MESSAGE(VPList, PELENGATOR_VP_LIST,      // отправляется при подключении и при изменении
        (std::vector<VP>, vp)    // список видов передач
    );

    SERIALIZABLE_STRUCT_MESSAGE(RppList, PELENGATOR_RPP_LIST,   // отправляется при подключении и при изменении
        (std::vector<Rpp>, rpps) //список всех РПП
    );

    SERIALIZABLE_STRUCT_MESSAGE(ListModify, PELENGATOR_MODIFY,
        (std::vector<ListEntry>, fileList)
    );

    SERIALIZABLE_STRUCT_MESSAGE(ListSubscribe, PELENGATOR_LIST_SUBSCRIBE,
        (bool, fileListEnable)
    );

    // запрос на поиск файлов, все установленные параметры объединяются по "И"
    SERIALIZABLE_STRUCT_MESSAGE(SearchQuery, PELENGATOR_SEARCH_QUERY,
        (uint64_t, searchId), // будет передан в ответе
        (std::optional<unsigned long long>, frequency),
        (std::optional<unsigned int>, sCom),
        (std::optional<ns_time_t>, intervalBegin),
        (std::optional<ns_time_t>, intervalEnd),
        (std::optional<int>, idRo),
        (std::optional<unsigned short>, idVp),
        (std::optional<unsigned long long>, uniqueId)
    );

    SERIALIZABLE_STRUCT_MESSAGE(SearchAnswer, PELENGATOR_SEARCH_ANSWER,
        (uint64_t, searchId),
        (std::vector<ListEntry>, fileList)
    );


#undef CURRENT_PROTOCOL
}
