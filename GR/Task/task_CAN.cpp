#include "board_config.h"

static TaskHandle_t g_xTaskHnd_CANComm;



void TaskCanManage(void* args);

void InitCANComm(ICANBus* _pCanBus){


    xTaskCreate(TaskCanManage, "TaskGmuTx", 256, (void*)_pCanBus, tskIDLE_PRIORITY + 3, &g_xTaskHnd_CANComm);
}



void TaskCanManage(void* args){

    ICANBus* pCanBus = (ICANBus*)args;


    while(true){

        pCanBus->RcvTask();
        pCanBus->SendTask();

        vTaskDelay(5);
    }


}
