
#include "board_config.h"
#include "digital_out.hpp"
#include "bzLight_pattern.h"
#include "task_main.h"

extern ITimer* g_IHwTimer;



TaskHandle_t g_xTaskHnd_DigitOut;
DigitFiltNode_t* g_pxDigitFiltHeader;

IGpio* g_pxGpiModeBtn;
IGpio* g_pxGpiBoostBtn;
IGpio* g_pxGpiStaffBtn;
IGpio* g_pxGpiEmergBtn;


IGpio* g_pxGpoBuzzor;
IGpio* g_pxGpoBoostLed;
IGpio* g_pxGpoHeadlight;

IGpio* g_pxGpoBrakeLight;
IGpio* g_pxGpoStsLeftLight;
IGpio* g_pxGpoStsRightLight;

IGpio* g_apxDouts[MAX_DOUT_PINS];


DoutContainer g_xDoutContainer = DoutContainer();



static void FuncDigitInFilter(void* args);
static void Task_DigitIO(void* args);



void InitDigitalInput(){

    static UserTimer tmDigitInFilter;

    g_pxDigitFiltHeader = DigitalIn_boardConfig(g_pxGpiModeBtn, g_pxGpiBoostBtn, g_pxGpiStaffBtn, g_pxGpiEmergBtn);

    tmDigitInFilter.SetTimerInterface(g_IHwTimer);
    tmDigitInFilter.RegisterCallback(FuncDigitInFilter, (void*)g_pxDigitFiltHeader, 1, true);
    tmDigitInFilter.OnOffCtl(1);
}

DOutControl* dbgBrkLight;

void InitDigitalOutput(){

    static DOutControl xDoutBuzzor;
    static DOutControl xBrkLight;



    DigitalOut1_boardConfig(g_pxGpoBuzzor, g_pxGpoBoostLed, g_pxGpoHeadlight);
    DigitalOut2_boardConfig( g_pxGpoStsLeftLight, g_pxGpoStsRightLight, g_pxGpoBrakeLight);

    xDoutBuzzor.Init(&g_xPattern_welcome, &g_xPattern_off, g_pxGpoBuzzor);
    xBrkLight.Init(&g_xPattern_welcome, &g_xPattern_off, g_pxGpoBrakeLight);

    g_xDoutContainer.AddIn(&xDoutBuzzor, eDOutRank::BUZZOR);
    g_xDoutContainer.AddIn(&xBrkLight, eDOutRank::BRAKE_LIGHT);

    xDoutBuzzor.Reset(true);
    xBrkLight.Reset(true); 


    dbgBrkLight = &xBrkLight;


    xTaskCreate(Task_DigitIO, "TaskDIO", 256, nullptr, tskIDLE_PRIORITY + 3, &g_xTaskHnd_DigitOut);
}






static void Task_DigitIO(void* args){

	u8 ucDigitInRead_pre[10] = {0,};
    eDigitInType eDigitInEdge[10] = {eDigitInType::NOT_EDGE,};

    vTaskDelay(100);

    ucDigitInRead_pre[(u32)eDInRank::MODE]      = g_pxDigitFiltHeader->next->m_ucFilterVal;
    ucDigitInRead_pre[(u32)eDInRank::BOOSTER]   = g_pxDigitFiltHeader->next->next->m_ucFilterVal;
    ucDigitInRead_pre[(u32)eDInRank::STAFF]     = g_pxDigitFiltHeader->next->next->next->m_ucFilterVal;
    ucDigitInRead_pre[(u32)eDInRank::EMERGENCY] = g_pxDigitFiltHeader->next->next->next->next->m_ucFilterVal;

    while(true){

        DigitFiltNode_t* xDigitInCurr = g_pxDigitFiltHeader->next;


        // Digital Output Pattern Control
        g_xDoutContainer.Operation();

        
        for(u8 idx=0; xDigitInCurr->pxPin != nullptr; ++idx, xDigitInCurr = xDigitInCurr->next){

            u8 ucDigitInRead = xDigitInCurr->m_ucFilterVal;

            if(ucDigitInRead != ucDigitInRead_pre[idx]){

                if(ucDigitInRead == 0 && ucDigitInRead_pre[idx] == 1){
                    eDigitInEdge[idx] = eDigitInType::eFALLING;
                }     
                else if(ucDigitInRead == 1 && ucDigitInRead_pre[idx] == 0) {
                    eDigitInEdge[idx] = eDigitInType::eRISING;
                } 
                else {  }
            }
            else {
				eDigitInEdge[idx] = eDigitInType::NOT_EDGE;
			}

            ucDigitInRead_pre[idx] = ucDigitInRead;


            if(eDigitInEdge[idx] == eDigitInType::NOT_EDGE){
                continue;
            }

            switch((eDInRank)idx){
                case eDInRank::MODE:
                    xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFIY_MODE_BTN, (uint32_t)eDigitInEdge[idx], eSetValueWithOverwrite );
                    break;

                case eDInRank::BOOSTER:
                    xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFIY_BOOSTER_BTN, (uint32_t)eDigitInEdge[idx], eSetValueWithOverwrite );
                    break;

                case eDInRank::STAFF:
                    xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFIY_STAFF_BTN, (uint32_t)eDigitInEdge[idx], eSetValueWithOverwrite );
                    break;

                case eDInRank::EMERGENCY:
                    xTaskNotifyIndexed( g_xTaskHnd_main, TASK_NOTIFIY_EMERGENCY_BTN, (uint32_t)eDigitInEdge[idx], eSetValueWithOverwrite );
                    break;

                default:    break;
            }
  
        }


        vTaskDelay(10);
    }
}



u8 ReadDigitalInPin(eDInRank eRank){
    u8 order = (u8)eRank;
    DigitFiltNode_t* xDigitInCurr = g_pxDigitFiltHeader->next;

    for(u8 idx=0; idx<order;++idx){
        xDigitInCurr = xDigitInCurr->next;
    }

    return (xDigitInCurr->m_ucFilterVal);
} 




static void FuncDigitInFilter(void* args){

    DigitFiltNode_t* node = (DigitFiltNode_t*)args;
    IGpio* pxPin;

    do {

        if(node->pxPin){
            
            pxPin = node->pxPin;

            u8 l_ucDiTemp = (u8)pxPin->Read();

            node->m_usFilter <<= 1;
            node->m_usFilter= node->m_usFilter | l_ucDiTemp;

            if(node->m_usFilter == 0x00 )
            {
                node->m_ucFilterVal = 0;
            }
            else if(node->m_usFilter == 0xFFFF)
            {
                node->m_ucFilterVal = 1;
            }
        }

        node = node->next;

    }while(node->pxPin);
}
