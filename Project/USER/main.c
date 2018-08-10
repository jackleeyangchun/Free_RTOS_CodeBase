
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "misc.h"

#include "led.h"
#include "P9813_RGB_LED_Controller.h"
#include "delay.h"
#include "uart.h"


void LED0_Task(void * pvParameters);
void LED1_Task(void * pvParameters);
void main_Task(void * pvParameters);

TaskHandle_t StartTask_Handler;
TaskHandle_t RGB_Task_Handler;

int main(void)
{
	LED_Init();
	uart_init();
	
	fputch('h');
	fputch('e');
	fputch('l');
	fputch('l');
	fputch('0');
		
	
/*	
	delay_init();
	
			LED1 = !LED1;
	delay_ms(1000);
			LED1 = !LED1;
		delay_ms(1000);
			LED1 = !LED1;
		delay_ms(1000);
			LED1 = !LED1;
		delay_ms(1000);
			LED1 = !LED1;
	*/
  xTaskCreate(main_Task, (const char *)"Start Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, (TaskHandle_t *)&StartTask_Handler);
	
	vTaskStartScheduler();
}

void main_Task(void * pvParameters)
{
	taskENTER_CRITICAL();
	
	xTaskCreate(LED0_Task, (const char *)"LED0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
	xTaskCreate(LED1_Task, (const char *)"RGB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, (TaskHandle_t *)&RGB_Task_Handler);
	
	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}
void LED0_Task(void * pvParameters)
{
	while (1)
	{
		LED1 = !LED1;
		LED2 = !LED2;
		LED3 = !LED3;
		LED4 = !LED4;
		vTaskDelay(800 / portTICK_RATE_MS);
	}
}

void LED1_Task(void * pvParameters)
{
/*	
	while (1)
	{
		LED3 = !LED3;
		LED4 = !LED4;
		vTaskDelay(500 / portTICK_RATE_MS);
	}
	*/
	P9813_Send_RGB_Data(0xff, 0xff, 0xff);
	vTaskDelete(RGB_Task_Handler);
}
