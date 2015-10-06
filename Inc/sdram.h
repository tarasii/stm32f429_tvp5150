#include "stm32f4xx_hal.h"

#define SDRAM_START_ADR             (uint32_t)0xD0000000
#define SDRAM_MEMORY_SIZE           (uint32_t)0x800000

#define SDRAM_Write8(address, value)       (*(__IO uint8_t *) (SDRAM_START_ADR + (address)) = (value))
#define SDRAM_Read8(address)               (*(__IO uint8_t *) (SDRAM_START_ADR + (address)))

#define SDRAM_TIMEOUT                   ((uint32_t)0xFFFF) 
#define SDRAM_REFRESH_COUNT         680
#define SDRAM_REG_VALUE             0x0231

uint8_t SDRAM_Init(SDRAM_HandleTypeDef *hsdram);
void SDRAM_InitPins(void);




