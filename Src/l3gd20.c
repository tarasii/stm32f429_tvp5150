#include "l3gd20.h"

L3GD20_Scale_t L3GD20_INT_Scale;

uint8_t L3GD20_INT_ReadSPI(uint8_t address) {
	uint8_t data;
	/* CS low */
	L3GD20_CS_LOW;
	/* Send address with read command */
  data = SPI_Read(address);
	/* CS high */
	L3GD20_CS_HIGH;
	/* Return data */
	return data;
}

void L3GD20_INT_WriteSPI(uint8_t address, uint8_t data) {
	/* CS low */
	L3GD20_CS_LOW;
	/* Send address with write command */
	SPI_Write(address, data);
	/* CS high */
	L3GD20_CS_HIGH;
}

DEV_Result_t L3GD20_Init(L3GD20_Scale_t scale) {
	//uint8_t r;
	
	if (L3GD20_TestConnection()) return DEV_Result_Error;

	/* Enable L3GD20 Power bit */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG1, 0xFF);

	/* Set L3GD20 scale */
	if (scale == L3GD20_Scale_250) {
		L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG4, 0x00);
	} else if (scale == L3GD20_Scale_500) {
		L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG4, 0x10);
	} else if (scale == L3GD20_Scale_2000) {
		L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG4, 0x20);
	}
	
	/* Save scale */
	L3GD20_INT_Scale = scale;

	/* Set high-pass filter settings */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG2, 0x00);

	/* Enable high-pass filter */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG5, 0x10);
	
	/* Everything OK */
	return DEV_Result_Ok;
}

DEV_Result_t L3GD20_Read(XYZ_t* L3DG20_Data) {
	float temp, s;
	
	/* Read X axis */
	L3DG20_Data->X = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_X_L);
	L3DG20_Data->X |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_X_H) << 8;

	/* Read Y axis */
	L3DG20_Data->Y = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Y_L);
	L3DG20_Data->Y |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Y_H) << 8;
	
	/* Read Z axis */
	L3DG20_Data->Z = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Z_L);
	L3DG20_Data->Z |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Z_H) << 8;
	
	/* Set sensitivity scale correction */
	if (L3GD20_INT_Scale == L3GD20_Scale_250) {
		/* Sensitivity at 250 range = 8.75 mdps/digit */
		s = L3GD20_SENSITIVITY_250 * 0.001;
	} else if (L3GD20_INT_Scale == L3GD20_Scale_500) {
		/* Sensitivity at 500 range = 17.5 mdps/digit */
		s = L3GD20_SENSITIVITY_500 * 0.001;
	} else {
		/* Sensitivity at 2000 range = 70 mdps/digit */
		s = L3GD20_SENSITIVITY_2000 * 0.001;
	}
	
	temp = (float)L3DG20_Data->X * s;
	L3DG20_Data->X = (int16_t) temp;
	temp = (float)L3DG20_Data->Y * s;
	L3DG20_Data->Y = (int16_t) temp;
	temp = (float)L3DG20_Data->Z * s;
	L3DG20_Data->Z = (int16_t) temp;
	
	/* Return OK */
	return DEV_Result_Ok;
}


DEV_Result_t L3GD20_TestConnection()
{
	L3GD20_CS_HIGH;
	/* Check if sensor is L3GD20 */
	if (L3GD20_INT_ReadSPI(L3GD20_REG_WHO_AM_I) != L3GD20_WHO_AM_I) {
		/* Sensor connected is not L3GD20 */
		return DEV_Result_Error;
	}
	return DEV_Result_Ok;
}


