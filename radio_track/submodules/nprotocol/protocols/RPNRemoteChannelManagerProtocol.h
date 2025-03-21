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
// ��������� ������
// ----------------------------------------------------------------------------
//���������� � ����������
SERIALIZABLE_STRUCT(Setting,
    (std::string, name), // ������������ ���������
    (std::string, value) // �������� ���������
);

//���������� � ���������� �������
SERIALIZABLE_STRUCT(DeviceChannel,
    (int, channelFrom), // ����� - �� ����
    (int, channelTo), // ����� - �� ����
    (std::string, device), // ����������
    (std::string, value) // ���������
);

//���������� �� ���
SERIALIZABLE_STRUCT(Rpp,
    (int, id),             // �������������
    (std::wstring, code), // ����������� �����������
    (std::wstring, name), // ���
    (std::wstring, branch), // �������������
    (int, type),         // ���
    (bool, isCurrent)     // ������� ���
);

//���������� � �����������
SERIALIZABLE_STRUCT(RppCoordinate,
    (int, id),     // �������������
    (int, posx),    // �������
    (int, posy)     // ������
);

//���������� � ��������� ������
SERIALIZABLE_STRUCT(RpaFreqRange,
    (unsigned long long, from), // ������ ���������
    (unsigned long long, to), // ����� ���������
    (bool, hasHistory)   // ������� ������� �������
);

//���������� � ���������
SERIALIZABLE_STRUCT(ChannelManagerRef,
    (int, id), // �� ���������
    (std::string, type) // ��� ���������
);

SERIALIZABLE_STRUCT(StatusCode,
    (uint32_t, code),
    (std::wstring, description)
);


//���������� � ������
SERIALIZABLE_STRUCT(ChannelRef,
    (int, id), // ����� - �� ����
    (std::string, channelName), // ������������ ������
    (ChannelManagerRef, manager) // ��������
);

//���������� � ������ ������
SERIALIZABLE_STRUCT(ChannelStream,
    (int, stream),   // �����������
    (ChannelRef, channel) // �����
);

SERIALIZABLE_STRUCT(DeviceInfo,
    (std::string, DspProgramVersion),  // ������ � ��������� ������ ��������� DSP
    (unsigned int, InterfaceVersion),  // ������ ���������� �������������� � ���������� DSP
    (unsigned int, ChannelsCount),   // ����� ������� ��������������� �����������
    (unsigned int, MaxFrameSize),   // ������������ ������ ����� ��� �������� � ����� (� ������)
    (unsigned int, MinFrameSize),   // ����������� ������ ����� ��� �������� � ����� (� ������)
    (unsigned int, ReceiveBufferSize),  // ������ ������ ������ (� ������� ������)
    (unsigned int, TransmitProrityCount) // ����� ����������� ��������
);

SERIALIZABLE_STRUCT(DeviceState,
    (bool, ReadyFlag), // ���� ���������� ���������� � ������
    (unsigned int, Errorflags) // ����� ������
);


SERIALIZABLE_STRUCT(ChannelInfo,
    (unsigned int, Signals), // ������� ������
    (unsigned int, Mode),  // ����� ������
    (unsigned int, TransmitSpeed), // �������� �������� ������ �� ������ (���/���)
    (unsigned int, ReceiveSpeed) // �������� ������ ������ �� ������ (���/���)
);

SERIALIZABLE_STRUCT(ChannelCounters,
    (unsigned int, TxTrasmitWords),  // ����� ���������� ����
    (unsigned int, TxTrasmitFrames), // ����� ���������� ������
    (unsigned int, TxBreaksCount),  // ������� ���������� �������� ����������������� ������
    (unsigned int, RxReceiveWords),  // ����� �������� ����
    (unsigned int, RxLostWords),  // ����� ����, ���������� ��-�� ������������ ������ ������
    (unsigned int, TxSynCycles),  // ����� ������ ������������� �� ��������
    (unsigned int, RxSynCycles)  // ����� ������ ������������� �� �����
);

SERIALIZABLE_STRUCT(ChannelCountersRef,
    (ChannelRef, ref),  // ����� ���������� ����
    (ChannelCounters, counter) // ����� ���������� ������
);

SERIALIZABLE_STRUCT(ChannelInfoRef,
    (ChannelRef, ref),  // ����� ���������� ����
    (ChannelInfo, info) // ����� ���������� ������
);

//���������� � ��������
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

//���������� � ������
SERIALIZABLE_STRUCT(ChannelQuality,
    (ChannelRef, channel), // �����
    (int, size), // ������ �������
    (int, speed), // �������� ������
    (int, coef) // ���
);

//���������� � �������
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

//���������� �� ������
SERIALIZABLE_STRUCT(PelQuality,
    (short, probability), //����������� ��������� � ���������� �������� ������ 
    (short, forecastedErr) //������������� ������, � ��������*10
);

//���������� � �������
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

//���������� � ����������
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
// ��������� - ������������
// ----------------------------------------------------------------------------
SERIALIZABLE_STRUCT_MESSAGE(Register, REGISTER,
    (std::wstring, name), //��� ����������
    (std::string, host), //��� ����������
    (int, id),   //��-�������
    (unsigned short, protocolVersion, { ProtocolVersion })   //������ ���������
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
// ��������� - ��������� �������
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
    (int, msiCount), // ���������� �������
    (DeviceInfo, info), // ���������� �� ����������
    (DeviceState, state), // ���������
    (std::vector<ChannelInfoRef>, channelInfo), // ���������� � �������
    (std::vector<ChannelCountersRef>, counters), // ���������� � ���������
    (std::vector<ChannelSignal>, signal) // �������������� ������� ����������
);

SERIALIZABLE_STRUCT_MESSAGE(DeviceDetach, DEVICE_DETACH,
    (unsigned long, id) // id ����������
);

SERIALIZABLE_STRUCT_MESSAGE(PCIDeviceSignals, PCI_DEVICE_UPDATE_SIGNALS,
    (std::vector<ChannelInfoRef>, channelInfo), // ���������� � �������
    (std::vector<ChannelCountersRef>, counters), // ���������� � ���������
    (std::vector<ChannelSignal>, signal) // �������������� ������� ����������
);

SERIALIZABLE_STRUCT_MESSAGE(ManagerState, MANAGER_STATE,
    (ChannelManagerRef, ref), // ���������� � ���������
    (StatusCode, status) // ���������   
);

SERIALIZABLE_STRUCT_MESSAGE(CheckChannelState, CHECK_CHANNEL_STATE,
    (ChannelRef, ref) // �����
);

SERIALIZABLE_STRUCT_MESSAGE(ChannelReady, CHANNEL_READY,
    (ChannelRef, ref) // �����
);

}

#undef CURRENT_PROTOCOL

}
