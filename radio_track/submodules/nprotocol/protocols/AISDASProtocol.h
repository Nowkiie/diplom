#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "serializable.hpp"

namespace AISDASProtocol
{
    const char* const protocolName = "AIS_DAS_results_protocol";
    const unsigned short protocolCode = 15;

    // все строки в протоколе в utf8

    enum MessageType
    {
        messageRegister = 0,
        messageQuery,
        messageAnswer,
        messageSubscribe,
    };

    struct Coordinates
    {
        float longitude{};  // долгота (градусы)
        float latitude{};   // широта (градусы)
    };

    struct AIS_Dimension
    {
        int16_t sizeA{};
        int16_t sizeB{};
        int16_t sizeC{};
        int16_t sizeD{};
    };

    enum InterestStatus : int
    {
        notInteresting = -1,     // объект не интересен
        neutral = 0,              // данные об интересности объекта отсутствуют
        interesting = 1           // объект интересен
    };

    struct AIS_Message
    {
        int64_t time{};  // в секундах с начала эпохи
        std::optional<Coordinates> coordinates;
        std::optional<int32_t> speed;    // скорость (1/10 узла)
        std::optional<float> course;     // курс /куда движется/ (градусы)
        std::optional<int32_t> rot;      // скорость изменения курса (градусы/мин)
        std::optional<int32_t> draught;  // осадка (1/10 метра)
        std::optional<float> heading;  // направление /куда смотрит нос/ (градусы)
        std::optional<int64_t> ETA;  // время прибытия (в секундах с начала эпохи)
        std::optional<int32_t> altitude;  // высота (метры)
        std::optional<int32_t> status;    // статус (по стандарту AIS)
    };

    enum class AIS_Type : int
    {
        ship = 1,
        base,
        plane
    };

    struct AIS_Object
    {
        int32_t MMSI{};
        AIS_Type type{};                         // тип
        std::optional<AIS_Dimension> dimension;  // размеры (по стандарту AIS)
        std::optional<int32_t> IMO;              // номер IMO
        std::string name;                        // название
        std::string callsign;                    // позывной
        InterestStatus interest;
        std::vector<AIS_Message> messages;
        std::string countryCode; // Государственная принадлежность (двухсимвольный код)
    };

    struct DAS_Message
    {
        int64_t time{};
        std::optional<Coordinates> coordinates;
        std::optional<int32_t> altitude;  // Высота (feet - футы)
        std::optional<int32_t> vrate;     // вертикальная скорость (feet/min)
        std::optional<float> speed;       // скорость (узлы)
        std::optional<float> course;      // курс (градусы)
    };

    struct DAS_Object
    {
        int32_t ICAO{};
        int32_t squawk{};
        std::string flight;   // рейс (позывной)
        std::string comment;  // комментарий (справочник)
        std::string regNum;   // регистрационный номер
        std::string airType;  // тип ВС  (справочник)
        std::string model;    // модель ВС (справочник)
        std::string owner;    // собственник ВС  (справочник)
        InterestStatus interest;
        std::vector<DAS_Message> messages;
        std::string countryCode; // Государственная принадлежность (двухсимвольный код)
    };

    struct ACARS_Message
    {
        int64_t time{};
        std::optional<Coordinates> coordinates;
        std::string textMessage;
    };

    struct ACARS_Object
    {
        int32_t ICAO{};
        std::string flight;   // рейс (позывной)
        std::string comment;  // комментарий (справочник)
        std::string regNum;   // регистрационный номер
        std::string airType;  // тип ВС  (справочник)
        std::string model;    // модель ВС (справочник)
        std::string owner;    // собственник ВС  (справочник)
        InterestStatus interest;
        std::vector<ACARS_Message> messages;
        std::string countryCode; // Государственная принадлежность (двухсимвольный код)
    };



    struct RepeatPeriod
    {
        int periodValue; // среднее значение ППИ (мкс)
        int periodWidth; // ширина интервала ППИ (мкс)
    };

    enum class RadarScanType : int
    {
        undefined = 0, // не установлен
        forward = 1, // по часовой стрелке
        backward = 2, // против часовой стрелки
        sector = 3, // секторный обзор
    };

    struct RADAR_Message
    {
        int64_t time{};  // в секундах с начала эпохи
        std::optional<Coordinates> coordinates;
        std::optional<int32_t> altitude;  // Высота (в метрах)
        bool syncted;
    };

    struct RADAR_Object
    {
        std::optional<float> rotateSpeed; // скорость вращения (об\мин)
        std::vector<RepeatPeriod> periods;
        std::string ident; // идентификатор передаваемый в пакетах режима S
        std::string modeList; // cписок запрашиваемых режимов
        std::string model;    // модель  РЛЗ
        RadarScanType scanType;  // тип сканирования пространства
        std::optional<float> sectorCenter; // Центр сектора обзора радиолокационного запросчика  в градусах 
        std::optional<float> sectorWidth; // Ширина сектора обзора РЛЗ в градусах 
        InterestStatus interest;
        std::vector<RADAR_Message> messages;
    };

    struct QueryFlags
    {
        bool queryAis{};
        bool queryDas{};
        bool queryAcars{};
        bool queryRadar{};
    };

    // сообщение с информацией (сервер -> клиент)
    struct MessageRegister
    {
        enum
        {
            message = messageRegister,
            protocol = protocolCode,
        };
        std::string host;            //имя машины
        std::string name;            //имя программы
        QueryFlags availableSource;  // доступные источники данных
    };

    // запрос данных за выбранный интервал (клиент -> сервер)
    struct MessageQuery
    {
        enum
        {
            message = messageQuery,
            protocol = protocolCode,
        };
        uint64_t queryId;
        uint64_t beginTime;      // UTC в секундах
        uint64_t endTime;        // UTC в секундах
        QueryFlags queryParams;  // флаги запрашиваемых данных
    };

    // ответ с данными (сервер -> клиент)
    struct MessageAnswer
    {
        enum
        {
            message = messageAnswer,
            protocol = protocolCode,
        };
        uint64_t queryId{};  //для ответов по подписке заполнено 0
        std::vector<AIS_Object> aisObjects;
        std::vector<DAS_Object> dasObjects;
        std::vector<ACARS_Object> acarsObjects;
        std::vector<RADAR_Object> radarObjects;
    };

    // управление подпиской (клиент -> сервер)
    struct MessageSubscribe
    {
        enum
        {
            message = messageSubscribe,
            protocol = protocolCode,
        };
        QueryFlags subscribeParams;  // если флаг установлен, подписка активируется
    };

}  // namespace AISDASProtocol
