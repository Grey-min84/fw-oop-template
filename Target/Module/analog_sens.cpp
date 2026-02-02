#include "analog_sens.h"


#include "board_config.h"
#include "analog_filter.h"

u16* g_pusAnalogSensRaw = nullptr;

static AVG_FILTER_VAR g_xAvgFilter[(uint8_t)(eAnalogSensRank::max)];
static MedianFilter_t g_xMedFilter[(uint8_t)(eAnalogSensRank::max)];

static s32 g_iAnalogAvgFilted[(uint8_t)(eAnalogSensRank::max)];
s32 g_iAnalogMedFilted[(uint8_t)(eAnalogSensRank::max)];

static UserTimer g_xAnalogFiltTimer;


extern ITimer* g_IHwTimer;


void Timer_analogFilt(void* args);


void InitAnalogFilter(){

    g_pusAnalogSensRaw = AnalogSensing_boardConfig();

    const uint8_t ucSampleCnt = 5;
    const float fAvgCoeff = 0.5f;

    for(uint8_t i = 0; i < (uint8_t)(eAnalogSensRank::max); i++){
        InitAverageFilter(&g_xAvgFilter[i], fAvgCoeff);
        InitMedianFilterVar(&g_xMedFilter[i], ucSampleCnt);
    }

    g_xAnalogFiltTimer.SetTimerInterface(g_IHwTimer);
    g_xAnalogFiltTimer.OnOffCtl(1);
    g_xAnalogFiltTimer.RegisterCallback(Timer_analogFilt, nullptr, 1, true);
}








void Timer_analogFilt(void* args){
    

    for(uint8_t i = 0; i < (uint8_t)(eAnalogSensRank::max); i++){

        // Average Filter
        g_iAnalogAvgFilted[i] = AverageFilter(&g_xAvgFilter[i], (int32_t)g_pusAnalogSensRaw[i]);
        
        // Median Filter
        g_iAnalogMedFilted[i] = MedianFilter(&g_xMedFilter[i], (int32_t)g_iAnalogAvgFilted[i]);
    }
}


s32 GetAnalogSens_AvgFilted(eAnalogSensRank rank){
    if((uint8_t)rank < (uint8_t)(eAnalogSensRank::max)){
        return g_iAnalogMedFilted[(uint8_t)rank];
    }
    else{
        return 0;
    }
}
