#pragma once

#include <vector>
#include <map>
#include "serializable.hpp"

namespace RPNNode {
namespace RemoteChannelManagerProtocol {
const char * const ProtocolName = "RPNNode_RemoteChannelManager";
const unsigned short ProtocolCode = 10;

const unsigned short ProtocolVersion = 2;

#define CURRENT_PROTOCOL ProtocolCode

enum EMessages {
    REGISTER,
    COMMON_SETTINGS,
    RPA_STATE,
    NOTIFY_SEND_COMMAND,
    NOTIFY_SEND_RPARESULT,
    CHANNEL_COMMAND,
    CHANNEL_RPARESULT,
    ATTACH_MANAGER,
    DETACH_MANAGER,
    DEVICE_STATUS_CHANGED,
    CHANNEL_STATUS_CHANGED,
    CHANNEL_QUALITIES,
    COMMAND_BY_DIRECTIONS,
    RPARESULT_BY_DIRECTIONS,
    ATTACH_LISTENER,
    DETACH_LISTENER,
    CHANNEL_DATA,
    PERSISTENT_SETTING,
    DEVICE_DETACH,
    PCI_DEVICE_ATTACH,
    PCI_DEVICE_UPDATE_SIGNALS,
    MANAGER_STATE,
    CHECK_CHANNEL_STATE,
    CHANNEL_READY
};


// ----------------------------------------------------------------------------
// структуры данных
// ----------------------------------------------------------------------------
//информация о настройках
SERIALIZABLE_STRUCT(Setting,
    (std::string, name), // наименование настройки
    (std::string, value) // значение настройки
);

//информация о настройках каналов
SERIALIZABLE_STRUCT(DeviceChannel,
    (int, channelFrom), // канал - от кого
    (int, channelTo), // канал - до кого
    (std::string, device), // устройство
    (std::string, value) // настройка
);

//информация об РПП
SERIALIZABLE_STRUCT(Rpp,
    (int, id),             // идентификатор
    (std::wstring, code), // сокращенное обозначение
    (std::wstring, name), // имя
    (std::wstring, branch), // подразделение
    (int, type),         // тип
    (bool, isCurrent)     // местный рпп
);

//информация о координатах
SERIALIZABLE_STRUCT(RppCoordinate,
    (int, id),     // идентификатор
    (int, posx),    // долгота
    (int, posy)     // широта
);

//информация о диапазоне частот
SERIALIZABLE_STRUCT(RpaFreqRange,
    (unsigned long long, from), // начало диапазона
    (unsigned long long, to), // конец диапазона
    (bool, hasHistory)   // признак наличия истории
);

//информация о мэнеджере
SERIALIZABLE_STRUCT(ChannelManagerRef,
    (int, id), // ид менеджера
    (std::string, type) // тип менеджера
);

SERIALIZABLE_STRUCT(StatusCode,
    (uint32_t, code),
    (std::wstring, description)
);


//информация о канале
SERIALIZABLE_STRUCT(ChannelRef,
    (int, id), // канал - до кого
    (std::string, channelName), // наименование канала
    (ChannelManagerRef, manager) // менеджер
);

//информация о потоке канала
SERIALIZABLE_STRUCT(ChannelStream,
    (int, stream),   // направление
    (ChannelRef, channel) // канал
);

SERIALIZABLE_STRUCT(DeviceInfo,
    (std::string, DspProgramVersion),  // Строка с описанием версии программы DSP
    (unsigned int, InterfaceVersion),  // Версия интерфейса взаимодействия с программой DSP
    (unsigned int, ChannelsCount),   // Число каналов поддержиываемых устройством
    (unsigned int, MaxFrameSize),   // Максимальный размер кадра для передачи в канал (в словах)
    (unsigned int, MinFrameSize),   // Минимальный размер кадра для передачи в канал (в словах)
    (unsigned int, ReceiveBufferSize),  // Размер буфера приема (в порциях данных)
    (unsigned int, TransmitProrityCount) // Число приоритетов передачи
);

SERIALIZABLE_STRUCT(DeviceState,
    (bool, ReadyFlag), // Флаг готовности устройства к работе
    (unsigned int, Errorflags) // Флаги ошибок
);


SERIALIZABLE_STRUCT(ChannelInfo,
    (unsigned int, Signals), // Сигналы канала
    (unsigned int, Mode),  // Режим работы
    (unsigned int, TransmitSpeed), // Скорость передачи данных по каналу (бит/сек)
    (unsigned int, ReceiveSpeed) // Скорость приема данных по каналу (бит/сек)
);

SERIALIZABLE_STRUCT(ChannelCounters,
    (unsigned int, TxTrasmitWords),  // Число переданных слов
    (unsigned int, TxTrasmitFrames), // Число переданных кадров
    (unsigned int, TxBreaksCount),  // Счетчик прерываний передачи низкоприоритетных кадров
    (unsigned int, RxReceiveWords),  // Число принятых слов
    (unsigned int, RxLostWords),  // Число слов, потерянных из-за переполнения буфера приема
    (unsigned int, TxSynCycles),  // Число циклов синхронизации на передачу
    (unsigned int, RxSynCycles)  // Число циклов синхронизации на прием
);

SERIALIZABLE_STRUCT(ChannelCountersRef,
    (ChannelRef, ref),  // Число переданных слов
    (ChannelCounters, counter) // Число переданных кадров
);

SERIALIZABLE_STRUCT(ChannelInfoRef,
    (ChannelRef, ref),  // Число переданных слов
    (ChannelInfo, info) // Число переданных кадров
);

//информация о сигналах
SERIALIZABLE_STRUCT(ChannelSignal,
    (int, id),
    (bool, ready),
    (bool, spReceive),
    (bool, spTransmit),
    (bool, taktReceive),
    (bool, taktTransmit),
    (bool, spfReceive),
    (bool, spfTransmit),
    (bool, normaZas),
    (int, speed),
    (int, coefRightWork)
);

//информация о канале
SERIALIZABLE_STRUCT(ChannelQuality,
    (ChannelRef, channel), // канал
    (int, size), // размер очереди
    (int, speed), // скорость канала
    (int, coef) // КИД
);

//информация о команде
SERIALIZABLE_STRUCT(Command,
    (int, idfrom),
    (int, idto),
    (int, ref),
    (int, scom),
    (unsigned long long, dtfrom),
    (unsigned long long, dtlength),
    (int, pi),
    (int, vp),
    (unsigned long long, freq),
    (int, freqnegdelta),
    (int, freqposdelta),
    (int, type),
    (unsigned int, client),
    (short, sectorbeg),
    (short, sectorend),
    (unsigned int, priority),
    (int, flags),
    (ChannelRef, channel),
    (int, tag)
);

//информация об оценке
SERIALIZABLE_STRUCT(PelQuality,
    (short, probability), //вероятность попадания в допустимый интервал ошибки 
    (short, forecastedErr) //предсказанная ошибка, в градусах*10
);

//информация о пеленге
SERIALIZABLE_STRUCT(Peleng,
    (int, angle),
    (int, freqnegdelta),
    (int, freqposdelta),
    (int, pi),
    (int, vp),
    (unsigned long long, offset),
    (PelQuality, quality),
    (unsigned char, num),
    (unsigned short, range),
    (std::string, iri),
    (std::vector<int>, placeangle)
);

//информация о результате
SERIALIZABLE_STRUCT(RpaResult,
    (int, idfrom),
    (int, idto),
    (int, ref),
    (int, scom),
    (unsigned long long, dtfrom),
    (int, posx),
    (int, posy),
    (bool, isftw),
    (int, rpa),
    (int, error),
    (std::vector<Peleng>, pelengs),
    (ChannelRef, channel),
    (int, tag)
);


// ----------------------------------------------------------------------------
// сообщения - конфигурация
// ----------------------------------------------------------------------------
SERIALIZABLE_STRUCT_MESSAGE(Register, REGISTER,
    (std::wstring, name), //имя приложения
    (std::string, host), //имя компьютера
    (int, id),   //ид-системы
    (unsigned short, protocolVersion, { ProtocolVersion })   //версия протокола
);

SERIALIZABLE_STRUCT_MESSAGE(CommonSettings, COMMON_SETTINGS,
    (int, currentAddress),
    (std::vector<Setting>, intSettings),
    (std::vector<DeviceChannel>, deviceChannels),
    (std::vector<Rpp>, rpps),
    (std::vector<RppCoordinate>, rppCoordinates)
);

SERIALIZABLE_STRUCT_MESSAGE(RpaState, RPA_STATE,
    (int, state),
    (std::vector<RpaFreqRange>, freqRanges)
);

// ----------------------------------------------------------------------------
// сообщения - интерфейс каналов
// ----------------------------------------------------------------------------
SERIALIZABLE_STRUCT_MESSAGE(AttachManager, ATTACH_MANAGER,
    (ChannelManagerRef, manager),
    (int, codec),
    (std::vector<ChannelRef>, channels),
    (std::string, routerName)
);

SERIALIZABLE_STRUCT_MESSAGE(DetachManager, DETACH_MANAGER,
    (ChannelManagerRef, manager)
);

SERIALIZABLE_STRUCT_MESSAGE(DeviceStatusChanged, DEVICE_STATUS_CHANGED,
    (ChannelManagerRef, manager),
    (std::vector<uint32_t>, statuses)
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelStatusChanged, CHANNEL_STATUS_CHANGED,
    (ChannelRef, channel),
    (std::vector<uint32_t>, statuses)
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelQualities, CHANNEL_QUALITIES,
    (std::vector<ChannelQuality>, qualities)
);

SERIALIZABLE_STRUCT_MESSAGE(CommandByDirections, COMMAND_BY_DIRECTIONS,
    (ChannelManagerRef, manager),
    (Command, command),
    (std::vector<int>, channels)
);

SERIALIZABLE_STRUCT_MESSAGE(RpaResultByDirections, RPARESULT_BY_DIRECTIONS,
    (ChannelManagerRef, manager),
    (RpaResult, result),
    (std::vector<int>, channels)
);

SERIALIZABLE_STRUCT_MESSAGE(NotifySendCommand, NOTIFY_SEND_COMMAND,
    (ChannelRef, channel),
    (Command, command)
);

SERIALIZABLE_STRUCT_MESSAGE(NotifySendRpaResult, NOTIFY_SEND_RPARESULT,
    (ChannelRef, channel),
    (RpaResult, result)
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelCommand, CHANNEL_COMMAND,
    (ChannelRef, channel),
    (Command, command)
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelRpaResult, CHANNEL_RPARESULT,
    (ChannelRef, channel),
    (RpaResult, result)
);

SERIALIZABLE_STRUCT_MESSAGE(AttachListener, ATTACH_LISTENER,
    (ChannelStream, stream)
);

SERIALIZABLE_STRUCT_MESSAGE(DetachListener, DETACH_LISTENER,
    (ChannelStream, stream)
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelData, CHANNEL_DATA,
    (ChannelStream, stream),
    (std::vector<uint8_t>, bytes)
);

SERIALIZABLE_STRUCT_MESSAGE(PersistentSetting, PERSISTENT_SETTING,
    (Setting, setting)
);

SERIALIZABLE_STRUCT_MESSAGE(PCIDeviceState, PCI_DEVICE_ATTACH,
    (int, msiCount), // количество каналов
    (DeviceInfo, info), // информация об устройстве
    (DeviceState, state), // состояние
    (std::vector<ChannelInfoRef>, channelInfo), // информация о каналам
    (std::vector<ChannelCountersRef>, counters), // информация о счетчиках
    (std::vector<ChannelSignal>, signal) // индивидуальные сигналы устройства
);

SERIALIZABLE_STRUCT_MESSAGE(DeviceDetach, DEVICE_DETACH,
    (unsigned long, id) // id устройства
);

SERIALIZABLE_STRUCT_MESSAGE(PCIDeviceSignals, PCI_DEVICE_UPDATE_SIGNALS,
    (std::vector<ChannelInfoRef>, channelInfo), // информация о каналам
    (std::vector<ChannelCountersRef>, counters), // информация о счетчиках
    (std::vector<ChannelSignal>, signal) // индивидуальные сигналы устройства
);

SERIALIZABLE_STRUCT_MESSAGE(ManagerState, MANAGER_STATE,
    (ChannelManagerRef, ref), // информация о менеджере
    (StatusCode, status) // состояние   
);

SERIALIZABLE_STRUCT_MESSAGE(CheckChannelState, CHECK_CHANNEL_STATE,
    (ChannelRef, ref) // канал
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelReady, CHANNEL_READY,
    (ChannelRef, ref) // канал
);

}

#undef CURRENT_PROTOCOL

}
