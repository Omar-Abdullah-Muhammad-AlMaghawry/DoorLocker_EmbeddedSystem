#ifndef PASSWORD
#define PASSWORD
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "string.h"

#define PUTTON_TIME 2200

uint8 checkPassword(char *password);
//uint8 getPassword(	char * pass);
uint8 newPassword(char *password);

#endif
