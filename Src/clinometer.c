#include "compas.h"

int16_t oldc_x = 0;
int16_t oldc_y = 0;

void DrawClinometrLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
  int16_t xn = rad - 2;
  int16_t yn = 0;
  int16_t yc = 0;
	int16_t en = 1 - xn;
	
	int16_t ax = ABS(x);	
  if (ax > 270) ax = 270;
		
	while(xn >= yn) {
			yn++;
			if(en <= 0) {
					en += 2 * yn + 1;
			} else {
					xn--;
					en += 2 * (yn - xn) + 1;
			}	
	}
	
	yc = (ax * yn)/265;
	
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
	
	if (x >= 0 && x >= 132 ) {
		GRPH_DrawLine(x0 + yn, y0 + xn, x0 - yn, y0 - xn); 
		GRPH_DrawLine(x0 - xn, y0 + yn, x0 + xn, y0 - yn); 
	}
	if (x >= 0 && x < 132 )  {
		GRPH_DrawLine(x0 + yn, y0 + xn, x0 - yn, y0 - xn);
		GRPH_DrawLine(x0 - xn, y0 + yn, x0 + xn, y0 - yn);
	}
	if (x < 0 && x < -132)  {
		GRPH_DrawLine(x0 - yn, y0 + xn, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 + xn, y0 + yn, x0 - xn, y0 - yn);
	}
	if (x < 0 && x >= -132)  {
		GRPH_DrawLine(x0 - yn, y0 + xn, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 + xn, y0 + yn, x0 - xn, y0 - yn);
	}
}


void DrawClinometer(uint16_t x0, uint16_t y0, uint16_t rad, uint16_t x, uint16_t y){
	GRPH_DrawCircle(x0, y0, rad);
	//water line
	GRPH_DrawLine(x0-rad+1, y0, x0-rad/2, y0);
	GRPH_DrawLine(x0+rad/2, y0, x0+rad-1, y0);
	GRPH_DrawLine(x0+rad/2, y0, x0, y0+rad/2);
	GRPH_DrawLine(x0-rad/2, y0, x0, y0+rad/2);
	//cross
//	GRPH_DrawLine(x0, y0+rad-3, x0, y0-rad+3);
//	GRPH_DrawLine(x0+rad-3, y0, x0-rad+3, y0);
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	DrawClinometrLine(x0,y0,rad,oldc_x,oldc_y);
	GRPH_SetForeColor(GRPH_COLOR_WHITE);
	DrawClinometrLine(x0,y0,rad,x,y);
	oldc_x = x;
	oldc_y = y;
}

