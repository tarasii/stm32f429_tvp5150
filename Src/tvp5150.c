#include "tvp5150.h"


void TVP_Init()
{
	//TVP_Write(TVP_Addr_InputSource, 0);
	TVP_SetInputSource(TVP_CS_AIP1A); //Same sheet
	TVP_SetAnalogChannelControls(TVP_ACC_DISABLED, TVP_ACC_DISABLED);
}


void TVP_Write(uint8_t addr, uint8_t data)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = addr;
	i2cbuf[1] = data;
	I2C1_WriteBuffer(TVP_WRITE_ADDRESS, i2cbuf, 2);
}

uint8_t TVP_Read(uint8_t addr)
{
	uint8_t i2cbuf[2], i2cbuflen;
	I2C1_ReadBuffer(TVP_READ_ADDRESS, addr, i2cbuf, i2cbuflen);
	return i2cbuf[0];
}


void TVP_SetInputSource(TVP_CS_TypeDef ChanelSource)
{
	TVP_Write(TVP_Addr_InputSource, ChanelSource);
}

TVP_CS_TypeDef TVP_GetInputSource()
{
	return (TVP_CS_TypeDef) TVP_Read(TVP_Addr_InputSource);
}


void TVP_SetAnalogChannelControls(TVP_ACC_TypeDef OffsetControl, TVP_ACC_TypeDef GainControl)
{
	TVP_Write(TVP_Addr_AnalogChannelControls, 0x10 + (OffsetControl << 2) + GainControl);
}

void TVP_GetAnalogChannelControls(TVP_ACC_StructTypeDef *res)
{
	res->VAL    = TVP_Read(TVP_Addr_AnalogChannelControls);
	res->Offset = (TVP_ACC_TypeDef) (res->VAL | 3);
	res->Gain   = (TVP_ACC_TypeDef) ((res->VAL >> 2) | 3);
}


//Important: PowerDown = 1 - power down; 0 - normal
void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO)
{
	TVP_Write(TVP_Addr_OperatingModeControls, (GLCO << 2) + 0x2 + PowerDown);
}

void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res)
{
	res->VAL 	 		 = TVP_Read(TVP_Addr_OperatingModeControls);
	res->PowerDown = (bool) (res->VAL | 1);
	res->GLCO 		 = (bool) ((res->VAL >> 2) | 1);
}


void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	uint8_t tmp;
	
	tmp = res->VBKO * 0x80 + res->GPLC * 0x40 + res->GPLC_Mode * 0x20 + res->HVLK * 0x10 
	          + res->YUV * 8 + res->HSYNK * 4 + res->VBLK * 2 + res->SCLK;
	TVP_Write(TVP_Addr_MiscellaneousControls, tmp);
}

void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	res->VAL   = TVP_Read(TVP_Addr_MiscellaneousControls);
	res->VBKO  = (bool) ((res->VAL >> 7) | 1);
	res->GPLC  = (bool) ((res->VAL >> 6) | 1);
	res->GPLC_Mode = (bool) ((res->VAL >> 5) | 1);
	res->HVLK  = (bool) ((res->VAL >> 4) | 1);
	res->YUV   = (bool) ((res->VAL >> 3) | 1);
	res->HSYNK = (bool) ((res->VAL >> 2) | 1);
	res->VBLK  = (bool) ((res->VAL >> 1) | 1);
	res->SCLK  = (bool) (res->VAL | 1);
}


void TVP_SetVideoStandart(TVP_VS_TypeDef VideoStandart)
{
	TVP_Write(TVP_Addr_VideoStandart, VideoStandart);
}

TVP_VS_TypeDef TVP_GetVideoStandart()
{
	return (TVP_VS_TypeDef) TVP_Read(TVP_Addr_VideoStandart);
}


void TVP_GetInfo(TVP_Info_StructTypeDef *res)
{
	res->DeviceId   = (TVP_Read(TVP_Addr_DeviceMSB) << 8) + TVP_Read(TVP_Addr_DeviceLSB);
	res->RAM  =  TVP_Read(TVP_Addr_RAMVersion);
	res->ROM  =  TVP_Read(TVP_Addr_ROMVersion);
	res->VerticalLineCount  = (TVP_Read(TVP_Addr_VerticalLineCountMSB) << 8) + TVP_Read(TVP_Addr_VerticalLineCountLSB);
}

void TVP_GetStatus(TVP_Status_StructTypeDef *res)
{
	res->r1  =  TVP_Read(TVP_Addr_StatusRegister1);
	res->r2  =  TVP_Read(TVP_Addr_StatusRegister2);
	res->AGC  =  TVP_Read(TVP_Addr_StatusRegister3);
	res->SCH  =  TVP_Read(TVP_Addr_StatusRegister4);
	res->r5  =  TVP_Read(TVP_Addr_StatusRegister5);
	res->int_r1  =  TVP_Read(TVP_Addr_InterruptActiveRegisterB);
	res->int_r2  =  TVP_Read(TVP_Addr_InterruptStatusRegisterB);
}

