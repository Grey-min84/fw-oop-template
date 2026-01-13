/*
 * arrangePin.h
 *
 *  Created on: Oct 21, 2024
 *      Author: hidel
 */

#ifndef INC_ARRANGEPIN_H_
#define INC_ARRANGEPIN_H_

#include "main.h"

/* ***************** ADC ****************** */
#define PORT_AD_ANGLE_SENS_Pin 			 AD_ANGLE_SENS_Pin
#define PORT_AD_ANGLE_SENS_GPIO_Port     AD_ANGLE_SENS_GPIO_Port

#define PORT_AD_IND_SEN1_Pin             AD_IND_SEN1_Pin
#define PORT_AD_IND_SEN1_GPIO_Port       AD_IND_SEN1_GPIO_Port

#define PORT_AD_IND_SEN2_Pin             AD_IND_SEN2_Pin
#define PORT_AD_IND_SEN2_GPIO_Port       AD_IND_SEN2_GPIO_Port

#define PORT_AD_MAGNET_Pin               AD_MAGNET_Pin
#define PORT_AD_MAGNET_GPIO_Port         AD_MAGNET_GPIO_Port

#define PORT_AD_BLDC_CUR1_Pin            AD_BLDC_CUR1_Pin
#define PORT_AD_BLDC_CUR1_GPIO_Port      AD_BLDC_CUR1_GPIO_Port

#define PORT_AD_BLDC_CUR2_Pin            AD_BLDC_CUR2_Pin
#define PORT_AD_BLDC_CUR2_GPIO_Port      AD_BLDC_CUR2_GPIO_Port

#define PORT_AD_BLDC_CUR3_Pin            AD_BLDC_CUR3_Pin
#define PORT_AD_BLDC_CUR3_GPIO_Port      AD_BLDC_CUR3_GPIO_Port

#define PORT_AD_CTRLER_VOL_Pin           AD_CTRLER_VOL_Pin
#define PORT_AD_CTRLER_VOL_GPIO_Port     AD_CTRLER_VOL_GPIO_Port



/* ***************** UART ****************** */
#define UART1_TX_DBG_Pin GPIO_PIN_9
#define UART1_TX_DBG_GPIO_Port GPIOA
#define UART1_RX_DBG_Pin GPIO_PIN_10
#define UART1_RX_DBG_GPIO_Port GPIOA

#define USART2_TX_GMU_Pin GPIO_PIN_5
#define USART2_TX_GMU_GPIO_Port GPIOD
#define USART2_RX_GMU_Pin GPIO_PIN_6
#define USART2_RX_GMU_GPIO_Port GPIOD

#define USART3_TX_LIDAR_Pin GPIO_PIN_8
#define USART3_TX_LIDAR_GPIO_Port GPIOD
#define USART3_RX_LIDAR_Pin GPIO_PIN_9
#define USART3_RX_LIDAR_GPIO_Port GPIOD

#define UART5_TX_485_Pin GPIO_PIN_12
#define UART5_TX_485_GPIO_Port GPIOC
#define UART5_RX_485_Pin GPIO_PIN_2
#define UART5_RX_485_GPIO_Port GPIOD

#define UART6_TX_RESV_Pin GPIO_PIN_6
#define UART6_TX_RESV_GPIO_Port GPIOC
#define UART6_RX_RESV_Pin GPIO_PIN_7
#define UART6_RX_RESV_GPIO_Port GPIOC



/* ********************** RS485 Flow ******************** */
#define PORT_GPO_MOD_485_FLOW_PIN           GPO_MOD_485_FLOW_Pin			
#define PORT_GPO_MOD_485_FLOW_GPIO_PORT     GPO_MOD_485_FLOW_GPIO_Port 		




/* ***************** Steer BLDC & Clutch ****************** */
#define PORT_GPO_BLDC_CAL_Pin       GPO_BLDC_CAL_Pin	    		
#define PORT_GPO_BLDC_CAL_GPIO_Port         GPO_BLDC_CAL_GPIO_Port           			

#define PORT_GPO_BLDC_EN_Pin        GPO_BLDC_EN_Pin                  				
#define PORT_GPO_BLDC_EN_GPIO_Port          GPO_BLDC_EN_GPIO_Port            			
#define PORT_T1CH1_BLDC_PWM1_Pin        T1CH1_BLDC_PWM1_Pin              			
#define PORT_T1CH1_BLDC_PWM1_GPIO_Port          T1CH1_BLDC_PWM1_GPIO_Port        		

#define PORT_GPO_BLDC_nBRK_Pin          GPO_BLDC_nBRK_Pin                				
#define PORT_GPO_BLDC_nBRK_GPIO_Port        GPO_BLDC_nBRK_GPIO_Port          		
#define PORT_GPO_BLDC_DIR_Pin       GPO_BLDC_DIR_Pin                 				
#define PORT_GPO_BLDC_DIR_GPIO_Port         GPO_BLDC_DIR_GPIO_Port           			
#define PORT_GPI_BLDC_FAULT_Pin         GPI_BLDC_FAULT_Pin               				
#define PORT_GPI_BLDC_FAULT_GPIO_Port       GPI_BLDC_FAULT_GPIO_Port         		

#define PORT_STR_CLUTCH_CTRL_Pin        STR_CLUTCH_CTRL_Pin              			
#define PORT_STR_CLUTCH_CTRL_GPIO_Port          STR_CLUTCH_CTRL_GPIO_Port        		




/* ***************** Mode **************************** */

#define PORT_GPI_MODE_SW_PIN        GPI_MODE_SW_Pin 				
#define PORT_GPI_MODE_SW_GPIO_PORT  GPI_MODE_SW_GPIO_Port 			




/* ************** Vehicle Speed Check **************** */
#define T4_VEHICLE_ENC_A_Pin 			GPIO_PIN_12
#define T4_VEHICLE_ENC_A_GPIO_Port 		GPIOD
#define T4_VEHICLE_ENC_B_Pin 			GPIO_PIN_13
#define T4_VEHICLE_ENC_B_GPIO_Port 		GPIOD

#define T2C1_VEHICLE_SPD_ENC_Pin 		GPIO_PIN_0
#define T2C1_VEHICLE_SPD_ENC_GPIO_Port 	GPIOA



/* *************** Staff Controller ********************** */
#define PORT_GPI_CTRLER_SW_PIN                  GPI_CTRLER_SW_Pin 				
#define PORT_GPI_CTRLER_SW_GPIO_Port            GPI_CTRLER_SW_GPIO_Port 		




/* **************** GEN4 Control *********************** */
#define PORT_GPO_GEN4_RELAY_PIN                 GPO_GEN4_RELAY_Pin 				
#define PORT_GPO_GEN4_RELAY_GPIO_PORT           GPO_GEN4_RELAY_GPIO_Port 		

#define PORT_GPI_GEN4_EMERG_PIN                 GPI_GEN4_EMERG_Pin 				
#define PORT_GPI_GEN4_EMERG_GPIO_PORT           GPI_GEN4_EMERG_GPIO_Port 		





/* **************** A3 boost ************************ */
#define PORT_GPO_BOOST_LED_PIN                  GPO_BOOST_LED_Pin 				
#define PORT_GPO_BOOST_LED_GPIO_PORT            GPO_BOOST_LED_GPIO_Port 		
#define PORT_GPI_BOOST_SW_PIN                   GPI_BOOST_SW_Pin 				
#define PORT_GPI_BOOST_SW_GPIO_PORT             GPI_BOOST_SW_GPIO_Port 			


/* **************** A3 Spoiler ************************ */
#define PORT_GPI_SPOILER_LMT_SENS0_PIN                  GPI_SPOILER_LMT_SENS0_Pin 		
#define PORT_GPI_SPOILER_LMT_SENS0_GPIO_PORT            GPI_SPOILER_LMT_SENS0_GPIO_Port 
#define PORT_GPI_SPOILER_LMT_SENS1_PIN                  GPI_SPOILER_LMT_SENS1_Pin 		
#define PORT_GPI_SPOILER_LMT_SENS1_GPIO_PORT            GPI_SPOILER_LMT_SENS1_GPIO_Port 

#define SPOILER_M_PWM_PIN 				            GPIO_PIN_8
#define SPOILER_M_PWM_GPIO_PORT 		            GPIOC
#define PORT_GPO_SPOILER_M_DIR_PIN                  GPO_SPOILER_M_DIR_Pin 			
#define PORT_GPO_SPOILER_M_DIR_GPIO_PORT            GPO_SPOILER_M_DIR_GPIO_Port 	

#define PORT_GPO_SPOILER_M_EN_PIN                   GPO_SPOILER_M_EN_Pin 			
#define PORT_GPO_SPOILER_M_EN_GPIO_PORT             GPO_SPOILER_M_EN_GPIO_Port 		


/* **************** A3 Handle ************************ */
#define GPO_RESV_RS485_FLOW_PIN 			    GPIO_PIN_14
#define GPO_RESV_RS485_FLOW_GPIO_PORT 		    GPIOD



/* **************** Seat ************************ */
#define GPI_SEAT_SENS1_PIN 				    GPIO_PIN_10
#define GPI_SEAT_SENS1_GPIO_PORT 		    GPIOE
#define GPI_SEAT_SENS2_PIN 				    GPIO_PIN_11
#define GPI_SEAT_SENS2_GPIO_PORT 		    GPIOE

#define PWM_SEAT_VIB_PIN 				    GPIO_PIN_14
#define PWM_SEAT_VIB_GPIO_PORT 			    GPIOB


/* ******************* Light ********************* */
#define GPO_STS_LIGHT_R_PIN 			    GPIO_PIN_3
#define GPO_STS_LIGHT_R_GPIO_PORT 		    GPIOD

#define GPO_STS_LIGHT_L_PIN 			    GPIO_PIN_4
#define GPO_STS_LIGHT_L_GPIO_PORT 		    GPIOD

#define GPO_BRK_LIGHT_PIN 				    GPIO_PIN_8
#define GPO_BRK_LIGHT_GPIO_PORT 		    GPIOB


/* ***************** Board LED & Buzzer ********************** */
#define PORT_GPO_BD_LED1_PIN               GPO_LED1_Pin 					
#define PORT_GPO_BD_LED1_GPIO_PORT         GPO_LED1_GPIO_Port 				
#define PORT_GPO_BD_LED2_PIN               GPO_LED2_Pin 					
#define PORT_GPO_BD_LED2_GPIO_PORT         GPO_LED2_GPIO_Port 				
#define PORT_GPO_BD_LED3_PIN               GPO_LED3_Pin 					
#define PORT_GPO_BD_LED3_GPIO_PORT         GPO_LED3_GPIO_Port 				
#define PORT_GPO_BD_LED4_PIN                   LED4_Pin 						
#define PORT_GPO_BD_LED4_GPIO_PORT             LED4_GPIO_Port 					
#define PORT_GPO_BD_LED5_PIN                   LED5_Pin 						
#define PORT_GPO_BD_LED5_GPIO_PORT             LED5_GPIO_Port 	
#define PORT_GPO_BD_LED6_PIN 						GPIO_PIN_15
#define PORT_GPO_BD_LED6_GPIO_PORT 					GPIOB				
#define PORT_GPO_BD_LED7_PIN                   LED7_Pin 						
#define PORT_GPO_BD_LED7_GPIO_PORT             LED7_GPIO_Port 					



#define PORT_GPO_BD_BUZZER_PIN 					GPIO_PIN_11
#define PORT_GPO_BD_BUZZER_GPIO_PORT 			GPIOD


/* **************** Reserved SPI ************************ */
#define SPI1_CS_Pin GPIO_PIN_8
#define SPI1_CS_GPIO_Port GPIOA

#define SPI1_INT_Pin GPIO_PIN_0
#define SPI1_INT_GPIO_Port GPIOE
#define SPI1_RST_Pin GPIO_PIN_1
#define SPI1_RST_GPIO_Port GPIOE







#endif /* INC_ARRANGEPIN_H_ */
