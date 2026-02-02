#ifndef __PROTOCOL_MODBUS_H__
#define __PROTOCOL_MODBUS_H__

#include "typeSimple.h"
#include "crc16.h"


enum class eMODBUS_PARSE_STS{
    Addr,
    Func,
    DataLen,
    Data,
    Crc,
    PacketOk,
};


enum class eMODBUS_RTN_CODE{
    Ok = 0,
    CrcErr,
    LenErr,
    FuncErr,
    Parsing,
    CrcWait,
    Idle,
};


typedef struct {
    eMODBUS_PARSE_STS ucRcvSts;
    u8 ucCrcOffset;
    u16 ucRcvDataLen;
    u16 usPacketLen;
    u8 aucCrc16[2];
    u16 usCrcRcv;
    u16 usCrcCal;
}ModbusRcvHnd_t;






class Modbus{
public:
    Modbus(u32 maxPktLen = 256){ 
        m_uiMaxPktLen = maxPktLen;

        if(m_uiMaxPktLen > 512){
            m_uiMaxPktLen = 512;
        }
    }


    bool GetDataPkt(u8* data, u16* len, u16 maxLen){

        if(m_rcvHnd.usPacketLen < 3 || m_usRcvDataLen > maxLen){

            return false;
        }

        // except : addr, func, dataLen
        memcpy(&data[0], &m_ucRecvPacketBuff[3], m_usRcvDataLen);
        *len = m_usRcvDataLen; // except : addr, func, dataLen, crc16(2byte)

        return true;
    }


    void InitPacketLen(){
        m_usRcvDataLen = 0;
        memset(m_ucRecvPacketBuff, 0, sizeof(m_ucRecvPacketBuff));
        m_rcvHnd.usPacketLen = 0;
    }


    eMODBUS_RTN_CODE RcvPacketHandle(u8 rcvByte){

        eMODBUS_RTN_CODE rtn = eMODBUS_RTN_CODE::Idle;

        switch(m_rcvHnd.ucRcvSts){
            case eMODBUS_PARSE_STS::Addr:    //
                if(rcvByte == 0x01){
                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Func;
                    rtn = eMODBUS_RTN_CODE::Parsing;

                    m_rcvHnd.usPacketLen = 0;
                    m_ucRecvPacketBuff[m_rcvHnd.usPacketLen++] = rcvByte;
                }
                else {
                    rtn = eMODBUS_RTN_CODE::Idle;
                }
                break;

            case eMODBUS_PARSE_STS::Func:
                if(rcvByte == 0x04){

                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::DataLen;
                    rtn = eMODBUS_RTN_CODE::Parsing;

                    m_ucRecvPacketBuff[m_rcvHnd.usPacketLen++] = rcvByte;
                }
                else {

                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Addr;
                    rtn = eMODBUS_RTN_CODE::FuncErr;
                }
                break;

            case eMODBUS_PARSE_STS::DataLen:
                m_ucRecvPacketBuff[m_rcvHnd.usPacketLen++] = rcvByte;
                m_usRcvDataLen = 0;

                m_rcvHnd.ucRcvDataLen = rcvByte;
                m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Data;
                rtn = eMODBUS_RTN_CODE::Parsing;
                break;

            case eMODBUS_PARSE_STS::Data:
                m_ucRecvPacketBuff[m_rcvHnd.usPacketLen++] = rcvByte;
                m_usRcvDataLen++;

                if(m_usRcvDataLen == m_rcvHnd.ucRcvDataLen){
                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Crc;
                    rtn = eMODBUS_RTN_CODE::CrcWait;
                    m_rcvHnd.ucCrcOffset = 0;
                }
                else if(m_usRcvDataLen >= m_uiMaxPktLen){
                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Addr ;
                    rtn = eMODBUS_RTN_CODE::LenErr;
                    m_rcvHnd.usPacketLen = 0;
                }
                break;

            case eMODBUS_PARSE_STS::Crc:
                m_rcvHnd.aucCrc16[m_rcvHnd.ucCrcOffset++] = rcvByte;

                if(m_rcvHnd.ucCrcOffset == 2){

                    memcpy(&m_rcvHnd.usCrcRcv, &m_rcvHnd.aucCrc16[0], sizeof(u16));

                    if(m_rcvHnd.usCrcRcv != Compute_ModbusCrc16(m_ucRecvPacketBuff, m_rcvHnd.usPacketLen)){

                    	rtn = eMODBUS_RTN_CODE::CrcErr;

                    }
                    else {

                        rtn = eMODBUS_RTN_CODE::Ok;
                    }

                    m_rcvHnd.usPacketLen = 0;
                    m_rcvHnd.ucRcvSts = eMODBUS_PARSE_STS::Addr ;


                }
                break;

            case eMODBUS_PARSE_STS::PacketOk:

            	break;
        }


        return rtn;
    }


private:



    u8 m_ucRecvPacketBuff[512];
    u16 m_usRcvDataLen = 0;
    u32 m_uiMaxPktLen = 0;
    ModbusRcvHnd_t m_rcvHnd;


};

#endif
