#include "adxl345.h"

DEV_Result_t ADXL_Init()
{
	if (ADXL_TestConnection()) return DEV_Result_Error;
	ADXL_SetPowerSaving(0,0,1,0,ADXL_WU_8);
	return DEV_Result_Ok;
}


void ADXL_WriteByte(uint8_t addr, uint8_t data)
{
	uint8_t i2cbuf[2];
	i2cbuf[0] = addr;
	i2cbuf[1] = data;
	I2C1_WriteBuffer(ADXL_WRITE_ADDRESS, i2cbuf, 2);
}

uint8_t ADXL_ReadByte(uint8_t addr)
{
	uint8_t i2cbuf[1];
  I2C1_WriteBuffer(ADXL_READ_ADDRESS, &addr, 1);
	I2C1_ReadBuffer(ADXL_READ_ADDRESS, i2cbuf, 1);
	return i2cbuf[0];
}


uint8_t ADXL_GetDeviceId()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_DEVID);
	return res;
}

uint8_t ADXL_GetTapThreshold()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_TAP_THRESH);
	return res;
}

void ADXL_SetTapThreshold(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_TAP_THRESH, res);
}

uint8_t ADXL_GetX_Offset()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_OFSX);
	return res;
}

void ADXL_SetX_Offset(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_OFSX, res);
}

uint8_t ADXL_GetY_Offset()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_OFSY);
	return res;
}

void ADXL_SetY_Offset(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_OFSY, res);
}

uint8_t ADXL_GetZ_Offset()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_OFSZ);
	return res;
}

void ADXL_SetZ_Offset(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_OFSZ, res);
}

void ADXL_SetXYZ_Offset(uint8_t x, uint8_t y, uint8_t z)
{
	ADXL_WriteByte(ADXL_Addr_OFSX, x);
	ADXL_WriteByte(ADXL_Addr_OFSY, y);
	ADXL_WriteByte(ADXL_Addr_OFSZ, z);
}

uint8_t ADXL_GetTapDuration()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_TAP_DUR);
	return res;
}

void ADXL_SetTapDuration(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_TAP_DUR, res);
}

uint8_t ADXL_GetTapLatency()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_TAP_LATENT);
	return res;
}

void ADXL_SetTapLatency(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_TAP_LATENT, res);
}

uint8_t ADXL_GetTapWindow()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_TAP_WINDOW);
	return res;
}

void ADXL_SetTapWindow(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_TAP_WINDOW, res);
}

uint8_t ADXL_GetActivityThreshold()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_ACT_THRESH);
	return res;
}

void ADXL_SetActivityThreshold(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_ACT_THRESH, res);
}

uint8_t ADXL_GetInactivityThreshold()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_INACT_THRESH);
	return res;
}

void ADXL_SetInactivityThreshold(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_INACT_THRESH, res);
}

uint8_t ADXL_GetInactivityTime()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_INACT_TIME);
	return res;
}

void ADXL_SetInactivityTime(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_INACT_TIME, res);
}


void ADXL_GetAxisControl(ADXL_AC_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_ACT_INACT_CTL);
	res->ACT_ACDC   = (bool) ((res->VAL >> 7) & 1);
	res->ACT_X      = (bool) ((res->VAL >> 6) & 1);
	res->ACT_Y      = (bool) ((res->VAL >> 5) & 1);
	res->ACT_Z      = (bool) ((res->VAL >> 4) & 1);
	res->INACT_ACDC = (bool) ((res->VAL >> 3) & 1);
	res->INACT_X    = (bool) ((res->VAL >> 2) & 1);
	res->INACT_Y    = (bool) ((res->VAL >> 1) & 1);
	res->INACT_Z    = (bool) ( res->VAL       & 1);	
}

void ADXL_SetAxisControl(bool act_acdc, bool act_x, bool act_y, bool act_z, bool inact_acdc, bool inact_x, bool inact_y, bool inact_z)
{
	uint8_t tmp;
	tmp = act_acdc * 0x80 + act_x * 0x40 + act_y * 0x20 + act_z * 0x10 + inact_acdc * 8 + inact_x * 4 + inact_y * 2 + inact_z;
	ADXL_WriteByte(ADXL_Addr_ACT_INACT_CTL, tmp);
}

uint8_t ADXL_GetFreeFallThreshold()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_FF_THRESH);
	return res;
}

void ADXL_SetFreeFallThreshold(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_FF_THRESH, res);
}

uint8_t ADXL_GetFreeFallTime()
{
	uint8_t res;
	res = ADXL_ReadByte(ADXL_Addr_FF_TIME);
	return res;
}

void ADXL_SetFreeFallTime(uint8_t res)
{
	ADXL_WriteByte(ADXL_Addr_FF_TIME, res);
}

void ADXL_GetTapAxis(ADXL_TA_StructTypeDef *res)
{
	res->VAL      = ADXL_ReadByte(ADXL_Addr_TAP_AXES);
	res->SUPRESS  = (bool) ((res->VAL >> 3) & 1);
	res->TAP_X    = (bool) ((res->VAL >> 2) & 1);
	res->TAP_Y    = (bool) ((res->VAL >> 1) & 1);
	res->TAP_Z    = (bool) ( res->VAL       & 1);	
}

void ADXL_SetTapAxis(bool supress, bool tap_x, bool tap_y, bool tap_z)
{
	uint8_t tmp;
	tmp = supress * 8 + tap_x * 4 + tap_y * 2 + tap_z;
	ADXL_WriteByte(ADXL_Addr_TAP_AXES, tmp);
}

void ADXL_GetActTapStatus(ADXL_ATS_StructTypeDef *res)
{
	res->VAL      = ADXL_ReadByte(ADXL_Addr_ACT_TAP_STATUS);
	res->ACT_X    = (bool) ((res->VAL >> 6) & 1);
	res->ACT_Y    = (bool) ((res->VAL >> 5) & 1);
	res->ACT_Z    = (bool) ((res->VAL >> 4) & 1);
	res->ASLEEP   = (bool) ((res->VAL >> 3) & 1);
	res->TAP_X    = (bool) ((res->VAL >> 2) & 1);
	res->TAP_Y    = (bool) ((res->VAL >> 1) & 1);
	res->TAP_Z    = (bool) ( res->VAL       & 1);	
}


void ADXL_GetDataRatePowerMode(ADXL_DR_StructTypeDef *res)
{
	res->VAL      = ADXL_ReadByte(ADXL_Addr_BW_RATE);
	res->LOWPOWER = (bool)            ((res->VAL >> 4) & 1  );
	res->RATE     = (ADXL_DR_TypeDef) ( res->VAL       & 0xF);	
}

void ADXL_SetDataRatePowerMode(bool low_power, ADXL_DR_TypeDef rate)
{
	uint8_t tmp;
	tmp = low_power * 0x10 + (rate & 0x0F);
	ADXL_WriteByte(ADXL_Addr_BW_RATE, tmp);
}

void ADXL_GetPowerSaving(ADXL_PS_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_POWER_CTL);
	res->LINK       = (bool) ((res->VAL >> 5) & 1);
	res->AUTO_SLEEP = (bool) ((res->VAL >> 4) & 1);
	res->MEASURE    = (bool) ((res->VAL >> 3) & 1);
	res->SLEEP      = (bool) ((res->VAL >> 2) & 1);
	res->WAKEUP     = (ADXL_WU_TypeDef) ( res->VAL       & 3);	
}

void ADXL_SetPowerSaving(bool link, bool auto_sleep, bool measure, bool sleep, ADXL_WU_TypeDef wakeup)
{
	uint8_t tmp;
	tmp = link * 0x20 + auto_sleep * 0x10 + measure * 8 + sleep * 4 + (wakeup & 3);
	ADXL_WriteByte(ADXL_Addr_POWER_CTL, tmp);
}

void ADXL_GetIntConfig(ADXL_IC_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_INT_ENABLE);
	res->DATA_READY = (bool) ((res->VAL >> 7) & 1);
	res->SINGLE_TAP = (bool) ((res->VAL >> 6) & 1);
	res->DOUBLE_TAP = (bool) ((res->VAL >> 5) & 1);
	res->ACTIVITY   = (bool) ((res->VAL >> 4) & 1);
	res->INACTIVITY = (bool) ((res->VAL >> 3) & 1);
	res->FREE_FALL  = (bool) ((res->VAL >> 2) & 1);
	res->WATTERMARK = (bool) ((res->VAL >> 1) & 1);
	res->OVERRUN    = (bool) ( res->VAL       & 1);	
}

void ADXL_SetIntConfig(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun)
{
	uint8_t tmp;
	tmp = data_ready * 0x80 + single_tap * 0x40 + double_tap * 0x20 + activity * 0x10 + inactivity * 8 + free_fall * 4 + watermark * 2 + overrun;
	ADXL_WriteByte(ADXL_Addr_INT_ENABLE, tmp);
}

void ADXL_GetIntMap(ADXL_IC_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_INT_MAP);
	res->DATA_READY = (bool) ((res->VAL >> 7) & 1);
	res->SINGLE_TAP = (bool) ((res->VAL >> 6) & 1);
	res->DOUBLE_TAP = (bool) ((res->VAL >> 5) & 1);
	res->ACTIVITY   = (bool) ((res->VAL >> 4) & 1);
	res->INACTIVITY = (bool) ((res->VAL >> 3) & 1);
	res->FREE_FALL  = (bool) ((res->VAL >> 2) & 1);
	res->WATTERMARK = (bool) ((res->VAL >> 1) & 1);
	res->OVERRUN    = (bool) ( res->VAL       & 1);	
}

void ADXL_SetIntMap(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun)
{
	uint8_t tmp;
	tmp = data_ready * 0x80 + single_tap * 0x40 + double_tap * 0x20 + activity * 0x10 + inactivity * 8 + free_fall * 4 + watermark * 2 + overrun;
	ADXL_WriteByte(ADXL_Addr_INT_MAP, tmp);
}

void ADXL_GetIntSource(ADXL_IC_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_INT_SOURCE);
	res->DATA_READY = (bool) ((res->VAL >> 7) & 1);
	res->SINGLE_TAP = (bool) ((res->VAL >> 6) & 1);
	res->DOUBLE_TAP = (bool) ((res->VAL >> 5) & 1);
	res->ACTIVITY   = (bool) ((res->VAL >> 4) & 1);
	res->INACTIVITY = (bool) ((res->VAL >> 3) & 1);
	res->FREE_FALL  = (bool) ((res->VAL >> 2) & 1);
	res->WATTERMARK = (bool) ((res->VAL >> 1) & 1);
	res->OVERRUN    = (bool) ( res->VAL       & 1);	
}

void ADXL_SetIntSource(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun)
{
	uint8_t tmp;
	tmp = data_ready * 0x80 + single_tap * 0x40 + double_tap * 0x20 + activity * 0x10 + inactivity * 8 + free_fall * 4 + watermark * 2 + overrun;
	ADXL_WriteByte(ADXL_Addr_INT_SOURCE, tmp);
}

void ADXL_GetDataFormat(ADXL_DF_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_DATA_FORMAT);
	res->SELF_TEST  = (bool) ((res->VAL >> 7) & 1);
	res->SPI        = (bool) ((res->VAL >> 6) & 1);
	res->INT_INVERT = (bool) ((res->VAL >> 5) & 1);
	res->FULL_RES   = (bool) ((res->VAL >> 3) & 1);
	res->JUSTIFY    = (bool) ((res->VAL >> 2) & 1);
	res->RANGE      = (ADXL_DFR_TypeDef) ( res->VAL       & 3);	
}

void ADXL_SetDataFormat(bool self_test, bool spi, bool int_invert, bool full_res, bool justify, ADXL_DFR_TypeDef range)
{
	uint8_t tmp;
	tmp = self_test * 0x80 + spi * 0x40 + int_invert * 0x10 + full_res * 8 + justify * 4 + (range & 3);
	ADXL_WriteByte(ADXL_Addr_DATA_FORMAT, tmp);
}

void ADXL_SelfTest()
{
	ADXL_DF_StructTypeDef tmp;
	ADXL_GetDataFormat(&tmp);
	ADXL_SetDataFormat(true, tmp.SPI, tmp.INT_INVERT, tmp.FULL_RES, tmp.JUSTIFY, tmp.RANGE);
}

uint16_t ADXL_GetX()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ADXL_Addr_DATAX_LSB;
  I2C1_WriteBuffer(ADXL_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ADXL_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[1] << 8)| i2cbuf[0];
//	res = ADXL_ReadByte(ADXL_Addr_DATAX0);
//	res = res << 8;
//	res = res + ADXL_ReadByte(ADXL_Addr_DATAX1);
	return res;
}

uint16_t ADXL_GetY()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ADXL_Addr_DATAY_LSB;
  I2C1_WriteBuffer(ADXL_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ADXL_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[1] << 8)| i2cbuf[0];
//	res = ADXL_ReadByte(ADXL_Addr_DATAY0);
//	res = res << 8;
//	res = res + ADXL_ReadByte(ADXL_Addr_DATAY1);
	return res;
}

uint16_t ADXL_GetZ()
{
	uint16_t res = 0;
	uint8_t i2cbuf[2];
	i2cbuf[0] = ADXL_Addr_DATAZ_LSB;
  I2C1_WriteBuffer(ADXL_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ADXL_READ_ADDRESS, i2cbuf, 2);

	res = (i2cbuf[1] << 8)| i2cbuf[0];
//	res = ADXL_ReadByte(ADXL_Addr_DATAZ0);
//	res = res << 8;
//	res = res + ADXL_ReadByte(ADXL_Addr_DATAZ1);
	return res;
}

void ADXL_GetXYZ(XYZ_t *res)
{
	uint8_t i2cbuf[6];
	i2cbuf[0] = ADXL_Addr_DATAX_LSB;
  I2C1_WriteBuffer(ADXL_READ_ADDRESS, i2cbuf, 1);
	I2C1_ReadBuffer(ADXL_READ_ADDRESS, i2cbuf, 6);

	res->X = (i2cbuf[1] << 8)| i2cbuf[0];
	res->Y = (i2cbuf[3] << 8)| i2cbuf[2];
	res->Z = (i2cbuf[5] << 8)| i2cbuf[4];
//	res->X = ADXL_GetX();
//	res->Y = ADXL_GetY();
//	res->Z = ADXL_GetZ();
}


void ADXL_GetFIFO_Status(ADXL_FC_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_FIFO_STATUS);
	res->FIFO_TRIG  = (bool)    ((res->VAL >> 7) & 1   );
	res->ENTRIES    = (uint8_t) ( res->VAL       & 0x3F);	
}

void ADXL_GetFIFO_Control(ADXL_FS_StructTypeDef *res)
{
	res->VAL        = ADXL_ReadByte(ADXL_Addr_FIFO_CTL);
	res->FIFO_MODE  = (ADXL_FM_TypeDef) ((res->VAL >> 6) & 3   );
	res->FIFO_TRIG  = (bool)            ((res->VAL >> 5) & 1   );
	res->SAMPLES    = (uint8_t)          ( res->VAL      & 0x1F);	
}

void ADXL_SetFIFO_Control(ADXL_FM_TypeDef fifo_mode, bool trigger, uint8_t samples)
{
	uint8_t tmp;
	tmp = fifo_mode * 0x40 + trigger * 0x20 + (samples & 0x1F);
	ADXL_WriteByte(ADXL_Addr_FIFO_CTL, tmp);
}

DEV_Result_t ADXL_TestConnection()
{
	if (ADXL_GetDeviceId() == ADXL_DEVICE_ID) return DEV_Result_Ok;
	return DEV_Result_Error;
}




