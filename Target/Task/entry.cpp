
#include "board_config.h"

ITimer* g_IHwTimer = nullptr;
ICANBus* g_ICanBus = nullptr;

extern void TaskMainInit();
extern void InitAnalogFilter();
extern void CliTaskInit();
extern void InitModuleNetwork();
extern void InitCANComm(ICANBus* _pCanBus);
extern void InitDigitalInput();
extern void InitDigitalOutput();


void GR_EntryPoint(){
    // Entry Point
    g_IHwTimer = HardTimer_boardConfig();
    g_IHwTimer->StartHWTimer();

    g_ICanBus = MainCANBus_boardConfing();
    InitCANComm(g_ICanBus);

    InitAnalogFilter();

    InitDigitalInput();
    InitDigitalOutput();


    InitModuleNetwork();

    TaskMainInit();
    CliTaskInit();
}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

  if(htim == &htim6){

    g_IHwTimer->HWTimerCallback();
    
  }
}