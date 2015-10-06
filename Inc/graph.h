#include "stdint.h"
#include "font_7_10.h"
#include "lcd.h"

typedef struct _TM_LCD_INT_t {
	uint16_t Width;
	uint16_t Height;
	uint8_t Orientation;
	uint32_t CurrentFrameBuffer;
	uint32_t FrameOffset;
	uint8_t CurrentLayer;
	
	/* Strings */
	uint32_t ForegroundColor;
	uint32_t BackgroundColor;
	FONT_typedef* CurrentFont;
	uint16_t CurrentX;
	uint16_t CurrentY;
} LCD_typedef;

#define GRPH_COLOR_WHITE            0xFFFF
#define GRPH_COLOR_BLACK            0x0000
#define GRPH_COLOR_RED              0xF800
#define GRPH_COLOR_GREEN            0x07E0
#define GRPH_COLOR_GREEN2           0xB723
#define GRPH_COLOR_BLUE             0x001F
#define GRPH_COLOR_BLUE2            0x051D
#define GRPH_COLOR_YELLOW           0xFFE0
#define GRPH_COLOR_ORANGE           0xFBE4
#define GRPH_COLOR_CYAN             0x07FF
#define GRPH_COLOR_MAGENTA          0xA254
#define GRPH_COLOR_GRAY             0x7BEF
#define GRPH_COLOR_BROWN            0xBBCA

/* Absolute number */
#define ABS(X)	((X) > 0 ? (X) : -(X))  

extern DMA2D_HandleTypeDef hdma2d;

void GRPH_DrawPixel(uint16_t x, uint16_t y);
void GRPH_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void DMA2DGRPH_Fill(void);
void GRPH_DrawCircle(uint16_t x0, uint16_t y0, uint16_t rad);
void GRPH_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void GRPH_SetXY(uint16_t X, uint16_t Y);
void GRPH_SetColors(uint32_t Foreground, uint32_t Background);
uint8_t TGRPH_Putc(char c);
void GRPH_Puts(char* str);
void GRPH_Init(void);


