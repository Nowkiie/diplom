#pragma once

#include "serializable.hpp"
#include <stdint.h>
#include <string>
#include <vector>

namespace WideBandSignalDetector
{
const char* const protocolPrefix = "WideBandDetector_";
const unsigned short protocolCode = 13;
#define CURRENT_PROTOCOL protocolCode
typedef int64_t Frequency; //< Частота
typedef int64_t NSTime; //< Время в наносекундах с начала эпохи(ns_time_t)

//Допустимые сообщения
enum Messages
{
    MSG_CURRENT_TASK,
    MSG_SET_TASK,
    MSG_DETECTION_RESULT,
    MSG_VP_LIST
};
// clang-format off

// ТИПЫ ДАННЫХ

//! Диапазон частот
SERIALIZABLE_STRUCT(FrequencyDiapason,                
    (Frequency, frequencyStart),
    (Frequency, frequencyStop)
);

//! массив диапазонов (для краткости)
typedef std::vector<FrequencyDiapason> DiapasonArray;


//! массив диапазонов для указаного ВП
SERIALIZABLE_STRUCT(VPDiapasons,
    (std::string, vpName),
    (DiapasonArray, diapasons)
);
typedef std::vector<VPDiapasons> VPDiapasonsArray;
typedef std::vector<Frequency> FrequenciesArray;

//! массив частот для указаного ВП
SERIALIZABLE_STRUCT(VPFrequencies,
    (std::string, vpName),
    (FrequenciesArray, frequencies)  
);
typedef std::vector<VPFrequencies> VPFrequenciesArray;

//! СООБЩЕНИЯ

//Клиент->Обнаружитель

//! Новое задание
SERIALIZABLE_STRUCT_MESSAGE(NewTaskMessage, MSG_SET_TASK,
    (VPDiapasonsArray, taskArray),
    (DiapasonArray, ignoredDiapasons)
);

//Обнаружитель->Клиент

//! Текущее задание
SERIALIZABLE_STRUCT_MESSAGE(CurrentTaskMessage, MSG_CURRENT_TASK,
    (VPDiapasonsArray, taskArray),
    (DiapasonArray, ignoredDiapasons)
);

//! информация о сервере
SERIALIZABLE_STRUCT_MESSAGE(ServerInfo, MSG_VP_LIST,
    (std::vector<std::string>, vpList),
    (FrequencyDiapason, diapason),
    (Frequency, hzPerChannel)
);

//! Результат обнаружения
SERIALIZABLE_STRUCT_MESSAGE(DetectionResultMessage, MSG_DETECTION_RESULT,
    (VPFrequenciesArray, detections),
    (NSTime,time)
);

// clang-format on
}
