#include "portSTM32_uart.h"

std::array<portSTM32Uart*, 6> portSTM32Uart::g_UartInstArr;
u8 portSTM32Uart::g_UartInstOrdIdx = 0;



bool portSTM32Uart::InitHw(UART_HandleTypeDef* huart){
    //refUartHw = huart;
    m_huart = huart;

    for(u8 idx = 0; idx<portSTM32Uart::g_UartInstOrdIdx; ++idx){
        if(m_huart == portSTM32Uart::g_UartInstArr[portSTM32Uart::g_UartInstOrdIdx]->GetHwPtr()){

            m_huart = nullptr;
            return false;
        }
    }

    portSTM32Uart::g_UartInstOrdIdx++;

    return true;
}





uint8_t portSTM32Uart::OpenPort(eUartRcvMode mode)  {

    uint8_t rtn = 0;

    if(m_huart == nullptr){

        PRINT_DBG("portSTM32Uart::OpenPort - UART HW is nullptr\r\n");
        return 10;
    }


    if(m_pstQueLinear == nullptr && m_pstQueCircle == nullptr){

        PRINT_DBG("portSTM32Uart::OpenPort - Queue is nullptr\r\n");
        return 3;
    }

    if(m_pstQueCircle != nullptr){
        m_pstQueCircle->Init();
    }

    if(m_pstQueLinear != nullptr){
        m_pstQueLinear->Init();
    }

    m_eRcvMode = mode;

    rtn = ResetRcv();

    if(rtn == 0){

        portSTM32Uart::g_UartInstArr[portSTM32Uart::g_UartInstOrdIdx++] = this;
        PRINT_DBG("%s - UART Opened\r\n", __FUNCTION__);
        return 0;
    }
    else {
    	return rtn;
    }
}



bool portSTM32Uart::ReadByteInQue(u8* ch){

    bool rtn = false;

    switch(m_eRcvMode){

        case eUartRcvMode::BUF_CIRCULAR:
        case eUartRcvMode::DMA_BUF_CIRCULAR:
            rtn = m_pstQueCircle->Dequeue(ch);
            break;

        case eUartRcvMode::DMA_BUF_LINEAR:
        case eUartRcvMode::BUF_LINEAR:
            rtn = m_pstQueLinear->Dequeue(ch);
            break;
        default:    break;
    }

    return rtn;
}


bool portSTM32Uart::IsDataAvailable() {
    bool rtn = false;

    switch(m_eRcvMode){

        case eUartRcvMode::BUF_CIRCULAR:
        case eUartRcvMode::DMA_BUF_CIRCULAR:
            rtn = !m_pstQueCircle->IsEmpty();
            break;

        case eUartRcvMode::DMA_BUF_LINEAR:
        case eUartRcvMode::BUF_LINEAR:
            rtn = !m_pstQueLinear->IsEmpty();
            break;
        default:    break;
    }

    return rtn;
}



void portSTM32Uart::PortReset(){

    // 2. UART 재초기화
    HAL_UART_DeInit(m_huart);

    HAL_Delay(10);

    HAL_UART_Init(m_huart);
}



void portSTM32Uart::StopRcv(){
    HAL_UART_DMAStop(m_huart);
}

uint8_t portSTM32Uart::ResetRcv(){

    uint8_t rtn = 0;

    switch(m_eRcvMode){
        
        case eUartRcvMode::DMA_BUF_CIRCULAR:
            if(m_pstQueCircle != nullptr && m_huart->hdmarx != nullptr){
                m_pstQueCircle->Refresh(QUEUE_CIRCULAR_SIZE);
                HAL_UART_Receive_DMA(m_huart, m_pstQueCircle->GetBufStartAddr(), QUEUE_CIRCULAR_SIZE);
				__HAL_DMA_DISABLE_IT(m_huart->hdmarx, DMA_IT_HT);
            }
            else {
                rtn = 1;
            }
            break;

        case eUartRcvMode::DMA_BUF_LINEAR:
            if(m_pstQueLinear != nullptr && m_huart->hdmarx != nullptr){
                m_pstQueLinear->Refresh();
                HAL_UARTEx_ReceiveToIdle_DMA(m_huart, m_pstQueLinear->rcvBuf, QUEUE_LINEAR_SIZE);
                __HAL_DMA_DISABLE_IT(m_huart->hdmarx, DMA_IT_HT);
            }
            else {
                rtn = 1;
            }
            
            break;

        case eUartRcvMode::BUF_LINEAR:
        case eUartRcvMode::BUF_CIRCULAR:
        default:
            rtn = 2;
            break;
    }

    return rtn;
}



u8 portSTM32Uart::SendDataDMA(u8* data, u16 len) {

    HAL_StatusTypeDef rtn = HAL_OK;
    //UART_HandleTypeDef huart = refUartHw->get();
    
    //HAL_UART_Transmit(&huart, (uint8_t*)data, strlen(data), HAL_MAX_DELAY);
    if(m_huart != nullptr && m_huart->hdmatx != nullptr)
        rtn =  HAL_UART_Transmit_DMA(m_huart , data, len);

    return (u8)rtn;
}



u8 portSTM32Uart::GetPortStatus(){

    uint8_t l_ucReturn = 0, l_ucFe = 0, l_ucPe = 0, l_ucOre = 0;

	l_ucFe = __HAL_UART_GET_FLAG(m_huart, UART_FLAG_FE);
	l_ucPe = __HAL_UART_GET_FLAG(m_huart, UART_FLAG_PE);
	l_ucOre = __HAL_UART_GET_FLAG(m_huart, UART_FLAG_ORE);

	l_ucReturn = l_ucFe ||  l_ucPe || l_ucOre;

	return l_ucReturn;
}




void portSTM32Uart::RegisterRcvCallback(eUartCbType type, std::function<void(void*)> callback, void* param)  {
    
    switch(type){
        case eUartCbType::RcvIdleDetect:
            RcvIdleDetCallback = callback;
            paramRcvIdleDet = param;
            break;

        case eUartCbType::TxDone:
            TxDoneCallback = callback;
            paramTxDone = param;
            break;

        default:    break;
    }
    
    //readCallback = callback;
}





// UART 인터럽트 발생 시 호출되는 메서드
void portSTM32Uart::OnISR_RcvIdleDetect(u16 size) {

    if(m_eRcvMode == eUartRcvMode::BUF_LINEAR || m_eRcvMode == eUartRcvMode::DMA_BUF_LINEAR){
        for(u16 idx=0; idx<size; ++idx){
            m_pstQueLinear->Enqueue(m_pstQueLinear->rcvBuf[idx]);
        }
    }

    if (RcvIdleDetCallback) {
        RcvIdleDetCallback(paramRcvIdleDet);  // 콜백 함수 호출
    }

    //uartHw.get();
}


void portSTM32Uart::OnISR_TxDone(){
    if (TxDoneCallback) {
        TxDoneCallback(paramTxDone);  // 콜백 함수 호출
    }
}







void portSTM32Uart::SetRcvQueuePtr(QueLinear* queLinear, QueDMACircular* queCircle, uint32_t* addr){
    m_pstQueLinear = queLinear;
    m_pstQueCircle = queCircle;
    if(m_pstQueCircle != nullptr){
        m_pstQueCircle->SetNDTRegister(addr);
    }
}




extern "C"{
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

    for(u8 idx=0; idx < portSTM32Uart::g_UartInstOrdIdx; ++idx){

            if(portSTM32Uart::g_UartInstArr[idx]->GetHwPtr() == huart){
                portSTM32Uart::g_UartInstArr[idx]->OnISR_TxDone();
            }
        }  
}

}


// UART 인터럽트 콜백 함수 (HAL 라이브러리에서 제공)
extern "C" {

    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    }

}


extern "C" {

    void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {

        for(u8 idx=0; idx < portSTM32Uart::g_UartInstOrdIdx; ++idx){

            if(portSTM32Uart::g_UartInstArr[idx]->GetHwPtr() == huart){
                portSTM32Uart::g_UartInstArr[idx]->OnISR_RcvIdleDetect(Size);
            }
        }
    }

}
