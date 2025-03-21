#include "../../submodules/json.hpp"
#include "workWithJson.h"

void workWithJson::writeToJson(QVector<unit> units)
{
    std::ofstream outf{"units.json"};
    json units_json;
    for (auto el : units)
    {
        structParamNet::unit un = el;

        structParamNet::antSystem system = el.hardware_.ant_system;
        json antSyst_json = json{{"name_system", system.name.toStdString()},
                                 {"gain", system.antGain},
                                 {"sectorSend", system.sectorSendRec},
                                 {"sectorAngle", system.sectorAngle},
                                 {"pol", system.typePolar}};
        structParamNet::sender send = el.hardware_.send;
        json send_json = json{{"name_sender", send.name.toStdString()},
                              {"power", send.power},
                              {"sample_rate", send.sample_rate},
                              {"heightAnt", send.heightAnt}};

        recvier recv = el.hardware_.rec;
        json recv_json = json{{"name_recv", recv.name.toStdString()},
                              {"sens", recv.sensitivity},
                              {"heightAnt", recv.heightAnt}};

        json hardware = json{{"antSystem", antSyst_json},
                             {"sender", send_json},
                             {"recv", recv_json}};

        json j = json{{"name", el.name.toStdString()},
                      {"coord_x", el.coord.x()},
                      {"coord_y", el.coord.y()},
                      {"hardware", hardware}};

        units_json.push_back(j);
    }
    outf << units_json.dump(4);
    outf.close();
    //readFromJson();
};

QVector<unit> workWithJson::readFromJson()
{
    QVector<unit> units{};
    unit test;
    try
    {
        std::ifstream inf{"units.json"};

        const auto units_json = json::parse(inf);

        for (auto el : units_json)
        {
            //todo: add check on containing parameter in json

            if (el.contains("hardware"))
            {
                hardware hardware_;
                if (el["hardware"].contains("antSystem"))
                {
                    antSystem system;
                    el["hardware"]["antSystem"].contains("gain")
                        ? system.antGain = el["hardware"]["antSystem"]["gain"]
                        : system.antGain = 0;
                    el["hardware"]["antSystem"].contains("name_system")
                        ? system.name = QString::fromStdString(
                              el["hardware"]["antSystem"]["name_system"])
                        : system.name = "default";
                    el["hardware"]["antSystem"].contains("sectorSend")
                        ? system.sectorSendRec =
                              el["hardware"]["antSystem"]["sectorSend"]
                        : system.sectorSendRec = std::pair{0, 90};
                    el["hardware"]["antSystem"].contains("sectorAngle")
                        ? system.sectorAngle =
                              el["hardware"]["antSystem"]["sectorAngle"]
                        : system.sectorAngle = std::pair{0, 90};
                    el["hardware"]["antSystem"].contains("pol")
                        ? system.typePolar = el["hardware"]["antSystem"]["pol"]
                        : system.typePolar = polarization::vertical;
                    hardware_.ant_system = system;
                }

                //todo: add exeption

                if (el["hardware"].contains("sender"))
                {
                    sender sender;
                    el["hardware"]["sender"].contains("name_sender")
                        ? sender.name = QString::fromStdString(
                              el["hardware"]["sender"]["name_sender"])
                        : sender.name = "default";
                    el["hardware"]["sender"].contains("power")
                        ? sender.power = el["hardware"]["sender"]["power"]
                        : sender.power = 25;
                    el["hardware"]["sender"].contains("sample_rate")
                        ? sender.sample_rate =
                              el["hardware"]["sender"]["sample_rate"]
                        : sender.sample_rate = 1130;
                    el["hardware"]["sender"].contains("heightAnt")
                        ? sender.heightAnt =
                              el["hardware"]["sender"]["heightAnt"]
                        : sender.heightAnt = 25;
                    hardware_.send = sender;
                }

                if (el["hardware"].contains("recv"))
                {
                    recvier recv;
                    el["hardware"]["recv"].contains("name_recv")
                        ? recv.name = QString::fromStdString(
                              el["hardware"]["recv"]["name_recv"])
                        : recv.name = "default";
                    el["hardware"]["recv"].contains("sens")
                        ? recv.sensitivity = el["hardware"]["recv"]["sens"]
                        : recv.sensitivity = 15;
                    el["hardware"]["recv"].contains("heightAnt")
                        ? recv.sensitivity = el["hardware"]["recv"]["heightAnt"]
                        : recv.sensitivity = 25;

                    hardware_.rec = recv;
                }

                unit unit_{QString::fromStdString(el["name"]),
                           QPointF{el["coord_x"], el["coord_y"]},
                           {},
                           100,
                           hardware_};

                units.push_back(unit_);
            }
            //todo: add exception
        }
    }
    catch (std::exception e)
    {
    }

    return units;
}

paramHardware workWithJson::readFromJsonHardware()
{
    try
    {
        std::ifstream inf{"hardwares.json"};
        const auto hardwares = json::parse(inf);

        QVector<antSystem> systems;
        QVector<structParamNet::sender> senders;
        QVector<recvier> recviers;
        for (auto el : hardwares[0])
        {
            antSystem system;
            el.contains("gain") ? system.antGain = el["gain"]
                                : system.antGain = 0;
            el.contains("name_system")
                ? system.name = QString::fromStdString(el["name_system"])
                : system.name = "default";
            el.contains("sectorSend") ? system.sectorSendRec = el["sectorSend"]
                                      : system.sectorSendRec = std::pair{0, 90};
            el.contains("sectorAngle") ? system.sectorAngle = el["sectorAngle"]
                                       : system.sectorAngle = std::pair{0, 90};
            el.contains("pol") ? system.typePolar = el["pol"]
                               : system.typePolar = polarization::vertical;
            systems.push_back(system);
        }
        for (auto el : hardwares[1])
        {
            sender sender;
            el.contains("name_sender")
                ? sender.name = QString::fromStdString(el["name_sender"])
                : sender.name = "default";
            el.contains("power") ? sender.power = el["power"]
                                 : sender.power = 25;
            el.contains("sample_rate") ? sender.sample_rate = el["sample_rate"]
                                       : sender.sample_rate = 1130;
            el.contains("heightAnt") ? sender.heightAnt = el["heightAnt"]
                                     : sender.heightAnt = 25;
            senders.push_back(sender);
        }
        for (auto el : hardwares[2])
        {
            recvier recv;
            el.contains("name_recv")
                ? recv.name = QString::fromStdString(el["name_recv"])
                : recv.name = "default";
            el.contains("sens") ? recv.sensitivity = el["sens"]
                                : recv.sensitivity = 15;
            el.contains("heightAnt") ? recv.heightAnt = el["heightAnt"]
                                     : recv.heightAnt = 25;
            recviers.push_back(recv);
        }
        inf.close();

        paramHardware listHardwares;
        listHardwares.ant_system = systems;
        listHardwares.send = senders;
        listHardwares.recv = recviers;
        return listHardwares;
    }
    catch (std::exception e)
    {
        paramHardware emptyStruct{};
        return emptyStruct;
    }
}

void workWithJson::writeToJsonHardware(paramHardware listHardware)
{
    std::ofstream outf{"hardwares.json"};
    json hardwares;
    json antSyst;
    json senders;
    json recviers;
    for (auto el : listHardware.ant_system)
    {
        json newAntSyst{{"name_system", el.name.toStdString()},
                        {"gain", el.antGain},
                        {"sectorSend", el.sectorSendRec},
                        {"sectorAngle", el.sectorAngle},
                        {"pol", el.typePolar}};
        antSyst.push_back(newAntSyst);
    }
    for (auto el : listHardware.send)
    {
        json newSender{{"name_sender", el.name.toStdString()},
                       {"power", el.power},
                       {"sample_rate", el.sample_rate},
                       {"heightAnt", el.heightAnt}};
        senders.push_back(newSender);
    }
    for (auto el : listHardware.recv)
    {
        json newRecvier{{"name_recv", el.name.toStdString()},
                        {"sens", el.sensitivity},
                        {"heightAnt", el.heightAnt}};
        recviers.push_back(newRecvier);
    }
    hardwares.push_back(antSyst);
    hardwares.push_back(senders);
    hardwares.push_back(recviers);
    outf << hardwares.dump(4);
    outf.close();
    readFromJsonHardware();
}
