#include "uart.h"

/*
 NAME: INIT UART
 Description : initialization the UART
 */
void UART_init(const UartConfig *conf) {

	UCSRA = (1 << U2X); //enable double trans

	UCSRB = (1 << RXEN) | (1 << TXEN); //enable recive and send
	switch (conf->noOfBits) {
	case fiveBits:
		if ((conf->parityType) == disableParity) {
			UCSRC = 0;
		} else if ((conf->parityType) == evenParity) {
			UCSRC = (1 << UPM1);
		} else {
			UCSRC = (1 << UPM1) | (1 << UPM0);
		}
		UCSRC |= (1 << URSEL) | ((conf->noOfStopBits) << USBS);
		break;
	case sexBits:
		if ((conf->parityType) == disableParity) {
			UCSRC = 0;
		} else if ((conf->parityType) == evenParity) {
			UCSRC = (1 << UPM1);
		} else {
			UCSRC = (1 << UPM1) | (1 << UPM0);
		}
		UCSRC |= (1 << URSEL) | ((conf->noOfStopBits) << USBS) | (1 << UCSZ0);
		break;
	case sevenBits:
		if ((conf->parityType) == disableParity) {
			UCSRC = 0;
		} else if ((conf->parityType) == evenParity) {
			UCSRC = (1 << UPM1);
		} else {
			UCSRC = (1 << UPM1) | (1 << UPM0);
		}
		UCSRC |= (1 << URSEL) | ((conf->noOfStopBits) << USBS) | (1 << UCSZ1);
		break;
	case eightBits:
		if ((conf->parityType) == disableParity) {
			UCSRC = 0;
		} else if ((conf->parityType) == evenParity) {
			UCSRC = (1 << UPM1);
		} else {
			UCSRC = (1 << UPM1) | (1 << UPM0);
		}
		UCSRC |= (1 << URSEL) | ((conf->noOfStopBits) << USBS) | (1 << UCSZ0)
				| (1 << UCSZ1);
		break;
	case nineBits:
		if ((conf->parityType) == disableParity) {
			UCSRC = 0;
		} else if ((conf->parityType) == evenParity) {
			UCSRC = (1 << UPM1);
		} else {
			UCSRC = (1 << UPM1) | (1 << UPM0);
		}
		UCSRC |= (1 << URSEL) | ((conf->noOfStopBits) << USBS) | (1 << UCSZ0)
				| (1 << UCSZ1) | (1 << UCSZ2);
		break;

	default:
		break;

	}
	UBRRH = BAUD_PRESCALE(conf->baudRate) >> 8;
	UBRRL = BAUD_PRESCALE(conf->baudRate);

//	for( c=0;c<10;c++);
}

/********************
 * NAME: recive UART
 * Description : recieving byte from the UART
 * in : null
 * out : uint8_t // Byte
 **********************/
uint16 UART_recieveChar(const UartConfig * conf) {
	while (!(UCSRA & (1 << RXC))) {}
	if(conf->noOfBits==nineBits)
	return (UCSRA&(1<<RXB8)<<8)|((uint8) UDR & (0xFF));
	else
	return ((uint8) UDR & (0xFF));
}
/*********************
 * NAME: sent UART
 * Description : sent byte from the UART0
 * in : data // byte
 * out : 0
 *********************/
void UART_sentChar(const UartConfig *conf, uint16 data) {
	while (!(UCSRA & (1 << UDRE))) {}
	if(conf->noOfBits==nineBits)
		UCSRA=(data&(1<<8))<<TXB8;
	UDR = data&0xFF;

}
void UART_recieveString(const UartConfig *conf, char *str, int lenght) {
	if(conf->noOfBits != nineBits)
	{uint8 charac;
	uint8 i = 0;

	do {
		charac = UART_recieveChar(conf);
		str[i] = charac&(0xFF);
		i++;
		lenght--;
	} while (lenght != 0);
	str[i] = '\0';
	i = 0;
	}
}
void UART_sentString(const UartConfig *conf, char *str) {
	uint8 i = 0;
	while (str[i] != '\0') {
		UART_sentChar(conf, str[i]);
		i++;
	}
	i = 0;
}
/*uint32_t * UART_recieveString(void){
 uint8_t data = UART_recieve();
 uint8_t * ptr = &data;
 uint32_t * ptrInt32 ;
 int i ;
 for( i = 0 ; i<4;i++){
 * ptrInt32 = * (ptr + i);
 }
 return ptrInt32;
 }
 */


