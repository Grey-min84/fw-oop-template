#ifndef __ENC_ONEWAY_H__
#define __ENC_ONEWAY_H__
#include "board_config.h"


class IEncOneway{
public:
    virtual float GetPeriod_sec() = 0; 
    virtual float GetVelocity() = 0;
    virtual float GetOdometry() = 0;
};


class EncOneway : public IEncOneway{
public:

    //EncOneway();

    void Init(IPwm* _pwm, u32 _validCh, float _timerFreq, u32 _timerPeriod){
        pIPwm = _pwm;
        m_uiPwmCh = _validCh;
        m_fTimerFrq = _timerFreq;
        m_uiTimerPeriod = _timerPeriod;
    }

    void InitMechanicAttribute(float _fWheelDiameter, u32 _uiWheelToothCnt){
        fWheelDiameter = _fWheelDiameter;
        uiWheelToothCnt = _uiWheelToothCnt;
    }


    void CalcPeriodNFrq(){
        bool IsUpdated = false;
        int32_t iDiff = 0;
        
        if(pIPwm == nullptr){
            return;
        }

        m_uiIcVal = pIPwm->GetInputCaptureVal(&IsUpdated, m_uiPwmCh);

        if(IsUpdated){
            IsUpdated = false;
            m_uiNotMeasCnt = 0;
            m_uiCnt++;
            m_bLetCalcVel = true;

            if (m_uiIcVal > m_uiIcVal_pre) {
                iDiff = m_uiIcVal - m_uiIcVal_pre;
            }
            else {
                // 타이머 오버플로우 처리
                iDiff = (m_uiTimerPeriod - m_uiIcVal_pre) + m_uiIcVal;
            }

            // 주파수 계산
            m_fFrq = m_fTimerFrq / (float)iDiff; 
            m_fPeriod = 1.0f / m_fFrq;  // unit : second

            // 이전 값을 업데이트
            m_uiIcVal_pre = m_uiIcVal;

            // 캡처 플래그를 수동으로 클리어
            CalcVelocity();
        }
        else {
            m_uiNotMeasCnt++;

            if((m_uiNotMeasCnt % 500) == 0){
                m_fVel = m_fVel * 0.9f;
            }
        }

    }


    float GetPeriod_ms(){return  m_fPeriod*1000.0f;}

    float GetFrequency(){
        return m_fFrq;
    }


    /* ************************* Implement Interface ********************* */
    float GetVelocity() override{
        return m_fVel;
    }
    float GetOdometry() override{
        return CalcOdometry();
    }

    float GetPeriod_sec() override{
        return m_fPeriod;
    }
    /* ******************************************************************* */
private:

    float CalcVelocity(){

        if(m_bLetCalcVel){
            m_bLetCalcVel = false;
            
            float fUnitDist_mm = fWheelDiameter / (float)uiWheelToothCnt;

            // Unit : mm/sec -> Km/h
            m_fVel = ( fUnitDist_mm * 0.0036f) / m_fPeriod;
        }

        return m_fVel;
    }

    float CalcOdometry(){
        float fOdo = 0.0f;

        fOdo = m_uiCnt * fWheelDiameter / (float)uiWheelToothCnt;
        fOdo = fOdo / 1000.0f;
    
        return fOdo;
    }

    u32 m_uiPeriod_us;

    u32 m_uiIcVal = 0;
    u32 m_uiIcVal_pre = 0;

    IPwm* pIPwm = nullptr;
    u32 m_uiPwmCh;

    float m_fFrq = 0.0f;
    float m_fPeriod = 0.0f;

    float m_fTimerFrq;
    u32 m_uiTimerPeriod;

    u32 m_uiNotMeasCnt = 0;
    float fWheelDiameter;
    u32 uiWheelToothCnt;

    float m_fVel;
    u32 m_uiCnt = 0;

    bool m_bLetCalcVel = false;
};




#endif