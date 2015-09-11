#ifndef __tvp5150_H
#define __tvp5150_H

#include <stdint.h>
#include <stdbool.h>
//#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"

//#define AIP1A 0
//#define AIP1B 2
//#define AIP_S 1
typedef enum
{
  TVP_CS_AIP1A             = 0x00,  /*!< Composite AIP1A    */
  TVP_CS_AIP_S             = 0x01,  /*!< S-Video            */
  TVP_CS_AIP1B             = 0x02   /*!< Composite AIP1B    */
}TVP_CS_TypeDef; //ChanelSource

typedef enum
{																		/*!<        === offset or gain ===        */
  TVP_ACC_DISABLED         = 0x00,  /*!< Disabled                             */
  TVP_ACC_AUTO             = 0x01,  /*!< Automatic                            */
  TVP_ACC_FROZEN           = 0x03   /*!< Level frozen to previously set value */
}TVP_ACC_TypeDef;          //AnalogChannelControls

typedef enum
{
  TVP_VS_AUTO             = 0x00,  /*!< AUTO          */
  TVP_VS_NTSC             = 0x02,  /*!< NTSC          */
  TVP_CS_PAL              = 0x04,  /*!< PAL BGH       */
  TVP_CS_PALM             = 0x06,  /*!< PAL M         */
  TVP_CS_COMB             = 0x08,  /*!< Combination-N */
  TVP_CS_NTSC4            = 0x0A   /*!< NTSC 4.43     */
}TVP_VS_TypeDef; //VideoStandart

typedef struct
{
	TVP_ACC_TypeDef Offset;
	TVP_ACC_TypeDef Gain;
	uint8_t VAL;
}TVP_ACC_StructTypeDef;

typedef struct
{
	bool PowerDown;
	bool GLCO;
	uint8_t VAL;
}TVP_OMC_StructTypeDef; //OperatingModeControls structure

typedef struct
{
	uint16_t DeviceId;
	uint8_t ROM;
	uint8_t RAM;
	uint16_t VerticalLineCount;
}TVP_Info_StructTypeDef; //Info structure

typedef struct
{
	uint8_t r1;
	uint8_t r2;
	uint8_t AGC;
	uint8_t SCH;
	uint8_t r5;
	uint8_t int_r1;
	uint8_t int_r2;
}TVP_Status_StructTypeDef; //Status structure

typedef enum
{
  TVP_P09_SCLK             = 0x00,  /*!< SCLK (default)  */
  TVP_P09_PCLK             = 0x01,  /*!< PCLK            */
}TVP_P09_TypeDef; //Pin 9

typedef enum
{
  TVP_P27_INTREQ           = 0x00,  /*!< INTREQ (default)  */
  TVP_P27_GPCL             = 0x01,  /*!< GPCL or VBLK      */
}TVP_P27_TypeDef; //Pin 27

typedef enum
{
  TVP_P24_VSYNC            = 0x00,  /*!< VSYNC (default)   */
  TVP_P24_PALI             = 0x01,  /*!< PALI              */
  TVP_P24_LOCK             = 0x02,  /*!< Lock indicator    */
}TVP_P24_TypeDef; //Pin 24

typedef enum
{
  TVP_P23_FID              = 0x00,  /*!< FID                */
  TVP_P23_GLCO             = 0x01,  /*!< GLCO (default)     */
  TVP_P23_LOCK             = 0x02,  /*!< Lock indicator     */
}TVP_P23_TypeDef; //Pin 24

typedef struct
{
	TVP_P09_TypeDef pin9;
	TVP_P27_TypeDef pin27;
	TVP_P24_TypeDef pin24;
	TVP_P23_TypeDef pin23;
	uint8_t VAL;
}TVP_Pins_StructTypeDef; //Pins config structure

typedef struct
{
	uint8_t Contrast;  //0..128(default)..255
	int8_t Hue;        //-180..0(default)..180
	uint8_t Saturation;  //0..128(default)..255
	uint8_t Brightness;  //0..128(default)..255
}TVP_IC_StructTypeDef; //Image config structure

typedef struct
{
	bool VBKO;      //VBKO (pin 27): 0 - GPLC (default); 1 - VBKL
	bool GPLC;      //0 - (default)
	bool GPLC_Mode; //0 - GPLC input (default); 1 - GPLC output
	bool HVLK;      //0 - PALI (default); 1 - HLK
	bool YUV;       //0 - high impendance (default); 1 - active
	bool HSYNK;     //HSYNK, VSYNK: 0 - high impendance (default); 1 - active
	bool VBLK;      //Vertical blanking: 0 - off (default); 1 - onn
	bool SCLK;      //0 - high impendance; 1 - active (default)
	uint8_t VAL;
}TVP_SMC_StructTypeDef; //MiscellaneousControls structure

#define		TVP_WRITE_ADDRESS 0xB8 //I2CSEL = 0
//#define	TVP_WRITE_ADDRESS 0xBA //I2CSEL = 1
#define		TVP_READ_ADDRESS 0xB9 //I2CSEL = 0
//#define	TVP_READ_ADDRESS 0xBB //I2CSEL = 1

#define TVP_Addr_InputSource 0x0					 //*
#define TVP_Addr_AnalogChannelControls 0x1 //*
#define TVP_Addr_OperatingModeControls 0x2 //*
#define TVP_Addr_MiscellaneousControls 0x3 //*
#define TVP_Addr_AutoswitchMask 0x4
#define TVP_Addr_SoftwareReset 0x5
#define TVP_Addr_ColorKillerControl 0x6
#define TVP_Addr_LuminanceControl1 0x7
#define TVP_Addr_LuminanceControl2 0x8
#define TVP_Addr_BrightnessControl 0x9     //*
#define TVP_Addr_SaturationControl 0x0A    //*
#define TVP_Addr_HueControl 0x0B           //*
#define TVP_Addr_ContrastControl 0x0C      //*
#define TVP_Addr_OutputAndRatesSelect 0x0D
#define TVP_Addr_LuminanceControl3 0x0E
#define TVP_Addr_PinsConfig 0x0F           //*
#define TVP_Addr_ActiveVideoCropingStartMSB 0x11
#define TVP_Addr_ActiveVideoCropingStartLSB 0x12
#define TVP_Addr_ActiveVideoCropingStopMSB 0x13
#define TVP_Addr_ActiveVideoCropingStopLSB 0x14
#define TVP_Addr_Genlock 0x15
#define TVP_Addr_HorisontalSynkStart 0x16
#define TVP_Addr_VerticalBlankingStart 0x18
#define TVP_Addr_VerticalBlankingStop 0x19
#define TVP_Addr_CrominanceControl1 0x1A
#define TVP_Addr_CrominanceControl2 0x1B
#define TVP_Addr_InterruptResetRegisterB 0x1C
#define TVP_Addr_InterruptEnableRegisterB 0x1D
#define TVP_Addr_InterruptConfigRegisterB 0x1E
#define TVP_Addr_VideoStandart 0x28

#define TVP_Addr_DeviceMSB 0x80            //*//Only read
#define TVP_Addr_DeviceLSB 0x81            //*
#define TVP_Addr_ROMVersion 0x82           //*
#define TVP_Addr_RAMVersion 0x83 					 //*
#define TVP_Addr_VerticalLineCountMSB 0x84 //*
#define TVP_Addr_VerticalLineCountLSB 0x85 //*

#define TVP_Addr_InterruptStatusRegisterB 0x86
#define TVP_Addr_InterruptActiveRegisterB 0x87
#define TVP_Addr_StatusRegister1 0x88
#define TVP_Addr_StatusRegister2 0x89
#define TVP_Addr_StatusRegister3 0x8A      //*
#define TVP_Addr_StatusRegister4 0x8B      //*
#define TVP_Addr_StatusRegister5 0x8C

#define TVP_Addr_ClosedCaptionData1 0x90
#define TVP_Addr_ClosedCaptionData2 0x91
#define TVP_Addr_ClosedCaptionData3 0x92
#define TVP_Addr_ClosedCaptionData4 0x93
#define TVP_Addr_WSS_Data1 0x94
#define TVP_Addr_WSS_Data2 0x95
#define TVP_Addr_WSS_Data3 0x96
#define TVP_Addr_WSS_Data4 0x97
#define TVP_Addr_WSS_Data5 0x98
#define TVP_Addr_WSS_Data6 0x99
#define TVP_Addr_VPS_Data01 0x9A
#define TVP_Addr_VPS_Data02 0x9B
#define TVP_Addr_VPS_Data03 0x9C
#define TVP_Addr_VPS_Data04 0x9D
#define TVP_Addr_VPS_Data05 0x9E
#define TVP_Addr_VPS_Data06 0x9F
#define TVP_Addr_VPS_Data07 0x0A1
#define TVP_Addr_VPS_Data08 0x0A2
#define TVP_Addr_VPS_Data09 0x0A3
#define TVP_Addr_VPS_Data10 0x0A4
#define TVP_Addr_VPS_Data11 0x0A5
#define TVP_Addr_VPS_Data12 0x0A6
#define TVP_Addr_VITC_Data01 0x0A7
#define TVP_Addr_VITC_Data02 0x0A8
#define TVP_Addr_VITC_Data03 0x0A9
#define TVP_Addr_VITC_Data04 0x0A7
#define TVP_Addr_VITC_Data05 0x0AA
#define TVP_Addr_VITC_Data06 0x0AB
#define TVP_Addr_VITC_Data07 0x0AC
#define TVP_Addr_VITC_Data08 0x0AD
#define TVP_Addr_VITC_Data09 0x0AE
#define TVP_Addr_VITC_Data10 0x0AF
#define TVP_Addr_VBI_FIFO 0x0B0

#define TVP_Addr_TeletextFilet11 0x0B1  //read write
#define TVP_Addr_TeletextFilet12 0x0B2
#define TVP_Addr_TeletextFilet13 0x0B3
#define TVP_Addr_TeletextFilet14 0x0B4
#define TVP_Addr_TeletextFilet15 0x0B5
#define TVP_Addr_TeletextFilet21 0x0B6
#define TVP_Addr_TeletextFilet22 0x0B7
#define TVP_Addr_TeletextFilet23 0x0B8
#define TVP_Addr_TeletextFilet24 0x0B9
#define TVP_Addr_TeletextFilet25 0x0BA

void TVP_Init(void);

void TVP_Write(uint8_t addr, uint8_t data);
uint8_t TVP_Read(uint8_t addr);

void TVP_SetInputSource(TVP_CS_TypeDef ChanelSource);
TVP_CS_TypeDef TVP_GetInputSource(void);

void TVP_SetAnalogChannelControls(TVP_ACC_TypeDef OffsetControl, TVP_ACC_TypeDef GainControl);
void TVP_GetAnalogChannelControls(TVP_ACC_StructTypeDef *res);

void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO);
void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res);

void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res);
void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res);

void TVP_InitImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfigA(uint8_t Brightness, uint8_t Contrast, uint8_t Saturation, int8_t Hue);
void TVP_GetImageConfig(TVP_IC_StructTypeDef *cfg);

void TVP_InitPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_SetPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_GetPinsConfig(TVP_Pins_StructTypeDef *pins);

void TVP_SetVideoStandart(TVP_VS_TypeDef VideoStandart);
TVP_VS_TypeDef TVP_GetVideoStandart(void);

void TVP_GetInfo(TVP_Info_StructTypeDef *res);
void TVP_GetStatus(TVP_Status_StructTypeDef *res);

#endif /*__ tvp5150_H */

