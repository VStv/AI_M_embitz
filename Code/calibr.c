//*********************************************************************************************
//                                         Calibr.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "calibr.h"


//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------
//---------------------------------- Calibration constants ------------------------------------

const uint32_t Transf_coef[CHNL_MESR] = 	{1850, 	1850, 	1850, 	1850, 	1850, 	1850, 	4214, 	4635, 	4635, 	4635, 	4635, 	4635}; 	// 
const uint32_t Base_clbr_coef[CHNL_MESR] = 	{10032, 10032, 	10032, 	10032, 	10032, 	10032, 	10032, 	10032, 	10032, 	10032, 	10032, 	10032};
const uint32_t Base_zero_level[CHNL_MESR] = {32767, 32767, 	32767, 	32767, 	32767, 	32767, 	32767, 	32767, 	32767, 	32767, 	32767, 	32767};


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------

//----------------------------- Calibration procedure (    us) --------------------------------
void Calibrate	(
				sample_t adc_dat,								// structure that contains ADC sample for all channel and sample's number
				spectr_t *target_val,							// pointer on array of structures that contain data for vectors calculated for 1st, 2nd, 5th harmonics of directly measured signals// pointer on array of structures that contain data for vectors calculated for 1st, 2nd, 5th harmonics of directly measured signals
				clbr_stts_t *calibr_dat,						// pointer on array of structures that contain control data for calibration
				uint8_t *tx_dat
				)
{
	uint8_t res = 0, chan;
	uint32_t coef, val;
	uint16_t temp16_1 = 0, buf_wr[IN_CALIB_SAVE_AREA_VOL/2] = {0};
	
	if(calibr_dat->clbr_stt == START_CLBR)
	{
		ReadBufFlash(ADR_LAST_PAGE_FLASH, buf_wr, IN_CALIB_SAVE_AREA_VOL/2);
		
		chan = calibr_dat->cur_clbr_chan;
		STOP_SYSTICK();
		
		// define zero level calibration
		if(chan == 0xfe)
		{
			for(int i=0; i<CHNL_MESR; i++)
			{
				if((adc_dat.sample[i]>(uint16_t)0x7320) && (adc_dat.sample[i]<(uint16_t)0x8CE0))
				{
					calibr_dat->zero_level[i] = adc_dat.sample[i];
					res++;
				}
				else 
					break;
			}
			if(res == CHNL_MESR)
				res = 0x0f;
		}
		
		// define coefficient calibration
		else if(chan < CHNL_MESR)
		{
			val = target_val[chan].harm1.ef_val;
			coef = (10000*((uint16_t)Transf_coef[chan]))/val;
			if((coef>(((uint16_t)Base_clbr_coef[chan])*85/100)) && (coef<((uint16_t)(Base_clbr_coef[chan])*115/100)))
			{
				calibr_dat->clbr_coef[chan] = (uint16_t)(coef + 1);
				res = 0x0f;
			}
		}

		// if calibration successful writes coefficients in ROM
		if(res == 0x0f)
		{
			for(int k=0; k<CHNL_MESR; k++)
			{
				buf_wr[k] = calibr_dat->clbr_coef[k];
				temp16_1 ^= buf_wr[k];
				buf_wr[k+CHNL_MESR] = calibr_dat->zero_level[k];
				temp16_1 ^= buf_wr[k+CHNL_MESR];
			}
			buf_wr[2*CHNL_MESR] = temp16_1;
			
			FlashUnLock();
			FlashErasePage(ADR_LAST_PAGE_FLASH);
			FlashWritePage(ADR_LAST_PAGE_FLASH, buf_wr, IN_CALIB_SAVE_AREA_VOL/2);
			FlashLock();

			*(tx_dat+TX_STATUS) |= (1<<ToCPU_Status_SUCCESS_CALIBRATION_bit);
		}
		calibr_dat->clbr_stt = FIN_CLBR;
		START_SYSTICK();
	}
}


//------------------------- Read calibration coefficients (    us) ----------------------------
void ReadCalibrCoef	(
					clbr_stts_t *calibr_dat							// pointer on array of structures that contain control data for calibration
					)
{
	uint16_t temp16_1 = 0, buf_rw[IN_CALIB_SAVE_AREA_VOL/2] = {0};
	uint8_t data_wrong = 0;
	
	// Read array from ROM and checks CRC & data correction
	ReadBufFlash(ADR_LAST_PAGE_FLASH, buf_rw, IN_CALIB_SAVE_AREA_VOL/2);
	for(int k=0; k<(2*CHNL_MESR); k++)
	{
		temp16_1 ^= buf_rw[k];
		if(buf_rw[k] == 0xffff)
		{
			data_wrong++;
		}
	}
	temp16_1 ^= buf_rw[2*CHNL_MESR];
	
	// if CRC is OK send read data to appropriate structure fields
	if(!temp16_1 && !data_wrong)
	{
		for(int i=0; i<CHNL_MESR; i++)
		{
			calibr_dat->clbr_coef[i] = buf_rw[i];
			calibr_dat->zero_level[i] = buf_rw[i+CHNL_MESR];
		}
		calibr_dat->crc = buf_rw[2*CHNL_MESR];
	}
	
	// if CRC isn't OK accept basic coefficients as calibration coefficients
	else
	{
		for(int i=0; i<CHNL_MESR; i++)
		{
			calibr_dat->clbr_coef[i] = (uint16_t)Base_clbr_coef[i];
			calibr_dat->zero_level[i] = (uint16_t)Base_zero_level[i];
		}
		
		// Calculates CRC and send to structure
		temp16_1 = 0;
		for(int i=0; i<CHNL_MESR; i++)
		{
			buf_rw[i] = calibr_dat->clbr_coef[i];
			temp16_1 ^= buf_rw[i];
			buf_rw[i+CHNL_MESR] = calibr_dat->zero_level[i];
			temp16_1 ^= buf_rw[i+CHNL_MESR];
		}
		buf_rw[2*CHNL_MESR] = temp16_1;
		calibr_dat->crc = temp16_1;
		
		// And save received data to ROM
		STOP_SYSTICK();
		FlashUnLock();
		FlashErasePage(ADR_LAST_PAGE_FLASH);
		FlashWritePage(ADR_LAST_PAGE_FLASH, buf_rw, IN_CALIB_SAVE_AREA_VOL/2);
		FlashLock();
		START_SYSTICK();
	}
}



//-------- Correction of results taking into account calibration coefficients (   us) ---------
void CorrectVect(
				spectr_t *target_val,							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
				clbr_stts_t *calibr_dat,						// pointer on structure that contain control data for calibration
				spectr_t *calibr_val							// pointer on array of structures that contain calibrated datas for vectors calculated for 1st harmonics of directly measured signals
				)
{
	vect_t  temp_v;
	uint16_t temp16_1;
	
	for(chan_mes_t i=I_AH_MES; i<=U_F_MES; i++)
	{
		temp16_1 = calibr_dat->clbr_coef[i];

		// currents
		temp_v.re = (target_val[i].harm1.re * (int32_t)temp16_1) / 10000;
		temp_v.im = (target_val[i].harm1.im * (int32_t)temp16_1) / 10000;
		temp_v.ef_val = (target_val[i].harm1.ef_val * (int32_t)temp16_1) / 10000;
		temp_v.phase = target_val[i].harm1.phase;
		if(i>=U_A_MES && i<U_F_MES) 
		{
			CorrectPhase(&temp_v, &calibr_val[i].harm1);
		}
		else
		{
			calibr_val[i].harm1.re = temp_v.re;
			calibr_val[i].harm1.im = temp_v.im;
			calibr_val[i].harm1.ef_val = temp_v.ef_val;
			calibr_val[i].harm1.phase = temp_v.phase;
		}
	}
}


//------------------- Start transmit of calibration coefficients(    us) ----------------------
void StartTxCalibr	(
					uint8_t *tx_buf,
					clbr_stts_t *calibr_dat				// pointer on array of structures that contain control data for calibration
					)
{
	*(tx_buf+TX_CLBR_COM) = 0xa9;
	for(int i=0; i<CHNL_MESR; i++)
	{
		*(tx_buf+TX_CLBR_COEF+2*i) = (uint8_t)((calibr_dat->clbr_coef[i])>>8);
		*(tx_buf+TX_CLBR_COEF+2*i+1) = (uint8_t)(calibr_dat->clbr_coef[i]);
		*(tx_buf+TX_CLBR_ZRLV+2*i) = (uint8_t)((calibr_dat->zero_level[i])>>8);
		*(tx_buf+TX_CLBR_ZRLV+2*i+1) = (uint8_t)(calibr_dat->zero_level[i]);
	}
	*(tx_buf+TX_STATUS) &= ~(1<<ToCPU_Status_VersionAI_bit);
	*(tx_buf+TX_STATUS) |= (1<<ToCPU_Status_CalibrationCoefficients_bit);
}


//-------------------- Phase correction for voltage transformer (    us) -----------------------
void CorrectPhase	(
								vect_t *source_v,
								vect_t *correct_v
								)
{	
	uint32_t ranges[13] = 		{U_NG, 			(15*K_TV/10), 	(25*K_TV/10), 	(35*K_TV/10), 	(55*K_TV/10), 	(75*K_TV/10), 	(95*K_TV/10), 	(115*K_TV/10), 	(145*K_TV/10), 	(185*K_TV/10), 	(225*K_TV/10), 	(315*K_TV/10), 	(505*K_TV/10)	};
	uint16_t delta_phi[13] = 	{13, 			11, 			10, 			9, 				8, 				7, 				6, 				5, 				4, 				3, 				2, 				1, 				0				};
	uint8_t range = 12;
	volatile int32_t temp1, temp2;
	volatile int16_t cos, sin;
	
	// define range
	for(uint8_t i=0; i<13; i++)
	{
		if(source_v->ef_val <= ranges[i])
		{
			range = i;
			break;
		}
	}
	
	// if range = (0..12) then correct phase
	cos = Cosin(delta_phi[range]);
	sin = Sinus(delta_phi[range]);
	temp1 = source_v->re * cos;
	temp2 = source_v->im * sin;
	correct_v->re = (temp1 + temp2) / 1024; //-
	temp1 = source_v->im * cos;
	temp2 = source_v->re * sin;
	correct_v->im = (temp1 - temp2) / 1024; //+
	VectParam(correct_v, U_NG, W_PHASE_ANG); 
}


//---------------------------------------------------------------------------------------------
//                                    Privat functions
//---------------------------------------------------------------------------------------------


