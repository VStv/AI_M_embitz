//*********************************************************************************************
//                                          Exti.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "exti.h"

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//---------------------------------- EXTI initialization --------------------------------------
void ExtiInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  													// Clock for Port C switch on
	SetAsInput(PPS_Port, PPS_Pin, 1);

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  													//
	AFIO->EXTICR[3] &= ~AFIO_EXTICR4_EXTI12;												// choose line PC12 as EXTI15-10 source
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PC;

	EXTI->RTSR &= ~(uint32_t)(1<<PPS_Pin);													// choose rising trigger
	EXTI->FTSR |= (uint32_t)(1<<PPS_Pin);													// choose falling trigger
	
	NVIC_SetPriority(EXTI15_10_IRQn, 9);
	//NVIC_EnableIRQ(EXTI15_10_IRQn);

	EXTI->EMR &= ~((uint32_t)(1<<PPS_Pin));	
	EXTI->IMR |= (uint32_t)(1<<PPS_Pin);													// activate EXTI15-10 interrupt
	EXTI->PR |= (uint32_t)(1<<PPS_Pin);
}


//------------------------------------- EXTI handler ------------------------------------------
//void EXTI15_10_IRQProcedure	(
//							uint32_t *s_cnt,
//							uint32_t *ms_cnt
//							)
//{
//	if(EXTI->PR & ((uint32_t)(1<<PPS_Pin)))
//	{
//		// clear interrupt flag
//		EXTI->PR |= (uint32_t)(1<<PPS_Pin);	
//		*s_cnt = 
//	}
//	NVIC_DisableIRQ(EXTI15_10_IRQn);
//}	


