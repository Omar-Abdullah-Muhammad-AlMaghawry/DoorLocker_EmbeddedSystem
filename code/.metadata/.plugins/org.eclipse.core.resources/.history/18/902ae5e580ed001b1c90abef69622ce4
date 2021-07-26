#ifndef TIMER0
#define TIMER0
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


typedef enum{
	normal,PWM,CTC,fastPWM
}modeType;
typedef enum{
	noClock,noPrescaling,clk_8,clk_64,clk_256,clk_1024
}prescaler;
typedef struct{
	modeType mode;
	uint8 initialVal;
	prescaler prescale;
	uint8 compareVal;
}Timer0Config;
//extern Timer0Config * timerconf;
void TIMER0_init(Timer0Config * conf);
void TIMER0_setCallBack(void(*callBackFN)());
void TIMER0_deInit(void);

#endif
