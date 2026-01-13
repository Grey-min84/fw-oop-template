/*
 * Common.h
 *
 *  Created on: Jan 8, 2022
 *      Author: j
 */

#ifndef TASKS_MISC_H_
#define TASKS_MISC_H_

#include "main.h"

typedef struct {
	uint32_t m_uiSender;
	uint32_t m_uiReceiver;
	uint32_t m_uiPacketLen;
	uint8_t m_ucBuff[256];
}Message_t;

#ifdef __cplusplus
extern "C" {
#endif
// void UartRecvInterruptEnable(UART_HandleTypeDef *l_pstUartHandle);
// uint8_t UartInterruptRecvHandler(UART_HandleTypeDef *l_pstUartHandle);
// uint16_t Compute_ModbusCrc16(uint8_t* l_ucarData, uint16_t l_usLen);
float TwoPointLine(float x1, float y1, float x2, float y2, float x);
void DivideFields(char (*strDest)[16], char* srcStr, int sizeStr);
float FirstOrderFunc(float slide, float y_offset, float input);
// void SendMsgToTask(osMailQId l_pstQueId, Message_t *l_stMessage);
// osEvent RecvMsgFromTask(osMailQId l_pstQueId, Message_t *l_stMessage, uint32_t l_uiTimeout );
#ifdef __cplusplus
}
#endif

#endif /* TASKS_MISC_H_ */
