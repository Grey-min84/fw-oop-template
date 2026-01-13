#ifndef __PORT_STM32_CAN_H__
#define __PORT_STM32_CAN_H__

extern "C" {
#include "stm32f4xx_hal.h"
#include "string.h"
}

#include "typeSimple.h"
#include "ICan.h"
#include <array>




class portStm32CANBus : public ICANBus {
public:
    portStm32CANBus(CAN_HandleTypeDef* _pCanInst) : pCanInst(_pCanInst){}

    void GetCANHw(CAN_HandleTypeDef* _pCanInst){
        pCanInst = _pCanInst;
    }

    void InitDriver() override;
    bool OpenCANBus() override;

    void RcvTask() override;
    void SendTask() override;

    ICANBus* GetBus() override {return this;}

    static void portRxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

private:

    CAN_HandleTypeDef* pCanInst;

    CAN_FilterTypeDef m_stCanFilter;
	CAN_TxHeaderTypeDef m_stTxMsgHeader;
	CAN_RxHeaderTypeDef m_stRxMsgHeader;
	
	//uint8_t m_ucCanTransFlag;
};












#endif