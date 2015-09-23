#ifndef __graph_H
#define __graph_H

#include <stdint.h>
#include "dma2d.h"

#define GRPH_MAX_X 640
#define GRPH_MAX_Y 480

typedef struct
{
	uint8_t Y;   //
	uint8_t Cb;  //
	uint8_t Cr;  //
}GRPH_YCbCr;   //   structure

typedef struct
{
	uint8_t R;  //
	uint8_t G;  //
	uint8_t B;  //
}GRPH_RGB;   // RGB color structure

void GRPH_SetForeColor(uint8_t r, uint8_t g, uint8_t b);
void GRPH_SetBackColor(uint8_t r, uint8_t g, uint8_t b);

void GRPH_PutPixel(uint16_t x, uint16_t y);
void GRPH_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void GRPH_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void GRPH_Circle(uint16_t x1, uint16_t y1, uint16_t rad);

//Taras Ivaniv

#endif /*__ svga050_H */
