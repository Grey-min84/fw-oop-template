#ifndef __PORT_STM32_ADC_H__
#define __PORT_STM32_ADC_H__

#include "IAdc.h"
#include "main.h"

class portSTM32Adc : public AdcInterface{
public:
    portSTM32Adc(ADC_HandleTypeDef* _adc) : m_adcInst(_adc) {

    }

    void GetAdcHw(ADC_HandleTypeDef* _adc){
        m_adcInst = _adc;
    }

    uint8_t ADCStartDMA(uint16_t* u16Val, uint8_t cnt) override{
        return (uint8_t)HAL_ADC_Start_DMA(m_adcInst, (uint32_t *)u16Val, cnt);
    }

    uint8_t ADCStartDMA(uint8_t* u8Val, uint8_t cnt) override{
        return (uint8_t)HAL_ADC_Start_DMA(m_adcInst, (uint32_t *)u8Val, cnt);
    }

    uint8_t ADCStartDMA(uint32_t* u32Val, uint8_t cnt) override{
        return (uint8_t)HAL_ADC_Start_DMA(m_adcInst, (uint32_t *)u32Val, cnt);
    }

    void ADCStart() override{

    }


private:
    ADC_HandleTypeDef* m_adcInst;     
};

#endif
