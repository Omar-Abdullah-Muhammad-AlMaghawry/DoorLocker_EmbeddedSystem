#include "keypad.h"

/*these function use to map bet. the pressed key and the actual number*/
#if (NO_COL == 4)
static uint8 KEYPAD_4x4_adjustSwitchNumber(uint8 location); // static bec. it's not used in other file, it uses internal
#elif(NO_COL == 3)
static uint8 KEYPAD_4x3_adjustSwitchNumber(uint8 location);// static bec. it's not used in other file, it uses internal
#endif

uint8 KEYPAD_getPressed(void) {
	uint8 col, row;
	while (1) {
	//	_delay_ms(700);
		for (col = 0; col < NO_COL; col++) {
			KEYPAD_PORT_DIR = (0b00010000) << col; //one col is only o/p
			KEYPAD_PORT_IN = ~((0b00010000) << col); //this col is like connected to ground
			for (row = 0; row < NO_ROW; row++) {
				if (!(KEYPAD_PORT_IN & (1 << row))) //which row is presses on this col
#if (NO_COL == 4)
					return KEYPAD_4x4_adjustSwitchNumber(
							(row * NO_COL) + col + 1); // static bec. it's not used in other file, it uses internal
#elif(NO_COL == 3)
					return  KEYPAD_4x3_adjustSwitchNumber((row*NO_COL)+col+1);// static bec. it's not used in other file, it uses internal
#endif

			}
		}
	}
}

#if (NO_COL == 4)
static uint8 KEYPAD_4x4_adjustSwitchNumber(uint8 location) { // static bec. it's not used in other file, it uses internal
	switch (location) {
	case 1:
		return 7;
	case 2:
		return 8;
	case 3:
		return 9;
	case 4:
		return '%';
	case 5:
		return 4;
	case 6:
		return 5;
	case 7:
		return 6;
	case 8:
		return '*';
	case 9:
		return 1;
	case 10:
		return 2;
	case 11:
		return 3;
	case 12:
		return '-';
	case 13:
		return 13; ///ascii for Enter
	case 14:
		return 0;
	case 15:
		return '=';
	case 16:
		return '+';
	default:
		return location;
	}
}
#elif (NO_COL == 3)
static uint8 KEYPAD_4x3_adjustSwitchNumber(uint8 location){// static bec. it's not used in other file, it uses internal
	switch(location){
		case 10 :
		return '*';
		case 11:
			return '0';
		case 12:
			return '#';
		default:
			return location;
		}
}
#endif
