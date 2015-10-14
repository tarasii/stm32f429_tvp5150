#ifndef __hmc5883_H
#define __hmc5883_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
#include "cmtypes.h"

typedef enum
{                     /*!< Output Data Rate (Hz)  */
  HMC_DR_0_75 = 0x00, /*!<         0,1            */
  HMC_DR_1_5  = 0x01, /*!<         0,2            */
  HMC_DR_3    = 0x02, /*!<         0,39           */
  HMC_DR_7_5  = 0x03, /*!<         0,78           */
  HMC_DR_15   = 0x04, /*!<         15 (default)   */
  HMC_DR_30   = 0x05, /*!<         30             */
  HMC_DR_75   = 0x06  /*!<         75             */
}HMC_DR_TypeDef ;     // Rate configuration 

typedef enum
{                   
  HMC_MM_Normal   = 0x00, /*!< Normal measurement configuration (default) */
  HMC_MM_Positive = 0x01, /*!< Positive bias configuration for X and Y axes, negative bias configuration for Z axis */
  HMC_MM_Negative = 0x02  /*!< Negative bias configuration for X and Y axes, positive bias configuration for Z axis */
}HMC_MM_TypeDef ;         // Measurement Modes

typedef enum
{                   
  HMC_MR_CMM   = 0x00, /*!< Continuous-Measurement Mode       */
  HMC_MR_SMM   = 0x01, /*!< Single-Measurement Mode (default) */
  HMC_MR_IDLE  = 0x02, /*!< Idle Mode                         */
  HMC_MR_SLEEP = 0x03  /*!< Sleep Mode                        */
}HMC_MR_TypeDef ;      // Modes

typedef enum
{                    /*!< Sensor Input Field Range      Gain  */
  HMC_GS_0_9 = 0x00, /*!<        ± 0.9 Ga               1280  */
  HMC_GS_1_2 = 0x01, /*!<        ± 1.2 Ga (default)     1024  */
  HMC_GS_1_9 = 0x02, /*!<        ± 1.9 Ga               768   */
  HMC_GS_2_5 = 0x03, /*!<        ± 2.5 Ga               614   */
  HMC_GS_4_0 = 0x04, /*!<        ± 4.0 Ga               415   */
  HMC_GS_4_6 = 0x05, /*!<        ± 4.6 Ga               361   */
  HMC_GS_5_5 = 0x06, /*!<        ± 5.5 Ga               307   */
  HMC_GS_7_9 = 0x07  /*!<        ± 7.9 Ga               219   */
}HMC_GS_TypeDef ;    // Gain settings 

typedef struct
{
	HMC_DR_TypeDef RATE; //
	HMC_MM_TypeDef MODE; //
	HMC_GS_TypeDef GAIN; //
	uint8_t VAL1;
	uint8_t VAL2;
}HMC_CF_StructTypeDef; //  Configuration structure

typedef struct
{
	bool REN; //
	bool LOCK; //
	bool RDY; //
	uint8_t VAL;
}HMC_SR_StructTypeDef; //  Status structure

typedef struct
{
	uint8_t VALA;
	uint8_t VALB;
	uint8_t VALC;
}HMC_ID_StructTypeDef; //  Status structure

//typedef struct
//{
//	int16_t X;    //
//	int16_t Y;    //
//	int16_t Z;    //
//}HMC_XYZ_StructTypeDef; //   structure


#define	HMC_WRITE_ADDRESS 0x3C 
#define	HMC_READ_ADDRESS  0x3D  

#define HMC_Addr_ConfA      0x00 //* rw
#define HMC_Addr_ConfB      0x01 //* rw
#define HMC_Addr_Mode       0x02 //* rw
#define HMC_Addr_X_MSB      0x03 // r
#define HMC_Addr_X_LSB      0x04 // r
#define HMC_Addr_Z_MSB      0x05 // r
#define HMC_Addr_Z_LSB      0x06 // r
#define HMC_Addr_Y_MSB      0x07 // r
#define HMC_Addr_Y_LSB      0x08 // r
#define HMC_Addr_Status     0x09 // r
#define HMC_Addr_IdentA     0x0A // r
#define HMC_Addr_IdentB     0x0B // r
#define HMC_Addr_IdentC     0x0C // r
//#define HMC_Addr_             0x00 //*

DEV_Result_t HMC_Init(HMC_MR_TypeDef mode, HMC_DR_TypeDef rate, HMC_MM_TypeDef moder, HMC_GS_TypeDef gain);
void HMC_WriteByte(uint8_t addr, uint8_t data);
uint8_t HMC_ReadByte(uint8_t addr);
void HMC_Get_Configuration(HMC_CF_StructTypeDef *res);
void HMC_Set_Configurarion(HMC_DR_TypeDef rate, HMC_MM_TypeDef mode, HMC_GS_TypeDef gain);
HMC_MR_TypeDef HMC_Get_Mode(void);
void HMC_Set_MODE(HMC_MR_TypeDef mode);
int16_t HMC_GetX(void);
int16_t HMC_GetY(void);
int16_t HMC_GetZ(void);
void HMC_GetXYZ(XYZ_t *res);
void HMC_GetStatus(HMC_SR_StructTypeDef *res);
void HMC_GetId(HMC_ID_StructTypeDef *res);
DEV_Result_t HMC_TestConnection(void);

//Taras Ivaniv

#endif /*__ hmc5883_H */
