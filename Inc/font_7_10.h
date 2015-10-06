#ifndef TM_FONTS_H
#define TM_FONTS_H 100

#include "stdint.h"
#include "string.h"

typedef struct {
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FONT_typedef;

typedef struct {
	uint16_t Width;       /*!< String width in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} FONT_SIZE_typedef;

extern FONT_typedef Font_7x10;

char* FONT_GetStringSize(char* str, FONT_SIZE_typedef* SizeStruct, FONT_typedef* Font);


 
#endif

