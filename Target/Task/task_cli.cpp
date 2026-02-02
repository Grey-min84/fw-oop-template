#include "cli.h"
#include "board_config.h"
#include "cli_main.h"
#include "task_main.h"

// #include "steer_ctl.h"
// #include "drive_ctl.h"

#define DEF_CLI_CH  0


static TaskHandle_t g_xTaskHnd_cli;

UnitTestMain g_xTestMainCtl;





extern DigitFiltNode_t* g_pxDigitFiltHeader;
extern DoutContainer g_xDoutContainer;

void TaskCli(void* args);

void CliTaskInit(){

    cliInit((void*)&g_xTestMainCtl);
    cliOpen(DEF_CLI_CH, &huart1);
    cliAdd("system", cliSystemSetup, (void*)&g_xTestMainCtl, 1);


    xTaskCreate(TaskCli, "TaskCli", 1024, nullptr, tskIDLE_PRIORITY + 3, &g_xTaskHnd_cli);
}


void TaskCli(void* args){


    cliAdd("digital_in", CliDigital_In, (void*)g_pxDigitFiltHeader, 0);
    cliAdd("digital_out", CliDigital_Out, (void*)&g_xDoutContainer, 0);

    cliPrintf("\r\n\r\nGR-A Series Unit Test is now possible\r\n");
    cliPrintf("\r\n");

    u8 ucTestMode_pre = 0;

    while(true){

        uint8_t bIsLogPossible = 0;

        bIsLogPossible = cliMain();


        DigitalIn_TestCtl(g_pxDigitFiltHeader);

        if(g_xTestMainCtl.bIsTestOn != ucTestMode_pre){
            
            if(g_xTestMainCtl.bIsTestOn != 0){
                //cliPrintf("GR Unit Test Mode On\r\n");
                xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFY_CLI_TEST_BTN, (uint32_t)1, eSetValueWithOverwrite );
            }
            else {
                //cliPrintf("GR Unit Test Mode Off\r\n");
                xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFY_CLI_TEST_BTN, (uint32_t)0, eSetValueWithOverwrite );
            }
        }

        ucTestMode_pre = g_xTestMainCtl.bIsTestOn;

        vTaskDelay(10);
    }
}
