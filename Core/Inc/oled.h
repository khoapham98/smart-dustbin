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
#define PAGE 4
#define COLUMN 128

typedef enum
{
	WRITE, READ
} mode_t;

typedef enum
{
	CMD = 0x00,
	DATA = 0x40
} ctrl_t;
void print_left_to_right();
void OLED_print_lidClose();
void OLED_print_lidOpen();
void SSD1306_Init();
void I2C_Init();
void OLED_Init();
void OLED_FillWhite();
void OLED_ClrScr();
void I2C_start();
void OLED_WriteData(uint8_t data);
void OLED_WriteCMD(uint8_t cmd);
void I2C_send_addr(uint8_t slave_addr, mode_t mode);
void I2C_send_byte(uint8_t data);
void I2C_stop();
#endif /* INC_OLED_H_ */
