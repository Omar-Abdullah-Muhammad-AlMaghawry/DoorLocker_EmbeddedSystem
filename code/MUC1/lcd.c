#include "lcd.h"
void LCD_init(void){
LCD_CTRL_PORT_DIR |=(1<<RS)|(1<<RW)|(1<<E);
LCD_DATA_PORT_DIR=0xFF;
LCD_sendCommand(0x38);
LCD_clearScreen();
LCD_sendCommand(0x0C);
}
void LCD_sendCommand(uint8 command){
LCD_CTRL_PORT_DATA &=~(1<<RS)&~(1<<RW);
_delay_ms(1);
LCD_CTRL_PORT_DATA |=(1<<E);
_delay_ms(1);
LCD_DATA_PORT_DATA =command;
_delay_ms(1);
LCD_CTRL_PORT_DATA &=~(1<<E);
_delay_ms(1);
}
void LCD_displayChar(char data){
	LCD_CTRL_PORT_DATA |=(1<<RS);
	LCD_CTRL_PORT_DATA &=~(1<<RW);
	_delay_ms(1);
	LCD_CTRL_PORT_DATA |=(1<<E);
	_delay_ms(1);
	LCD_DATA_PORT_DATA =data;
	_delay_ms(1);
	LCD_CTRL_PORT_DATA &=~(1<<E);
	_delay_ms(1);
}
void LCD_displayString(const char * str){
	int i =0;
	while(str[i] != '\0'){
	LCD_displayChar(str[i]);
	i++;
}
}
void LCD_goToRowColumn(uint8 row,uint8 col){
	uint16 address =0;
	switch (row){
	case 0:
		address = col;
		break;
	case 1:
		address = 0x40+col;
		break;
	case 2:
		address = 0x10+col;
		break;
	case 3:
		address = 0x50+col;
		break;
	default :
		break;
	}
	LCD_sendCommand( 0x80|address);//to move the courser first bit =1 and the address;
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char * str){
	LCD_goToRowColumn(row,col);
	LCD_displayString(str);

}
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(){
	LCD_sendCommand(0x01);
}
