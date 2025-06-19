#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"
#include "uart.h"

uint32_t distance = 0;


int main()
{
	HAL_Init();
	HCSR04_Init();
	TIM2_Init();
	USART2_Init();
	TIM3_Init();
	while (1)
	{
		servo_ctrl(18);
		delay_ms(600);
		servo_ctrl(15);
		delay_ms(3000);
		servo_ctrl(12);
		delay_ms(600);
		servo_ctrl(15);
		delay_ms(3000);

	}
	return 0;
}

