#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"
#include "servo.h"
#include "uart.h"
#include "oled.h"

int distance = 0;

int main()
{
	HAL_Init();
	HCSR04_Init();
	TIM2_Init();
	USART2_Init();
	TIM3_Init();
	I2C_Init();
	SSD1306_Init();
	OLED_ClrScr();
	servo_ctrl(LEFT);
	OLED_print_lidClose();

	while (1)
	{
		distance = cal_distance();
		if (distance <= 10)
		{
			servo_ctrl(RIGHT);
			OLED_print_lidOpen();
			delay_ms(4000);
			servo_ctrl(LEFT);
			OLED_print_lidClose();
		}
		HAL_Delay(1000);

	}
	return 0;
}
