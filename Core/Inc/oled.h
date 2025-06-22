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
	FALSE, TRUE
} bool_t;

typedef enum
{
	WRITE, READ
} mode_t;

void I2C_Init();
bool_t I2C_send_start(uint8_t slave_addr, mode_t mode);
void I2C_send_data(char* str);

#endif /* INC_OLED_H_ */
