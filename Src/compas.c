#include "compas.h"

int16_t old_x = 0;
int16_t old_y = 0;

void DrawCompasLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
  int16_t xn = 0;
  int16_t yn = 0;
  int16_t yc = rad;
 
	int16_t xs = 0;
  int16_t ys = 0;
  int16_t yz = rad;

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
		GRPH_DrawLine(x0, y0, x0 + xn, y0 - yn);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 + ys, y0 + xs);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 + xn, y0 - yn);
		GRPH_DrawLine(x0 + xn, y0 - yn, x0 + ys, y0 + xs);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 - xn, y0 + yn);
		GRPH_DrawLine(x0 - xn, y0 + yn, x0 + ys, y0 + xs);
	}
	if (x >= 0 && y >= 0 && x < y){
		GRPH_DrawLine(x0, y0, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 + xs, y0 + ys);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 + yn, y0 - xn, x0 + xs, y0 + ys);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 - yn, y0 + xn);
		GRPH_DrawLine(x0 - yn, y0 + xn, x0 + xs, y0 + ys);
	}
	if (x < 0 && y >= 0 && ABS(x) >= y){
		GRPH_DrawLine(x0, y0, x0 - xn, y0 - yn);
		GRPH_DrawLine(x0 - ys, y0 + xs, x0 + ys, y0 - xs);
		GRPH_DrawLine(x0 - ys, y0 + xs, x0 - xn, y0 - yn);
		GRPH_DrawLine(x0 - xn, y0 - yn, x0 + ys, y0 - xs);
		GRPH_DrawLine(x0 - ys, y0 + xs, x0 + xn, y0 + yn);
		GRPH_DrawLine(x0 + xn, y0 + yn, x0 + ys, y0 - xs);
	}
	if (x < 0 && y >= 0 && ABS(x) < y){
		GRPH_DrawLine(x0, y0, x0 - yn, y0 - xn);
		GRPH_DrawLine(x0 - xs, y0 + ys, x0 + xs, y0 - ys);
		GRPH_DrawLine(x0 - xs, y0 + ys, x0 - yn, y0 - xn);
		GRPH_DrawLine(x0 - yn, y0 - xn, x0 + xs, y0 - ys);
		GRPH_DrawLine(x0 - xs, y0 + ys, x0 + yn, y0 + xn);
		GRPH_DrawLine(x0 + yn, y0 + xn, x0 + xs, y0 - ys);
	}
	if (x >= 0 && y < 0 && x >= ABS(y)){
		GRPH_DrawLine(x0, y0, x0 + xn, y0 + yn);
		GRPH_DrawLine(x0 + ys, y0 - xs, x0 - ys, y0 + xs);
		GRPH_DrawLine(x0 + ys, y0 - xs, x0 + xn, y0 + yn);
		GRPH_DrawLine(x0 + xn, y0 + yn, x0 - ys, y0 + xs);
		GRPH_DrawLine(x0 + ys, y0 - xs, x0 - xn, y0 - yn);
		GRPH_DrawLine(x0 - xn, y0 - yn, x0 - ys, y0 + xs);
	}
	if (x >= 0 && y < 0 && x < ABS(y)){
		GRPH_DrawLine(x0, y0, x0 + yn, y0 + xn);
		GRPH_DrawLine(x0 + xs, y0 - ys, x0 - xs, y0 + ys);
		GRPH_DrawLine(x0 + xs, y0 - ys, x0 + yn, y0 + xn);
		GRPH_DrawLine(x0 + yn, y0 + xn, x0 - xs, y0 + ys);
		GRPH_DrawLine(x0 + xs, y0 - ys, x0 - yn, y0 - xn);
		GRPH_DrawLine(x0 - yn, y0 - xn, x0 - xs, y0 + ys);
	}
	if (x < 0 && y < 0 && ABS(x) >= ABS(y)){
		GRPH_DrawLine(x0, y0, x0 - xn, y0 + yn);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 + ys, y0 + xs);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 - xn, y0 + yn);
		GRPH_DrawLine(x0 - xn, y0 + yn, x0 + ys, y0 + xs);
		GRPH_DrawLine(x0 - ys, y0 - xs, x0 + xn, y0 - yn);
		GRPH_DrawLine(x0 + xn, y0 - yn, x0 + ys, y0 + xs);
	}
	if (x < 0 && y < 0 && ABS(x) < ABS(y)){
		GRPH_DrawLine(x0, y0, x0 - yn, y0 + xn);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 + xs, y0 + ys);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 - yn, y0 + xn);
		GRPH_DrawLine(x0 - yn, y0 + xn, x0 + xs, y0 + ys);
		GRPH_DrawLine(x0 - xs, y0 - ys, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 + yn, y0 - xn, x0 + xs, y0 + ys);
	}
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

