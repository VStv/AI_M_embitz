//*********************************************************************************************
//                                        Mem_adr.h
//*********************************************************************************************

#ifndef __MEM_ADR__
#define __MEM_ADR__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define MAX_OSC_AMOUNT				36																// Maximum amount of oscillogram storing in external SRAM   35

#define FMWR_RECEIVED				(uint16_t)0x1234		//0x5a3c
#define FMWR_LOADED					(uint16_t)0x5678		//0x3c5a


//-------------------- FLASH ROM addresses ----------------------
#define ADR_START_FLASH	   			(uint32_t)0x08000000            								// Address start Flash memory MC
#define FLASH_PAGE_SIZE				(uint32_t)0x00000800											// 0x400
#define LAST_PAGE_NUM				127																// 63
#define FLASH_ADR_USER_APP  		(uint32_t)0x08002000             								// Address in Flash memory MC  user application sector

// page with firmware update data (126)
#define ADR_FMWR_MARKS_PAGE_FLASH   (uint32_t)(ADR_START_FLASH + (LAST_PAGE_NUM-1)*FLASH_PAGE_SIZE)	// 

#define ADR_FRMW_FULL_CRC   		ADR_FMWR_MARKS_PAGE_FLASH  										// (uint16_t)
#define ADR_FRMW_CUR_CRC			(uint32_t)(ADR_FRMW_FULL_CRC + 0x02)            				// (uint16_t)
#define ADR_FRMW_CNTR_CRC			(uint32_t)(ADR_FRMW_FULL_CRC + 0x04)            				// (uint16_t)
#define ADR_FRMW_LAST_CRC   		(uint32_t)(ADR_FRMW_FULL_CRC + 0x06)            				// (uint16_t)
#define ADR_FRMW_ERROR   			(uint32_t)(ADR_FRMW_FULL_CRC + 0x0a)            				// (uint16_t)

#define ADR_FRMW_LEN_BLCK			(uint32_t)(ADR_FRMW_FULL_CRC + 0x10)            				// (uint32_t)
#define ADR_FRMW_LEN_BYTE   		(uint32_t)(ADR_FRMW_FULL_CRC + 0x1a)            				// (uint32_t)
#define ADR_FMWR_RECEIVED_MARK		(uint32_t)(ADR_FMWR_MARKS_PAGE_FLASH + 0x20)					// (uint16_t)
#define ADR_FMWR_LOADED_MARK		(uint32_t)(ADR_FMWR_RECEIVED_MARK + 0x02)						// (uint16_t)
#define ADR_BOOT_VERS  				(uint32_t)(ADR_FMWR_MARKS_PAGE_FLASH + 0x2e)     				// (uint16_t)
#define IN_FW_UPD_SAVE_AREA_VOL  	(uint32_t)0x30      											// 

// page with calibration data (127)
#define ADR_LAST_PAGE_FLASH   		(uint32_t)(ADR_START_FLASH + LAST_PAGE_NUM*FLASH_PAGE_SIZE)		// 
#define IN_CALIB_SAVE_AREA_VOL  	(uint32_t)(2*(2*CHNL_MESR + 1))     												// Address in Flash memory MC
	
#define MAX_FRMW_SIZE				(ADR_FMWR_MARKS_PAGE_FLASH - FLASH_ADR_USER_APP)				// Address in Flash memory MC  user application sector


//-------------------- SRAM addresses ----------------------
#define END_ADR_SRAM        		(uint32_t)0x000FFFFF											// Maximum address of external SRAM
#define END_ADR_OSC					(uint32_t)(END_ADR_SRAM)										// Maximum address of oscillogram area in external SRAM (- CHNL_AMOUNT*2)
#define START_ADR_OSC				(uint32_t)(END_ADR_OSC - MAX_OSC_AMOUNT*1200*CHNL_MESR*2 + 1)	// Start address of oscillogram area in external SRAM										(0x00002Å00)
#define START_ADR_OSC_NUM_STRGE		(uint32_t)(uint32_t)0x00000C00									// Start address of oscillogram numbers storage area in external SRAM (MAX_OSC_AMOUNT*1) 	(0x00000C00)
#define END_ADR_OSC_NUM_STRGE		(uint32_t)(START_ADR_OSC_NUM_STRGE + MAX_OSC_AMOUNT - 1)		// End address of oscillogram numbers storage area in external SRAM (1)
#define ADR_PRESENCE_OSC_FLAG		(uint32_t)(END_ADR_OSC_NUM_STRGE + 1)							// Address in external SRAM where flag of oscillogram presence stores (1)					(0x00000C24)
#define ADR_STRGE_CUR_REC_ADR		(uint32_t)(ADR_PRESENCE_OSC_FLAG + 1)							// Address in external SRAM where current recording oscillogram address stores (4)			(0x00000C25)
#define ADR_CUR_NUM_OSC				(uint32_t)(ADR_STRGE_CUR_REC_ADR + 4)							// Address in external SRAM where current recording oscillogram number stores (1)			(0x00000C29)
#define START_ADR_OSC_ADR_STRGE		(uint32_t)(ADR_CUR_NUM_OSC + 1)									// Start address of oscillogram address storage area (MAX_OSC_AMOUNT*4)						(0x00000C2A)
#define START_ADR_OSC_LEN_STRGE		(uint32_t)(START_ADR_OSC_ADR_STRGE + MAX_OSC_AMOUNT*4)			// Start address of oscillogram length storage area (MAX_OSC_AMOUNT*2)						(0x00000CBA)

#define ADR_THERMAL_STATE			(uint32_t)(START_ADR_OSC_LEN_STRGE + MAX_OSC_AMOUNT*2)			// Address of thermal state area (16 bytes)													(0x00000D02)
#define ADR_OFF_TIME				(uint32_t)(ADR_THERMAL_STATE + 16)								// Address of data that contains switch-off time (4 bytes)									(0x00000D12)
#define ADR_OFF_MARKER				(uint32_t)(ADR_OFF_TIME + 4)									// Address of marker that marks switch-off event (1 byte)									(0x00000D16)



#define ADR_FIRMW_STRG				(uint32_t)(0x00000400)											// Address in external SRAM where  stores (1)												
#define MAX_FIRMW_LENGTH			MAX_FRMW_SIZE													//
#define ADR_FIRMW_LENGTH			(uint32_t)(ADR_FIRMW_STRG + MAX_FIRMW_LENGTH + 16)				// Adress in external SRAM where  stores (1)
#define ADR_FIRMW_CRC				(uint32_t)(ADR_FIRMW_LENGTH + 4)								// Adress in external SRAM where  stores (1)



#endif
