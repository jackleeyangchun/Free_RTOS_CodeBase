#ifndef UART_H
#define UART_H

#include "stdio.h"
//#include "string.h"
//#include "malloc.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 50
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//extern UART_HandleTypeDef UART1_Handler; //UART句柄

#define RXBUFFERSIZE   1 //缓存大小
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL库USART接收Buffer

void USART1_IRQHandler(void);
int fputc(int ch, FILE *f);



void uart_init();

#endif 

