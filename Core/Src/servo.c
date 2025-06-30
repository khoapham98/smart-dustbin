/*
 * servo.c
 *
 *  Created on: Jun 19, 2025
 *      Author: ACER
 */
#include "main.h"
#include "servo.h"

void servo_ctrl(direc_t d)
{
	uint32_t* TIM3_CCR1 = (uint32_t*) (TIM3_BASE_ADDR + 0x34);
	*TIM3_CCR1 = d;
	uint32_t* TIM3_EGR = (uint32_t*) (TIM3_BASE_ADDR + 0x14);
	*TIM3_EGR |= (1 << 0);	// update generation
}

/*
 * PB4: Timer3 Channel 1 (AF2)
*/
void TIM3_Init()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_BASE_ADDR + 0x00);
	uint32_t* GPIOB_AFRL = (uint32_t*) (GPIOB_BASE_ADDR + 0x20);
	*GPIOB_MODER &= ~(0b11 << 8);
	*GPIOB_MODER |= (0b10 << 8);	// set PB4 at AF mode for TIMER3
	*GPIOB_AFRL &= ~(0xf << 16);
	*GPIOB_AFRL |= (2 << 16);	// select AF02

	__HAL_RCC_TIM3_CLK_ENABLE();
	uint32_t* TIM3_CR1 = (uint32_t*) (TIM3_BASE_ADDR + 0x00);
	uint32_t* TIM3_PSC = (uint32_t*) (TIM3_BASE_ADDR + 0x28);
	uint32_t* TIM3_ARR = (uint32_t*) (TIM3_BASE_ADDR + 0x2C);
	uint32_t* TIM3_CCMR1 = (uint32_t*) (TIM3_BASE_ADDR + 0x18);
	uint32_t* TIM3_CCR1 = (uint32_t*) (TIM3_BASE_ADDR + 0x34);
	uint32_t* TIM_CCER = (uint32_t*) (TIM3_BASE_ADDR + 0x20);
	*TIM3_CR1 &= ~(1 << 4);		// up-counter
	*TIM3_PSC = 16 - 1;		// PSC = N - 1, set CLK_TIM3 = 1 MHz
	*TIM3_ARR = 19999;		// PWM period = 20 ms (50 Hz)
	*TIM3_CCMR1 |= (0b110 << 4);	// select PWM mode 1
//	*TIM3_CCMR1 |= (1 << 3);	// enable pre-load
	*TIM3_CCR1 = 1500;	// set motor default status is IDLE
	*TIM_CCER |= (1 << 0); 	// enable channel 1
	*TIM3_CR1 |= (1 << 0);	// enable counter
}
