#include "tvp5150.h"

void TVP_Init()
{
	TVP_SetInputSource(TVP_CS_AIP1A);
	TVP_SetAnalogChannelControls(TVP_ACC_DISABLED, TVP_ACC_DISABLED);
}

void TVP_SetInputSource(TVP_CS_TypeDef ChanelSource)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = TVP_Addr_InputSource;
	i2cbuf[1] = ChanelSource;
	I2C1_WriteBuffer(TVP_WRITE_ADDRESS, i2cbuf, 2);
}

TVP_CS_TypeDef TVP_GetInputSource()
{
	uint8_t i2cbuf[2], i2cbuflen;
	I2C1_ReadBuffer(TVP_WRITE_ADDRESS, TVP_Addr_InputSource, i2cbuf, i2cbuflen);
	return (TVP_CS_TypeDef) i2cbuf[0];
}

void TVP_SetAnalogChannelControls(TVP_ACC_TypeDef OffsetControl, TVP_ACC_TypeDef GainControl)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = TVP_Addr_AnalogChannelControls;
	i2cbuf[1] = 0x10 + (OffsetControl << 2) + GainControl;
	I2C1_WriteBuffer(TVP_WRITE_ADDRESS, i2cbuf, 2);
}

void TVP_GetAnalogChannelControls(TVP_ACC_StructTypeDef *res)
{
	uint8_t i2cbuf[2], i2cbuflen;
	I2C1_ReadBuffer(TVP_WRITE_ADDRESS, TVP_Addr_AnalogChannelControls, i2cbuf, i2cbuflen);
	res->Offset = (TVP_ACC_TypeDef) (i2cbuf[0] | 3);
	res->Gain = (TVP_ACC_TypeDef) ((i2cbuf[0] >>2) | 3);
	res->VAL = i2cbuf[0];
}

//Important: PowerDown = 1 - power down; 0 - normal
void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = TVP_Addr_OperatingModeControls;
	i2cbuf[1] = (GLCO << 2) + 0x2 + PowerDown;
	I2C1_WriteBuffer(TVP_WRITE_ADDRESS, i2cbuf, 2);
}

void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res)
{
	uint8_t i2cbuf[2], i2cbuflen;
	I2C1_ReadBuffer(TVP_WRITE_ADDRESS, TVP_Addr_OperatingModeControls, i2cbuf, i2cbuflen);
	res->PowerDown = (bool) (i2cbuf[0] | 1);
	res->GLCO = (bool) ((i2cbuf[0] >> 2) | 1);
	res->VAL = i2cbuf[0];
}

void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = TVP_Addr_MiscellaneousControls;
	i2cbuf[1] = res->VBKO * 0x80 + res->GPLC * 0x40 + res->GPLC_Mode * 0x20 + res->HVLK * 0x10 
	          + res->YUV * 8 + res->HSYNK * 4 + res->VBLK * 2 + res->SCLK;
	res->VAL = i2cbuf[1];
	I2C1_WriteBuffer(TVP_WRITE_ADDRESS, i2cbuf, 2);
}

void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	uint8_t i2cbuf[2], i2cbuflen;
	I2C1_ReadBuffer(TVP_WRITE_ADDRESS, TVP_Addr_MiscellaneousControls, i2cbuf, i2cbuflen);
	res->VBKO =  (bool) ((i2cbuf[0] >> 7) | 1);
	res->GPLC =  (bool) ((i2cbuf[0] >> 6) | 1);
	res->GPLC_Mode = (bool) ((i2cbuf[0] >> 5) | 1);
	res->HVLK =  (bool) ((i2cbuf[0] >> 4) | 1);
	res->YUV =   (bool) ((i2cbuf[0] >> 3) | 1);
	res->HSYNK = (bool) ((i2cbuf[0] >> 2) | 1);
	res->VBLK =  (bool) ((i2cbuf[0] >> 1) | 1);
	res->SCLK =  (bool) (i2cbuf[0] | 1);
	res->VAL = i2cbuf[0];
}


