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
#include "uart.h"

void SSD1306_Init()
{
	HAL_Delay(100);
	I2C_send_byte(CMD, 0xAE); //display off

	I2C_send_byte(CMD, 0x20); //Set Memory Addressing Mode
	I2C_send_byte(CMD, 0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
							  // 10b,Page Addressing Mode (RESET); 11b,Invalid

	I2C_send_byte(CMD, 0xB0); //Set Page Start Address for Page Addressing Mode,0-7

	I2C_send_byte(CMD, 0xC8); //Set COM Output Scan Direction

	I2C_send_byte(CMD, 0x00); //---set low column address
	I2C_send_byte(CMD, 0x10); //---set high column address

	I2C_send_byte(CMD, 0x40); //--set start line address - CHECK

	I2C_send_byte(CMD, 0xFF);

	I2C_send_byte(CMD, 0xA1); //--set segment re-map 0 to 127 - CHECK

	I2C_send_byte(CMD, 0xA6); //--set normal color
	I2C_send_byte(CMD, 0xA8); //--set multiplex ratio(1 to 64) - CHECK
	I2C_send_byte(CMD, 0x1F); //
	I2C_send_byte(CMD, 0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

	I2C_send_byte(CMD, 0xD3); //-set display offset - CHECK
	I2C_send_byte(CMD, 0x00); //-not offset

	I2C_send_byte(CMD, 0xD5); //--set display clock divide ratio/oscillator frequency
	I2C_send_byte(CMD, 0xF0); //--set divide ratio

	I2C_send_byte(CMD, 0xD9); //--set pre-charge period
	I2C_send_byte(CMD, 0x22); //

	I2C_send_byte(CMD, 0xDA); //--set com pins hardware configuration - CHECK
	I2C_send_byte(CMD, 0x02);
	I2C_send_byte(CMD, 0xDB); //--set vcomh
	I2C_send_byte(CMD, 0x20); //0x20,0.77xVcc

	I2C_send_byte(CMD, 0x8D); //--set DC-DC enable
	I2C_send_byte(CMD, 0x14); //
	I2C_send_byte(CMD, 0xAF); //--turn on SSD1306 panel
}

void OLED_Init()
{
	I2C_send_byte(CMD, 0xAE);  // Display OFF
	I2C_send_byte(CMD, 0x8D); I2C_send_byte(CMD, 0x14);  // Charge pump ON
	I2C_send_byte(CMD, 0xAF);
}

void check_ACK()
{
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	if (((*I2C_SR1 >> 10) & 1) == 0)
	{
		UART_send_string("Data is sent!\n");
	}
	else
	{
		UART_send_string("Data is not sent!!!\n");
	}
}

void I2C_send_byte(ctrl_t ctrl_byte, uint8_t data)
{
	uint8_t* I2C_DR = (uint8_t*) (I2C1_BASE_ADDR + 0x10);
	uint32_t* I2C_SR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x14);
	*I2C_DR = ctrl_byte;
	while (((*I2C_SR1 >> 7) & 1) == 0);	// wait until data has been transferred
	check_ACK();
	*I2C_DR = data;
	while (((*I2C_SR1 >> 7) & 1) == 0);	// wait until data has been transferred
	check_ACK();
}

void I2C_stop()
{
	uint32_t* I2C_CR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x00);
	*I2C_CR1 |= 1 << 9;		// send STOP
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
	if (((*I2C_SR1 >> 1) & 1) == 1)
	{
		UART_send_string("Slave Address sent successfully!\n");
	}
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
	uint32_t* GPIOB_OSPEEDR = (uint32_t*) (GPIOB_BASE_ADDR + 0x08);
	*GPIOB_MODER &= ~(0xf << 12);	// clear bit
	*GPIOB_MODER |= (0b1010 << 12);	// set PB6, PB7 at AF mode
	*GPIOB_OTYPER |= (0b11 << 6);	// set open-drain mode
	*GPIOB_PUPDR &= ~(0xf << 12);	// clear bit
//	*GPIOB_PUPDR |= (0b0101 << 12);	// configure PB6, PB7 the I/O pull-up
	*GPIOB_OSPEEDR &= ~(0b11 << 6);	// set low speed
	*GPIOB_AFRL &= ~(0xff << 24);	// clear bit
	*GPIOB_AFRL |= (4 << 24) | (4 << 28);	// select AF04

	__HAL_RCC_I2C1_CLK_ENABLE();
	uint32_t* I2C_CR2 = (uint32_t*) (I2C1_BASE_ADDR + 0x04);
	uint32_t* I2C_CCR = (uint32_t*) (I2C1_BASE_ADDR + 0x1C);
	uint32_t* I2C_TRISE = (uint32_t*) (I2C1_BASE_ADDR + 0x20);
	uint32_t* I2C_CR1 = (uint32_t*) (I2C1_BASE_ADDR + 0x00);
	*I2C_CR2 |= (16 << 0);	// set f = 16MHz
	*I2C_CCR &= ~(1 << 15);	// select standard mode
	*I2C_CCR |= 80 << 0; 	// set SCL freq = 100 kHz
	*I2C_TRISE = 17; 		// set time rise
	*I2C_CR1 |= (1 << 0);	// enable peripheral
}
