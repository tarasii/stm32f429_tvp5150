#include "graph.h"

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

void GRPH_PutPixelRGB(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t addr;
	uint16_t mx = GRPH_MAX_X;
	uint16_t my = GRPH_MAX_Y;
	
	if(x > mx || y > my) return;
	addr = y * GRPH_MAX_X * 3 + x * 3;
	VideoBuff[addr]     = GRPH_GetY (r, g, b);
	VideoBuff[addr + 1] = GRPH_GetCb(r, g, b);
	VideoBuff[addr + 2] = GRPH_GetCr(r, g, b);
}

void GRPH_PutPixel(uint16_t x, uint16_t y, GRPH_RGB *rgb)
{
	GRPH_PutPixelRGB(x, y, rgb->R, rgb->G, rgb->B);
}

int abs(int x)
{
	int res;
	if(x < 0) res = -x;
	else      res =  x;
	return res;
}

void GRPH_DrawLineRGB(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t r, uint8_t g, uint8_t b)
{
    const uint16_t deltaX = abs(x2 - x1);
    const uint16_t deltaY = abs(y2 - y1);
    const uint16_t signX = x1 < x2 ? 1 : -1;
    const uint16_t signY = y1 < y2 ? 1 : -1;
    
    uint16_t error = deltaX - deltaY;
		uint16_t error2;
    
    GRPH_PutPixelRGB(x2, y2, r, g, b);
    while(x1 != x2 || y1 != y2) {
        GRPH_PutPixelRGB(x1, y1, r, g, b);
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


void GRPH_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, GRPH_RGB *rgb)
{
  GRPH_DrawLineRGB(x1, y1, x2, y2, rgb->R, rgb->G, rgb->B);
}

void GRPH_RectangleRGB(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b) 
{
	GRPH_DrawLineRGB(x1, y1, x2, y1, r, g, b);
	GRPH_DrawLineRGB(x2, y1, x2, y2, r, g, b);
	GRPH_DrawLineRGB(x1, y2, x2, y2, r, g, b);
	GRPH_DrawLineRGB(x1, y1, x1, y2, r, g, b);
}

void GRPH_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, GRPH_RGB *rgb)
{
  GRPH_RectangleRGB(x1, y1, x2, y2, rgb->R, rgb->G, rgb->B);
}

void GRPH_CircleRGB(uint16_t x0, uint16_t y0, uint16_t rad, uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t x = rad;
    uint16_t y = 0;
		uint16_t error2 = 1 - x;
    
    while(x <= y) {
        GRPH_PutPixelRGB( x + x0,  y + y0, r, g, b);
        GRPH_PutPixelRGB( y + x0,  x + y0, r, g, b);
        GRPH_PutPixelRGB(-x + x0,  y + y0, r, g, b);
        GRPH_PutPixelRGB(-y + x0,  x + y0, r, g, b);
        GRPH_PutPixelRGB(-x + x0, -y + y0, r, g, b);
        GRPH_PutPixelRGB(-y + x0, -x + y0, r, g, b);
        GRPH_PutPixelRGB( x + x0, -y + y0, r, g, b);
        GRPH_PutPixelRGB( y + x0, -x + y0, r, g, b);
        y++;
        if(error2 <= 0) {
            error2 += 2 * y + 1;
        } else {
					  x--;
            error2 += 2 * (y - x) + 1;
				}	
    }
}

void GRPH_Circle(uint16_t x1, uint16_t y1, uint16_t rad, GRPH_RGB *rgb)
{
  GRPH_CircleRGB(x1, y1, rad, rgb->R, rgb->G, rgb->B);
}


