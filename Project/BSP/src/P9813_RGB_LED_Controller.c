#include "P9813_RGB_LED_Controller.h"


static void delay_us(unsigned char us)
{
	unsigned char i,j;
		for(i=us; i>0; i--)
			for(j=50; j>0; j--);
}

void P9813_Pin_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;	//端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		    //IO口速度为50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					        //根据设定参数初始化GPIOB
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);						    //PB.8 输出LOW
		GPIO_ResetBits(GPIOB,GPIO_Pin_9); 						 	//PB.9 输出LOW
}

void P9813_Send_RGB_Data(unsigned char rData, unsigned char gData, unsigned char bData)
{
		unsigned char i=0;
	
		SDA = 0;
	  delay_us(100);
	
		for(i=0; i<32; i++){	// header data
				SCL = 0;
				delay_us(100);
				SCL = 1;
				delay_us(100);
		}					

		
		for(i=0; i<8; i++){	//check sum data
			
				SCL = 0;
				delay_us(100);
			
				switch(i){
					case 0:
					case 1:SDA = 1; delay_us(100); break;
					
					case 2:SDA = (bData >> 7) & 0x01;delay_us(100);break;
					case 3:SDA = (bData >> 6) & 0x01;delay_us(100);break;
					
					case 4:SDA = (gData >> 7) & 0x01;delay_us(100);break;
					case 5:SDA = (gData >> 6) & 0x01;delay_us(100);break;
					
					case 6:SDA = (rData >> 7) & 0x01;delay_us(100);break;
					case 7:SDA = (rData >> 6) & 0x01;delay_us(100);break;
				}
					
				SCL = 1;
				delay_us(100);
		}	
		
		for(i=0; i<8; i++){	//B data
				SCL = 0;
				delay_us(100);
				
				SDA = (bData >> (7-i))& 0x01;
				delay_us(100);
			
				SCL = 1;
				delay_us(100);
		}
		
		for(i=0; i<8; i++){	// G data
				SCL = 0;
				delay_us(100);
			
				SDA = (gData >> (7-i))& 0x01;
				delay_us(100);
			
				SCL = 1;
				delay_us(100);
		}
		
		for(i=0; i<8; i++){	//R data
				SCL = 0;
				delay_us(100);
			
				SDA = (rData >> (7-i))& 0x01;
				delay_us(100);
			
				SCL = 1;
				delay_us(100);
		}
}


