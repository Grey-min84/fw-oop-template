#include "portSTM32_timer.h"



void portSTM32Timer::GetTimerInstace(TIM_HandleTypeDef* _pstTimerHandle){

    m_pstTimerHandle = _pstTimerHandle;
    m_ucRegisterCount = 0;
    m_usTmState = eTimerStatus::Stopped;
}



void portSTM32Timer::StartHWTimer()  {
    if(m_pstTimerHandle == nullptr){
        return;
    }
    HAL_TIM_Base_Start_IT(m_pstTimerHandle);
    m_usTmState = eTimerStatus::Started;
}


void portSTM32Timer::StopHWTimer() {
    if(m_pstTimerHandle == nullptr){
        return;
    }
    HAL_TIM_Base_Stop_IT(m_pstTimerHandle);
    m_usTmState = eTimerStatus::Stopped;
}



uint8_t portSTM32Timer::RegisterTimer(UserTimer* _timer){

    m_pTimer[m_ucRegisterCount++] = _timer;

    return m_ucRegisterCount;
}



void portSTM32Timer::HWTimerCallback(){

    if(m_pstTimerHandle == nullptr){
        return;
    }

    for( int i=0 ; i<m_ucRegisterCount ; i++) {
    
        m_pTimer[i]->TimerMain();
        
    }
}