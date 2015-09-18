#include "font.h"

const FONT_INFO *font = 0;      //


uint8_t LCD_PutCharRGB(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t c)
{
    if(!font) return 0;
    if(c < font->FirstChar || c > font->LastChar) return 0;
    // info
    uint8_t width = CHAR_WIDTH(c);
    uint8_t height = font->Height;

		uint8_t i, j;
                
    for(i = 0; i < width; ++i)
		{
          for(j = 0; j < height; ++j)
					{
                 if( (CHAR_START_INDEX(c) + i) ) GRPH_PutPixelRGB( x+i,  y+j, r, g, b);
						     else GRPH_PutPixelRGB( x+i,  y+j, 0, 0, 0);
          }                        
    }
		return width;
}

void LCD_PutStrigRGB(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, const char *str)
{   
   uint8_t CharWidth = 0;
   
   if(!font || !str) return;
  
   while(*str!=0)
   {
      if(CharWidth !=0)
	    {
		    x += CHAR_SPACE;
	    }   
      CharWidth = LCD_PutCharRGB(x, y, r, g, b, *str);
      x += CharWidth;
      str++;	  
   }	
}











