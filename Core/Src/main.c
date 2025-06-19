#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"
#include "uart.h"
#include "servo.h"

uint32_t distance = 0;

void I2C_Init();

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

/*
 * This function is used to initialize I2C1 peripheral
 * PB6: SCL
 * PB7: SDA
 */
void I2C_Init()
{
	uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_OTYPER = (uint32_t*) (GPIOB_BASE_ADDR + 0x04);
	uint32_t* GPIOB_PUPDR = (uint32_t*) (GPIOB_BASE_ADDR + 0x0C);
	uint32_t* GPIOB_AFRL = (uint32_t*) (GPIOB_BASE_ADDR + 0x20);
	*GPIOB_MODER &= ~(0xf << 12);	// clear bit
	*GPIOB_MODER |= (0b1010 << 12);	// set PB6, PB7 at AF mode
	*GPIOB_OTYPER |= (0b11 << 6);	// set open-drain mode
	*GPIOB_PUPDR &= ~(0xf << 12);	// clear bit
	*GPIOB_PUPDR |= (0b0101 << 12);	// configure PB6, PB7 the I/O pull-up
	*GPIOB_AFRL &= ~(0xff << 24);	// clear bit
	*GPIOB_AFRL |= (4 << 24) | (4 << 28);	// select AF04

	__HAL_RCC_I2C1_CLK_ENABLE();
	*GPIOB_AFRL |= (4 << 24) | (4 << 28);	// select AF04
}

