#ifndef KEYPAD
#define KEYPAD
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define NO_ROW 4
#define NO_COL 4

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_DIR DDRA


uint8 KEYPAD_getPressed(void);
#endif
