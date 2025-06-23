/*
 * oled.h
 *
 *  Created on: Jun 20, 2025
 *      Author: ACER
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_
#define I2C1_BASE_ADDR 0x40005400
#define SSD1306_ADDR 0x3C

typedef enum
{
	WRITE, READ
} mode_t;

typedef enum
{
	CMD = 0x00,
	DATA = 0x40
} ctrl_t;

void check_ACK();
void SSD1306_Init();
void I2C_Init();
void OLED_Init();
void I2C_start();
void I2C_send_addr(uint8_t slave_addr, mode_t mode);
void I2C_send_byte(ctrl_t ctrl_byte, uint8_t data);
void I2C_stop();
#endif /* INC_OLED_H_ */
