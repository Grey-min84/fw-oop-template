#include "cli_main.h"


void cliSystemSetup(cli_args_t *args, void* param){

  uint8_t rtn = 0;
  UnitTestMain* pxTestCmd = (UnitTestMain*)param;


  if(args->isStr(0, "test") == 1){

         if(args->isStr(1, "on") == 1){

           cliTestEnable(1);
           pxTestCmd->bIsTestOn = 1;
           rtn = 1;
         }
         else if(args->isStr(1, "off") == 1){

           cliTestEnable(0);
           pxTestCmd->bIsTestOn = 0;
           rtn = 1;
         }

    }

    else if(args->isStr(0, "factory_test") == 1){

       

    }
    else if(args->isStr(0, "reset") == 1){

        cliPrintf("system reset after 1sec...\r\nCount down - ");

        for(uint32_t idx=0; idx<10;++idx){
          HAL_Delay(100);
          cliPrintf("%d.", 10- idx);
        }

        cliPrintf("0\r\n");
        __NVIC_SystemReset();
    }
    else if(args->isStr(0, "head_light") == 1){

    }
    else {
      cliPrintf("system test [on/off]\r\n");
      cliPrintf("system log [on/off]\r\n");
      cliPrintf("system gmu_msg [on/off]\r\n");
      cliPrintf("system self_drive [on/off]\r\n");
      cliPrintf("system self_drive param [spd] [predTm] [predRatio]\r\n");
      cliPrintf("system factory_test [on/off]\r\n");
      cliPrintf("system head_light [on/off]\r\n");
      cliPrintf("system reset\r\n");
      rtn = 1;
    }

    if(rtn  == 0){
      cliPrintf("system test [on/off]\r\n");
      cliPrintf("system reset\r\n");
    }
    else {
      cliPrintf("OK\r\n");
    }
}
