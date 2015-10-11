#include "stm32f4xx_hal.h"


extern SPI_HandleTypeDef hspi5;

uint8_t SPI_Read(uint8_t address);
void SPI_Write(uint8_t address, uint8_t data);
void SPI_Send(uint8_t data);
void SPI_Init_Pins(void);

