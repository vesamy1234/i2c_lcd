/*
 * kp.h
 *
 *  Created on: Feb 15, 2025
 *      Author: User
 */

#ifndef KP_H_
#define KP_H_

#include "stdio.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_utils.h"
#include "i2c.h"

#define left 'l'
#define right 'r'
#define Sol 's'
#define DEL 'd'
#define AC 'a'
#define Cal 'c'
#define khong 10

uint8_t Keypad_Getkey(void);
void selectRow(uint8_t row);
void Press (uint8_t key);
void Keypad_handle();

#endif /* KP_H_ */
