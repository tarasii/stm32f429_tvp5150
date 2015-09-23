#ifndef __tvp5150_H
#define __tvp5150_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"


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
	bool AutoInit;
	bool AutoClock;
	uint8_t VAL;
}TVP_AI_StructTypeDef; //Automatic Initialization

typedef struct
{
	bool Field1;
	bool Field2;
	uint8_t LineNumber;
	uint8_t VAL;
}TVP_LNI_StructTypeDef; //Line Number Interrupt

typedef struct
{
	uint16_t DeviceId;
	uint8_t ROM;
	uint8_t RAM;
	uint16_t VerticalLineCount;
}TVP_Info_StructTypeDef; //Info structure

typedef enum
{
  TVP_NoCopyProtection      = 0x00,  /*!<No copy protection                                        */
  TVP_AGC_PseudoSyncs       = 0x01,  /*!<AGC pulses/pseudo-syncs present                           */
  TVP_LPG_PseudoSyncs_2     = 0x02,  /*!<AGC pulses/pseudo-syncs and 2-line color striping present */
  TVP_LPG_PseudoSyncs_4     = 0x03,  /*!<AGC pulses/pseudo-syncs and 4-line color striping present */
}TVP_MD_TypeDef; //Macrovision detection

typedef struct
{
	bool PeakWhiteDetect;     //Peak white detect status: 0 - is not detected; 1 - Peak white is detected.
	bool LineAlternating;     //Line-alternating status: 0 - nonline alternating; 1 - line alternating
	bool FieldRate;           //Field rate status: 0 - 60 Hz; 1 - 50 Hz
	bool LostLock;            //Lost lock detect: 0 - No lost lock since status register #1 was last read; 1 - Lost lock since status register #1 was last read.
	bool ColorSubcarrierLock; //Color subcarrier lock status: 0 - is not locked; 1 - is locked
	bool VerticalSyncLock;    //Vertical sync lock: 0 - is not locked; 1 - is locked
	bool HorizontalSyncLock;  //Horizontal sync lock: 0 - is not locked; 1 - is locked.
	bool TV_VCR;              //0 - TV;1 - VCR
	uint8_t VAL1;
	bool WeakSignalDetection; //Weak signal detection: 0 - No weak signal; 1 - Weak signal mode
	bool PAL_SwitchPolarity;  //PAL switch polarity of first line of odd field: 0 - PAL switch is 0; 1 - PAL switch is 1
	bool FieldSequence;       //Field sequence status: 0 - Even field; 1 - Odd field
	bool AGC_AndOffsetFrozen; //AGC and offset frozen status: 0 - AGC and offset are not frozen; 1 - AGC and offset are frozen.
	TVP_MD_TypeDef MacrovisionDetection; //Macrovision detection
	uint8_t VAL2;
	uint8_t AGC;
	uint8_t SCH;
	bool AutoswitchMode;      //Autoswitch mode: 0 - Stand-alone (forced video standard) mode; 1 - Autoswitch mode
	TVP_VS_TypeDef VideoStandard;
	bool SamplingRate;        //Sampling rate (SR): 0 - Reserved; 1 - ITU-R BT.601
	uint8_t VAL3;
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

typedef enum
{
  TVP_AUTO                 = 0x00,  /*!< (default)               */
  TVP_Enabled              = 0x02,  /*!<       */
  TVP_Disabled             = 0x03,  /*!<      */
}TVP_CK_TypeDef; //Color killer

typedef struct
{
	TVP_CK_TypeDef ColorKiller;
	uint8_t Theshold;
	uint8_t VAL;
}TVP_CK_StructTypeDef; //Color killer structure

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
	uint8_t Contrast;    //0..128(default)..255
	int8_t Hue;          //-180..0(default)..180
	uint8_t Saturation;  //0..128(default)..255
	uint8_t Brightness;  //0..128(default)..255
}TVP_IC_StructTypeDef; //Image config structure

typedef struct
{
	bool palm;        //1(default)
	bool paln;        //1(default)
	bool n443;        //1(default)
	uint8_t VAL;      
}TVP_ASM_StructTypeDef; //Autoswitch Mask

typedef enum
{
  TVP_LSD_0                 = 0x00,  /*!< (default)               */
  TVP_LSD_Plus1             = 0x01,  /*!<       */
  TVP_LSD_Plus2             = 0x02,  /*!<       */
  TVP_LSD_Plus3             = 0x03,  /*!<       */
  TVP_LSD_Plus4             = 0x04,  /*!<       */
  TVP_LSD_Plus5             = 0x05,  /*!<       */
  TVP_LSD_Plus6             = 0x06,  /*!<       */
  TVP_LSD_Plus7             = 0x07,  /*!<       */
  TVP_LSD_Minus1            = 0x08,  /*!<       */
  TVP_LSD_Minus2            = 0x09,  /*!<       */
  TVP_LSD_Minus3            = 0x0A,  /*!<       */
  TVP_LSD_Minus4            = 0x0B,  /*!<       */
  TVP_LSD_Minus5            = 0x0C,  /*!<       */
  TVP_LSD_Minus6            = 0x0D,  /*!<       */
  TVP_LSD_Minus7            = 0x0E,  /*!<       */
  TVP_LSD_Minus8            = 0x0F,  /*!<       */
}TVP_LSD_TypeDef; //luminance signal dellay

typedef enum
{
  TVP_LPG_0                 = 0x00,  /*!< (default)               */
  TVP_LPG_05                = 0x01,  /*!<       */
  TVP_LPG_1                 = 0x02,  /*!<       */
  TVP_LPG_3                 = 0x03,  /*!<       */
}TVP_LPG_TypeDef; //Peaking gain

typedef enum
{
  TVP_LFS_NO                = 0x00,  /*!< (default)               */
  TVP_LFS_Notch1            = 0x01,  /*!<       */
  TVP_LFS_Notch2            = 0x02,  /*!<       */
  TVP_LFS_Notch3            = 0x03,  /*!<       */
}TVP_LFS_TypeDef; //Luminance filter stop band bandwidth

typedef struct
{
	bool BypassMode;         //Luma bypass mode: 0 (default) - bypass the chroma trap and comb filters; 1 - bypass the whole luma processing
	bool NoPedetal;          //Pedestal on the analog video input signal: 0 (default) - present; 1 -  not present
	bool NoRawHeader;        //656 ancillary headers for raw data: 0 - insert; 1 (default) - disabled
	bool VertBlanckBypass;   //Luminance bypass during vertical blanking: 0 (default) - disabled; 1 - enabled
	TVP_LSD_TypeDef SignalDelay; //Luminance signal delay with respect to chrominance signal
	bool Filter;             //Luminance filter: 0 (default) - comb filter; 1 - chroma trap filter
	TVP_LPG_TypeDef PeakingGain; //Peaking gain: 0 (default)
	TVP_LFS_TypeDef FilterStopBand; //Luminance filter stop band bandwidth (MHz): 0 (default)
	uint8_t VAL1;      
	uint8_t VAL2;      
	uint8_t VAL3;      
}TVP_LC_StructTypeDef; //LuminanceControl

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

typedef enum
{
  TVP_YOF_YUV            = 0x00,  /*!< 4:2:2 YUV               */
  TVP_YOF_ITU            = 0x07,  /*!< ITU-R BT.656  (default) */
}TVP_YOF_TypeDef; //YUV output format

typedef enum
{
  TVP_YUD_Normal         = 0x00,  /*!< Normal            (default)   */
  TVP_YUD_Filter         = 0x01,  /*!< Digital composite output pins connected to decimation filter output, decoder function bypassed, 
	                                data output alternately as Y and UV buses at the SCLK rate  */
  TVP_YUD_AD             = 0x02,  /*!< YUV output pins connected to A/D output, decoder function bypassed, data output at SCLK rate  */
}TVP_YUD_TypeDef; //YUV data path bypass

typedef struct
{
	bool YUV_CodeRange;               //YUV output code range: 0 - ITU-R BT.601 ; 1 (default) - Extended
	bool UV_CodeFormat;               //UV code format 0(default) - Offset binary; 1 - Straight binary
	TVP_YUD_TypeDef YUV_Data;         //YUV data path bypass: 0 (default)
	TVP_YOF_TypeDef YUV_OutputFormat; //YUV output format: 7 (default)
	uint8_t VAL;
}TVP_OAR_StructTypeDef; //Outputs and Data Rates Select structure

typedef struct
{
	int16_t Start;    //Active Video Cropping Start Pixel: -512..0(default)..511
	int16_t Stop;     //Active Video Cropping Stop Pixel; -512..0(default)..511
	bool AVID;        //AVID out active in VBLK: 0 (default) - active; 1 - inactive
	uint8_t VAL1;
	uint8_t VAL2;
	uint8_t VAL3;
	uint8_t VAL4;
}TVP_AVC_StructTypeDef; //Active Video Croping structure

typedef struct
{
	bool CDTO_LSB;      //CDTO_LSB_Switch (CDTO_SW) forced to: 0; 1 (default)
	bool GLCO_RTC;      //GLCO/RTC: 1 - GLCO; 0 (default) - RTC
	uint8_t VAL;
}TVP_SG_StructTypeDef; //Genlock and RTC Register structure

typedef struct
{
	int8_t start;               
	int8_t stop;               
}TVP_VB_StructTypeDef; //Vertical Blanking structure

typedef enum
{
  TVP_ACGC_Enabled             = 0x00,  /*!< (default)               */
  TVP_ACGC_Disabled            = 0x02,  /*!<       */
  TVP_ACGC_Previous            = 0x03,  /*!<       */
}TVP_ACGC_TypeDef; //Automatic color gain control

typedef enum
{
  TVP_CCFM_3_121_4_2    = 0x00,  /*!< 3-line (1, 2, 1)/4 and 2-line comb filter                */
  TVP_CCFM_3_121_4      = 0x01,  /*!< 3-line (1, 2, 1)/4 comb filter (default NTSC)            */
  TVP_CCFM_3_101_2_2    = 0x02,  /*!< 3-line (1, 0, 1)/2 comb filter and 2-line comb filter    */
  TVP_CCFM_3_101_2      = 0x03,  /*!< 3-line (1, 0, 1)/2 comb filter and no comb filte         */
  TVP_CCFM_4_1111_4_2   = 0x04,  /*!< 4-line (1, 1, 1, 1)/4 and 2-line comb filter                       */
  TVP_CCFM_4_1111_4     = 0x05,  /*!< 4-line (1, 1, 1, 1)/4 comb filter and no comb filter (default PAL)  */
  TVP_CCFM_4_1331_4_2   = 0x06,  /*!< 4-line (1, 3, 3, 1)/8 comb filter and 2-line comb filter            */
  TVP_CCFM_4_1331_4     = 0x07,  /*!< 4-line (1, 3, 3, 1)/8 comb filter and no comb filter     */
  TVP_CCFM_2_2          = 0x08,  /*!< 2-line comb filter                                       */
  TVP_CCFM_2            = 0x0F,  /*!< 2-line comb filter                                       */
}TVP_CCFM_TypeDef; //Chrominance comb filter mode

typedef struct
{
	bool ColorPLL_Reset;             //Color PLL: 0 - not reset; 1 (default) - reset               
	bool CE;                         //Chrominance comb filter (CE): 0 - disable; 1 (default) - enable          
	bool ACE;                        //Chrominance adaptive comb filter (ACE): 0 - not disable; 1 (default) - enable          
	TVP_ACGC_TypeDef ACGC;           //Automatic color gain control (ACGC): 0 (default) - enabled         
	TVP_CCFM_TypeDef CombFilterMode; //Chrominance comb filter mode: 0 (default) - enabled         
	bool WCF;                        //Wideband chroma filter (WCF): 0 - disable; 1 (default) - enable          
	TVP_LFS_TypeDef FilterSelect;    //Chrominance filter select: 0 (default)
	uint8_t VAL1;
	uint8_t VAL2;
}TVP_CC_StructTypeDef; //Chrominance Control structure

typedef struct
{
	bool SoftwareInit;            
	bool MacrovisionDetect;          
	bool CommandReady;
	bool FieldRate;
	bool LineAlternation;       
	bool ColorLock;
	bool HV_Lock;
	bool TV_VCR;	
	uint8_t VAL;
}TVP_INTB_StructTypeDef; //Interrupt Register B structure

typedef struct
{
	bool YUV;            
	bool InterruptA;          
	bool Polaryty;
	uint8_t VAL;
}TVP_INTA_Conf_StructTypeDef; //Interrupt Register A structure

typedef struct
{
	bool LockState;            
	bool Lock;          
	bool CycleComplete;
	bool BusError;
	bool FIFO_Threshold;       
	bool Line;
	bool Data;	
	uint8_t VAL;
}TVP_INTA_StructTypeDef; //Interrupt Register A structure


typedef struct
{
	bool FIFO_FullError;            
	bool FIFO_Empty;          
	bool Teletext;
	bool CC_Field1;
	bool CC_Field2;       
	bool WSS;
	bool WPS;
	bool VITC;	
	uint8_t VAL;
}TVP_VDP_StructTypeDef; //VDP Status structure

typedef enum
{
  TVP_LFM_WST_PAL_B   = 0x01,  /*!< WST PAL B  */
  TVP_LFM_WST_PAL_C   = 0x02,  /*!< WST PAL C  */
  TVP_LFM_WST_NTSC    = 0x03,  /*!< WST NTSC   */
  TVP_LFM_NABTS_NTSC  = 0x04,  /*!< NABTS NTSC */
  TVP_LFM_TTX_NTSC    = 0x05,  /*!< TTX NTSC   */
  TVP_LFM_CC_PAL      = 0x06,  /*!< CC PAL     */
  TVP_LFM_CC_NTSC     = 0x07,  /*!< CC NTSC    */
  TVP_LFM_WSS_PAL     = 0x08,  /*!< WSS PAL    */
  TVP_LFM_WSS_NTSC    = 0x09,  /*!< WSS NTSC   */
  TVP_LFM_VITC_PAL    = 0x0A,  /*!< VITC PAL   */
  TVP_LFM_VITC_NTSC   = 0x0B,  /*!< VITC NTSC  */
  TVP_LFM_VPS_PAL     = 0x0C,  /*!< VPS PAL    */
  TVP_LFM_Custom1     = 0x0D,  /*!< Custom 1   */
  TVP_LFM_Custom2     = 0x0E,  /*!< Custom 2   */
  TVP_LFM_ActiveVideo = 0x0F,  /*!< Active video (VDP off) (default) */
}TVP_LFM_TypeDef; //Line Mode

typedef struct
{
	bool NullFiltering;  //Filtering of null bytes in closed caption modes: 0 - disabled; 1 (default) - enabled          
	bool SendVBI;        //Send VBI data: 0 - to registers only; 1 (default) - FIFO and the registers        
	bool ErrorVBI;       //VBI data with errors in the FIFO: 0 - allow; 1 (default) - do not allow
	bool ErroCorrection; //Error detection and correction: 0 - do not enable; 1 (default) - enable (when bits [3:0] = 1 2, 3, and 4 only)
  TVP_LFM_TypeDef Mode;
	uint8_t VAL;
}TVP_LFM_StructTypeDef; //Line Mode structure

typedef enum
{
  TVP_TTC_NOR  = 0x00,  /*!< NOR (default)  */
  TVP_TTC_NAND = 0x01,  /*!< NAND  */
  TVP_TTC_OR   = 0x02,  /*!< OR    */
  TVP_TTC_AND  = 0x03,  /*!< AND   */
}TVP_TTC_TypeDef; //Filter logic

typedef struct
{
	bool Mode;             //0 - Teletext WST PAL mode B (2 header bytes) (default); 1 - Teletext NABTS NTSC mode C (5 header bytes)       
	bool TeletextFilter2;  //Teletext filter 2 enable: 0 = Disabled (default); 1 = Enable     
	bool TeletextFilter1;  //Teletext filter 2 enable: 0 = Disabled (default); 1 = Enable
  TVP_TTC_TypeDef FilterLogic;
	uint8_t VAL;
}TVP_TTC_StructTypeDef; //Line Mode structure

#define		TVP_WRITE_ADDRESS 0xB8 //I2CSEL = 0
//#define	TVP_WRITE_ADDRESS 0xBA //I2CSEL = 1
#define		TVP_READ_ADDRESS 0xB9  //I2CSEL = 0
//#define	TVP_READ_ADDRESS 0xBB  //I2CSEL = 1

#define TVP_Addr_InputSource                0x00 //*
#define TVP_Addr_AnalogChannelControls      0x01 //*
#define TVP_Addr_OperatingModeControls      0x02 //*
#define TVP_Addr_MiscellaneousControls      0x03 //*
#define TVP_Addr_AutoswitchMask             0x04 //*
#define TVP_Addr_SoftwareReset              0x05 //*
#define TVP_Addr_ColorKillerControl         0x06 //*
#define TVP_Addr_LuminanceControl1          0x07 //*
#define TVP_Addr_LuminanceControl2          0x08 //*
#define TVP_Addr_BrightnessControl          0x09 //*
#define TVP_Addr_SaturationControl          0x0A //*
#define TVP_Addr_HueControl                 0x0B //*
#define TVP_Addr_ContrastControl            0x0C //*
#define TVP_Addr_OutputAndRatesSelect       0x0D //*
#define TVP_Addr_LuminanceControl3          0x0E //*
#define TVP_Addr_PinsConfig                 0x0F //*
#define TVP_Addr_ActiveVideoCropingStartMSB 0x11 //*
#define TVP_Addr_ActiveVideoCropingStartLSB 0x12 //*
#define TVP_Addr_ActiveVideoCropingStopMSB  0x13 //*
#define TVP_Addr_ActiveVideoCropingStopLSB  0x14 //*
#define TVP_Addr_Genlock                    0x15 //*
#define TVP_Addr_HorisontalSynkStart        0x16 //*
#define TVP_Addr_VerticalBlankingStart      0x18 //*
#define TVP_Addr_VerticalBlankingStop       0x19 //*
#define TVP_Addr_CrominanceControl1         0x1A //*
#define TVP_Addr_CrominanceControl2         0x1B //*
#define TVP_Addr_InterruptB_Reset           0x1C //*
#define TVP_Addr_InterruptB_Enable          0x1D //*
#define TVP_Addr_InterruptB_Config          0x1E //*
#define TVP_Addr_VideoStandart              0x28 //*

#define TVP_Addr_DeviceMSB                  0x80 //* //Only read
#define TVP_Addr_DeviceLSB                  0x81 //*
#define TVP_Addr_ROMVersion                 0x82 //*
#define TVP_Addr_RAMVersion                 0x83 //*
#define TVP_Addr_VerticalLineCountMSB       0x84 //*
#define TVP_Addr_VerticalLineCountLSB       0x85 //*

#define TVP_Addr_InterruptB_Status          0x86 //*
#define TVP_Addr_InterruptB_Active          0x87 //*
#define TVP_Addr_StatusRegister1            0x88 //*
#define TVP_Addr_StatusRegister2            0x89 //*
#define TVP_Addr_StatusRegister3            0x8A //*
#define TVP_Addr_StatusRegister4            0x8B //*
#define TVP_Addr_StatusRegister5            0x8C //*

#define TVP_Addr_ClosedCaptionData1 0x90 //*
#define TVP_Addr_ClosedCaptionData2 0x91
#define TVP_Addr_ClosedCaptionData3 0x92
#define TVP_Addr_ClosedCaptionData4 0x93
#define TVP_Addr_WSS_Data1     0x094 //*
//#define TVP_Addr_WSS_Data2   0x095
//#define TVP_Addr_WSS_Data3   0x096
//#define TVP_Addr_WSS_Data4   0x097
//#define TVP_Addr_WSS_Data5   0x098
//#define TVP_Addr_WSS_Data6   0x099
#define TVP_Addr_VPS_Data01    0x09A //*
//#define TVP_Addr_VPS_Data02  0x09B
//#define TVP_Addr_VPS_Data03  0x09C
//#define TVP_Addr_VPS_Data04  0x09D
//#define TVP_Addr_VPS_Data05  0x09E
//#define TVP_Addr_VPS_Data06  0x09F
//#define TVP_Addr_VPS_Data07  0x0A1
//#define TVP_Addr_VPS_Data08  0x0A2
//#define TVP_Addr_VPS_Data09  0x0A3
//#define TVP_Addr_VPS_Data10  0x0A4
//#define TVP_Addr_VPS_Data11  0x0A5
//#define TVP_Addr_VPS_Data12  0x0A6
#define TVP_Addr_VITC_Data01   0x0A7 //*
//#define TVP_Addr_VITC_Data02 0x0A8
//#define TVP_Addr_VITC_Data03 0x0A9
//#define TVP_Addr_VITC_Data04 0x0A7
//#define TVP_Addr_VITC_Data05 0x0AA
//#define TVP_Addr_VITC_Data06 0x0AB
//#define TVP_Addr_VITC_Data07 0x0AC
//#define TVP_Addr_VITC_Data08 0x0AD
//#define TVP_Addr_VITC_Data09 0x0AE
//#define TVP_Addr_VITC_Data10 0x0AF
#define TVP_Addr_VBI_FIFO     0x0B0 //*

#define TVP_Addr_TeletextFilter11      0x0B1 //* //read write
//#define TVP_Addr_TeletextFilter12    0x0B2
//#define TVP_Addr_TeletextFilter13    0x0B3
//#define TVP_Addr_TeletextFilter14    0x0B4
//#define TVP_Addr_TeletextFilter15    0x0B5
//#define TVP_Addr_TeletextFilter21    0x0B6
//#define TVP_Addr_TeletextFilter22    0x0B7
//#define TVP_Addr_TeletextFilter23    0x0B8
//#define TVP_Addr_TeletextFilter24    0x0B9
//#define TVP_Addr_TeletextFilter25    0x0BA
#define TVP_Addr_TeletextFilterControl 0x0BB //*

#define TVP_Addr_InterruptA_Status    0x0C0 //*
#define TVP_Addr_InterruptA_Enable    0x0C1 //* 
#define TVP_Addr_InterruptA_Config    0x0C2 //*  

#define TVP_Addr_VDP_Conf_RAM_Data       0x0C3 //*
#define TVP_Addr_VDP_Conf_RAM_AddressLSB 0x0C4 //*
#define TVP_Addr_VDP_Conf_RAM_AddressMSB 0x0C5 //*
#define TVP_Addr_VDP_Status              0x0C6 //*
#define TVP_Addr_FIFO_WordCount          0x0C7 //*
#define TVP_Addr_FIFO_InterruptThreshold 0x0C8 //*
#define TVP_Addr_FIFO_Reset              0x0C9 //*
#define TVP_Addr_LineNumberInterrupt     0x0CA //*
#define TVP_Addr_PixelAlignmentLSB       0x0CB //*
#define TVP_Addr_PixelAlignmentMSB       0x0CC //*
#define TVP_Addr_FIFO_OutputControl      0x0CD //*
#define TVP_Addr_AutomaticInitialization 0x0CE //*
#define TVP_Addr_FullFieldEnable         0x0CF //*
#define TVP_Addr_LineModeStart           0x0D0 //*
#define TVP_Addr_LineModeEnd             0x0FB //*
#define TVP_Addr_FullFieldMode           0x0FC //*


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

void TVP_SetAutoswitchMask(bool paln, bool palm, bool ntsc443);
void TVP_GetAutoswitchMask(TVP_ASM_StructTypeDef *res);

void TVP_SoftwareReset(void);

void TVP_SetColorKillerControl(TVP_CK_TypeDef colorKiller, uint8_t theshold);
void TVP_GetColorKillerControl(TVP_CK_StructTypeDef *res);

void TVP_SetLuminanceControl(TVP_LC_StructTypeDef *res);
void TVP_GetLuminanceControl(TVP_LC_StructTypeDef *res);

void TVP_SetOutputAndRates(TVP_OAR_StructTypeDef *res);
void TVP_GetOutputAndRates(TVP_OAR_StructTypeDef *res);

void TVP_InitImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfigA(uint8_t Brightness, uint8_t Contrast, uint8_t Saturation, int8_t Hue);
void TVP_GetImageConfig(TVP_IC_StructTypeDef *cfg);

void TVP_InitPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_SetPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_GetPinsConfig(TVP_Pins_StructTypeDef *pins);

void TVP_SetActiveVideoCroping(TVP_AVC_StructTypeDef *res);
void TVP_GetActiveVideoCroping(TVP_AVC_StructTypeDef *res);

void TVP_SetGenlock(bool CDTO_LSB, bool GLCO_RTC);
void TVP_GetGenlock(TVP_SG_StructTypeDef *res);

void TVP_SetHorizontalSyncStart(uint8_t HSYNC);
uint8_t TVP_GetHorizontalSyncStart(void);

void TVP_SetVerticalBlanking(TVP_VB_StructTypeDef *res);
void TVP_GetVerticalBlanking(TVP_VB_StructTypeDef *res);

void TVP_SetChrominanceControl(TVP_CC_StructTypeDef *res);
void TVP_GetChrominanceControl(TVP_CC_StructTypeDef *res);

void TVP_SetVideoStandart(TVP_VS_TypeDef VideoStandart);
TVP_VS_TypeDef TVP_GetVideoStandart(void);

void TVP_SetInterruptB_Reset(TVP_INTB_StructTypeDef *res);
void TVP_GetInterruptB_Reset(TVP_INTB_StructTypeDef *res);
void TVP_SetInterruptB_Enable(TVP_INTB_StructTypeDef *res);
void TVP_GetInterruptB_Enable(TVP_INTB_StructTypeDef *res);
void TVP_SetInterruptB_Polarity(bool res);
bool TVP_GetInterruptB_Polarity(void);
void TVP_GetInterruptB_Status(TVP_INTB_StructTypeDef *res);
bool TVP_GetInterruptB_Active(void);

void TVP_GetInfo(TVP_Info_StructTypeDef *res);
void TVP_GetStatus(TVP_Status_StructTypeDef *res);

void TVP_SetFullFieldEnabled(bool res);
bool TVP_GetFullFieldEnabled(void);
uint8_t TVP_GetFIFO_WordCount(void);
void TVP_SetFIFO_InterruptThreshold(uint8_t res);
uint8_t TVP_GetFIFO_InterruptThreshold(void);
void TVP_FIFO_Reset(uint8_t res);
void TVP_SetFIFO_OutputControl(bool res);
bool TVP_GetFIFO_OutputControl(void);

void TVP_SetAutomaticInit(bool auto_init, bool auto_clock);
void TVP_GetAutomaticInit(TVP_AI_StructTypeDef *res);

void TVP_SetPixelAlignment(uint16_t addr);
uint16_t TVP_GetPixelAlignment(void);

void TVP_SetLineNumberInterrupt(bool field1, bool field2, uint8_t line_num);
void TVP_GetLineNumberInterrupt(TVP_LNI_StructTypeDef *res);

void TVP_SetVDP_Conf(uint16_t addr, uint8_t data);
uint8_t TVP_GetVDP_Conf(uint16_t addr);
void TVP_SetVDPStatus(TVP_VDP_StructTypeDef *res);
void TVP_GetVDPStatus(TVP_VDP_StructTypeDef *res);

void TVP_SetInterruptA_Config(TVP_INTA_Conf_StructTypeDef *res);
void TVP_GetInterruptA_Config(TVP_INTA_Conf_StructTypeDef *res);
void TVP_SetInterruptA_Enable(TVP_INTA_StructTypeDef *res);
void TVP_GetInterruptA_Enable(TVP_INTA_StructTypeDef *res);
void TVP_SetInterruptA_Status(TVP_INTA_StructTypeDef *res);
void TVP_GetInterruptA_Status(TVP_INTA_StructTypeDef *res);

void TVP_SetLineMode(uint8_t line_num, TVP_LFM_StructTypeDef *res);
void TVP_GetLineMode(uint8_t line_num, TVP_LFM_StructTypeDef *res);
void TVP_SetFieldMode(TVP_LFM_StructTypeDef *res);
void TVP_GetFieldMode(TVP_LFM_StructTypeDef *res);

uint8_t TVP_GetWSS_Data(uint8_t num);
uint8_t TVP_GetVPS_Data(uint8_t num);
uint8_t TVP_GetVITC_Data(uint8_t num);
uint8_t TVP_GetClosedCapture_Data(uint8_t num);
uint8_t TVP_GetVBI_FIFO_Data(void);

void TVP_SetTeletextFilterControl(TVP_TTC_StructTypeDef *res);
void TVP_GetTeletextFilterControl(TVP_TTC_StructTypeDef *res);

void TVP_PowerDown(void);

//Taras Ivaniv

#endif /*__ tvp5150_H */

