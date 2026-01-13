#include "task_main.h"


extern ITimer* g_IHwTimer;

extern DoutContainer g_xDoutContainer;
extern QueueHandle_t g_xQueHnd_VMU_to_Main;
extern QueueHandle_t g_xQueHnd_Main_to_VMU;
extern u8 ReadDigitalInPin(eDInRank eRank);


TaskHandle_t g_xTaskHnd_main;


IBrake* g_pxIBrake = nullptr;
ISteer* g_pxISteer = nullptr;
IDrive* g_pxIDrive = nullptr;
ILidar* g_pxILidar = nullptr;



static UserTimer g_xMainTimer;
static IGpio* g_pLed_KeepAlive = nullptr;



void TaskMain(void *args);
void FuncTimeToAlive(void* args);

void TaskMainInit(){

    g_pLed_KeepAlive = KeepAliveLed_boardConfig();

    g_xMainTimer.SetTimerInterface(g_IHwTimer);
    g_xMainTimer.OnOffCtl(1);
    g_xMainTimer.RegisterCallback(FuncTimeToAlive, (void*)0, 10, true);


    xTaskCreate(TaskMain, "TaskMain", 512, nullptr, tskIDLE_PRIORITY + 3, &g_xTaskHnd_main);
}





void TaskMain(void *args){


    while(true){


        HAL_IWDG_Refresh(&hiwdg);


        vTaskDelay(1);
    }
}














void FuncTimeToAlive(void* args){

    static u32 ucTTLperiod = 0;


    if((ucTTLperiod%10) == 0){
        // Periodic Task every 1 second
        if(g_pLed_KeepAlive){
            g_pLed_KeepAlive->Toggle();
        }
    }

    

    ucTTLperiod++;
}

