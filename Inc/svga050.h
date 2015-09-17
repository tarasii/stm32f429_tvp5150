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
}SVGA_SP_StructTypeDef; // V sync/H sync Polarity& 3D function

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
//}SVGA__StructTypeDef; //

//#define TVP_WRITE_ADDRESS 0x1C //SELADR0 = 0
#define	  SVGA_WRITE_ADDRESS 0x1E //SELADR0 = 1
//#define	TVP_READ_ADDRESS 0x1D  //SELADR0 = 0
#define	  SVGA_READ_ADDRESS 0x1F  //SELADR0 = 1

#define SVGA_Addr_RevisionInformation            0x00 //
#define SVGA_Addr_InputVideoTypeSet              0x01 //
#define SVGA_Addr_SyncSignalPolaritySet          0x02 //
#define SVGA_Addr_VerticalBlankLines             0x03 //
#define SVGA_Addr_HorizontalBlankPixels          0x04 //
#define SVGA_Addr_AdjustStartActiveVideoPosition 0x05 //
#define SVGA_Addr_FieldStartLinePosition         0x06 //
#define SVGA_Addr_DownScaling                    0x07 //*
#define SVGA_Addr_BrightnessControl              0x08 //*
#define SVGA_Addr_ContrastControl                0x09 //*
#define SVGA_Addr_PowerDownModeControl           0x0F //*
#define SVGA_Addr_DisplayOff                     0x10 //*
#define SVGA_Addr_DisplayLeftMargin              0x11 //*
#define SVGA_Addr_DisplayRightMargin             0x12 //*
#define SVGA_Addr_DisplayTopMargin               0x13 //*
#define SVGA_Addr_DisplayBottomMargin            0x14 //*
#define SVGA_Addr_DA_OffsetSetting               0x16 //*
#define SVGA_Addr_DischargeCurrentSetting        0x17 //*
#define SVGA_Addr_DischargeEnabledControl        0x18 //*
#define SVGA_Addr_VcomLevelSetting               0x19 //*
#define SVGA_Addr_TemperatureSensorReadout       0x1D //*
#define SVGA_Addr_GammaCorrectionLUT0_LSB        0x20 //*
#define SVGA_Addr_GammaCorrectionLUT0_MSB        0x21 //*
#define SVGA_Addr_RedSignalOffset_LSB            0x44 //*
#define SVGA_Addr_RedSignalOffset_MSB            0x45 //*
#define SVGA_Addr_GreenSignalOffset_LSB          0x46 //*
#define SVGA_Addr_GreenSignalOffset_MSB          0x47 //*
#define SVGA_Addr_BlueSignalOffset_LSB           0x48 //*
#define SVGA_Addr_BlueSignalOffset_MSB           0x49 //*
#define SVGA_Addr_TestPatternModeSelection       0x4A //*
#define SVGA_Addr_TestPatternLineWidthSetting    0x4B //*
#define SVGA_Addr_TestPatternLineSpaceSetting    0x4C //*
#define SVGA_Addr_TestPatternColorSetting        0x4D //*

void SVGA_Write(uint8_t addr, uint8_t data);
uint8_t SVGA_Read(uint8_t addr);
uint8_t SVGA_GetChipRev();
void SVGA_GetInputVideoTypeSet(SVGA_SCM_StructTypeDef *res);
void SVGA_SetInputVideoType(SVGA_SM_TypeDef signal_mode, SVGA_SSM_TypeDef sync_signal, SVGA_SCM_TypeDef scan_mode);
void SVGA_GetSyncSignalPolarity(SVGA_SP_StructTypeDef *res);
void SVGA_SetSyncSignalPolarity(bool enable_3d, bool refresh_3d, bool v_pol, bool h_pol);
uint8_t SVGA_GetVerticalBlankLines();
void SVGA_SetVerticalBlankLines(uint8_t v_blank);
uint8_t SVGA_GetHorizontalBlankPixels();
void SVGA_SetHorizontalBlankPixels(uint8_t h_blank);
SVGA_SVP_TypeDef SVGA_GetStartActiveVideoPosition();
void SVGA_SetStartActiveVideoPosition(SVGA_SVP_TypeDef v_offset);
SVGA_SLP_TypeDef SVGA_GetFieldStartLinePosition();
void SVGA_SetFieldStartLinePosition(SVGA_SLP_TypeDef h_offset);


#endif /*__ svga050_H */
