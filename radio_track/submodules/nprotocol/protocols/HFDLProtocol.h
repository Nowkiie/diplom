#ifndef HFDLProtocolH
#define HFDLProtocolH
//----------------------------------------------------------------------------------------------------------------------
#pragma once

#include <memory>
#include <vector>
#include "serializable.hpp"

namespace HFDLProtocol
{
    const char * const      protocolName1 = "net_results_hfdl_block_from_client_to_server1";
    const char * const      protocolName2 = "net_results_hfdl_block_from_client_to_server2";
    const unsigned short    protocolCode = 5;

    #define CURRENT_PROTOCOL protocolCode

        enum MessageType
        {
            HFDL_RESULTS = 0
        };

        SERIALIZABLE_STRUCT(BlockHFDL,
            (int                        , id_ground_station     ),  //    Номер в протоколе HFDL от 1 до 17 приваивается наземной станции 
            (int                        , id_air                ),    //    Номер в протоколе HFDL от 0 до 255 присваивается самолету (самолет вклинивается в сеть с номером 0xFF (log-on), ему присваивается свой номер в протоколе HFDL)
            (int                        , aircraft_icao_address ),    //    Номер "ИКАО" (занимает 24 bit)
            (std::string                , aircraft_reg            ),    //    Поле "aircraft reg"
            (std::string                , flight_id             ),    //     Имя Рейса "Flight id"     
            (long long                  , utc_time              ),    //    Временная метка полученная из пакета (измерения по UTC [мили сек])
            (long long                  , utc_time_receive      ),    //    Временная метка начала пакета HFDL (измерения по UTC [мили сек])
            (int                        , longitude             ),     //     Долгота [секунды]
            (int                        , latitude              ),    //     Широта [секунды]
            (std::string                , message_content       ),  //    ACARS: Сообщение
            (std::string                 , acars_mode            ),    //    ACARS: mode
            (std::string                , message_label            ),    //    ACARS: Message label
            (std::string                , block_id                ),    //    ACARS: Block id
            (std::string                , msg_no                )    //    ACARS: Msg. no
        );
        
        SERIALIZABLE_STRUCT_MESSAGE(BlockHFDLList, HFDL_RESULTS,
            (std::vector<BlockHFDL>, blocks)
        ); 
    
    #undef CURRENT_PROTOCOL    
}
//----------------------------------------------------------------------------------------------------------------------
#endif