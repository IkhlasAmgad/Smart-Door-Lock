 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ikhlas Amgad
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
 /********************Module Configurations *************************/
         /* UART Driver Baud Rate */
#define  USART_BAUDRATE     9600
#define  SPEED_MODE        DOUBLE_SPEED
#define  SYNCH_MODE         ASYNCH
#define  PARITY_MODE        NO_PARITY
#define  N_DATA_BITS        _8_DATA_BITS
#define  N_STOP_BITS        ONE_STOP_BIT

/********************speed mode*************************/
#define NORMAL_SPEED      0
#define DOUBLE_SPEED      1

/*******************parity mode*************************/
#define NO_PARITY    0
#define EVEN_PARITY  1
#define ODD_PARITY   2
/*************** number of data bits********************/
#define  _5_DATA_BITS    5
#define  _6_DATA_BITS    6
#define  _7_DATA_BITS    7
#define  _8_DATA_BITS    8
#define  _9_DATA_BITS    9

/***************      sync mode*************************/
#define  SYNCH  0
#define  ASYNCH 1
/************    number of stop bits*****************/
#define  ONE_STOP_BIT   1
#define  TWO_STOP_BIT   2



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_init(void);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

void RX_InterruptEnable(void);
void RX_InterruptDisable(void);

void TX_InterruptEnable(void);
void Tx_InterruptDisable(void);

void Tx_setCallBack(void(*a_ptr)(void));
void Rx_setCallBack(void(*a_ptr)(void));




#endif /* UART_H_ */
