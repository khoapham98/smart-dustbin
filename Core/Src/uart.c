/*
 * uart.c
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */
#include "main.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "uart.h"

/* This function is used to send string */
void UART_send_string(char* str, ...)
{
	va_list list;
	va_start(list, str);
	char print_buf[128] = { 0 };
	vsprintf(print_buf, str, list);
	int size = strlen(print_buf);
	for (int i = 0; i < size; i++)
	{
		UART_send_char(print_buf[i]);
	}
	va_end(list);
}

/* This function is used to send character */
void UART_send_char(char data)
{
	uint32_t* USART2_DR = (uint32_t*) (USART2_BASE_ADDR + 0x04);
	*USART2_DR = data;

	uint32_t* USART2_SR = (uint32_t*) (USART2_BASE_ADDR + 0x00);
	while (((*USART2_SR >> 7) & 1) == 0);	// wait until the data is transferred to the Shift Register
}

/* This function is used to initialize the USART2
 * PD5: TX pin
 * PD6: RX pin
 * Data size: 8 bits
 * Parity: Odd
 * Baud rate: 14400 bps
*/
void USART2_Init()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*) (GPIOD_BASE_ADDR + 0x00);
	uint32_t* GPIOD_AFRL = (uint32_t*) (GPIOD_BASE_ADDR + 0x20);
	*GPIOD_MODER &= ~(0xf << 10);
	*GPIOD_MODER |= (0b1010 << 10); // configure PD5 and PD6 at AF mode
	*GPIOD_AFRL &= ~(0xff << 20);
	*GPIOD_AFRL |= (7 << 20) | (7 << 24);	// AF07 for PD5 and PD6

	__HAL_RCC_USART2_CLK_ENABLE();
	uint32_t* USART2_CR1 = (uint32_t*) (USART2_BASE_ADDR + 0x0C);
	uint32_t* USART2_BRR = (uint32_t*) (USART2_BASE_ADDR + 0x08);
	*USART2_CR1 |= (1 << 12);	// set word length = 9 data bits
	*USART2_CR1 |= (1 << 10); 	// enable parity control
	*USART2_CR1 |= (1 << 9); 	// select odd parity
	*USART2_CR1 |= (1 << 3); 	// enable transmitter
	*USART2_BRR = (69 << 4) | (0b0111 << 0);	// set baud rate at 14400 bps
	*USART2_CR1 |= (1 << 13); 	// enable USART
}
