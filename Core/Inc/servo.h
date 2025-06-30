/*
 * servo.h
 *
 *  Created on: Jun 19, 2025
 *      Author: ACER
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_
#define GPIOB_BASE_ADDR 0x40020400
#define TIM3_BASE_ADDR 0x40000400

typedef enum
{
	LEFT = 500,
	MIDDLE = 1500,
	RIGHT = 2450
} direc_t;

void TIM3_Init();
void servo_ctrl(direc_t d);

#endif /* INC_SERVO_H_ */
