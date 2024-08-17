//*********************************************************************************************
//                                        Protect.h
//*********************************************************************************************


#ifndef __PROTECT__
#define __PROTECT__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "oper_val.h"
#include "MAP_for_setpoints.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define	PROTECT_AMOUNT				(LAST_cmp)
#define	MTZ_AMOUNT					(MTZ_4_cmp-MTZ_1_cmp+1)
#define	TIMER_AMOUNT				MTZ_AMOUNT


#define	T_PREEMERG					50	// 50 ms

#define	ZMN_F_ON					1
#define	ZMN_L_ON					2
#define	ZMN_U1_ON					3
#define	ZPN_U2_ON					4
#define	ZPN_L_ON					3
#define	ZNZ_ON						4
#define	U2_MAX_ON					5
#define	U1_MIN_ON					6

#define	COS_L_ON					1
#define	COS_C_ON					2
#define	COS_LC_ON					3

#define	EN_POTEN					1
#define	EN_BEFORE_ACK				2

#define	EN_F_MAX					1
#define	EN_F_MIN					2

#define	IH_ON						1
#define	IK_ON						2

//#define	BY_I2						0
//#define	BY_I2_I1					1

#define	FWRD_ON						1
#define	RVRS_ON						2

#define	BLOCK_DIR_ON				1
#define	BLOCK_RAB_ON				2

#define	LOGIC_AND					0
#define	LOGIC_OR 					1


#define	MTZ_1_state					(ToAI_ToAI_b_LockMTZ1_bit)
#define	MTZ_2_state					(ToAI_ToAI_b_LockMTZ2_bit)
#define	MTZ_3_state					(ToAI_ToAI_b_LockMTZ3_bit)
#define	MTZ_4_state					(ToAI_ToAI_b_LockMTZ4_bit)
#define	RPO_state					(ToAI_ToAI_b_RPO_bit)
#define	NCEVO_state					(ToAI_ToAI_b_NCV_bit)
#define	DN_state					(ToAI_ToAI_b_DN_bit)
#define	ACK_state					(ToAI_ToAI_b_KVT_bit)
#define	DI_BNN1_state				(ToAI_ToAI_b_BNN1DI_bit)
#define	DI_BNN2_state				(ToAI_ToAI_b_BNN2DI_bit)
#define	TRUE_state					(ToAI_ToAI_b_ToAITrue_bit)


#define	_MTZ_1_byte					(MTZ_1_state/8 + ToAI_ToAI_b_a)
#define	_MTZ_2_byte					(MTZ_2_state/8 + ToAI_ToAI_b_a)
#define	_MTZ_3_byte					(MTZ_3_state/8 + ToAI_ToAI_b_a)
#define	_MTZ_4_byte					(MTZ_4_state/8 + ToAI_ToAI_b_a)
#define	_RPO_byte					(RPO_state/8 + ToAI_ToAI_b_a)
#define	_NCEVO_byte					(NCEVO_state/8 + ToAI_ToAI_b_a)
#define	_DN_byte					(DN_state/8 + ToAI_ToAI_b_a)
#define	_ACK_byte					(ACK_state/8 + ToAI_ToAI_b_a)
#define	_DI_BNN1_byte				(DI_BNN1_state/8 + ToAI_ToAI_b_a)
#define	_DI_BNN2_byte				(DI_BNN2_state/8 + ToAI_ToAI_b_a)
#define	_TRUE_byte					(TRUE_state/8 + ToAI_ToAI_b_a)


#define	_MTZ_1_bit					(MTZ_1_state - 8*(_MTZ_1_byte - ToAI_ToAI_b_a))
#define	_MTZ_2_bit					(MTZ_2_state - 8*(_MTZ_2_byte - ToAI_ToAI_b_a))
#define	_MTZ_3_bit					(MTZ_3_state - 8*(_MTZ_3_byte - ToAI_ToAI_b_a))
#define	_MTZ_4_bit					(MTZ_4_state - 8*(_MTZ_4_byte - ToAI_ToAI_b_a))
#define	_RPO_bit					(RPO_state - 8*(_RPO_byte - ToAI_ToAI_b_a))
#define	_NCEVO_bit					(NCEVO_state - 8*(_NCEVO_byte - ToAI_ToAI_b_a))
#define	_DN_bit						(DN_state - 8*(_DN_byte - ToAI_ToAI_b_a))
#define	_ACK_bit					(ACK_state - 8*(_ACK_byte - ToAI_ToAI_b_a))
#define	_DI_BNN1_bit				(DI_BNN1_state - 8*(_DI_BNN1_byte - ToAI_ToAI_b_a))
#define	_DI_BNN2_bit				(DI_BNN2_state - 8*(_DI_BNN2_byte - ToAI_ToAI_b_a))
#define	_TRUE_bit					(TRUE_state - 8*(_TRUE_byte - ToAI_ToAI_b_a))



#define	COMP_MTZ_1_MASK				(uint32_t)(1<<MTZ_1_cmp)
#define	COMP_MTZ_2_MASK				(uint32_t)(1<<MTZ_2_cmp)
#define	COMP_MTZ_3_MASK				(uint32_t)(1<<MTZ_3_cmp)
#define	COMP_MTZ_4_MASK				(uint32_t)(1<<MTZ_4_cmp)
#define	COMP_MTZ_1T_MASK			(uint32_t)(1<<MTZ_1T_cmp)
#define	COMP_MTZ_2T_MASK			(uint32_t)(1<<MTZ_2T_cmp)
#define	COMP_MTZ_3T_MASK			(uint32_t)(1<<MTZ_3T_cmp)
#define	COMP_MTZ_4T_MASK			(uint32_t)(1<<MTZ_4T_cmp)
#define	COMP_KAM_1_MASK				(uint32_t)(1<<KAM_1_cmp)
#define	COMP_KAM_2_MASK				(uint32_t)(1<<KAM_2_cmp)
#define	COMP_KAM_3_MASK				(uint32_t)(1<<KAM_3_cmp)
#define	COMP_ZNZ_1_MASK				(uint32_t)(1<<ZNZ_1_cmp)
#define	COMP_ZNZ_2_MASK				(uint32_t)(1<<ZNZ_2_cmp)
#define	COMP_ZNZ_3_MASK				(uint32_t)(1<<ZNZ_3_cmp)
#define	COMP_OBR_1_MASK				(uint32_t)(1<<OBR_1_cmp)
#define	COMP_OBR_2_MASK				(uint32_t)(1<<OBR_2_cmp)
#define	COMP_ZF_1_MASK				(uint32_t)(1<<ZF_1_cmp)
#define	COMP_ZF_2_MASK				(uint32_t)(1<<ZF_2_cmp)
#define	COMP_DN_MASK				(uint32_t)(1<<DN_cmp)
#define	COMP_DT_MASK				(uint32_t)(1<<DT_cmp)
#define	COMP_DO_MASK				(uint32_t)(1<<DO_cmp)
#define	COMP_VMB_MASK				(uint32_t)(1<<VMB_cmp)
#define	COMP_APV_MASK				(uint32_t)(1<<APV_cmp)
#define	COMP_ZVS_MASK				(uint32_t)(1<<ZVS_cmp)
#define	COMP_ZNR_MASK				(uint32_t)(1<<ZNR_cmp)
#define	COMP_ZMT_MASK				(uint32_t)(1<<ZMT_cmp)
#define	COMP_UROV_MASK				(uint32_t)(1<<UROV_cmp)
#define	COMP_UF_MIN_MASK			(uint32_t)(1<<UF_MIN_cmp)
#define	COMP_DECR_U_MASK			(uint32_t)(1<<DECR_U_cmp)
#define	COMP_BNN1_MASK				(uint32_t)(1<<BNN1_cmp)
//#define	COMP_BNN1_EXT1_MASK			(uint32_t)(1<<BNN1_EXT1_cmp)
//#define	COMP_BNN1_EXT2_MASK			(uint32_t)(1<<BNN1_EXT2_cmp)


#define	COMP_ZN_1_MASK				(uint32_t)(1<<(ZN_1_cmp-32))
#define	COMP_ZN_2_MASK				(uint32_t)(1<<(ZN_2_cmp-32))
#define	COMP_ZN_3_MASK				(uint32_t)(1<<(ZN_3_cmp-32))
#define	COMP_ZN_4_MASK				(uint32_t)(1<<(ZN_4_cmp-32))
#define	COMP_ZN_5_MASK				(uint32_t)(1<<(ZN_5_cmp-32))
#define	COMP_ZZP_MASK				(uint32_t)(1<<(ZZP_cmp-32))
#define	COMP_ZBR_MASK				(uint32_t)(1<<(ZBR_cmp-32))
#define	COMP_IPD_MASK				(uint32_t)(1<<(IPD_cmp-32))
#define	COMP_MOT_ON_MASK			(uint32_t)(1<<(MOT_ON_cmp-32))
#define	COMP_TZP_EMRG_MASK			(uint32_t)(1<<(TZP_EMRG_cmp-32))
#define	COMP_TZP_WARN_MASK			(uint32_t)(1<<(TZP_WARN_cmp-32))
//#define	COMP_GR_START_MASK			(uint32_t)(1<<(GR_START_cmp-32))
#define	COMP_BNN2_MASK				(uint32_t)(1<<(BNN2_cmp-32))
#define	COMP_LAST_MASK				(uint32_t)(1<<(LAST_cmp-32))


#define	STAT_MTZ_1_MASK				(uint32_t)(1<<MTZ_1_state)
#define	STAT_MTZ_2_MASK				(uint32_t)(1<<MTZ_2_state)
#define	STAT_MTZ_3_MASK				(uint32_t)(1<<MTZ_3_state)
#define	STAT_MTZ_4_MASK				(uint32_t)(1<<MTZ_4_state)
#define	STAT_RPO_MASK				(uint32_t)(1<<RPO_state)
#define	STAT_NCEVO_MASK				(uint32_t)(1<<NCEVO_state)
#define	STAT_DN_MASK				(uint32_t)(1<<DN_state)
#define	STAT_ACK_MASK				(uint32_t)(1<<ACK_state)
#define	STAT_DI_BNN1_MASK			(uint32_t)(1<<DI_BNN1_state)
#define	STAT_DI_BNN2_MASK			(uint32_t)(1<<DI_BNN2_state)



#define	COMP_DN_SET					COMP_DN_MASK
#define	COMP_DN_RESET				~COMP_DN_MASK

#define	COMP_DT_SET					COMP_DT_MASK
#define	COMP_DT_RESET				~COMP_DT_MASK

#define	COMP_DO_SET					COMP_DO_MASK
#define	COMP_DO_RESET				~COMP_DO_MASK

#define	COMP_MTZ_1_SET				COMP_MTZ_1_MASK
#define	COMP_MTZ_1_RESET			~COMP_MTZ_1_MASK

#define	COMP_MTZ_2_SET				COMP_MTZ_2_MASK
#define	COMP_MTZ_2_RESET			~COMP_MTZ_2_MASK

#define	COMP_MTZ_3_SET				COMP_MTZ_3_MASK
#define	COMP_MTZ_3_RESET			~COMP_MTZ_3_MASK

#define	COMP_MTZ_4_SET				COMP_MTZ_4_MASK
#define	COMP_MTZ_4_RESET			~COMP_MTZ_4_MASK

#define	COMP_MTZ_1T_SET				COMP_MTZ_1T_MASK
#define	COMP_MTZ_1T_RESET			~COMP_MTZ_1T_MASK

#define	COMP_MTZ_2T_SET				COMP_MTZ_2T_MASK
#define	COMP_MTZ_2T_RESET			~COMP_MTZ_2T_MASK

#define	COMP_MTZ_3T_SET				COMP_MTZ_3T_MASK
#define	COMP_MTZ_3T_RESET			~COMP_MTZ_3T_MASK

#define	COMP_MTZ_4T_SET				COMP_MTZ_4T_MASK
#define	COMP_MTZ_4T_RESET			~COMP_MTZ_4T_MASK

#define	COMP_KAM_1_SET				COMP_KAM_1_MASK
#define	COMP_KAM_1_RESET			~COMP_KAM_1_MASK

#define	COMP_KAM_2_SET				COMP_KAM_2_MASK
#define	COMP_KAM_2_RESET			~COMP_KAM_2_MASK

#define	COMP_KAM_3_SET				COMP_KAM_3_MASK
#define	COMP_KAM_3_RESET			~COMP_KAM_3_MASK

#define	COMP_ZNZ_1_SET				COMP_ZNZ_1_MASK
#define	COMP_ZNZ_1_RESET			~COMP_ZNZ_1_MASK

#define	COMP_ZNZ_2_SET				COMP_ZNZ_2_MASK
#define	COMP_ZNZ_2_RESET			~COMP_ZNZ_2_MASK

#define	COMP_ZNZ_3_SET				COMP_ZNZ_3_MASK
#define	COMP_ZNZ_3_RESET			~COMP_ZNZ_3_MASK

#define	COMP_OBR_1_SET				COMP_OBR_1_MASK
#define	COMP_OBR_1_RESET			~COMP_OBR_1_MASK

#define	COMP_OBR_2_SET				COMP_OBR_2_MASK
#define	COMP_OBR_2_RESET			~COMP_OBR_2_MASK

#define	COMP_ZF_1_SET				COMP_ZF_1_MASK
#define	COMP_ZF_1_RESET				~COMP_ZF_1_MASK

#define	COMP_ZF_2_SET				COMP_ZF_2_MASK
#define	COMP_ZF_2_RESET				~COMP_ZF_2_MASK

#define	COMP_VMB_SET				COMP_VMB_MASK
#define	COMP_VMB_RESET				~COMP_VMB_MASK

#define	COMP_ZVS_SET				COMP_ZVS_MASK
#define	COMP_ZVS_RESET				~COMP_ZVS_MASK

#define	COMP_UROV_SET				COMP_UROV_MASK
#define	COMP_UROV_RESET				~COMP_UROV_MASK

#define	COMP_APV_SET				COMP_APV_MASK
#define	COMP_APV_RESET				~COMP_APV_MASK

#define	COMP_ZNR_SET				COMP_ZNR_MASK
#define	COMP_ZNR_RESET				~COMP_ZNR_MASK

#define	COMP_ZMT_SET				COMP_ZMT_MASK
#define	COMP_ZMT_RESET				~COMP_ZMT_MASK

#define	COMP_IPD_SET				COMP_IPD_MASK
#define	COMP_IPD_RESET				~COMP_IPD_MASK

#define	COMP_UF_MIN_SET				COMP_UF_MIN_MASK
#define	COMP_UF_MIN_RESET			~COMP_UF_MIN_MASK

#define	COMP_GR_START_SET			COMP_GR_START_MASK
#define	COMP_GR_START_RESET			~COMP_GR_START_MASK

#define	COMP_DECR_U_SET				COMP_DECR_U_MASK
#define	COMP_DECR_U_RESET			~COMP_DECR_U_MASK

#define	COMP_BNN1_SET				COMP_BNN1_MASK
#define	COMP_BNN1_RESET				~COMP_BNN1_MASK

#define	COMP_ZN_1_SET				COMP_ZN_1_MASK
#define	COMP_ZN_1_RESET				~COMP_ZN_1_MASK

#define	COMP_ZN_2_SET				COMP_ZN_2_MASK
#define	COMP_ZN_2_RESET				~COMP_ZN_2_MASK

#define	COMP_ZN_3_SET				COMP_ZN_3_MASK
#define	COMP_ZN_3_RESET				~COMP_ZN_3_MASK

#define	COMP_ZN_4_SET				COMP_ZN_4_MASK
#define	COMP_ZN_4_RESET				~COMP_ZN_4_MASK

#define	COMP_ZN_5_SET				COMP_ZN_5_MASK
#define	COMP_ZN_5_RESET				~COMP_ZN_5_MASK

#define	COMP_ZZP_SET				COMP_ZZP_MASK
#define	COMP_ZZP_RESET				~COMP_ZZP_MASK

#define	COMP_ZBR_SET				COMP_ZBR_MASK
#define	COMP_ZBR_RESET				~COMP_ZBR_MASK

#define	COMP_MOT_ON_SET				COMP_MOT_ON_MASK
#define	COMP_MOT_ON_RESET			~COMP_MOT_ON_MASK

#define	COMP_TZP_EMRG_SET			COMP_TZP_EMRG_MASK
#define	COMP_TZP_EMRG_RESET			~COMP_TZP_EMRG_MASK

#define	COMP_TZP_WARN_SET			COMP_TZP_WARN_MASK
#define	COMP_TZP_WARN_RESET			~COMP_TZP_WARN_MASK



//---------------------------------------------------------------------------------------------
//                                          Macros
//---------------------------------------------------------------------------------------------
//#define RECEIVE_SETTINGS_HANDLER(x, rx_d)	   	x.cntrl = RCV_SET_START; x.blck_num = rx_d[RX_SET_BLCK_NUM]; x.blck_lngth = rx_d[RX_SET_BLCK_LEN]



//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef enum{
	MTZ_1_cmp = 0,
	MTZ_2_cmp,
	MTZ_3_cmp,
	MTZ_4_cmp,
	MTZ_1T_cmp,
	MTZ_2T_cmp,
	MTZ_3T_cmp,
	MTZ_4T_cmp,
	KAM_1_cmp,
	KAM_2_cmp,
	KAM_3_cmp,
	ZNZ_1_cmp,
	ZNZ_2_cmp,
	ZNZ_3_cmp,
	OBR_1_cmp,
	OBR_2_cmp,
	ZF_1_cmp,
	ZF_2_cmp,
	DN_cmp,
	DT_cmp,
	DO_cmp,
	VMB_cmp,
	APV_cmp,
	ZVS_cmp,
	ZNR_cmp,
	ZMT_cmp,
	UROV_cmp,
	UF_MIN_cmp,
	DECR_U_cmp,
	BNN1_cmp,
	BNN1_EXT1_cmp,
	BNN1_EXT2_cmp,
	
	ZN_1_cmp,
	ZN_2_cmp,
	ZN_3_cmp,
	ZN_4_cmp,
	ZN_5_cmp,
	ZZP_cmp,
	ZBR_cmp,
	IPD_cmp,
	MOT_ON_cmp,
	TZP_EMRG_cmp,
	TZP_WARN_cmp,
	BNN2_cmp,
	BNN2_EXT1_cmp,
	BNN2_EXT2_cmp,
//	GR_START_cmp,
	
	LAST_cmp,
} comp_num_t;


//typedef enum{
//	_MTZ_1_state = 0,
//	_MTZ_2_state,
//	_MTZ_3_state,
//	_MTZ_4_state,
//	_RPO_state,
//	_NCEVO_state,
//	_DN_state,
//	_ACK_state,
//	_DI_BNN1_state,
//	_DI_BNN2_state,
//} state_num_t;



typedef struct{
	uint32_t	shifted_cur[T_PREEMERG/5];		// 10 last samples of shifted maximal current from I_AH, I_BH, I_CH (eff. val.)
	uint32_t	value[MTZ_AMOUNT];				// saved preemergency values
	uint8_t		pntr2next;						// pointer on cell number for next values
} preemrg_t;


typedef struct{
	uint8_t		main_enbl;						// main permission: 		for MTZ,KAM,DN,DO,DT,UROV,APV,ZNR,ZMT,ZZP(ZBR),TZP (1- On, 0- Off) 
												// 							for VMB (1- ZMN_F_ON, 2- ZMN_L_ON, 3- ZMN_U1_ON, 4- ZPN_U2_ON, 0- Off)
												// 							for ZNZ (0- BNN block disable, 1- BNN block direction enable, 2- BNN block processing enable)
												//							for OBR (1- IH_ON, 2- IK_ON, 0- Off)
												//							for ZF  (1- EN_F_MAX, 2- EN_F_MIN, 0- disable)
												//							for ZN  (1- ZMN_F_ON, 2- ZMN_L_ON, 3- ZPN_L_ON, 4- ZNZ_ON, 5- U2_MAX_ON, 6- U1_MIN_ON, 0- Off)
												// 							for BNN (1- BNN enable, 0- BNN disable)
												// 							for IPD -

	uint8_t		dir_enbl;						// directive mode enable: 	for MTZ (0- disable, 1- enable) 
												//							for KAM (0- disable, 1- forward on, 2- revers on)
												//							for ZNZ (0- disable, 1- enable)

	uint8_t		add1_enbl;						// additional condition 1: 	for MTZ (0- BNN block disable, 1- BNN block direction enable, 2- BNN block processing enable) 
												//					 		for KAM - block by RPO
												//							for ZNZ (0- disable, 1- 3I0 enable)
												//							for DO,DT (0- disable, 1- enable potentional, 2- enable before acknowledgment)
												//							for OBR (0- I2 mode, 1- I2/I1 mode)
												//							for ZNR,ZMT (1- enable motor start control, 0- disable)
												//							for ZF  (1- enable RPO block, 0- disable)
												//							for ZN  (1- BNN_ON, 0- Off)
												//							for BNN (0- 3I0&3U0 disable, 1- 3I0&3U0 enable)
												// 							for IPD (1- enables control of block-contacts, 0- disable)

	uint8_t		add2_enbl;						// additional condition 2: 	for MTZ (0- decr.U block disable, 1- decr.U block direction enable, 2- decr.U block processing enable) 
												//							for KAM - block by motor start
												//							for ZNZ (0- disable, 1- 3U0 enable)
												//							for ZN  (1- LOGIC_OR, 0- LOGIC_AND)
												//							for BNN (0- I2&U2 disable, 1- I2&U2 enable)

	uint8_t		add3_enbl;						// additional condition 3: 	for MTZ (0- VMB disable, 1- VMB enable)
												//							for BNN (0- I1&U1 disable, 1- I1&U1 enable)
	
	uint32_t	trshld[3];						// treshold values   (MTZ,DN,UROV,APV,UF_MIN: 		[0]- treshold value 	[1]-   					[2]-  )
												//					 (DO, DT:						[0]- treshold Ia 		[1]- treshold Ib 		[2]- treshold Ic)
												// 					 (KAM: 							[0]- treshold Pvg 		[1]- treshold Png 		[2]- treshold Pmin)
												// 					 (ZVS: 							[0]- treshold cos_phi_c	[1]- treshold cos_phi_l	[2]-  )
												// 					 (ZNZ: 							[0]- treshold cur. Iy	[1]- treshold volt. Uy 	[2]- treshold volt. Uy0 )
												//					 (OBR:							[0]- treshold IystI2	[1]- treshold IystI2/I1	[2]-  )
												//					 (ZNR:							[0]- treshold deltaI	[1]- treshold Iyn		[2]-  )
												//					 (ZMT:							[0]- 					[1]- treshold Iyn		[2]- treshold Iyv)
												//					 (ZF:							[0]- treshold Fy		[1]- 					[2]-  )
												//					 (ZN,VMB:						[0]- treshold Uy		[1]- treshold Uy		[2]-  )
												//					 (BNN:							[0]- Ubnn_y				[1]- 3U0_y				[2]- 3I0_y)
												//					 (BNN_ext1:						[0]- U2_y				[1]- I2_y				[2]- U1_y)
												//					 (BNN_ext2:						[0]- I1_max				[1]- I1_min				[2]- 70V)
												//					 (ZZP:							[0]- treshold Istart_y	[1]- 					[2]-  )
												//					 (ZBR:							[0]- 					[1]- 					[2]-  )
												//					 (IPD:							[0]- treshold Ing		[1]- treshold Ivg		[2]-  )
												//					 (MOT_ON:						[0]- 					[1]- 					[2]-  )
												//					 (TZP_EMRG:						[0]- E_trash			[1]- 					[2]-  )
												//					 (TZP_WARN:						[0]- E_warn				[1]- 					[2]-  )
												
	uint32_t 	k_retrn[3];						// return coeff. *100(MTZ,DN,UF_MIN: 				[0]- return coeff. 		[1]-   					[2]-  )
												//					 (DO, DT:						[0]- return Ia 			[1]- return Ib, 		[2]- return Ic)
												// 					 (KAM: 							[0]- return Pvg 		[1]- return Png, 		[2]- return Pmin (0.95))
												// 					 (ZNZ: 							[0]- return cur. Iy		[1]- return volt. Uy, 	[2]-  )
												//					 (OBR:							[0]- 0.95				[1]- 0.95				[2]-  )
												//					 (APV,UROV:						[0]- 0.95				[1]- 					[2]-  )
												//					 (ZNR:							[0]- return deltaI		[1]- 0.95				[2]-  )
												//					 (ZMT:							[0]- 					[1]- return Iyn			[2]- return Iyv)
												//					 (ZF:							[0]- return Kv			[1]- 					[2]-  )
												//					 (ZN:							[0]- 0.95(ZPN,U2MAX,ZNZ)[1]- 1.05(ZMN,U1MIN)	[2]-  )
												//					 (VMB:							[0]- 0.95(ZPNU2)		[1]- 1.05(ZMNF,ZMNL,ZMNU1)[2]-  )
												//					 (BNN:							[0]- 0.95				[1]- 0.95				[2]- 0.95)
												//					 (BNN_ext1:						[0]- 0.95				[1]- 1.05				[2]- 1.05)
												//					 (BNN_ext2:						[0]- 1.05				[1]- 0.95				[2]- 1.05)
												//					 (ZZP,ZBR,IPD,MOT_ON:			[0]- 					[1]- 					[2]-  )
												//					 (TZP_EMRG:						[0]- E_ret				[1]- 					[2]-  )
												//					 (TZP_WARN:						[0]- 0.95				[1]- 					[2]-  )
												
	uint16_t	ang_set[3];						// angle zones  	 (MTZ, ZNZ: 					[0]- phi_m_ch 			[1]- phi_sh_z/2 		[2]- phi_sh_z/2 + phi_gist) 
	uint32_t	T_set;							// timeout for softtimer (setted by CPU)
												//					 (ZZP:		T pusk_dv)
												//					 (ZBR:		T bl_rot)
												//					 (IPD:		T dlit_pusk)
												//					 (MOT_ON:	T contr_pusk)
												
	uint32_t	T_trsh;							// timeout for protect treshold (calculated by AI based on .T_set and .tcc)
	
	uint8_t		sttngs_chng;					// settings change flag (0- no change, 1- there is change)
	tcc_t		tcc;							// TCC type
} prtct_set_t;


typedef enum{									// flag that shows stage of settings receiving
	RCV_SET_STOP = 0,
	RCV_SET_START,
} rcv_set_t;


typedef enum{									// flag that shows status of settings updating
	NO_SET = 0,
	UPDATING,
	UPDATED,
	TESTED,
//	NEW_SET, 
	VALID,
} set_upd_t;


typedef struct{
	rcv_set_t		cntrl;	
	set_upd_t		sttus;
	uint8_t			blck_num;
	uint8_t			blck_lngth;
} set_stts_t;



//----------------------------------------------------------------------------------------------
//                                  Function's prototypes
//----------------------------------------------------------------------------------------------
void SavePreemrgCur(uint32_t *, vect_t *, preemrg_t *);
void CalcTccMTZ(vect_t *, preemrg_t *, prtct_set_t *);
void ReceiveSettingsHandler(uint8_t *, set_stts_t *);
void ReceiveSettings(uint8_t *, set_stts_t *, uint8_t * /* , setngs_t *, prtct_set_t *, RTC_stts_t * */ );
void UnzipSettings(uint8_t *, setngs_t *, prtct_set_t *, rtc_strct_t *);
void TrigShmidt4Compar(uint32_t *, uint32_t *);
void PackCmpr4Txd(uint32_t *, uint8_t *);
void CalcVectBreakCur(spectr_t *, setngs_t *, uint32_t *, prtct_set_t *);

void ComparVMB(vect_t *, FRZseq_t *, prtct_set_t *, uint32_t *);
void ComparKAM(power_t *, prtct_set_t *, uint32_t , uint32_t *);
//void ComparDecrU(vect_t *, uint32_t *);
void ProtectMTZ(uint32_t *, vect_t *, uint16_t *, FRZseq_t *, prtct_set_t *, preemrg_t *, uint32_t, uint32_t *);
void TimingMTZ(uint32_t *, prtct_set_t *, uint32_t *);
void DelayMTZ(uint32_t *, prtct_set_t *, uint32_t *);
void ProtectZVS(power_t *, uint16_t *, prtct_set_t *, uint32_t *);
void ProtectZNZ(vect_t *, uint16_t *, prtct_set_t *, uint32_t *, uint8_t *);
//void ProtectDnDoDt(vect_t *, prtct_set_t *, uint32_t , uint32_t *);	
void ProtectDN(vect_t *, prtct_set_t *, uint32_t *);		
void ProtectDT(vect_t *, prtct_set_t *, uint32_t , uint32_t *);
void ProtectDO(vect_t *, prtct_set_t *, uint32_t , uint32_t *);	
void ProtectUROV(vect_t *, prtct_set_t *, uint32_t *);
void ProtectAPV(vect_t *, prtct_set_t *, uint32_t *);
void ProtectOBR(FRZseq_t *, prtct_set_t *, uint32_t *);
void ProtectZNR(vect_t *, uint32_t *, prtct_set_t *, uint32_t *);
void ProtectZMT(vect_t *, prtct_set_t *, uint32_t *);
void ComparUFMIN(dat4freq_t *, prtct_set_t *, uint32_t *);
void ProtectZF(dat4freq_t *, prtct_set_t *, uint32_t, uint32_t *);
void ProtectZN(vect_t *, FRZseq_t *, prtct_set_t *, uint32_t *);
void ProtectBNN(vect_t *, vect_t *, FRZseq_t *, prtct_set_t *, uint32_t, uint32_t *);
void ProtectZZP_ZBR(vect_t *, prtct_set_t *, uint32_t *);
void ProtectIPD(vect_t *, prtct_set_t *, uint32_t, uint32_t *);
void ProtectTZP(therm_t *, prtct_set_t *, uint32_t *);




#endif
