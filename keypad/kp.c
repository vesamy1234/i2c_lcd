/*
 * kp.c
 *
 *  Created on: Feb 15, 2025
 *      Author: User
 */

#include "kp.h"


extern volatile uint8_t key_current;
extern volatile uint8_t key_last;
double display_text [100];
uint8_t i = 0;
uint8_t decimalFlag = 0;
double num = 0;
double decimalDivisor = 1; // số lần chia 10
const uint8_t key_code [8][4] =
{
		{left , 'x' ,  7  , '(' },
		{ ' ' , DEL ,  9  , ';' },
		{right, '^' ,  8  , ')' },
		{ Sol , AC  , '+' , ':' },
		{  4  ,  1  ,  khong        },
		{  5  ,  2  , '.'       },
		{  6  ,  3  , '='       },
		{ '-' , '*' , '/'       },
};


void selectRow(uint8_t row)
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_3);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);

    // Gán lại giá trị cho các bit theo `row`
    if (row & 0x01) LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
    if (row & 0x02) LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
    if (row & 0x04) LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
}
uint8_t Keypad_Getkey()
{
	for (uint8_t row=0 ; row<8 ; row ++)
	{
		selectRow(row);
		LL_mDelay(5);
			if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_15) == 0)
			{
				LL_mDelay(10);
				if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_15) == 0){
					return key_code[row][0];
				}
			}
			else if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_14) == 0)
			{
				LL_mDelay(10);
				if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_14) == 0){
					return key_code[row][1];
				}
			}
			else if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_13) == 0)
			{
				LL_mDelay(10);
				if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_13) == 0){
					return key_code[row][2];
				}
			}
			else if (row < 4 && LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_12) == 0)
			{
				LL_mDelay(10);
				if (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_12) == 0){
					return key_code[row][3];
				}
			}
	}
	return 0;
}
void Press (uint8_t key)
{
	if ( key > 0 && key <= 10 )
	{
		if (key == khong)
		{
			key = 0;
		}
		if (!decimalFlag){
			num = num*10 + key;
		}
		else
		{
			decimalDivisor *= 10;
			num = num + key / decimalDivisor;
		}
		LCD_Write_Number(key);
	}
	else if (key == '.')
	{
		decimalFlag = 1;
		LCD_Write_String(".");
	}
	else if (key == '+' || key == '-' || key == '*' || key == '/' || key == '(' || key == ')')
	{
		decimalFlag = 0;
		decimalDivisor = 1;
		display_text[i++] = num;
		num = 0;
		display_text[i++] = key;
		char buffer[2] = { key, '\0' };
		LCD_Write_String(buffer);
	}
}
void Keypad_handle()
{
	if ( key_current != key_last )
	{
		if ( key_current !=0 ) Press(key_current);
//		else Release (key_last);
		key_last = key_current;
	}
}
