//*********************************************************************************************
//                                        Calibr.h
//*********************************************************************************************

#ifndef __CALIBR__
#define __CALIBR__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "flash.h"
#include "com_ext.h"
#include "adc_ext.h"
#include "oper_val.h"
#include "mem_adr.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
//                                          Macros
//---------------------------------------------------------------------------------------------
//Systick control
#define STOP_SYSTICK()	    	SysTick->CTRL &= (uint32_t)0xFFFFFFFE
#define START_SYSTICK()   		SysTick->CTRL |= (uint32_t)0x00000001


//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef enum {
	FIN_CLBR = 0,
	START_CLBR,
} clbr_stt_t;


typedef struct {
	clbr_stt_t	clbr_stt;							// calibration status
	uint8_t 	cur_clbr_chan;						// current calibrated channel number
	uint16_t 	clbr_coef[CHNL_MESR];				// current values of calibration coefficients for every channel
	uint16_t 	zero_level[CHNL_MESR];				// current values of zero level for every channel
	uint16_t 	crc;								// CRC for calibration coefficients & zero level values
	uint32_t	tx_clbr_ready;						// FlagStatus that indicates packet with calibration data is ready
} clbr_stts_t;





//----------------------------------------------------------------------------------------------
//                                    Function's prototypes
//----------------------------------------------------------------------------------------------
void Calibrate(sample_t, spectr_t *, clbr_stts_t *, uint8_t *);
void ReadCalibrCoef(clbr_stts_t *);
void StartTxCalibr(uint8_t *, clbr_stts_t *);
void CorrectVect(spectr_t *, clbr_stts_t *, spectr_t *);
void CorrectPhase(vect_t *, vect_t *);

#endif
