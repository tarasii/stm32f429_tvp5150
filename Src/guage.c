#include "guage.h"

void DrawGuage(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t oldx, uint32_t color){
	int16_t ax;
	uint32_t tmp = GRPH_GetForeColor();

	GRPH_DrawRect(x0 - 2, y0 - rad, x0 + 2, y0 + rad);

	ax = oldx;
	if (ax > 255) ax = 255;
	if (ax < -255) ax = -255;
	ax = ax * (rad-1) / 256;
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	GRPH_DrawLine(x0    , y0, x0    , y0 - ax);
	GRPH_DrawLine(x0 + 1, y0, x0 + 1, y0 - ax);
	GRPH_DrawLine(x0 - 1, y0, x0 - 1, y0 - ax);

	ax = x;
	if (ax > 255) ax = 255;
	if (ax < -255) ax = -255;
	ax = ax * (rad-1) / 256;
	GRPH_SetForeColor(color);
	GRPH_DrawLine(x0    , y0, x0    , y0 - ax);
	GRPH_DrawLine(x0 + 1, y0, x0 + 1, y0 - ax);
	GRPH_DrawLine(x0 - 1, y0, x0 - 1, y0 - ax);
	GRPH_SetForeColor(tmp);
	//
}

void DrawGuageAbsolut(uint16_t x0, uint16_t y0, uint16_t rad, uint16_t x, uint16_t oldx, uint32_t color){
	int16_t ax;
	uint32_t tmp = GRPH_GetForeColor();
	
	GRPH_DrawRect(x0 - 2, y0 - rad, x0 + 2, y0 + rad);
	
	ax = oldx;
	if (ax > 255) ax = 255;
	ax = ax * (2 * rad - 1)/ 256;
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	GRPH_DrawLine(x0    , y0 + rad - 1, x0    , y0 + rad - 1 - ax);
	GRPH_DrawLine(x0 + 1, y0 + rad - 1, x0 + 1, y0 + rad - 1 - ax);
	GRPH_DrawLine(x0 - 1, y0 + rad - 1, x0 - 1, y0 + rad - 1 - ax);
	//
	ax = x;
	if (ax > 255) ax = 255;
	ax = ax * (2 * rad - 1) / 256;
	GRPH_SetForeColor(color);
	GRPH_DrawLine(x0    , y0 + rad - 1, x0    , y0 + rad - 1 - ax);
	GRPH_DrawLine(x0 + 1, y0 + rad - 1, x0 + 1, y0 + rad - 1 - ax);
	GRPH_DrawLine(x0 - 1, y0 + rad - 1, x0 - 1, y0 + rad - 1 - ax);
	GRPH_SetForeColor(tmp);
}

