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
            (int                        , id_ground_station     ),  //    ����� � ��������� HFDL �� 1 �� 17 ������������ �������� ������� 
            (int                        , id_air                ),    //    ����� � ��������� HFDL �� 0 �� 255 ������������� �������� (������� ������������ � ���� � ������� 0xFF (log-on), ��� ������������� ���� ����� � ��������� HFDL)
            (int                        , aircraft_icao_address ),    //    ����� "����" (�������� 24 bit)
            (std::string                , aircraft_reg            ),    //    ���� "aircraft reg"
            (std::string                , flight_id             ),    //     ��� ����� "Flight id"     
            (long long                  , utc_time              ),    //    ��������� ����� ���������� �� ������ (��������� �� UTC [���� ���])
            (long long                  , utc_time_receive      ),    //    ��������� ����� ������ ������ HFDL (��������� �� UTC [���� ���])
            (int                        , longitude             ),     //     ������� [�������]
            (int                        , latitude              ),    //     ������ [�������]
            (std::string                , message_content       ),  //    ACARS: ���������
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