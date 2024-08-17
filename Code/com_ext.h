//*********************************************************************************************
//                                        Com_ext.h
//*********************************************************************************************


#ifndef __COM_EXT__
#define __COM_EXT__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "gpio_control.h"
#include "systick.h"

#include "MAP_TX_AI_to_CPU.h"
#include "MAP_RX_AI_from_CPU.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
// Transmit buffer (number of bytes in package)
#define TX_BUF_SIZE						ToCPU_Length


#define TX_BUF_START 					ToCPU_Sign_a
#define TX_BUF_SIGN						ToCPU_Sign_a
#define TX_BUF_LENGTH					ToCPU_LengthData_a

#define T_NO_MAX						150
#define T_NO_MIN						5
#define T1_RX							15//20	//
#define T2_RX							20//350	//
#define T3_RX							30//150	//


// Analog data
#define TX_UI_CHNL 						ToCPU_AD_Ua_a
#define TX_I_AH							ToCPU_AD_Ian_a
#define TX_I_BH							ToCPU_AD_Ibn_a
#define TX_I_CH							ToCPU_AD_Icn_a
#define TX_I_AK							ToCPU_AD_Iak_a
#define TX_I_BK							ToCPU_AD_Ibk_a
#define TX_I_CK							ToCPU_AD_Ick_a
#define TX_I_0							ToCPU_AD_3Io_a
#define TX_U_A							ToCPU_AD_Ua_a
#define TX_U_B							ToCPU_AD_Ub_a
#define TX_U_C							ToCPU_AD_Uc_a
#define TX_U_0							ToCPU_AD_3Uo_a
#define TX_U_F							ToCPU_AD_Uf_a
#define TX_U_AB							ToCPU_ADtmp_Uab_a
#define TX_U_BC							ToCPU_ADtmp_Ubc_a
#define TX_U_CA							ToCPU_ADtmp_Uca_a
#define TX_I_DA							ToCPU_ADtmp_Ida_a
#define TX_I_DB							ToCPU_ADtmp_Idb_a
#define TX_I_DC							ToCPU_ADtmp_Idc_a

#define TX_I_1H							ToCPU_ADtmp_I1n_a
#define TX_I_2H							ToCPU_ADtmp_I2n_a
#define TX_I_21H						ToCPU_ADtmp_I2divI1n_a	
#define TX_I_1K							ToCPU_ADtmp_I1k_a
#define TX_I_2K							ToCPU_ADtmp_I2k_a
#define TX_I_21K						ToCPU_ADtmp_I2divI1k_a	
#define TX_U_1							ToCPU_ADtmp_U1_a	
#define TX_U_2							ToCPU_ADtmp_U2_a	

#define TX_I_TA							ToCPU_ADtmp_Ita_a	
#define TX_I_TB							ToCPU_ADtmp_Itb_a	
#define TX_I_TC							ToCPU_ADtmp_Itc_a	

#define TX_ANGL_IA_UBC					ToCPU_ADtmp_aIaUbc_a	
#define TX_ANGL_IB_UCA					ToCPU_ADtmp_aIbUca_a	
#define TX_ANGL_IC_UAB					ToCPU_ADtmp_aIcUab_a	
#define TX_ANGL_I0_U0					ToCPU_ADtmp_a3Io3Uo_a	

#define TX_P							ToCPU_ADtmp_P_a	
#define TX_Q							ToCPU_ADtmp_Q_a	
#define TX_S							ToCPU_ADtmp_S_a	
#define TX_COSPHI						ToCPU_ADtmp_Cos_f_a	

#define TX_U_BNN						ToCPU_ADtmp_Ubnn_a	
#define TX_DELTA_IH						ToCPU_ADtmp_dIn_a
#define TX_F							ToCPU_AD_F_a
#define TX_OVERHEAT						ToCPU_AD_kHeat_a
#define TX_TYPE_KZ						ToCPU_AD_Damage_a


#define TX_TIME							ToCPU_DT_Date_a						// 8 bytes
#define TX_BLCK							ToCPU_Info_a						// 1 bytes
#define TX_CMPR							ToCPU_Compar_a						// 5 bytes
#define TX_STATUS						ToCPU_Status_a						// 1 byte

#define TX_ADD_DAT						ToCPU_AddData_a	
#define TX_OSC							TX_ADD_DAT							// 69 byte max
#define TX_VER							TX_ADD_DAT							// 
#define TX_CLBR							TX_ADD_DAT							// 
#define TX_CRC							ToCPU_CS_a							// 1 byte




#define TX_YEAR							TX_TIME	
#define TX_MONTH						(TX_TIME+1)
#define TX_MDAY							(TX_TIME+2)
#define TX_HOUR							(TX_TIME+3)
#define TX_MIN							(TX_TIME+4)
#define TX_SEC							(TX_TIME+5)
#define TX_MLSEC						(TX_TIME+6)



// for comand 0xa5
#define TX_OSC_NUM						TX_OSC								// 1 byte
#define TX_OSC_POINT_NUM				(TX_OSC+1)							// 2 bytes
#define TX_OSC_POINT_1					(TX_OSC+3)							// 22 bytes
#define TX_OSC_POINT_2					(TX_OSC+3+CHNL_MESR*2)				// 24 bytes
#define TX_OSC_POINT_3					(TX_OSC+3+CHNL_MESR*4)				// 24 bytes
#define TX_OSC_CRC						(TX_OSC+3+CHNL_MESR*6)				// 1 byte

// for comand 0xa7
#define TX_VER_0						TX_VER			// 1 byte
#define TX_VER_1						(TX_VER+1)		// 1 byte
#define TX_VER_2						(TX_VER+2)		// 1 byte
#define TX_VER_3						(TX_VER+3)							// 1 byte
#define TX_VER_4						(TX_VER+4)							// 1 byte
#define TX_VER_CRC						(TX_VER+5)							// 1 byte


// for comand 0xa9
#define TX_CLBR_COM						(TX_CLBR+0)
#define TX_CLBR_COEF					(TX_CLBR+1)
#define TX_CLBR_ZRLV					(TX_CLBR+1+2*CHNL_MESR)
#define TX_CLBR_CRC						(TX_CLBR+1+4*CHNL_MESR)		// 1 byte

// for comand 0xc1
#define TX_FRMW_CURBLK_H				(TX_BUF_START+2)
#define TX_FRMW_CURBLK_L				(TX_BUF_START+3)
#define TX_FRMW_ERR						(TX_BUF_START+2)




// Recieve buffer (number of bytes in package)
#define RX_BUF_SIZE						ToAI_Length

#define RX_BUF_START 					0
#define RX_STATE 						ToAI_StatusToAI_a	// 1 bytes
#define RX_COMAND 						ToAI_Command_a		// 1 byte
#define RX_PACK 						ToAI_Data_a			// 

// for comand 0xa1
#define RX_YEAR							RX_PACK	
#define RX_MONTH						(RX_PACK+1)
#define RX_MDAY							(RX_PACK+2)
#define RX_HOUR							(RX_PACK+3)
#define RX_MIN							(RX_PACK+4)
#define RX_SEC							(RX_PACK+5)
#define RX_TIME_CRC 					(RX_PACK+6)		

// for comand 0xa2
#define RX_CLBR_CHAN					(RX_PACK+0)		// 1 byte
#define RX_CLBR_CRC						(RX_PACK+1)		// 1 byte

// for comand 0xa3
#define RX_SET_BLCK0_SZ					(ToAI_Length - 6)
#define RX_SET_BLCK1_SZ					21
#define RX_SET_BLCK2_SZ					18
#define RX_SET_BLCK_NUM					(RX_PACK+0)
#define RX_SET_BLCK_LEN					(RX_PACK+1)
#define RX_SET_DATA						(RX_PACK+2)

// for comand 0xa4
#define RX_WR_OSC_NUM 					(RX_PACK+0)		// 1 byte
#define RX_WR_OSC_LNG_H 				(RX_PACK+1)		// 1 byte
#define RX_WR_OSC_LNG_L 				(RX_PACK+2)		// 1 byte
#define RX_WR_OSC_CRC 					(RX_PACK+3)		// 1 byte

// for comand 0xa5
#define RX_RD_OSC_NUM 					(RX_PACK+0)		// 1 byte
#define RX_RD_OSC_PNT_H 				(RX_PACK+1)		// 1 byte
#define RX_RD_OSC_PNT_L 				(RX_PACK+2)		// 1 byte
#define RX_RD_OSC_CRC 					(RX_PACK+3)		// 1 byte

// for comand 0xa6
#define RX_ERASE_CRC					(RX_PACK+0)

// for comand 0xa7
#define RX_VER_CRC						(RX_PACK+0)

// for comand 0xa8
#define RX_OFF_CRC						(RX_PACK+0)

// for comand 0xa9
#define RX_CLBRTX_CRC					(RX_PACK+0)


// for comand 0xc1
#define RX_FRMW_STT						(RX_PACK+0)

#define RX_FRMW_CURBLK_H				(RX_PACK+1)
#define RX_FRMW_CURBLK_L				(RX_PACK+2)

#define RX_FRMW_LNG_3					(RX_PACK+1)
#define RX_FRMW_LNG_2					(RX_PACK+2)
#define RX_FRMW_LNG_1					(RX_PACK+3)
#define RX_FRMW_LNG_0					(RX_PACK+4)

#define RX_FRMW_BLK_H					(RX_PACK+5)
#define RX_FRMW_BLK_L					(RX_PACK+6)

#define RX_FRMW_CRC_L					(RX_PACK+7)
#define RX_FRMW_CRC_H					(RX_PACK+8)

#define RX_FRMW_DAT						(RX_PACK+3)
#define FRMW_DAT_BLCK_LEN				128
#define FRMW_SERV_DAT					(RX_FRMW_DAT+1)	// amount of service-bytes: 0..5, 6 - command, 7 - ID, 8..9 - block number (10 bytes) + contr.sum. at the end of packet (1 byte)


//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
//                                  Function's prototypes
//----------------------------------------------------------------------------------------------
uint32_t TxRxCpu(uint8_t *, uint8_t *, uint32_t *, uint8_t *,uint32_t *);

#endif
