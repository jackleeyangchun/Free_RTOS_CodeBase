#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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


void LED_Init(void);//��ʼ��

		 				    
#endif
