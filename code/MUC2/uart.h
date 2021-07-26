#ifndef UART
#define UART
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#ifndef F_CPU_U
#define F_CPU_U 8000000
#endif
#define CLKDIV 8
#define BAUD_PRESCALE(USART_BAUDRATE) (((F_CPU_U / (USART_BAUDRATE * CLKDIV))) - 1)
typedef enum {
	disableParity,oddParity,evenParity
}ParityType;
typedef enum {
	oneStop,twoStop
}NoOfStopBits;
typedef enum {
	fiveBits,sexBits,sevenBits,eightBits,nineBits
}NoOfBits;
typedef struct {
	ParityType parityType;
	NoOfStopBits noOfStopBits;
	NoOfBits noOfBits;
	int baudRate;
}UartConfig;
//extern UartConfig confUart;
//extern	UartConfig * conf;
void UART_init(const UartConfig * conf);
uint16 UART_recieveChar(const UartConfig * conf);
void UART_sentChar(const UartConfig * conf,uint16 data);
//uint8_t * UART_recieveString(const UartConfig * conf,int lenght);
void UART_recieveString(const UartConfig * conf,char * str,int lenght);
void UART_sentString(const UartConfig * conf,char * str);
//uint32_t * UART_recieveString(void);

#endif
