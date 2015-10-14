#include "compas.h"

int16_t old_x = 0;
int16_t old_y = 0;

void DrawCompasLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
  int16_t xn = rad - 2;
  int16_t yn = 0;
  int16_t yc = 0;
	int16_t en = 1 - xn;	
	int16_t ax = ABS(x);	
	int16_t ay = ABS(y);
  if (ay > ax){
		ay = ABS(x);	
		ax = ABS(y);
	}	
    
	while(xn >= yn) {
			yn++;
			if(en <= 0) {
					en += 2 * yn + 1;
			} else {
					xn--;
					en += 2 * (yn - xn) + 1;
			}	
	}
	
	yc = (ay * yn)/ax;
	
  xn = rad - 2;
  yn = 0;
	while(xn >= yn && yc >= yn) {
			yn++;
			if(en <= 0) {
					en += 2 * yn + 1;
			} else {
					xn--;
					en += 2 * (yn - xn) + 1;
			}	
	}
	
	if (x >= 0 && y >= 0 && x >= y)  GRPH_DrawLine(x0, y0, x0 + xn, y0 - yn);
	if (x >= 0 && y >= 0 && x < y)  GRPH_DrawLine(x0, y0, x0 + yn, y0 - xn);
	if (x < 0 && y >= 0 && ABS(x) >= y)  GRPH_DrawLine(x0, y0, x0 - xn, y0 - yn);
	if (x < 0 && y >= 0 && ABS(x) < y)  GRPH_DrawLine(x0, y0, x0 - yn, y0 - xn);
	if (x >= 0 && y < 0 && x >= ABS(y))  GRPH_DrawLine(x0, y0, x0 + xn, y0 + yn);
	if (x >= 0 && y < 0 && x < ABS(y))  GRPH_DrawLine(x0, y0, x0 + yn, y0 + xn);
	if (x < 0 && y < 0 && ABS(x) >= ABS(y))  GRPH_DrawLine(x0, y0, x0 - xn, y0 + yn);
	if (x < 0 && y < 0 && ABS(x) < ABS(y))  GRPH_DrawLine(x0, y0, x0 - yn, y0 + xn);
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

