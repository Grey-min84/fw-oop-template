#ifndef __COMM_HALF_DUPLEX_H__
#define __COMM_HALF_DUPLEX_H__

#include "portSTM32_uart.h"
#include "portSTM32_gpio.h"

#include <array>

enum class eHDuplexCommSts{
    Idle = 0,
    Send,
    WaitAck,
    AckOk,
};




class DrvRs485{
public:
    DrvRs485() {
        DrvRs485::m_selfList[DrvRs485::m_listIdx++] = this;
        
    }

    void Init(IUart* _port, IGpio* _flowPin){
        m_port = _port;
        m_flowPin = _flowPin;

    }

    bool ReadByte(uint8_t* byte);
    bool IsData_Available();
    void AvailableSendDoneCheck(bool onOff){
        
        if(onOff)
            m_port->RegisterRcvCallback(eUartCbType::TxDone, OnISR_DMASendDone, this);
    }
    
    


    u8 CheckCommSts();
    void ResetCommRx();
    void StopCommRx();
    void PortReset(){
        m_port->PortReset();
    }

    u8 SendPacketDMA(u8 *l_ucarData, u8 l_ucDataLen);
    u8 SendPacket(u8 *l_ucarData, u8 l_ucDataLen);
    void FlowCtl(u8 ucCtl);

    bool WaitSendDone(u32 timeout, std::function<u32(void)> funcGetTick);
    bool IsSendDone(){return m_sendSts == eHDuplexCommSts::AckOk ? true : false;}

    

    void Delay(u32 uiMatchTick, u32 uiCurrTick, u32 (*fpTick)(void));

    //void RegisterRcvCallback(eUartCbType type, std::function<void(void*)> callback, void* param)  {
    void RegisterRcvCallback(eUartCbType type, void(*callback)(void*), void* param)  {
        m_port->RegisterRcvCallback(type, callback, param);
    }


    
    const eHDuplexCommSts GetSendSts(){return m_sendSts;}
    void AutoFlowLowSet(bool _onOff) {m_bEnableAutoFlow = _onOff;}
    void Reset_RcvHnd(){
        m_port->ResetRcv();
    }

    static std::array<DrvRs485*, 6> m_selfList;
    static u8 m_listIdx;

private:
    IUart* m_port;
    IGpio* m_flowPin;
    eHDuplexCommSts m_sendSts = eHDuplexCommSts::Idle;

    bool m_bEnableAutoFlow = false;
    u8 m_supportWaitSendDone = 0;


    static void OnISR_DMASendDone(void* args);
};


#endif
