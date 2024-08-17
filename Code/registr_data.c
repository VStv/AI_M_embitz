//*********************************************************************************************
//                                      Registr_data.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                      Include section 
//---------------------------------------------------------------------------------------------
#include "registr_data.h"


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//---------------------------------- Data prerecord ( us) -------------------------------------
void PrerecDat	(
				sample_t *adc_dat, 							// structure that contains actual ADC sample for all channel and sample's number
				prerec_t *prerec_dat						// pointer on structure that contains prerecorded data and index of last recorded word 
				)
{
	uint32_t ind;
	
	ind = prerec_dat->index;
	for(chan_mes_t ch=I_AH_MES; ch<=U_F_MES; ch++)
		prerec_dat->buffer[ind][ch] = adc_dat->sample[ch];

	ind++;
	if(ind > PREREC_BUF_SIZE-1) 
		ind = 0;
	prerec_dat->index = ind;
}


//------------------ Transform array of 16-bit values to byte array ( us) ---------------------
void Resize16to8(
				uint16_t *s_buf,
				uint8_t *d_buf, 
				uint32_t cnt
				)
{
	uint16_t temp16;
	
	for(uint32_t i=0; i<cnt; i++)
	{
		temp16 = *(s_buf+i);
		*(d_buf+2*i) = (uint8_t)(temp16>>8);
		*(d_buf+2*i+1) = (uint8_t)temp16;
	}
}


//--------------------------- Record data to exterhal SRAM ( us) ------------------------------
void RecordingOsc	(
					sample_t *adc_dat, 						// pointer on structure that contains actual ADC sample for all channel and sample's number
					prerec_t *prerec_dat, 					// pointer on structure that contains prerecorded data and index of last recorded word 
					osc_stts_t *oscill_ctrl,				// pointer on structure that contains data for oscilloscope function control
					uint8_t *tx_dat							// 
					)
{
	// We have enter in procedure after making the following (in function that processes recieved comand from CPU):
	// - we must define number of new oscillogram 
	// - we must calculate 
	
	uint16_t temp16_buf[CHNL_MESR];
	uint8_t temp8_buf[2*CHNL_MESR], temp8;
	uint32_t ind;
	
	if(oscill_ctrl->rec_st == REC_OSC) 
	{
		if(oscill_ctrl->remain_2nd_part)					// check complit recording of 2nd part of oscillogram
		{													// if not complit - continue recording of 2nd part 
			// write data to SRAM
			Resize16to8(adc_dat->sample, temp8_buf, CHNL_MESR);
			WriteArrayToRam(oscill_ctrl->cur_adr_2nd_p, temp8_buf, 2*CHNL_MESR);
			oscill_ctrl->cur_adr_2nd_p += 2*CHNL_MESR;
			if(oscill_ctrl->cur_adr_2nd_p > END_ADR_OSC) 
				oscill_ctrl->cur_adr_2nd_p = START_ADR_OSC;

			// save current adress to SRAM
			WriteWordToRam(ADR_STRGE_CUR_REC_ADR, &(oscill_ctrl->cur_adr_2nd_p));
			oscill_ctrl->remain_2nd_part--;
			if(oscill_ctrl->remain_2nd_part == 0) 
				*(tx_dat+TX_STATUS) &= ~(1<<ToCPU_Status_Write_Osc_bit);
		}
		else if(oscill_ctrl->remain_1st_part)				// else records data from prerecord buffer. First - check complit recording of 1st part of oscillogram - from prerecord buffer
		{													// if not complit - continue recording of the 1st part 
			for(chan_mes_t ch=I_AH_MES; ch<=U_F_MES; ch++)	// copy data from prerecord buffer in temp_buf[]
			{
				ind = prerec_dat->index;
				temp16_buf[ch] = prerec_dat->buffer[ind][ch];
			}
			PrerecDat(adc_dat, prerec_dat);

			// write data to SRAM
			Resize16to8(temp16_buf, temp8_buf, CHNL_MESR);
			WriteArrayToRam(oscill_ctrl->cur_adr_1st_p, temp8_buf, 2*CHNL_MESR);
			oscill_ctrl->cur_adr_1st_p += 2*CHNL_MESR;
			if(oscill_ctrl->cur_adr_1st_p > END_ADR_OSC) 
				oscill_ctrl->cur_adr_1st_p = START_ADR_OSC;
			oscill_ctrl->remain_1st_part--;
		}
		else												// else - record complit. Finishing procedure
		{
			PrerecDat(adc_dat, prerec_dat);

			// updates structures with control oscilloscope data, finishing procedure
			temp8 = 0x3c;
			WriteByteToRam(ADR_PRESENCE_OSC_FLAG, &temp8);
			oscill_ctrl->cur_osc_num = 0xff;				// reset current oscillogram number
			oscill_ctrl->rec_st = NO_REC;					// reset recording
		}
	}
	else 													// reset recording flag in status-byte of TxD-pack
		PrerecDat(adc_dat, prerec_dat);
}


//----------------------- Start recording data to exterhal SRAM ( us) -------------------------
void StartRecOsc(
				uint8_t *rx_data,							// pointer on array of symbols recieved from CPU
				uint8_t *tx_data,							// pointer on array of symbols transmitted to CPU
				osc_stts_t *oscill_ctrl						// pointer on structure that contains control data of oscilloscope
				)
// Before entering this procedure (in ComandProces()):
//	1) check comand,
//	2) check control sum
{
	uint32_t offset, temp;
	
	if(oscill_ctrl->rec_st == NO_REC) 
	{
		// set recording flag in status-byte of TxD-pack
		*(tx_data+TX_STATUS) |= (uint8_t)(1<<ToCPU_Status_Write_Osc_bit);

		// Oscillogram number recording
		offset = oscill_ctrl->cur_osc_num_adr - START_ADR_OSC_NUM_STRGE;
		oscill_ctrl->num_store[offset] = *(rx_data+RX_WR_OSC_NUM);
		oscill_ctrl->cur_osc_num = *(rx_data+RX_WR_OSC_NUM);
		WriteByteToRam(oscill_ctrl->cur_osc_num_adr, (uint8_t *)&(oscill_ctrl->cur_osc_num));
		
		// Oscillogram start adress recording
		temp = 4*offset + START_ADR_OSC_ADR_STRGE;
		WriteWordToRam(temp, &(oscill_ctrl->cur_adr_2nd_p));
		oscill_ctrl->cur_adr_1st_p = oscill_ctrl->cur_adr_2nd_p;
		temp = oscill_ctrl->cur_adr_2nd_p + PREREC_BUF_SIZE*CHNL_MESR*2;
		if(temp > END_ADR_OSC) 
		{
			temp -= END_ADR_OSC;
			oscill_ctrl->cur_adr_2nd_p = START_ADR_OSC + temp;
		}
		else 
			oscill_ctrl->cur_adr_2nd_p = temp;
		
		// Oscillogram length recording in external SRAM
		temp = START_ADR_OSC_LEN_STRGE + offset*2;
		WriteByteToRam(temp, rx_data+RX_WR_OSC_LNG_H);
		temp++;
		WriteByteToRam(temp, rx_data+RX_WR_OSC_LNG_L);
		
		// Define length of prerecording (1st part) and realtime recording (2nd part) (in records)
		temp = ((uint32_t)*(rx_data+RX_WR_OSC_LNG_H)<<8) | (uint32_t)*(rx_data+RX_WR_OSC_LNG_L);
		if(temp < MIN_REC_TIME)
			temp = MIN_REC_TIME;
		temp = temp * RECORDS_AT_1SEC;
		oscill_ctrl->remain_2nd_part = temp/1000 - RECORDS_AT_1SEC/2;
		oscill_ctrl->remain_1st_part = RECORDS_AT_1SEC/2;
		
		// update oscillogram number
		(oscill_ctrl->cur_osc_num_adr)++;
		if(oscill_ctrl->cur_osc_num_adr > END_ADR_OSC_NUM_STRGE) 
			oscill_ctrl->cur_osc_num_adr = START_ADR_OSC_NUM_STRGE;
		offset = oscill_ctrl->cur_osc_num_adr - START_ADR_OSC_NUM_STRGE;
		WriteByteToRam(ADR_CUR_NUM_OSC, (uint8_t *)&offset);
		
		// record enables
		oscill_ctrl->rec_st = REC_OSC;
	}
}


//------------- Initialization of recording to exterhal SRAM procedures ( us) -----------------
void InitRecOsc	(
				osc_stts_t *oscill_ctrl														// pointer on structure that contains control data of oscilloscope
				)
{
	uint8_t temp8;
	
	ReadByteFromRam(ADR_PRESENCE_OSC_FLAG, &temp8);
	if(temp8 == 0x3c)
	{
		// reading from SRAM current adress of recording (oscill_ctrl.cur_adr_2nd_p)
		ReadWordFromRam(ADR_STRGE_CUR_REC_ADR,	&(oscill_ctrl->cur_adr_2nd_p));
		
		// reading from SRAM array of oscillogram numbers
		ReadArrayFromRam(START_ADR_OSC_NUM_STRGE, oscill_ctrl->num_store, MAX_OSC_AMOUNT);
		
		// reading from SRAM current oscillogram index 
		ReadByteFromRam(ADR_CUR_NUM_OSC, &temp8);
		
		// setting current adress for recording of current oscillogram number
		if(temp8 > MAX_OSC_AMOUNT) 
			temp8 = 0;
		oscill_ctrl->cur_osc_num_adr = temp8 + START_ADR_OSC_NUM_STRGE;
	}
	else
	{
		// initializing of current adress of recording (oscill_ctrl.cur_adr_2nd_p)
		oscill_ctrl->cur_adr_2nd_p = START_ADR_OSC;
		
		// initializing of oscillogram numbers array in SRAM
		for(int i=0; i<MAX_OSC_AMOUNT; i++) 
			oscill_ctrl->num_store[i] = 0xff;
		WriteArrayToRam(START_ADR_OSC_NUM_STRGE, oscill_ctrl->num_store, MAX_OSC_AMOUNT);
		
		// initializing current adress for recording of current oscillogram number
		oscill_ctrl->cur_osc_num_adr = START_ADR_OSC_NUM_STRGE;
	}
}


//---------------- Read data from external SRAM & filling TX-buffer p.1( us) ------------------
void ReadingOsc	(
				osc_stts_t *oscill_ctrl,					// pointer on structure that contains control data of oscilloscope
				uint8_t *tx_data 							// pointer on array transmitted to CPU
				)
{
	uint32_t temp32_1, temp32_2;

	// if oscillogram isn't found, send to TX buffer request osc. number, request point number and array of 0xff as content
	if(oscill_ctrl->osc_pres_st == NO_OSC)
	{
		*(tx_data+TX_OSC_NUM) = oscill_ctrl->rqst_osc_num;
		*(tx_data+TX_OSC_POINT_NUM) = (uint8_t)((oscill_ctrl->rqst_point_num)>>8);
		*(tx_data+TX_OSC_POINT_NUM+1) = (uint8_t)(oscill_ctrl->rqst_point_num);
		for(int i=TX_OSC_POINT_1; i<TX_OSC_POINT_1+3*CHNL_MESR*2; i++)  
			*(tx_data+i) = 0xff;
		oscill_ctrl->osc_pres_st = OSC_PRES;
	}
	
	// else if oscillogram is found, but flag "Oscillogram output" is reset, send to TX buffer array of 0xff as content
	else if(oscill_ctrl->out_st == NO_OUT)
	{
		for(int i=TX_OSC_NUM; i<TX_OSC_POINT_1+(2*3*CHNL_MESR); i++)  
			*(tx_data+i) = 0xff;
	}
	
	// else if flag "Oscillogram output" is set, send to TX buffer requested information from external SRAM
	else
	{
		temp32_1 = oscill_ctrl->rqst_osc_adr + (2*3*CHNL_MESR - 1);
		if(temp32_1 > END_ADR_OSC)
		{
			temp32_2 = temp32_1 - END_ADR_OSC;
			temp32_1 = (2*3*CHNL_MESR) - temp32_2;
			ReadArrayFromRam((oscill_ctrl->rqst_osc_adr), (tx_data+TX_OSC_POINT_1), temp32_1);
			ReadArrayFromRam(START_ADR_OSC, (tx_data+TX_OSC_POINT_1+temp32_1), temp32_2);
		}
		else
			ReadArrayFromRam((oscill_ctrl->rqst_osc_adr), (tx_data+TX_OSC_POINT_1), (2*3*CHNL_MESR));

		*(tx_data+TX_OSC_NUM) = oscill_ctrl->rqst_osc_num;
		*(tx_data+TX_OSC_POINT_NUM) = (uint8_t)((oscill_ctrl->rqst_point_num)>>8);
		*(tx_data+TX_OSC_POINT_NUM+1) = (uint8_t)(oscill_ctrl->rqst_point_num);
		oscill_ctrl->out_st = NO_OUT;
	}
}


//----------------- Read data from exterhal SRAM & filling TX-buffer ( us) --------------------
void StartReadOsc	(
					uint8_t *rx_data, 						// pointer on array of symbols recieved from CPU
					uint8_t *tx_data,						// 
					osc_stts_t *oscill_ctrl					// pointer on structure that contains control data of oscilloscope
					)
// Before entering this procedure (in ComandProces()):
//	1) check comand,
//	2) check control sum,
{
	uint8_t temp8;
	uint32_t temp32;

	*(tx_data+TX_STATUS) |= (1<<ToCPU_Status_IsDataOsc_bit);
	
	// Read number of request oscillogram from array recieved from CPU
	oscill_ctrl->rqst_osc_num = *(rx_data+RX_RD_OSC_NUM);
	
	// If number of request oscillogram is OK then process continues
	if((oscill_ctrl->rqst_osc_num != oscill_ctrl->cur_osc_num) && (oscill_ctrl->rqst_osc_num != 0xff))
	{
		oscill_ctrl->rqst_point_num = ((uint16_t)((*(rx_data+RX_RD_OSC_PNT_H))<<8) | (uint16_t)(*(rx_data+RX_RD_OSC_PNT_L)));
		temp8 = 0xff;
		for(int n=0; n<MAX_OSC_AMOUNT; n++)
		{
			if(oscill_ctrl->rqst_osc_num == oscill_ctrl->num_store[n])
			{
				temp8 = (uint8_t)n;
				oscill_ctrl->osc_pres_st = OSC_PRES;		//!!!!!!!!!!!!!
				break;
			}
		}
		if(temp8 < MAX_OSC_AMOUNT)
		{
			temp32 = START_ADR_OSC_ADR_STRGE + ((uint32_t)temp8) * 4;
			ReadWordFromRam(temp32, &(oscill_ctrl->rqst_osc_adr));
			if(oscill_ctrl->rqst_osc_adr >= START_ADR_OSC)
			{
				temp32 = oscill_ctrl->rqst_osc_adr + (uint32_t)((oscill_ctrl->rqst_point_num)*(2*CHNL_MESR));
				if(temp32 > END_ADR_OSC) 
					oscill_ctrl->rqst_osc_adr = START_ADR_OSC + (temp32 - END_ADR_OSC) - 1;
				else 
					oscill_ctrl->rqst_osc_adr = temp32;
				oscill_ctrl->out_st = OUT_OSC;
			}
			else 
				oscill_ctrl->osc_pres_st = NO_OSC;
		}
		else 
			oscill_ctrl->osc_pres_st = NO_OSC;
	}

	// Else sets flag
	else 
		oscill_ctrl->osc_pres_st = NO_OSC;
}



//-------------------------- Erase data from exterhal SRAM ( us) ------------------------------
void ErasingOsc	(
				osc_stts_t *oscill_ctrl						// pointer on structure that contains control data of oscilloscope
				)
{
	uint8_t temp8;

	// initializing of oscillogram numbers array in SRAM
	for(int i=0; i<MAX_OSC_AMOUNT; i++) 
		oscill_ctrl->num_store[i] = 0xff;
	WriteArrayToRam(START_ADR_OSC_NUM_STRGE, oscill_ctrl->num_store, MAX_OSC_AMOUNT);

	// initializing of current adress of recording (oscill_ctrl.cur_adr_2nd_p)
	oscill_ctrl->cur_adr_2nd_p = START_ADR_OSC;

	// initializing current adress for recording of current oscillogram number
	oscill_ctrl->cur_osc_num_adr = START_ADR_OSC_NUM_STRGE;

	// update oscillogram number
	temp8 = 0;
	WriteByteToRam(ADR_CUR_NUM_OSC, &temp8);
	
	temp8 = 0x00;
	WriteByteToRam(ADR_PRESENCE_OSC_FLAG, &temp8);
}




