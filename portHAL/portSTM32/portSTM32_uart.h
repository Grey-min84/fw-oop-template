#ifndef __PORT_STM32_UART_H__
#define __PORT_STM32_UART_H__

#include <optional>

extern "C" {
#include "stm32f4xx_hal.h"
#include "string.h"
}

#include "typeSimple.h"
#include "IUart.h"
#include "byteQueue.h"




class portSTM32Uart : public IUart {
public:
	portSTM32Uart() : m_huart(nullptr) {
       // m_huart = nullptr;
    }

	bool InitHw(UART_HandleTypeDef* huart);

    UART_HandleTypeDef* GetHwPtr(){return m_huart;}

    uint8_t OpenPort(eUartRcvMode mode) override ;

    uint8_t ResetRcv() override;

    void PortReset() override;

    void StopRcv() override;

    u8 SendDataDMA(u8* data, u16 len) override;

    bool ReadByteInQue(u8* ch) override;

    bool IsDataAvailable() override ;

    u8 GetPortStatus() override;

    void RegisterRcvCallback(eUartCbType type, std::function<void(void*)> callback, void* param) override;

    void SetRcvQueuePtr(QueLinear* queLinear, QueDMACircular* queCircle, uint32_t* addr) override;

    // UART 인터럽트 발생 시 호출되는 메서드
    void OnISR_RcvIdleDetect(u16 size) override;
    void OnISR_TxDone() override;



    


    //------------------------------------------------------
    static std::array<portSTM32Uart*, 6> g_UartInstArr;
    static u8 g_UartInstOrdIdx;

private:
    UART_HandleTypeDef* m_huart;
    eUartRcvMode m_eRcvMode;
    
    std::function<void(void*)> RcvIdleDetCallback = nullptr;
    std::function<void(void*)> TxDoneCallback = nullptr;

    void* paramTxDone;
    void* paramRcvIdleDet;


    QueLinear* m_pstQueLinear;
    QueDMACircular* m_pstQueCircle;

    //static std::vector<portSTM32Uart*> g_UartInstVec;
};







#endif
