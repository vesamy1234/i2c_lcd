/*
 * i2c.c
 *
 *  Created on: Jan 20, 2025
 *      Author: User
 */

#include "i2c.h"
//bool i2c_I2C1_masterTransmit(uint8_t Addr, uint8_t *pData, uint8_t len, uint32_t timeout)
//{
//  uint32_t count = 0;
//  uint8_t index = 0;
//
//  // Chờ I2C vào trạng thái bận
//  while ((I2C1->SR2 & I2C_SR2_BUSY))
//  {
//    if (++count > timeout)
//      return false;
//  }
//
//
//  // Xóa POS và tạo điều kiện Start
//  I2C1->CR1 &= ~(I2C_CR1_POS);
//  I2C1->CR1 |= I2C_CR1_START;
//
//  // Chờ bit Start được set
//  while (!(I2C1->SR1 & I2C_SR1_SB))
//  {
//    if (++count > timeout)
//      return false;
//  }
//  count = 0;
//
//  // Gửi địa chỉ Slave
//  I2C1->DR = Addr << 1;
//
//  while (!(I2C1->SR1 & I2C_SR1_ADDR))
//  {
//    if (++count > timeout)
//    {
//      return false;
//    }
//  }
//  count = 0;
//
//  // Xóa bit ADDR
//  (void)I2C1->SR1;
//  (void)I2C1->SR2;
//
//  // Truyền dữ liệu
//  while (len > 0U)
//  {
//    // Chờ bộ đệm trống
//    while (!(I2C1->SR1 & I2C_SR1_TXE))
//    {
//      if (++count > timeout)
//        return false;
//    }
//    count = 0;
//
//    // Gửi dữ liệu
//    I2C1->DR = pData[index];
//    index++;
//    len--;
//
//    // Nếu còn dữ liệu và BTF=1, gửi tiếp byte tiếp theo
//    if ((len > 0U) && (I2C1->SR1 & I2C_SR1_BTF))
//    {
//      I2C1->DR = pData[index];
//      index++;
//      len--;
//    }
//  }
//
//  // Chờ byte cuối cùng hoàn tất
//  while (!(I2C1->SR1 & I2C_SR1_BTF))
//  {
//    if (++count > timeout)
//      return false;
//  }
//
//  // Tạo điều kiện STOP
//  I2C1->CR1 |= I2C_CR1_STOP;
//
//  return true;
//}
bool i2c_I2C1_masterTransmit(uint8_t Addr, uint8_t *pData, uint8_t len, uint32_t timeout)
{
  uint32_t count = 0;
  uint8_t index = 0;
  // Ch�? I2C vào trạng thái bận
  while ((LL_I2C_IsActiveFlag_BUSY(I2C1)))
  {
    if (++count > timeout)
      return false;
  }

  // Bit POS được xóa để đảm bảo I2C hoạt động trong chế độ chuẩn (standard mode).
  LL_I2C_DisableBitPOS(I2C1);
  // Tạo đi�?u kiện Start
  LL_I2C_GenerateStartCondition(I2C1);
  // Ch�? bit start được tạo
  while (!(LL_I2C_IsActiveFlag_SB(I2C1)))
  {
    if (++count > timeout)
      return false;
  }
  count = 0;
  // Gửi địa chỉ slave
  LL_I2C_TransmitData8(I2C1, Addr<<1);
//   Ch�? ACK
  while (!(LL_I2C_IsActiveFlag_ADDR(I2C1)))
  {
    if (++count > timeout)
      return false;
  }
  count = 0;
  // Xóa c�? Addr
  (void)I2C1->SR1;
  (void)I2C1->SR2;
//  // Gửi thanh ghi thiết bị cần ghi ra
//  LL_I2C_TransmitData8(I2C1, reg);
  // Truy�?n dữ liệu
  while (len > 0U)
  {
    // Kiểm tra bộ đệm Tx có trống không
    while (!(LL_I2C_IsActiveFlag_TXE(I2C1)))
    {
      if (++count > timeout)
        return false;
    }
    count = 0;
    // Gửi dữ liệu ra
    LL_I2C_TransmitData8(I2C1, pData[index]);
    len--;
    index++;
    // Nếu truy�?n xong BTF=1 và len != 0 thì truy�?n tiếp
    if ((LL_I2C_IsActiveFlag_BTF(I2C1)) && (len > 0U))
    {
      // Gửi dữ liệu ra
      I2C1->DR = pData[index];
      len--;
      index++;
    }
    while (!(I2C1->SR1 & I2C_SR1_BTF))
    {
      if (++count > timeout)
        return false;
    }
  }
  // Tạo đi�?u kiện dừng
  LL_I2C_GenerateStopCondition(I2C1);
  return true;
}
void LCD_Write_CMD(uint8_t data)
{
	uint8_t buf[4] = {(data &0xF0)|0x04|0x08 , (data &0xF0)|0x00|0x08 , (data << 4)|0x04|0x08 , (data << 4)|0x00|0x08}; //RS=0, gửi lệnh
	i2c_I2C1_masterTransmit(0x27, buf, 4, 1000);
}

void LCD_Write_DATA(uint8_t data)
{
	uint8_t buf[4] = {(data &0xF0)|0x05|0x08 , (data &0xF0)|0x01|0x08 , (data << 4)|0x05|0x08 , (data << 4)|0x01|0x08}; //RS=1, gửi data
	i2c_I2C1_masterTransmit(0x27, buf, 4, 1000);
}

void LCD_Init()
{
	LCD_Write_CMD(0x33);                   // lenh de khoi tao
	LCD_Write_CMD(0x32);                  // lenh de khoi tao
	LCD_Write_CMD(0x28);                   // che do 4 bit, 2 hang, 5x7
	LCD_Write_CMD(0x0C);                   // hien thi man hinh
//	LCD_Write_CMD(0x0E);
	LCD_Write_CMD(0x06);                  // tang con tro
	LCD_Write_CMD(0x01);                   // xoa toan man hinh
	LL_mDelay(2);
}

void LCD_Clear()                                //xoa toan man hinh
{
	LCD_Write_CMD(0x01);
}

void LCD_Location(uint8_t x, uint8_t y)         // chon vi tri
{
  if(x == 0)
	  LCD_Write_CMD(0x80 + y);
  else if(x == 1)
	  LCD_Write_CMD(0xC0 + y);
}

void LCD_Write_String(char* string)              // ghi chuoi ki tu
{
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		LCD_Write_DATA(string[i]);
	}
}

void LCD_Write_Number(int8_t number)                 // ghi chu so
{
	char buffer[8];
	sprintf(buffer, "%d", number);
	LCD_Write_String(buffer);
}

void LCD_Write_Float(double number)                 // ghi chu so thap phan
{
	char buffer[16];
	floatToStr(number,buffer,10);
	LCD_Write_String(buffer);
}
void floatToStr(double num, char *str, int8_t precision)
{
    int64_t intPart = (int64_t)num;  // Lay phan nguyen
    double decimalPart = num - (double)intPart;  // Lay phan thap phân
    int8_t i = 0;

    // Xu ly phan nguyen
    if (intPart == 0)
    {
        str[i++] = '0';
    }
    else
    {
        if (intPart < 0)
        {
            str[i++] = '-';
            intPart = -intPart;
            decimalPart = -decimalPart;  // Cap nhat phan thap phân theo dau
        }

        // Chuyen tung chu so cua phan nguyen sang chuoi
        int64_t tempInt = intPart;
        int8_t len = 0;
        while (tempInt > 0)
        {
            len++;
            tempInt /= 10;
        }

        for (int8_t j = len - 1; j >= 0; j--)
        {
            str[j + i] = (intPart % 10) + '0';
            intPart /= 10;
        }
        i += len;
    }
    if (decimalPart == 0)
    {
    	str[i] = '\0';
    	return;
    }
    // Them dau cham thap phân
    str[i++] = '.';

    for (int8_t j = 0; j < precision; j++)
    {
        decimalPart *= 10;
        int8_t digit = (int8_t)(decimalPart);  // Làm tròn trước khi lấy phần nguyên
        str[i++] = digit + '0';
        decimalPart -= digit;
    }

    //Ket thuc chuoi
    str[i] = '\0';
}
