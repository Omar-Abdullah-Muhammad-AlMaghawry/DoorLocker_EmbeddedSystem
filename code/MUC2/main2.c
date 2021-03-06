 /******************************************************************************
 *
 * Project Name: Door Locker
 *
 * Module: MCU2
 *
 * Description for The project: Creating password, open door, new password,alarm for wrong password 3 times
 *
 * Author: Omar Abdullah
 *
 *******************************************************************************/


#include "timer0.h"
#include "uart.h"
#include "i2c.h"
#include "ex_eeprom.h"
#include "dcmotor.h"

#define BUZZER_LOC PC2
#define BUZZER_DIR DDRC
#define BUZZER_OUTPUT PORTC

#define NO_PER_SEC 32

uint8 volatile tick = 0;
uint8 volatile mSec = 0;
uint8 volatile sec = 0;

uint8 check_with_eeprom(char *ptr1, char *ptr2) {
	int i;
	for (i = 0; i < 5; i++) {
		//read the saved 5 bits from the address 0x0311
		EXEEPROM_readByte(0x03 + i, &ptr2[i]);
		if (ptr1[i] != ptr2[i]) { //compare the saved bit with the input data
			return ERROR;
		}
	}
	return SUCCESS;
}
void getPassFromEeprom(char * str) {
	int i;
	for (i = 0; i < 5; i++) {
		//read the saved 5 bits from the address 0x0311
		EXEEPROM_readByte(0x0311 + i, str+i);
	}
}
void setPassToEeprom(char *str) {
	int i;
	for (i = 0; i < 5; i++) {
		//write the saved 5 bits from the address 0x0311
		EXEEPROM_writeByte(0x0311 + i, str[i]);
		_delay_ms(100);
	}

}
void setPassToEepromFirst(char *str) {
	//write the saved 5 bits from the address 0x0311
	int i;
		for (i = 0; i < 5; i++) {
			//write the saved 5 bits from the address 0x0311
			EXEEPROM_writeByte(0x0311 + i, str[i]);
			_delay_ms(100);
		}

}
void ISR_Count(void) {

	tick++;
	if (tick == NO_PER_SEC) {
		sec++;
		tick = 0;
	}

}

int main(void) {

	UartConfig UartConf = { disableParity, oneStop, eightBits, 9600 };
	Timer0Config Timer0Conf = { CTC, 0, clk_1024, 245 };
	char *write = "!!!!!";
	char *read = "#####";
	SREG |= (1 << 7);
	UART_init(&UartConf);
	EXEEPROM_init();
	TIMER0_init(&Timer0Conf);
	TIMER0_setCallBack(ISR_Count);
	DCMOTOR_init();
	BUZZER_DIR |= (1 << BUZZER_LOC);

	setPassToEepromFirst(write);
	while (1) {
		switch ((char) UART_recieveChar(&UartConf)) {
		case 'P':
			getPassFromEeprom(read);
			UART_sentString(&UartConf, read);
			break;
		case 'N':
			UART_recieveString(&UartConf, write, 5);
			setPassToEeprom(write);
			break;
		case 'O':
		sec =1;

			while (sec % 15)
				DCMOTOR_clockWise();
			sec =1;
			DCMOTOR_stop();
			while (sec % 15)
				DCMOTOR_antiClockWise();
			DCMOTOR_stop();
		//	TIMER0_deInit();
			break;
		case 'W':
			//tick = 1;
			sec = 1;
			//TIMER0_init(&Timer0Conf);
			//TIMER0_setCallBack(ISR_Count);
			while (sec % 30)
				BUZZER_OUTPUT |= (1 << BUZZER_LOC);

			BUZZER_OUTPUT &= ~(1 << BUZZER_LOC);

			//TIMER0_deInit();

			break;
		}
	}
	return 0;
}
