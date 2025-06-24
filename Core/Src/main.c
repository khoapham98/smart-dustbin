#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"
#include "servo.h"
#include "uart.h"
#include "oled.h"


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
	while (1)
	{
		OLED_print_lidOpen();
	}
	return 0;
}
