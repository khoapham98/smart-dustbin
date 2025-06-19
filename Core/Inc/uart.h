/*
 * uart.h
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#define GPIOD_BASE_ADDR 0x40020C00
#define USART2_BASE_ADDR 0x40004400

void USART2_Init();
void UART_send_char(char data);
void UART_send_string(char* str, ...);

#endif /* INC_UART_H_ */
