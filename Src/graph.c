#include "graph.h"

static LCD_typedef LCD;

void GRPH_DrawPixel(uint16_t x, uint16_t y) {
	if (x > LCD.Width || y > LCD.Height) return;
	*(__IO uint16_t *) (LCD_FRAME_BUFFER + LCD_PIXEL_SIZE * (y * LCD_PIXEL_WIDTH + x)) = LCD.ForegroundColor;
}

void GRPH_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	int i;
	for (i=x1; i<x2; i++) GRPH_DrawPixel(i, y1);
	for (i=x1; i<x2; i++) GRPH_DrawPixel(i, y2);
	for (i=y1; i<y2; i++) GRPH_DrawPixel(x1, i);
	for (i=y1; i<y2; i++) GRPH_DrawPixel(x2, i);
}


uint32_t DMA2D_Convert565ToARGB8888(uint16_t color) {
	/* Input LCD.ForegroundColor: RRRRR GGGGGG BBBBB */
	/* Output LCD.ForegroundColor: RRRRR000 GGGGGG00 BBBBB000 */
	uint32_t DMA2D_Color = 0;
	
	DMA2D_Color |= (color & 0xF800) << 8;
	DMA2D_Color |= (color & 0x07E0) << 5;
	DMA2D_Color |= (color & 0x001F) << 3;
	return DMA2D_Color;
}

void DMA2DGRPH_Fill() {
	uint32_t DMA2D_Color = 0;

	/* Set parameters */
	hdma2d.Init.Mode = DMA2D_R2M;
	hdma2d.Init.ColorMode = DMA2D_RGB565;
	hdma2d.Init.OutputOffset = 0;

	/* Convert LCD.ForegroundColor */
	DMA2D_Color = DMA2D_Convert565ToARGB8888(LCD.BackgroundColor);

	/* Init DMA2D and start transfer */
	if (HAL_DMA2D_Init(&hdma2d) == HAL_OK) {
		if (HAL_DMA2D_ConfigLayer(&hdma2d, 0) == HAL_OK) {
			if (HAL_DMA2D_Start(&hdma2d, DMA2D_Color, (uint32_t)(LCD_FRAME_BUFFER), LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT) == HAL_OK) {        
				HAL_DMA2D_PollForTransfer(&hdma2d, 20);
			}
		}
	}
}

void GRPH_DrawCircle(uint16_t x0, uint16_t y0, uint16_t rad)
{
    int16_t x = rad;
    int16_t y = 0;
		int16_t error2 = 1 - x;
    
    while(x >= y) {
        GRPH_DrawPixel( x + x0,  y + y0);
        GRPH_DrawPixel( y + x0,  x + y0);
        GRPH_DrawPixel(-x + x0,  y + y0);
        GRPH_DrawPixel(-y + x0,  x + y0);
        GRPH_DrawPixel(-x + x0, -y + y0);
        GRPH_DrawPixel(-y + x0, -x + y0);
        GRPH_DrawPixel( x + x0, -y + y0);
        GRPH_DrawPixel( y + x0, -x + y0);
        y++;
        if(error2 <= 0) {
            error2 += 2 * y + 1;
        } else {
					  x--;
            error2 += 2 * (y - x) + 1;
				}	
    }
}

void GRPH_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    const uint16_t deltaX = ABS(x2 - x1);
    const uint16_t deltaY = ABS(y2 - y1);
    const int16_t signX = x1 < x2 ? 1 : -1;
    const int16_t signY = y1 < y2 ? 1 : -1;
    
		int16_t error2 = 0 ;
    int16_t error  = deltaX - deltaY;
    
    //GRPH_DrawPixel(x1, y1);
    GRPH_DrawPixel(x2, y2);
    while(x1 != x2 || y1 != y2) {
        GRPH_DrawPixel(x1, y1);
        error2 = error * 2;
        
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void GRPH_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3)
{
    const uint16_t deltaX = ABS(x2 - x1);
    const uint16_t deltaY = ABS(y2 - y1);
    const int16_t signX = x1 < x2 ? 1 : -1;
    const int16_t signY = y1 < y2 ? 1 : -1;
    
		int16_t error2 = 0 ;
    int16_t error  = deltaX - deltaY;
    
    //GRPH_DrawPixel(x1, y1);
    //GRPH_DrawPixel(x2, y2);
		GRPH_DrawLine(x2, y2, x3, y3);
    while(x1 != x2 || y1 != y2) {
				GRPH_DrawLine(x1, y1, x3, y3);
        error2 = error * 2;
        
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

//void GRPH_DrawVector(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rad)
//{
//    const uint16_t deltaX = ABS(x2 - x1);
//    const uint16_t deltaY = ABS(y2 - y1);
//    const int16_t signX = x1 < x2 ? 1 : -1;
//    const int16_t signY = y1 < y2 ? 1 : -1;
//    
//		int16_t error2 = 0 ;
//		uint16_t cnt = 0 ;
//    int16_t error  = deltaX - deltaY;
//    
//    //GRPH_DrawPixel(x2, y2);
//    while(x1 != x2 || y1 != y2) {
//        GRPH_DrawPixel(x1, y1);
//        error2 = error * 2;
//        
//        if(error2 > -deltaY) {
//            error -= deltaY;
//            x1 += signX;
//        }
//        if(error2 < deltaX) {
//            error += deltaX;
//            y1 += signY;
//        }
//				cnt++;
//				
//				if (cnt > rad) return;
//    }
//}

void GRPH_SetXY(uint16_t X, uint16_t Y) {
	if (X >= LCD.Width || Y >= LCD.Height) {
		return;
	}
	LCD.CurrentX = X;
	LCD.CurrentY = Y;
}

void GRPH_SetColors(uint32_t Foreground, uint32_t Background) {
	LCD.ForegroundColor = Foreground;
	LCD.BackgroundColor = Background;
}

void GRPH_SetForeColor(uint32_t Foreground) {
	LCD.ForegroundColor = Foreground;
}

uint32_t GRPH_GetForeColor() {
	return LCD.ForegroundColor;
}

void GRPH_Init() {
	LCD.CurrentX = 0;
	LCD.CurrentY = 0;
	LCD.CurrentFont = &Font_7x10;
	LCD.ForegroundColor = GRPH_COLOR_WHITE;
	LCD.BackgroundColor = GRPH_COLOR_BLACK;
	LCD.Height = LCD_PIXEL_HEIGHT;
	LCD.Width = LCD_PIXEL_WIDTH;
}

uint8_t GRPH_Putc(char c) {
	uint32_t i, b, j;
	uint32_t tmpfc;
	
	/* Check current coordinates */
	if ((LCD.CurrentX + LCD.CurrentFont->FontWidth) >= LCD.Width || c == '\n') {
		/* If at the end of a line of display, go to new line and set x to 0 position */
		LCD.CurrentY += LCD.CurrentFont->FontHeight;
		//LCD.CurrentX = LCD.StartX;
		
		/* Check X */
		if ((LCD.CurrentX + LCD.CurrentFont->FontWidth) >= LCD.Width) {
			LCD.CurrentX = 0;
		}
		
		/* Check for Y position */
		if (LCD.CurrentY >= LCD.Height) {
			/* Return error */
			return 0;
		}
	}
	
	tmpfc = LCD.ForegroundColor;
	
	/* Draw character */
	if (c != '\n') {
		/* Draw all pixels */
		for (i = 0; i < LCD.CurrentFont->FontHeight; i++) {
			b = LCD.CurrentFont->data[(c - 32) * LCD.CurrentFont->FontHeight + i];
			for (j = 0; j < LCD.CurrentFont->FontWidth; j++) {
				if ((b << j) & 0x8000) {
					GRPH_SetForeColor(tmpfc);
					GRPH_DrawPixel(LCD.CurrentX + j, (LCD.CurrentY + i));
				} else {
					GRPH_SetForeColor(LCD.BackgroundColor);
					GRPH_DrawPixel(LCD.CurrentX + j, (LCD.CurrentY + i));
				}
			}
		}
	
		/* Set new current X location */
		LCD.CurrentX += LCD.CurrentFont->FontWidth;
	}
	GRPH_SetForeColor(tmpfc);
	return 1;
}

void GRPH_Puts(char* str) {
	/* Send till string ends or error returned */
	while (*str) {
		/* Check if string OK */
		if (!GRPH_Putc(*str)) {
			/* Return error */
			return ;
		}
		
		/* Increase pointer */
		str++;
	}
}






