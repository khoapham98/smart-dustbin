/*
 * mydelay.h
 *
 *  Created on: Jun 16, 2025
 *      Author: ACER
 */

#ifndef INC_MYDELAY_H_
#define INC_MYDELAY_H_
#define TIM2_BASE_ADDR 0x40000000

void TIM2_Init();
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#endif /* INC_MYDELAY_H_ */
