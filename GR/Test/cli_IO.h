#ifndef __CLI_IO_H__
#define __CLI_IO_H__

#include "cli.h"
#include "board_config.h"
#include "digital_out.hpp"


void CliDigital_In(cli_args_t *args, void* param);
void CliDigital_Out(cli_args_t *args, void* param);
void DigitalIn_TestCtl(DigitFiltNode_t* pxDigitIn);
#endif