#ifndef __DIGITAL_OUT_H__
#define __DIGITAL_OUT_H__

#include "board_config.h"



enum class eDoutPhase{
    IDLE = 0,
    OFF,
    ON,
    ON_START,
    OFF_START,
    END,
};




typedef struct DoutPattNode_tag{
    u16 usOnTime;
    u16 usOffTime;
    u8 ucRepeatCnt;
    struct DoutPattNode_tag* next;

    // != 연산자 오버로딩
    bool operator!=(const DoutPattNode_tag& other) const {
        return (usOnTime != other.usOnTime) ||
               (usOffTime != other.usOffTime) ||
               (ucRepeatCnt != other.ucRepeatCnt) ||
               (next != other.next);
    }
    
    // 선택사항: == 연산자도 함께 정의하는 것이 좋습니다
    bool operator==(const DoutPattNode_tag& other) const {
        return (usOnTime == other.usOnTime) &&
               (usOffTime == other.usOffTime) &&
               (ucRepeatCnt == other.ucRepeatCnt) &&
               (next == other.next);
    }
    
}DoutPattNode_t;



extern DoutPattNode_t g_xPattern_off;
extern DoutPattNode_t g_xPattern_on;


class DOutControl{
public:

    void Init(DoutPattNode_t* _header, DoutPattNode_t* _defOffPatt, IGpio* _pin){
        header = _header;
        pxPin = _pin;
        ePhase = eDoutPhase::IDLE;
        pxDefOffPatt = _defOffPatt;
    }

    void Reset(bool _IsPrior){
        currNode = header;
        ucCurrRepeat = 0;
        ePhase = eDoutPhase::ON_START;

        IsPrior = _IsPrior;
    }


    void ChangePattern(DoutPattNode_t* _header, bool _IsPrior){

    	if(IsPrior){
    		return;
    	}

        header = _header;
        Reset(_IsPrior);
    }

    

    void OutCtl(){
        switch (ePhase)
        {
            case eDoutPhase::IDLE:  
                pxPin->Write(GpioState::LOW);
                break;

            case eDoutPhase::ON_START:
                if(currNode->usOnTime >0){
                    pxPin->Write(GpioState::HIGH);
                    ePhase = eDoutPhase::ON;
                    usTick = currNode->usOnTime;
                }
                else {
                    ePhase = eDoutPhase::OFF_START;
                }
                break;

            case eDoutPhase::ON:
                if(usTick == 0){
                    ePhase = eDoutPhase::OFF_START;
                    break;
                }
                else {
                    usTick--;
                    pxPin->Write(GpioState::HIGH);
                }
                break;

            case eDoutPhase::OFF_START:
                usTick = currNode->usOffTime;
                pxPin->Write(GpioState::LOW);
                ePhase = eDoutPhase::OFF;
                break;

            case eDoutPhase::OFF:
                if(usTick == 0){

                    ucCurrRepeat++;

                    if(ucCurrRepeat == currNode->ucRepeatCnt){

                        if(currNode->next){
                            currNode = currNode->next;
                            ucCurrRepeat = 0;
                            ePhase = eDoutPhase::ON_START;
                        }
                        else {
                            ePhase = eDoutPhase::IDLE;
                        }

                        IsPrior = false;
                        
                    }
                    else {
                        ePhase = eDoutPhase::ON_START;
                    }
                    break;
                }
                else {
                    usTick--;
                }

                pxPin->Write(GpioState::LOW);
                break;
            
            
            default:
                pxPin->Write(GpioState::LOW);
                break;
        }
    }


    void GMUPatternRcv(u16 usOnTm, u16 usOffTm, u8 ucRepeatTm){
        DoutPattNode_t xRcvNew;

        if(IsPrior){
            return;
        }

        xRcvNew.usOnTime = usOnTm;
        xRcvNew.usOffTime = usOffTm;
        xRcvNew.ucRepeatCnt = ucRepeatTm;
        xRcvNew.next = pxDefOffPatt;

        if(xRcvNew != xGMUPattern){
            xGMUPattern = xRcvNew;

            header = &xGMUPattern;
            Reset(false);
        }
    }




    void DigitOutTest(){
        ePhase = eDoutPhase::ON_START;
        ucCurrRepeat = 0;
        IsPrior = true;

        currNode->next = nullptr;
        currNode->ucRepeatCnt = 3;
        currNode->usOnTime = 25;
        currNode->usOffTime = 25;
    }


    void DigitOutTest_AlwaysOn(){
        ePhase = eDoutPhase::ON_START;
        ucCurrRepeat = 0;
        IsPrior = true;

        currNode = &g_xPattern_on;
    }

    void DigitOutTest_AlwaysOff(){
        ePhase = eDoutPhase::ON_START;
        ucCurrRepeat = 0;
        IsPrior = false;

        currNode = &g_xPattern_off;
    }

    


private:
    DoutPattNode_t* header;
    DoutPattNode_t* currNode;
    DoutPattNode_t* pxDefOffPatt;

    DoutPattNode_t xGMUPattern;
    IGpio* pxPin;

    eDoutPhase ePhase;
    u16 usTick;
    u8 ucCurrRepeat;
    bool IsPrior;
};

#define MAX_DOUT_PINS       (10)


class DoutContainer{
public:
    DoutContainer() {
        for(u8 idx=0; idx<MAX_DOUT_PINS; ++idx){
            array[idx] = nullptr;
        }
    }

    

    bool Add(DOutControl* _in){
        if(count >= MAX_DOUT_PINS){
            return false;
        }

        array[count++] = _in;

        return true;
    }

    bool AddIn(DOutControl* _in, eDOutRank pos){
        array[(u8)pos] = _in;

        return true;
    }

    void Operation(){
        for(u8 idx=0; idx<MAX_DOUT_PINS; ++idx){
            if(array[idx])
                array[idx]->OutCtl();
        }
    }

    DOutControl* GetDoutPin(eDOutRank pos){
        if(array[(u8)pos]){
            return array[(u8)pos];
        }

        return nullptr;
    }

    void DoutTest(eDOutRank pos){
        array[(u8)pos]->DigitOutTest();
    }

    void DoutTest_alwaysOn(eDOutRank pos){
        array[(u8)pos]->DigitOutTest_AlwaysOn();
    }

    void DoutTest_alwaysOff(eDOutRank pos){
        array[(u8)pos]->DigitOutTest_AlwaysOff();
    }

private:
    u8 count;
    DOutControl* array[MAX_DOUT_PINS];
};




#endif
