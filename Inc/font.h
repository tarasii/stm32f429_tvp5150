#include <stdint.h>                           /* Include standard types */
#include "graph.h"

#define CHAR_WIDTH(c)        (font->FontTable[(c) - font->FirstChar].width)
#define CHAR_START_INDEX(c)  (font->FontTable[(c) - font->FirstChar].start)
#define CHAR_SPACE           (font->FontSpace)

//
typedef struct FontTable {
	uint16_t width; // 
	uint16_t start; // 
} FONT_CHAR_INFO;

//
typedef struct
{
    uint8_t Height;		               // 
    uint8_t FirstChar;	             // 
    uint8_t LastChar;		             // 
    uint8_t FontSpace;               // 
    const FONT_CHAR_INFO *FontTable; // 
    const uint8_t *FontBitmaps;      // 
} FONT_INFO;

//Project installed fonts
extern const FONT_INFO tahoma24ptFontInfo;

uint8_t LCD_PutCharRGB(uint16_t x, uint16_t y, uint8_t c);
void LCD_PutStrig(uint16_t x, uint16_t y, const char *str);

