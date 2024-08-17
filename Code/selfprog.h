//*********************************************************************************************
//                                        Selfprog.h
//*********************************************************************************************


#ifndef __SELFPROG__
#define __SELFPROG__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "mem_adr.h"
#include "com_ext.h"
#include "ram_ext.h"
#include "flash.h"
#include "led.h"
#include "user_types.h"
//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef enum {
	CMND_C0 = 0,
	CMND_C1,
	CHECK_FW_IN_SRAM,
	FINALIZE,
} fw_stage_t;


typedef struct {
	uint8_t 	get_upd;
	fw_stage_t	upd_stage;
	uint8_t		step;
	uint8_t 	wr_mark_flag;
	uint8_t 	err;
	uint16_t 	cur_blk_num;
	uint16_t 	blk_amount;
	uint16_t	cur_crc;
	uint16_t	cntr_crc;
	uint16_t	full_crc;
	uint32_t 	cur_sram_adr;
	uint32_t 	fw_size;
	uint8_t 	wr_buf[128];
	uint8_t 	rd_buf[128];
	uint32_t 	debug_field;
	uint8_t 	ai_type_shft;
} firmw_upd_t;


//---------------------------------------------------------------------------------------------
//                                          Macros
//---------------------------------------------------------------------------------------------
#define INIT_FIRMW_UPDATE(x)	   	x.get_upd = 0x0f; 					\
									x.upd_stage = CMND_C0; 				\
									x.step = 0

#define CONT_FIRMW_UPDATE(x)	   	x.upd_stage = CMND_C1; 				\
									x.step = 0

#define INIT_FIRMW_CHECK(x)	   		x.upd_stage = CHECK_FW_IN_SRAM; 	\
									x.cur_sram_adr = ADR_FIRMW_STRG;	\
									x.step = 0

#define FIN_FIRMW_UPDATE(x)	   		x.upd_stage = FINALIZE; 			\
									x.wr_mark_flag = 0x0f;				\
									x.step = 0


//----------------------------------------------------------------------------------------------
//                                  Function's prototypes
//----------------------------------------------------------------------------------------------
uint16_t CalcCRC16(uint8_t * , uint32_t, uint16_t);
uint8_t CommandProcessFw(uint32_t, uint8_t *, firmw_upd_t *);
void FirmwUpdate(uint32_t *, uint8_t *, uint32_t *, uint8_t *, firmw_upd_t *);
uint8_t SearchAiType(uint8_t *);


#endif

