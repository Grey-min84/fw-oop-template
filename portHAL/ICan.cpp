#include "ICan.h"
#include "main.h"







void CANDevice::InitCANDevice(u32 l_uiCanId, u32 l_uiIdMask) {

    m_uiTxId = l_uiCanId;
	m_uiIdMask = l_uiIdMask;
	//cb = _cb;
}



void CANDevice::SendMessage(u8* l_pData) {


	while(m_ucTxFlag != 0) ;

	if( l_pData != NULL )
		memcpy(m_pucTxData, l_pData, 8);

	m_ucTxFlag = 1;
}



//u8 CANDevice::ReadMessage(u8* l_pData, u32 l_ucTimeout, std::function<u32()> fpGetTick) {
u8 CANDevice::ReadMessage(u8* l_pData, u32 l_ucTimeout, u32(*fpGetTick)(void)) {

    u8 l_ucRet = 0xFF;
	u32 l_ucCurTIme;

	l_ucCurTIme = fpGetTick();

	while(m_ucRxFlag == 0)
	{
		if( fpGetTick() - l_ucCurTIme >= l_ucTimeout )
		{
			l_ucRet = 0x01;
			return l_ucRet;
		}

		//osDelay(1);
	}

	memcpy(l_pData, m_pucRxData, 8);
	m_ucRxFlag = 0;
	l_ucRet = 0;

	return l_ucRet;
}



void CANDevice::CheckRcv(u32 uiStdId, u8* pucRcvData){

        uint32_t l_uiIdMask = 0;

        l_uiIdMask = (uiStdId & m_uiIdMask) ;//.m_pCanDeviceList[i]->m_uiIdMask;
        if( m_uiIdMask == l_uiIdMask )
        {
            memcpy(m_pucRxData, pucRcvData, 8);
            
            if(cb)
                cb(m_vUser, uiStdId, m_pucRxData, 8);
            
            m_ucRxFlag = 1;
        }
    }



void CANDevice::EnrollBus(ICANBus* l_pstCanBus) {


    if(l_pstCanBus->g_ucDeviceUsedCnt < MAX_NR_OF_CAN_DEVICE )
	{
		l_pstCanBus->m_CANDeviceList[l_pstCanBus->g_ucDeviceUsedCnt] = this;
		l_pstCanBus->g_ucDeviceUsedCnt++;
	}
}
