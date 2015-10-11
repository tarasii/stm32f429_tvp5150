#include "compas.h"

int16_t old_x = 0;
int16_t old_y = 0;

void DrawCompasLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
	if (x >= 0 && y >= 0 && x >= y)  GRPH_DrawLine(x0, y0, x0 + rad - 2, y0);
	if (x >= 0 && y >= 0 && x < y)  GRPH_DrawLine(x0, y0, x0 + 2 * rad/3, y0 - 2 * rad/3);
	if (x < 0 && y >= 0 && ABS(x) >= y)  GRPH_DrawLine(x0, y0, x0 - 2 * rad/3, y0 - 2 * rad/3);
	if (x < 0 && y >= 0 && ABS(x) < y)  GRPH_DrawLine(x0, y0, x0, y0 - rad + 2);
	if (x >= 0 && y < 0 && x >= ABS(y))  GRPH_DrawLine(x0, y0, x0 + 2 * rad/3, y0+ 2 * rad/3);
	if (x >= 0 && y < 0 && x < ABS(y))  GRPH_DrawLine(x0, y0, x0 , y0 + rad - 2);
	if (x < 0 && y < 0 && ABS(x) >= ABS(y))  GRPH_DrawLine(x0, y0, x0 - rad - 2, y0);
	if (x < 0 && y < 0 && ABS(x) < ABS(y))  GRPH_DrawLine(x0, y0, x0 - 2 * rad/3, y0 + 2 * rad/3);
}

void DrawCompas(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
	//GRPH_DrawCircle(22,297,20);
	GRPH_DrawCircle(x0, y0, rad);
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	DrawCompasLine(x0,y0,rad,old_x,old_y);
	GRPH_SetForeColor(GRPH_COLOR_WHITE);
	DrawCompasLine(x0,y0,rad,x,y);
	old_x = x;
	old_y = y;
//	//sm
//	GRPH_DrawLine(x0-4, y0, x0+4, y0);
//	//up
//	GRPH_DrawLine(x0, y0-rad+2, x0-4, y0);
//	GRPH_DrawLine(x0, y0-rad+2, x0+4, y0);
//	//down
//	GRPH_DrawLine(x0, y0+rad-2, x0-4, y0);
//	GRPH_DrawLine(x0, y0+rad-2, x0+4, y0);
//	GRPH_DrawLine(x0, y0+rad-2, x0, y0);
}

