#ifndef DCMOTOR
#define DCMOTOR
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define IN1 PC3
#define IN2 PC4


#define DCMOTOR_DIR DDRC
#define DCMOTOR_OUTPUT PORTC

void DCMOTOR_init(void);
void DCMOTOR_clockWise(void);
void DCMOTOR_antiClockWise(void);
void DCMOTOR_stop(void);


#endif
