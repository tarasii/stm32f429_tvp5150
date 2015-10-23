#include "clinometer.h"

int16_t oldc_x = 0;
int16_t oldc_y = 0;

	
void DrawClinometrLine(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
  int16_t xn = 0;
  int16_t yn = 0;
  int16_t yc = rad;
  int16_t xc = rad;
	
	int16_t bx = ABS(x);	
	int16_t by = -y;	
	
	
  if (bx > 256) bx = 256;
  if (bx < -256) bx = -256;
	
  if (by > 128) by = 128;
  if (by < -128) by = -128;
	
  OnCircleIterationsXY(&xn, &yn, 2*rad/3, xc);	
	
  if (bx > 128) xc = ((256 - bx) * yn)/128;
	else xc = (bx * yn)/128;
//  if (bx < -128) xc = ((-256 - bx) * yn)/128;
//	else xc = (bx * yn)/128;
	
	yc = (by * rad/2) /128;
	
  OnCircleIterationsXY(&xn, &yn, 2*rad/3, xc);	
	
	if (x >= 0 && x >= 128 ) {
//		GRPH_DrawLine(x0 - xn, y0 - yn, x0 + xn, y0 + yn); 
		GRPH_DrawLine(x0 - yn, y0 - xn + yc, x0 + yn, y0 + xn + yc); 
		GRPH_DrawLine(x0     , y0      + yc, x0 - xn, y0 + yn + yc); 
	}
	if (x >= 0 && x < 128)  {
		//GRPH_DrawLine(x0 + yn, y0 + xn, x0 - yn, y0 - xn);
		GRPH_DrawLine(x0 - yn, y0 + xn + yc, x0     , y0      + yc);
		GRPH_DrawLine(x0 + xn, y0 + yn + yc, x0 - xn, y0 - yn + yc);
	}
	if (x < 0 && x < -128)  {
//		GRPH_DrawLine(x0 + xn, y0 - yn, x0 - xn, y0 + yn);
		GRPH_DrawLine(x0 + yn, y0 - xn + yc, x0 - yn, y0 + xn + yc);
		GRPH_DrawLine(x0     , y0      + yc, x0 + xn, y0 + yn + yc);
	}
	if (x < 0 && x >= -128)  {
		//GRPH_DrawLine(x0 - yn, y0 + xn, x0 + yn, y0 - xn);
		GRPH_DrawLine(x0 + yn, y0 + xn + yc, x0     , y0      + yc);
		GRPH_DrawLine(x0 - xn, y0 + yn + yc, x0 + xn, y0 - yn + yc);
	}
}


void DrawClinometer(uint16_t x0, uint16_t y0, uint16_t rad, int16_t x, int16_t y){
	uint16_t rad8 = rad-rad/4, rad6 = rad-rad/6, rad23 = 2*rad/3;
	GRPH_DrawCircle(x0, y0, rad);
	
	//grid
	GRPH_DrawLine(x0-rad6, y0, x0-rad23, y0);
	GRPH_DrawLine(x0+rad23, y0, x0+rad6, y0);

	GRPH_DrawLine(x0-rad6, y0-rad/2, x0-rad23, y0-rad/2);
	GRPH_DrawLine(x0+rad23, y0-rad/2, x0+rad6, y0-rad/2);

	GRPH_DrawLine(x0-rad8, y0-rad/4, x0-rad23, y0-rad/4);
	GRPH_DrawLine(x0+rad23, y0-rad/4, x0+rad8, y0-rad/4);

	GRPH_DrawLine(x0-rad6, y0+rad/2, x0-rad23, y0+rad/2);
	GRPH_DrawLine(x0+rad23, y0+rad/2, x0+rad6, y0+rad/2);

	GRPH_DrawLine(x0-rad8, y0+rad/4, x0-rad23, y0+rad/4);
	GRPH_DrawLine(x0+rad23, y0+rad/4, x0+rad8, y0+rad/4);
	
	//water line
	GRPH_SetForeColor(GRPH_COLOR_BLACK);
	DrawClinometrLine(x0, y0, rad, oldc_x, oldc_y);
	GRPH_SetForeColor(GRPH_COLOR_WHITE);
	if (ABS(x) < 5 ) GRPH_SetForeColor(GRPH_COLOR_GREEN);
	DrawClinometrLine(x0, y0, rad, x, y);
	GRPH_SetForeColor(GRPH_COLOR_WHITE);
	oldc_x = x;
	oldc_y = y;
}

