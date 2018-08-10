#ifndef __P9813_RGB_LED_CONTROLLER_H__
#define __P9813_RGB_LED_CONTROLLER_H__
#include "sys.h"

#define SCL PBout(8)// PA0
#define SDA PBout(9)// PA1	

void P9813_Pin_Init(void);//≥ı ºªØ
void P9813_Send_RGB_Data(unsigned char rData, unsigned char gData, unsigned char bData);

#endif 

