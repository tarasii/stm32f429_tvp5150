#include "itg3200.h"

void ITG_Init(ITG_DLPF_TypeDef dlpf, uint8_t semp, ITG_CLK_TypeDef clk)
{
//	ITG_SetDLPF_Config(ITG_DLPF_256_8);
//	ITG_SetSampleRateDivider(7);
	ITG_SetSampleRateDivider(semp);
	ITG_SetDLPF(dlpf);
	ITG_SetPowerManagement(0,0,0,0,0, clk);
}


void ITG_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = addr;
	i2cbuf[1] = data;
	I2C1_WriteBuffer(ITG_WRITE_ADDRESS, i2cbuf, 2);
}

uint8_t ITG_ReadByte(uint8_t addr)
{
	uint8_t i2cbuf[1];
  I2C1_WriteBuffer(ITG_READ_ADDRESS, &addr, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	return i2cbuf[0];
}


uint8_t ITG_GetChipAddr()
{
	uint8_t res;
	res = ITG_ReadByte(ITG_Addr_WHO_AM_I);
	return res << 1;
}

void ITG_SetChipAddr(uint8_t res)
{
	ITG_WriteByte(ITG_Addr_WHO_AM_I, res >> 1);
}

uint8_t ITG_GetSampleRateDivider()
{
	uint8_t res;
	res = ITG_ReadByte(ITG_Addr_SMPLRT_DIV);
	return res;
}

void ITG_SetSampleRateDivider(uint8_t res)
{
	ITG_WriteByte(ITG_Addr_SMPLRT_DIV, res);
}

ITG_DLPF_TypeDef ITG_GetDLPF()
{
	uint8_t res;
	res = ITG_ReadByte(ITG_Addr_DLPF_FS);
	return (ITG_DLPF_TypeDef) (res & 7);
}

void ITG_SetDLPF(ITG_DLPF_TypeDef dlpf)
{
	uint8_t tmp;
	tmp = 0x18 | dlpf;
	ITG_WriteByte(ITG_Addr_DLPF_FS, tmp);
}

void ITG_GetIntConfig(ITG_INT_StructTypeDef *res)
{
	res->VAL     = ITG_ReadByte(ITG_Addr_INT_CFG);
	res->ACTL    = (bool) ((res->VAL >> 7) & 1);
	res->OPEN    = (bool) ((res->VAL >> 6) & 1);
	res->LATCH   = (bool) ((res->VAL >> 5) & 1);
	res->ANY_RD  = (bool) ((res->VAL >> 4) & 1);
	res->ITG_RDY = (bool) ((res->VAL >> 2) & 1);
	res->RAW_RDY = (bool) ( res->VAL       & 1);	
}

void ITG_SetIntConfig(bool actl, bool open, bool latch, bool any_rd, bool itg_rdy, bool raw_rdy)
{
	uint8_t tmp;
	tmp = actl * 0x80 + open * 0x40 + latch * 0x20 + any_rd * 0x10 + itg_rdy * 4 + raw_rdy;
	ITG_WriteByte(ITG_Addr_INT_CFG, tmp);
}

void ITG_GetIntStatus(ITG_INT_StructTypeDef *res)
{
	res->VAL     = ITG_ReadByte(ITG_Addr_INT_CFG);
	res->ITG_RDY = (bool) ((res->VAL >> 2) & 1);
	res->RAW_RDY = (bool) ( res->VAL       & 1);	
}

int16_t ITG_GetTemperature()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ITG_Addr_TEMP_OUT_H;
  I2C1_WriteBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[1] << 8)| i2cbuf[0];
//	res = ITG_ReadByte(ITG_Addr_TEMP_OUT_L);
//	res = res << 8;
//	res = res + ITG_ReadByte(ITG_Addr_TEMP_OUT_H);
	return res;
}

int16_t ITG_ConvTemp(int16_t in){
	int32_t res;
	res = in  / 7;
	return res;
}

int16_t ITG_GetX()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ITG_Addr_GYRO_XOUT_H;
  I2C1_WriteBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = ITG_ReadByte(ITG_Addr_GYRO_XOUT_H);
//	res = res << 8;
//	res = res + ITG_ReadByte(ITG_Addr_GYRO_XOUT_L);
	return res;
}

int16_t ITG_GetY()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ITG_Addr_GYRO_YOUT_H;
  I2C1_WriteBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = ITG_ReadByte(ITG_Addr_GYRO_YOUT_H);
//	res = res << 8;
//	res = res + ITG_ReadByte(ITG_Addr_GYRO_YOUT_L);
	return res;
}

int16_t ITG_GetZ()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ITG_Addr_GYRO_ZOUT_H;
  I2C1_WriteBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = ITG_ReadByte(ITG_Addr_GYRO_ZOUT_H);
//	res = res << 8;
//	res = res + ITG_ReadByte(ITG_Addr_GYRO_ZOUT_L);
	return res;
}

void ITG_GetXYZ(ITG_XYZ_StructTypeDef *res)
{
	uint8_t i2cbuf[6];
	i2cbuf[0] = ITG_Addr_GYRO_XOUT_H;
  I2C1_WriteBuffer(ITG_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ITG_READ_ADDRESS, i2cbuf, 6);

	res->X = (i2cbuf[0] << 8)| i2cbuf[1];
	res->Y = (i2cbuf[2] << 8)| i2cbuf[3];
	res->Z = (i2cbuf[4] << 8)| i2cbuf[5];

//	res->X = ITG_GetX();
//	res->Y = ITG_GetY();
//	res->Z = ITG_GetZ();

}

void ITG_GetPowerManagement(ITG_PM_StructTypeDef *res)
{
	res->VAL   = ITG_ReadByte(ITG_Addr_PWR_MGM);
	res->Reset = (bool) ((res->VAL >> 7) & 1);
	res->Sleep = (bool) ((res->VAL >> 6) & 1);
	res->StbyX = (bool) ((res->VAL >> 5) & 1);
	res->StbyY = (bool) ((res->VAL >> 4) & 1);
	res->StbyZ = (bool) ((res->VAL >> 3) & 1);
	res->CLK   = (ITG_CLK_TypeDef) (res->VAL & 7);	
}

void ITG_SetPowerManagement(bool reset, bool sleep, bool stby_x, bool stby_y, bool stby_z, ITG_CLK_TypeDef clk)
{
	uint8_t tmp;
	tmp = reset * 0x80 + sleep * 0x40 + stby_x * 0x20 + stby_y * 0x10 + stby_z * 4 + (clk & 7);
	ITG_WriteByte(ITG_Addr_PWR_MGM, tmp);
}

void ITG_Reset()
{
	ITG_SetPowerManagement(1,0,0,0,0,ITG_CLK_Internal);
}

void ITG_Sleep()
{
	ITG_SetPowerManagement(0,1,0,0,0,ITG_CLK_Internal);
}

