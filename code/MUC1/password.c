#include "password.h"

uint8 newPassword(char *password) {
	uint8 key;
	char *pass = "#####";
	char *repass = "####!";
	uint8 i = 0;
	uint8 match = 1;
	uint8 ent = 0;
	_delay_ms(PUTTON_TIME);
	while (1) {
		match = 1;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Enter new Pass");
		_delay_ms(500);
		for (i = 0; i < 5; i++) {
			key = KEYPAD_getPressed();
			if (key == 13) {
				_delay_ms(PUTTON_TIME);
				break;
			} else {
				LCD_displayStringRowColumn(1, i, "*");
				_delay_ms(PUTTON_TIME);
		//		LCD_displayChar((char) key);
				if ( key <= 9)
											pass[i] =  key + 48;
										else
											pass[i] = (char) key;
			}
		}
	//	LCD_displayStringRowColumn(1, 0, pass);
	//	_delay_ms(10000);
		if (i != 5) {
			LCD_displayStringRowColumn(1, 0, "pass must be 5 v");
			_delay_ms(10000);
			continue;
		} else {
			key = KEYPAD_getPressed();
			if (key == 13) {

				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Renter the Pass");
				_delay_ms(10000);
				for (i = 0; i < 5; i++) {
					key = KEYPAD_getPressed();
					if (key == 13) {
						_delay_ms(PUTTON_TIME);
						break;
					} else {
						LCD_displayStringRowColumn(1, i, "*");
						_delay_ms(PUTTON_TIME);
					//	LCD_displayChar((char) key);
						if (key <= 9)
													repass[i] =  key + 48;
												else
													repass[i] = (char) key;
					}

				}
		//		LCD_displayStringRowColumn(1, 0, repass);
		//		_delay_ms(10000);
				if (i != 5) {
					LCD_displayStringRowColumn(1, 0, "pass must be 5 v");
					_delay_ms(10000);
					continue;
				} else {
					key = KEYPAD_getPressed();

					if (key == 13) {
						ent = 1;
						_delay_ms(PUTTON_TIME);
					} else {
						LCD_displayStringRowColumn(1, 0, "pass must be 5 v");
						_delay_ms(10000);
						continue;
					}
				}
			} else {
				LCD_displayStringRowColumn(1, 0, "pass must be 5 v");
				_delay_ms(10000);
				continue;
			}
		}

		if (ent) {
			for (i = 0; i < 5; i++) {
				if (pass[i] != repass[i]) {
					match = 0;
				}

			}
		}

		if (match == 0) {
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "***unmatched***");
			_delay_ms(200000);
			continue;
		} else {
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, " ***matched***");
			LCD_displayStringRowColumn(1, 0, "saving..........");
			_delay_ms(200000);
			for (i = 0; i < 5; i++) {
				password[i] = pass[i];
			}
			return 1;
		}
	}
}


uint8 checkPassword(char *password) {

	//uint8 *password ="";
	uint8 key;
	char * pass ="#####";
//	uint8 *repass;
	uint8 i = 0;
	uint8 match = 1;
	uint8 ent = 0;
	_delay_ms(PUTTON_TIME);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Enter Your Pass");
	for (i = 0; i < 5; i++) {
				key = KEYPAD_getPressed();
				if (key == 13) {
					_delay_ms(PUTTON_TIME);
					break;
				} else {
					LCD_displayStringRowColumn(1, i, "*");
					_delay_ms(PUTTON_TIME);
			//		LCD_displayChar((char) key);
					if ( key <= 9)
												pass[i] =  key + 48;
											else
												pass[i] = (char) key;
				}
			}
	if (i != 5) {
		return 0;
	} else {
		key = KEYPAD_getPressed();
		if (key == 13) {
			_delay_ms(PUTTON_TIME);
			ent = 1;

		}else{
			return 0;
		}
	}
	if (ent) {
			match = strcmp(pass,password);
}
	if (match)
		return 0;
	else
		return 1;
}
/*uint8 getPassword(	char * pass) {

	uint8 key;
	uint8 i = 0;
	uint8 match = 1;
	uint8 ent = 0;
	_delay_ms(PUTTON_TIME);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Enter Your Pass");
	for (i = 0; i < 5; i++) {
				key = KEYPAD_getPressed();
				if (key == 13) {
					_delay_ms(PUTTON_TIME);
					break;
				} else {
					LCD_displayStringRowColumn(1, i, "*");
					_delay_ms(PUTTON_TIME);
			//		LCD_displayChar((char) key);
					pass[i] = (char) key;
				}
			}
	if (i != 5) {
		return 0;
	} else {
		key = KEYPAD_getPressed();
		if (key == 13) {
			_delay_ms(PUTTON_TIME);
			ent = 1;

		}else{
			return 0;
		}
	}

}*/
