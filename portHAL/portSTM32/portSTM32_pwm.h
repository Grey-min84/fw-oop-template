#ifndef __PORT_STM32_PWM_H__
#define __PORT_STM32_PWM_H__

#include "main.h"
#include "IPwm.h"

class portSTM32_Pwm : public IPwm{

public:
    portSTM32_Pwm(TIM_HandleTypeDef* _pwmSrc, u32 _ch1) : m_pwmSrc(_pwmSrc) {
        m_uiCh1 = _ch1;
        m_uiCh2 = UINT32_MAX;
        m_uiCh3 = UINT32_MAX;
        m_uiCh4 = UINT32_MAX;
    }

    portSTM32_Pwm(TIM_HandleTypeDef* _pwmSrc, u32 _ch1, u32 _ch2) : m_pwmSrc(_pwmSrc) {
        m_uiCh1 = _ch1;
        m_uiCh2 = _ch2;
        m_uiCh3 = UINT32_MAX;
        m_uiCh4 = UINT32_MAX;
    }

    void GetPwmSrcTimer(TIM_HandleTypeDef* _timer){
        m_pwmSrc = _timer;
    }


    void StartStopPwm(bool onOff) override {

        if(onOff){
            if(m_uiCh1 != UINT32_MAX)
                HAL_TIM_PWM_Start(m_pwmSrc, m_uiCh1);

            if(m_uiCh2 != UINT32_MAX)
                HAL_TIM_PWM_Start(m_pwmSrc, m_uiCh2);

            if(m_uiCh3 != UINT32_MAX)
                HAL_TIM_PWM_Start(m_pwmSrc, m_uiCh3);

            if(m_uiCh4 != UINT32_MAX)
                HAL_TIM_PWM_Start(m_pwmSrc, m_uiCh4);
        }
        else {
            if(m_uiCh1 != UINT32_MAX)
                HAL_TIM_PWM_Stop(m_pwmSrc, m_uiCh1);

            if(m_uiCh1 != UINT32_MAX)
                HAL_TIM_PWM_Stop(m_pwmSrc, m_uiCh2);

            if(m_uiCh1 != UINT32_MAX)
                HAL_TIM_PWM_Stop(m_pwmSrc, m_uiCh3);

            if(m_uiCh1 != UINT32_MAX)
                HAL_TIM_PWM_Stop(m_pwmSrc, m_uiCh4);
        }

        uiMaxPeriod = m_pwmSrc->Init.Period;
        
    }

    void PwmControl_Single_Ch1(u32 _usDuty ) override {

        if(m_uiCh1 == UINT32_MAX)   return;

        __HAL_TIM_SET_COMPARE(m_pwmSrc, m_uiCh1, _usDuty) ;
    }

    void PwmControl_Single_Ch2(u32 _usDuty ) override {

        if(m_uiCh2 == UINT32_MAX)   return;

        __HAL_TIM_SET_COMPARE(m_pwmSrc, m_uiCh2, _usDuty) ;
    }

    void PwmControl_DualCh(u32 _usDuty) override {

        if(m_uiCh1 == UINT32_MAX || m_uiCh2 == UINT32_MAX)   return;

        __HAL_TIM_SET_COMPARE(m_pwmSrc, m_uiCh1, _usDuty) ;
        __HAL_TIM_SET_COMPARE(m_pwmSrc, m_uiCh2, _usDuty) ;
    }

    void PwmOnOff(bool onOff, u32 _uiCh) override {
        if(onOff){
            HAL_TIM_PWM_Start(m_pwmSrc, _uiCh);
        }
    }


    // ---------------------- Input Capture Mode --------------------------
    void InputCaptureOnOff(bool onOff, u32 _uiCh) override {

        if(onOff){
            HAL_TIM_IC_Start(m_pwmSrc, _uiCh);
        }
        else {
            HAL_TIM_IC_Stop(m_pwmSrc, _uiCh);
        }
    }

    u32 GetInputCaptureVal(bool* pbIsUpdated, u32 _uiCh) override {

        if(__HAL_TIM_GET_FLAG(m_pwmSrc, TIM_FLAG_CC1) != RESET){
            
            *pbIsUpdated = true;
            __HAL_TIM_CLEAR_FLAG(m_pwmSrc, TIM_FLAG_CC1);
            return __HAL_TIM_GET_COMPARE(m_pwmSrc, _uiCh);
        }
        else {
            *pbIsUpdated = false;
            return 0;
        }
    }

    bool IsOverFlowDetected() override {
        return false;
    }



    // ---------------------- Encoder Mode --------------------------
    void EncoderModeOnOff(bool onOff) override {
        if(onOff){
            HAL_TIM_Encoder_Start(m_pwmSrc, TIM_CHANNEL_ALL);
        }
        else {
            HAL_TIM_Encoder_Stop(m_pwmSrc, TIM_CHANNEL_ALL);
        }
        
    }


    u32 GetEncoderCount() override {
        return __HAL_TIM_GET_COUNTER(m_pwmSrc);
    }

    
protected:
    u32 m_uiCh1;
    u32 m_uiCh2;
    u32 m_uiCh3;
    u32 m_uiCh4;

    
private:

    TIM_HandleTypeDef* m_pwmSrc;
    

};



#endif
