
#include "i2c.h"

void TWI_init(I2cConfig * conf){
	TWBR = BAUD_PRESCALE_I2C(conf->baudRate);//calc baud rate
	TWSR =0x00; //prescale = 1
	  /* Two Wire Bus address my address if any master device want to call me: (conf->addr) (used in case this MC is a slave device)
	       General Call Recognition: Off */
	TWAR = 0;
	TWAR = (TWAR&0xFE)|((conf->addr)<<1); // my address = (conf->addr)
	TWCR=(1<<TWEN);//enable TWI
}
void TWI_init0(void)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = 0x00;

    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = 0b00000010; // my address = 0x01 :)

    TWCR = (1<<TWEN); /* enable TWI */
}


void TWI_start(void){

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//clear the flag represent intr , enable start bit, and enable intr////(((((|=)))))
	while(!(TWCR&(1<<TWINT)));//wait for sending the start bit in the new op (start bit sent succ))
}
void TWI_stop(void){
		/*
		 * Clear the TWINT flag before sending the stop bit TWINT=1
		 * send the stop bit by TWSTO=1
		 * Enable TWI Module intr TWEN=1
		 */
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);//clear the flag represent intr , enable stop bit, and enable intr
}
void TWI_write(uint8 data){
	/*putting the next byte*/
	TWDR = data;
	/*
	 * clear the TWINT before sending data TWINT = 1
	 * enable the TWI Module
	 */
	TWCR=(1<<TWINT)|(1<<TWEN);
	/*wait for sending the data (data sent succ)*/
	while(!(TWCR&(1<<TWINT)));
}
uint8 TWI_readWithAck(void){
	/*
	 * clear the TWINT before recieving data TWINT = 1
	 * enable ack
	 * enable module intr
	 */
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	/*wait for twint is set (data recieved succ)*/
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

uint8 TWI_readWithNack(void){
	/*
	 * clear the TWINT before recieving data TWINT = 1
	 * disable ack TWEA = 0
	 * enable module intr
	 */
	TWCR=(1<<TWINT)|(1<<TWEN);
	/*wait for twint is set (data recieved succ)*/
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}
uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
/*int8 TWI_getStatus(void){
	///*masking for getting the last five bits in their location*
	return (TWSR & 0xF8);
}
*/


