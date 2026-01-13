#ifndef __TYPE_SIMPLE_H__
#define __TYPE_SIMPLE_H__

#ifdef __cplusplus
extern "C" {
#endif
//extern "C"{
//#include <string.h>
//#include <stdint.h>
//}
#include <stdint.h>
#include <string.h>
#include "tiny_printf.h"
#include "model_config.h"

#define PRINT_DBG(...) 	printf(__VA_ARGS__)


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;


#ifdef __cplusplus
}
#endif

#endif
