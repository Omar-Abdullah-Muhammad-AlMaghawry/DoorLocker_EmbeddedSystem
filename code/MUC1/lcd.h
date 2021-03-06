#ifndef LCD
#define LCD
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
#include "stdio.h"
#define RS PD4
#define RW PD5
#define E PD6
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_CTRL_PORT_DATA PORTD
#define LCD_DATA_PORT_DIR DDRC
#define LCD_DATA_PORT_DATA PORTC
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayChar(char data);
void LCD_displayString(const char * str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char * str);
void LCD_intgerToString(int data);
void LCD_clearScreen();
#endif
