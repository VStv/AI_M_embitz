//*********************************************************************************************
//                                          Timer.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "timer.h"

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//-------------------------------- Timer1 initialization --------------------------------------
void TimerInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;  													// TIM8 clock switch on
	if(BKP->DR2 != PSC_SAVED)
	{
		PWR->CR |= PWR_CR_DBP;																// enable access to DBP
		BKP->DR3 = (uint16_t)(SystemCoreClock/2000 - 1); 									// 2kHz (SystemCoreClock/2000) - 1
		BKP->DR2 = PSC_SAVED;
		PWR->CR &= ~PWR_CR_DBP;																// disable access to DBP
	}
	TIM8->PSC = BKP->DR3;																	//
	TIM8->ARR = 2000 - 1;
	TIM8->DIER |= TIM_DIER_UIE;
	TIM8->CR1 |= TIM_CR1_CEN;																// Запускаем счет таймера	
	NVIC_SetPriority(TIM8_UP_IRQn, 15);
	NVIC_EnableIRQ(TIM8_UP_IRQn);
	
	
	
#ifdef _FREQ_MESURE_ON_
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  													// Clock for Port A switch on
	SetAsInput(U_F_Port, U_F_Pin, 1);

	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  													// Timer 1 clock switch on
	TIM1->PSC = (SystemCoreClock/1000000) - 1;												// 1MHz
	
	TIM1->CCMR1 |= TIM_CCMR1_CC2S_0;														// Выбор активного входа. Записываем "01" в биты CC2S - связываем регистр TIM1_CCR2 со входом TI2
	TIM1->CCMR1 |= (/*TIM_CCMR1_IC2F_1 |*/ TIM_CCMR1_IC2F_0);								// Выбор длительности действия фильтра - 8 тактов. IC2F = 0011.
	TIM1->CCMR1 &= ~TIM_CCMR1_IC2PSC;														// Предделитель отключен
	TIM1->CCER &= ~TIM_CCER_CC2P;															// По переднему фронту - положительный перепад импульса
	TIM1->CCER |= TIM_CCER_CC2E;															// Разрешен захват значения счетчика в регистр TIM1_CCR2

	TIM1->DIER |= TIM_DIER_CC2IE;															// Разрешена генерация прерывания при захвате
	TIM1->CR1 |= TIM_CR1_CEN;																// Запускаем счет таймера	

	NVIC_SetPriority(TIM1_CC_IRQn, 15);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
#endif
}


//------------------------------------- EXTI handler ------------------------------------------
void TIM1_CC_IRQProcedure	(
							dat4freq_t *dat
							)
{
	static uint16_t temp_cptr;
	
	if(TIM1->SR & TIM_SR_CC2IF)
	{
		if(TIM1->CCR2 > temp_cptr)
			dat->elapsed_time = TIM1->CCR2 - temp_cptr;
		else
			dat->elapsed_time = 0xffff + TIM1->CCR2 - temp_cptr;
		temp_cptr = TIM1->CCR2;
	}
	TIM1->SR = 0;
}	

////------------------------------------- TIM8 handler ------------------------------------------
//void TIM8_IRQProcedure	(
//						uint32_t *s_cnt
//						)
//{
//	if(TIM8->SR & TIM_SR_UIF)
//	{
//		(*s_cnt)++;
//		TIM8->SR &= ~TIM_SR_UIF;
//	}
//}

