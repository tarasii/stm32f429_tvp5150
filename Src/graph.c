#include "graph.h"

GRPH_RGB GRPH_ForeColor;
GRPH_RGB GRPH_BackColor;


uint8_t VideoBuff[GRPH_MAX_X * GRPH_MAX_Y * 3]; //800x600 (1440000) //640x480 (921600) //320x200(192000)

uint8_t GRPH_GetY(uint8_t r, uint8_t g, uint8_t b)
{
	float tmp;
	tmp = 0.299 * r + 0.587 * g + 0.114 * b;
	return (uint8_t) tmp;
}

uint8_t GRPH_GetCb(uint8_t r, uint8_t g, uint8_t b)
{
	float tmp;
	tmp = - 1.168736 * r - 0.331264 * g + 0.5 * b;
	return 128 + (uint8_t) tmp;
}

uint8_t GRPH_GetCr(uint8_t r, uint8_t g, uint8_t b)
{
	float tmp;
	tmp = 0.5 * r + 0.418688 * g + 0.081312 * b;
	return 128 + (uint8_t) tmp;
}

void GRPH_SetForeColor(uint8_t r, uint8_t g, uint8_t b)
{
	GRPH_ForeColor.R = r;
	GRPH_ForeColor.G = g;
	GRPH_ForeColor.B = b;
}	

void GRPH_SetBackColor(uint8_t r, uint8_t g, uint8_t b)
{
	GRPH_BackColor.R = r;
	GRPH_BackColor.G = g;
	GRPH_BackColor.B = b;
}	

void GRPH_PutPixel(uint16_t x, uint16_t y)
{
	uint16_t *addr;
	uint16_t mx = GRPH_MAX_X;
	//uint16_t my = DMA2D->NLR;//GRPH_MAX_Y;
	uint16_t my = GRPH_MAX_Y;
	
	if(x > mx || y > my) return;
	
	addr = (uint16_t *) DMA2D->FGMAR + y * GRPH_MAX_X + x;
	*addr = ((GRPH_ForeColor.R & 0x1f) << 10) + ((GRPH_ForeColor.G & 0x3f) << 5) + (GRPH_ForeColor.B & 0x1f);
//	VideoBuff[addr]     = GRPH_GetY (r, g, b);
//	VideoBuff[addr + 1] = GRPH_GetCb(r, g, b);
//	VideoBuff[addr + 2] = GRPH_GetCr(r, g, b);
}

int abs(int x)
{
	int res;
	if(x < 0) res = -x;
	else      res =  x;
	return res;
}

void GRPH_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    const uint16_t deltaX = abs(x2 - x1);
    const uint16_t deltaY = abs(y2 - y1);
    const uint16_t signX = x1 < x2 ? 1 : -1;
    const uint16_t signY = y1 < y2 ? 1 : -1;
    
    uint16_t error = deltaX - deltaY;
		uint16_t error2;
    
    GRPH_PutPixel(x2, y2);
    while(x1 != x2 || y1 != y2) {
        GRPH_PutPixel(x1, y1);
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


void GRPH_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) 
{
	GRPH_DrawLine(x1, y1, x2, y1);
	GRPH_DrawLine(x2, y1, x2, y2);
	GRPH_DrawLine(x1, y2, x2, y2);
	GRPH_DrawLine(x1, y1, x1, y2);
}

void GRPH_Circle(uint16_t x0, uint16_t y0, uint16_t rad)
{
    uint16_t x = rad;
    uint16_t y = 0;
		uint16_t error2 = 1 - x;
    
    while(x <= y) {
        GRPH_PutPixel( x + x0,  y + y0);
        GRPH_PutPixel( y + x0,  x + y0);
        GRPH_PutPixel(-x + x0,  y + y0);
        GRPH_PutPixel(-y + x0,  x + y0);
        GRPH_PutPixel(-x + x0, -y + y0);
        GRPH_PutPixel(-y + x0, -x + y0);
        GRPH_PutPixel( x + x0, -y + y0);
        GRPH_PutPixel( y + x0, -x + y0);
        y++;
        if(error2 <= 0) {
            error2 += 2 * y + 1;
        } else {
					  x--;
            error2 += 2 * (y - x) + 1;
				}	
    }
}


