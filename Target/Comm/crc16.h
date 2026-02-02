/*
 * CRC16.h
 *
 *  Created on: 2020. 6. 26.
 *      Author: jaeho
 */

#ifndef CRC16_H_
#define CRC16_H_

#include <stdint.h>


extern uint16_t g_usarCrcTable[256];


#ifdef __cplusplus
extern "C" {
#endif
uint16_t Compute_ModbusCrc16(uint8_t* l_ucarData, uint16_t l_usLen);
unsigned int ComputeCrc32 (const unsigned char *buf, int len, unsigned int init);
#ifdef __cplusplus
}
#endif
#endif /* CRC16_H_ */
