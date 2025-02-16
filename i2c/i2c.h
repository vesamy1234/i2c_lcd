/*
 * i2c.h
 *
 *  Created on: Jan 20, 2025
 *      Author: User
 */

#ifndef I2C_H_
#define I2C_H_

#include "stdio.h"
#include "stm32f1xx_ll_i2c.h"
#include "stm32f1xx_ll_utils.h"
#include "stdbool.h"
#include "string.h"

bool i2c_I2C1_masterTransmit(uint8_t Addr, uint8_t *pData, uint8_t len, uint32_t timeout);
void LCD_Write_CMD(uint8_t data);
void LCD_Write_DATA(uint8_t data);
void LCD_Init();
void LCD_Clear();
void LCD_Location(uint8_t x, uint8_t y);
void LCD_Write_String(char* string);
void LCD_Write_Number(int8_t number);
void LCD_Write_Float(double number);
void floatToStr(double num, char *str, int8_t precision);


#endif /* I2C_H_ */
