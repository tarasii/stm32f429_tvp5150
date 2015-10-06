#include "stdint.h"

#define GPIO_HIGH(a,b) 		a->BSRR = b
#define GPIO_LOW(a,b)			a->BSRR = b << 16
#define GPIO_TOGGLE(a,b) 	a->ODR ^= b

extern uint8_t flagButton;

