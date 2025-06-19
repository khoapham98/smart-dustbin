/*
 * hcsr04.h
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_
#define GPIOC_BASE_ADDR 0x40020800

void HCSR04_Init();
void trig_HCSR04();
uint32_t cal_distance();

#endif /* INC_HCSR04_H_ */
