#ifndef __IADC_H__
#define __IADC_H__

#include "typeSimple.h"
#include "portSTM32_adc.h"

class AdcInterface{
public:
    virtual uint8_t ADCStartDMA(uint16_t* u16Val, uint8_t cnt) = 0;
    virtual uint8_t ADCStartDMA(uint32_t* u32Val, uint8_t cnt) = 0;
    virtual uint8_t ADCStartDMA(uint8_t* u8Val, uint8_t cnt) = 0;
    virtual void ADCStart() = 0;
private:
};





#endif
