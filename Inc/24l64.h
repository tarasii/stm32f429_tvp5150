#ifndef __24l64_H
#define __24l64_H

#include <stdint.h>
#include "i2c.h"

//#define EEPROM_WRITE_ADDRESS 0xA2 //A2 = 0; A1 = 0; A0 = 1
//#define EEPROM_WRITE_ADDRESS 0xA4 //A2 = 0; A1 = 1; A0 = 0
//#define EEPROM_WRITE_ADDRESS 0xA8 //A2 = 1; A1 = 0; A0 = 0
#define	  EEPROM_WRITE_ADDRESS 0xA0 //A2 = 0; A1 = 0; A0 = 0
//#define	EEPROM_READ_ADDRESS 0xA3  //A2 = 0; A1 = 0; A0 = 1
//#define	EEPROM_READ_ADDRESS 0xA5  //A2 = 0; A1 = 1; A0 = 0
//#define	EEPROM_READ_ADDRESS 0xA9  //A2 = 1; A1 = 0; A0 = 0
#define	  EEPROM_READ_ADDRESS 0xA1  //A2 = 0; A1 = 0; A0 = 0
	
	
void EEPROM_WriteByte(uint16_t addr, uint8_t data);
uint8_t EEPROM_ReadByte(uint16_t addr);
void EEPROM_WriteWord(uint16_t addr, uint16_t data);
uint16_t EEPROM_ReadWord(uint16_t addr);
void EEPROM_WriteDoubleWord(uint16_t addr, uint32_t data);
uint32_t EEPROM_ReadDoubleWord(uint16_t addr);


//Taras Ivaniv

#endif /*__ 24l64_H */
