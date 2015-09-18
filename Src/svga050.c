#include "svga050.h"

void SVGA_Init()
{
  SVGA_SetInputVideoType(SVGA_SM_YCbCr_444_24, SVGA_SSM_EmbeddedSync0, SVGA_NonInterlaced);
	SVGA_SetDisplayOff(0,0,0);
  SVGA_SetVcomLevel(0x80);
	//test field
	SVGA_SetTestPattern(SVGA_TP_Chess, 20, 20, SVGA_TPC_Black, SVGA_TPC_White);
}


void SVGA_Write(uint8_t addr, uint8_t data)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = addr;
	i2cbuf[1] = data;
	I2C1_WriteBuffer(SVGA_WRITE_ADDRESS, i2cbuf, 2);
}

uint8_t SVGA_Read(uint8_t addr)
{
	uint8_t i2cbuf[2], i2cbuflen = 0;
	I2C1_ReadBuffer(SVGA_READ_ADDRESS, addr, i2cbuf, i2cbuflen);
	return i2cbuf[0];
}


uint8_t SVGA_GetChipRev()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_RevisionInformation);
	return res;
}

void SVGA_GetInputVideoTypeSet(SVGA_SCM_StructTypeDef *res)
{
	res->VAL = SVGA_Read(SVGA_Addr_InputVideoTypeSet);
	res->SignalMode = (SVGA_SM_TypeDef)  ((res->VAL >> 4) & 7);
	res->SyncSignal = (SVGA_SSM_TypeDef) ((res->VAL >> 2) & 3);
	res->ScanMode   = (SVGA_SCM_TypeDef)  (res->VAL & 3);
}

void SVGA_SetInputVideoType(SVGA_SM_TypeDef signal_mode, SVGA_SSM_TypeDef sync_signal, SVGA_SCM_TypeDef scan_mode)
{
	uint8_t tmp;
	tmp = signal_mode * 0x10 + sync_signal * 4 + scan_mode;
	SVGA_Write(SVGA_Addr_InputVideoTypeSet, tmp);
}

void SVGA_GetSyncSignalPolarity(SVGA_SP_StructTypeDef *res)
{
	res->VAL = SVGA_Read(SVGA_Addr_SyncSignalPolaritySet);
	res->Enable_3D          = (bool) ((res->VAL >> 5) & 1);
	res->Refresh_3D         = (bool) ((res->VAL >> 2) & 1);
	res->VericalPolarity    = (bool) ((res->VAL >> 1) & 1);
	res->HorisontalPolarity = (bool)  (res->VAL & 1);
}

void SVGA_SetSyncSignalPolarity(bool enable_3d, bool refresh_3d, bool v_pol, bool h_pol)
{
	uint8_t tmp;
	tmp = enable_3d * 0x10 + refresh_3d * 4 + v_pol * 2 + h_pol;
	SVGA_Write(SVGA_Addr_SyncSignalPolaritySet, tmp);
}

uint8_t SVGA_GetVerticalBlankLines()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_VerticalBlankLines);
	return res;
}

void SVGA_SetVerticalBlankLines(uint8_t v_blank)
{
	SVGA_Write(SVGA_Addr_SyncSignalPolaritySet, v_blank);
}

uint8_t SVGA_GetHorizontalBlankPixels()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_HorizontalBlankPixels);
	return res;
}

void SVGA_SetHorizontalBlankPixels(uint8_t h_blank)
{
	SVGA_Write(SVGA_Addr_HorizontalBlankPixels, h_blank);
}

SVGA_SVP_TypeDef SVGA_GetStartActiveVideoPosition()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_AdjustStartActiveVideoPosition);
	return (SVGA_SVP_TypeDef) res;
}

void SVGA_SetStartActiveVideoPosition(SVGA_SVP_TypeDef v_offset)
{
	SVGA_Write(SVGA_Addr_AdjustStartActiveVideoPosition, v_offset);
}

SVGA_SLP_TypeDef SVGA_GetFieldStartLinePosition()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_FieldStartLinePosition);
	return (SVGA_SLP_TypeDef) res;
}

void SVGA_SetFieldStartLinePosition(SVGA_SLP_TypeDef h_offset)
{
	SVGA_Write(SVGA_Addr_FieldStartLinePosition, h_offset);
}

//Down Scaling
void SVGA_GetDownScaling(SVGA_DS_StructTypeDef *res)
{
	res->VAL = SVGA_Read(SVGA_Addr_DownScaling);
	res->V_Scale = (bool) ((res->VAL >> 2) & 1);
	res->H_Scale = (SVGA_SD_TypeDef) (res->VAL & 3);
}

void SVGA_SetDownScaling(bool v_scale, SVGA_SD_TypeDef h_scale)
{
	uint8_t tmp;
	tmp = v_scale * 4 + h_scale;
	SVGA_Write(SVGA_Addr_DownScaling, tmp);
}

uint8_t SVGA_GetBrightness()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_BrightnessControl);
	return res;
}

void SVGA_SetBrightness(uint8_t val)
{
	SVGA_Write(SVGA_Addr_BrightnessControl, val);
}

uint8_t SVGA_GetContrast()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_ContrastControl);
	return res;
}

void SVGA_SetContrast(uint8_t val)
{
	SVGA_Write(SVGA_Addr_ContrastControl, val);
}

void SVGA_SetImageConfig(uint8_t brightness, uint8_t contrast)
{
	SVGA_Write(SVGA_Addr_BrightnessControl, brightness);
	SVGA_Write(SVGA_Addr_ContrastControl, contrast);
}

void SVGA_GetPowerDown(SVGA_PD_StructTypeDef *res)
{
	res->VAL = SVGA_Read(SVGA_Addr_PowerDownModeControl);
	res->PDOWN   = (bool) ((res->VAL >> 7) & 1);
	res->BSGENPD = (bool) ((res->VAL >> 4) & 1);
	res->RDACPD  = (bool) ((res->VAL >> 3) & 1);
	res->RAMPPD  = (bool) ((res->VAL >> 2) & 1);
	res->VCOMPD  = (bool) ((res->VAL >> 1) & 1);
	res->TSENPD  = (bool)  (res->VAL & 3);
}

void SVGA_SetPowerDown(bool PDOWN, bool BSGENPD, bool RDACPD, bool RAMPPD, bool VCOMPD, bool TSENPD)
{
	uint8_t tmp;
	tmp = PDOWN * 0x80 + BSGENPD * 0x10 + RDACPD * 8 + RAMPPD * 4 + VCOMPD * 2 + TSENPD;
	SVGA_Write(SVGA_Addr_PowerDownModeControl, tmp);
}

void SVGA_GetDisplayOff(SVGA_DO_StructTypeDef *res)
{
	res->VAL = SVGA_Read(SVGA_Addr_DisplayOff);
	res->DispOff = (bool) ((res->VAL >> 2) & 1);
	res->VSCAN   = (bool) ((res->VAL >> 1) & 1);
	res->HSCAN   = (bool)  (res->VAL & 3);
}

void SVGA_SetDisplayOff(bool DispOff, bool VSCAN, bool HSCAN)
{
	uint8_t tmp;
	tmp = DispOff * 4 + VSCAN * 2 + HSCAN;
	SVGA_Write(SVGA_Addr_DisplayOff, tmp);
}

uint8_t SVGA_GetLeftMargin()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DisplayLeftMargin);
	return res;
}

void SVGA_SetLeftMargin(uint8_t val)
{
	SVGA_Write(SVGA_Addr_DisplayLeftMargin, val);
}

uint8_t SVGA_GetRightMargin()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DisplayRightMargin);
	return res;
}

void SVGA_SetRightMargin(uint8_t val)
{
	SVGA_Write(SVGA_Addr_DisplayRightMargin, val);
}

uint8_t SVGA_GetTopMargin()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DisplayTopMargin);
	return res;
}

void SVGA_SetTopMargin(uint8_t val)
{
	SVGA_Write(SVGA_Addr_DisplayTopMargin, val);
}

uint8_t SVGA_GetBottomMargin()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DisplayBottomMargin);
	return res;
}

void SVGA_SetBottomMargin(uint8_t val)
{
	SVGA_Write(SVGA_Addr_DisplayBottomMargin, val);
}

void SVGA_SetMargin(uint8_t left, uint8_t right, uint8_t top, uint8_t bottom)
{
	SVGA_Write(SVGA_Addr_DisplayLeftMargin, left);
	SVGA_Write(SVGA_Addr_DisplayRightMargin, right);
	SVGA_Write(SVGA_Addr_DisplayTopMargin, top);
	SVGA_Write(SVGA_Addr_DisplayBottomMargin, bottom);
}

uint8_t SVGA_Get_DA_OffsetSetting()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DA_OffsetSetting);
	return res;
}

void SVGA_Set_DA_OffsetSetting(uint8_t val)
{
	SVGA_Write(SVGA_Addr_DA_OffsetSetting, val);
}

SVGA_DCS_TypeDef SVGA_GetDischargeCurrent()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DischargeCurrentSetting);
	return (SVGA_DCS_TypeDef) res;
}

void SVGA_SetDischargeCurrent(SVGA_DCS_TypeDef val)
{
	SVGA_Write(SVGA_Addr_DischargeCurrentSetting, val);
}

bool SVGA_GetDischargeEnabled()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_DischargeEnabledControl);
	return (bool) (res & 1);
}

void SVGA_SetDischargeEnabled(bool val)
{
	SVGA_Write(SVGA_Addr_DischargeEnabledControl, val);
}

uint8_t SVGA_GetVcomLevel()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_VcomLevelSetting);
	return res;
}

void SVGA_SetVcomLevel(uint8_t val)
{
	SVGA_Write(SVGA_Addr_VcomLevelSetting, val);
}

uint8_t SVGA_GetTemperatureSensor()
{
	uint8_t res;
	res = SVGA_Read(SVGA_Addr_TemperatureSensorReadout);
	return res;
}

float SVGA_CalculateTemperature(uint8_t raw_temp)
{
	float res;
	res = 0.47 * raw_temp  - 40;
	return res;
}

void SVGA_SetTemperatureLuminanceCompensation()
{
	uint8_t val;
	uint8_t res;
	int8_t delta[120] = {-86, -85, -84, -83, -82, -81, -80, -79, -78, -77,
	                     -76, -75, -74, -72, -71, -70, -69, -68, -66, -65,
	                     -64, -62, -61, -60, -58, -57, -56, -54, -53, -51,
                     	 -50, -49, -47, -46, -44, -43, -41, -40, -38, -37,
	                     -35, -34, -32, -31, -29, -28, -26, -25, -23, -22,
	                     -20, -19, -17, -16, -14, -13, -11, -10, - 8, - 7,
	                     - 5, - 4, - 2, - 1,   1,   2,   3,   5,   6,   8,
	                       9,  11,  12,  13,  15,  16,  17,  19,  20,  21, 
		                    23,  24,  25,  26,  28,  29,  30,  31,  32,  34,
	                      35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
	                      45,  46,  47,  47,  48,  49,  50,  50,  51,  52,
	                      52,  53,  54,  55,  55,  56,  56,  56,  57,  57};
	val = SVGA_GetTemperatureSensor() / 2;
  res = SVGA_Default_VCOM_Level + delta[val];
  if (res < 0x20) return;
	SVGA_SetVcomLevel(res);
}

uint16_t SVGA_GetGammaCorrection(uint8_t num)
{
	uint16_t res;
	if (num > 16) return 0;
	res = SVGA_Read(SVGA_Addr_GammaCorrectionLUT0_MSB + num * 2);
	res = res << 8;
	res = res + SVGA_Read(SVGA_Addr_GammaCorrectionLUT0_LSB + num * 2);
	return res;
}

void SVGA_SetGammaCorrection(uint8_t num, uint16_t val)
{
	uint8_t tmp;
	if (num > 16) return;
	tmp = val & 0x0f;
	SVGA_Write(SVGA_Addr_GammaCorrectionLUT0_LSB + num * 2, tmp);
	tmp = (val >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_GammaCorrectionLUT0_MSB + num * 2, tmp);
}

uint16_t SVGA_GetRedSignalOffset()
{
	uint16_t res;
	res = SVGA_Read(SVGA_Addr_RedSignalOffset_MSB);
	res = res << 8;
	res = res + SVGA_Read(SVGA_Addr_RedSignalOffset_LSB);
	return res;
}

void SVGA_SetRedSignalOffset(uint16_t val)
{
	uint8_t tmp;
	tmp = val & 0x0f;
	SVGA_Write(SVGA_Addr_RedSignalOffset_LSB, tmp);
	tmp = (val >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_RedSignalOffset_MSB, tmp);
}

uint16_t SVGA_GetGreenSignalOffset()
{
	uint16_t res;
	res = SVGA_Read(SVGA_Addr_GreenSignalOffset_MSB);
	res = res << 8;
	res = res + SVGA_Read(SVGA_Addr_GreenSignalOffset_LSB);
	return res;
}

void SVGA_SetGreenSignalOffset(uint16_t val)
{
	uint8_t tmp;
	tmp = val & 0x0f;
	SVGA_Write(SVGA_Addr_GreenSignalOffset_LSB, tmp);
	tmp = (val >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_GreenSignalOffset_MSB, tmp);
}

uint16_t SVGA_GetBlueSignalOffset()
{
	uint16_t res;
	res = SVGA_Read(SVGA_Addr_BlueSignalOffset_MSB);
	res = res << 8;
	res = res + SVGA_Read(SVGA_Addr_BlueSignalOffset_LSB);
	return res;
}

void SVGA_SetBlueSignalOffset(uint16_t val)
{
	uint8_t tmp;
	tmp = val & 0x0f;
	SVGA_Write(SVGA_Addr_BlueSignalOffset_LSB, tmp);
	tmp = (val >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_BlueSignalOffset_MSB, tmp);
}

void SVGA_SetRGB_SignalOffset(uint16_t red, uint16_t green, uint16_t blue)
{
	uint8_t tmp;
	tmp = red & 0x0f;
	SVGA_Write(SVGA_Addr_RedSignalOffset_LSB, tmp);
	tmp = (red >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_RedSignalOffset_MSB, tmp);
	tmp = green & 0x0f;
	SVGA_Write(SVGA_Addr_GreenSignalOffset_LSB, tmp);
	tmp = (green >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_GreenSignalOffset_MSB, tmp);
	tmp = blue & 0x0f;
	SVGA_Write(SVGA_Addr_BlueSignalOffset_LSB, tmp);
	tmp = (blue >> 8) & 0x01;
	SVGA_Write(SVGA_Addr_BlueSignalOffset_MSB, tmp);
}


void SVGA_GetTestPattern(SVGA_TP_StructTypeDef *res)
{
	uint8_t tmp;
	tmp = SVGA_Read(SVGA_Addr_TestPatternModeSelection);
	res->TestPattern = (SVGA_TPC_TypeDef) tmp;
	res->LineWidth   = SVGA_Read(SVGA_Addr_TestPatternLineWidthSetting);
	res->LineSpace   = SVGA_Read(SVGA_Addr_TestPatternLineSpaceSetting);
	tmp = SVGA_Read(SVGA_Addr_TestPatternColorSetting);
	res->BackColor   = (SVGA_TPC_TypeDef) ((tmp >> 4 ) & 7) ;
	res->ForeColor   = (SVGA_TPC_TypeDef)  (tmp & 7);
}

void SVGA_SetTestPattern(SVGA_TP_TypeDef pal, uint8_t line_width, uint8_t line_space, SVGA_TPC_TypeDef back_color, SVGA_TPC_TypeDef fore_color)
{
	uint8_t tmp;
	tmp = pal & 0x07;
	SVGA_Write(SVGA_Addr_TestPatternModeSelection, tmp);
	if ((pal == SVGA_TP_VerticalLines) || (pal == SVGA_TP_HorizontalLines) || (pal == SVGA_TP_Chess))
	{
	  SVGA_Write(SVGA_Addr_TestPatternLineWidthSetting, line_width);
	  SVGA_Write(SVGA_Addr_TestPatternLineSpaceSetting, line_space);
	  tmp = back_color * 0x10 + fore_color;
	  SVGA_Write(SVGA_Addr_TestPatternColorSetting, tmp);
	}
}


