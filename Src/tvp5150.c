#include "tvp5150.h"


void TVP_Init()
{
	TVP_Pins_StructTypeDef tpins;
	TVP_IC_StructTypeDef tcfg;
	
	//TVP_Write(TVP_Addr_InputSource, 0);
	TVP_SetInputSource(TVP_CS_AIP1A); //Same sheet
	TVP_SetAnalogChannelControls(TVP_ACC_DISABLED, TVP_ACC_DISABLED);

	//TVP_Write(TVP_Addr_PinsConfig, 0x08);
	TVP_InitPinsConfig(&tpins);
	TVP_SetPinsConfig(&tpins);
	
	//TVP_SetImageConfigA(128,128,128,0);
	TVP_InitImageConfig(&tcfg);
	TVP_SetImageConfig(&tcfg);
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
	uint8_t i2cbuf[2], i2cbuflen = 0;
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
	res->Offset = (TVP_ACC_TypeDef) (res->VAL & 3);
	res->Gain   = (TVP_ACC_TypeDef) ((res->VAL >> 2) & 3);
}


//Important: PowerDown = 1 - power down; 0 - normal
void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO)
{
	TVP_Write(TVP_Addr_OperatingModeControls, (GLCO << 2) + 0x2 + PowerDown);
}

void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res)
{
	res->VAL 	 		 = TVP_Read(TVP_Addr_OperatingModeControls);
	res->PowerDown = (bool) (res->VAL & 1);
	res->GLCO 		 = (bool) ((res->VAL >> 2) & 1);
}


void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->VBKO * 0x80 + res->GPLC * 0x40 + res->GPLC_Mode * 0x20 + res->HVLK * 0x10 
	    + res->YUV * 8 + res->HSYNK * 4 + res->VBLK * 2 + res->SCLK;
	TVP_Write(TVP_Addr_MiscellaneousControls, tmp);
}

void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res)
{
	res->VAL   = TVP_Read(TVP_Addr_MiscellaneousControls);
	res->VBKO  = (bool) ((res->VAL >> 7) & 1);
	res->GPLC  = (bool) ((res->VAL >> 6) & 1);
	res->GPLC_Mode = (bool) ((res->VAL >> 5) & 1);
	res->HVLK  = (bool) ((res->VAL >> 4) & 1);
	res->YUV   = (bool) ((res->VAL >> 3) & 1);
	res->HSYNK = (bool) ((res->VAL >> 2) & 1);
	res->VBLK  = (bool) ((res->VAL >> 1) & 1);
	res->SCLK  = (bool) (res->VAL & 1);
}


void TVP_SetAutoswitchMask(bool paln, bool palm, bool ntsc443)
{
	uint8_t tmp = 0;
	
	tmp = ntsc443 * 8 + paln * 4 + palm * 2;
	TVP_Write(TVP_Addr_AutoswitchMask, tmp);
}

void TVP_GetAutoswitchMask(TVP_ASM_StructTypeDef *res)
{
	res->VAL   = TVP_Read(TVP_Addr_AutoswitchMask);
	res->n443  = (bool) ((res->VAL >> 4) & 1);
	res->paln  = (bool) ((res->VAL >> 3) & 1);
	res->palm  = (bool) ((res->VAL >> 2) & 1);
}


void TVP_SoftwareReset()
{
	TVP_Write(TVP_Addr_SoftwareReset, 1);
}


void TVP_SetColorKillerControl(TVP_CK_TypeDef colorKiller, uint8_t theshold)
{
	uint8_t tmp = 0;
	
	tmp = (((colorKiller << 4) + (theshold & 0x1f)) & 0x7f);
	TVP_Write(TVP_Addr_ColorKillerControl, tmp);
}

void TVP_GetColorKillerControl(TVP_CK_StructTypeDef *res)
{
	res->VAL          = TVP_Read(TVP_Addr_ColorKillerControl);
	res->ColorKiller  = (TVP_CK_TypeDef) ((res->VAL >> 4) & 3);
	res->Theshold     = res->VAL  & 0x1f;
}


void TVP_SetLuminanceControl(TVP_LC_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->BypassMode * 0x80 + res->NoPedetal * 0x40 + res->NoRawHeader * 0x20 + res->VertBlanckBypass * 0x10 
	    + (res->SignalDelay & 0x0f);
	TVP_Write(TVP_Addr_LuminanceControl1, tmp);
	
	tmp = res->Filter * 0x40 + res->PeakingGain * 0x2;
	TVP_Write(TVP_Addr_LuminanceControl2, tmp);
	
	tmp = res->FilterStopBand & 0x03;
	TVP_Write(TVP_Addr_LuminanceControl3, tmp);
}

void TVP_GetLuminanceControl(TVP_LC_StructTypeDef *res)
{
	res->VAL1              = TVP_Read(TVP_Addr_LuminanceControl1);
	res->BypassMode        = (bool) ((res->VAL1 >> 7) & 1);
	res->NoPedetal         = (bool) ((res->VAL1 >> 6) & 1);
	res->NoRawHeader       = (bool) ((res->VAL1 >> 5) & 1);
	res->VertBlanckBypass  = (bool) ((res->VAL1 >> 4) & 1);
	res->SignalDelay       = (TVP_LSD_TypeDef) (res->VAL1 & 0x0f);
	res->VAL2              = TVP_Read(TVP_Addr_LuminanceControl2);
	res->Filter            = (bool) ((res->VAL1 >> 6) & 1);
	res->PeakingGain       = (TVP_LPG_TypeDef) ((res->VAL1 >> 1) & 0x0f);
	res->VAL3              = TVP_Read(TVP_Addr_LuminanceControl3);
	res->FilterStopBand    = (TVP_LFS_TypeDef) (res->VAL1 & 0x03);
}

//OutputAndRates
void TVP_SetOutputAndRates(TVP_OAR_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->YUV_CodeRange * 0x40 + res->UV_CodeFormat * 0x20 
	    + res->YUV_Data * 0x08 + (res->YUV_OutputFormat & 0x07);
	TVP_Write(TVP_Addr_OutputAndRatesSelect, tmp);
}

void TVP_GetOutputAndRates(TVP_OAR_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_OutputAndRatesSelect);
	res->YUV_CodeRange  = (bool) ((res->VAL >> 6) & 1);
	res->UV_CodeFormat  = (bool) ((res->VAL >> 5) & 1);
	res->YUV_Data       = (TVP_YUD_TypeDef) ((res->VAL >> 3) & 3);
	res->YUV_OutputFormat  = (TVP_YOF_TypeDef) (res->VAL  & 7);
}


void TVP_InitImageConfig(TVP_IC_StructTypeDef *cfg)
{
	cfg->Brightness = 128;
	cfg->Contrast   = 128;
	cfg->Saturation = 128;
	cfg->Hue        = 0;
}

void TVP_SetImageConfig(TVP_IC_StructTypeDef *cfg)
{
	TVP_Write(TVP_Addr_BrightnessControl, cfg->Brightness);
	TVP_Write(TVP_Addr_ContrastControl,   cfg->Contrast);
	TVP_Write(TVP_Addr_SaturationControl, cfg->Saturation);
	TVP_Write(TVP_Addr_HueControl,        cfg->Hue);
}

void TVP_SetImageConfigA(uint8_t Brightness, uint8_t Contrast, uint8_t Saturation, int8_t Hue)
{
	TVP_Write(TVP_Addr_BrightnessControl, Brightness);
	TVP_Write(TVP_Addr_ContrastControl,   Contrast);
	TVP_Write(TVP_Addr_SaturationControl, Saturation);
	TVP_Write(TVP_Addr_HueControl,        Hue);
}

void TVP_GetImageConfig(TVP_IC_StructTypeDef *cfg)
{
	cfg->Brightness = TVP_Read(TVP_Addr_BrightnessControl);
	cfg->Contrast   = TVP_Read(TVP_Addr_ContrastControl);
	cfg->Saturation = TVP_Read(TVP_Addr_SaturationControl);
	cfg->Hue        = TVP_Read(TVP_Addr_HueControl);
}


void TVP_InitPinsConfig(TVP_Pins_StructTypeDef *pins)
{
	pins->pin23 = TVP_P23_GLCO;
	pins->pin24 = TVP_P24_VSYNC;
	pins->pin27 = TVP_P27_INTREQ;
	pins->pin9  = TVP_P09_SCLK;
}

void TVP_SetPinsConfig(TVP_Pins_StructTypeDef *pins)
{
	uint8_t tmp;
	
	tmp = ((pins->pin23 & 2)>>1) * 0x40 + ((pins->pin24 & 2)>>1) * 0x20 + ((pins->pin24 & 2)>>1) * 0x10 
	    + (pins->pin23 & 1) * 8 + (pins->pin24 & 1) * 4 + pins->pin27 * 2 + pins->pin9;
	
	TVP_Write(TVP_Addr_PinsConfig, tmp);
}

void TVP_GetPinsConfig(TVP_Pins_StructTypeDef *pins)
{
	uint8_t tmp;
	tmp = TVP_Read(TVP_Addr_PinsConfig);
	pins->VAL = tmp;

	if ((tmp >> 6) & 1)  pins->pin23 = TVP_P23_LOCK;
	else pins->pin23 = (TVP_P23_TypeDef) ((tmp >> 3) & 1);

	if (((tmp >> 4) & 1) || ((tmp >> 5) & 1)) pins->pin24 = TVP_P24_LOCK;
	else pins->pin24 = (TVP_P24_TypeDef) ((tmp >> 2) & 1);

	pins->pin27 = (TVP_P27_TypeDef) ((tmp >> 1) & 1);
	pins->pin9  = (TVP_P09_TypeDef) (tmp & 1);
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

