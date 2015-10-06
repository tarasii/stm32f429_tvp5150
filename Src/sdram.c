#include "sdram.h"

uint8_t SDRAM_Init(SDRAM_HandleTypeDef *hsdram)
{
	FMC_SDRAM_CommandTypeDef Command;
	uint32_t timeout;
	
	Command.CommandMode				= FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget 			= FMC_SDCMR_CTB2;
	Command.AutoRefreshNumber 		= 1;
	Command.ModeRegisterDefinition 	= 0;
	
	/* Send command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	
	/* Little delay */
	timeout = SDRAM_TIMEOUT * 0xF;
	while (timeout--);
	
	/* Configure a PALL (precharge all) command */ 
	Command.CommandMode          	= FMC_SDRAM_CMD_PALL;
	Command.CommandTarget          	= FMC_SDCMR_CTB2;
	Command.AutoRefreshNumber      	= 1;
	Command.ModeRegisterDefinition 	= 0;
	
	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Configure a Auto-Refresh command */ 
	Command.CommandMode            	= FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget          	= FMC_SDCMR_CTB2;
	Command.AutoRefreshNumber      	= 8;
	Command.ModeRegisterDefinition 	= 0;
	
	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	
	/* Configure a load Mode register command */
	Command.CommandMode            	= FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget          	= FMC_SDCMR_CTB2;
	Command.AutoRefreshNumber      	= 1;
	Command.ModeRegisterDefinition 	= (uint32_t)SDRAM_REG_VALUE;
	
	/* Wait until the SDRAM controller is ready */
	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
  
	/* Step 6: Set the refresh rate counter */
	/* Set the device refresh rate */
	HAL_SDRAM_ProgramRefreshRate(hsdram, SDRAM_REFRESH_COUNT); 
	
	/* Little delay */
	timeout = SDRAM_TIMEOUT * 0xF;
	while (timeout--);

	SDRAM_Write8(0x50, 0x45);
	if (SDRAM_Read8(0x50) == 0x45) {
		return 1;
	}
	return 0;
}

void SDRAM_InitPins(void) {
	//
  GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	__HAL_RCC_FMC_CLK_ENABLE();

}


