

#include "ex_eeprom.h"

void EXEEPROM_init(void) {
	I2cConfig i2cConf = { 1, 400000 };
	TWI_init(&i2cConf);
	//TWI_init0();
}
uint8 EXEEPROM_writeByte(uint16 addr, char data) {
	TWI_start();
	if (TWI_getStatus() != TW_START)
		return ERROR;

	TWI_write((uint8) (((addr & 0x0700) >> 7) | 0xA0)); //decice addr 1010 + device addr a10,a9,a8
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	TWI_write((uint8) addr); // word addr 1st 8 bits
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_write((uint8) data); //send the data to store it
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_stop(); //send stop bit
	return SUCCESS;
}

uint8 EXEEPROM_readByte(uint16 addr, char *data) {
	TWI_start();
	if (TWI_getStatus() != TW_START)
		return ERROR;

	TWI_write((uint8) (((addr & 0x0700) >> 7) | 0xA0)); //decice addr 1010 + device addr a10,a9,a8 //write to write initial addr
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	TWI_write((uint8) addr); //intial word addr 1st 8 bits
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_start(); //send repeated
	if (TWI_getStatus() != TW_REP_START)
		return ERROR;

	TWI_write((uint8) (((addr & 0x0700) >> 7) | 0xA0 | 1)); //decice addr 1010 + device addr a10,a9,a8 // read int R/W bit
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
		return ERROR;

	*data = (char)TWI_readWithNack();	//recieve byte without ack
	if (TWI_getStatus() != TW_MR_DATA_NACK)
		return ERROR;

	TWI_stop();	//send stop bit
	return SUCCESS;

}


