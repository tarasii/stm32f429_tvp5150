#ifndef __itg3200_H
#define __itg3200_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

typedef enum
{                        /*!< Low Pass Filter Bandwidth  Internal Sample Rate  */
  ITG_DLPF_256_8 = 0x00, /*!<         256Hz                   8kHz             */
  ITG_DLPF_188_1 = 0x01, /*!<         188Hz                   1kHz             */
  ITG_DLPF_98_1  = 0x02, /*!<          98Hz                   1kHz             */
  ITG_DLPF_42_1  = 0x03, /*!<          42Hz                   1kHz             */
  ITG_DLPF_20_1  = 0x04, /*!<          20Hz                   1kHz             */
  ITG_DLPF_10_1  = 0x05, /*!<          10Hz                   1kHz             */
  ITG_DLPF_5_1   = 0x06  /*!<           5Hz                   1kHz             */
}ITG_DLPF_TypeDef ;      //Digital low pass filter configuration and internal sampling rate configuration 

typedef struct
{
	bool ACTL;     //
	bool OPEN;     //
	bool LATCH;    //
	bool ANY_RD;   //
	bool ITG_RDY;  //
	bool RAW_RDY;  //
	uint8_t VAL;
}ITG_INT_StructTypeDef; //   structure

typedef struct
{
	int16_t X;    //
	int16_t Y;    //
	int16_t Z;    //
}ITG_XYZ_StructTypeDef; //   structure

typedef enum
{
  ITG_CLK_Internal  = 0x00, /*!< Internal oscillator                   */
  ITG_CLK_GyroX     = 0x01, /*!< PLL with X Gyro reference             */
  ITG_CLK_GyroY     = 0x02, /*!< PLL with Y Gyro reference             */
  ITG_CLK_GyroZ     = 0x03, /*!< PLL with Z Gyro reference             */
  ITG_CLK_32Khz     = 0x04, /*!< PLL with external 32.768kHz reference */
  ITG_CLK_19Mhz     = 0x05  /*!< PLL with external 19.2MHz reference   */
}ITG_CLK_TypeDef ; // 

typedef struct
{
	bool Reset;      //
	bool Sleep;      //
	bool StbyX;      //
	bool StbyY;      //
	bool StbyZ;      //
	ITG_CLK_TypeDef CLK;         //
	uint8_t VAL;
}ITG_PM_StructTypeDef; // Power management structure

#define		ITG_WRITE_ADDRESS 0xD0 //AD0 = 0
//#define	ITG_WRITE_ADDRESS 0xD2 //AD0 = 1
#define		ITG_READ_ADDRESS  0xD1 //AD0 = 0
//#define	ITG_READ_ADDRESS  0xD3 //AD0 = 1

#define ITG_Addr_WHO_AM_I     0x00 // rw
#define ITG_Addr_SMPLRT_DIV   0x15 //
#define ITG_Addr_DLPF_FS      0x16 //
#define ITG_Addr_INT_CFG      0x17 //
#define ITG_Addr_INT_STATUS   0x1A // r
#define ITG_Addr_TEMP_OUT_H   0x1B //
#define ITG_Addr_TEMP_OUT_L   0x1C //
#define ITG_Addr_GYRO_XOUT_H  0x1D //
#define ITG_Addr_GYRO_XOUT_L  0x1E //
#define ITG_Addr_GYRO_YOUT_H  0x1F //
#define ITG_Addr_GYRO_YOUT_L  0x20 //
#define ITG_Addr_GYRO_ZOUT_H  0x21 //
#define ITG_Addr_GYRO_ZOUT_L  0x22 //
#define ITG_Addr_PWR_MGM      0x3E // rw

void ITG_Init(ITG_DLPF_TypeDef dlpf, uint8_t semp, ITG_CLK_TypeDef clk);
void ITG_WriteByte(uint8_t addr, uint8_t data);
uint8_t ITG_ReadByte(uint8_t addr);
uint8_t ITG_GetChipAddr(void);
void ITG_SetChipAddr(uint8_t res);
uint8_t ITG_GetSampleRateDivider(void);
void ITG_SetSampleRateDivider(uint8_t res);
ITG_DLPF_TypeDef ITG_GetDLPF(void);
void ITG_SetDLPF(ITG_DLPF_TypeDef dlpf);
void ITG_GetIntConfig(ITG_INT_StructTypeDef *res);
void ITG_SetIntConfig(bool actl, bool open, bool latch, bool any_rd, bool itg_rdy, bool raw_rdy);
void ITG_GetIntStatus(ITG_INT_StructTypeDef *res);
int16_t ITG_GetTemperature(void);
int16_t ITG_GetX(void);
int16_t ITG_GetY(void);
int16_t ITG_GetZ(void);
void ITG_GetXYZ(ITG_XYZ_StructTypeDef *res);
void ITG_GetPowerManagement(ITG_PM_StructTypeDef *res);
void ITG_SetPowerManagement(bool reset, bool sleep, bool stby_x, bool stby_y, bool stby_z, ITG_CLK_TypeDef clk);
void ITG_Reset(void);
void ITG_Sleep(void);
int16_t ITG_ConvTemp(int16_t in);

//Taras Ivaniv

#endif /*__ itg3200_H */
