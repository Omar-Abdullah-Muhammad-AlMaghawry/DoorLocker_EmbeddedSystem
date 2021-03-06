 /******************************************************************************
 *
 * Project Name: Door Locker
 *
 * Module: MCU1
 *
 * Description for The project: Creating password, open door, new password,alarm for wrong password 3 times
 *
 * Author: Omar Abdullah
 *
 *******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include "timer0.h"
#include "uart.h"
#include "password.h"

#define NO_PER_SEC 32

uint8 volatile tick = 0;
uint8 volatile mSec = 0;
uint8 volatile sec = 0;
UartConfig UartConf = { disableParity, oneStop, eightBits, 9600 };
char *password = "!!!!!";
char *ch = "!!!!!";

void ISR_Count(void) {

	tick++;
	if (tick == NO_PER_SEC) {
		//	UART_sentChar(&UartConf, 'N');
		//UART_sentString(&UartConf, password);

		sec++;
		tick = 0;
	}

}

int main(void) {

	uint8 done = 0;
	uint8 key;
	uint8 match = 0;
	uint8 c;
//	UartConfig  UartConf = { disableParity, oneStop, eightBits, 9600 };
	Timer0Config Timer0Conf = { CTC, 0, clk_1024, 245 };
	SREG |= (1 << 7);
	UART_init(&UartConf);
	TIMER0_init(&Timer0Conf);
	TIMER0_setCallBack(ISR_Count);
	LCD_init();
	LCD_displayStringRowColumn(0, 0, "   WELCOME TO  ");
	LCD_displayStringRowColumn(1, 0, "  DOOR  lOCKER  ");
	_delay_ms(1000);
	while (1) {
		match = 0;
		if (sec < 1) {
			UART_sentChar(&UartConf, 'P');
			UART_recieveString(&UartConf, password, 5);
			if (strcmp((password), ch) == 0) { //////////////////////////////
				done = newPassword(password);
				if (done == 1) {
					UART_sentChar(&UartConf, 'N');
					UART_sentString(&UartConf, password);

				}
				done = 0;
			}
		}

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : open door");
		LCD_displayStringRowColumn(1, 0, "- : change pass");
		_delay_ms(500);
		key = KEYPAD_getPressed();
		if (key == '+') {
			UART_sentChar(&UartConf, 'P');
			UART_recieveString(&UartConf, password, 5);

			done = checkPassword(password);

			if (done) {
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "    WORKING  ");
				_delay_ms(200000);
				UART_sentChar(&UartConf, 'O');
				done = 0;
				match = 1;
			} else {
				for (c = 0; c < 2; c++) {
					 done = checkPassword(password);
					if (done) {
						UART_sentChar(&UartConf, 'O');
						match = 1;
						break;
					}
				}
				if (match == 0) {
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "  3 WRONG PASS  ");
					UART_sentChar(&UartConf, 'W');
				}
			}
		} else if (key == '-') {
			UART_sentChar(&UartConf, 'P');
			UART_recieveString(&UartConf, password,5);
			done = checkPassword(password);
			if (done) {
				done = newPassword(password);
				if (done)
					UART_sentChar(&UartConf, 'N');
				UART_sentString(&UartConf, password);
				match = 1;

			} else {
				for (c = 0; c < 2; c++) {
					done = checkPassword(password);
					if (done) {
						done = newPassword(password);
						if (done)
							UART_sentChar(&UartConf, 'N');
						UART_sentString(&UartConf, password);
						match = 1;
						break;
					}
				}
				if (match == 0) {
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "  3 WRONG PASS  ");
					UART_sentChar(&UartConf, 'W');
				}
			}

		}
	}
	return 0;
}

