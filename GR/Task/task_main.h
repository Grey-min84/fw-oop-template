#ifndef __TASK_MAIN_H__
#define __TASK_MAIN_H__
#include "board_config.h"
//#include "digital_out.hpp"
#include "bzLight_pattern.h"
#include "analog_sens.h"
#include "misc.h"
#include "module_interface.hpp"


#define VMU_COMM_PERIOD     (100)
#define TTALIVE_PERIOD      (10)



extern TaskHandle_t g_xTaskHnd_main;
#endif