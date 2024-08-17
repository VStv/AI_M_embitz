//*********************************************************************************************
//                                       Oper_val.h
//*********************************************************************************************


#ifndef __OPER_VAL__
#define __OPER_VAL__

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "adc_ext.h"
#include "fourier.h"
#include "com_ext.h"
#include "ram_ext.h"
#include "rtc.h"
//#include "protect.h"
#include "timer.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define THERM_CONST_BASE		1000UL			// 1000sec
#define DELTA_T_TZP				1UL				// 1 sec
#define COEF_TZP				1000000UL		// 



//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef struct{
	vect_t harm1;
//	vect_t harm2;
//	vect_t harm5;
} spectr_t;

typedef struct{
	subvect_t subharm1;
//	subvect_t subharm2;
//	subvect_t subharm5;
} subspectr_t;

typedef struct{
	vect_t forward;
	vect_t reverse;
//	vect_t zero;
	uint32_t relat_r2f;
} FRZseq_t;

typedef enum {
	ph_A = 0,
	ph_B,
	ph_C,
	ph_N
} phases_t;

typedef struct{
//	uint32_t 	align[2];						//  coeffitient of alignment on H, K sides
//	uint32_t 	kta;							//  coeffitient of current transformation for H, K sides
//	uint32_t 	kta0;							//  coeffitient of current transformation for zero sequence transformator
	uint32_t 	ktv;							//  coeffitient of voltage transformation for H, K sides
	uint32_t 	ktv0;							//  coeffitient of voltage transformation for zero sequence transformator
	uint32_t 	k_t[2];							//  coeffitient of taking part in forming of br. cur. for H, K sides
	uint32_t 	k_br;							//  breaking coeffitient
	uint32_t 	i_t0;							//  starting breaking current
	uint32_t 	i_do;							//  treshold current for dif. treshold
	uint32_t 	i_dt0;							//  start treshold current for dif. protection
	uint32_t 	i_tlim;							//  limiting breaking current
	
	int16_t 	temprt_envir;
	int16_t 	temprt_envir_nom;
	int16_t 	temprt_motor_crtic;
	int16_t 	temprt_motor_start;
	uint16_t 	heat_const;
	uint16_t 	cool_const;
	uint32_t 	mot_current_nom;
} setngs_t;


typedef enum {
	FR = 0,
	Z,
	FRZ,
} FRZset_t;


typedef struct{
	int32_t active;
	int32_t reactive;
	uint32_t full;
	int32_t cos_phi;
} power_t;


typedef enum {
	UA_IAH,
	UB_IBH,
	UC_ICH,
	UBC_IAH,
	UCA_IBH,
	UAB_ICH,
	U0_I0,
} phi_t;


typedef struct{
	int32_t ovrht;
	uint32_t therm_const;
//	uint32_t cool_constant;
	uint16_t time_cnt;
	uint16_t off_cnt;
} therm_t;



//----------------------------------------------------------------------------------------------
//                                  Function's prototypes
//----------------------------------------------------------------------------------------------
void CalcSum(sample_t *, subspectr_t *);
void CalcVectPhase(sample_t *, subspectr_t *, spectr_t *);
void CalcVectLine(spectr_t *, spectr_t *);
void CalcVectFR(spectr_t *, spectr_t *, FRZseq_t *);
void CalcVectDifCur(spectr_t *, spectr_t *);
//void CalcVectBreakCur(spectr_t *, setngs_t *, uint32_t *, prtct_set_t *);
void CalcUnsymCur(spectr_t *, uint32_t *);
void CalcUnbalVol(spectr_t *, setngs_t *, vect_t *);
void DefBaseVect(spectr_t *, spectr_t *, chan_bas_t *);
void RotVectors(spectr_t *, spectr_t *, spectr_t *, chan_bas_t, vect_t *);
void CalcUIAngles(vect_t *, uint16_t *);
void CalcPower(vect_t *, uint16_t *, power_t *);
void CalcFreq(spectr_t *, dat4freq_t *);
void ThermModel(vect_t *, FRZseq_t *, setngs_t *, therm_t *);
void FindEquivalCur(vect_t *, FRZseq_t *, uint64_t *);
void FindThermConst(uint64_t *, setngs_t *, therm_t *);
int32_t FindDeriv(uint64_t *, setngs_t *, therm_t *, uint32_t);
void RungeKutt(uint64_t *, setngs_t *, therm_t *);
void SaveThermalState(uint32_t, setngs_t *, therm_t *);
void InitThermalState(setngs_t *, therm_t *);
void PackInfTxBuf(vect_t *,	FRZseq_t *,	uint32_t *,	uint32_t *,	power_t *, uint16_t *, vect_t *, dat4freq_t *, therm_t *, uint8_t *, uint8_t *);


#endif
