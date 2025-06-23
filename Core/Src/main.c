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
		if (check == 0)
		{
			OLED_Init();
			delay_ms(100);

			I2C_start();
			I2C_send_addr(SSD1306_ADDR, WRITE);
			I2C_send_byte(DATA, 0xFF);
			I2C_stop();
			check++;
		}
	}
	return 0;
}
