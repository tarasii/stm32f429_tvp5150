#include "spi.h"

uint8_t SPI_Read(uint8_t address) {
	uint8_t data, tmp;
	/* Send address with read command */
	tmp = address | 0x80;
	HAL_SPI_Transmit(&hspi5, &tmp, 1, 100);
	/* Read data */
	HAL_SPI_Receive(&hspi5, &data, 1, 100);
	/* Return data */
	return data;
}

void SPI_Write(uint8_t address, uint8_t data) {
	/* Send address with write command */
	HAL_SPI_Transmit(&hspi5, &address, 1, 100);
	/* Write data */
	HAL_SPI_Transmit(&hspi5, &data, 1, 100);
}

void SPI_Send(uint8_t data) {
	HAL_SPI_Transmit(&hspi5, &data, 1, 100);
}

void SPI_Init_Pins(void){
  GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	//
}

