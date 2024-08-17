//*********************************************************************************************
//                                        Oper_val.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "oper_val.h"


//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------
extern const int16_t SIN1_TAB[48];
extern const int16_t COS1_TAB[48];


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//--------------- Calculation of integral sums for vectors (directly) (  us) ------------------
void CalcSum(
			sample_t *adc_dat,										// pointer on structure that contains ADC sample for all channel and sample's number
			subspectr_t *intermed_val 								// pointer on array of structures that contain running cos & sin sums for fourier coef. calculated for 1st harmonics
			)
{
	for(chan_mes_t i=I_AH_MES; i<=U_F_MES; i++)								
	{
		FourierSum(adc_dat, i, 1, &intermed_val[i].subharm1);	 	// 1-st harmonic
	}
}


//------------------ Calculation of vector's parameters (directly) (  us) ---------------------
void CalcVectPhase	(
					sample_t *adc_dat,								// pointer on structure that contains ADC sample for all channel and sample's number
					subspectr_t *intermed_val, 						// pointer on array of structures that contain running cos & sin sums for fourier coef. calculated for 1st harmonics
					spectr_t *target_val							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals - result
					)
{
	uint32_t min_val;
	
	for(chan_mes_t i=I_AH_MES; i<=U_F_MES; i++)								
	{
		if(i<U_A_MES)	
			min_val = I_NG;
		else 			
			min_val = U_NG;
		FourierVect(adc_dat->sample_num, 1, min_val, W_PHASE_ANG, &intermed_val[i].subharm1, &target_val[i].harm1);
	}
#if _AI_MX_ == _VER_M2_
	for(chan_mes_t j=I_AK_MES; j<=I_CK_MES; j++)								
	{
		target_val[j].harm1.re = 0;
		target_val[j].harm1.im = 0;
		target_val[j].harm1.ef_val = 0;
		target_val[j].harm1.phase = 0xffff;
	}
#endif		
}


//----------------- Calculation of vector's parameters (line values) (  us) -------------------
void CalcVectLine	(
					spectr_t *target_val,							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
					spectr_t *line_val								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of line values measured signals - result
					)
{
	vect_t *p_temp_v;
	uint32_t k;
	
	for(phases_t i=ph_A; i<=ph_C; i++)
	{
		if(i == ph_C) 
			k = ph_A;
		else 
			k = i+1;

		p_temp_v = &((line_val+i)->harm1);
		p_temp_v->re = target_val[U_A_MES+i].harm1.re - target_val[U_A_MES+k].harm1.re;
		p_temp_v->im = target_val[U_A_MES+i].harm1.im - target_val[U_A_MES+k].harm1.im;
		VectParam(p_temp_v, U_NG, W_PHASE_ANG);
	}
}


//-------- Calculation of vector's parameters (forward and reverse sequence) (  us) -----------
void CalcVectFR (
				spectr_t *target_val,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
				spectr_t *line_val,									// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of line values measured signals - result
//				vect_t *rotated,									// pointer on array of structures that contain datas for rotated vectors 
				FRZseq_t *frz_seq									// pointer on array of structures that contain datas for vectors calculated for 1st harmonic of currents of forward, reverse sequence and its relations - result
				)
{
	int32_t re_[3], im_[3]; 
	int64_t	temp;
	uint32_t temp32;
	spectr_t *p_spec, *pntr[3];
	chan_rot_t p_chan[3] = 	{I_AH_ROT, 	I_AK_ROT, 	0};
	uint32_t min_val[3] = 	{I_NG, 		I_NG,		U_NG	};
	
	pntr[0] =  target_val;
	pntr[1] =  target_val;
	pntr[2] =  line_val;
	
	for(int j=0; j<3; j++)							
	{
		for(phases_t i=ph_A; i<=ph_C; i++)													// take Re and Im values for all phase current
		{
			p_spec = pntr[j] + p_chan[j] + i;
			re_[i] = p_spec->harm1.re;
			im_[i] = p_spec->harm1.im;
		}

		temp = re_[ph_A] * COS1_TAB[0] + (re_[ph_B] + re_[ph_C]) * COS1_TAB[8] + (im_[ph_B] - im_[ph_C]) * SIN1_TAB[8];
		temp = temp / 3072;
		frz_seq[j].reverse.re = (int32_t)temp;
		temp = im_[ph_A] * COS1_TAB[0] + (im_[ph_B] + im_[ph_C]) * COS1_TAB[8] + (re_[ph_C] - re_[ph_B]) * SIN1_TAB[8];
		temp = temp / 3072;
		frz_seq[j].reverse.im = (int32_t)temp;
		VectParam(&(frz_seq[j].reverse), min_val[j], W_EF_VAL);								// find reverse sequence current

		temp = re_[ph_A] * COS1_TAB[0] + (re_[ph_B] + re_[ph_C]) * COS1_TAB[8] + (im_[ph_C] - im_[ph_B]) * SIN1_TAB[8];
		temp = temp / 3072;
		frz_seq[j].forward.re = (int32_t)temp;
		temp = im_[ph_A] * COS1_TAB[0] + (im_[ph_B] + im_[ph_C]) * COS1_TAB[8] + (re_[ph_B] - re_[ph_C]) * SIN1_TAB[8];
		temp = temp / 3072;
		frz_seq[j].forward.im = (int32_t)temp;
		VectParam(&(frz_seq[j].forward), min_val[j], W_EF_VAL);								// find forward sequence current

		if(frz_seq[j].forward.ef_val > min_val[j])											// relation of reverse and forward sequence currents 
		{
			temp32 = (frz_seq[j].reverse.ef_val * 100) / frz_seq[j].forward.ef_val;
			if(temp32 > 6500) frz_seq[j].relat_r2f = 6500;
			else frz_seq[j].relat_r2f = temp32;
		}
		else frz_seq[j].relat_r2f = 0;
	}
}


//------------- Calculation of vector's parameters (differential currents) (  us) -------------
void CalcVectDifCur	(
					spectr_t *target_val,						// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
//					setngs_t *coef, 								// structures that contains coeffitients
					spectr_t *diff_cur							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of differential currents - result
					)
{
	int32_t re_x_y[6], im_x_y[6];
	int32_t temp2;
	
	// 1st harmonic
	for(chan_mes_t n=I_AH_MES; n<I_0_MES; n++)							// load Re & Im projections of phase currents
	{
		re_x_y[n] = target_val[n].harm1.re;
		im_x_y[n] = target_val[n].harm1.im;
	}
	for(phases_t j=ph_A; j<=ph_C; j++)
	{
		temp2 = /*coef.align[0] * */re_x_y[j] + /*coef.align[1] * */re_x_y[j+3];
		diff_cur[j].harm1.re = (int32_t)(temp2);//100
		temp2 = /*coef.align[0] * */im_x_y[j] + /*coef.align[1] * */im_x_y[j+3];
		diff_cur[j].harm1.im = (int32_t)(temp2);//100
		VectParam(&(diff_cur[j].harm1), I_NG, W_PHASE_ANG);
	}
}


////------------------- Calculation of parameters (breaking currents)(  us) ---------------------
//void CalcVectBreakCur	(
//						spectr_t *target_val,						// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
//						setngs_t *coef, 							// pointer on structures that contains coeffitients
//						uint32_t *break_cur,							// pointer on array that contains datas for breaking currents vectors - result
//						prtct_set_t *i_set							// pointer on array of structures that contain datas for protect settings
//						)
//{
//	uint32_t temp5, temp32;
//	
//	for(phases_t j=ph_A; j<=ph_C; j++)
//	{
//		temp5 = coef->k_t[0] * target_val[j].harm1.ef_val + coef->k_t[1] * target_val[j+3].harm1.ef_val;
//		break_cur[j] = temp5/100;

//		if(break_cur[j]<coef->i_t0)
//		{
//			temp32 = coef->i_dt0;
//		}
//		else if(break_cur[j]>=coef->i_t0 && break_cur[j]<coef->i_tlim) 
//		{
//			temp32 = coef->i_dt0 + ((break_cur[j] - coef->i_t0) * coef->k_br) / 100;
//		}
//		else 
//		{
//			temp32 = coef->i_dt0 + ((coef->i_tlim - coef->i_t0) * coef->k_br) / 100; 
//		}
//		i_set[DT_cmp].trshld[j] 		= temp32;											// in rel. units    
//		i_set[DT_cmp].k_retrn[j] 		= 95;												// in %  		
//		
//	}
////	for(phases_t i=ph_A; i<=ph_C; i++)
////	{

////	}	
//}


//---------------- Calculation of parameters (unsymmetrical currents)(  us) -------------------
void CalcUnsymCur	(
					spectr_t *target_val,							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
					uint32_t *del_cur								// pointer on array that contains datas for unsymmetrical currents - result
					)
{
	uint32_t min, max;
	uint32_t val[3];
	
	for(int j=0; j<2; j++)
	{
		for(int k=0; k<3; k++) 
			val[k] = target_val[3*j+k].harm1.ef_val;
		max = val[FindExtrElem(val, 3, MAXIM)];
		min = val[FindExtrElem(val, 3, MINIM)];
		if(max<I_NG) 
			del_cur[j] = 0;
		else 
			del_cur[j] = ((max - min) * 100) / max;
	}
}


//------------------ Calculation of parameters (unbalansed voltage)(  us) ---------------------
void CalcUnbalVol	(
					spectr_t *target_val,							// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
					setngs_t *coef, 									// structures that contains coeffitients
					vect_t *unbal_vol								// pointer on value of unbalansed voltage - result
					)
{
	int32_t re_, im_;
	
	re_ = (target_val[U_A_MES].harm1.re + target_val[U_B_MES].harm1.re + target_val[U_C_MES].harm1.re); 
	unbal_vol->re = re_ + (target_val[U_0_MES].harm1.re * (int32_t)coef->ktv0) / (int32_t)coef->ktv;
	
	im_ = (target_val[U_A_MES].harm1.im + target_val[U_B_MES].harm1.im + target_val[U_C_MES].harm1.im); 
	unbal_vol->im = im_ + (target_val[U_0_MES].harm1.im * (int32_t)coef->ktv0) / (int32_t)coef->ktv;
	
	VectParam(unbal_vol, U_NG, W_EF_VAL);
}


//------------------------------ Base vector computing (  us) ---------------------------------
void DefBaseVect(
				spectr_t *target_val,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
				spectr_t *line_val,									// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of line values measured signals
				chan_bas_t *Vbas									// pointer on variable that contains basic vector
				)
{
	vect_t *p_vect;
	uint32_t temp_min, min_val[CHNL_BASE] = {	U_NG, 		U_NG, 		U_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG0, 		U_NG,		U_NG, 		U_NG, 		U_NG};
	chan_bas_t temp_chan, order[CHNL_BASE]= {	U_A_BAS, 	U_B_BAS, 	U_C_BAS, 	I_AH_BAS, 	I_BH_BAS, 	I_CH_BAS, 	I_AK_BAS, 	I_BK_BAS, 	I_CK_BAS, 	I_0_BAS, 	U_0_BAS,	U_AB_BAS, 	U_BC_BAS, 	U_CA_BAS}; // define processing order
	
	//now we can refer to vectors that concerns to different structure
	for(uint32_t k=0; k<CHNL_BASE; k++)
	{
		temp_chan = order[k];
		temp_min = min_val[k];

		if(temp_chan<U_AB_BAS) 
			p_vect = &(target_val[temp_chan].harm1);
		else 
			p_vect = &(line_val[temp_chan - U_AB_BAS].harm1);

		if(p_vect->ef_val > temp_min)
		{
			*Vbas = temp_chan;
			return;
		}
	}
	*Vbas = NONE;
}


//-------------------- Rotation of vectors relative to the basic (15us) -----------------------
void RotVectors	(
				spectr_t *target_val,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
				spectr_t *line_val,									// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of measured signals considering to digital assemble
				spectr_t *diff_cur,									// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of differential currents
				chan_bas_t Vbas,									// variable that contains basic vector
				vect_t *rotated										// pointer on array of structures that contain datas for rotated vectors - result
				)
{
	vect_t *p_vect[CHNL_ROTD];							
	uint16_t angle_base, temp1;
	
	// forming array of pointers; every element points on request vector
	for(chan_rot_t k=I_AH_ROT; k<=I_DC_ROT; k++)
	{
		if(k <= U_0_ROT)
			p_vect[k] = &(target_val[k].harm1);
		else if(k <= U_CA_ROT)
			p_vect[k] = &(line_val[k - U_AB_ROT].harm1);
		else
			p_vect[k] = &(diff_cur[k-I_DA_ROT].harm1);
	}
	//now we can refer to vectors that concerns to different structure
	for(chan_rot_t i=I_AH_ROT; i<=I_DC_ROT; i++) 
	{
		rotated[i].ef_val = p_vect[i]->ef_val;
		rotated[i].phase = 0xffff;
	}
	
	if(Vbas != NONE) 
	{
		angle_base = p_vect[Vbas]->phase;		// check allow value of base vector
		if(angle_base == 0xffff) return;
		for(chan_rot_t i=I_AH_ROT; i<=I_DC_ROT; i++) 
		{
			temp1 = p_vect[i]->phase;
			if(temp1 == 0xffff) rotated[i].phase = temp1;
			else
			{
				while(temp1<angle_base)	temp1 += 360;
				rotated[i].phase = temp1 - angle_base;
			}
		}		
	}
	
}


//------------------ Calculation of parameters (unbalansed voltage)(  us) ---------------------
void CalcUIAngles	(
					vect_t *rotated,								// pointer on array of structures that contain datas for rotated vectors
					uint16_t *ang									// pointer on array of values of voltage-current angeles - result
					)
{
	uint32_t min_i;
	int16_t temp16;
	chan_rot_t chan_u, chan_i;
	uint32_t min[7]   	= {	I_NG,		I_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG, 		I_NG0	};
	uint16_t ref_ang[7] = { 0, 			0, 			0, 			90, 		90, 		90, 		0		};
	chan_rot_t order_u[7]={ U_A_ROT, 	U_B_ROT, 	U_C_ROT, 	U_BC_ROT, 	U_CA_ROT,	U_AB_ROT,	U_0_ROT	};
	chan_rot_t order_i[7]={ I_AH_ROT, 	I_BH_ROT, 	I_CH_ROT, 	I_AH_ROT, 	I_BH_ROT, 	I_CH_ROT, 	I_0_ROT	}; // define processing order
	//now we can refer to vectors that concerns to different structure

	for(int k=0; k<7; k++)
	{
		chan_u = order_u[k];
		chan_i = order_i[k];
		min_i = min[k];
		
		if(rotated[chan_u].ef_val >= U_NG && rotated[chan_i].ef_val >= min_i)
		{
			temp16 = rotated[chan_u].phase - rotated[chan_i].phase + ref_ang[k];
			while(temp16<0)		
				temp16 += 360;
			while(temp16>360)	
				temp16 -= 360;
			ang[k] = (uint16_t)temp16;
		}			
		else 
			ang[k] = 0xffff;
	}
}


//------------------ Calculation of parameters (unbalansed voltage)(  us) ---------------------
void CalcPower	(
				vect_t *rotated,									// pointer on array of structures that contain datas for rotated vectors
				uint16_t *ang,										// pointer on array of values of voltage-current angeles
				power_t *pow										// pointer on strcture with power component - result
				)
{
	int64_t temp64[4];
	int16_t cos[3], sin[3];
	
	//compute arrays of sinus @ cosinus
	for(phi_t k=UA_IAH; k<=UC_ICH; k++)
	{
//		if(ang[k]>360) return;
		cos[k] = Cosin(ang[k]);
		sin[k] = Sinus(ang[k]);
	}
	
	// active power
	temp64[0] = 0;
	for(chan_rot_t j=I_AH_ROT; j<=I_CH_ROT; j++)
	{
		temp64[0] += (int64_t)rotated[j].ef_val * (int64_t)rotated[j+U_A_ROT].ef_val * cos[j];
	}
	temp64[0] = temp64[0]/1024/K_TA/K_TV;
	pow->active = (int32_t)temp64[0];
	
	// reactive power
	temp64[1] = 0;
	for(chan_rot_t j=I_AH_ROT; j<=I_CH_ROT; j++)
	{
		temp64[1] += (int64_t)rotated[j].ef_val * (int64_t)rotated[j+U_A_ROT].ef_val * sin[j];
	}
	temp64[1] = temp64[1]/1024 /K_TA/K_TV;
	pow->reactive = (int32_t)temp64[1];
	
	// full power
	temp64[2] = temp64[0]*temp64[0];
	temp64[2] += temp64[1]*temp64[1];
	temp64[3] = SqRoot(temp64[2]);
	pow->full = (uint32_t)temp64[3];
	
	// cos phi
	pow->cos_phi = (int32_t)(temp64[0] * 1000 / temp64[3]);
}
	
	
//----------------------------- Calculation of frequency (  us) -------------------------------
void CalcFreq	(
				spectr_t *target_val,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
				dat4freq_t *dat
				)
{
	dat->uf_level = target_val[U_F_MES].harm1.ef_val;
	if(dat->uf_level > 10*U_NG)
		dat->frequency = (SystemCoreClock/72 * 100) / dat->elapsed_time;
	else
	{	
		dat->frequency = 0;
		dat->elapsed_time = 0;
	}
}


//-------------------------------- Motor thermal model (  us) ---------------------------------
void ThermModel	(
				vect_t *rotated,									// pointer on array of structures that contain datas for rotated vectors
				FRZseq_t *frz_seq,									// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of currents (voltages) of forward, reverse sequence and thire relations
				setngs_t *coef, 										// structures that contains coeffitients
				therm_t *thermal									// pointer on structure that contains datas for motor thermal state - result
				)
{
	uint64_t i_equ;
	
	FindEquivalCur(rotated, frz_seq, &i_equ);
	//			i_equ = 1151329;
	FindThermConst(&i_equ, coef, thermal);
	RungeKutt(&i_equ, coef, thermal);
	
	if(thermal->ovrht > 2 * COEF_TZP)
		thermal->ovrht = 2 * COEF_TZP;
		
	if(i_equ < (I_NG*I_NG))
	{
		thermal->off_cnt += DELTA_T_TZP;
		if(thermal->off_cnt > (4*coef->cool_const)) 
			thermal->ovrht = 0;
	}
	else 
		thermal->off_cnt = 0;
}


//------------------------- Find value of equivalent current (Ieq^2) --------------------------
//__forceinline 
void FindEquivalCur	(
					vect_t *rotated,								// pointer on array of structures that contain datas for rotated vectors
					FRZseq_t *frz_seq,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of currents (voltages) of forward, reverse sequence and thire relations
					uint64_t *i_equiv								// pointer on value of equivalent current
					)
{
	uint32_t temp_arr[3];
	uint64_t temp1, temp2, temp3;
	
	// find max phase current
	for(chan_rot_t i=I_AH_ROT; i<=I_CH_ROT; i++) 
		temp_arr[i] = rotated[i].ef_val;
	temp1 = (uint64_t)temp_arr[FindExtrElem(temp_arr, 3, MAXIM)];
	
	// find equivalent current
	temp2 = temp1 * temp1;
	temp1 = (uint64_t)frz_seq[0].reverse.ef_val;
	temp3 = 3 * temp1 * temp1;
	*i_equiv = temp2 + temp3;
}


//--------------------- Find value of thermal time constant of motor (  us) -------------------
//__forceinline 
void FindThermConst	(
					uint64_t *i_equiv,								// equivalent current
					setngs_t *coef, 								// pointer on structures that contains coeffitients
					therm_t *thermal								// pointer on structure that contains datas for motor thermal state - result
					)
{	
	if(*i_equiv > (I_NG*I_NG)) 
		thermal->therm_const = coef->heat_const;
	else 
		thermal->therm_const = coef->cool_const;
} 


//--------------------------- Find derivative of motor overheat (  us) ------------------------
int32_t FindDeriv	(
					uint64_t *i_equiv,								// equivalent current
					setngs_t *coef, 								// pointer on structures that contains coeffitients
					therm_t *thermal,								// pointer on structure that contains datas for motor thermal state - result
					uint32_t overheat								// 
					)
{	
	int32_t	teta_max_nom, dlta_teta_envr;
	int64_t temp1;
	uint32_t i_nom;
	
	teta_max_nom = coef->temprt_motor_crtic - coef->temprt_envir_nom;
	dlta_teta_envr = coef->temprt_envir_nom - coef->temprt_envir;
	i_nom = coef->mot_current_nom * coef->mot_current_nom;
	temp1 = teta_max_nom * (*i_equiv) * COEF_TZP / (teta_max_nom + dlta_teta_envr) / i_nom ;
	temp1 = temp1 - overheat;
	temp1 = temp1 / thermal->therm_const;
	return (int32_t)temp1;
} 


//-------------- Find 1 step solving of diff. equation by Runge-Kutt method (  us) ------------
//__forceinline 
void RungeKutt	(
				uint64_t *i_equiv,									// equivalent current
				setngs_t *coef, 										// structures that contains coeffitients
				therm_t *thermal									// pointer on structure that contains datas for motor thermal state - result
				)
{
	int32_t overheat; 
	int32_t k1, k2, k3, k4, deriv;
	
	overheat = thermal->ovrht;
	k1 = FindDeriv(i_equiv, coef, thermal, overheat);

	overheat = (int32_t)(k1 * DELTA_T_TZP);
	overheat /= 2;
	overheat += thermal->ovrht;
	k2 = FindDeriv(i_equiv, coef, thermal, overheat);
	
	overheat = (int32_t)(k2 * DELTA_T_TZP);
	overheat /= 2;
	overheat += thermal->ovrht;
	k3 = FindDeriv(i_equiv, coef, thermal, overheat);

	overheat = (int32_t)(k3 * DELTA_T_TZP);
	overheat += thermal->ovrht;
	k4 = FindDeriv(i_equiv, coef, thermal, overheat);

	deriv = (k1 + k4 + 2 * (k2 + k3)) / 6;
	thermal->ovrht = thermal->ovrht + (deriv * DELTA_T_TZP);
}


//---------------------- Save thermal state before switch-off (  us) --------------------------
void SaveThermalState	(
						uint32_t soft_time,							// current time in seconds
						setngs_t *coef, 							// pointer on structures that contains coeffitients
						therm_t *thermal							// pointer on structure that contains datas for motor thermal state - result
						)
{
	uint8_t temp8, *temp_pntr;
	uint32_t temp32;
	
	if(thermal->ovrht > 0)
	{
		// Save thermal model data in SRAM (Therm_state)
		//thermal->cool_constant = coef->cool_const;						//thermal->cool_constant
		temp_pntr = (void *)thermal;
		WriteArrayToRam(ADR_THERMAL_STATE, temp_pntr, sizeof(therm_t));

		// Save current time in SRAM
		temp32 = soft_time;
		temp_pntr = (void *)&temp32;
		WriteArrayToRam(ADR_OFF_TIME, temp_pntr, 4);
		
		// Save marker
		temp8 = 0xcc;
		WriteByteToRam(ADR_OFF_MARKER, &temp8);
	}
}

//extern uint8_t led_st;
//------------------------- Initialization of thermal state (  us) ----------------------------
void InitThermalState	(
						setngs_t *coef, 							// pointer on structures that contains coeffitients
						therm_t *thermal							// pointer on structure that contains datas for motor thermal state - result
						)
{
	uint8_t temp8, *temp_pntr;
	int32_t temp32;
	int64_t temp64;
	uint16_t temp16;
	uint32_t temp1, arg1;
	uint32_t temp2;
	therm_t temp_term;
	
	// Reead marker that marks switch-off event (1 byte)
	ReadByteFromRam(ADR_OFF_MARKER, &temp8);
	if(temp8 != 0xcc) 
	{
		// thermal state hasn't been saved:
		//	- load overheat start value
		temp32 = coef->temprt_motor_crtic - coef->temprt_envir;
		thermal->ovrht = (int32_t)((coef->temprt_motor_start - coef->temprt_envir) * COEF_TZP / temp32);
	}
	else
	{
		// thermal state has been saved
		//	- read current time
		temp1 = ((uint32_t)RTC->CNTH << 16) | RTC->CNTL;
		
		//	- read saved state and switch-off time
		temp_pntr = (void *)&temp_term;
		ReadArrayFromRam(ADR_THERMAL_STATE, temp_pntr, sizeof(therm_t));
		
		temp_pntr = (void *)&temp2;
		ReadArrayFromRam(ADR_OFF_TIME, temp_pntr, 4);
		
		//	- analyze elapsed time
		if((temp1 - temp2) >= 4*temp_term.therm_const)				// if timeout more then 4Toff - load overheat start value    cool_constant
			thermal->ovrht = (int32_t)0x00;							
		else														// if timeout less then 4Toff - compute and load current thermal state
		{
			arg1 = (temp1 - temp2) * 10 / temp_term.therm_const;		//cool_constant
			FindExp(arg1, &temp16);
			temp64 = (int64_t)temp_term.ovrht;
			temp64 = (temp64 * (int64_t)temp16) / (int64_t)EXP_SCALE_FACTOR;
			thermal->ovrht = (int32_t)temp64;
		}
		
		//	- erase marker
		temp8 = 0;
		WriteByteToRam(ADR_OFF_MARKER, &temp8);
	}
}


//---------------------- Packing information in transmit buffer (20us) ------------------------
void PackInfTxBuf	(
					vect_t *rotated,								// pointer on array of structures that contain datas for rotated vectors
					FRZseq_t *frz_seq,								// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of currents of forward, reverse sequence and thire relations
					uint32_t *del_cur,								// pointer on array that contains datas for unsymmetrical currents
					uint32_t *ibreak,								// pointer on array of break currents
					power_t *pow,									// strcture with power component
					uint16_t *ang,									// pointer on array of values of voltage-current angeles
					vect_t *unbal_vol,								// pointer on strcture with value of unbalansed voltage
					dat4freq_t *dat4freq,							// pointer on frequency
					therm_t *thermal,								// pointer on structure that contains datas for motor thermal state 
					uint8_t *breaked_phase,							// pointer on array of breaked phases
					uint8_t *tx_buf									// pointer on transmit buffer - result
					)
{
	// 655536 - 5V => 1bit = 0.07629mV																								
	// Voltage on ADC input: Val*0.07629mV																							
	// Maximum voltage amplitude - 5V / 2 = 2.5V																					
	// Maximum voltage effective value - 2.5V / 1.414 = 1.768V																		

	// Transfer factor of current measuring circuit (I_AH...I_CK): Km = 125A/1.768V (effective values) = 70.701 A/V					
	// Full transfer factor: K = Km * 0.07629 / 1000 = 0.005394																		
	// K_TA=185 - for w=1, k=2.2
	
	// Transfer factor of current measuring circuit (I_0): 																			
	// Km = 5A/1.768V (effective values) = 2.828 A/V
	// Full transfer factor: K = Km * 0.07629 / 1000 = 0.0002157
	// K_TA0=4214 - for w=5, k=10 			// K_TA0=4635 - for w=5, k=11
	
	// Transfer factor of voltage measuring circuit (U_A...U_C, U_0): 
	// Km = 200V/1.768V (effective values) = 113.12 V/V		
	// Full transfer factor: K = Km * 0.07629 / 1000 = 0.00863	
	// (K_TV=142)			K_TV=116		
	
	// Main currents & voltages
	uint32_t temp;
	uint16_t temp16;
	uint32_t place1[CHNL_ROTD] = {		TX_I_AH, 	TX_I_BH, 	TX_I_CH, 	TX_I_AK, 	TX_I_BK, 	TX_I_CK, 	TX_I_0, 
										TX_U_A, 	TX_U_B, 	TX_U_C, 	TX_U_0, 	TX_U_AB, 	TX_U_BC, 	TX_U_CA, 
										TX_I_DA, 	TX_I_DB, 	TX_I_DC														}; 	// define offset in buffer	TX_U_F, 	
	uint16_t coef1[CHNL_ROTD] = {		K_TA, 		K_TA, 		K_TA, 		K_TA, 		K_TA, 		K_TA, 		K_TA0, 
										K_TV, 		K_TV, 		K_TV, 		K_TV, 		K_TV, 		K_TV, 		K_TV, 
										K_TA, 		K_TA, 		K_TA														}; 	// define transform factors for every channel 		K_TV,	
	
	for(chan_rot_t i=I_AH_ROT; i<=I_DC_ROT; i++)					// directly measured, line & differential values
	{
		temp = rotated[i].ef_val;
		if(i == I_0_ROT)
			temp = (temp<<16)/coef1[i];
		else
			temp = (temp<<8)/coef1[i];

		if((i >= U_AB_ROT && i <= U_CA_ROT) || (i == I_0_ROT))							// for 3-byte values
		{
			*(tx_buf+place1[i]) = (uint8_t)(temp >> 16);
			*(tx_buf+place1[i]+1) = (uint8_t)(temp >> 8);
			*(tx_buf+place1[i]+2) = (uint8_t)temp;
			temp = rotated[i].phase;
			*(tx_buf+place1[i]+3) = (uint8_t)(temp >> 8);
			*(tx_buf+place1[i]+4) = (uint8_t)temp;		
		}
		else														// for 2-byte values
		{
			*(tx_buf+place1[i]) = (uint8_t)(temp >> 8);
			*(tx_buf+place1[i]+1) = (uint8_t)temp;
			if(i < I_DA_ROT)										// besides that hasn't angles (I_DA_ROT, I_DB_ROT, I_DC_ROT)
			{
				temp = rotated[i].phase;
				*(tx_buf+place1[i]+2) = (uint8_t)(temp >> 8);
				*(tx_buf+place1[i]+3) = (uint8_t)temp;		
			}
		}
	}
	
	// Forward & reverse sequence currents
	uint32_t place2[8] = {	TX_I_1H, 	TX_I_2H, 	TX_I_21H, 	TX_I_1K, 	TX_I_2K, 	TX_I_21K, 	TX_U_1, 	TX_U_2	}; 						// define offset in buffer
	uint16_t coef2[3] =  {	K_TA, 								K_TA, 								K_TV				}; 						// define transform factors for every channel
	for(int i=0; i<3; i++)											// forward, reverse sequence currents and reverse to forward relations
	{
		temp = frz_seq[i].forward.ef_val;							// load forward seq. cur.
		temp =  (temp<<8)/coef2[i];	
		*(tx_buf+place2[3*i]) = (uint8_t)(temp >> 8);
		*(tx_buf+place2[3*i]+1) = (uint8_t)temp;

		temp = frz_seq[i].reverse.ef_val;							// load reverse seq. cur.
		temp =  (temp<<8)/coef2[i];	
		*(tx_buf+place2[3*i+1]) = (uint8_t)(temp >> 8);
		*(tx_buf+place2[3*i+1]+1) = (uint8_t)temp;
		
		if(i<2)
		{
			temp = frz_seq[i].relat_r2f;							// load reverse to forward relations
			temp = (temp<<8)/100;	
			*(tx_buf+place2[3*i+2]) = (uint8_t)(temp>>8);
			*(tx_buf+place2[3*i+2]+1) = (uint8_t)temp;
		}
	}
	
	// Break currents
	uint32_t place3[3] = {	TX_I_TA, 	TX_I_TB, 	TX_I_TC	}; 		// define offset in buffer
	for(int i=0; i<3; i++)											
	{
		temp = ibreak[i];											// load break cur.
		temp =  (temp<<8)/K_TA;	
		*(tx_buf+place3[i]) = (uint8_t)(temp >> 8);
		*(tx_buf+place3[i]+1) = (uint8_t)temp;
	}
	
	// Other angles
	uint32_t place4[4] = {	TX_ANGL_IA_UBC, TX_ANGL_IB_UCA, TX_ANGL_IC_UAB,	TX_ANGL_I0_U0	}; 		// define offset in buffer
	phi_t ang_order[4] = {	UBC_IAH, 		UCA_IBH, 		UAB_ICH,		U0_I0			};
	for(int i=0; i<4; i++)														
	{
		temp16 = ang[ang_order[i]];									// load angles
		*(tx_buf+place4[i]) = (uint8_t)(temp16 >> 8);
		*(tx_buf+place4[i]+1) = (uint8_t)temp16;
	}
	
	// Power values
	uint32_t place5[4] = {	TX_P,	TX_Q,	TX_S,	TX_COSPHI}; 	// define offset in buffer
	int32_t *pntr[4], temp1;
	pntr[0] = &(pow->active);
	pntr[1] = &(pow->reactive);
	pntr[2] = (int32_t *)&(pow->full);
	pntr[3] = &(pow->cos_phi);
	for(int i=0; i<4; i++)														
	{
		temp1 = *(pntr[i]);											// load power components
		if(temp1 < 0) 
		{
			*(tx_buf+place5[i]) = 0x80;
			temp1 = (int32_t)(0 - temp1);
		}
		else
			*(tx_buf+place5[i]) = 0x00;		
		
		if(i != 3)
		{
			*(tx_buf+place5[i]) |= (uint8_t)(temp1 >> 8);
			*(tx_buf+place5[i]+1) = (uint8_t)temp1;
		}
		else
		{
			*(tx_buf+place5[i]) |= (uint8_t)(temp1/1000);
			temp1 = (temp1<<16)/1000;
			*(tx_buf+place5[i]+1) = (uint8_t)(temp1>>8);
			*(tx_buf+place5[i]+2) = (uint8_t)temp1;
		}
	}
	
	// Unbalansed voltage
	temp = unbal_vol->ef_val;
	temp =  (temp<<8)/K_TV;	
	*(tx_buf+TX_U_BNN) = (uint8_t)(temp >> 16);
	*(tx_buf+TX_U_BNN+1) = (uint8_t)(temp >> 8);
	*(tx_buf+TX_U_BNN+2) = (uint8_t)temp;
	
	// Unsymmetrical currents
	temp = del_cur[0];
	*(tx_buf+TX_DELTA_IH) = (uint8_t)temp;
	
	// Frequency
	temp = dat4freq->frequency;
	temp =  (temp<<8)/100;	
	*(tx_buf+TX_F) = (uint8_t)(temp>>8);
	*(tx_buf+TX_F+1) = (uint8_t)temp;
	temp = dat4freq->uf_level;
	temp =  (temp<<8)/K_TV;	
	*(tx_buf+TX_U_F) = (uint8_t)(temp>>8);
	*(tx_buf+TX_U_F+1) = (uint8_t)temp;
	
	// Thermal state
	temp = thermal->ovrht * 100 / COEF_TZP;
	*(tx_buf+TX_OVERHEAT) = (uint8_t)temp;
	
	// Type of KZ
	for(int i=0; i<3; i++)
	{
		if(breaked_phase[i]!=0xff)
		{
			temp=breaked_phase[i];
			break;
		}
		if(i==2)
			temp=0xff;
	}
	*(tx_buf+TX_TYPE_KZ) = (uint8_t)temp;
}





