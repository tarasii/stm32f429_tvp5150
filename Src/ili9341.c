#include "ili9341.h"

void ILI9341_SendCommand(uint8_t data) {
	ILI9341_WRX_RESET;
	ILI9341_CS_RESET;
	SPI_Send(data);
	ILI9341_CS_SET;
}

void ILI9341_SendData(uint8_t data) {
	ILI9341_WRX_SET;
	ILI9341_CS_RESET;
	SPI_Send(data);
	ILI9341_CS_SET;
}


void ILI9341_Init(void) {

	ILI9341_CS_SET;
	
	/* Initialization sequence */
	ILI9341_SendCommand(0xCA);
	ILI9341_SendData(0xC3);
	ILI9341_SendData(0x08);
	ILI9341_SendData(0x50);
	ILI9341_SendCommand(ILI9341_POWERB);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0xC1);
	ILI9341_SendData(0x30);
	ILI9341_SendCommand(ILI9341_POWER_SEQ);
	ILI9341_SendData(0x64);
	ILI9341_SendData(0x03);
	ILI9341_SendData(0x12);
	ILI9341_SendData(0x81);
	ILI9341_SendCommand(ILI9341_DTCA);
	ILI9341_SendData(0x85);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x78);
	ILI9341_SendCommand(ILI9341_POWERA);
	ILI9341_SendData(0x39);
	ILI9341_SendData(0x2C);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x34);
	ILI9341_SendData(0x02);
	ILI9341_SendCommand(ILI9341_PRC);
	ILI9341_SendData(0x20);
	ILI9341_SendCommand(ILI9341_DTCB);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x00);
	ILI9341_SendCommand(ILI9341_FRC);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x1B);
	ILI9341_SendCommand(ILI9341_DFC);
	ILI9341_SendData(0x0A);
	ILI9341_SendData(0xA2);
	ILI9341_SendCommand(ILI9341_POWER1);
	ILI9341_SendData(0x10);
	ILI9341_SendCommand(ILI9341_POWER2);
	ILI9341_SendData(0x10);
	ILI9341_SendCommand(ILI9341_VCOM1);
	ILI9341_SendData(0x45);
	ILI9341_SendData(0x15);
	ILI9341_SendCommand(ILI9341_VCOM2);
	ILI9341_SendData(0x90);
	ILI9341_SendCommand(ILI9341_MAC);
	ILI9341_SendData(0xC8);
	ILI9341_SendCommand(ILI9341_3GAMMA_EN);
	ILI9341_SendData(0x00);
	ILI9341_SendCommand(ILI9341_RGB_INTERFACE);
	ILI9341_SendData(0xC2);
	ILI9341_SendCommand(ILI9341_DFC);
	ILI9341_SendData(0x0A);
	ILI9341_SendData(0xA7);
	ILI9341_SendData(0x27);
	ILI9341_SendData(0x04);

	ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0xEF);

	ILI9341_SendCommand(ILI9341_PAGE_ADDR);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x01);
	ILI9341_SendData(0x3F);
	ILI9341_SendCommand(ILI9341_INTERFACE);
	ILI9341_SendData(0x01);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x06);

	ILI9341_SendCommand(ILI9341_GRAM);
	HAL_Delay(10);

	ILI9341_SendCommand(ILI9341_GAMMA);
	ILI9341_SendData(0x01);

	ILI9341_SendCommand(ILI9341_PGAMMA);
	ILI9341_SendData(0x0F);
	ILI9341_SendData(0x29);
	ILI9341_SendData(0x24);
	ILI9341_SendData(0x0C);
	ILI9341_SendData(0x0E);
	ILI9341_SendData(0x09);
	ILI9341_SendData(0x4E);
	ILI9341_SendData(0x78);
	ILI9341_SendData(0x3C);
	ILI9341_SendData(0x09);
	ILI9341_SendData(0x13);
	ILI9341_SendData(0x05);
	ILI9341_SendData(0x17);
	ILI9341_SendData(0x11);
	ILI9341_SendData(0x00);
	ILI9341_SendCommand(ILI9341_NGAMMA);
	ILI9341_SendData(0x00);
	ILI9341_SendData(0x16);
	ILI9341_SendData(0x1B);
	ILI9341_SendData(0x04);
	ILI9341_SendData(0x11);
	ILI9341_SendData(0x07);
	ILI9341_SendData(0x31);
	ILI9341_SendData(0x33);
	ILI9341_SendData(0x42);
	ILI9341_SendData(0x05);
	ILI9341_SendData(0x0C);
	ILI9341_SendData(0x0A);
	ILI9341_SendData(0x28);
	ILI9341_SendData(0x2F);
	ILI9341_SendData(0x0F);

	ILI9341_SendCommand(ILI9341_SLEEP_OUT);
	HAL_Delay(10);
	ILI9341_SendCommand(ILI9341_DISPLAY_ON);

	ILI9341_SendCommand(ILI9341_GRAM);
}

void ILI9341_DisplayOn(void) {
	/* Enable LTDC */
	LTDC->GCR |= LTDC_GCR_LTDCEN;
	
	ILI9341_SendCommand(0x29);
}

void ILI9341_DisplayOff(void) {
	/* Disable LTDC */
	LTDC->GCR &= ~LTDC_GCR_LTDCEN;
	ILI9341_SendCommand(0x28);
}

void ILI9341_InitPins(void) {

	__HAL_RCC_DMA2D_CLK_ENABLE();
	__HAL_RCC_LTDC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = ILI9341_WRX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(ILI9341_WRX_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = ILI9341_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

