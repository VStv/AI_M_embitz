//*********************************************************************************************
//                                          Main.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section
//---------------------------------------------------------------------------------------------
#include "main.h"

//---------------------------------------------------------------------------------------------
//                                        Constants
//---------------------------------------------------------------------------------------------
const uint16_t VersProg = (uint16_t)203;    										// v.2.03


//---------------------------------------------------------------------------------------------
//                                     Global variable
//---------------------------------------------------------------------------------------------
uint16_t 	VersBoot;
rtc_strct_t	Rtc_fact;
rtc_strct_t	Rtc_set;
rtc_strct_t	Rtc_sync;
uint32_t 	rtc_err = 0;

sample_t 	adc_sample = {0};   													// 1 ADC sample for channels: Ia_n, Ib_n, Ic_n, Ia_k, Ib_k, Ic_k, I0, Ua, Ub_lv, Ic_lv, In_1, In_2 & step number (0..23)
uint8_t		start_obr = 0;															// Flag that enables processing data in main
uint32_t	numb_Rec_byte, numb_Trans_byte, com_res;
clbr_stts_t	clbr_ctrl = {   FIN_CLBR,
                            0xff,
                            {10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL, 10032UL},
                            {32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL, 32767UL},
                            0,
                            0   };

osc_stts_t	osc_ctrl = {NO_REC, 0, 0, 0, 0, 0xff, 0, {0xff}, NO_OSC, NO_OUT, 0, 0, 0};
ver_ctrl_t	vers_ctrl = NO_VER;
set_stts_t	settng_upd_ctrl = {RCV_SET_STOP, NO_SET, 0, 0,};

uint8_t 	izmer[TX_BUF_SIZE];
uint8_t 	input[RX_BUF_SIZE];
setngs_t 	Coef = {1000UL, 1000UL, {100UL, 100UL}, 0UL, 20UL, 20UL, 150UL, 20UL, 293L, 293L, 378L, 293L, THERM_CONST_BASE, 3*THERM_CONST_BASE, 5*K_TA};
chan_bas_t	Basic = NONE;
uint8_t		Collect_buf[MapAISetings_Length+1];										// for received data (with settings) collection
prtct_set_t	Pr_settings[PROTECT_AMOUNT];
preemrg_t	preemrg_buf = {0};
uint32_t	Comparat[2] = {0}, Comp_final[2] = {0};
uint32_t	Stat_from_Cpu = 0, mtz_timers[TIMER_AMOUNT];
prerec_t	prerecord;
firmw_upd_t	firmw_ctrl = {0};

subspectr_t iu[CHNL_MESR];
spectr_t 	IU[CHNL_MESR], IU_clbr[CHNL_MESR], Uline[CHNL_LINE], Idif[CHNL_IDIFF];
FRZseq_t	IU_fr[3];
uint32_t 	Ibreak[3], DeltaI[2];
uint16_t	PhiUI[7];
vect_t		IU_rot[CHNL_ROTD], Ubnn;
power_t		Power;
therm_t		Therm_state = {0, THERM_CONST_BASE, 0, 0};
dat4freq_t 	dat4freq;
uint8_t		Emerg_phase[3] = {0xff, 0xff, 0xff};

uint32_t 	tmp_cycles_count, cycles_count[6] = {0};
uint8_t 	led_st = 5;																// 0 - off, 1 - on, 2 - blink (4Hz), 3 - flash (1Hz, width - 1/240), 4 - blink (50Hz)
uint32_t 	ram_adr = 0, test_cnt = 0;



//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//-------------------------- Load sinformation about versin (  us) ----------------------------
static void LoadTimeStruct	(
							uint8_t *rx_dat,
							rtc_ctrl_t rtc_cmd,
							rtc_strct_t	*rtc_dat
							)
{
	rtc_dat->time.year = *(rx_dat+RX_YEAR);
	rtc_dat->time.month = *(rx_dat+RX_MONTH);
	rtc_dat->time.mday = *(rx_dat+RX_MDAY);
	rtc_dat->time.hour = *(rx_dat+RX_HOUR);
	rtc_dat->time.min = *(rx_dat+RX_MIN);
	rtc_dat->time.sec = *(rx_dat+RX_SEC);
	rtc_dat->rtc_flag = rtc_cmd;
}


//--------------------------------- CPU comand processing -------------------------------------
static void CommandProcess(void)
{
	uint8_t temp8;
	volatile uint8_t cntrSum;
	volatile uint32_t temp32;

	// Processing of Stat_from_Cpu
	// 1 - check control sum
	cntrSum = 0;
	for(volatile int k1=0; k1<=ToAI_ToAI_Length - 1; k1++)
		cntrSum += input[k1];
	if(	cntrSum == input[ToAI_CSToAI_a]
		&&
		(input[_TRUE_byte] & (1<<_TRUE_bit)))
	{
		// 2 - processing bits
		if(input[_MTZ_1_byte] & (1<<_MTZ_1_bit))
			Stat_from_Cpu |= STAT_MTZ_1_MASK;
		else
			Stat_from_Cpu &= ~STAT_MTZ_1_MASK;

		if(input[_MTZ_2_byte] & (1<<_MTZ_2_bit))
			Stat_from_Cpu |= STAT_MTZ_2_MASK;
		else
			Stat_from_Cpu &= ~STAT_MTZ_2_MASK;

		if(input[_MTZ_3_byte] & (1<<_MTZ_3_bit))
			Stat_from_Cpu |= STAT_MTZ_3_MASK;
		else
			Stat_from_Cpu &= ~STAT_MTZ_3_MASK;

		if(input[_MTZ_4_byte] & (1<<_MTZ_4_bit))
			Stat_from_Cpu |= STAT_MTZ_4_MASK;
		else
			Stat_from_Cpu &= ~STAT_MTZ_4_MASK;

		if(input[_RPO_byte] & (1<<_RPO_bit))
			Stat_from_Cpu |= STAT_RPO_MASK;
		else
			Stat_from_Cpu &= ~STAT_RPO_MASK;

		if(input[_NCEVO_byte] & (1<<_NCEVO_bit))
			Stat_from_Cpu |= STAT_NCEVO_MASK;
		else
			Stat_from_Cpu &= ~STAT_NCEVO_MASK;

		if(input[_DN_byte] & (1<<_DN_bit))
			Stat_from_Cpu |= STAT_DN_MASK;
		else
			Stat_from_Cpu &= ~STAT_DN_MASK;

		if(input[_ACK_byte] & (1<<_ACK_bit))
			Stat_from_Cpu |= STAT_ACK_MASK;
		else
			Stat_from_Cpu &= ~STAT_ACK_MASK;

		if(input[_DI_BNN1_byte] & (1<<_DI_BNN1_bit))
			Stat_from_Cpu |= STAT_DI_BNN1_MASK;
		else
			Stat_from_Cpu &= ~STAT_DI_BNN1_MASK;

		if(input[_DI_BNN2_byte] & (1<<_DI_BNN2_bit))
			Stat_from_Cpu |= STAT_DI_BNN2_MASK;
		else
			Stat_from_Cpu &= ~STAT_DI_BNN2_MASK;
	}

	cntrSum = 0;
	switch(input[RX_COMAND])
	{
		case 0xA0:
		// Empty command, no data
			break;

		case 0xA1:
		// Command - set time/date, data - 6 bytes (dd:mm:yy hh:mm:ss)
			for(volatile int n1=ToAI_Command_a; n1<=RX_TIME_CRC; n1++)
				cntrSum ^= input[n1];
			if(cntrSum == 0 && Rtc_sync.timeout[1] > 60)
				LoadTimeStruct(input, RTC_SETUP, &Rtc_set);
			break;

		case 0xA2:
		// Command - calibrate channel, data - channel number (1 byte)
			if((input[RX_COMAND] ^ input[RX_CLBR_CHAN]) == input[RX_CLBR_CRC])
			{
				clbr_ctrl.cur_clbr_chan = input[RX_CLBR_CHAN];
				clbr_ctrl.clbr_stt = START_CLBR;
			}
			break;

		case 0xA3:
		// Command - save settings, data - pack number(1), pack volume(1), data for settings(210, 150 or 61), CRC(1)
			temp8 = input[RX_SET_BLCK_LEN];
			for(volatile int n2=RX_COMAND; n2<=(RX_SET_DATA+temp8); n2++)
				cntrSum ^= input[n2];
			if(cntrSum == 0)
			{
				ReceiveSettingsHandler(input, &settng_upd_ctrl);
			}
			break;

		case 0xA4:
		// Command - start oscilloscope, data - osc.num., osc. length (3 bytes)
			for(volatile int n3=RX_COMAND; n3<=RX_WR_OSC_CRC; n3++)
				cntrSum ^= input[n3];
			if(cntrSum == 0)
				StartRecOsc(input, izmer, &osc_ctrl);
			break;

		case 0xA5:
		// Command - transmit oscillogram, data - oscillogram number, point number (3 bytes)
			for(volatile int n4=RX_COMAND; n4<=RX_RD_OSC_CRC; n4++)
				cntrSum ^= input[n4];
			if(cntrSum == 0)
				StartReadOsc(input, izmer, &osc_ctrl);
			break;

		case 0xA6:
		// Command - erase oscillogram, data - no
			if(input[RX_COMAND] == input[RX_ERASE_CRC])
				ErasingOsc(&osc_ctrl);
			break;

		case 0xA7:
		// Command - transmit program version, data - no
			vers_ctrl = GET_VER;
			break;

		case 0xA8:
		// Command - prepare to device switch-off, data -
			if(input[RX_COMAND] == input[RX_OFF_CRC])
			{
				if(osc_ctrl.rec_st == REC_OSC)
				{
					if(osc_ctrl.cur_osc_num_adr != START_ADR_OSC_NUM_STRGE)
						temp32 = osc_ctrl.cur_osc_num_adr - 1 - START_ADR_OSC_NUM_STRGE;
					else
						temp32 = MAX_OSC_AMOUNT - 1;
					temp32 = temp32*4 + START_ADR_OSC_NUM_STRGE;
					temp8 = 0x5a;
					WriteByteToRam(ADR_PRESENCE_OSC_FLAG, &temp8);
					osc_ctrl.cur_osc_num = 0xff;
					osc_ctrl.remain_1st_part = 0;
					osc_ctrl.remain_2nd_part = 0;
					osc_ctrl.rec_st = REC_OSC;
				}

				// Save thermal model data in SRAM (Therm_state)
				SaveThermalState(Rtc_fact.s_counter, &Coef, &Therm_state);

				// reload rtc_soft to RTC_CNT
				RestoreSoftRtc(Rtc_fact.s_counter);
			}
			break;

		case 0xA9:
		// Command - transmit calibration coefficients, data - no
			clbr_ctrl.tx_clbr_ready = 0x04;
			break;

		case 0xAA:
		// Comand - synchronize RTC, data - 6 bytes (dd:mm:yy hh:mm:ss)
			for(int n1=RX_COMAND; n1<=RX_TIME_CRC; n1++)
				cntrSum ^= input[n1];
			if(cntrSum == 0)
				LoadTimeStruct(input, RTC_SYNC_START, &Rtc_sync);
			break;

		case 0xC0:
			INIT_FIRMW_UPDATE(firmw_ctrl);
			break;

		default:
		// error
			break;
	}
}





//---------------------------------------------------------------------------------------------
//                                        Main function
//---------------------------------------------------------------------------------------------
int main(void)
{
	uint8_t tx_dat_length, controlSum, tx_crc_pos;
	static int last_sec;
	static int fourier_timer = 24, fourier_en = 0/*, settngs_en = 0*/;

	__disable_irq();

#ifdef _BOOTLOADER_ON_
	SCB->VTOR = FLASH_ADR_USER_APP;															// vector interrupts table offset (if bootloader uses)
#endif
																							// can be used SPL function <void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset> from "misc.c"
#ifdef _TICK_COUNT_ON_
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; 										// Enable TRACE
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; 													// Enable tick counter
#endif

	SysTick_Config(SystemCoreClock/SYSTICK_IRQ_FREQ);								    	// 0.833(3)ms
	GpioInit();
	RtcInit();
//	rtc_err = RtcInit3(&rtc_err);


	TimerInit();
	Rtc_fact.summer_time_need = 0;
	Rtc_sync.timeout[1] = 100;
	LoadSoftRtc(&Rtc_fact);																	// Load software RTC
	ExtiInit();

	LedInit();

	VersBoot = ReadWordFlash(ADR_BOOT_VERS);
	ReadCalibrCoef(&clbr_ctrl);
	InitRecOsc(&osc_ctrl);
	InitThermalState(&Coef, &Therm_state);
	adc_sample.sample_num = 23;
	__enable_irq();

	while(1)
	{
		// firmware updating loop
		if(start_obr == 3)
		{
//#ifdef _BOOTLOADER_ON_
			FirmwUpdate(&numb_Rec_byte, input, &numb_Trans_byte, izmer, &firmw_ctrl);
//#endif
			start_obr = 0;
		}


		// normal mode loop
		if(start_obr == 2)
		{

#ifdef _TICK_COUNT_ON_
			DWT->CYCCNT = 0; 																// Reset tick counter
#endif

			AdcPolling(&adc_sample);														// receive data from ADC
			RecordingOsc(&adc_sample, &prerecord, &osc_ctrl, izmer);
			CalcSum(&adc_sample, iu);

			if(fourier_timer)
				fourier_timer--;
			else
				fourier_en = 1;

//// ----------- LED driver -------------
			LedCtrl(led_st);
//// ------------------------------------


			switch(adc_sample.sample_num)
			{
				case 0:
				case 6:
				case 12:
				case 18:
					// main computing procedures
					CalcVectPhase(&adc_sample, iu, IU);
					CorrectVect(IU, &clbr_ctrl, IU_clbr);

#ifdef _FREQ_MESURE_ON_
					CalcFreq(IU_clbr, &dat4freq);
#endif

					if(settng_upd_ctrl.sttus != NO_SET)
					{
						CalcVectLine(IU_clbr, Uline);
#if _AI_MX_ == _VER_M1_
						CalcVectDifCur(IU_clbr, Idif);
#endif
						CalcVectBreakCur(IU_clbr, &Coef, Ibreak, Pr_settings);
						CalcUnsymCur(IU_clbr, DeltaI);
						CalcUnbalVol(IU_clbr, &Coef, &Ubnn);

						DefBaseVect(IU_clbr, Uline, &Basic);
						RotVectors(IU_clbr, Uline, Idif, Basic, IU_rot);

						CalcVectFR(IU_clbr, Uline, IU_fr);
						CalcUIAngles(IU_rot, PhiUI);

						CalcPower(IU_rot, PhiUI, &Power);
						SavePreemrgCur(Comp_final, IU_rot, &preemrg_buf);
					}

					// pack data to transmit buffer
					PackInfTxBuf(IU_rot, IU_fr, DeltaI, Ibreak, &Power, PhiUI, &Ubnn, &dat4freq, &Therm_state, Emerg_phase, izmer);

					// get actual time from RTC
					GetTimeRtc(Rtc_fact.s_counter, &(Rtc_fact.time), Rtc_fact.summer_time_need);
					izmer[TX_YEAR] = Rtc_fact.time.year;
					izmer[TX_MONTH] = Rtc_fact.time.month;
					izmer[TX_MDAY] = Rtc_fact.time.mday;
					izmer[TX_HOUR] = Rtc_fact.time.hour;
					izmer[TX_MIN] = Rtc_fact.time.min;
					izmer[TX_SEC] = Rtc_fact.time.sec;
					izmer[TX_MLSEC] = (uint8_t)(Rtc_fact.ms_counter >> 8);
					izmer[TX_MLSEC+1] = (uint8_t)Rtc_fact.ms_counter;
					tx_crc_pos = TX_ADD_DAT;

					izmer[ToCPU_GT_a+0] = (uint8_t)(Rtc_fact.s_counter >> 24);
					izmer[ToCPU_GT_a+1] = (uint8_t)(Rtc_fact.s_counter >> 16);
					izmer[ToCPU_GT_a+2] = (uint8_t)(Rtc_fact.s_counter >> 8);
					izmer[ToCPU_GT_a+3] = (uint8_t)Rtc_fact.s_counter;

					// set new time to RTC
					if(Rtc_set.rtc_flag == RTC_SETUP)
					{
						Rtc_set.s_counter = PrepTime4Rtc(&(Rtc_set.time), Rtc_set.summer_time_need);
//						RestoreSoftRtc(Rtc_set.s_counter);														// send to hardware RTC
						Rtc_fact.s_counter = Rtc_set.s_counter;
						Rtc_set.rtc_flag = NO_CMD;
					}

					// syncronizing RTC
					switch(Rtc_sync.rtc_flag)
					{
						case RTC_SYNC_START:
							Rtc_sync.s_counter = PrepTime4Rtc(&(Rtc_sync.time), Rtc_sync.summer_time_need);
							Rtc_sync.rtc_flag = RTC_PPS_WAIT;
							Rtc_sync.timeout[0] = 12;															// set timeout 60ms
							NVIC_EnableIRQ(EXTI15_10_IRQn);														// enable ext_int
							break;

						case RTC_PPS_WAIT:
							// if timeout >60 ms - reset sync_flag
							--Rtc_sync.timeout[0];
							if(!Rtc_sync.timeout[0])
							{
								++Rtc_sync.rtc_err;
								NVIC_DisableIRQ(EXTI15_10_IRQn);
								Rtc_sync.rtc_flag = NO_CMD;
							}
							break;

						default:
							Rtc_sync.rtc_flag = NO_CMD;
							break;
					}

					if(settng_upd_ctrl.sttus == VALID)
					{
						// find motor thermal state
						if(Rtc_fact.time.sec != last_sec)
						{
							last_sec = Rtc_fact.time.sec;
							Therm_state.time_cnt++;
							if(Therm_state.time_cnt >= DELTA_T_TZP)
							{
								ThermModel(IU_rot, IU_fr, &Coef, &Therm_state);
								Therm_state.time_cnt = 0;
							}
						}
					}
					tx_crc_pos = TX_ADD_DAT;
					break;

				case 1:
				case 7:
				case 13:
				case 19:
					izmer[TX_STATUS] &= ~(	(1<<ToCPU_Status_IsDataOsc_bit)|
											(1<<ToCPU_Status_VersionAI_bit)|
											(1<<ToCPU_Status_DataFromOut_bit)|
											(1<<ToCPU_Status_CalibrationCoefficients_bit)|
											(1<<ToCPU_Status_SUCCESS_CALIBRATION_bit));

					// Processing of CPU command
					CommandProcess();

					// reading oscillogram (if it's need)
					if(izmer[TX_STATUS] & (1<<ToCPU_Status_IsDataOsc_bit))
					{
						ReadingOsc(&osc_ctrl, izmer);
						tx_crc_pos = TX_OSC_CRC;
					}
					break;

				case 2:
				case 8:
				case 14:
				case 20:
					// calibration & saving coefficient
					Calibrate(adc_sample, IU, &clbr_ctrl, izmer);
					break;

				case 3:
				case 9:
				case 15:
				case 21:
					// receive settings from CPU and store to collector buffer, finally - updates settings array
					ReceiveSettings(input, &settng_upd_ctrl, Collect_buf);
					if(settng_upd_ctrl.sttus == UPDATING)
					{
						// unzip settings
						UnzipSettings(Collect_buf, &Coef, Pr_settings, &Rtc_fact);
						// flag of unzip finalizing
						settng_upd_ctrl.sttus = UPDATED;
					}
					break;

				case 4:
				case 10:
				case 16:
				case 22:
					// clear blocker's & comparator's bytes in TX buffer
					izmer[ToCPU_Info_Bs_a] = 0;
					izmer[ToCPU_Compar_a] = 0;

					// protection procedures
					if(settng_upd_ctrl.sttus != NO_SET)
					{
#ifdef _PROTECTION_ON_
						ProtectBNN(IU_rot, &Ubnn, IU_fr, Pr_settings, Stat_from_Cpu, Comparat);					// !!!!!!!!
						ComparKAM(&Power, Pr_settings, Stat_from_Cpu, Comparat);								// !!!!!!!!
						ProtectIPD(IU_rot, Pr_settings, Stat_from_Cpu, Comparat);								// !!!!!!!!
						ProtectZZP_ZBR(IU_rot, Pr_settings, Comparat);											// !!!!!!!!
						ProtectOBR(IU_fr, Pr_settings, Comparat);												// !!!!!!!!
						ProtectZF(&dat4freq, Pr_settings, Stat_from_Cpu, Comparat);								// !!!!!!!!
						ProtectTZP(&Therm_state, Pr_settings, Comparat);										// !!!!!!!!
#if _AI_MX_ == _VER_M1_
						ProtectDN(IU_rot, Pr_settings, Comparat);												// !!!!!!!!
						ProtectDT(IU_rot, Pr_settings, Stat_from_Cpu, Comparat);								// !!!!!!!!
						ProtectDO(IU_rot, Pr_settings, Stat_from_Cpu, Comparat);								// !!!!!!!!
#else
						Comparat[0] &= ~(COMP_DN_MASK | COMP_DO_MASK | COMP_DT_MASK);
#endif
						ProtectUROV(IU_rot, Pr_settings, Comparat);												// !!!!!!!!
						ProtectAPV(IU_rot, Pr_settings, Comparat);												// !!!!!!!!
						ProtectZMT(IU_rot, Pr_settings,	Comparat);												// !!!!!!!!
						ProtectZVS(&Power, PhiUI, Pr_settings, Comparat);										// !!!!!!!!
						ProtectZNR(IU_rot, DeltaI, Pr_settings,	Comparat);										// !!!!!!!!
						ProtectZNZ(IU_rot, PhiUI, Pr_settings, Comparat, Emerg_phase);							// !!!!!!!!
						ProtectZN(IU_rot, IU_fr, Pr_settings, Comparat);										// !!!!!!!!
						ProtectMTZ(mtz_timers, IU_rot, PhiUI, IU_fr, Pr_settings, &preemrg_buf, Stat_from_Cpu, Comparat);	//
#endif

						if(settng_upd_ctrl.sttus == UPDATED)
							settng_upd_ctrl.sttus = TESTED;
					}
					TrigShmidt4Compar(Comparat, Comp_final);

					// Pack blocker's & comparator's states in TX buffer
					PackCmpr4Txd(Comp_final, izmer);

					// form packet with calibration & service data for next transmition
					if(clbr_ctrl.tx_clbr_ready == 0x04)
					{
						StartTxCalibr(izmer, &clbr_ctrl);
						tx_crc_pos = TX_CLBR_CRC;
						clbr_ctrl.tx_clbr_ready = 0;
					}

					// send version info
					if(vers_ctrl)
					{
						izmer[TX_VER_0] = 0xa7;
						izmer[TX_VER_1] = (uint8_t)(VersProg>>8);
						izmer[TX_VER_2] = (uint8_t)VersProg;
						izmer[TX_VER_3] = (uint8_t)(VersBoot>>8);
						izmer[TX_VER_4] = (uint8_t)VersBoot;
						tx_crc_pos = TX_VER_CRC;
						vers_ctrl = NO_VER;
						izmer[TX_STATUS] |= (1<<ToCPU_Status_VersionAI_bit);
					}

					// form head of packet
					tx_dat_length = tx_crc_pos+1;
					izmer[TX_BUF_SIGN] = 0;
					izmer[TX_BUF_LENGTH] = tx_dat_length;

					// processing status-byte of TX-buffer
					if(fourier_en == 1 && settng_upd_ctrl.sttus == VALID)
						izmer[TX_STATUS] |= (1<<ToCPU_Status_COMPARATORS_IS_VALID_bit);
					else
						izmer[TX_STATUS] &= ~(1<<ToCPU_Status_COMPARATORS_IS_VALID_bit);

					// if settings updated & tested then settings validate flag set
					if(settng_upd_ctrl.sttus == TESTED)
						settng_upd_ctrl.sttus = VALID;

					// calculate checksum
					controlSum = 0;
					for(int i=0; i<tx_crc_pos; i++)
						controlSum ^= izmer[i];
					izmer[tx_crc_pos] = controlSum;

					// clear receive buffer
					for(int i=0; i<(RX_BUF_SIZE-1); i++)
						input[i] = 0;
					break;

				case 5:
				case 11:
				case 17:
				case 23:
					// data exchange with CPU
					__disable_irq();
					com_res = TxRxCpu(izmer, &tx_dat_length, &numb_Trans_byte, input, &numb_Rec_byte);
					__enable_irq();
					break;

				default:
					break;
			}
			start_obr = 0;
//			if(rtc_err != (int32_t)(-1))
//				rtc_err = RtcInit(&rtc_err);
#ifdef _TICK_COUNT_ON_
			// Read tick counter
			tmp_cycles_count = DWT->CYCCNT;
			if(tmp_cycles_count > cycles_count[adc_sample.sample_num % 6])
			{
				cycles_count[adc_sample.sample_num % 6] = tmp_cycles_count;
				if(tmp_cycles_count > (SystemCoreClock/SYSTICK_IRQ_FREQ))
					led_st = 2;
			}
#endif
		}
	}
}
