#ifndef _PORT_STM32_TIMER_H__
#define _PORT_STM32_TIMER_H__

extern "C" {
#include "stm32f4xx_hal.h"
#include "string.h"
}

#include "typeSimple.h"
#include "ITimer.h"





//class portSTM32Timer : public TimerInterface {
class portSTM32Timer : public ITimer {

public:
    portSTM32Timer()  { }

    void GetTimerInstace(TIM_HandleTypeDef* _pstTimerHandle);


    void StartHWTimer() override;

    void StopHWTimer() override;

    uint8_t RegisterTimer(UserTimer* _timer) override;

    uint8_t GetTimerOccupy() override { return m_ucRegisterCount; }


    void HWTimerCallback() override;

private:

    TIM_HandleTypeDef* m_pstTimerHandle;

};

#endif
