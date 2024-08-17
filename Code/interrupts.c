//*********************************************************************************************
//                                       Interrupts.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "interrupts.h"

//---------------------------------------------------------------------------------------------
//                                        Constants
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                     Global variable
//---------------------------------------------------------------------------------------------
extern uint8_t 		start_obr;
extern dat4freq_t 	dat4freq;
extern firmw_upd_t	firmw_ctrl;
extern rtc_strct_t	Rtc_fact;
extern rtc_strct_t	Rtc_sync;
//extern uint32_t		ms1_cnt;

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
void SysTick_Handler(void) 
{ 
	SysTick_IRQProcedure(&start_obr, &(firmw_ctrl.get_upd));
}


//---------------------------------------------------------------------------------------------
void HardFault_Handler(void)
{
	NVIC_SystemReset();
}


//---------------------------------------------------------------------------------------------
void UsageFault_Handler(void)
{
	NVIC_SystemReset();
}


//---------------------------------------------------------------------------------------------
#ifdef _FREQ_MESURE_ON_
void TIM1_CC_IRQHandler(void)
{
    TIM1_CC_IRQProcedure(&dat4freq);
}
#endif


//---------------------------------------------------------------------------------------------
void TIM8_UP_IRQHandler(void)
{
//    TIM8_IRQProcedure();
	if(TIM8->SR & TIM_SR_UIF)
	{
		(Rtc_fact.s_counter)++;
		Rtc_sync.timeout[1]++;
		TIM8->SR &= ~TIM_SR_UIF;
	}
}


//---------------------------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & ((uint32_t)(1<<PPS_Pin)))
	{
		
		// set sync time to RTC
		TIM8->EGR |= TIM_EGR_UG;
		TIM8->SR &= ~TIM_SR_UIF;
		Rtc_fact.s_counter = Rtc_sync.s_counter;
		Rtc_fact.ms_counter = 0;
		
		// change sync flag
		Rtc_sync.rtc_flag = NO_CMD;			//RTC_SYNC_END

		// reset timeout counter for synchronize control
		Rtc_sync.timeout[1] = 0;

		// clear interrupt flag
		EXTI->PR |= (1<<PPS_Pin);
	}
	NVIC_DisableIRQ(EXTI15_10_IRQn);
}



