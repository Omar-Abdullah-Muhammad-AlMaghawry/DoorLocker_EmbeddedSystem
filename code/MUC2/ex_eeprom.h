#ifndef EXEEPROM
#define EXEEPROM
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "i2c.h"

#define SUCCESS 1;
#define ERROR 0;

void EXEEPROM_init(void);
uint8 EXEEPROM_writeByte(uint16 addr, char data);
uint8 EXEEPROM_readByte(uint16 addr,char * data);

#endif
