#pragma once

#include <string>
#include <limits>
#include <vector>
#include "serializable.hpp"

namespace CrpaDiagnosticProtocol
{
const unsigned short crpa_diagnostic_protocol_code = 14;

const char * const crpa_diagnostic_protocol_name = "crpa_diagnostic_protocol";

constexpr int invalidCoordinate = std::numeric_limits<int>::min();
constexpr int64_t invalidTimeMark = std::numeric_limits<int64_t>::min();
constexpr float invalidPel = -1.f;

#define CURRENT_PROTOCOL crpa_diagnostic_protocol_code

enum external_command_protocol_messages
{
    command_message = 1,
    answer_message,
    pel_info_message,
    command_result_message
};

enum peleng_result_status : int
{
    Success,            //все хорошо
    SignalGetError,     //не смогли получить сигнал
    SignalFreqError,    //не смогли найти источник сигнала, проходящий по частоте,
    SignalTimeError,    //не смогли найти источник сигнала, проходящий по времени,
    SignalTimeout,      //превышено время ожидания в очереди - проверяется по таймеру
    CalcPelengError,    //ошибка расчета пеленга
    CommandCheckError   //неверная команда
};

//КОМАНДА НА ПЕЛЕНГОВАНИЕ
SERIALIZABLE_STRUCT_MESSAGE(PelCommand, command_message,
    (unsigned long long, uniqueId), //идентификатор команды для привязки к ней ответа
    (unsigned long long, frequency),//центральная частота (Гц)
    (int, freqNegDelta),            //вниз от frequency
    (int, freqPosDelta),            //вверх frequency
    (long long, startTime),         //время начала пеленгования
    (long long, timeOfPel),         //время пеленгования (длительность)
    (unsigned short, idVp),         //идентификатор видов передач
    (unsigned short, idPi),         //идентификатор пеленгуемого излучения
    (int, realLongitude, =invalidCoordinate),           //долгота ожидаемая(секунды)
    (int, realLatitude, =invalidCoordinate),            //широта ожидаемая(секунды)
    (float, realPeleng, = -1),      //ожидаемый пеленг (юзается только если нет координат)
    (std::string, objectType),      //тип объекта(корабль, самолет, наземный и т. д.)
    (std::string, callsign)         //позывной объекта для идентификации
    //приоритет отпрравке координат
    );

//ОДИНОЧНЫЙ РЕЗУЛЬТАТ ПЕЛЕНГОВАНИЯ
SERIALIZABLE_STRUCT(Peleng,
    (float, angle),                 // угол пеленга
    (unsigned short, range),        // дальность (в км)    (для ДАС)
    (long long, timeFrom),          // время начала пеленгования пеленгатором (в нс) UTC
    (long long, timeTo),            // время окончания пеленгования пеленгатором (в нс) UTC
    (int, freqNegDelta),            // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
    (int, freqPosDelta),            // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
    (std::vector<unsigned short>, placeAngles)  // углы места
    );

SERIALIZABLE_STRUCT(PelengatorInfoStruct,
    (uint64_t, freqStart),
    (uint64_t, freqStop),
    (bool, hasHistory)
);

//ОТВЕТ НА КОМАНДУ ПЕЛЕНГОВАНИЯ: СОДЕРЖИТ МАССИВ ОДИНОЧНЫХ ПЕЛЕНГОВ
SERIALIZABLE_STRUCT_MESSAGE(PelAnswer, answer_message,
    (unsigned long long, uniqueId),//идентификатор команды для привязки к ней ответа
    (peleng_result_status, status),//статус обработки команды (код ошибки)
    (std::vector<Peleng>, pelengs) //список пеленгов
    );

SERIALIZABLE_STRUCT_MESSAGE(PelengatorInfo, pel_info_message,
    (std::vector<PelengatorInfoStruct>, pelengatorInfoList), //
    (std::vector<int>,  piList)
);

SERIALIZABLE_STRUCT(Coordinate,
    (int, latitude, =invalidCoordinate), //широта в секундах
    (int, longitude, =invalidCoordinate) //долгота в секундах
);

SERIALIZABLE_STRUCT(ChannelMeasure,
    (float, dphase), // разности фаз, в радианах
    (float, amplitude) // относительная амплитуда
);

//ДИАГНОСТИЧЕСКАЯ КОМАНДА С РЕЗУЛЬТАТАМИ
SERIALIZABLE_STRUCT_MESSAGE(DiagnosticMessage, command_result_message,
    (uint64_t, frequency),                              //центральная частота (Гц)
    (std::string, callsign),                            //позывной объекта для идентификации
    (std::string, objectType),                          //тип объекта (или тип идентификатора)
    (int64_t, timeMark, =invalidTimeMark),              //временная метка, нс
    (float, peleng_raw, =invalidPel),                   //пеленг(без учёта курса) + магн. склонение° (в диапазоне 0..360)
    (std::vector<ChannelMeasure>, channelsMeasurement), //измерения по каналам (размером channels)
    (Coordinate, objectCoordinate)                      //координаты объекта в секундах
    );
}

#undef CURRENT_PROTOCOL
