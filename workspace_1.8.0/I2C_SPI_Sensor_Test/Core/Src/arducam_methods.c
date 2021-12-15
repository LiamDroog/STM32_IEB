/*
 * arducam_methods.c
 *
 *  Created on: Dec 15, 2021
 *      Author: Liam Droog
 */
#include "arducam_methods.h"
#include "main.h"
#include "delay.h"

#define CS_PORT NFC_NSS_GPIO_Port
#define CS_PIN NFC_NSS_Pin

//void SPI2_write_reg(uint8_t addr, uint8_t data)
//{
//	 bus_write(addr | 0x80, data);
//}
//
//uint8_t SPI2_read_reg(uint8_t addr)
//{
//	uint8_t data;
//	data = bus_read(addr & 0x7F);
//	return data;
//}
//
////uint8_t bus_read(int address)
////{
////	uint8_t value;
////	CS_LOW();
////	SPI2_ReadWriteByte(address);
////	value = SPI2_ReadWriteByte(0x00);
////	CS_HIGH();
////	return value;
////}
//
//uint8_t bus_write(int address,int value)
//{
//	CS_LOW();
//	delay_us(10);
//	SPI2_ReadWriteByte(address);
//	SPI2_ReadWriteByte(value);
//	delay_us(10);
//	CS_HIGH();
//	return 1;
//}



// ########################### SPI STUFF #################################
////Control the CS pin
//void CS_HIGH(void)
//{
// 	GPIO_SetBits(CS_PORT,CS_PIN);
//}
//
//void CS_LOW(void)
//{
// 	GPIO_ResetBits(CS_PORT,CS_PIN);
//}

//uint8_t SPI2_ReadWriteByte(uint8_t TxData)
//{
//	uint8_t retry=0;
//	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
//	{
//		retry++;
//		if(retry>200)return 0;
//	}
//	SPI_I2S_SendData(SPI2, TxData);
//	retry=0;
//
//	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
//	{
//		retry++;
//		if(retry>200)return 0;
//	}
//	return SPI_I2S_ReceiveData(SPI2);
//}
