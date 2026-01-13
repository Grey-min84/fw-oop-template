#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include "typeSimple.h"
#include "portHAL_STM32.h"
#include "drv_rs485.h"
#include "EncOneway.hpp"
#include "model_config.h"
//#include "bzLight_pattern.h"





enum class eAnalogSensRank{
	Sense_0 = 0,
	Sense_1,		// 1
	Sense_2,

	Sense_3,
	Sense_4,				// 4

	Sense_5,			// 5
	
	Sense_6,

	Sense_7,
	Sense_8,				// 8
    max,
};


enum class eDInRank{
    MODE = 0,
	BOOSTER,
	STAFF,
	EMERGENCY,
};


enum class eDOutRank{
    BUZZOR = 0,
    BRAKE_LIGHT,
    LIGHT_2,
    LIGHT_3,
	LED_1,
	LED_2,
    LED3,
};




enum class eDigitInType{
	NOT_EDGE = 0,
	eRISING = 1,
	eFALLING = 2,
	PRESS_LONG,
};




typedef struct DigitFiltNode_tag{
	IGpio* pxPin;
	
	u16 m_usFilter;
	u8 m_ucFilterVal;
	struct DigitFiltNode_tag* next;
}DigitFiltNode_t;






#define TASK_NOTIFIY_MODE_BTN		(1)
#define TASK_NOTIFIY_BOOSTER_BTN		(2)
#define TASK_NOTIFIY_STAFF_BTN		(3)
#define TASK_NOTIFIY_EMERGENCY_BTN		(4)

#define TASK_NOTIFY_CLI_TEST_BTN   (5)	




ITimer* HardTimer_boardConfig();
u16* AnalogSensing_boardConfig();
ICANBus* MainCANBus_boardConfing();


IUart* GmuPort_boardConfig(IGpio*& pIndicateLed);
DrvRs485* LidarPort_boardConfig(IGpio*& pFlowPin, IUart*& pPort, IGpio*& pIndicateLed);
DrvRs485* ModuleNetworkPort_boardConfig(IGpio*& pIndicateLed);



bool DriveModulePin_Config(IGpio*& pRelay, IGpio*& pEmerg);
EncOneway* DriveSpeedSens_Config();






IGpio* KeepAliveLed_boardConfig();



DigitFiltNode_t* DigitalIn_boardConfig(IGpio*& pModeBtn, IGpio*& pBoostBtn, IGpio*& pStaffBtn, IGpio*& pEmergfBtn);
bool DigitalOut1_boardConfig(IGpio*& pBuzzor, IGpio*& pBoostLed, IGpio*& pHeadlight);
bool DigitalOut2_boardConfig( IGpio*& pStsLightL, IGpio*& pStsLightR, IGpio*& pBrkLight);








extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim1;
#endif