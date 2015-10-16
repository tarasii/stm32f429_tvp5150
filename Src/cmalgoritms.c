#include "cmalgoritms.h"

void OnCircleIterationsXY(int16_t *xn, int16_t *yn, uint16_t rad, uint16_t yc){
  *xn = rad - 2;
  *yn = 0;
	int16_t en = 1 - *xn;
	
	while(*xn >= *yn && yc > *yn) {
			*yn = *yn + 1;
			if(en <= 0) {
					en += 2 * *yn + 1;			
			} else {
					*xn = *xn - 1;
					en += 2 * (*yn - *xn) + 1;
			}	
	}
}

