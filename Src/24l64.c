#include "24l64.h"

void EEPROM_WriteByte(uint16_t addr, uint8_t data)
{
	uint8_t i2cbuf[3];
	i2cbuf[0] = (addr >> 8) & 0xff;
	i2cbuf[1] = addr & 0xff;
	i2cbuf[2] = data;
	I2C1_WriteBuffer(EEPROM_WRITE_ADDRESS, i2cbuf, 3);
}


uint8_t EEPROM_ReadByte(uint16_t addr)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = (addr >> 8) & 0xff;
	i2cbuf[1] = addr & 0xff;
  I2C1_WriteBuffer(EEPROM_READ_ADDRESS, i2cbuf, 2);
	i2cbuf[0] = 0;
	i2cbuf[1] = 0;
	I2C1_ReadBuffer(EEPROM_READ_ADDRESS, i2cbuf, 1);
	return i2cbuf[0];
}

void EEPROM_WriteWord(uint16_t addr, uint16_t data)
{
	uint8_t i2cbuf[4];
	i2cbuf[0] = (addr >> 8) & 0xff;
	i2cbuf[1] = addr & 0xff;
	i2cbuf[2] = (data >> 8) & 0xff;
	i2cbuf[3] = data & 0xff;
	I2C1_WriteBuffer(EEPROM_WRITE_ADDRESS, i2cbuf, 4);
}

uint16_t EEPROM_ReadWord(uint16_t addr)
{
	uint8_t i2cbuf[4];
	i2cbuf[0] = (addr >> 8) & 0xff;
	i2cbuf[1] = addr & 0xff;
  I2C1_WriteBuffer(EEPROM_READ_ADDRESS, i2cbuf, 2);
	i2cbuf[0] = 0;
	i2cbuf[1] = 0;
	i2cbuf[2] = 0;
	i2cbuf[3] = 0;
	I2C1_ReadBuffer(EEPROM_READ_ADDRESS, i2cbuf, 2);
	return i2cbuf[0] * 0xff + i2cbuf[1];
}

void EEPROM_WriteDoubleWord(uint16_t addr, uint32_t data)
{
	uint8_t i2cbuf[6];
	i2cbuf[0] = (addr >> 24) & 0xff;
	i2cbuf[1] = addr & 0xff;
	i2cbuf[2] = (data >> 16) & 0xff;
	i2cbuf[3] = data & 0xff;
	i2cbuf[4] = (data >> 8) & 0xff;
	i2cbuf[5] = data & 0xff;
	I2C1_WriteBuffer(EEPROM_WRITE_ADDRESS, i2cbuf, 6);
}

uint32_t EEPROM_ReadDoubleWord(uint16_t addr)
{
	uint8_t i2cbuf[4];
	i2cbuf[0] = (addr >> 8) & 0xff;
	i2cbuf[1] = addr & 0xff;
  I2C1_WriteBuffer(EEPROM_READ_ADDRESS, i2cbuf, 2);
	i2cbuf[0] = 0;
	i2cbuf[1] = 0;
	i2cbuf[2] = 0;
	i2cbuf[3] = 0;
	I2C1_ReadBuffer(EEPROM_READ_ADDRESS, i2cbuf, 4);
	return i2cbuf[0] * 0xffffff + i2cbuf[1] * 0xffff + i2cbuf[2] * 0xff + i2cbuf[3];
}


