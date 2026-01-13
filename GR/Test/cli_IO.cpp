#include "cli_IO.h"




static u8 g_ucDigitInTestOn = 0;

void DigitalIn_TestCtl(DigitFiltNode_t* pxDigitIn){

    static u8 aucPinSts_pre[10] = {0x0,};

    if(g_ucDigitInTestOn != 0){

        u8 ucPinSts = 0;
        DigitFiltNode_t* currNode = pxDigitIn->next;

        for(u8 idx=0; currNode->pxPin != nullptr; idx++){

            ucPinSts = currNode->m_ucFilterVal;

            if(ucPinSts != aucPinSts_pre[idx]){

                switch(idx){
                    case 0: // Mode Button
                        cliPrintf("Mode Button(%d) State Changed [%d] -> [%d]\r\n", idx, aucPinSts_pre[idx], ucPinSts);
                        break;

                    case 1: // Booster Button
                        cliPrintf("Booster Button(%d) State Changed [%d] -> [%d]\r\n", idx, aucPinSts_pre[idx], ucPinSts);
                        cliPrintf("\r\n");
                        break;

                    case 2: // Staff Button
                        cliPrintf("Staff Button(%d) State Changed [%d] -> [%d]\r\n", idx, aucPinSts_pre[idx], ucPinSts);
                        cliPrintf("\r\n");
                        break;
                }
                
            }

            aucPinSts_pre[idx] = ucPinSts;

            currNode = currNode->next;
        }
    }
            

}

void CliDigital_In(cli_args_t *args, void* param){

    //DigitFiltNode_t* pxDigitInHeader = (DigitFiltNode_t*)param;


    if( args->isStr(0, "monitoring") == 1 ){

        if(args->isStr(1, "on") == 1){
            g_ucDigitInTestOn = 1;
            cliPrintf("Digital Input Monitoring Start~\r\n\r\n");

        }
        else if(args->isStr(1, "off") == 1 ){
            g_ucDigitInTestOn = 0;
            cliPrintf("Digital Input Monitoring Stop!!\r\n\r\n");

        }

    }
    else {
        cliPrintf("digital_in monitoring on/off\r\n");
    }

}


void CliDigital_Out(cli_args_t *args, void* param){

    DoutContainer* pxDoutContainer = (DoutContainer*)param;

    if( args->isStr(0, "test") == 1 ){

        int temp = args->getData(1);

        if(0 <= temp && temp < MAX_DOUT_PINS){
            pxDoutContainer->DoutTest((eDOutRank)temp);
        }
    }
    else if( args->isStr(0, "always_on") == 1 ){

        int temp = args->getData(1);

        if(0 <= temp && temp < MAX_DOUT_PINS){
            pxDoutContainer->DoutTest_alwaysOn((eDOutRank)temp);
        }
    }
    else if( args->isStr(0, "always_off") == 1 ){

        int temp = args->getData(1);

        if(0 <= temp && temp < MAX_DOUT_PINS){
            pxDoutContainer->DoutTest_alwaysOff((eDOutRank)temp);
        }
    }
    else {
        cliPrintf("digital_out test [0~9]\r\n");
        cliPrintf("digital_out always_on [0~9]\r\n");
        cliPrintf("digital_out always_off [0~9]\r\n");
        cliPrintf("Dout #0 : Buzzor\r\n");
        cliPrintf("Dout #1 : Sts. Left Light\r\n");
        cliPrintf("Dout #2 : Sts. Right Light\r\n");
        cliPrintf("Dout #3 : Brake Light\r\n");
    }
}




