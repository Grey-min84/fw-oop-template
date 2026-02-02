#include "board_config.h"
#include "halfDupl_master.hpp"
#include "brakeCtlMod.h"
#include "powerCtlMod.h"
#include "digital_out.hpp"

#define COMM_PERIOD         (20)


extern IBrake* g_pxIBrake;
extern ITimer* g_IHwTimer;

IGpio* g_pxBcmLed;


TaskHandle_t g_xTaskHnd_ModNet;
TaskHandle_t g_xTaskHnd_ModNetHelp;
SemaphoreHandle_t g_xHelperSemaphore;

HalfDuplMaster g_xBusMaster;

DrvRs485* g_pxRs485Bus;

IRs485Device* pxBusSlave_bcm;
IRs485Device* pxBusSlave_pcm;

BrakeCtlModule xBcm;
PowerCtlModule xPcm;




static UserTimer g_xTimerForCommSync;


static void TaskModNetwork(void* args);
static void TaskNetworkHelp(void* args);
static void LedControl(eBCM_ErrCode, ePCM_ErrCode);
static void TimerCommTimingChk(void* args);


void InitModuleNetwork(){

    xBcm.Init(COMM_PERIOD);
    xBcm.InitTest();
    xPcm.Init(COMM_PERIOD);

    

    pxBusSlave_bcm = (IRs485Device*)&xBcm;
    pxBusSlave_pcm = (IRs485Device*)&xPcm;

    

    g_pxRs485Bus = ModuleNetworkPort_boardConfig(g_pxBcmLed);

    g_xHelperSemaphore = xSemaphoreCreateBinary();

    //g_pxBus->AvailableSendDoneCheck(true);
    xTaskCreate(TaskModNetwork, "TaskModNet", 1024, nullptr, tskIDLE_PRIORITY + 3, &g_xTaskHnd_ModNet);
    //xTaskCreate(TaskNetworkHelp, "ModeNetHelp", 256, nullptr, tskIDLE_PRIORITY + 5, &g_xTaskHnd_ModNetHelp);


    // g_xTimerForCommSync.SetTimerInterface(g_IHwTimer);
    // g_xTimerForCommSync.OnOffCtl(0);
    // g_xTimerForCommSync.RegisterCallback(TimerCommTimingChk, (void*)&g_xBusMaster, COMM_PERIOD, false);


    g_pxIBrake = (IBrake*)&xBcm;


}


static void TaskModNetwork(void* args){


    SlaveList_t xDeviceList[3] = {
        {0, pxBusSlave_bcm, &xDeviceList[1]},
        {0, pxBusSlave_bcm, &xDeviceList[2]},
        {1, pxBusSlave_pcm, &xDeviceList[0]},
    };


    g_xBusMaster.Init(g_pxRs485Bus);
    g_xBusMaster.SetDeviceList(&xDeviceList[0]);


    while(true){

        g_xBusMaster.Process(HAL_GetTick, vTaskDelay);

        vTaskDelay(1);
        
    }
}





static void TaskNetworkHelp(void* args){

    // 이 태스크는 최고 우선순위로 실행
    // 오직 통신 태스크의 우선순위 관리만 담당
    
    while(1) {
        // 세마포어 대기 (무한 대기)
        if(xSemaphoreTake(g_xHelperSemaphore, portMAX_DELAY) == pdTRUE) {
            
            // 통신 태스크 우선순위 부스트
            vTaskPrioritySet(g_xTaskHnd_ModNet, tskIDLE_PRIORITY + 5);
            
            
            g_xTimerForCommSync.OnOffCtl(0);
            
            // 통신 태스크에 슬롯 시작 알림
            //xTaskNotifyGive(g_commSys.hCommTask);
            
            // 즉시 다시 대기 상태로 (CPU 양보)
        }
    }
}






static void TimerCommTimingChk(void* args){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
    // 보조 태스크 깨우기 (세마포어)
    xSemaphoreGiveFromISR(g_xHelperSemaphore, &xHigherPriorityTaskWoken);
    
    // 보조 태스크로 즉시 전환
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


