/*
 * hcsr04.c
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */
#include "main.h"
#include "mydelay.h"
#include "hcsr04.h"

/*
 * PC6: ECHO pin
 * PC7: TRIG pin
*/
void HCSR04_Init()
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	uint32_t* GPIOC_MODER = (uint32_t*) (GPIOC_BASE_ADDR + 0x00);
	*GPIOC_MODER &= ~(0b1111 << 12);	// set PC6 as INPUT ~ ECHO
	*GPIOC_MODER |= (0b01 << 14);	// set PC7 as OUTPUT ~ TRIG
}

/* This function is used to trigger the HC-SR04 sensor to start sending out an ultrasonic burst */
void trig_HCSR04()
{
	uint32_t* GPIOC_ODR = (uint32_t*) (GPIOC_BASE_ADDR + 0x14);
	*GPIOC_ODR |= (1 << 7);		// set TRIG to HIGH
	delay_us(10);
	*GPIOC_ODR &= ~(1 << 7);	// clear TRIG to LOW
}

/*
 * This function is used to calculate the distance in centimeter
 */
uint32_t cal_distance()
{
	trig_HCSR04();
	volatile uint32_t* GPIOC_IDR = (uint32_t*) (GPIOC_BASE_ADDR + 0x10);
	while (((*GPIOC_IDR >> 6) & 1) == 0);	// wait until ECHO is HIGH

	volatile uint32_t* TIM2_CNT = (uint32_t*) (TIM2_BASE_ADDR + 0x24);
	*TIM2_CNT = 0;	// set counter counting back from 0
	while (((*GPIOC_IDR >> 6) & 1) == 1);	// Keep counting until ECHO is LOW
	uint32_t time = *TIM2_CNT;	// save the time
	return time / 58;	// use equation 3 in datasheet to calculate distance
}
