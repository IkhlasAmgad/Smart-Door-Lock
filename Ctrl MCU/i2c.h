 /******************************************************************************

 *
 * File Name: i2c.h
 *
 *
 * Author:Ikhlas Amgad
 *
 **********************************************************/ 


#ifndef I2C_H_
#define I2C_H_
#include <math.h>
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define SCL_CLK 400000UL    /*/* Bit Rate: 400.000 kbps  */
#define No_Prescaler  0x00
#define Prescaler_4   0x01
#define Prescaler_16  0x02
#define Prescaler_64  0x03


#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);
void I2c_setCallBack(void(*a_ptr)(void));
void TWI_init_withInterrupt(void);
#endif /* I2C_H_ */
