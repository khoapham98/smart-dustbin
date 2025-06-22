#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"
#include "uart.h"
#include "servo.h"
#include "oled.h"

uint32_t distance = 0;

int main()
{
	HAL_Init();
	HCSR04_Init();
	TIM2_Init();
	USART2_Init();
	TIM3_Init();
	I2C_Init();

	int check = 0;
	while (1)
	{
		if (check == 0 && I2C_send_start(SSD1306_ADDR, WRITE) == TRUE)
		{
			I2C_send_data("hello world");
			check++;
			I2C_send_stop();
		}
	}
	return 0;
}
