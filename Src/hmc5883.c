#include "hmc5883.h"

DEV_Result_t HMC_Init(HMC_MR_TypeDef mode, HMC_DR_TypeDef rate, HMC_MM_TypeDef moder, HMC_GS_TypeDef gain)
{
	//HMC_Set_Configurarion(HMC_DR_15, HMC_MR_SMM, HMC_GS_1_9);
	if (HMC_TestConnection()) return DEV_Result_Error;
	HMC_Set_Configurarion(rate, moder, gain);
	HMC_Set_MODE(mode);
	return DEV_Result_Ok;
}


void HMC_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = addr;
	i2cbuf[1] = data;
	I2C1_WriteBuffer(HMC_WRITE_ADDRESS, i2cbuf, 2);
}

uint8_t HMC_ReadByte(uint8_t addr)
{
	uint8_t i2cbuf[1];
  I2C1_WriteBuffer(HMC_READ_ADDRESS, &addr, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	return i2cbuf[0];
}


void HMC_Get_Configuration(HMC_CF_StructTypeDef *res)
{
	res->VAL1 = HMC_ReadByte(HMC_Addr_ConfA);
	res->RATE = (HMC_DR_TypeDef) ((res->VAL1 >> 2) & 7);
	res->MODE = (HMC_MM_TypeDef)  (res->VAL1       & 3);
	res->VAL2 = HMC_ReadByte(HMC_Addr_ConfA);
	res->GAIN = (HMC_GS_TypeDef) ((res->VAL2 >> 5) & 7);
}

void HMC_Set_Configurarion(HMC_DR_TypeDef rate, HMC_MM_TypeDef mode, HMC_GS_TypeDef gain)
{
	uint8_t tmp = 0;
	tmp = (rate & 7) * 4 + (mode & 3);
	HMC_WriteByte(HMC_Addr_ConfA, tmp);
	tmp = 0;
	tmp = (gain & 7) * 0x20;
	HMC_WriteByte(HMC_Addr_ConfB, tmp);
}

HMC_MR_TypeDef HMC_Get_Mode()
{
	uint8_t res;
	res = HMC_ReadByte(HMC_Addr_Mode);
	return (HMC_MR_TypeDef) (res & 3);
}

void HMC_Set_MODE(HMC_MR_TypeDef mode)
{
	uint8_t tmp = 0;
	tmp = mode & 3;
	HMC_WriteByte(HMC_Addr_Mode, tmp);
}

int16_t HMC_GetX()
{
	int16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = HMC_Addr_X_MSB;
  I2C1_WriteBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = HMC_ReadByte(HMC_Addr_X_MSB);
//	res = res << 8;
//	res = res + HMC_ReadByte(HMC_Addr_X_LSB);
	return res;
}

int16_t HMC_GetY()
{
	int16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = HMC_Addr_Y_MSB;
  I2C1_WriteBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = HMC_ReadByte(HMC_Addr_Y_MSB);
//	res = res << 8;
//	res = res + HMC_ReadByte(HMC_Addr_Y_LSB);
	return res;
}

int16_t HMC_GetZ()
{
	int16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = HMC_Addr_Z_MSB;
  I2C1_WriteBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[0] << 8)| i2cbuf[1];
//	res = HMC_ReadByte(HMC_Addr_Z_MSB);
//	res = res << 8;
//	res = res + HMC_ReadByte(HMC_Addr_Z_LSB);
	return res;
}

void HMC_GetXYZ(XYZ_t *res)
{
	uint8_t i2cbuf[6];
	i2cbuf[0] = HMC_Addr_X_MSB;
  I2C1_WriteBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 6);

	res->X = (i2cbuf[0] << 8)| i2cbuf[1];
	res->Z = (i2cbuf[2] << 8)| i2cbuf[3];
	res->Y = (i2cbuf[4] << 8)| i2cbuf[5];

//	res->X = HMC_GetX();
//	res->Y = HMC_GetY();
//	res->Z = HMC_GetZ();
}

void HMC_GetStatus(HMC_SR_StructTypeDef *res)
{
	res->VAL  = HMC_ReadByte(HMC_Addr_Status);
	res->REN  = (bool) ((res->VAL >> 2) & 1);
	res->LOCK = (bool) ((res->VAL >> 1) & 1);
	res->RDY  = (bool)  (res->VAL       & 1);
}

void HMC_GetId(HMC_ID_StructTypeDef *res)
{
	uint8_t i2cbuf[3];
	i2cbuf[0] = HMC_Addr_IdentA;
  I2C1_WriteBuffer(HMC_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(HMC_READ_ADDRESS, i2cbuf, 3);

	res->VALA = i2cbuf[0];
	res->VALB = i2cbuf[1];
	res->VALC = i2cbuf[2];
	
//	res->VALA  = HMC_ReadByte(HMC_Addr_IdentA);
//	res->VALB  = HMC_ReadByte(HMC_Addr_IdentB);
//	res->VALC  = HMC_ReadByte(HMC_Addr_IdentC);
}

DEV_Result_t HMC_TestConnection()
{
	HMC_ID_StructTypeDef res;
	HMC_GetId(&res);
	if (res.VALA == 'H' && res.VALB == '4' && res.VALC == '3' ) return DEV_Result_Ok;
	return DEV_Result_Error;
}


