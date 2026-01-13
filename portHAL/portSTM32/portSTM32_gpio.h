#ifndef __PORT_STM32_GPIO_H__
#define __PORT_STM32_GPIO_H__

extern "C" {
#include "stm32f4xx_hal.h"
#include "string.h"
}

#include "typeSimple.h"
#include "IGpio.h"





class Stm32GpioPin : public IGpio {
private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
    GpioState currentState_;

public:
    Stm32GpioPin(GPIO_TypeDef* port, uint16_t pin)
        : port_(port), pin_(pin), currentState_(GpioState::LOW) {}
    
    // void setMode(GpioMode mode) override {
    //     GPIO_InitTypeDef GPIO_InitStruct = {0};
    //     GPIO_InitStruct.Pin = pin_;
    //     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        
    //     switch (mode) {
    //         case GpioMode::INPUT:
    //             GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    //             GPIO_InitStruct.Pull = GPIO_NOPULL;
    //             break;
                
    //         case GpioMode::OUTPUT:
    //             GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    //             GPIO_InitStruct.Pull = GPIO_NOPULL;
    //             break;
                
    //         case GpioMode::INPUT_PULLUP:
    //             GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    //             GPIO_InitStruct.Pull = GPIO_PULLUP;
    //             break;
                
    //         case GpioMode::INPUT_PULLDOWN:
    //             GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    //             GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    //             break;
                
    //         case GpioMode::OUTPUT_OPEN_DRAIN:
    //             GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    //             GPIO_InitStruct.Pull = GPIO_NOPULL;
    //             break;
    //     }
        
    //     HAL_GPIO_Init(port_, &GPIO_InitStruct);
    // }
    
    void Write(GpioState state) override {
        HAL_GPIO_WritePin(port_, pin_, 
                         state == GpioState::HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET);
        currentState_ = state;
    }
    
    GpioState Read() override {
        GPIO_PinState pinState = HAL_GPIO_ReadPin(port_, pin_);
        return (pinState == GPIO_PIN_SET) ? GpioState::HIGH : GpioState::LOW;
    }
    
    void Toggle() override {
        HAL_GPIO_TogglePin(port_, pin_);
        currentState_ = (currentState_ == GpioState::HIGH) ? 
                        GpioState::LOW : GpioState::HIGH;
    }
};




// 반드시 정적으로 생성할것!!
class FactoryGpioPin{

public:
    FactoryGpioPin(GPIO_TypeDef* port, uint16_t pin)
        : m_pin(port, pin) {
    }

    IGpio* GetGpioPin(){
        return &m_pin;
    }

private:
    Stm32GpioPin m_pin;
};




#endif
