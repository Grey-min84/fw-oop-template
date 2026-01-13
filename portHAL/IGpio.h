#ifndef __IGPIO_H__
#define __IGPIO_H__

#include "typeSimple.h"
#include "portSTM32_timer.h"


#define GPI_FILTER_ON       (1)
#define GPI_FILTER_OFF      (0)

#define MAX_GPIO_LIST_NUM   (32)

// GPIO 핀 모드
enum class GpioMode {
    INPUT,
    OUTPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    OUTPUT_OPEN_DRAIN
};

// GPIO 핀 상태
enum class GpioState {
    LOW = 0,
    HIGH = 1
};

enum class eGpioMode{
    Input = 0,
    Output,
    Interrupt,
};


class IGpio{
public:
    virtual ~IGpio() = default;
    
    // 핀 모드 설정
    //virtual void setMode(GpioMode mode) = 0;
    
    // 디지털 출력
    virtual void Write(GpioState state) = 0;
    
    // 디지털 입력
    virtual GpioState Read() = 0;
    
    // 토글
    virtual void Toggle() = 0;    
};












#endif
