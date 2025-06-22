/*
 * oled.c
 *
 *  Created on: Jun 20, 2025
 *      Author: ACER
 */
#include "main.h"
#include "oled.h"
#include "servo.h"
#include "string.h"

void OLED_Init()
{
	I2C_Init();
	I2C_start();
	I2C_send_addr(SSD1306_ADDR, WRITE);
	I2C_send_control_byte(CMD);
	I2C_send_byte(0xAF);
	I2C_stop();
}

void I2C_send_control_byte(ctrl_t ctrl_byte)
{
	uint32_t* I2C_DR = (uint32_t*) (I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	*I2C_DR = ctrl_byte;
	while (((*I2C_SR1 >> 7) & 1) == 0);
}

void I2C_stop()
{
	uint32_t* I2C_CR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x00);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	*I2C_SR1 &= ~(1 << 10);	// clear AF bit
	*I2C_CR1 |= 1 << 9;		// send STOP
}

void I2C_send_byte(uint8_t data)
{
	uint32_t* I2C_DR = (uint32_t*) (I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	*I2C_DR = data;
	while (((*I2C_SR1 >> 7) & 1) == 0);	// wait until data has been transferred
}

void I2C_send_addr(uint8_t slave_addr, mode_t mode)
{
	uint8_t* I2C_DR = (uint8_t*) (I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	uint32_t* I2C_SR2 = (uint32_t*) (I2C1_BASE_ADDR + 0x18);
	/*	ADDRESS PHASE  */
	// send address to slave and select WRITE mode
	*I2C_DR = (slave_addr << 1) | mode;
	// wait until the address transmission is completed
	while (((*I2C_SR1 >> 1) & 1) == 0);
	// read SR1 and SR2 to clear ADDR bit
	volatile int tmp = *I2C_SR1;
	tmp = *I2C_SR2;
}

void I2C_start()
{
	uint32_t* I2C_CR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x00);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	// send START
	*I2C_CR1 |= 1 << 8;
	// wait until START condition is generated and operate at Master mode
	while ((*I2C_SR1 & 1) == 0);
}

/*
 * This function is used to initialize I2C1 peripheral
 * PB6: SCL
 * PB7: SDA
 */
void I2C_Init()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
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
