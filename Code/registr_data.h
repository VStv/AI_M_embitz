//*********************************************************************************************
//                                     Registr_data.h
//*********************************************************************************************

#ifndef __REGISTR_DATA__
#define __REGISTR_DATA__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "adc_ext.h"
#include "ram_ext.h"
#include "com_ext.h"
#include "mem_adr.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define PREREC_BUF_SIZE				600UL											// Prerecord buffer size
#define RECORDS_AT_1SEC				1200UL											// Amount of records at 1 sec
#define MIN_REC_TIME				1000UL											// Min. record time (1000 msec)


//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef struct {
	uint16_t 	buffer[PREREC_BUF_SIZE][CHNL_MESR];
	uint32_t 	index;
	uint32_t 	enable;
} prerec_t;


typedef enum {
	NO_REC = 0,
	REC_OSC,
} rec_ctrl_t;


typedef enum {
	NO_OUT = 0,
	OUT_OSC,
} out_ctrl_t;


typedef enum {
	NO_OSC = 0,
	OSC_PRES,
} osc_pres_t;


typedef struct {
	rec_ctrl_t 	rec_st;								// recordind status
	uint32_t 	remain_2nd_part;					// how many bytes remain to write to 2nd part of SRAM array
	uint32_t 	remain_1st_part;					// how many bytes remain to write to 1st part of SRAM array
	uint32_t 	cur_adr_2nd_p;						// current adress in external SRAM where data next time can be written to (2nd part of SRAM array)
	uint32_t 	cur_adr_1st_p;						// current adress in external SRAM where data next time can be written to (1st part of SRAM array)
	uint8_t 	cur_osc_num;						// current oscillogram number 				(uint32_t)
	uint32_t	cur_osc_num_adr;					// adress of current oscillogram number 
	uint8_t 	num_store[MAX_OSC_AMOUNT];			// oscillogram numbers storage area in MCU RAM

	osc_pres_t 	osc_pres_st;						// oscillogram presence status
	out_ctrl_t 	out_st;								// oscillogram output status
	uint32_t 	rqst_osc_num;						// number of request oscillogram 
	uint32_t	rqst_osc_adr;						// start adress of request oscillogram 
	uint16_t	rqst_point_num;						// point number of request oscillogram 
//	uint8_t 	nothing3;							// 											(uint16_t)
} osc_stts_t;


//----------------------------------------------------------------------------------------------
//                                    Function's prototypes
//----------------------------------------------------------------------------------------------
void PrerecDat(sample_t *, prerec_t *);
void RecordingOsc(sample_t *, prerec_t *, osc_stts_t *, uint8_t *);
void StartRecOsc(uint8_t *, uint8_t *, osc_stts_t *);
void InitRecOsc(osc_stts_t *);
void ReadingOsc(osc_stts_t *, uint8_t *);
void StartReadOsc(uint8_t *, uint8_t *, osc_stts_t *);
void ErasingOsc(osc_stts_t *);
void Resize16to8(uint16_t *,uint8_t *, uint32_t);


#endif

