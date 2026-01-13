/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "tiny_printf.h"
//#include "typeSimple.h"
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* ***************** Model Select ***************** */
// #define MODEL_A12       (1)
// #define MODEL_A3        (2)

// #define CURR_MODEL      (MODEL_A3)




// #define A3_SELF_DRIVE_OFF   (0)
// #define A3_SELF_DRIVE_ON    (1)


// #define A3_SELF_DRIVE_STS   (A3_SELF_DRIVE_OFF)
// /* ************************************************ */





// // GR-A3에 적용된 레졸버 타입의 각도에 따라 아날로그 데이터를 출력하는 엔코더 
// #define USE_STEER_ANALOG_ENCODER    (0)

// // GR2에 적용중인 마그넷 엔코더
// #define USE_STEER_MAGNET_ENCODER    (1)


// // GR-A3처럼 GCU에서 구동을 관리
// #define USE_INSTALLED_DRIVE_MODULE  (0)

// // GR-A1처럼 별도의 DCM보드에서 구동을 관리
// #define USE_EXTERNAL_DRIVE_MODULE   (1)


/* *****************************************************************
조향제어에 있어 레퍼런스 각도(Target Angle)을 생성하는 절차 중
마지막 단계에 차량 속도에 따라 유도선 이탈 거리를 지수함수 형태로
감쇄를 적용할지 여부
***************************************************************** */
//#define USE_STEER_CTL_EXP_FUNC		(0)


/* *****************************************************************
조향제어에 있어 레퍼런스 각도(Target Angle)을 생성하는 절차 중
예측시간(T) 후 예측 이탈거리를 계산할 때 T를 차량 속도에 따라 계산을
수행하는지 여부
 * 비활성화 할 경우 GMU에서 내려오는 예측시간(T) 사용
 * 활성화한 경우 Sigmoid함수(tanh)를 피팅 함수로 사용
***************************************************************** */
//#define USE_STEER_CTL_PRED_TM_CALC  (0)




// #if(CURR_MODEL == MODEL_A12)

//   #define STEER_ENCODER_MODE          USE_STEER_MAGNET_ENCODER
//   #define DRIVE_MODULE                USE_EXTERNAL_DRIVE_MODULE

// #elif(CURR_MODEL == MODEL_A3)

//   #define STEER_ENCODER_MODE          USE_STEER_ANALOG_ENCODER
//   #define DRIVE_MODULE                USE_INSTALLED_DRIVE_MODULE
// #endif






/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define MASS_LOG_SCALE                    (2000)




#define SERIAL_FLASH_SECTOR_STEER_PARAM     (1)



#define SERIAL_FLASH_SECTOR_BRAKE           (2)
#define SERIAL_FLASH_PAGE_GENRAL            (3)


#define SERIAL_FLASH_SECTOR_STEER_LOG       (16)





#define NOTIFY_IDX_GMU_RCV    (1)
#define NOTIFY_IDX_GMU_SEND   (2)
#define NOTIFY_IDX_STEER_CTL  (3)
#define NOTIFY_IDX_STEER_ACK  (4)



#define NOTIFY_IDX_ISTEER     (7)
#define NOTIFY_IDX_IDRIVE     (8)
#define NOTIFY_IDX_IBRAKE     (9)
#define NOTIFY_IDX_ILIDAR     (10)

#define NOTIFY_IDX_BZ_LIGHT   (11)

#define NOTIFY_IDX_TEST_START   (13)






#define PRINT_ERR(...) 	printf(__VA_ARGS__)


#define PRINT_BRK(...)	//printf(__VA_ARGS__)
#define PRINT_LIDR(...) printf(__VA_ARGS__)
#define PRINT_GMU(...) 	printf(__VA_ARGS__)
#define PRINT_NET(...)  printf(__VA_ARGS__)




// enum FAULT_SELF_CHK{

// };




/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim12;

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

extern ADC_HandleTypeDef hadc1;

extern CAN_HandleTypeDef hcan1;

extern IWDG_HandleTypeDef hiwdg;
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPO_LED1_Pin GPIO_PIN_3
#define GPO_LED1_GPIO_Port GPIOE
#define GPO_LED2_Pin GPIO_PIN_4
#define GPO_LED2_GPIO_Port GPIOE
#define GPO_LED3_Pin GPIO_PIN_5
#define GPO_LED3_GPIO_Port GPIOE
#define GPO_BOOST_LED_Pin GPIO_PIN_6
#define GPO_BOOST_LED_GPIO_Port GPIOE
#define GPI_BOOST_SW_Pin GPIO_PIN_13
#define GPI_BOOST_SW_GPIO_Port GPIOC
#define AD_ANGLE_SENS_Pin GPIO_PIN_0
#define AD_ANGLE_SENS_GPIO_Port GPIOC
#define AD_IND_SEN1_Pin GPIO_PIN_1
#define AD_IND_SEN1_GPIO_Port GPIOC
#define AD_IND_SEN2_Pin GPIO_PIN_2
#define AD_IND_SEN2_GPIO_Port GPIOC
#define AD_MAGNET_Pin GPIO_PIN_3
#define AD_MAGNET_GPIO_Port GPIOC
#define T2C1_VEHICLE_SPD_ENC_Pin GPIO_PIN_0
#define T2C1_VEHICLE_SPD_ENC_GPIO_Port GPIOA
#define AD_BLDC_CUR1_Pin GPIO_PIN_2
#define AD_BLDC_CUR1_GPIO_Port GPIOA
#define AD_BLDC_CUR2_Pin GPIO_PIN_3
#define AD_BLDC_CUR2_GPIO_Port GPIOA
#define AD_BLDC_CUR3_Pin GPIO_PIN_4
#define AD_BLDC_CUR3_GPIO_Port GPIOA
#define AD_CTRLER_VOL_Pin GPIO_PIN_4
#define AD_CTRLER_VOL_GPIO_Port GPIOC
#define GPO_BLDC_CAL_Pin GPIO_PIN_5
#define GPO_BLDC_CAL_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOB
#define GPO_BLDC_EN_Pin GPIO_PIN_7
#define GPO_BLDC_EN_GPIO_Port GPIOE
#define T1CH1_BLDC_PWM1_Pin GPIO_PIN_9
#define T1CH1_BLDC_PWM1_GPIO_Port GPIOE
#define GPI_SEAT_SENS1_Pin GPIO_PIN_10
#define GPI_SEAT_SENS1_GPIO_Port GPIOE
#define GPI_SEAT_SENS2_Pin GPIO_PIN_11
#define GPI_SEAT_SENS2_GPIO_Port GPIOE
#define GPO_BLDC_nBRK_Pin GPIO_PIN_12
#define GPO_BLDC_nBRK_GPIO_Port GPIOE
#define GPO_BLDC_DIR_Pin GPIO_PIN_13
#define GPO_BLDC_DIR_GPIO_Port GPIOE
#define GPI_BLDC_FAULT_Pin GPIO_PIN_14
#define GPI_BLDC_FAULT_GPIO_Port GPIOE
#define GPI_SPOILER_LMT_SENS0_Pin GPIO_PIN_10
#define GPI_SPOILER_LMT_SENS0_GPIO_Port GPIOB
#define GPI_SPOILER_LMT_SENS1_Pin GPIO_PIN_11
#define GPI_SPOILER_LMT_SENS1_GPIO_Port GPIOB
#define LED7_Pin GPIO_PIN_12
#define LED7_GPIO_Port GPIOB
#define PWM_SEAT_VIB_Pin GPIO_PIN_14
#define PWM_SEAT_VIB_GPIO_Port GPIOB
#define LED6_Pin GPIO_PIN_15
#define LED6_GPIO_Port GPIOB
#define USART3_TX_LIDAR_Pin GPIO_PIN_8
#define USART3_TX_LIDAR_GPIO_Port GPIOD
#define USART3_RX_LIDAR_Pin GPIO_PIN_9
#define USART3_RX_LIDAR_GPIO_Port GPIOD
#define GPI_CTRLER_SW_Pin GPIO_PIN_10
#define GPI_CTRLER_SW_GPIO_Port GPIOD
#define GPO_BUZZER_Pin GPIO_PIN_11
#define GPO_BUZZER_GPIO_Port GPIOD
#define T4_VEHICLE_ENC_A_Pin GPIO_PIN_12
#define T4_VEHICLE_ENC_A_GPIO_Port GPIOD
#define T4_VEHICLE_ENC_B_Pin GPIO_PIN_13
#define T4_VEHICLE_ENC_B_GPIO_Port GPIOD
#define GPO_RESV_RS485_FLOW_Pin GPIO_PIN_14
#define GPO_RESV_RS485_FLOW_GPIO_Port GPIOD
#define GPI_GEN4_EMERG_Pin GPIO_PIN_15
#define GPI_GEN4_EMERG_GPIO_Port GPIOD
#define UART6_TX_RESV_Pin GPIO_PIN_6
#define UART6_TX_RESV_GPIO_Port GPIOC
#define UART6_RX_RESV_Pin GPIO_PIN_7
#define UART6_RX_RESV_GPIO_Port GPIOC
#define SPOILER_M_PWM_Pin GPIO_PIN_8
#define SPOILER_M_PWM_GPIO_Port GPIOC
#define GPO_SPOILER_M_DIR_Pin GPIO_PIN_9
#define GPO_SPOILER_M_DIR_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_8
#define SPI1_CS_GPIO_Port GPIOA
#define UART1_TX_DBG_Pin GPIO_PIN_9
#define UART1_TX_DBG_GPIO_Port GPIOA
#define UART1_RX_DBG_Pin GPIO_PIN_10
#define UART1_RX_DBG_GPIO_Port GPIOA
#define STR_CLUTCH_CTRL_Pin GPIO_PIN_11
#define STR_CLUTCH_CTRL_GPIO_Port GPIOA
#define GPO_GEN4_RELAY_Pin GPIO_PIN_12
#define GPO_GEN4_RELAY_GPIO_Port GPIOA
#define GPO_SPOILER_M_EN_Pin GPIO_PIN_10
#define GPO_SPOILER_M_EN_GPIO_Port GPIOC
#define GPO_MOD_485_FLOW_Pin GPIO_PIN_11
#define GPO_MOD_485_FLOW_GPIO_Port GPIOC
#define UART5_TX_485_Pin GPIO_PIN_12
#define UART5_TX_485_GPIO_Port GPIOC
#define UART5_RX_485_Pin GPIO_PIN_2
#define UART5_RX_485_GPIO_Port GPIOD
#define GPO_STS_LIGHT_R_Pin GPIO_PIN_3
#define GPO_STS_LIGHT_R_GPIO_Port GPIOD
#define GPO_STS_LIGHT_L_Pin GPIO_PIN_4
#define GPO_STS_LIGHT_L_GPIO_Port GPIOD
#define USART2_TX_GMU_Pin GPIO_PIN_5
#define USART2_TX_GMU_GPIO_Port GPIOD
#define USART2_RX_GMU_Pin GPIO_PIN_6
#define USART2_RX_GMU_GPIO_Port GPIOD
#define GPO_BRK_LIGHT_Pin GPIO_PIN_8
#define GPO_BRK_LIGHT_GPIO_Port GPIOB
#define GPI_MODE_SW_Pin GPIO_PIN_9
#define GPI_MODE_SW_GPIO_Port GPIOB
#define SPI1_INT_Pin GPIO_PIN_0
#define SPI1_INT_GPIO_Port GPIOE
#define SPI1_RST_Pin GPIO_PIN_1
#define SPI1_RST_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
#define GPI_IMPACT_REAR_CH1_Port    GPIOE
#define GPI_IMPACT_REAR_CH1_Pin     GPIO_PIN_2

#define GPI_IMPACT_REAR_CH2_Port    GPIOE
#define GPI_IMPACT_REAR_CH2_Pin     GPIO_PIN_8

#define GPI_IMPACT_FRONT_CH1_Port   GPIOC
#define GPI_IMPACT_FRONT_CH1_Pin    GPIO_PIN_14

#define GPI_IMPACT_FRONT_CH2_Port   GPIOC
#define GPI_IMPACT_FRONT_CH2_Pin    GPIO_PIN_15


#define GPO_HEADLIGHT_CTL_Port   GPIOE
#define GPO_HEADLIGHT_CTL_Pin    GPIO_PIN_15

#define GPI_LIDAR_485_FLOW_Port   GPIOD
#define GPI_LIDAR_485_FLOW_Pin    GPIO_PIN_7



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
