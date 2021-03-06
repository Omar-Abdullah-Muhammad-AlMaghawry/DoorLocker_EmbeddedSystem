




#ifndef I2C
#define I2C
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
///////////////////////////////////////////////////////////////////////////////////////
#ifndef F_CPU_I //////////////////////////////
#define F_CPU_I 8000000
#endif
///////////////////////////////////////////////////////////////////////////////////////
#define CLKDIV 8
#define BAUD_PRESCALE_I2C(I2C_BAUDRATE) (((F_CPU_I / (I2C_BAUDRATE))-16)/ (2))
typedef struct{
	uint8 addr;
	int baudRate;
}I2cConfig;
//extern I2cConfig * i2cConf;
void TWI_init(I2cConfig * conf);
void TWI_init0(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithAck(void);
uint8 TWI_readWithNack(void);
uint8 TWI_getStatus(void);


#endif
