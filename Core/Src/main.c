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
	OLED_Init();

	int check = 0;
	while (1)
	{
		if (check == 0)
		{
			I2C_start();
			I2C_send_control_byte(DATA);
			I2C_send_byte('k');
//			I2C_send_control_byte(DATA);
//			I2C_send_byte('h');
//			I2C_send_control_byte(DATA);
//			I2C_send_byte('o');
//			I2C_send_control_byte(DATA);
//			I2C_send_byte('a');
			I2C_stop();
			check++;
		}
	}
	return 0;
}
