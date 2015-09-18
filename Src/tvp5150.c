#include "tvp5150.h"


void TVP_Init()
{
	TVP_Pins_StructTypeDef tpins;
	TVP_IC_StructTypeDef tcfg;
	TVP_OAR_StructTypeDef tvidfrmt;
	
	//TVP_Write(TVP_Addr_InputSource, 0);
	TVP_SetInputSource(TVP_CS_AIP1A); //Same sheet
	TVP_SetAnalogChannelControls(TVP_ACC_DISABLED, TVP_ACC_DISABLED);

	//TVP_Write(TVP_Addr_PinsConfig, 0x08);
	TVP_InitPinsConfig(&tpins);
	TVP_SetPinsConfig(&tpins);
	
	//TVP_SetImageConfigA(128,128,128,0);
	TVP_InitImageConfig(&tcfg);
	TVP_SetImageConfig(&tcfg);
	
	TVP_GetOutputAndRates(&tvidfrmt);
	tvidfrmt.YUV_OutputFormat = TVP_YOF_ITU; //YUV422
	TVP_SetOutputAndRates(&tvidfrmt);
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
	uint8_t tmp = 0;
	
	tmp = (GLCO * 4) + PowerDown;
	TVP_Write(TVP_Addr_OperatingModeControls, tmp);
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
	res->VAL  = TVP_Read(TVP_Addr_AutoswitchMask);
	res->n443 = (bool) ((res->VAL >> 4) & 1);
	res->paln = (bool) ((res->VAL >> 3) & 1);
	res->palm = (bool) ((res->VAL >> 2) & 1);
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
	res->VAL         = TVP_Read(TVP_Addr_ColorKillerControl);
	res->ColorKiller = (TVP_CK_TypeDef) ((res->VAL >> 4) & 3);
	res->Theshold    = res->VAL  & 0x1f;
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
	res->VAL1             = TVP_Read(TVP_Addr_LuminanceControl1);
	res->BypassMode       = (bool) ((res->VAL1 >> 7) & 1);
	res->NoPedetal        = (bool) ((res->VAL1 >> 6) & 1);
	res->NoRawHeader      = (bool) ((res->VAL1 >> 5) & 1);
	res->VertBlanckBypass = (bool) ((res->VAL1 >> 4) & 1);
	res->SignalDelay      = (TVP_LSD_TypeDef) (res->VAL1 & 0x0f);
	res->VAL2             = TVP_Read(TVP_Addr_LuminanceControl2);
	res->Filter           = (bool) ((res->VAL1 >> 6) & 1);
	res->PeakingGain      = (TVP_LPG_TypeDef) ((res->VAL1 >> 1) & 0x0f);
	res->VAL3             = TVP_Read(TVP_Addr_LuminanceControl3);
	res->FilterStopBand   = (TVP_LFS_TypeDef) (res->VAL1 & 0x03);
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
	res->VAL              = TVP_Read(TVP_Addr_OutputAndRatesSelect);
	res->YUV_CodeRange    = (bool) ((res->VAL >> 6) & 1);
	res->UV_CodeFormat    = (bool) ((res->VAL >> 5) & 1);
	res->YUV_Data         = (TVP_YUD_TypeDef) ((res->VAL >> 3) & 3);
	res->YUV_OutputFormat = (TVP_YOF_TypeDef) (res->VAL  & 7);
}

//ActiveVideoCroping
void TVP_SetActiveVideoCroping(TVP_AVC_StructTypeDef *res)
{
	uint8_t tmp = 0;
	int16_t tst;
	
	tst = res->Start;
	if (tst<0) tst = (-513 - tst);
	tmp = (res->AVID * 4) + (tst & 3);
	TVP_Write(TVP_Addr_ActiveVideoCropingStartLSB, tmp);
	
	tmp = (tst >> 6) & 0x07f + ((tst & 0x8000)>> 8);
	TVP_Write(TVP_Addr_ActiveVideoCropingStartMSB, tmp);
	
	tst = res->Stop;
	if (tst<0) tst = (-513 - tst);
	tmp = tst & 0x03;
	TVP_Write(TVP_Addr_ActiveVideoCropingStopLSB, tmp);
	
	tmp = (tst >> 6) & 0x07f + ((tst & 0x8000) >> 8);
	TVP_Write(TVP_Addr_ActiveVideoCropingStopMSB, tmp);
}

void TVP_GetActiveVideoCroping(TVP_AVC_StructTypeDef *res)
{
	res->VAL1  = TVP_Read(TVP_Addr_ActiveVideoCropingStartLSB);
	res->VAL2  = TVP_Read(TVP_Addr_ActiveVideoCropingStartMSB);
	res->AVID  = (bool) ((res->VAL1 >> 2) & 1);
	res->Start = res->VAL2;
	res->Start = (((res->Start & 0x07f) << 2) + (res->VAL1 & 3) | ((res->Start & 0x80) << 8));
	res->VAL1  = TVP_Read(TVP_Addr_ActiveVideoCropingStopLSB);
	res->VAL2  = TVP_Read(TVP_Addr_ActiveVideoCropingStopMSB);
	res->Stop  = res->VAL2;
	res->Stop  = (((res->Stop & 0x07f) << 2) + (res->VAL1 & 3)) | ((res->Stop & 0x80) << 8) ;
}

//Genlock
void TVP_SetGenlock(bool CDTO_LSB, bool GLCO_RTC)
{
	uint8_t tmp = 0;
	
	tmp = (CDTO_LSB << 2) + GLCO_RTC;
	TVP_Write(TVP_Addr_Genlock, tmp);
}

void TVP_GetGenlock(TVP_SG_StructTypeDef *res)
{
	res->VAL      = TVP_Read(TVP_Addr_Genlock);
	res->CDTO_LSB = (bool) ((res->VAL >> 4) & 1);
	res->GLCO_RTC = (bool) res->VAL & 0x01;
}

//Horizontal Sync (HSYNC) Start
void TVP_SetHorizontalSyncStart(uint8_t HSYNC)
{
	TVP_Write(TVP_Addr_HorisontalSynkStart, HSYNC);
}

uint8_t TVP_GetHorizontalSyncStart()
{
	uint8_t res;
	res = TVP_Read(TVP_Addr_HorisontalSynkStart);
	return res;
}

//VerticalBlanking
void TVP_SetVerticalBlanking(TVP_VB_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->start ;
	TVP_Write(TVP_Addr_VerticalBlankingStart, tmp);
	
	tmp = res->stop;
	TVP_Write(TVP_Addr_VerticalBlankingStop, tmp);
	
}

void TVP_GetVerticalBlanking(TVP_VB_StructTypeDef *res)
{
	res->start = TVP_Read(TVP_Addr_VerticalBlankingStart);
	res->stop  = TVP_Read(TVP_Addr_VerticalBlankingStop);
}

//Chrominance Control
void TVP_SetChrominanceControl(TVP_CC_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = (res->ColorPLL_Reset << 4) + (res->CE << 3) + (res->CE << 2) + res->ACGC;
	TVP_Write(TVP_Addr_CrominanceControl1, tmp);
	
	tmp = (res->CombFilterMode << 4) + (res->WCF << 2) + res->FilterSelect;
	TVP_Write(TVP_Addr_CrominanceControl2, tmp);
	
}

void TVP_GetChrominanceControl(TVP_CC_StructTypeDef *res)
{
	res->VAL1           = TVP_Read(TVP_Addr_CrominanceControl1);
	res->ColorPLL_Reset = (bool) ((res->VAL1 >> 4) & 1);
	res->ACE            = (bool) ((res->VAL1 >> 3) & 1);
	res->CE             = (bool) ((res->VAL1 >> 2) & 1);
	res->ACGC           = (TVP_ACGC_TypeDef) (res->VAL1 & 0x03);
	
	res->VAL2           = TVP_Read(TVP_Addr_CrominanceControl2);
	res->CombFilterMode = (TVP_CCFM_TypeDef) ((res->VAL2 >> 4) & 0x0F);
	res->WCF            = (bool) ((res->VAL2 >> 2) & 1);
	res->FilterSelect   = (TVP_LFS_TypeDef) (res->VAL2 & 0x03);
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
	pins->pin9  = (TVP_P09_TypeDef)  (tmp & 1);
}


void TVP_SetVideoStandart(TVP_VS_TypeDef VideoStandart)
{
	TVP_Write(TVP_Addr_VideoStandart, VideoStandart);
}

TVP_VS_TypeDef TVP_GetVideoStandart()
{
	return (TVP_VS_TypeDef) TVP_Read(TVP_Addr_VideoStandart);
}

//Interrupt
void TVP_SetInterruptB_Reset(TVP_INTB_StructTypeDef *res)
{
	uint8_t tmp;
	tmp = res->SoftwareInit * 0x80 + res->MacrovisionDetect * 0x40 + res->CommandReady * 0x20 + res->FieldRate * 0x10 
	    + res->LineAlternation * 8 + res->ColorLock * 4 + res->HV_Lock * 2 + res->TV_VCR;
	TVP_Write(TVP_Addr_InterruptB_Reset, tmp);
}

void TVP_GetInterruptB_Reset(TVP_INTB_StructTypeDef *res)
{
	res->VAL                = TVP_Read(TVP_Addr_InterruptB_Reset);
	res->SoftwareInit       = (bool) ((res->VAL >> 7) & 1);
	res->MacrovisionDetect  = (bool) ((res->VAL >> 6) & 1);
	res->CommandReady       = (bool) ((res->VAL >> 5) & 1);
	res->FieldRate          = (bool) ((res->VAL >> 4) & 1);
	res->LineAlternation    = (bool) ((res->VAL >> 3) & 1);
	res->ColorLock          = (bool) ((res->VAL >> 2) & 1);
	res->HV_Lock            = (bool) ((res->VAL >> 1) & 1);
	res->TV_VCR             = (bool)  (res->VAL & 1);
}

void TVP_SetInterruptB_Enable(TVP_INTB_StructTypeDef *res)
{
	uint8_t tmp;
	tmp = res->SoftwareInit * 0x80 + res->MacrovisionDetect * 0x40 + res->CommandReady * 0x20 + res->FieldRate * 0x10 
	    + res->LineAlternation * 8 + res->ColorLock * 4 + res->HV_Lock * 2 + res->TV_VCR;
	TVP_Write(TVP_Addr_InterruptB_Enable, tmp);
}

void TVP_GetInterruptB_Enable(TVP_INTB_StructTypeDef *res)
{
	res->VAL                = TVP_Read(TVP_Addr_InterruptB_Enable);
	res->SoftwareInit       = (bool) ((res->VAL >> 7) & 1);
	res->MacrovisionDetect  = (bool) ((res->VAL >> 6) & 1);
	res->CommandReady       = (bool) ((res->VAL >> 5) & 1);
	res->FieldRate          = (bool) ((res->VAL >> 4) & 1);
	res->LineAlternation    = (bool) ((res->VAL >> 3) & 1);
	res->ColorLock          = (bool) ((res->VAL >> 2) & 1);
	res->HV_Lock            = (bool) ((res->VAL >> 1) & 1);
	res->TV_VCR             = (bool)  (res->VAL & 1);
}

//Interrupt B is: 0 (default) - active low; 1 = active high
void TVP_SetInterruptB_Polarity(bool res)
{
	TVP_Write(TVP_Addr_InterruptB_Config, res & 1);
}

bool TVP_GetInterruptB_Polarity()
{
	return (bool) (TVP_Read(TVP_Addr_InterruptB_Config) & 1);
}

void TVP_GetInterruptB_Status(TVP_INTB_StructTypeDef *res)
{
	res->VAL                = TVP_Read(TVP_Addr_InterruptB_Status);
	res->SoftwareInit       = (bool) ((res->VAL >> 7) & 1);
	res->MacrovisionDetect  = (bool) ((res->VAL >> 6) & 1);
	res->CommandReady       = (bool) ((res->VAL >> 5) & 1);
	res->FieldRate          = (bool) ((res->VAL >> 4) & 1);
	res->LineAlternation    = (bool) ((res->VAL >> 3) & 1);
	res->ColorLock          = (bool) ((res->VAL >> 2) & 1);
	res->HV_Lock            = (bool) ((res->VAL >> 1) & 1);
	res->TV_VCR             = (bool)  (res->VAL & 1);
}

bool TVP_GetInterruptB_Active()
{
	return (bool) (TVP_Read(TVP_Addr_InterruptB_Active) & 1);
}


void TVP_GetInfo(TVP_Info_StructTypeDef *res)
{
	res->DeviceId   = TVP_Read(TVP_Addr_DeviceMSB);
	res->DeviceId   = (res->DeviceId << 8) + TVP_Read(TVP_Addr_DeviceLSB);
	res->RAM        =  TVP_Read(TVP_Addr_RAMVersion);
	res->ROM        =  TVP_Read(TVP_Addr_ROMVersion);
	res->VerticalLineCount  = TVP_Read(TVP_Addr_VerticalLineCountMSB);
	res->VerticalLineCount  = (res->VerticalLineCount << 8) + TVP_Read(TVP_Addr_VerticalLineCountLSB);
}

void TVP_GetStatus(TVP_Status_StructTypeDef *res)
{
	res->VAL1          =  TVP_Read(TVP_Addr_StatusRegister1);
	res->PeakWhiteDetect     = (bool) ((res->VAL1 >> 7) & 1);
	res->LineAlternating     = (bool) ((res->VAL1 >> 6) & 1);
	res->FieldRate           = (bool) ((res->VAL1 >> 5) & 1);
	res->LostLock            = (bool) ((res->VAL1 >> 4) & 1);
	res->ColorSubcarrierLock = (bool) ((res->VAL1 >> 3) & 1);
	res->VerticalSyncLock    = (bool) ((res->VAL1 >> 2) & 1);
	res->HorizontalSyncLock  = (bool) ((res->VAL1 >> 1) & 1);
	res->TV_VCR              = (bool) (res->VAL1 & 1);
	res->VAL2          =  TVP_Read(TVP_Addr_StatusRegister2);
	res->WeakSignalDetection = (bool) ((res->VAL2 >> 6) & 1);
	res->PAL_SwitchPolarity  = (bool) ((res->VAL2 >> 5) & 1);
	res->FieldSequence       = (bool) ((res->VAL2 >> 4) & 1);
	res->AGC_AndOffsetFrozen = (bool) ((res->VAL2 >> 3) & 1);
	res->MacrovisionDetection = (TVP_MD_TypeDef) (res->VAL2 & 3);
	res->AGC           =  TVP_Read(TVP_Addr_StatusRegister3);
	res->SCH           =  TVP_Read(TVP_Addr_StatusRegister4);
	res->VAL3          =  TVP_Read(TVP_Addr_StatusRegister5);
	res->PeakWhiteDetect     = (bool) ((res->VAL3 >> 7) & 1);
	res->VideoStandard       = (TVP_VS_TypeDef) ((res->VAL3  & 0x0F) + 1);
	res->SamplingRate        = (bool) (res->VAL3 & 1);
}

void TVP_SetFullFieldEnabled(bool res)
{
	TVP_Write(TVP_Addr_FullFieldEnable, res & 1);
}

bool TVP_GetFullFieldEnabled()
{
	return (bool) (TVP_Read(TVP_Addr_FullFieldEnable) & 1);
}


uint8_t TVP_GetFIFO_WordCount()
{
	uint8_t res;
	res = TVP_Read(TVP_Addr_FIFO_WordCount);
	return res;
}

void TVP_SetFIFO_InterruptThreshold(uint8_t res)
{
	TVP_Write(TVP_Addr_FIFO_InterruptThreshold, res);
}

uint8_t TVP_GetFIFO_InterruptThreshold()
{
	uint8_t res;
	res = TVP_Read(TVP_Addr_FIFO_InterruptThreshold);
	return res;
}

void TVP_FIFO_Reset(uint8_t res)
{
	TVP_Write(TVP_Addr_FIFO_InterruptThreshold, res);
}

void TVP_SetFIFO_OutputControl(bool res)
{
	TVP_Write(TVP_Addr_FIFO_OutputControl, res & 1);
}

bool TVP_GetFIFO_OutputControl()
{
	return (bool) (TVP_Read(TVP_Addr_FIFO_OutputControl) & 1);
}

//Automatic Initialization
void TVP_SetAutomaticInit(bool auto_init, bool auto_clock)
{
	uint8_t tmp = 0;
	
	tmp = (auto_init * 4) +  (auto_clock * 2);
	TVP_Write(TVP_Addr_AutomaticInitialization, tmp);
}

void TVP_GetAutomaticInit(TVP_AI_StructTypeDef *res)
{
	res->VAL 	 		 = TVP_Read(TVP_Addr_AutomaticInitialization);
	res->AutoInit  = (bool) ((res->VAL >> 2) & 1);
	res->AutoClock = (bool) ((res->VAL >> 1) & 1);
}

//Pixel Alignment
void TVP_SetPixelAlignment(uint16_t addr)
{
	uint8_t tmp = 0;
	
	tmp = addr & 0xFF ;
	TVP_Write(TVP_Addr_PixelAlignmentLSB, tmp);
	
	tmp = (addr >> 8) & 3;
	TVP_Write(TVP_Addr_PixelAlignmentMSB, tmp);
	
}

uint16_t TVP_GetPixelAlignment()
{
	uint16_t res = 0;
	res =       TVP_Read(TVP_Addr_PixelAlignmentMSB) * 0x0FF;
	res = res + TVP_Read(TVP_Addr_PixelAlignmentLSB);
  return res;
}

//Line Number Interrupt
void TVP_SetLineNumberInterrupt(bool field1, bool field2, uint8_t line_num)
{
	uint8_t tmp = 0;
	
	tmp = (field1 * 0x80) +  (field2 * 0x40) + line_num & 0x3F;
	TVP_Write(TVP_Addr_LineNumberInterrupt, tmp);
}

void TVP_GetLineNumberInterrupt(TVP_LNI_StructTypeDef *res)
{
	res->VAL 	 		  = TVP_Read(TVP_Addr_LineNumberInterrupt);
	res->Field1     = (bool) ((res->VAL >> 7) & 1);
	res->Field2 		= (bool) ((res->VAL >> 6) & 1);
	res->LineNumber =          res->VAL  & 0x3F;
}

//VDP Status
void TVP_SetVDPStatus(TVP_VDP_StructTypeDef *res)
{
	uint8_t tmp = 0;
	tmp = res->FIFO_FullError * 0x80 + res->FIFO_Empty * 0x40 + res->Teletext * 0x20 + res->CC_Field1 * 0x10 
	    + res->CC_Field2 * 8 + res->WSS * 4 + res->WPS * 2 + res->VITC;
	TVP_Write(TVP_Addr_VDP_Status, tmp);
}

void TVP_GetVDPStatus(TVP_VDP_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_VDP_Status);
	res->FIFO_FullError = (bool) ((res->VAL >> 7) & 1);
	res->FIFO_Empty     = (bool) ((res->VAL >> 6) & 1);
	res->Teletext       = (bool) ((res->VAL >> 5) & 1);
	res->CC_Field1      = (bool) ((res->VAL >> 4) & 1);
	res->CC_Field2      = (bool) ((res->VAL >> 3) & 1);
	res->WSS            = (bool) ((res->VAL >> 2) & 1);
	res->WSS            = (bool) ((res->VAL >> 1) & 1);
	res->VITC           = (bool)  (res->VAL & 1);
}

void TVP_SetVDP_Conf(uint16_t addr, uint8_t data)
{
	uint8_t tmp = 0;
	tmp =  addr & 0xFF;
	TVP_Write(TVP_Addr_VDP_Conf_RAM_AddressLSB, tmp);
	tmp = (addr >> 8) & 0x1;
	TVP_Write(TVP_Addr_VDP_Conf_RAM_AddressMSB, tmp);
	TVP_Write(TVP_Addr_VDP_Conf_RAM_Data, data);
}

uint8_t TVP_GetVDP_Conf(uint16_t addr)
{
	uint8_t tmp = 0, res;
	tmp =  addr & 0xFF;
	TVP_Write(TVP_Addr_VDP_Conf_RAM_AddressLSB, tmp);
	tmp = (addr >> 8) & 0x1;
	TVP_Write(TVP_Addr_VDP_Conf_RAM_AddressMSB, tmp);
	res = TVP_Read(TVP_Addr_VDP_Conf_RAM_Data);
	return res;
}

//Interrupt Configuration Register A
void TVP_SetInterruptA_Config(TVP_INTA_Conf_StructTypeDef *res)
{
	uint8_t tmp = 0;
	tmp = res->YUV * 4 + res->InterruptA * 2 + res->Polaryty;
	TVP_Write(TVP_Addr_InterruptA_Config, tmp);
}

void TVP_GetInterruptA_Config(TVP_INTA_Conf_StructTypeDef *res)
{
	res->VAL         = TVP_Read(TVP_Addr_InterruptA_Config);
	res->YUV         = (bool) ((res->VAL >> 2) & 1);
	res->InterruptA  = (bool) ((res->VAL >> 1) & 1);
	res->Polaryty    = (bool) (res->VAL & 1);
}

void TVP_SetInterruptA_Enable(TVP_INTA_StructTypeDef *res)
{
	uint8_t tmp;
	tmp = res->Lock * 0x40 + res->CycleComplete * 0x20 + res->BusError * 0x10 
	    + res->FIFO_Threshold * 4 + res->Line * 2 + res->Data;
	TVP_Write(TVP_Addr_InterruptA_Enable, tmp);
}

void TVP_GetInterruptA_Enable(TVP_INTA_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_InterruptA_Enable);
	res->Lock           = (bool) ((res->VAL >> 6) & 1);
	res->CycleComplete  = (bool) ((res->VAL >> 5) & 1);
	res->BusError       = (bool) ((res->VAL >> 4) & 1);
	res->FIFO_Threshold = (bool) ((res->VAL >> 2) & 1);
	res->Line           = (bool) ((res->VAL >> 1) & 1);
	res->Data           = (bool)  (res->VAL & 1);
}

void TVP_SetInterruptA_Status(TVP_INTA_StructTypeDef *res)
{
	uint8_t tmp;
	tmp = res->LockState * 0x80 + res->Lock * 0x40 + res->CycleComplete * 0x20 + res->BusError * 0x10 
	    + res->FIFO_Threshold * 4 + res->Line * 2 + res->Data;
	TVP_Write(TVP_Addr_InterruptA_Enable, tmp);
}

void TVP_GetInterruptA_Status(TVP_INTA_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_InterruptA_Enable);
	res->LockState      = (bool) ((res->VAL >> 7) & 1);
	res->Lock           = (bool) ((res->VAL >> 6) & 1);
	res->CycleComplete  = (bool) ((res->VAL >> 5) & 1);
	res->BusError       = (bool) ((res->VAL >> 4) & 1);
	res->FIFO_Threshold = (bool) ((res->VAL >> 2) & 1);
	res->Line           = (bool) ((res->VAL >> 1) & 1);
	res->Data           = (bool)  (res->VAL & 1);
}

void TVP_SetLineMode(uint8_t line_num, TVP_LFM_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->NullFiltering * 0x80 + res->SendVBI * 0x40 + res->ErrorVBI * 0x20 + res->ErroCorrection * 0x10 
	    + (res->Mode & 0x0f);
	TVP_Write(TVP_Addr_LineModeStart + line_num, tmp);
	
}

void TVP_GetLineMode(uint8_t line_num, TVP_LFM_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_LineModeStart + line_num);
	res->NullFiltering  = (bool) ((res->VAL >> 7) & 1);
	res->SendVBI        = (bool) ((res->VAL >> 6) & 1);
	res->ErrorVBI       = (bool) ((res->VAL >> 5) & 1);
	res->ErroCorrection = (bool) ((res->VAL >> 4) & 1);
	res->Mode           = (TVP_LFM_TypeDef) (res->VAL & 0x0f);
}

void TVP_SetFieldMode(TVP_LFM_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->NullFiltering * 0x80 + res->SendVBI * 0x40 + res->ErrorVBI * 0x20 + res->ErroCorrection * 0x10 
	    + (res->Mode & 0x0f);
	TVP_Write(TVP_Addr_FullFieldMode, tmp);
	
}

void TVP_GetFieldMode(TVP_LFM_StructTypeDef *res)
{
	res->VAL            = TVP_Read(TVP_Addr_FullFieldMode);
	res->NullFiltering  = (bool) ((res->VAL >> 7) & 1);
	res->SendVBI        = (bool) ((res->VAL >> 6) & 1);
	res->ErrorVBI       = (bool) ((res->VAL >> 5) & 1);
	res->ErroCorrection = (bool) ((res->VAL >> 4) & 1);
	res->Mode           = (TVP_LFM_TypeDef) (res->VAL & 0x0f);
}

uint8_t TVP_GetWSS_Data(uint8_t num)
{
	uint8_t res;
	if (num > 5) return 0;
	res            = TVP_Read(TVP_Addr_WSS_Data1 + num);
	return res;
}

uint8_t TVP_GetVPS_Data(uint8_t num)
{
	uint8_t res;
	if (num > 11) return 0;
	res            = TVP_Read(TVP_Addr_VPS_Data01 + num);
	return res;
}

uint8_t TVP_GetVITC_Data(uint8_t num)
{
	uint8_t res;
	if (num > 9) return 0;
	res            = TVP_Read(TVP_Addr_VITC_Data01 + num);
	return res;
}

uint8_t TVP_GetClosedCapture_Data(uint8_t num)
{
	uint8_t res;
	if (num > 3) return 0;
	res            = TVP_Read(TVP_Addr_ClosedCaptionData1 + num);
	return res;
}

uint8_t TVP_GetVBI_FIFO_Data()
{
	uint8_t res;
	res            = TVP_Read(TVP_Addr_VBI_FIFO);
	return res;
}

void TVP_SetTeletextFilter(uint8_t num, uint8_t res)
{
	if (num > 9) return;
	
	TVP_Write(TVP_Addr_LineModeStart + num, res);
	
}

uint8_t TVP_GetTeletextFilter(uint8_t num)
{
	uint8_t res;
	if (num > 9) return 0;
	res            = TVP_Read(TVP_Addr_LineModeStart + num);
	return res;
}

void TVP_SetTeletextFilterControl(TVP_TTC_StructTypeDef *res)
{
	uint8_t tmp = 0;
	
	tmp = res->FilterLogic * 8 + res->Mode * 4 + res->TeletextFilter2 * 2 + res->TeletextFilter1;
	TVP_Write(TVP_Addr_TeletextFilterControl, tmp);
	
}

void TVP_GetTeletextFilterControl(TVP_TTC_StructTypeDef *res)
{
	res->VAL             = TVP_Read(TVP_Addr_TeletextFilterControl);
	res->FilterLogic     = (TVP_TTC_TypeDef) ((res->VAL >> 3) & 3);
	res->Mode            = (bool) ((res->VAL >> 2) & 1);
	res->TeletextFilter2 = (bool) ((res->VAL >> 1) & 1);
	res->TeletextFilter1 = (bool)  (res->VAL & 1);
}

