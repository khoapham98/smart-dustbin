/*
 * oled.c
 *
 *  Created on: Jun 20, 2025
 *      Author: ACER
 */
#include "main.h"
#include "oled.h"
#include "servo.h"

void master_send_data()
{

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
	uint32_t* I2C_CR2 = (uint32_t*) (I2C1_BASE_ADDR + 0x04);
	uint32_t* I2C_CCR = (uint32_t*) (I2C1_BASE_ADDR + 0x1C);
	uint32_t* I2C_TRISE = (uint32_t*) (I2C1_BASE_ADDR + 0x20);
	uint32_t* I2C_CR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x00);
	*I2C_CR2 |= (16 << 0);	// set f = 16MHz
	*I2C_CCR &= ~(1 << 15);	// select Sm mode
	*I2C_CCR |= 80 << 0; 	// set SCL freq = 100 kHz
	*I2C_TRISE = 17; 		// set time rise
	*I2C_CR1 |= (1 << 0);	// enable peripheral
}
