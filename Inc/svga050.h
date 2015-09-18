#ifndef __svga050_H
#define __svga050_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

typedef enum
{
  SVGA_SM_YCbCr_422_16 = 0x00, /*!< 16-bit 422, YCbCr */
  SVGA_SM_YCbCr_444_24 = 0x01, /*!< 24-bit 444, YcbCr */
  SVGA_SM_MONO_8       = 0x02, /*!< 8-bit MONO        */
  SVGA_SM_RGB_444_24   = 0x03, /*!< 24-bit 444, RGB   */
  SVGA_SM_YCbCr_422_8  = 0x04  /*!< 8-bit 422, RGB    */
}SVGA_SM_TypeDef; //Signal Mode: Select input data format

typedef enum
{
  SVGA_SSM_EmbeddedSync0         = 0x00, /*!< Embedded Sync            */
  SVGA_SSM_EmbeddedSync1         = 0x01, /*!< Embedded Sync            */
  SVGA_SSM_SyncWithDE            = 0x02, /*!< External Sync with DE    */
  SVGA_SSM_ExternalSyncWithoutDE = 0x03  /*!< External Sync without DE */
}SVGA_SSM_TypeDef; //Sync Signal: Select sync mode

typedef enum
{
  SVGA_NonInterlaced    = 0x00, /*!< Non-interlaced    */
  SVGA_Interlaced       = 0x01, /*!< Interlaced        */
  SVGA_PseudoInterlaced = 0x03  /*!< Pseudo-Interlaced */
}SVGA_SCM_TypeDef ; //Scan mode : Select scan mode 

typedef struct
{
	SVGA_SM_TypeDef  SignalMode;  //
	SVGA_SSM_TypeDef SyncSignal;  //
	SVGA_SCM_TypeDef ScanMode;    //
	uint8_t VAL;
}SVGA_SCM_StructTypeDef; //Input video type structure

typedef struct
{
	bool Enable_3D;          //
	bool Refresh_3D;         //
	bool VericalPolarity;    //
	bool HorisontalPolarity; //
	uint8_t VAL;
}SVGA_SP_StructTypeDef; // V sync/H sync Polarity& 3D structure

typedef enum
{
  SVGA_SVP_Before1 = 0x00, /*!< 1 pixel before input SAV */
  SVGA_SVP_Same    = 0x01, /*!< Same as input SAV        */
  SVGA_SVP_After1  = 0x02, /*!< 1 pixel after input SAV  */
  SVGA_SVP_After2  = 0x03  /*!< 2 pixel after input SAV  */
}SVGA_SVP_TypeDef; // SAV Offset : Adjust start active video (SAV) position

typedef enum
{
  SVGA_SLP_Same   = 0x00, /*!< Same as Even field       */
  SVGA_SLP_After  = 0x01, /*!< 1 line after Even field  */
  SVGA_SLP_Before = 0x02  /*!< 1 line before Even field */
}SVGA_SLP_TypeDef; // V Offset : Adjust odd field active video start position when interlaced video mode

typedef enum
{
  SVGA_SD_1_1   = 0x00, /*!< 1:1   */
  SVGA_SD_11_10 = 0x01, /*!< 11:10 */
  SVGA_SD_9_8   = 0x02  /*!< 9:8   */
}SVGA_SD_TypeDef; // H Scale : Horizontal 4/3downscale for PAL/NTSC

typedef struct
{
	bool V_Scale;            //0 - 1:1; 1 - 6:5
	SVGA_SD_TypeDef H_Scale; //0 - 1:1; 1 - 11:10; 2 - 9:8
	uint8_t VAL;
}SVGA_DS_StructTypeDef; // Down scaling for NTSC & PAL video structure

typedef struct
{
	bool PDOWN;   // All system power off
	bool BSGENPD; // Discharge current generator power off
	bool RDACPD;  // DAC module power off
	bool RAMPPD;  // DAC Buffer module power off
	bool VCOMPD;  // Vcom power off
	bool TSENPD;  // Temperature sensor power off
	uint8_t VAL;
}SVGA_PD_StructTypeDef; // Power down structure

typedef struct
{
	bool DispOff; // 0 - ON; 1 - OFF
	bool VSCAN;   // 0 - Top > Bottom; 1 - Bottom > Top
	bool HSCAN;   // 0 - Left > Right; 1 - Right > Left
	uint8_t VAL;
}SVGA_DO_StructTypeDef; // Power down structure

typedef enum
{
  SVGA_DCS_0   = 0x00, /*!< 0 nA (OFF) */
  SVGA_DCS_0_5 = 0x01, /*!< 0.5 nA     */
  SVGA_DCS_1   = 0x02  /*!< 1 nA       */
}SVGA_DCS_TypeDef ; // 

typedef enum
{
  SVGA_TP_OFF             = 0x00, /*!< Pattern Generator Off (Normal) */
  SVGA_TP_ColorBar        = 0x01, /*!< Color Bar                      */
  SVGA_TP_GrayScale       = 0x02, /*!< Gray Scale                     */
  SVGA_TP_Tile            = 0x03, /*!< Tile                           */
  SVGA_TP_VerticalLines   = 0x04, /*!< Vertical Lines                 */
  SVGA_TP_HorizontalLines = 0x05, /*!< Horizontal Lines               */
  SVGA_TP_Chess           = 0x06  /*!< Ver. & Hor. Lines              */
}SVGA_TP_TypeDef ; // Test Pattern

typedef enum
{
  SVGA_TPC_Black = 0x00, /*!< Black */
  SVGA_TPC_Blue  = 0x01, /*!< Blue  */
  SVGA_TPC_Green = 0x02, /*!< Green */
  SVGA_TPC_Red   = 0x04, /*!< Red   */
  SVGA_TPC_White = 0x07  /*!< White */
}SVGA_TPC_TypeDef ; // 

typedef struct
{
	SVGA_TPC_TypeDef TestPattern; //
	SVGA_TPC_TypeDef BackColor;   //
	SVGA_TPC_TypeDef ForeColor;   //
	uint8_t LineWidth;
	uint8_t LineSpace;
	uint8_t VAL1;
	uint8_t VAL2;
}SVGA_TP_StructTypeDef; // Test Pattern structure

//typedef enum
//{
//  SVGA_         = 0x00, /*!<              */
//  SVGA_         = 0x01, /*!<              */
//  SVGA_         = 0x02, /*!<              */
//  SVGA_         = 0x03  /*!<              */
//}SVGA__TypeDef ; // 
//
//typedef struct
//{
//	__ __;               //
//	__ __;               //
//	__ __;         //
//	uint8_t VAL;
//}SVGA__StructTypeDef; //   structure

//#define TVP_WRITE_ADDRESS 0x1C //SELADR0 = 0
#define	  SVGA_WRITE_ADDRESS 0x1E //SELADR0 = 1
//#define	TVP_READ_ADDRESS 0x1D  //SELADR0 = 0
#define	  SVGA_READ_ADDRESS 0x1F  //SELADR0 = 1

#define SVGA_Default_VCOM_Level 0x1B

#define SVGA_Addr_RevisionInformation            0x00 //
//Video Related Registers
#define SVGA_Addr_InputVideoTypeSet              0x01 //
#define SVGA_Addr_SyncSignalPolaritySet          0x02 //
#define SVGA_Addr_VerticalBlankLines             0x03 //
#define SVGA_Addr_HorizontalBlankPixels          0x04 //
#define SVGA_Addr_AdjustStartActiveVideoPosition 0x05 //
#define SVGA_Addr_FieldStartLinePosition         0x06 //
#define SVGA_Addr_DownScaling                    0x07 //
#define SVGA_Addr_BrightnessControl              0x08 //
#define SVGA_Addr_ContrastControl                0x09 //
#define SVGA_Addr_PowerDownModeControl           0x0F //
//Video Display Control Registers
#define SVGA_Addr_DisplayOff                     0x10 //
#define SVGA_Addr_DisplayLeftMargin              0x11 //
#define SVGA_Addr_DisplayRightMargin             0x12 //
#define SVGA_Addr_DisplayTopMargin               0x13 //
#define SVGA_Addr_DisplayBottomMargin            0x14 //
#define SVGA_Addr_DA_OffsetSetting               0x16 //
#define SVGA_Addr_DischargeCurrentSetting        0x17 //
#define SVGA_Addr_DischargeEnabledControl        0x18 //
#define SVGA_Addr_VcomLevelSetting               0x19 //
//Temperature Sensor Register
#define SVGA_Addr_TemperatureSensorReadout       0x1D //
//Gamma Look-Up Table Registers
#define SVGA_Addr_GammaCorrectionLUT0_LSB        0x20 //
#define SVGA_Addr_GammaCorrectionLUT0_MSB        0x21 //
//Color Offset Control Registers
#define SVGA_Addr_RedSignalOffset_LSB            0x44 //
#define SVGA_Addr_RedSignalOffset_MSB            0x45 //
#define SVGA_Addr_GreenSignalOffset_LSB          0x46 //
#define SVGA_Addr_GreenSignalOffset_MSB          0x47 //
#define SVGA_Addr_BlueSignalOffset_LSB           0x48 //
#define SVGA_Addr_BlueSignalOffset_MSB           0x49 //
//Test Pattern Generator Control Register
#define SVGA_Addr_TestPatternModeSelection       0x4A //*
#define SVGA_Addr_TestPatternLineWidthSetting    0x4B //*
#define SVGA_Addr_TestPatternLineSpaceSetting    0x4C //*
#define SVGA_Addr_TestPatternColorSetting        0x4D //*

void SVGA_Init(void);

void SVGA_Write(uint8_t addr, uint8_t data);
uint8_t SVGA_Read(uint8_t addr);

uint8_t SVGA_GetChipRev(void);
void SVGA_GetInputVideoTypeSet(SVGA_SCM_StructTypeDef *res);
void SVGA_SetInputVideoType(SVGA_SM_TypeDef signal_mode, SVGA_SSM_TypeDef sync_signal, SVGA_SCM_TypeDef scan_mode);
void SVGA_GetSyncSignalPolarity(SVGA_SP_StructTypeDef *res);
void SVGA_SetSyncSignalPolarity(bool enable_3d, bool refresh_3d, bool v_pol, bool h_pol);
uint8_t SVGA_GetVerticalBlankLines(void);
void SVGA_SetVerticalBlankLines(uint8_t v_blank);
uint8_t SVGA_GetHorizontalBlankPixels(void);
void SVGA_SetHorizontalBlankPixels(uint8_t h_blank);
SVGA_SVP_TypeDef SVGA_GetStartActiveVideoPosition(void);
void SVGA_SetStartActiveVideoPosition(SVGA_SVP_TypeDef v_offset);
SVGA_SLP_TypeDef SVGA_GetFieldStartLinePosition(void);
void SVGA_SetFieldStartLinePosition(SVGA_SLP_TypeDef h_offset);

void SVGA_GetDownScaling(SVGA_DS_StructTypeDef *res);
void SVGA_SetDownScaling(bool v_scale, SVGA_SD_TypeDef h_scale);

uint8_t SVGA_GetBrightness(void);
void SVGA_SetBrightness(uint8_t val);
uint8_t SVGA_GetContrast(void);
void SVGA_SetContrast(uint8_t val);
void SVGA_SetDisplayConfig(uint8_t brightness, uint8_t contrast);

void SVGA_GetPowerDown(SVGA_PD_StructTypeDef *res);
void SVGA_SetPowerDown(bool PDOWN, bool BSGENPD, bool RDACPD, bool RAMPPD, bool VCOMPD, bool TSENPD);

void SVGA_GetDisplayOff(SVGA_DO_StructTypeDef *res);
void SVGA_SetDisplayOff(bool DispOff, bool VSCAN, bool HSCAN);

uint8_t SVGA_GetLeftMargin(void);
void SVGA_SetLeftMargin(uint8_t val);
uint8_t SVGA_GetRightMargin(void);
void SVGA_SetRightMargin(uint8_t val);
uint8_t SVGA_GetTopMargin(void);
void SVGA_SetTopMargin(uint8_t val);
uint8_t SVGA_GetBottomMargin(void);
void SVGA_SetBottomMargin(uint8_t val);
void SVGA_SetMargin(uint8_t left, uint8_t right, uint8_t top, uint8_t bottom);

uint8_t SVGA_Get_DA_OffsetSetting(void);
void SVGA_Set_DA_OffsetSetting(uint8_t val);

SVGA_DCS_TypeDef SVGA_GetDischargeCurrent(void);
void SVGA_SetDischargeCurrent(SVGA_DCS_TypeDef val);
bool SVGA_GetDischargeEnabled(void);
void SVGA_SetDischargeEnabled(bool val);

uint8_t SVGA_GetVcomLevel(void);
void SVGA_SetVcomLevel(uint8_t val);
uint8_t SVGA_GetTemperatureSensor(void);
float SVGA_CalculateTemperature(uint8_t raw_temp);
void SVGA_SetTemperatureLuminanceCompensation(void);


uint16_t SVGA_GetGammaCorrection(uint8_t num);
void SVGA_SetGammaCorrection(uint8_t num, uint16_t val);
uint16_t SVGA_GetRedSignalOffset(void);
void SVGA_SetRedSignalOffset(uint16_t val);
uint16_t SVGA_GetGreenSignalOffset(void);
void SVGA_SetGreenSignalOffset(uint16_t val);
uint16_t SVGA_GetBlueSignalOffset(void);
void SVGA_SetBlueSignalOffset(uint16_t val);
void SVGA_SetRGB_SignalOffset(uint16_t red, uint16_t green, uint16_t blue);

void SVGA_GetTestPattern(SVGA_TP_StructTypeDef *res);
void SVGA_SetTestPattern(SVGA_TP_TypeDef pal, uint8_t line_width, uint8_t line_space, SVGA_TPC_TypeDef back_color, SVGA_TPC_TypeDef fore_color);


#endif /*__ svga050_H */
