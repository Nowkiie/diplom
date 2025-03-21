#pragma once

#include <memory>
#include <vector>
#include "serializable.hpp"

namespace ExtraViewInformer
{
const char* const protocolName = "ExtraViewInformerProtocol";
const unsigned short protocolCode = 16;


enum ProtocolMessages
{
    messageRadionets,
    messageSessions,
};

enum SessionAction : int
{
    sessionAdd,  // добавить сеанс (если такой уже есть, то происходит обновление)
    sessionRemove,  // удалить сеанс
};

struct RadionetDeclaration
{
    std::string name;  //имя радиосети utf8
};

// передача списка радиосетей на РК-ДПЛ
// передаётся один раз при подключении, и при изменении
struct RadionetDeclarationMessage
{
    enum
    {
        message = messageRadionets,
        protocol = protocolCode
    };
    std::vector<RadionetDeclaration> radionets;
};

// передача события на РК-ДПЛ
// передаётся при изменениях в списке сеансов
struct SessionInformationMessage
{
    enum
    {
        message = messageSessions,
        protocol = protocolCode
    };
    SessionAction action;
    uint64_t sessionId;
    uint64_t frequency;
    std::string radionetName;  // имя радиосети utf8
    bool dangerSession;
};

}  // namespace ExtraViewInformer
