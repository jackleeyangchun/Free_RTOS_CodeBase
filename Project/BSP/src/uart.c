#include "uart.h"

#include "string.h"
//#include "malloc.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

u8 aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                   
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

//重定义fputc函数 
int fputc(int ch, FILE *f)

{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}


void USART1_IRQHandler(void) //串口 1 中断服务程序
{
	u8 Res;

	#ifdef OS_TICKS_PER_SEC //如果时钟节拍数定义了 ,说明要使用 ucosII 了 .
		OSIntEnter();
	#endif

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	//接收中断(接收到的数据必须是 0x0d 0x0a 结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1 ->DR); //读取接收到的数据
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了 0x0d
			{
				if(Res!=0x0a)
					USART_RX_STA=0;//接收错误,重新开始
				else 
					USART_RX_STA|=0x8000; //接收完成了
			}
			else //还没收到 0X0D
			{
				if(Res==0x0d)
					USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;
					//接收数据错误,重新开始接收 
				}
			}
		}
 	}

	#ifdef OS_TICKS_PER_SEC //如果时钟节拍数定义了 ,说明要使用 ucosII 了 .
		OSIntExit();
	#endif
}
void uart_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	USART_DeInit(USART1);   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  


	USART_InitStructure.USART_BaudRate = 115200L; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????????

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//???

	USART_Init(USART1, &USART_InitStructure); //初始化串口
	#if EN_USART1_RX    //如果使能了接收
	//⑤初始化 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //抢占优先级 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //子优先级 3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ 通道使能
	NVIC_Init(&NVIC_InitStructure);   //中断优先级初始化
	//⑤开启中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
	#endif
	//⑥使能串口
	USART_Cmd(USART1, ENABLE);   //使能串口

}




