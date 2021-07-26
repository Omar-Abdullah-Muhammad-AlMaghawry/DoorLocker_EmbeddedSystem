#include "dcmotor.h"

void DCMOTOR_init(void){
	DCMOTOR_DIR |= (1<<IN1)|(1<<IN2);
	DCMOTOR_OUTPUT &= ~((1<<IN1)|(1<<IN2));
}
void DCMOTOR_clockWise(void){
	DCMOTOR_OUTPUT &= ~(1<<IN1);
	DCMOTOR_OUTPUT |= (1<<IN2);
}
void DCMOTOR_antiClockWise(void){
	DCMOTOR_OUTPUT &= ~(1<<IN2);
	DCMOTOR_OUTPUT |= (1<<IN1);
}
void DCMOTOR_stop(void){
	DCMOTOR_OUTPUT &= ~(1<<IN1);
	DCMOTOR_OUTPUT &= ~(1<<IN2);
}
