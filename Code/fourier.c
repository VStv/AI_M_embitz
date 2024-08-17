//*********************************************************************************************
//                                        Fourier.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "fourier.h"

//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------
//---------------------------- Table of Sinus for 1st harmonic --------------------------------
const int16_t SIN1_TAB[48] = {	0,  265,  512,  724,  887,  989, 1024,  989,  887,  724,  512,  265,       
								0, -265, -512, -724, -887, -989,-1024, -989, -887, -724, -512, -265,
								0,  265,  512,  724,  887,  989, 1024,  989,  887,  724,  512,  265,       
								0, -265, -512, -724, -887, -989,-1024, -989, -887, -724, -512, -265		};

//--------------------------- Table of Cosinus for 1st harmonic ------------------------------- 
const int16_t COS1_TAB[48] = {	1024,  989,  887,  724,  512,  265,   0, -265, -512, -724, -887, -989,
							   -1024, -989, -887, -724, -512, -265,   0,  265,  512,  724,  887,  989, 
								1024,  989,  887,  724,  512,  265,   0, -265, -512, -724, -887, -989,
							   -1024, -989, -887, -724, -512, -265,   0,  265,  512,  724,  887,  989	};

////----------------------------- Table of Sinus for 2nd harmonic -------------------------------
//const int16_t SIN2_TAB[48] = {	0,  512,  887, 1024,  887,  512,	0, -512, -887,-1024, -887, -512,
//								0,  512,  887, 1024,  887,  512,	0, -512, -887,-1024, -887, -512,       
//								0,  512,  887, 1024,  887,  512,	0, -512, -887,-1024, -887, -512,
//								0,  512,  887, 1024,  887,  512,	0, -512, -887,-1024, -887, -512		};

////---------------------------- Table of Cosinus for 2nd harmonic ------------------------------
//const int16_t COS2_TAB[48] = {	1024,  887,  512,   0, -512, -887,-1024, -887, -512,   0,  512,  887, 
//								1024,  887,  512,   0, -512, -887,-1024, -887, -512,   0,  512,  887,
//								1024,  887,  512,   0, -512, -887,-1024, -887, -512,   0,  512,  887, 
//								1024,  887,  512,   0, -512, -887,-1024, -887, -512,   0,  512,  887	};

////----------------------------- Table of Sinus for 5th harmonic -------------------------------
//const int16_t SIN5_TAB[48] = {	0,  989,  512, -724, -887,  265, 1024,  265, -887, -724,  512,  989,
//								0, -989, -512,  724,  887, -265,-1024, -265,  887,  724, -512, -989,
//								0,  989,  512, -724, -887,  265, 1024,  265, -887, -724,  512,  989,
//								0, -989, -512,  724,  887, -265,-1024, -265,  887,  724, -512, -989		};

////---------------------------- Table of Cosinus for 5th harmonic ------------------------------
//const int16_t COS5_TAB[48] = {	1024,  265, -887, -724,  512,  989,    0, -989, -512,  724,  887, -265,
//							   -1024, -265,  887,  724, -512, -989,	   0,  989,  512, -724, -887,  265, 
//								1024,  265, -887, -724,  512,  989,    0, -989, -512,  724,  887, -265,
//							   -1024, -265,  887,  724, -512, -989,    0,  989,  512, -724, -887,  265  };



//---------------------------------------------------------------------------------------------
//                                         Functions
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// Realize of discret Fourier transform for request harmonic of request signal in 4 streams(4..6 us)
// For request signal (adc_dat.sample[chan]) for request harmonic (harmonic) defines current 
// integral sums (4 streams) 
//---------------------------------------------------------------------------------------------
void FourierSum	(						
				sample_t *adc_dat,							// structure that contains ADC sample for all channel and sample's number
				chan_mes_t chan,							// processed channel
				uint8_t harmonic,							// processed harmonic
				subvect_t *subvect							// pointer on structure that contains running cos & sin sums for fourier coef. calculated for request harmonics
				)
{
	uint16_t num;
	uint32_t cur_val;
	int16_t *pSin, *pCos;
	int32_t cur_sum;
//	uint8_t adc_ch_num[12] = {0, 1, 2, 4, 5, 6, 3, 7, 8, 9, 10, 11};
	
	// Calculation of the integral sums for request harmonic of request signal in 4 streams
	num = adc_dat->sample_num;
	cur_val = (uint32_t)adc_dat->sample[chan];
	switch(harmonic)
	{
//		case 5:
//			pSin = (int16_t *)SIN5_TAB;
//			pCos = (int16_t *)COS5_TAB;
//			break;
//		case 2:
//			pSin = (int16_t *)SIN2_TAB;
//			pCos = (int16_t *)COS2_TAB;
//			break;
		default:
			pSin = (int16_t *)SIN1_TAB;
			pCos = (int16_t *)COS1_TAB;
			break;
	}
	for(int stream=0; stream<4; stream++)
	{
		cur_sum = subvect->a_sum[stream];
		cur_sum += cur_val * (*(pCos + num));
		subvect->a_sum[stream] = cur_sum;
		cur_sum = subvect->b_sum[stream];
		cur_sum += cur_val * (*(pSin + num));
		subvect->b_sum[stream] = cur_sum;
		num += 6;
	}
}


//---------------------------------------------------------------------------------------------
// For request harmonic (harmonic) defines current (that pointed by *vect) 
// Re, Im vector's projections, effective value, phase angle
//---------------------------------------------------------------------------------------------
void FourierVect(						
				uint16_t num,								// current number of sample
				uint8_t harmonic,							// processed harmonic
				uint32_t Vgr,								// min value
				par_set_t settings,							// parameter that defines set of calculated parameters of vector
				subvect_t *subvect,							// pointer on structure that contains running cos & sin sums for fourier coef. calculated for request harmonics
				vect_t *vect								// pointer on structure that will contain projections of vector - result
				)
{
	uint32_t stream; 
	int32_t temp;
	vect_t temp_v;
	int64_t temp64;
	
	// Calculation of the vector's projections when stream complete
	stream = num/6;
	temp64 = (int64_t)subvect->a_sum[stream];
	temp64 = temp64/(12*1024);										
	temp_v.re = (int32_t)temp64;									
	temp64 = (int64_t)subvect->b_sum[stream];
	temp64 = temp64/(12*1024);									
	temp_v.im = 0 - (int32_t)temp64;								
	subvect->a_sum[stream] = 0;									// reset of the sums
	subvect->b_sum[stream] = 0;

	// Calculation of vector's parameters
	VectParam(&temp_v, Vgr, settings); 
	if(temp_v.phase != 0xffff) 
	{
		temp_v.phase += ((uint16_t)(15 * harmonic * num));
		while(temp_v.phase >= 360) temp_v.phase -= 360;			// to provide 0<angle<360
	}

	// Turn vector according to stream and harmonic number 
	switch(harmonic)
	{
		case 2:
			if(num == 6 || num == 18)
			{
				temp_v.im = 0 - temp_v.im;
				temp_v.re = 0 - temp_v.re;
			}
			break;

		default:
			if(num == 6)
			{
				temp = temp_v.re;
				temp_v.re = 0 - temp_v.im;
				temp_v.im = temp;
			}
			else if(num == 12)
			{
				temp_v.im = 0 - temp_v.im;
				temp_v.re = 0 - temp_v.re;
			}
			else if(num == 18)
			{
				temp = temp_v.im;
				temp_v.im = 0 - temp_v.re;
				temp_v.re = temp;
			}
			break;
	}

	vect->re = temp_v.re;
	vect->im = temp_v.im;
	vect->ef_val = temp_v.ef_val;
	vect->phase = temp_v.phase;
}



