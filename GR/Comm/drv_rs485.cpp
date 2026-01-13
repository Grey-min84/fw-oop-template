#include "drv_rs485.h"


std::array<DrvRs485*, 6> DrvRs485::m_selfList;
u8 DrvRs485::m_listIdx;

bool DrvRs485::ReadByte(uint8_t* byte){

    bool rtn = false;

    rtn = m_port->ReadByteInQue(byte);

    return rtn;
}

bool DrvRs485::IsData_Available(){
    bool rtn = m_port->IsDataAvailable();

    return rtn;
}



uint8_t DrvRs485::CheckCommSts(){

    u8 rtn = m_port->GetPortStatus();
    
    return rtn;
}

void DrvRs485::ResetCommRx(){
    m_port->ResetRcv();
}


void DrvRs485::StopCommRx(){
    m_port->StopRcv();
}


u8 DrvRs485::SendPacketDMA(u8 *l_ucarData, u8 l_ucDataLen){
    u8 rtn = 0;

    rtn = m_port->SendDataDMA(l_ucarData, l_ucDataLen);
    if(rtn == 0){
        m_sendSts = eHDuplexCommSts::WaitAck;
    }
    else {
        m_sendSts = eHDuplexCommSts::Idle;
    }
    return rtn;
}


u8 DrvRs485::SendPacket( u8 *l_ucarData, u8 l_ucDataLen){
    u8 rtn = 0;

    

    return rtn;
}


void DrvRs485::FlowCtl(u8 ucCtl){

    if(ucCtl == 1){
        m_flowPin->Write(GpioState::HIGH);
    }
    else {
        m_flowPin->Write(GpioState::LOW);
    }
}



//bool DrvRs485::WaitSendDone(u32 timeout, std::function<u32(void)> funcGetTick){
bool DrvRs485::WaitSendDone(u32 timeout, std::function<u32(void)> funcGetTick){
    
    u32 currTick = funcGetTick();

    while(m_sendSts != eHDuplexCommSts::AckOk){
        if(funcGetTick() - currTick >= timeout){
            return false;
        }
    }

    return true;
}





void DrvRs485::OnISR_DMASendDone(void* args){
    DrvRs485* self = (DrvRs485*)args;

    if(self->m_sendSts != eHDuplexCommSts::AckOk){
        self->m_sendSts = eHDuplexCommSts::AckOk;
    }

    if(self->m_bEnableAutoFlow){
        self->FlowCtl(0);
    }
}

