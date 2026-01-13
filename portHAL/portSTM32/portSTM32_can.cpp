#include "portSTM32_can.h"


std::array<ICANBus*, STM32_MAX_CAN_BUS> ICANBus::m_CANBusList = {nullptr,};
u8 ICANBus::g_ucBusUsedCnt = 0;


void portStm32CANBus::InitDriver(){

}



bool portStm32CANBus::OpenCANBus(){

    for( int i=0 ; i<g_ucBusUsedCnt ; i++ )
	{
		if(  m_CANBusList[g_ucBusUsedCnt] == this )
			return false;
	}

    m_CANBusList[g_ucBusUsedCnt++] = this;

    if(g_ucBusUsedCnt > STM32_MAX_CAN_BUS){return false;}


    m_stCanFilter.FilterMaskIdHigh = 0;
	m_stCanFilter.FilterMaskIdLow = 0;
	m_stCanFilter.FilterBank = 0;
	m_stCanFilter.FilterMode = CAN_FILTERMODE_IDMASK;//CAN_FILTERMODE_IDLIST;
	m_stCanFilter.FilterScale = CAN_FILTERSCALE_16BIT;
	m_stCanFilter.FilterIdHigh = 0;
	m_stCanFilter.FilterIdLow = 0;
	m_stCanFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	m_stCanFilter.FilterActivation = ENABLE;

    HAL_CAN_ConfigFilter(pCanInst, &m_stCanFilter);
	HAL_CAN_ActivateNotification(pCanInst, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Start(pCanInst);

	return true;
}



void portStm32CANBus::RcvTask(){

    //uint32_t l_uiIdMask = 0;

    if( m_ucCanRecvFlag  != 0)
    {
        for( int idx= 0 ; idx < g_ucDeviceUsedCnt ; idx++ )
        {
            m_CANDeviceList[idx]->CheckRcv( m_stRxMsgHeader.StdId, m_pucCanRxData);

            // l_uiIdMask = m_stRxMsgHeader.StdId & m_CANDeviceList[idx]->m_uiIdMask ;//.m_pCanDeviceList[i]->m_uiIdMask;
            // if( m_CANDeviceList[idx]->m_uiIdMask == l_uiIdMask )
            // {
            //     memcpy(m_CANDeviceList[idx]->m_pucRxData, m_pucCanRxData, 8);

            //     m_CANDeviceList[idx]->cb(m_stRxMsgHeader.StdId, m_CANDeviceList[idx]->m_pucRxData, 8);
                
            //     m_CANDeviceList[idx]->m_ucRxFlag = 1;
            // }
        }

        m_ucCanRecvFlag = 0;
    }

}


void portStm32CANBus::SendTask(){

    uint32_t l_uiTxMailBox = 0;

    for( int j=0 ; j<g_ucDeviceUsedCnt ; j++ )
    {
        if( m_CANDeviceList[j]->m_ucTxFlag )
        {
            m_stTxMsgHeader.RTR = CAN_RTR_DATA;
            m_stTxMsgHeader.IDE = CAN_ID_STD;
            m_stTxMsgHeader.DLC = 8;
            m_stTxMsgHeader.StdId = m_CANDeviceList[j]->m_uiTxId;

            l_uiTxMailBox = HAL_CAN_GetTxMailboxesFreeLevel(pCanInst);
            HAL_CAN_AddTxMessage(pCanInst, &m_stTxMsgHeader, m_CANDeviceList[j]->m_pucTxData, &l_uiTxMailBox);
            m_CANDeviceList[j]->m_ucTxFlag = 0;
        }
    }
}






void portStm32CANBus::portRxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

    for( int i = 0 ; i<g_ucBusUsedCnt ; i++ )
	{
        portStm32CANBus* pCanBus = (portStm32CANBus*)m_CANBusList[i];

		if( hcan->Instance == pCanBus->pCanInst->Instance )
		{
			HAL_CAN_GetRxMessage( pCanBus->pCanInst, CAN_RX_FIFO0, &pCanBus->m_stRxMsgHeader, pCanBus->m_pucCanRxData);
			pCanBus->m_ucCanRecvFlag = 1;
		}
	}

}




    // CAN Interrupt
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	portStm32CANBus::portRxFifo0MsgPendingCallback(hcan);
}
