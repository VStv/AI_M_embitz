//*********************************************************************************************
//                                        Adc_ext.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "adc_ext.h"


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//------------------------- Get data from 2 external ADC (18.5us) -----------------------------

void AdcPolling	(
				sample_t *adc_dat
				)
{
	chan_mes_t chan_pntr[CHNL_MESR] = {I_AH_MES, I_BH_MES, I_CH_MES, I_0_MES, I_AK_MES, I_BK_MES, I_CK_MES, U_A_MES, U_B_MES, U_C_MES, U_0_MES, U_F_MES};
	
	(adc_dat->sample_num)++;
	if(adc_dat->sample_num > 23)	
		adc_dat->sample_num = 0;

	AdcDataBusAsInput();
	__ASM("NOP");__ASM("NOP");
	SET_PIN(CONVST1_ADC_Port, CONVST1_ADC_Pin);					// start conversion
	SET_PIN(CONVST2_ADC_Port, CONVST2_ADC_Pin);					// start conversion
	usDelay(3);
	RESET_PIN(CONVST1_ADC_Port, CONVST1_ADC_Pin);				// stop conversion
	RESET_PIN(CONVST2_ADC_Port, CONVST2_ADC_Pin);				// stop conversion
	__ASM("NOP");__ASM("NOP");__ASM("NOP");
	__ASM("NOP");__ASM("NOP");__ASM("NOP");
	__ASM("NOP");__ASM("NOP");__ASM("NOP");

	RESET_PIN(CS1_ADC_Port, CS1_ADC_Pin);						// CS ADC  -  select ADC #1
	__ASM("NOP");__ASM("NOP");__ASM("NOP");
	__ASM("NOP");__ASM("NOP");__ASM("NOP");
	__ASM("NOP");__ASM("NOP");__ASM("NOP");
	for(uint32_t i=0; i<7; i++)
	{
		RESET_PIN(RD_ADC_Port, RD_ADC_Pin);
		__ASM("NOP");__ASM("NOP");__ASM("NOP");__ASM("NOP");
		adc_dat->sample[chan_pntr[i]] = RxWordByBus();			// read data from ADC channel #i
		SET_PIN(RD_ADC_Port, RD_ADC_Pin);
		__ASM("NOP");
	}
	SET_PIN(CS1_ADC_Port, CS1_ADC_Pin);     					// CS ADC  -  resume ADC #1
	
	RESET_PIN(CS2_ADC_Port, CS2_ADC_Pin);						// CS ADC  -  select ADC #2
	__ASM("NOP");
	for(uint32_t i=7; i<CHNL_MESR; i++)
	{
		RESET_PIN(RD_ADC_Port, RD_ADC_Pin);
		__ASM("NOP");__ASM("NOP");__ASM("NOP");__ASM("NOP");
		adc_dat->sample[chan_pntr[i]] = RxWordByBus();			// read data from ADC channel #7..11
		SET_PIN(RD_ADC_Port, RD_ADC_Pin);
		__ASM("NOP");
	}
	SET_PIN(CS2_ADC_Port, CS2_ADC_Pin);     					// CS ADC  -  resume ADC #2
	RESET_ADC_CTRL();											// Return Bus and control lines
	RESET_BUS();
}


//---------------------------------------------------------------------------------------------
//                                    Privat functions
//---------------------------------------------------------------------------------------------
