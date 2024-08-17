//*********************************************************************************************
//                                         Systick.c
//*********************************************************************************************

//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "systick.h"


//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//                                     Global variables
//---------------------------------------------------------------------------------------------
uint8_t del_sygnal;
//extern uint32_t	s1_cnt;
//extern uint32_t	ms1_cnt;
extern rtc_strct_t	Rtc_fact;


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
void SysTick_IRQProcedure	(
							uint8_t *main_flag, 
							uint8_t *firmw_ct
							)
{
	// get actual time from RTC & ms_timer
	Rtc_fact.ms_counter = ((uint32_t)TIM8->CNT)>>1;
//	s1_cnt = Rtc_fact.s_counter;

    del_sygnal = 1;

	if(*firmw_ct == 0) 
		*main_flag = 2;																	// if no need of firmware updating - enable data processing in main
	else 
		*main_flag = 3;																	// else enable firmware updating in main
}


//--------------------------------------- us Delay --------------------------------------------
void usDelay(
			uint32_t us_del
			)
{
	uint32_t tick_cnt, del_cnt, temp32;
	int32_t end_cnt;
	
	del_sygnal = 0;
    tick_cnt = SysTick->VAL;
    temp32 = SystemCoreClock/1000000;
	del_cnt = us_del*temp32;
    if(del_cnt >= tick_cnt)
    {
        while(!del_sygnal);
        del_sygnal = 0;
        del_cnt -= tick_cnt;
        while(del_cnt >= SysTick->LOAD)
        {
            while(!del_sygnal);
            del_sygnal = 0;
            del_cnt -= SysTick->LOAD;
        }
        end_cnt = SysTick->LOAD - del_cnt;
    }
    else
    {
        end_cnt = tick_cnt - del_cnt;
    }
    while(tick_cnt > end_cnt) {tick_cnt = SysTick->VAL;}
    return;
}

