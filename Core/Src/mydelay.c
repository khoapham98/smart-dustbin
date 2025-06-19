/*
 * mydelay.c
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */
#include "main.h"
#include "mydelay.h"

/* This function is used to initialize the TIMER2 */
void TIM2_Init()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	uint32_t* TIM2_CR1 = (uint32_t*) (TIM2_BASE_ADDR + 0x00);
	*TIM2_CR1 &= ~(1 << 4);	// up-counter
	*TIM2_CR1 &= ~(1 << 0); // make sure CEN = 0 (stop timer)

	uint32_t* TIM2_PSC = (uint32_t*) (TIM2_BASE_ADDR + 0x28);
	*TIM2_PSC = 16 - 1;		// PSC = N - 1, set CLK_TIM2 = 1 MHz

	uint32_t* TIM2_EGR = (uint32_t*) (TIM2_BASE_ADDR + 0x14);
	*TIM2_EGR |= (1 << 0); 	// enable update generation

	*TIM2_CR1 |= (1 << 0);	// enable counter
}

/* This function is used to delay in microsecond */
void delay_us(uint32_t us)
{
	uint32_t* TIM2_CNT = (uint32_t*) (TIM2_BASE_ADDR + 0x24);
	*TIM2_CNT = 0;
	while (*TIM2_CNT < us);
}

/* This function is used to delay in millisecond */
void delay_ms(uint32_t ms)
{
	uint32_t* TIM2_CNT = (uint32_t*) (TIM2_BASE_ADDR + 0x24);
	*TIM2_CNT = 0;
	while (*TIM2_CNT < (ms * 1000));
}
