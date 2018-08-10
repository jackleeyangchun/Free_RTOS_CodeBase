#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define LED1 PAout(0)// PA0
#define LED2 PAout(1)// PA1	
#define LED3 PAout(4)// PA4
#define LED4 PBout(0)// PB0

//key1 D9  --> PB11
//key2 D10 --> PB12
//key3 D12 --> PA7
//key4 D2 --> PB7

//Humidity D3	--> PB3
//Buzzer A4 --> PB1


void LED_Init(void);//初始化

		 				    
#endif
