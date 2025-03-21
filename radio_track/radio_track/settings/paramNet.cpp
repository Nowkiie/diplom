#include "paramNet.h"

#include <iostream>

paramNet::paramNet()
{
    workWithJson_ = std::make_shared<workWithJson>();
}

QVector<unit> paramNet::readDataFromJson()
{
    return workWithJson_->readFromJson();
}

QVector<structParamNet::sender> paramNet::getPointerOnVectorSender()
{
    return sender_;
}

QVector<recvier> paramNet::getPointerOnVectorRecvier()
{
    return recv_;
}

void paramNet::readDataHardwareFromJson()
{
    paramHardware listHardwares = workWithJson_->readFromJsonHardware();
    if (!listHardwares.ant_system.isEmpty())
    {
        antSystems_ = listHardwares.ant_system;
    }
    if (!listHardwares.send.isEmpty())
    {
        sender_ = listHardwares.send;
    }
    if (!listHardwares.recv.isEmpty())
    {
        recv_ = listHardwares.recv;
    }
}

void paramNet::writeDataOnHardwareIntoUnit(QVector<unit> units)
{
    for (auto& un : units)
    {
        QString nameAntSystem = un.hardware_.ant_system.name;
        auto it = std::find_if(antSystems_.begin(), antSystems_.end(),
                               [nameAntSystem](antSystem system)
                               {
                                   return system.name == nameAntSystem;
                               });
        if (it != antSystems_.end())
        {
            //std::cout << it - antSystems_.begin() << '\n';
            un.hardware_.ant_system.antGain =
                antSystems_[it - antSystems_.begin()].antGain;
            un.hardware_.ant_system.sectorSendRec.first =
                antSystems_[it - antSystems_.begin()].sectorSendRec.first;
            un.hardware_.ant_system.sectorSendRec.second =
                antSystems_[it - antSystems_.begin()].sectorSendRec.second;
            un.hardware_.ant_system.sectorAngle =
                antSystems_[it - antSystems_.begin()].sectorAngle;
            un.hardware_.ant_system.typePolar =
                antSystems_[it - antSystems_.begin()].typePolar;
        }
        QString nameSender = un.hardware_.send.name;

        //если ничего не выбрано - нет поиска
        if (nameSender != "-")
        {
            auto itSend = std::find_if(sender_.begin(), sender_.end(),
                                       [nameSender](structParamNet::sender send)
                                       {
                                           return send.name == nameSender;
                                       });
            if (itSend != sender_.end())
            {
                un.hardware_.send.name = sender_[itSend - sender_.begin()].name;
                un.hardware_.send.power =
                    sender_[itSend - sender_.begin()].power;
                un.hardware_.send.sample_rate =
                    sender_[itSend - sender_.begin()].sample_rate;
                un.hardware_.send.heightAnt =
                    sender_[itSend - sender_.begin()].heightAnt;
            }
        }
        QString nameRecvier = un.hardware_.rec.name;

        if (nameRecvier != "-")
        {
            auto itRec =
                std::find_if(recv_.begin(), recv_.end(),
                             [nameRecvier](structParamNet::recvier recv)
                             {
                                 return recv.name == nameRecvier;
                             });

            if (itRec != recv_.end())
            {
                un.hardware_.rec.name = recv_[itRec - recv_.begin()].name;
                un.hardware_.rec.sensitivity =
                    recv_[itRec - recv_.begin()].sensitivity;
                un.hardware_.rec.heightAnt =
                    recv_[itRec - recv_.begin()].heightAnt;
            }
        }
    }
}

void paramNet::writeDatOnJson(QVector<unit> const& units)
{
    writeDataOnHardwareIntoUnit(units);
    workWithJson_->writeToJson(units);

    paramHardware listHardwares;
    listHardwares.ant_system = antSystems_;
    listHardwares.send = sender_;
    listHardwares.recv = recv_;

    workWithJson_->writeToJsonHardware(listHardwares);
    /* hardware new_hardware;
    new_hardware.ant_system = antSystems_[0];
    workWithJson_->writeToJson(hardwares_[0]);*/
}

QVector<antSystem> paramNet::getPointerOnVectorAntSystem()
{
    return antSystems_;
}

void paramNet::del(int number, typeSendParam param)
{
    switch (param)
    {
        case typeSendParam::ant_system:
        {
            antSystems_.remove(number);
            emit updateVectorAntSystem(antSystems_);
            break;
        }
        case typeSendParam::send:
        {
            sender_.remove(number);
            emit updateVectorSender(sender_);
            break;
        }
        case typeSendParam::recvier:
        {
            recv_.remove(number);
            emit updateVectorRecvier(recv_);
            break;
        }
        case typeSendParam::system_link:
        {
            systemLinks_.remove(number);
            break;
        }
        default:
            break;
    }
}

void paramNet::add(QVariant sendingParam, typeSendParam param)
{
    switch (param)
    {
        case typeSendParam::ant_system:
        {
            antSystem system = sendingParam.value<antSystem>();
            antSystems_.push_back(system);
            emit updateVectorAntSystem(antSystems_);
            break;
        }
        case typeSendParam::recvier:
        {
            recvier recv = sendingParam.value<recvier>();
            recv_.push_back(recv);
            emit updateVectorRecvier(recv_);
            break;
        }
        case typeSendParam::send:
        {
            structParamNet::sender send =
                sendingParam.value<structParamNet::sender>();
            sender_.push_back(send);
            emit updateVectorSender(sender_);
            break;
        }
        case typeSendParam::system_link:
        {
            systemLink link = sendingParam.value<systemLink>();
            systemLinks_.push_back(link);
        }

        default:
            break;
    }
}

structParamNet::sender paramNet::getDataForChangingSender(int number)
{
    return sender_[number];
}

antSystem paramNet::getDataForChangingAntSystem(int number)
{
    return antSystems_[number];
}

recvier paramNet::getDataForChangingRecvier(int number)
{
    return recv_[number];
}

void paramNet::update(QVariant sendingParam, typeSendParam param, int number)
{
    switch (param)
    {
        case typeSendParam::ant_system:
        {
            antSystem system = sendingParam.value<antSystem>();
            antSystems_[number].name = system.name;
            antSystems_[number].sectorAngle = system.sectorAngle;
            antSystems_[number].sectorSendRec = system.sectorSendRec;
            antSystems_[number].antGain = system.antGain;
            antSystems_[number].typePolar = system.typePolar;
            emit updateVectorAntSystem(antSystems_);
            break;
        }
        case typeSendParam::recvier:
        {
            recvier recv = sendingParam.value<recvier>();
            recv_[number].name = recv.name;
            recv_[number].sensitivity = recv.sensitivity;
            emit updateVectorRecvier(recv_);
            break;
        }
        case typeSendParam::send:
        {
            structParamNet::sender send =
                sendingParam.value<structParamNet::sender>();
            sender_[number].name = send.name;
            sender_[number].power = send.power;
            sender_[number].sample_rate = send.sample_rate;
            emit updateVectorSender(sender_);
            break;
        }
        case typeSendParam::system_link:
        {
            systemLink link = sendingParam.value<systemLink>();
            systemLinks_[number].name = link.name;
            systemLinks_[number].units = link.units;
            break;
        }
        default:
            break;
    }
}
