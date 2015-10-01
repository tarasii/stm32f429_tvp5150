#ifndef __adxl345_H
#define __adxl345_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

typedef enum
{                      /*!< Output Data Rate (Hz)  Bandwidth (Hz)  */
  ADXL_DR_0_10 = 0x00, /*!<         0,1                0,05        */
  ADXL_DR_0_20 = 0x01, /*!<         0,2                0,1         */
  ADXL_DR_0_39 = 0x02, /*!<         0,39               0,2         */
  ADXL_DR_0_78 = 0x03, /*!<         0,78               0,39        */
  ADXL_DR_1_56 = 0x04, /*!<         1,56               0,78        */
  ADXL_DR_3_13 = 0x05, /*!<         3,13               1,56        */
  ADXL_DR_6_25 = 0x06, /*!<         6,25               3,13        */
  ADXL_DR_12_5 = 0x07, /*!<         12,5               6,25        */
  ADXL_DR_25   = 0x08, /*!<         25                 12,5        */
  ADXL_DR_50   = 0x09, /*!<         50                 25          */
  ADXL_DR_100  = 0x0A, /*!<         100                50          */
  ADXL_DR_200  = 0x0B, /*!<         200                100         */
  ADXL_DR_400  = 0x0C, /*!<         400                200         */
  ADXL_DR_800  = 0x0D, /*!<         800                400         */
  ADXL_DR_1600 = 0x0E, /*!<         1600               800         */
  ADXL_DR_3200 = 0x0F  /*!<         3200               1600        */
}ADXL_DR_TypeDef ;     // Rate configuration 

typedef enum
{                   /*!< Frequency (Hz)  */
  ADXL_WU_8 = 0x00, /*!<      8          */
  ADXL_WU_4 = 0x01, /*!<      4          */
  ADXL_WU_2 = 0x02, /*!<      2          */
  ADXL_WU_1 = 0x03  /*!<      1          */
}ADXL_WU_TypeDef ;  // Frequency of Readings in Sleep Mode 

typedef enum
{                     /*!< Range (g)        */
  ADXL_DFR_2  = 0x00, /*!<      ±2          */
  ADXL_DFR_4  = 0x01, /*!<      ±4          */
  ADXL_DFR_8  = 0x02, /*!<      ±8          */
  ADXL_DFR_16 = 0x03  /*!<      ±16         */
}ADXL_DFR_TypeDef ;   // Data format range  

typedef enum
{                         
  ADXL_FM_BYPASS  = 0x00, /*!< FIFO is bypassed  */
  ADXL_FM_FIFO    = 0x01, /*!< FIFO collects up to 32 values and then stops collecting data, collecting new data only when FIFO is not full. */
  ADXL_FM_STREAM  = 0x02, /*!< FIFO holds the last 32 data values. When FIFO is full, the oldest data is overwritten with newer data. */
  ADXL_FM_TRIGGER = 0x03  /*!< When triggered by the trigger bit, FIFO holds the last data samples before the trigger event and then continues to collect data until full. New data is collected only when FIFO is not full */
}ADXL_FM_TypeDef ;        // FIFO Modes  

typedef struct
{
	ADXL_DR_TypeDef RATE;   //
	bool LOWPOWER;      //
	uint8_t VAL;
}ADXL_DR_StructTypeDef; //   structure

typedef struct
{
	bool ACT_ACDC;   //
	bool ACT_X;      //
	bool ACT_Y;      //
	bool ACT_Z;      //
	bool INACT_ACDC; //
	bool INACT_X;    //
	bool INACT_Y;    //
	bool INACT_Z;    //
	uint8_t VAL;
}ADXL_AC_StructTypeDef; // Axis enable control  structure

typedef struct
{
	bool DATA_READY;  //
	bool SINGLE_TAP;  //
	bool DOUBLE_TAP;  //
	bool ACTIVITY;    //
	bool INACTIVITY;  //
	bool FREE_FALL;   //
	bool WATTERMARK;  //
	bool OVERRUN;     //
	uint8_t VAL;
}ADXL_IC_StructTypeDef; // Interrupt enable control structure

typedef struct
{
	bool SELF_TEST;  //
	bool SPI;        //
	bool INT_INVERT; //
	bool FULL_RES;   //
	bool JUSTIFY;    //
	ADXL_DFR_TypeDef RANGE;   //
	uint8_t VAL;
}ADXL_DF_StructTypeDef; // Data format control structure

typedef struct
{
	bool ACT_X;      //
	bool ACT_Y;      //
	bool ACT_Z;      //
	bool ASLEEP;     //
	bool TAP_X;      //
	bool TAP_Y;      //
	bool TAP_Z;      //
	uint8_t VAL;
}ADXL_ATS_StructTypeDef; // Act tap status  structure

typedef struct
{
	bool SUPRESS;   //
	bool TAP_X;     //
	bool TAP_Y;     //
	bool TAP_Z;     //
	uint8_t VAL;
}ADXL_TA_StructTypeDef; //   structure

typedef struct
{
	bool LINK;       //
	bool AUTO_SLEEP; //
	bool MEASURE;    //
	bool SLEEP;      //
	ADXL_WU_TypeDef WAKEUP;  //
	uint8_t VAL;
}ADXL_PS_StructTypeDef; //   structure

typedef struct
{
	bool FIFO_TRIG;   //
	ADXL_FM_TypeDef FIFO_MODE;  //
	uint8_t SAMPLES;  //
	uint8_t VAL;
}ADXL_FS_StructTypeDef; //   structure

typedef struct
{
	bool FIFO_TRIG;   //
	uint8_t ENTRIES;  //
	uint8_t VAL;
}ADXL_FC_StructTypeDef; //   structure

typedef struct
{
	uint16_t X;    //
	uint16_t Y;    //
	uint16_t Z;    //
}ADXL_XYZ_StructTypeDef; //   structure


//typedef enum
//{
//  ITG_         = 0x00, /*!<              */
//  ITG_         = 0x01, /*!<              */
//  ITG_         = 0x02, /*!<              */
//  ITG_         = 0x03  /*!<              */
//}ITG__TypeDef ; // 
//
//typedef struct
//{
//	__ __;               //
//	__ __;               //
//	__ __;         //
//	uint8_t VAL;
//}ITG__StructTypeDef; //   structure


//#define		ADXL_WRITE_ADDRESS 0x3A //ALT ADDRESS = 1
#define	ADXL_WRITE_ADDRESS 0xA6 //ALT ADDRESS = 0
//#define		ADXL_READ_ADDRESS 0x3B  //ALT ADDRESS = 1
#define	ADXL_READ_ADDRESS 0xA7  //ALT ADDRESS = 0

#define ADXL_Addr_DEVID          0x00 // r
#define ADXL_Addr_TAP_THRESH     0x1D // rw
#define ADXL_Addr_OFSX           0x1E //
#define ADXL_Addr_OFSY           0x1F //
#define ADXL_Addr_OFSZ           0x20 //
#define ADXL_Addr_TAP_DUR        0x21 //
#define ADXL_Addr_TAP_LATENT     0x22 //
#define ADXL_Addr_TAP_WINDOW     0x23 //
#define ADXL_Addr_ACT_THRESH     0x24 //
#define ADXL_Addr_INACT_THRESH   0x25 //
#define ADXL_Addr_INACT_TIME     0x26 //
#define ADXL_Addr_ACT_INACT_CTL  0x27 //
#define ADXL_Addr_FF_THRESH      0x28 //
#define ADXL_Addr_FF_TIME        0x29 // 
#define ADXL_Addr_TAP_AXES       0x2A // rw
#define ADXL_Addr_ACT_TAP_STATUS 0x2B // r
#define ADXL_Addr_BW_RATE        0x2C // rw
#define ADXL_Addr_POWER_CTL      0x2D //
#define ADXL_Addr_INT_ENABLE     0x2E //
#define ADXL_Addr_INT_MAP        0x2F // rw
#define ADXL_Addr_INT_SOURCE     0x30 // r
#define ADXL_Addr_DATA_FORMAT    0x31 // rw
#define ADXL_Addr_DATAX0         0x32 // r
#define ADXL_Addr_DATAX1         0x33 //
#define ADXL_Addr_DATAY0         0x34 //
#define ADXL_Addr_DATAY1         0x35 //
#define ADXL_Addr_DATAZ0         0x36 //
#define ADXL_Addr_DATAZ1         0x37 //
#define ADXL_Addr_FIFO_CTL       0x38 //* rw
#define ADXL_Addr_FIFO_STATUS    0x39 //* r
//#define ADXL_Addr_             0x00 //*


void ADXL_Init(void);
void ADXL_WriteByte(uint8_t addr, uint8_t data);
uint8_t ADXL_ReadByte(uint8_t addr);
uint8_t ADXL_GetDeviceId(void);
uint8_t ADXL_GetTapThreshold(void);
void ADXL_SetTapThreshold(uint8_t res);
uint8_t ADXL_GetX_Offset(void);
void ADXL_SetX_Offset(uint8_t res);
uint8_t ADXL_GetY_Offset(void);
void ADXL_SetY_Offset(uint8_t res);
uint8_t ADXL_GetZ_Offset(void);
void ADXL_SetZ_Offset(uint8_t res);
void ADXL_SetXYZ_Offset(uint8_t x, uint8_t y, uint8_t z);
uint8_t ADXL_GetTapDuration(void);
void ADXL_SetTapDuration(uint8_t res);
uint8_t ADXL_GetTapLatency(void);
void ADXL_SetTapLatency(uint8_t res);
uint8_t ADXL_GetTapWindow(void);
void ADXL_SetTapWindow(uint8_t res);
uint8_t ADXL_GetActivityThreshold(void);
void ADXL_SetActivityThreshold(uint8_t res);
uint8_t ADXL_GetInactivityThreshold(void);
void ADXL_SetInactivityThreshold(uint8_t res);
uint8_t ADXL_GetInactivityTime(void);
void ADXL_SetInactivityTime(uint8_t res);
void ADXL_GetAxisControl(ADXL_AC_StructTypeDef *res);
void ADXL_SetAxisControl(bool act_acdc, bool act_x, bool act_y, bool act_z, bool inact_acdc, bool inact_x, bool inact_y, bool inact_z);
uint8_t ADXL_GetFreeFallThreshold(void);
void ADXL_SetFreeFallThreshold(uint8_t res);
uint8_t ADXL_GetFreeFallTime(void);
void ADXL_SetFreeFallTime(uint8_t res);
void ADXL_GetTapAxis(ADXL_TA_StructTypeDef *res);
void ADXL_SetTapAxis(bool supress, bool tap_x, bool tap_y, bool tap_z);
void ADXL_GetActTapStatus(ADXL_ATS_StructTypeDef *res);
void ADXL_GetDataRatePowerMode(ADXL_DR_StructTypeDef *res);
void ADXL_SetDataRatePowerMode(bool low_power, ADXL_DR_TypeDef rate);
void ADXL_GetPowerSaving(ADXL_PS_StructTypeDef *res);
void ADXL_SetPowerSaving(bool link, bool auto_sleep, bool measure, bool sleep, ADXL_WU_TypeDef wakeup);
void ADXL_GetIntConfig(ADXL_IC_StructTypeDef *res);
void ADXL_SetIntConfig(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun);
void ADXL_GetIntMap(ADXL_IC_StructTypeDef *res);
void ADXL_SetIntMap(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun);
void ADXL_GetIntSource(ADXL_IC_StructTypeDef *res);
void ADXL_SetIntSource(bool data_ready, bool single_tap, bool double_tap, bool activity, bool inactivity, bool free_fall, bool watermark, bool overrun);
void ADXL_GetDataFormat(ADXL_DF_StructTypeDef *res);
void ADXL_SetDataFormat(bool self_test, bool spi, bool int_invert, bool full_res, bool justify, ADXL_DFR_TypeDef range);
void ADXL_SelfTest(void);
uint16_t ADXL_GetX(void);
uint16_t ADXL_GetY(void);
uint16_t ADXL_GetZ(void);
void ADXL_GetXYZ(ADXL_XYZ_StructTypeDef *res);
void ADXL_GetFIFO_Status(ADXL_FC_StructTypeDef *res);
void ADXL_GetFIFO_Control(ADXL_FS_StructTypeDef *res);
void ADXL_SetFIFO_Control(ADXL_FM_TypeDef fifo_mode, bool trigger, uint8_t samples);
	


//Taras Ivaniv

#endif /*__ adxl345_H */
