#include "svga050.h"

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


