#include "sdram.h"

#define LCD_PIXEL_WIDTH        240
#define LCD_PIXEL_HEIGHT       320
#define LCD_PIXEL_SIZE         2

/* Frame settings */
#define LCD_FRAME_BUFFER           ((uint32_t)SDRAM_START_ADR)
#define LCD_BUFFER_OFFSET          ((uint32_t)(LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT * LCD_PIXEL_SIZE))

