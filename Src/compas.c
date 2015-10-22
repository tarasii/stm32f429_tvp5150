#include "compas.h"

int16_t old_x = 0;
int16_t old_y = 0;

void DrawCompasLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
	int32_t tmpc = GRPH_GetForeColor();
  int16_t xn = 0;
  int16_t yn = 0;
  int16_t yc = rad;
 
	int16_t xs = 0;
  int16_t ys = 0;
  int16_t yz = rad;

	int16_t x1 = 0;
  int16_t y1 = 0;
	int16_t x2 = 0;
  int16_t y2 = 0;
	int16_t x3 = 0;
  int16_t y3 = 0;
	int16_t x4 = 0;
  int16_t y4 = 0;

	int16_t ax = ABS(x);	
	int16_t ay = ABS(y);
  if (ay > ax){
		ay = ABS(x);	
		ax = ABS(y);
	}	
    
  OnCircleIterationsXY(&xn, &yn, rad-2, yc);	
	yc = (ay * yn)/ax;
	OnCircleIterationsXY(&xn, &yn, rad-2, yc);	

  OnCircleIterationsXY(&xs, &ys, rad/5, yz);	
	yz = (ay * ys)/ax;
	OnCircleIterationsXY(&xs, &ys, rad/5, yz);	

	
	if (x >= 0 && y >= 0 && x >= y){
		x1 = x0 - ys;
		y1 = y0 - xs;
		x2 = x0 + ys;
		y2 = y0 + xs;
		x3 = x0 + xn;
		y3 = y0 - yn;
		x4 = x0 - xn;
		y4 = y0 + yn;
	}
	if (x >= 0 && y >= 0 && x < y){
		x1 = x0 - xs;
		y1 = y0 - ys;
		x2 = x0 + xs;
		y2 = y0 + ys;
		x3 = x0 + yn;
		y3 = y0 - xn;
		x4 = x0 - yn;
		y4 = y0 + xn;
	}
	if (x < 0 && y >= 0 && ABS(x) >= y){
		x1 = x0 - ys;
		y1 = y0 + xs;
		x2 = x0 + ys;
		y2 = y0 - xs;
		x3 = x0 - xn;
		y3 = y0 - yn;
		x4 = x0 + xn;
		y4 = y0 + yn;
	}
	if (x < 0 && y >= 0 && ABS(x) < y){
		x1 = x0 - xs;
		y1 = y0 + ys;
		x2 = x0 + xs;
		y2 = y0 - ys;
		x3 = x0 - yn;
		y3 = y0 - xn;
		x4 = x0 + yn;
		y4 = y0 + xn;
	}
	if (x >= 0 && y < 0 && x >= ABS(y)){
		x1 = x0 + ys;
		y1 = y0 - xs;
		x2 = x0 - ys;
		y2 = y0 + xs;
		x3 = x0 + xn;
		y3 = y0 + yn;
		x4 = x0 - xn;
		y4 = y0 - yn;
	}
	if (x >= 0 && y < 0 && x < ABS(y)){
		x1 = x0 + xs;
		y1 = y0 - ys;
		x2 = x0 - xs;
		y2 = y0 + ys;
		x3 = x0 + yn;
		y3 = y0 + xn;
		x4 = x0 - yn;
		y4 = y0 - xn;
	}
	if (x < 0 && y < 0 && ABS(x) >= ABS(y)){
		x1 = x0 - ys;
		y1 = y0 - xs;
		x2 = x0 + ys;
		y2 = y0 + xs;
		x3 = x0 - xn;
		y3 = y0 + yn;
		x4 = x0 + xn;
		y4 = y0 - yn;
	}
	if (x < 0 && y < 0 && ABS(x) < ABS(y)){
		x1 = x0 - xs;
		y1 = y0 - ys;
		x2 = x0 + xs;
		y2 = y0 + ys;
		x3 = x0 - yn;
		y3 = y0 + xn;
		x4 = x0 + yn;
		y4 = y0 - xn;
	}
	if (GRPH_GetForeColor() != GRPH_COLOR_BLACK) GRPH_SetForeColor(GRPH_COLOR_RED);
	GRPH_DrawFilledTriangle(x1, y1, x2, y2, x3, y3);
	if (GRPH_GetForeColor() != GRPH_COLOR_BLACK) GRPH_SetForeColor(GRPH_COLOR_BLUE);
	GRPH_DrawFilledTriangle(x1, y1, x2, y2, x4, y4);
	if (GRPH_GetForeColor() != GRPH_COLOR_BLACK) GRPH_SetForeColor(GRPH_COLOR_WHITE);
	GRPH_DrawLine(x1, y1, x2, y2);
	GRPH_DrawLine(x1, y1, x3, y3);
	GRPH_DrawLine(x2, y2, x3, y3);
	GRPH_DrawLine(x1, y1, x4, y4);
	GRPH_DrawLine(x2, y2, x4, y4);
	GRPH_SetForeColor(tmpc);
}

void DrawCompas(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
	GRPH_DrawCircle(x0, y0, rad);
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	DrawCompasLine(x0,y0,rad,old_x,old_y);
	GRPH_SetForeColor(GRPH_COLOR_WHITE);
	DrawCompasLine(x0,y0,rad,x,y);
	old_x = x;
	old_y = y;
}

