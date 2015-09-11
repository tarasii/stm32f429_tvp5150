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

#define TVP_Addr_InputSource 0x0
#define TVP_Addr_AnalogChannelControls 0x1
#define TVP_Addr_OperatingModeControls 0x2
#define TVP_Addr_MiscellaneousControls 0x3

void TVP_Init(void);

void TVP_SetInputSource(TVP_CS_TypeDef ChanelSource);
TVP_CS_TypeDef TVP_GetInputSource(void);

void TVP_SetAnalogChannelControls(TVP_ACC_TypeDef OffsetControl, TVP_ACC_TypeDef GainControl);
void TVP_GetAnalogChannelControls(TVP_ACC_StructTypeDef *res);

void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO);
void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res);

void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res);
void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res);

#endif /*__ tvp5150_H */

