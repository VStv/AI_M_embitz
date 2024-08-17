//*********************************************************************************************
//                                        Math_soft.h
//*********************************************************************************************

#ifndef __MATH_SOFT__
#define __MATH_SOFT__

//---------------------------------------------------------------------------------------------
//                                      Include section 
//---------------------------------------------------------------------------------------------
#include "stm32f10x.h"


//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define EXP_TAB_SIZE				41
#define LOG_TAB_SIZE				41
#define CHART_2_7_B1_TAB_SIZE		51
#define CHART_2_7_B2_TAB_SIZE		71
#define CHART_2_7_B3_TAB_SIZE		11
#define EXP_SCALE_FACTOR			10000UL

#define COLLECTED_MAX_VAL			100000000UL


#define MINIM						0
#define MAXIM						1

//---------------------------------------------------------------------------------------------
//                                      Typedef section
//---------------------------------------------------------------------------------------------
typedef enum {
	RES_OK = 0,
	VALUE_IS_LESS_THEN_POSSIBLE,
	VALUE_IS_GREATER_THEN_POSSIBLE,
} error_t;


typedef struct {
	int32_t 	re;
	int32_t 	im;
	uint32_t   	ef_val;
	uint16_t   	phase;
	uint16_t   	nothing1;
} vect_t;


typedef enum {
	PROJ = 0,
	W_EF_VAL,
	W_PHASE_ANG
} par_set_t;


typedef enum {
	TCC_1 = 0,
	TCC_2,
	TCC_3,
	TCC_4,
	TCC_5,
	TCC_6,
	TCC_7,
	TCC_8,
} tcc_t;


//----------------------------------------------------------------------------------------------
//                                   Function's prototypes
//----------------------------------------------------------------------------------------------
//uint32_t FindMax(uint32_t *);
//uint16_t FindMaxElem(uint32_t *, uint16_t);
//uint32_t FindMin(uint32_t *);
//uint16_t FindMinElem(uint32_t *, uint16_t);
uint16_t FindExtrElem(uint32_t *, uint16_t, uint8_t);
uint32_t SqRoot(uint32_t);
//void PhaseAngle(vect_t *, uint32_t);
//void EfVal(vect_t *);
void VectParam(vect_t *, uint32_t, par_set_t);
int16_t Sinus(uint16_t);
int16_t Cosin(uint16_t);
int32_t QuadInterp(int32_t *, int32_t *, int32_t, uint16_t, int32_t);
error_t FindLn(uint16_t, int32_t *);
error_t FindValTcc2_7(uint32_t, tcc_t, int32_t *);
error_t FindExp(uint16_t, uint16_t *);


// Privat

#endif
