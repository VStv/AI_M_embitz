//*********************************************************************************************
//                                        Protect.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "protect.h"


//---------------------------------------------------------------------------------------------
//                                   Tables of Constants
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//-------------------- Saving pre-emergency (50ms) current values (  us) ----------------------
void SavePreemrgCur	(
					uint32_t *compar,								// 32-bit value that stores comparators states
					vect_t *rotated,								// pointer on array of structures that contain datas for calculated vectors 
					preemrg_t *i_preemerg							// pointer on structure with pre-emergency (50ms) current values - result
					)
{
	uint32_t max_cur, temp_arr[3];
	comp_num_t p_set[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};
	
	// find max current value 
	for(int i=0; i<3; i++) 
		temp_arr[i] = rotated[I_AH_ROT+i].ef_val;
	max_cur = temp_arr[FindExtrElem(temp_arr, 3, MAXIM)];
	
	// save max current value in circle buffer
	i_preemerg->shifted_cur[i_preemerg->pntr2next++] = max_cur;
	if(i_preemerg->pntr2next >= T_PREEMERG/5)
		i_preemerg->pntr2next = 0;
	// Now there is a delaied on 50ms value in cell where i_preemerg[i].pntr2next points  
	
	for(int i=0; i<4; i++)
	{
		// update preemergancy value, if comparator switched-off
		if(!(compar[0] & (uint32_t)(1<<p_set[i])))
			i_preemerg->value[i] = i_preemerg->shifted_cur[i_preemerg->pntr2next];
	}
}


//------------------ Calculation of time-current chart (TCC) for MTZ (  us) -------------------
void CalcTccMTZ	(													// !!!!!!!!!! must be contained in appropriate protective precedure MTZ_xx !!!!!!!!!!!!
				vect_t *rotated,									// pointer on array of structures that contain datas for calculated vectors 
				preemrg_t *i_preemerg,								// pointer on structure with pre-emergency (-50ms) current value
				prtct_set_t *i_set									// pointer on array of structures that contain setting datas for MTZ_xx - result
				)
{
	uint32_t Max_cur, max_cur, temp_arr[3];
	uint64_t temp_arg1, temp_arg2, temp_arg3;
	int32_t temp32;
	int cmp_num;
	comp_num_t p_set[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};
	
	// find max current
	for(int i=0; i<3; i++) 
		temp_arr[i] = rotated[I_AH_ROT+i].ef_val;
	Max_cur = 10000 * temp_arr[FindExtrElem(temp_arr, 3, MAXIM)];
	
	for(int i=0; i<4; i++)
	{
		cmp_num = p_set[i];
		max_cur = Max_cur / i_set[cmp_num].trshld[0];									// (max(I)/Iust)*10000
		
		// calculate treshold time for appropriate TCC
		switch(i_set[cmp_num].tcc)
		{
			case TCC_5:
			case TCC_6:
				if(FindValTcc2_7(max_cur, i_set[cmp_num].tcc, &temp32) == RES_OK)
					i_set[cmp_num].T_trsh = i_set[cmp_num].T_set + temp32;
				else 
					i_set[cmp_num].T_trsh = 0xffffffff;
				break;
			case TCC_2:
			case TCC_3:
			case TCC_4:
			case TCC_7:
				if(FindValTcc2_7(max_cur, i_set[cmp_num].tcc, &temp32) == RES_OK)
					i_set[cmp_num].T_trsh = (i_set[cmp_num].T_set * temp32) / 1000;
				else 
					i_set[cmp_num].T_trsh = 0xffffffff;
				break;
			case TCC_8:
				temp_arg1 = ((uint64_t)max_cur) * ((uint64_t)max_cur);
				max_cur = 10000 * i_preemerg->value[i];
				max_cur = max_cur / i_set[cmp_num].trshld[0];
				temp_arg2 = ((uint64_t)max_cur) * ((uint64_t)max_cur);
				temp_arg3 = (temp_arg1 - (10000*10000))/1000;			// denumenator
				temp_arg1 = temp_arg1 - temp_arg2;						// numenator
				temp_arg1 = temp_arg1 / temp_arg3;
				if(FindLn((uint16_t)temp_arg1, &temp32) == RES_OK)
					i_set[cmp_num].T_trsh = (i_set[cmp_num].T_set * temp32) / 1000;
				else 
					i_set[cmp_num].T_trsh = 0xffffffff;
				break;
			default:
				i_set[cmp_num].T_trsh = i_set[cmp_num].T_set;
				break;
		}
	}
}


//--------------------------- Comparator VMB processing (  us) --------------------------------
void ComparVMB	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				FRZseq_t *i_fr,								// pointer on array of structures that contain datas of forward, revers sequence currents based on line currents
				prtct_set_t *i_set,							// pointer on array of structures that contain comparator settings 
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint32_t trshld_zmn, trshld_zpn, rtrn_zmn, rtrn_zpn;
	
	trshld_zpn = i_set[VMB_cmp].trshld[0];
	trshld_zmn = i_set[VMB_cmp].trshld[1];
	rtrn_zpn = (i_set[VMB_cmp].k_retrn[0] * trshld_zpn) / 100;
	rtrn_zmn = (i_set[VMB_cmp].k_retrn[1] * trshld_zmn) / 100;
	switch(i_set[VMB_cmp].main_enbl)
	{
		case ZMN_F_ON:
			if(	(!(compar[0] & COMP_VMB_MASK) && 
				((rotated[U_A_ROT].ef_val <= trshld_zmn)|| 
				(rotated[U_B_ROT].ef_val <= trshld_zmn) || 
				(rotated[U_C_ROT].ef_val <= trshld_zmn)))
				||
				((compar[0] & COMP_VMB_MASK) && 
				((rotated[U_A_ROT].ef_val <= rtrn_zmn) || 
				(rotated[U_B_ROT].ef_val <= rtrn_zmn)  || 
				(rotated[U_C_ROT].ef_val <= rtrn_zmn)))	)
			{
				compar[0] |= COMP_VMB_SET;
			}
			else
			{
				compar[0] &= COMP_VMB_RESET;
			}
			break;

		case ZMN_L_ON:
			if(	(!(compar[0] & COMP_VMB_MASK) && 
				((rotated[U_AB_ROT].ef_val <= trshld_zmn)|| 
				(rotated[U_BC_ROT].ef_val <= trshld_zmn) || 
				(rotated[U_CA_ROT].ef_val <= trshld_zmn)))
				||
				((compar[0] & COMP_VMB_MASK) && 
				((rotated[U_AB_ROT].ef_val <= rtrn_zmn) || 
				(rotated[U_BC_ROT].ef_val <= rtrn_zmn)  || 
				(rotated[U_CA_ROT].ef_val <= rtrn_zmn))) )
			{
				compar[0] |= COMP_VMB_SET;
			}
			else
			{
				compar[0] &= COMP_VMB_RESET;
			}
			break;
			
		case ZMN_U1_ON:
			if(	((compar[0] & COMP_VMB_MASK) && (i_fr[2].forward.ef_val <= rtrn_zmn))
				||
				(!(compar[0] & COMP_VMB_MASK) && (i_fr[2].forward.ef_val <= trshld_zmn)))
			{
				compar[0] |= COMP_VMB_SET;
			}
			else
			{
				compar[0] &= COMP_VMB_RESET;
			}
			break;
		
		case ZPN_U2_ON:
			if(	((compar[0] & COMP_VMB_MASK) && (i_fr[2].reverse.ef_val >= rtrn_zpn))
				||
				(!(compar[0] & COMP_VMB_MASK) && (i_fr[2].reverse.ef_val >= trshld_zpn)))
			{
				compar[0] |= COMP_VMB_SET;
			}
			else
			{
				compar[0] &= COMP_VMB_RESET;
			}
			break;

		default:
			compar[0] &= COMP_VMB_RESET;
			break;
	}
}


//-------------------------- Comparator of KAM processing (  us) ------------------------------
void ComparKAM	(
				power_t *pow,								// pointer on strcture with power components
				prtct_set_t *i_set,							// pointer on array of structures that contain comparator settings 
				uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint32_t comp;
	uint32_t temp32;
	uint8_t main_en, cmp_num, dir_en, rpo_en,/**/ mot_strt_en, comp_trsh[3], comp_retr[3];
	comp_num_t p_set[3] = {KAM_1_cmp, KAM_2_cmp, KAM_3_cmp};

	for(int i=0; i<3; i++)
	{
		cmp_num = p_set[i];

		main_en = i_set[cmp_num].main_enbl;
		dir_en = i_set[cmp_num].dir_enbl;
		rpo_en = i_set[cmp_num].add1_enbl;
		mot_strt_en = i_set[cmp_num].add2_enbl;
		comp = compar[0] & (uint32_t)(1<<cmp_num);
		
		if(pow->active<0) 
			temp32 = 0 - pow->active;
		else
			temp32 = pow->active;
		for(int k=0; k<3; k++)
		{
			comp_trsh[k] = temp32 > i_set[cmp_num].trshld[k];
			comp_retr[k] = temp32 > (i_set[cmp_num].k_retrn[k] * i_set[cmp_num].trshld[k]) / 100;
		}

		if(main_en)
		{
			if(((!comp && !comp_trsh[0] && comp_trsh[1]) 	||
				(!comp && !comp_trsh[0] && !comp_trsh[1] && !comp_trsh[2]))
				||
				((comp && !comp_retr[0] && comp_retr[1]) 	||
				(comp && !comp_retr[0] && !comp_retr[1] && !comp_retr[2])))
			{
				compar[0] &= (uint32_t)~(1<<cmp_num);
				continue;
			}
			if(	(rpo_en && (stat_cpu & STAT_RPO_MASK)) ||
				(!rpo_en && mot_strt_en && (compar[1] & COMP_IPD_MASK)) ||
				(rpo_en && !(stat_cpu & STAT_RPO_MASK) && mot_strt_en && (compar[1] & COMP_IPD_MASK))	)
			{
				compar[0] &= (uint32_t)~(1<<cmp_num);
			}
			else
			{
				if(((dir_en==FWRD_ON) && !(pow->active > 0)) ||
				   ((dir_en==RVRS_ON) && !(pow->active < 0)))
				{
					compar[0] &= (uint32_t)~(1<<cmp_num);
				}
				else
				{
					compar[0] |= (uint32_t)(1<<cmp_num);
				}
			}
		}
		else
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
		}
	}
}


//-------------------------- Protection algorithm for ZVS (  us) ------------------------------
void ProtectZVS	(
				power_t *pow,								// strcture with power components
				uint16_t *ang,								// pointer on array of values of voltage-current angeles - result
				prtct_set_t *i_set,							// pointer on array of structures that contain comparator settings 
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint8_t cond_trsh, cond_rtrn, cond_1, cond_2, cond_fin;
	uint32_t  temp_cos, temp_cos_095, cos_yC, cos_yL;
	
	temp_cos = (pow->cos_phi < 0) ? (uint32_t)(0 - pow->cos_phi) : (uint32_t)pow->cos_phi;
	temp_cos_095 = (temp_cos * 95) / 100;
	
	cos_yC = i_set[ZVS_cmp].trshld[0];
	cos_yL = i_set[ZVS_cmp].trshld[1];
	cond_1 = (	((ang[UBC_IAH] < 90) && (ang[UCA_IBH] < 90) && (ang[UAB_ICH] < 90)) 
				|| 
				((ang[UBC_IAH] < 270 && ang[UBC_IAH] >= 180) && (ang[UCA_IBH] < 270 && ang[UCA_IBH] >= 180) && (ang[UAB_ICH] < 270 && ang[UAB_ICH] >= 180))	);
	cond_2 = (	((ang[UBC_IAH] >= 90 && ang[UBC_IAH] < 180) && (ang[UCA_IBH] >= 90 && ang[UCA_IBH] < 180) && (ang[UAB_ICH] >= 90 && ang[UAB_ICH] < 180)) 
				|| 
				((ang[UBC_IAH] >= 270 && ang[UBC_IAH] < 360) && (ang[UCA_IBH] >= 270 && ang[UCA_IBH] < 360) && (ang[UAB_ICH] >= 270 && ang[UAB_ICH] < 360))	);
	
	switch(i_set[ZVS_cmp].main_enbl)
	{
		case COS_L_ON:
			cond_trsh = /*(temp_cos>=0) &&*/ (temp_cos<cos_yL) && cond_1;
			cond_rtrn = /*(temp_cos>=0) &&*/ (temp_cos_095<cos_yL) && cond_1;
			break;
		
		case COS_C_ON:
			cond_trsh = /*(temp_cos>=0) &&*/ (temp_cos<cos_yC) && cond_2;
			cond_rtrn = /*(temp_cos>=0) &&*/ (temp_cos_095<cos_yC) && cond_2;
			break;
		
		case COS_LC_ON:
			cond_trsh = (/*(temp_cos>=0) &&*/ (temp_cos<cos_yL) && cond_1) || (/*(temp_cos>=0) &&*/ (temp_cos<cos_yC) && cond_2);
			cond_rtrn = (/*(temp_cos>=0) &&*/ (temp_cos_095<cos_yL) && cond_1) || (/*(temp_cos>=0) &&*/ (temp_cos_095<cos_yC) && cond_2);
			break;
		
		default:
			compar[0] &= COMP_ZVS_RESET;
			return;
	}
	
	cond_fin = !(compar[0] & COMP_ZVS_MASK) ? cond_trsh : cond_rtrn;
	if(cond_fin)
		compar[0] |= COMP_ZVS_SET; 
	else
		compar[0] &= COMP_ZVS_RESET; 
}


//------------------ Comparator of voltage decreasing processing (  us) -----------------------
//__forceinline void ComparDecrU(
//				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
//				uint32_t *compar							// pointer on variable that stores comparator's states - result
//				)
//{
//	if(	(!(compar[0] & COMP_DECR_U_MASK) && (rotated[U_A_ROT].ef_val < U_NG) && (rotated[U_B_ROT].ef_val < U_NG) && (rotated[U_C_ROT].ef_val < U_NG))
//		||
//		((compar[0] & COMP_DECR_U_MASK) && (rotated[U_A_ROT].ef_val < (11*U_NG/10)) && (rotated[U_B_ROT].ef_val < (11*U_NG/10)) && (rotated[U_C_ROT].ef_val < (11*U_NG/10)))	)
//	{
//		compar[0] |= COMP_DECR_U_SET;
//	}
//	else
//	{
//		compar[0] &= COMP_DECR_U_RESET;
//	}
//}


//------------------------- Protection algorithm for MTZ (  us) -------------------------------
void ProtectMTZ	(
				uint32_t *prtct_timer,
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				uint16_t *phi_ui,							// pointer on array of angles
				FRZseq_t *i_fr,								// pointer on array of structures that contain datas of forward, revers sequence currents based on line currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of MTZ 
				preemrg_t *i_preemerg,						// structure with pre-emergency (50ms) current values - result
				uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint32_t comp, msk_cmp; 
	uint32_t val_trsh, val_retr;
	uint16_t ang_trsh, ang_retr, ang_mean, ang_fact[3];
	uint8_t main_en, cmp_num, dir_en, decr_u_en, bnn_en, vmb_en, comp_trsh[3], comp_retr[3];
	comp_num_t p_set[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};
	uint8_t p_state[4] = {MTZ_1_state, MTZ_2_state, MTZ_3_state, MTZ_4_state};

	ComparVMB(rotated, i_fr, i_set, compar);
//	ComparDecrU(rotated, compar);
	if(	(!(compar[0] & COMP_DECR_U_MASK) && (rotated[U_A_ROT].ef_val < U_NG) && (rotated[U_B_ROT].ef_val < U_NG) && (rotated[U_C_ROT].ef_val < U_NG))
		||
		((compar[0] & COMP_DECR_U_MASK) && (rotated[U_A_ROT].ef_val < (11*U_NG/10)) && (rotated[U_B_ROT].ef_val < (11*U_NG/10)) && (rotated[U_C_ROT].ef_val < (11*U_NG/10)))	)
	{
		compar[0] |= COMP_DECR_U_SET;
	}
	else
	{
		compar[0] &= COMP_DECR_U_RESET;
	}
	
	for(int i=0; i<4; i++)
	{
		cmp_num = p_set[i];
		
		// load data for procedure
		main_en = i_set[cmp_num].main_enbl;
		dir_en = i_set[cmp_num].dir_enbl;
		decr_u_en = i_set[cmp_num].add2_enbl;
		bnn_en = i_set[cmp_num].add1_enbl;
		vmb_en = i_set[cmp_num].add3_enbl;
		msk_cmp = (uint32_t)(1<<cmp_num);
		comp = compar[0] & msk_cmp;
		val_trsh = i_set[cmp_num].trshld[0];
		val_retr = (val_trsh * i_set[cmp_num].k_retrn[0]) / 100;
		ang_mean = i_set[cmp_num].ang_set[0];
		ang_trsh = i_set[cmp_num].ang_set[1];
		ang_retr = i_set[cmp_num].ang_set[2];
		
		if(phi_ui[UBC_IAH] != 0xffff)
		{
			if(phi_ui[UBC_IAH] >= ang_mean) 
				ang_fact[0] = phi_ui[UBC_IAH] - ang_mean;
			else 
				ang_fact[0] = ang_mean - phi_ui[UBC_IAH];
			if(ang_fact[0] > 180) 
				ang_fact[0] = 360 - ang_fact[0];
		}
		else
			ang_fact[0] = 0xffff;
		
		if(phi_ui[UCA_IBH] != 0xffff)
		{
			if(phi_ui[UCA_IBH] >= ang_mean) 
				ang_fact[1] = phi_ui[UCA_IBH] - ang_mean;
			else 
				ang_fact[1] = ang_mean - phi_ui[UCA_IBH];
			if(ang_fact[1] > 180) 
				ang_fact[1] = 360 - ang_fact[1];
		}
		else
			ang_fact[1] = 0xffff;
			
		if(phi_ui[UAB_ICH] != 0xffff)
		{
			if(phi_ui[UAB_ICH] >= ang_mean) 
				ang_fact[2] = phi_ui[UAB_ICH] - ang_mean;
			else 
				ang_fact[2] = ang_mean - phi_ui[UAB_ICH];
			if(ang_fact[2] > 180) 
				ang_fact[2] = 360 - ang_fact[2];
		}
		else
			ang_fact[2] = 0xffff;
		
		comp_trsh[0] = (rotated[I_AH_ROT].ef_val > I_NG) && (rotated[U_BC_ROT].ef_val > U_NG) && (ang_fact[0] < ang_trsh);
		comp_trsh[1] = (rotated[I_BH_ROT].ef_val > I_NG) && (rotated[U_CA_ROT].ef_val > U_NG) && (ang_fact[1] < ang_trsh);
		comp_trsh[2] = (rotated[I_CH_ROT].ef_val > I_NG) && (rotated[U_AB_ROT].ef_val > U_NG) && (ang_fact[2] < ang_trsh);
		comp_retr[0] = (rotated[I_AH_ROT].ef_val > I_NG) && (rotated[U_BC_ROT].ef_val > U_NG) && (ang_fact[0] < ang_retr);
		comp_retr[1] = (rotated[I_BH_ROT].ef_val > I_NG) && (rotated[U_CA_ROT].ef_val > U_NG) && (ang_fact[1] < ang_retr);
		comp_retr[2] = (rotated[I_CH_ROT].ef_val > I_NG) && (rotated[U_AB_ROT].ef_val > U_NG) && (ang_fact[2] < ang_retr);

		if(main_en)
		{
			if(!(compar[0] & COMP_VMB_MASK) && vmb_en)														// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				compar[0] &= ~msk_cmp;
			}
			else
			{
				if(dir_en)
				{
					if((decr_u_en == BLOCK_RAB_ON) && (compar[0] & COMP_DECR_U_MASK))
					{
						compar[0] &= ~msk_cmp;
						continue;
					}
					else if(((decr_u_en == BLOCK_DIR_ON) && !(compar[0] & COMP_DECR_U_MASK))
							||
							((decr_u_en == BLOCK_RAB_ON) && !(compar[0] & COMP_DECR_U_MASK))
							||
							!decr_u_en)
					{
						if((bnn_en == BLOCK_RAB_ON) && (compar[0] & COMP_BNN1_MASK))
						{
							compar[0] &= ~msk_cmp;
							continue;
						}
						else if(((bnn_en == BLOCK_DIR_ON) && !(compar[0] & COMP_BNN1_MASK))
								||
								((bnn_en == BLOCK_RAB_ON) && !(compar[0] & COMP_BNN1_MASK))
								||
								!bnn_en)
						{
							if((!comp && !comp_trsh[0] && !comp_trsh[1] && !comp_trsh[2])
								||
								(comp && !comp_retr[0] && !comp_retr[1] && !comp_retr[2]))
							{
								compar[0] &= ~msk_cmp;
								continue;
							}
						}
					}
				}
				if(	(!comp &&
					((rotated[I_AH_ROT].ef_val >= val_trsh)|| 
					(rotated[I_BH_ROT].ef_val >= val_trsh) || 
					(rotated[I_CH_ROT].ef_val >= val_trsh)))
					||
					(comp &&
					((rotated[I_AH_ROT].ef_val >= val_retr) || 
					(rotated[I_BH_ROT].ef_val >= val_retr)  || 
					(rotated[I_CH_ROT].ef_val >= val_retr))))
				{
					if(stat_cpu & (1<<p_state[i]))
						compar[0] &= ~msk_cmp;
					else 
						compar[0] |= msk_cmp;
				}
				else
				{
					compar[0] &= ~msk_cmp;
				}
			}
		}
		else 
			compar[0] &= ~msk_cmp;
	}
	CalcTccMTZ(rotated, i_preemerg, i_set);
//	TimingMTZ(prtct_timer, i_set, compar);
	DelayMTZ(prtct_timer, i_set, compar);
}


//----------- Protection algorithm for realising MTZ with timeout accounting (  us) -----------
void TimingMTZ	(
				uint32_t *prtct_timer,
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of MTZ 
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	comp_num_t cmp_num, p_set[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};

	for(int i=0; i<4; i++)
	{
		cmp_num = p_set[i];
		
		// timers processing
		if(compar[0] & (uint32_t)(1<<cmp_num))
		{
			if(compar[0] & (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp)))
			{
				compar[0] |= (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
			}
			else
			{
				if(prtct_timer[cmp_num] >= i_set[cmp_num].T_trsh)
					compar[0] |= (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
				else 
				{
					compar[0] &= (uint32_t)~(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
					prtct_timer[cmp_num] += 5;
				}
			}
		}
		else
		{
			prtct_timer[cmp_num] = 0;
			compar[0] &= (uint32_t)~(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
		}
	}
}
	

//----------- Protection algorithm for realising MTZ with timeout accounting (  us) -----------
void DelayMTZ	(
				uint32_t *prtct_timer,
				prtct_set_t *i_set,															// pointer on array of structures that contain datas for treshold/return currents of MTZ 
				uint32_t *compar															// pointer on variable that stores comparator's states - result
				)
{
	comp_num_t cmp_num, p_set[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};
	uint32_t delta_5ms;
	
	for(int i=0; i<4; i++)
	{
		cmp_num = p_set[i];
		
		// timers processing
		if(compar[0] & (uint32_t)(1<<cmp_num))
		{
			if(compar[0] & (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp)))
			{
				compar[0] |= (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
			}
			else
			{
				if(prtct_timer[cmp_num] >= COLLECTED_MAX_VAL || 
					i_set[cmp_num].T_trsh == 0)
				{
					compar[0] |= (uint32_t)(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
					prtct_timer[cmp_num] = COLLECTED_MAX_VAL;
				}
				else 
				{
					compar[0] &= (uint32_t)~(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
					delta_5ms = (COLLECTED_MAX_VAL*5)/(i_set[cmp_num].T_trsh);
					prtct_timer[cmp_num] += delta_5ms;
				}
			}
		}
		else
		{
			prtct_timer[cmp_num] = 0;
			compar[0] &= (uint32_t)~(1<<(cmp_num + MTZ_1T_cmp - MTZ_1_cmp));
		}
	}
}
	

//------------------------- Protection algorithm for ZNZ (  us) -------------------------------
void ProtectZNZ	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				uint16_t *phi_ui,							// pointer on array of angles
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of MTZ 
				uint32_t *compar,							// pointer on variable that stores comparator's states - result
				uint8_t *emrg_phas							// pointer on variable that stores emergancy phase - result
				)
{
	uint32_t comp;
	uint32_t min_u, temp_arr[3];
	uint16_t ang_mean, ang_fact, ang_trsh, ang_retr;
	uint8_t bnn_en, cmp_num, dir_en, i0_en, u0_en, comp_trsh[3], comp_retr[3];
	comp_num_t p_set[3] = {ZNZ_1_cmp, ZNZ_2_cmp, ZNZ_3_cmp};

	for(int i=0; i<3; i++)
	{
		cmp_num = p_set[i];

		bnn_en = i_set[cmp_num].main_enbl;
		dir_en = i_set[cmp_num].dir_enbl;
		i0_en = i_set[cmp_num].add1_enbl;
		u0_en = i_set[cmp_num].add2_enbl;
		comp = compar[0] & (uint32_t)(1<<cmp_num);
		
		ang_mean = i_set[cmp_num].ang_set[0];
		ang_trsh = i_set[cmp_num].ang_set[1];
		ang_retr = i_set[cmp_num].ang_set[2];
		
		if(phi_ui[U0_I0] != 0xffff)
		{
			if(phi_ui[U0_I0] >= ang_mean) 
				ang_fact = phi_ui[U0_I0] - ang_mean;
			else 
				ang_fact = ang_mean - phi_ui[U0_I0];
			if(ang_fact > 180) 
				ang_fact = 360 - ang_fact;		
		}
		else
			ang_fact = 0xffff;
		
		comp_trsh[0] = rotated[I_0_ROT].ef_val >= i_set[cmp_num].trshld[0];
		comp_retr[0] = rotated[I_0_ROT].ef_val >= (i_set[cmp_num].trshld[0] * i_set[cmp_num].k_retrn[0]) / 100;
		comp_trsh[1] = rotated[U_0_ROT].ef_val >= i_set[cmp_num].trshld[1];
		comp_retr[1] = rotated[U_0_ROT].ef_val >= (i_set[cmp_num].trshld[1] * i_set[cmp_num].k_retrn[1]) / 100;
		comp_trsh[2] = (rotated[U_0_ROT].ef_val > U_NG) && (rotated[I_0_ROT].ef_val > I_NG0) && (ang_fact < ang_trsh);
		comp_retr[2] = (rotated[U_0_ROT].ef_val > U_NG) && (rotated[I_0_ROT].ef_val > I_NG0) && (ang_fact < ang_retr);

		if(!i0_en && !u0_en && !dir_en)
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
			emrg_phas[i] = 0xff;
			continue;
		}
		if((i0_en && !comp && !comp_trsh[0]) || (i0_en && comp && !comp_retr[0]))
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
			emrg_phas[i] = 0xff;
			continue;
		}
		if((u0_en && !comp && !comp_trsh[1]) || (u0_en && comp && !comp_retr[1]))
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
			emrg_phas[i] = 0xff;
			continue;
		}
		if( ((bnn_en == BLOCK_RAB_ON) && (compar[0] & COMP_BNN1_MASK))
			||
			(((bnn_en && !(compar[0] & COMP_BNN1_MASK)) || !bnn_en) && (dir_en && ((!comp && !comp_trsh[2]) || (comp && !comp_retr[2]))))	)	
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
			emrg_phas[i] = 0xff;
			continue;
		}
		
		compar[0] |= (uint32_t)(1<<cmp_num);
		temp_arr[0] = rotated[U_A_ROT].ef_val;
		temp_arr[1] = rotated[U_B_ROT].ef_val;
		temp_arr[2] = rotated[U_C_ROT].ef_val;
		min_u = temp_arr[FindExtrElem(temp_arr, 3, MINIM)];
		if((temp_arr[0] == min_u) && (temp_arr[0] <= i_set[cmp_num].trshld[2]))
		{
			emrg_phas[i] = 1;
			continue;
		}
		if((temp_arr[1] == min_u) && (temp_arr[1] <= i_set[cmp_num].trshld[2]))
		{
			emrg_phas[i] = 2;
			continue;
		}
		if((temp_arr[2] == min_u) && (temp_arr[2] <= i_set[cmp_num].trshld[2]))
		{
			emrg_phas[i] = 3;
			continue;
		}
		emrg_phas[i] = 0xff;			
	}
}


//----------------------- Protection algorithm for DO (  us) --------------------------
void ProtectDO	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of DO
				uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
				uint32_t *compar							// pointer on value that stores comparators states - result
				)
{                           
	static uint8_t dn_before_ack;
	uint8_t main_en, dn_blck_en;
	uint32_t comp, comp_dn;
	uint32_t i_dif[3], trshl[3], retr[3];

	// load data for procedure
	for(phases_t j=ph_A; j<=ph_C; j++)
	{
		trshl[j] = i_set[DO_cmp].trshld[j];
		retr[j] = (trshl[j] * i_set[DO_cmp].k_retrn[j]) / 100;
		i_dif[j] = rotated[I_DA_ROT+j].ef_val;
	}
	main_en = i_set[DO_cmp].main_enbl;
	dn_blck_en = i_set[DO_cmp].add1_enbl;
	comp_dn = compar[0] & COMP_DN_MASK;
	comp = compar[0] & COMP_DO_MASK;

	// process DO main comparator
	if(!main_en)
	{
		compar[0] &= COMP_DO_RESET;
		dn_before_ack = 0;
		return;
	}
	switch(dn_blck_en)
	{
		case EN_POTEN:
			if(stat_cpu & STAT_DN_MASK)
			{
				compar[0] &= COMP_DO_RESET;
				dn_before_ack = 0;
				return;
			}
			break;
		
		case EN_BEFORE_ACK:
			if((!(dn_before_ack==1) && comp_dn) 
				||
				((dn_before_ack==1) && !(stat_cpu & STAT_ACK_MASK))
				||
				((dn_before_ack==1) && (stat_cpu & STAT_ACK_MASK) && comp_dn))
			{
				compar[0] &= COMP_DO_RESET;
				dn_before_ack = 1;
				return;
			}
			break;
		
		default:
			break;
	}
	
	dn_before_ack = 0;
	if((!comp && ((i_dif[ph_A]>=trshl[ph_A]) || (i_dif[ph_B]>=trshl[ph_B]) || (i_dif[ph_C]>=trshl[ph_C]))) 
		|| 
		(comp && ((i_dif[ph_A]>=retr[ph_A]) || (i_dif[ph_B]>=retr[ph_B]) || (i_dif[ph_C]>=retr[ph_C]))))
	{
		compar[0] |= COMP_DO_SET;
	}
	else
	{
		compar[0] &= COMP_DO_RESET;
	}
}


//----------------------- Protection algorithm for DT (  us) --------------------------
void ProtectDT	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of DT
				uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
				uint32_t *compar							// pointer on value that stores comparators states - result
				)
{                           
	static uint8_t dn_before_ack;
	uint8_t main_en, dn_blck_en;
	uint32_t comp, comp_dn;
	uint32_t i_dif[3], trshl[3], retr[3];

	// load data for procedure
	for(phases_t j=ph_A; j<=ph_C; j++)
	{
		trshl[j] = i_set[DT_cmp].trshld[j];
		retr[j] = (trshl[j] * i_set[DT_cmp].k_retrn[j]) / 100;
		i_dif[j] = rotated[I_DA_ROT+j].ef_val;
	}
	main_en = i_set[DT_cmp].main_enbl;
	dn_blck_en = i_set[DT_cmp].add1_enbl;
	comp_dn = compar[0] & COMP_DN_MASK;
	comp = compar[0] & COMP_DT_MASK;

	// process DT main comparator
	if(!main_en)
	{
		compar[0] &= COMP_DT_RESET;
		dn_before_ack = 0;
		return;
	}
	switch(dn_blck_en)
	{
		case EN_POTEN:
			if(stat_cpu & STAT_DN_MASK)
			{
				compar[0] &= COMP_DT_RESET;
				dn_before_ack = 0;
				return;
			}
			break;
		
		case EN_BEFORE_ACK:
			if((!(dn_before_ack==1) && comp_dn) 
				||
				((dn_before_ack==1) && !(stat_cpu & STAT_ACK_MASK))
				||
				((dn_before_ack==1) && (stat_cpu & STAT_ACK_MASK) && comp_dn))
			{
				compar[0] &= COMP_DT_RESET;
				dn_before_ack = 1;
				return;
			}
			break;
		
		default:
			break;
	}
	
	dn_before_ack = 0;
	if((!comp && ((i_dif[ph_A]>=trshl[ph_A]) || (i_dif[ph_B]>=trshl[ph_B]) || (i_dif[ph_C]>=trshl[ph_C]))) 
		|| 
		(comp && ((i_dif[ph_A]>=retr[ph_A]) || (i_dif[ph_B]>=retr[ph_B]) || (i_dif[ph_C]>=retr[ph_C]))))
	{
		compar[0] |= COMP_DT_SET;
	}
	else
	{
		compar[0] &= COMP_DT_RESET;
	}
}


//--------------------------- Protection algorithm for DN (  us) ------------------------------
void ProtectDN	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of DN
				uint32_t *compar							// pointer on 32-bit value that stores comparators states - result
				)
{                           
	uint32_t comp;
	uint8_t main_en; 
	uint32_t i_dif[3], trshl, retr;

	// load data for procedure
	trshl = i_set[DN_cmp].trshld[0];
	retr = (trshl * i_set[DN_cmp].k_retrn[0]) / 100;
	for(phases_t j=ph_A; j<=ph_C; j++)	
		i_dif[j] = rotated[I_DA_ROT+j].ef_val;
	main_en = i_set[DN_cmp].main_enbl;
	comp = compar[0] & COMP_DN_MASK;

	// process DN main comparator
	if(!main_en) 
	{
		compar[0] &= COMP_DN_RESET;	
		return;
	}
	if((!comp && ((i_dif[ph_A]>=trshl) || (i_dif[ph_B]>=trshl) || (i_dif[ph_C]>=trshl))) 
		|| 
		(comp && ((i_dif[ph_A]>=retr) || (i_dif[ph_B]>=retr) || (i_dif[ph_C]>=retr))))
	{
		compar[0] |= COMP_DN_SET;
	}
	else
	{
		compar[0] &= COMP_DN_RESET;
	}
}


////----------------------- Protection algorithm for DO & DT (  us) -----------------------------
//void ProtectDnDoDt	(
//					vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
//					prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of DT
//					uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
//					uint32_t *compar							// pointer on value that stores comparators states - result
//					)
//{                           
//	static uint8_t dn_before_ack[3];
//	uint8_t main_en, dn_blck_en;
//	uint32_t comp, comp_dn;
//	uint32_t i_dif[3], trshl[3], retr[3];

//	for(comp_num_t c=DN_cmp; c<=DT_cmp; c++)
//	{
//		// load data for procedure
//		for(phases_t j=ph_A; j<=ph_C; j++)
//		{
//			if(c == DN_cmp)
//			{
//				trshl[j] = i_set[c].trshld[0];
//				retr[j] = (trshl[j] * i_set[c].k_retrn[0]) / 100;
//			}
//			else
//			{
//				trshl[j] = i_set[c].trshld[j];
//				retr[j] = (trshl[j] * i_set[c].k_retrn[j]) / 100;
//			}
//			i_dif[j] = rotated[I_DA_ROT+j].ef_val;
//		}
//		main_en = i_set[c].main_enbl;
//		dn_blck_en = i_set[c].add1_enbl;
//		comp_dn = compar[0] & COMP_DN_MASK;
//		comp = compar[0] & ((uint32_t)(1<<c));

//		// process Dx main comparator
//		if(!main_en)
//		{
//			compar[0] &= ~((uint32_t)(1<<c));
//			dn_before_ack[c-DN_cmp] = 0;
//			continue;
//		}
//		
//		if(c != DN_cmp)
//		{
//			switch(dn_blck_en)
//			{
//				case EN_POTEN:
//					if(comp_dn)
//					{
//						compar[0] &= ~((uint32_t)(1<<c));
//						dn_before_ack[c-DN_cmp] = 0;
//						continue;
//					}
//					break;
//				
//				case EN_BEFORE_ACK:
//					if((!(dn_before_ack[c-DN_cmp]==1) && comp_dn) 
//						||
//						((dn_before_ack[c-DN_cmp]==1) && !(stat_cpu & STAT_ACK_MASK))
//						||
//						((dn_before_ack[c-DN_cmp]==1) && (stat_cpu & STAT_ACK_MASK) && comp_dn))
//					{
//						compar[0] &= ~((uint32_t)(1<<c));
//						dn_before_ack[c-DN_cmp] = 1;
//						continue;
//					}
//					break;
//				
//				default:
//					break;
//			}
//			dn_before_ack[c-DN_cmp] = 0;
//		}
//		
//		if((!comp && ((i_dif[ph_A]>=trshl[ph_A]) || (i_dif[ph_B]>=trshl[ph_B]) || (i_dif[ph_C]>=trshl[ph_C]))) 
//			|| 
//			(comp && ((i_dif[ph_A]>=retr[ph_A]) || (i_dif[ph_B]>=retr[ph_B]) || (i_dif[ph_C]>=retr[ph_C]))))
//		{
//			compar[0] |= (uint32_t)(1<<c);
//		}
//		else
//		{
//			compar[0] &= ~((uint32_t)(1<<c));
//		}		
//	}
//}



//------------------------- Protection algorithm for UROV (  us) ------------------------------
void ProtectUROV(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of UROV
				uint32_t *compar							// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en; 
	uint32_t i_abc[3], trshl, retr;
	uint32_t comp;

	// load data for procedure
	trshl = i_set[UROV_cmp].trshld[0];
	retr = (trshl * i_set[UROV_cmp].k_retrn[0]) / 100;
	for(phases_t j=ph_A; j<=ph_C; j++)	
		i_abc[j] = rotated[I_AH_ROT+j].ef_val;
	main_en = i_set[UROV_cmp].main_enbl;
	comp = compar[0] & COMP_UROV_MASK;

	// process UROV main comparator
	if(!main_en) 
	{
		compar[0] &= COMP_UROV_RESET;	
		return;
	}
	if((!comp && ((i_abc[ph_A]>=trshl) || (i_abc[ph_B]>=trshl) || (i_abc[ph_C]>=trshl))) 
		|| 
		(comp && ((i_abc[ph_A]>=retr) || (i_abc[ph_B]>=retr) || (i_abc[ph_C]>=retr))))
	{
		compar[0] |= COMP_UROV_SET;
	}
	else
	{
		compar[0] &= COMP_UROV_RESET;
	}
}
	

//------------------------- Protection algorithm for APV us) ------------------------------
void ProtectAPV (
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of UROV
				uint32_t *compar							// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en; 
	uint32_t i_abc[3], trshl, retr; 
	uint32_t comp;

	// load data for procedure
	trshl = i_set[APV_cmp].trshld[0];
	retr = (trshl * i_set[APV_cmp].k_retrn[0]) / 100;
	for(phases_t j=ph_A; j<=ph_C; j++)	
		i_abc[j] = rotated[I_AH_ROT+j].ef_val;
	main_en = i_set[APV_cmp].main_enbl;
	comp = compar[0] & COMP_APV_MASK;

	// process APV main comparator
	if(!main_en) 
	{
		compar[0] &= COMP_APV_RESET;	
		return;
	}
	if((!comp && ((i_abc[ph_A]>=trshl) || (i_abc[ph_B]>=trshl) || (i_abc[ph_C]>=trshl))) 
		|| 
		(comp && ((i_abc[ph_A]>=retr) || (i_abc[ph_B]>=retr) || (i_abc[ph_C]>=retr))))
	{
		compar[0] |= COMP_APV_SET;
	}
	else
	{
		compar[0] &= COMP_APV_RESET;
	}
}
	

//-------------------------- Protection algorithm for OBR (  us) ------------------------------
void ProtectOBR	(
				FRZseq_t *i_fr,								// pointer on array of structures that contain datas of forward, revers sequence currents based on line currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return currents of OBR 
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint32_t comp;
	uint32_t trshl, retr, temp_32;
	uint8_t cond, main_en, cmp_num, mode;
	comp_num_t p_set[2] = {OBR_1_cmp, OBR_2_cmp};

	for(int i=0; i<2; i++)
	{
		cmp_num = p_set[i];

		// load data for procedure
		main_en = i_set[cmp_num].main_enbl;
		mode = i_set[cmp_num].add1_enbl;
		comp = compar[0] & (uint32_t)(1<<cmp_num);
		if(!mode)
		{
			trshl = i_set[cmp_num].trshld[0];
			retr = (trshl * i_set[cmp_num].k_retrn[0]) / 100;
		}
		else
		{
			trshl = i_set[cmp_num].trshld[1];
			retr = (trshl * i_set[cmp_num].k_retrn[1]) / 100;
		}

		switch(main_en)
		{
			case IH_ON:
				if(mode) 
					temp_32 = i_fr[0].relat_r2f;
				else 
					temp_32 = i_fr[0].reverse.ef_val;
				cond = (comp && (temp_32>=retr)) || (!comp && (temp_32>=trshl));
				break;
#if _AI_MX_ == _VER_M1_
			case IK_ON:	
				if(mode) 
					temp_32 = i_fr[1].relat_r2f;
				else 
					temp_32 = i_fr[1].reverse.ef_val;
				cond = (comp && (temp_32>=retr)) || (!comp && (temp_32>=trshl));
				break;
#endif
			default:
				cond = 0;
				break;
		}
		if(cond) 
			compar[0] |= (uint32_t)(1<<cmp_num);
		else
			compar[0] &= (uint32_t)~(1<<cmp_num);
	}
}


//--------------------------- Protection algorithm for ZNR us) --------------------------------
void ProtectZNR (
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				uint32_t *del_cur,							// pointer on array that contains datas for unsymmetrical currents - result
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return values
				uint32_t *compar							// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en, mot_strt_contr; 
	uint32_t i_abc[3], min_i, trshl_del, retr_del, trshl_I, retr_I;
	uint32_t comp;

	// load data for procedure
	trshl_del = i_set[ZNR_cmp].trshld[0];
	trshl_I = i_set[ZNR_cmp].trshld[1];
	retr_del = (trshl_del * i_set[ZNR_cmp].k_retrn[0]) / 1000;
	retr_I = (trshl_I * i_set[ZNR_cmp].k_retrn[1]) / 100;
	for(phases_t j=ph_A; j<=ph_C; j++)	
		i_abc[j] = rotated[I_AH_ROT+j].ef_val;
	min_i = i_abc[FindExtrElem(i_abc, 3, MINIM)];
	main_en = i_set[ZNR_cmp].main_enbl;
	mot_strt_contr = i_set[ZNR_cmp].add1_enbl;
	comp = compar[0] & COMP_ZNR_MASK;

	// process ZNR main comparator
	if(!main_en) 
	{
		compar[0] &= COMP_ZNR_RESET;	
		return;
	}
	if( (comp && !(del_cur[0]>=retr_del)) 
		||
		(comp && (del_cur[0]>=retr_del) && !(min_i>=retr_I))
		||
		(!comp && !(del_cur[0]>=trshl_del))
		||
		(!comp && (del_cur[0]>=trshl_del) && !(min_i>=trshl_I)))
	{
		compar[0] &= COMP_ZNR_RESET;
	}
	else if(mot_strt_contr && (compar[1] & COMP_IPD_MASK))
	{
		compar[0] &= COMP_ZNR_RESET;
	}
	else
	{
		compar[0] |= COMP_ZNR_SET;
	}
}


//--------------------------- Protection algorithm for ZMT us) --------------------------------
void ProtectZMT (
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,							// pointer on array of structures that contain datas for treshold/return values
				uint32_t *compar							// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en, mot_strt_contr; 
	uint32_t i_abc[3], max_i, trshl_In, retr_In, trshl_Iv, retr_Iv;
	uint32_t comp;

	// load data for procedure
	trshl_In = i_set[ZMT_cmp].trshld[1];
	trshl_Iv = i_set[ZMT_cmp].trshld[2];
	retr_In = (trshl_In * i_set[ZMT_cmp].k_retrn[1]) / 1000;
	retr_Iv = (trshl_Iv * i_set[ZMT_cmp].k_retrn[2]) / 1000;
	for(phases_t j=ph_A; j<=ph_C; j++)	
		i_abc[j] = rotated[I_AH_ROT+j].ef_val;
	max_i = i_abc[FindExtrElem(i_abc, 3, MAXIM)];
	main_en = i_set[ZMT_cmp].main_enbl;
	mot_strt_contr = i_set[ZMT_cmp].add1_enbl;
	comp = compar[0] & COMP_ZMT_MASK;

	// process ZMT main comparator
	if(!main_en) 
	{
		compar[0] &= COMP_ZMT_RESET;	
		return;
	}
	if( (comp && !(max_i<=retr_Iv)) 
		||
		(comp && (max_i<=retr_Iv) && !(max_i>=retr_In))
		||
		(!comp && !(max_i<=trshl_Iv))
		||
		(!comp && (max_i<=trshl_Iv) && !(max_i>=trshl_In)))
	{
		compar[0] &= COMP_ZMT_RESET;
	}
	else if(mot_strt_contr && (compar[1] & COMP_IPD_MASK))
	{
		compar[0] &= COMP_ZMT_RESET;
	}
	else
	{
		compar[0] |= COMP_ZMT_SET;
	}
}


//-------------------------- Comparator Uf_min processing (  us) ------------------------------
void ComparUFMIN(
				dat4freq_t *f_dat,								// 
				prtct_set_t *i_set,								// pointer on array of structures that contain comparator settings 
				uint32_t *compar								// pointer on variable that stores comparator's states - result
				)
{
	uint32_t trshl, retr;
	
	// load data for procedure
	trshl = i_set[UF_MIN_cmp].trshld[0];
	retr = (trshl * i_set[UF_MIN_cmp].k_retrn[0]) / 100;

	// process U_min comparator
	if(!i_set[ZF_1_cmp].main_enbl && !i_set[ZF_2_cmp].main_enbl)
	{
		compar[0] &= COMP_UF_MIN_RESET;
		return;
	}
	if((!(compar[0] & COMP_UF_MIN_MASK) && !(f_dat->uf_level <= trshl))
		||
		((compar[0] & COMP_UF_MIN_MASK) && !(f_dat->uf_level <= retr)))
	{
		compar[0] &= COMP_UF_MIN_RESET;
	}
	else
	{
		compar[0] |= COMP_UF_MIN_SET;
	}
}


//---------------------------- Protection algorithm for ZF (us) -------------------------------
void ProtectZF 	(
				dat4freq_t *f_dat,								// 
				prtct_set_t *i_set,								// pointer on array of structures that contain datas for treshold/return values
				uint32_t stat_cpu,								// variable that stores states of bits transmitted from CPU
				uint32_t *compar								// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en, cmp_num, rpo_block; 
	uint32_t trshl, retr;
	uint32_t comp;
	comp_num_t  p_set[2] = {ZF_1_cmp, ZF_2_cmp};

	ComparUFMIN(f_dat, i_set, compar);
	for(int i=0; i<2; i++)
	{
		cmp_num = p_set[i];

		// load data for procedure
		main_en = i_set[cmp_num].main_enbl;
		rpo_block = i_set[cmp_num].add1_enbl;
		comp = compar[0] & (uint32_t)(1<<cmp_num);
		trshl = i_set[cmp_num].trshld[0];
		
		// process ZF comparator
		switch(main_en)
		{
			case EN_F_MAX:
				retr = trshl - i_set[cmp_num].k_retrn[0];
				if( (comp && !(f_dat->frequency >= retr))
					||
					(!comp && !(f_dat->frequency >= trshl)))
				{
					compar[0] &= (uint32_t)~(1<<cmp_num);
					continue;
				}
				break;
			
			case EN_F_MIN:
				retr = trshl + i_set[cmp_num].k_retrn[0];
				if( (comp && !(f_dat->frequency <= retr))
					||
					(!comp && !(f_dat->frequency <= trshl)))
				{
					compar[0] &= (uint32_t)~(1<<cmp_num);
					continue;
				}
				break;
			
			default:
				compar[0] &= (uint32_t)~(1<<cmp_num);
				continue;
		}
		if((compar[0] & COMP_UF_MIN_MASK)
			||
			(!(compar[0] & COMP_UF_MIN_MASK) && rpo_block && (stat_cpu & STAT_RPO_MASK)))
		{
			compar[0] &= (uint32_t)~(1<<cmp_num);
		}
		else
		{
			compar[0] |= (uint32_t)(1<<cmp_num);
		}
	}
}


//---------------------------- Protection algorithm for ZN (us) -------------------------------
void ProtectZN 	(
				vect_t *rotated,								// pointer on array of structures that contain datas for vectors calculated for currents
				FRZseq_t *i_fr,									// pointer on array of structures that contain datas of forward, revers sequence currents based on line currents
				prtct_set_t *i_set,								// pointer on array of structures that contain datas for treshold/return values
				uint32_t *compar								// pointer on value that stores comparator's states - result
				)
{
	uint8_t main_en, bnn_blck_en, logic, fin_cond, cond[3], index, cmp_num; 
	uint32_t trshl;
	uint32_t comp;
	comp_num_t p_set[5] = {ZN_1_cmp, ZN_2_cmp, ZN_3_cmp, ZN_4_cmp, ZN_5_cmp};

	for(int i=0; i<5; i++)
	{
		cmp_num = p_set[i]-32;

		// load data for procedure
		main_en = i_set[cmp_num+32].main_enbl;
		bnn_blck_en = i_set[cmp_num+32].add1_enbl;
		logic = i_set[cmp_num+32].add2_enbl;
		comp = compar[1] & (uint32_t)(1<<cmp_num);
		
		// process ZN comparator
		if(!main_en
			||
		   (main_en && bnn_blck_en && (compar[0] & COMP_BNN1_MASK)))
		{
			compar[1] &= (uint32_t)~(1<<cmp_num);
		}
		else
		{
			if(main_en == ZMN_F_ON || main_en == ZMN_L_ON || main_en == U1_MIN_ON)
				index = 1;
			else 
				index = 0;
			if(!comp)	
				trshl = i_set[cmp_num+32].trshld[index];
			else		
				trshl = (i_set[cmp_num+32].trshld[index] * i_set[cmp_num+32].k_retrn[index]) / 100;

			switch(main_en)
			{
				case ZMN_F_ON:
					cond[0] = rotated[U_A_ROT].ef_val <= trshl;
					cond[1] = rotated[U_B_ROT].ef_val <= trshl;
					cond[2] = rotated[U_C_ROT].ef_val <= trshl;
					fin_cond = (((logic==LOGIC_OR) && (cond[0] || cond[1] || cond[2])) 
								|| 
							   (!(logic==LOGIC_OR) && (cond[0] && cond[1] && cond[2])));
					break;
				
				case ZMN_L_ON:
					cond[0] = rotated[U_AB_ROT].ef_val <= trshl;
					cond[1] = rotated[U_BC_ROT].ef_val <= trshl;
					cond[2] = rotated[U_CA_ROT].ef_val <= trshl;
					fin_cond = (((logic==LOGIC_OR) && (cond[0] || cond[1] || cond[2])) 
								|| 
							   (!(logic==LOGIC_OR) && (cond[0] && cond[1] && cond[2])));
					break;
				
				case ZNZ_ON:
//					cond[0] = rotated[U_0_ROT].ef_val >= trshl;
//					cond[1] = rotated[U_B_ROT].ef_val >= trshl;
//					cond[2] = rotated[U_C_ROT].ef_val >= trshl;
//					fin_cond = (((logic==LOGIC_OR) && (cond[0] || cond[1] || cond[2])) 
//								|| 
//							   (!(logic==LOGIC_OR) && (cond[0] && cond[1] && cond[2])));
					fin_cond = rotated[U_0_ROT].ef_val >= trshl;
					break;
				
				case ZPN_L_ON:
					cond[0] = rotated[U_AB_ROT].ef_val >= trshl;
					cond[1] = rotated[U_BC_ROT].ef_val >= trshl;
					cond[2] = rotated[U_CA_ROT].ef_val >= trshl;
					fin_cond = (((logic==LOGIC_OR) && (cond[0] || cond[1] || cond[2])) 
								|| 
							   (!(logic==LOGIC_OR) && (cond[0] && cond[1] && cond[2])));
					break;
				
				case U2_MAX_ON:
					fin_cond = i_fr[2].reverse.ef_val >= trshl;
					break;
				
				default:
					fin_cond = i_fr[2].forward.ef_val <= trshl;
					break;
			}
			if(fin_cond)
				compar[1] |= (uint32_t)(1<<cmp_num);
			else
				compar[1] &= (uint32_t)~(1<<cmp_num);
		}
	}
}


//-------------------------- Comparator of BNN processing (  us) ------------------------------
void ProtectBNN	(
				vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
				vect_t *u_bnn,								// structure that contains datas for vectors calculated for currents
				FRZseq_t *i_fr,								// pointer on array of structures that contain datas of forward, revers sequence currents based on line currents
				prtct_set_t *i_set,							// pointer on array of structures that contain comparator settings 
				uint32_t stat_cpu,							// variable that stores states of bits transmitted from CPU
				uint32_t *compar							// pointer on variable that stores comparator's states - result
				)
{
	uint8_t ubnn_en, u0i0_en, u2i2_en, u1i1_en, cond_tr, cond_ret; 
	uint32_t comp, trsh[3], retr[3];
	
	// load data for procedure
	ubnn_en = i_set[BNN1_cmp].main_enbl;
	u0i0_en = i_set[BNN1_cmp].add1_enbl;
	u2i2_en = i_set[BNN1_cmp].add2_enbl;
	u1i1_en = i_set[BNN1_cmp].add3_enbl;
	comp = compar[0] & COMP_BNN1_MASK;

	
	// process ZN comparator
	trsh[0] = i_set[BNN1_cmp].trshld[0];
	retr[0] = (trsh[0] * i_set[BNN1_cmp].k_retrn[0]) / 100;
	cond_tr = u_bnn->ef_val >= trsh[0];
	cond_ret = u_bnn->ef_val >= retr[0];
	if(ubnn_en)
	{
		if( (!comp && cond_tr) 
			|| 
			(comp && cond_ret) )
		{
			compar[0] |= COMP_BNN1_SET;
			return;
		}
	}

	trsh[0] = i_set[BNN1_cmp].trshld[1];
	retr[0] = (trsh[0] * i_set[BNN1_cmp].k_retrn[1]) / 100;
	trsh[1] = i_set[BNN1_cmp].trshld[2];
	retr[1] = (trsh[1] * i_set[BNN1_cmp].k_retrn[2]) / 100;
	cond_tr = (rotated[U_0_ROT].ef_val >= trsh[0]) && (rotated[I_0_ROT].ef_val <= trsh[1]);
	cond_ret = (rotated[U_0_ROT].ef_val >= retr[0]) && (rotated[I_0_ROT].ef_val <= retr[1]);
	if(u0i0_en)
	{
		if( (!comp && cond_tr) 
			|| 
			(comp && cond_ret) )
		{
			compar[0] |= COMP_BNN1_SET;
			return;
		}
	}

	trsh[0] = i_set[BNN1_EXT1_cmp].trshld[0];
	retr[0] = (trsh[0] * i_set[BNN1_EXT1_cmp].k_retrn[0]) / 100;
	trsh[1] = i_set[BNN1_EXT1_cmp].trshld[1];
	retr[1] = (trsh[1] * i_set[BNN1_EXT1_cmp].k_retrn[1]) / 100;
	cond_tr = (i_fr[2].reverse.ef_val >= trsh[0]) && (i_fr[0].reverse.ef_val <= trsh[1]);
	cond_ret = (i_fr[2].reverse.ef_val >= retr[0]) && (i_fr[0].reverse.ef_val <= retr[1]);
	if(u2i2_en)
	{
		if( (!comp && cond_tr) 
			|| 
			(comp && cond_ret) )
		{
			compar[0] |= COMP_BNN1_SET;
			return;
		}
	}

	trsh[0] = i_set[BNN1_EXT1_cmp].trshld[2];
	retr[0] = (trsh[0] * i_set[BNN1_EXT1_cmp].k_retrn[2]) / 100;
	trsh[1] = i_set[BNN1_EXT2_cmp].trshld[0];
	retr[1] = (trsh[1] * i_set[BNN1_EXT2_cmp].k_retrn[0]) / 100;
	trsh[2] = i_set[BNN1_EXT2_cmp].trshld[1];
	retr[2] = (trsh[2] * i_set[BNN1_EXT2_cmp].k_retrn[1]) / 100;
	cond_tr = (i_fr[2].forward.ef_val <= trsh[0]) && (i_fr[0].forward.ef_val <= trsh[1]) && (i_fr[0].forward.ef_val >= trsh[2]);
	cond_ret = (i_fr[2].forward.ef_val <= retr[0]) && (i_fr[0].forward.ef_val <= retr[1]) && (i_fr[0].forward.ef_val >= retr[2]);
	if(u1i1_en)
	{
		if( (!comp && cond_tr) 
			||
			(comp && cond_ret) )
		{
			compar[0] |= COMP_BNN1_SET;
			return;
		}
	}
	
	trsh[0] = i_set[BNN1_EXT2_cmp].trshld[2];
	retr[0] = (trsh[0] * i_set[BNN1_EXT2_cmp].k_retrn[2]) / 100;
	cond_tr = 	(rotated[U_AB_ROT].ef_val <= trsh[0]) || 
				(rotated[U_BC_ROT].ef_val <= trsh[0]) || 
				(rotated[U_CA_ROT].ef_val <= trsh[0]);
	cond_ret =	(rotated[U_AB_ROT].ef_val <= retr[0]) || 
				(rotated[U_BC_ROT].ef_val <= retr[0]) || 
				(rotated[U_CA_ROT].ef_val <= retr[0]);
	if(((stat_cpu & STAT_DI_BNN1_MASK) && !comp && cond_tr)
		||
		((stat_cpu & STAT_DI_BNN1_MASK) && comp && cond_ret))
	{
		compar[0] |= COMP_BNN1_SET;
	}
	else
	{
		compar[0] &= COMP_BNN1_RESET;
	}
}


//------------------------ Comparator of ZZP & ZBR processing (  us) --------------------------
void ProtectZZP_ZBR	(
					vect_t *rotated,							// pointer on array of structures that contain datas for vectors calculated for currents
					prtct_set_t *i_set,							// pointer on array of structures that contain comparator settings 
					uint32_t *compar							// pointer on variable that stores comparator's states - result
					)
{
	uint32_t max_cur, temp_arr[3];
	int	strt_mot_timer_out, strt_mot_plus_timer_out, blck_rot_timer_out, temp_cmp;
	static uint32_t strt_mot_timer, strt_mot_plus_timer, blck_rot_timer;
	
	if(i_set[ZZP_cmp].main_enbl)
	{
		// find max current value 
		for(int i=0; i<3; i++) 
			temp_arr[i] = rotated[I_AH_ROT+i].ef_val;
		max_cur = temp_arr[FindExtrElem(temp_arr, 3, MAXIM)];
		
		// timers processing
		if(max_cur > i_set[ZZP_cmp].trshld[0])
		{
			if(blck_rot_timer < i_set[ZBR_cmp].T_set)
			{
				blck_rot_timer += 5;
				blck_rot_timer_out = 0;
			}
			else
				blck_rot_timer_out = 1;
			if(strt_mot_timer < i_set[ZZP_cmp].T_set)
			{
				strt_mot_timer += 5;
				strt_mot_timer_out = 0;
			}
			else
				strt_mot_timer_out = 1;
		}
		else
		{
			blck_rot_timer = 0;
			blck_rot_timer_out = 0;
			strt_mot_timer = 0;
			strt_mot_timer_out = 0;
		}

		if(compar[1] & COMP_IPD_MASK)
		{
			if(strt_mot_plus_timer < (i_set[ZZP_cmp].T_set + 200))
			{
				strt_mot_plus_timer += 5;
				strt_mot_plus_timer_out = 0;
			}
			else
				strt_mot_plus_timer_out = 1;
		}
		else
		{
			strt_mot_plus_timer = 0;
			strt_mot_plus_timer_out = 0;
		}
		
		// comparators processing
		temp_cmp = (compar[1] & COMP_IPD_MASK) && !strt_mot_plus_timer_out;
		if(blck_rot_timer_out && !temp_cmp)
		{
			compar[1] |= COMP_ZBR_SET;
		}
		else
		{
			compar[1] &= COMP_ZBR_RESET;
		}

		if(strt_mot_timer_out && temp_cmp)
		{
			compar[1] |= COMP_ZZP_SET;
		}
		else
		{
			compar[1] &= COMP_ZZP_RESET;
		}
	}
	else
	{
		compar[1] &= COMP_ZBR_RESET;
		compar[1] &= COMP_ZZP_RESET;
	}
}


//----------------------- Comparator of IPD & MOT_ON processing (  us) ------------------------
void ProtectIPD	(
				vect_t *rotated,								// pointer on array of structures that contain datas for vectors calculated for currents
				prtct_set_t *i_set,								// pointer on array of structures that contain comparator settings 
				uint32_t stat_cpu,								// variable that stores states of bits transmitted from CPU
				uint32_t *compar								// pointer on variable that stores comparator's states - result
				)
{
	uint32_t comp_mot_on, max_cur, temp_arr[3], trshl;
	uint32_t strt_ctrl_timer_out, strt_len_timer_out, rpo, ncevo, bl_cont_ctrl_en, cond1, cond2, cond3;
	static uint32_t strt_ctrl_timer, strt_len_timer;
	
	// load data for procedure
	rpo = stat_cpu & STAT_RPO_MASK;
	ncevo = stat_cpu & STAT_NCEVO_MASK;
	bl_cont_ctrl_en = (uint32_t)i_set[IPD_cmp].add1_enbl;
	comp_mot_on = compar[1] & COMP_MOT_ON_MASK;
	
	
	// find max current value 
	for(int i=0; i<3; i++)
		temp_arr[i] = rotated[I_AH_ROT+i].ef_val;
	max_cur = temp_arr[FindExtrElem(temp_arr, 3, MAXIM)];
	
	// process hysteresys
	if(!comp_mot_on)
		trshl = i_set[IPD_cmp].trshld[0];
	else
		trshl = i_set[IPD_cmp].trshld[0] * 95 / 100;

	// timer processing
	if(max_cur > trshl)
	{
		if(strt_ctrl_timer < (i_set[MOT_ON_cmp].T_set))
		{
			strt_ctrl_timer += 5;
			strt_ctrl_timer_out = 1;
		}
		else
			strt_ctrl_timer_out = 0;
	}
	else
	{
		strt_ctrl_timer = 0;
		strt_ctrl_timer_out = 0;
	}

	// comparator processing
	cond1 = (((rpo && !ncevo && bl_cont_ctrl_en) || !bl_cont_ctrl_en)			// R
			&&
			!(max_cur > trshl));
	
	cond2 = (((!rpo && !ncevo && bl_cont_ctrl_en) || !bl_cont_ctrl_en)			// S
			&&
			(max_cur > i_set[IPD_cmp].trshld[1])
			&&
			strt_ctrl_timer_out);
	
	cond3 = !cond1 && (comp_mot_on || (!comp_mot_on && cond2));
	
	// timer processing
	if(cond3)
	{
		if(strt_len_timer < (i_set[IPD_cmp].T_set))
		{
			strt_len_timer += 5;
			strt_len_timer_out = 1;
		}
		else
			strt_len_timer_out = 0;
	}
	else
	{
		strt_len_timer = 0;
		strt_len_timer_out = 0;
	}

	// comparator processing
	if(cond3)
		compar[1] |= COMP_MOT_ON_SET;
	else
		compar[1] &= COMP_MOT_ON_RESET;
	
	if(strt_len_timer_out)
		compar[1] |= COMP_IPD_SET;
	else
		compar[1] &= COMP_IPD_RESET;
}


//--------------------------- Comparator of TZP processing (  us) -----------------------------
void ProtectTZP	(
				therm_t *thermal,									// pointer on structure that contains datas for motor thermal state
				prtct_set_t *i_set,									// pointer on array of structures that contain comparator settings 
				uint32_t *compar									// array of variables that store comparator's states - result
				)
{
	uint32_t trash_e, trash_w, retr_e, retr_w, overheat, comp_e, comp_w;
	
	//load data
	trash_e = i_set[TZP_EMRG_cmp].trshld[0] * 10000;
	trash_w = i_set[TZP_WARN_cmp].trshld[0] * 10000;
	retr_e = (trash_e * i_set[TZP_EMRG_cmp].k_retrn[0]) / 100;
	retr_w = (trash_w * i_set[TZP_WARN_cmp].k_retrn[0]) / 100;
	overheat = thermal->ovrht;
	comp_e = compar[1] & COMP_TZP_EMRG_MASK;
	comp_w = compar[1] & COMP_TZP_WARN_MASK;
	
	//comparator processing
	if(i_set[TZP_EMRG_cmp].main_enbl)
	{
		if( (comp_w && (overheat >= retr_w))
			||
			(!comp_w && (overheat >= trash_w)))
		{
			compar[1] |= COMP_TZP_WARN_SET;
			if( (comp_e && (overheat >= retr_e))
				||
				(!comp_e && (overheat >= trash_e)))
			{
				compar[1] |= COMP_TZP_EMRG_SET;
			}
			else
			{
				compar[1] &= COMP_TZP_EMRG_RESET;
			}
		}
		else
		{
			compar[1] &= COMP_TZP_WARN_RESET;
			compar[1] &= COMP_TZP_EMRG_RESET;
		}
	}
	else
	{
		compar[1] &= COMP_TZP_WARN_RESET;
		compar[1] &= COMP_TZP_EMRG_RESET;
	}
}


//extern uint8_t 	led_st;
//--------------- Receive settings handler, starts updating of settings ( us) -----------------
void ReceiveSettingsHandler	(
							uint8_t *rx_data,					// pointer on array of bytes received from CPU
							set_stts_t *settings_stat
							)
{
	settings_stat->cntrl = RCV_SET_START;						// if comand arrived - set handler flag
	settings_stat->blck_num = rx_data[RX_SET_BLCK_NUM];			// load data block number & length
	settings_stat->blck_lngth = rx_data[RX_SET_BLCK_LEN];
}


//------------------------- Receive settings data from CPU ( us) ------------------------------
void ReceiveSettings(
					uint8_t *rx_data,							// pointer on array of bytes received from CPU
					set_stts_t *settings_stat,					// pointer on structure that indicates settings update status  
					uint8_t *collector							// pointer on array with collected settings data
//					setngs_t *coef,								// pointer on structure that contains device settings 
//					prtct_set_t *i_set,							// pointer on array of structures that contain datas for protect settings
//					RTC_stts_t *rtc_set							// pointer on structure with RTC settings
					)
{
	static int strt, fin, pack_cnt;
	
	// if handler flag setted (comand arrived)	
	if(settings_stat->cntrl == RCV_SET_START)
	{
		// fill collector buffer with current pack content
		if(settings_stat->blck_num == 0) 
			strt = 0;
		fin = strt + settings_stat->blck_lngth;
		for(int i=strt; i<fin; i++)
			collector[i] = rx_data[RX_SET_DATA+i-strt];
		
		// if all data are collected, update settings array, set flags and reset handler for next receive
		if(settings_stat->blck_num == 2)
		{
			// send from collector to settings array
			if(pack_cnt == settings_stat->blck_num)
			{
				settings_stat->sttus = UPDATING;
			}
			strt = 0;
			pack_cnt = 0;
		}
		else
		{
			strt = fin;
			pack_cnt++;
		}			
		// finally - reset handler flag
		settings_stat->cntrl = RCV_SET_STOP;
	}
}


//------------------- Unzip settings from collector array to structure ( us) ------------------
void UnzipSettings	(
					uint8_t *collector,							// pointer on array with collected settings data
					setngs_t *coef,								// pointer on structure that contains device settings 
					prtct_set_t *i_set,							// pointer on array of structures that contain datas for protect settings
					rtc_strct_t *rtc_data														// pointer on structure with RTC settings
					)
{
	uint8_t temp8;
	uint16_t temp16, temp17;
	uint32_t temp32, temp33, temp34; 
	
	// RTC (summer-winter time account)
	rtc_data->summer_time_need = collector[Data2_AddFags_AutoDaylightTimeSet_a] & (1<<Data2_AddFags_AutoDaylightTimeSet_bit);							
	
	// Coeffitients
	// Ktv  (1...4000)
	temp16 = ((uint16_t)collector[Data2_KT_KTN_a]) << 8;
	temp16 += (uint16_t)collector[Data2_KT_KTN_a+1];
	coef->ktv = (uint32_t)temp16;	

	// Ktv0 (1...4000)
	temp16 = ((uint16_t)collector[Data2_KT_KTN0_a]) << 8;
	temp16 += (uint16_t)collector[Data2_KT_KTN0_a+1];
	coef->ktv0 = (uint32_t)temp16;	

	// Kt_n  (0.00 - 1.00) <-> (0 - 100)
	temp16 = ((uint16_t)collector[Data1_DT_Kn_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DT_Kn_a+1]) * 100;
	coef->k_t[0] = (uint32_t)(temp16 + (temp17>>8));	

	// Kt_k  (0.00 - 1.00) <-> (0 - 100)
	temp16 = ((uint16_t)collector[Data1_DT_Kk_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DT_Kk_a+1]) * 100;
	coef->k_t[1] = (uint32_t)(temp16 + (temp17>>8));

	// k_t  (0.00 - 0.90) <-> (0 - 90)
	temp16 = ((uint16_t)collector[Data1_DT_Kt_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DT_Kt_a+1]) * 100;
	coef->k_br = (uint32_t)(temp16 + (temp17>>8));	

	// It0  (1.50 - 4.00 A) <-> (277 - 740)
	temp16 = ((uint16_t)collector[Data1_DT_It0_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DT_It0_a+1]) * 100;
	coef->i_t0 = (((uint32_t)(temp16 + (temp17>>8))) * K_TA)/100;							// in rel. units 	

	// Idt0  (0.10 - 100.00 A) <-> (18 - 18500)
	temp16 = ((uint16_t)collector[Data1_DT_Idt0_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DT_Idt0_a+1]) * 100;
	coef->i_dt0 = (((uint32_t)(temp16 + (temp17>>8))) * K_TA)/100;							// in rel. units  	
	
	// Id0  (0.1 - 100.0 A) <-> (18 - 18500)
	temp16 = ((uint16_t)collector[Data1_DO_Ido_a]) * 10;
	temp17 = ((uint16_t)collector[Data1_DO_Ido_a+1]) * 10;
	coef->i_do = (((uint32_t)(temp16 + (temp17>>8))) * K_TA)/10;							// in rel. units  	
	
	// It_ogr (10 - 80 A) <-> (1850 - 14800)
	coef->i_tlim = ((uint32_t)collector[Data1_DT_It_bnd_a]) * K_TA;							// in rel. units  	
	
	// I_nom (0.02 - 10.00 A) <-> (3 - 1850)
	temp16 = ((uint16_t)collector[Data1_TZP_Icur_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_TZP_Icur_a+1]) * 100;
	coef->mot_current_nom = (((uint32_t)(temp16 + (temp17>>8))) * K_TA)/100;				// in rel. units  	

	// T_nagrev (100 - 10000 s)
	temp16 = ((uint16_t)collector[Data1_TZP_Theat_a]) << 8;
	coef->heat_const = temp16 + ((uint16_t)collector[Data1_TZP_Theat_a+1]);					// in sec
	
	// T_ostyv (100 - 10000 s)
	temp16 = ((uint16_t)collector[Data1_TZP_Tcd_a]) << 8;
	coef->cool_const = temp16 + ((uint16_t)collector[Data1_TZP_Tcd_a+1]);					// in sec

	// t_nach (220 - 345 K)
	temp16 = ((uint16_t)collector[Data1_TZP_tKh_a]) << 8;
	coef->temprt_motor_start = temp16 + ((uint16_t)collector[Data1_TZP_tKh_a+1]);			// in K

	// t_okr_nom (220 - 345 K)
	temp16 = ((uint16_t)collector[Data1_TZP_tKam_n_a]) << 8;
	coef->temprt_envir_nom = temp16 + ((uint16_t)collector[Data1_TZP_tKam_n_a+1]);			// in K
	
	// t_okr (220 - 345 K)
	temp16 = ((uint16_t)collector[Data1_TZP_tKam_a]) << 8;
	coef->temprt_envir = temp16 + ((uint16_t)collector[Data1_TZP_tKam_a+1]);				// in K

	// Isol_class 
	switch(collector[Data1_TZP_IC_a])
	{
		case 1:
			temp16 = 378;
			break;
		case 2:
			temp16 = 393;
			break;
		case 3:
			temp16 = 403;
			break;
		case 4:
			temp16 = 428;
			break;
		case 5:
			temp16 = 453;
			break;
		case 6:
			temp16 = 478;
			break;
		default:
			temp16 = 363;
			break;
	}
	coef->temprt_motor_crtic = temp16;														// in K
	
	// DT settings
	i_set[DT_cmp].main_enbl = collector[Data1_DT_Mode_a];									// 0/1
	i_set[DT_cmp].add1_enbl = collector[Data1_DT_BlocDN_a];									// 0/1/2
//	for(phases_t i=ph_A; i<=ph_C; i++)
//	{
//		if(break_cur[i]<coef->i_t0)
//		{
//			temp32 = coef->i_dt0;
//		}
//		else if(break_cur[i]>=coef->i_t0 && break_cur[i]<coef->i_tlim) 
//		{
//			temp32 = coef->i_dt0 + ((break_cur[i] - coef->i_t0) * coef->k_br) / 100;
//		}
//		else 
//		{
//			temp32 = coef->i_dt0 + ((coef->i_tlim - coef->i_t0) * coef->k_br) / 100; 
//		}
//		i_set[DT_cmp].trshld[i] 		= temp32;											// in rel. units    
//		i_set[DT_cmp].k_retrn[i] 		= 95;												// in %  
//	}	

	// DO settings
	i_set[DO_cmp].main_enbl 			= collector[Data1_DO_Mode_a];						// 0/1
	i_set[DO_cmp].add1_enbl 			= collector[Data1_DO_BlocDN_a];						// 0/1/2
//	for(phases_t i=ph_A; i<=ph_C; i++)
//	{
//		if(i_set[DT_cmp].trshld[i] <= coef->i_do) 
//			i_set[DO_cmp].trshld[i] 	= coef->i_do;										// in rel. units  
//		else 
//			i_set[DO_cmp].trshld[i] 	= i_set[DT_cmp].trshld[i];							// in rel. units  
//		temp32 = i_set[DT_cmp].trshld[i]*i_set[DT_cmp].k_retrn[i];
//		if(temp32 <= coef->i_do * 95) 
//			i_set[DO_cmp].k_retrn[i] 	= (coef->i_do * 95) / i_set[DO_cmp].trshld[i];		// in %  
//		else 
//			i_set[DO_cmp].k_retrn[i] 	= temp32 / i_set[DO_cmp].trshld[i];					// in %
//	}	

	// DN settings
	i_set[DN_cmp].main_enbl = collector[Data1_DN_Mode_a];									// 0/1
	temp16 = ((uint16_t)collector[Data1_DN_Idn_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_DN_Idn_a+1]) * 100;
	i_set[DN_cmp].trshld[0] = (((uint32_t)(temp16 + (temp17>>8))) * K_TA)/100;				// in rel. units  	
	i_set[DN_cmp].k_retrn[0] = 95;															// in %  	

	// MTZ1..MTZ4 settings
	uint32_t adr_mtz[4] = {Data1_MTZ1_a, Data1_MTZ2_a, Data1_MTZ3_a, Data1_MTZ4_a};
	comp_num_t mtz[4] = {MTZ_1_cmp, MTZ_2_cmp, MTZ_3_cmp, MTZ_4_cmp};
	for(int n=0; n<4; n++)
	{
		temp32 = adr_mtz[n];
		comp_num_t mtz_num = mtz[n];
		temp8 = collector[temp32+0];
		i_set[mtz_num].main_enbl 		= ((temp8 & (1<<Data1_MTZ1_Mode_On_bit)) != 0);
		i_set[mtz_num].dir_enbl 		= ((temp8 & (1<<Data1_MTZ1_Mode_NAPR_bit)) != 0);
		i_set[mtz_num].add3_enbl 		= ((temp8 & (1<<Data1_MTZ1_Mode_LockVMB_bit)) != 0);
		i_set[mtz_num].add1_enbl 		= collector[temp32+(Data1_MTZ1_BlocBNN_a-Data1_MTZ1_a)];
		i_set[mtz_num].add2_enbl 		= collector[temp32+(Data1_MTZ1_BlocU_a-Data1_MTZ1_a)];
		i_set[mtz_num].tcc 				= (tcc_t)collector[temp32+(Data1_MTZ1_TMode_a-Data1_MTZ1_a)];
		temp16 	= ((uint16_t)collector[temp32+(Data1_MTZ1_Fms_a-Data1_MTZ1_a)]) << 8;
		temp16 += (uint16_t)collector[temp32+(Data1_MTZ1_Fms_a-Data1_MTZ1_a)+1];
		i_set[mtz_num].ang_set[0] 		= temp16;															// in deg.
		i_set[mtz_num].ang_set[1] 		= ((uint16_t)collector[temp32+(Data1_MTZ1_Fw_a-Data1_MTZ1_a)]) / 2;	// in deg.
		i_set[mtz_num].ang_set[2] 		= (uint16_t)(i_set[mtz_num].ang_set[1] + collector[Data2_GYST_a]);	// in deg.
		
		temp33 = ((uint32_t)collector[temp32+(Data1_MTZ1_Tsr_a-Data1_MTZ1_a)]) << 16;
		temp33 += (((uint32_t)collector[temp32+(Data1_MTZ1_Tsr_a-Data1_MTZ1_a)+1]) << 8);
		temp33 += (uint32_t)collector[temp32+(Data1_MTZ1_Tsr_a-Data1_MTZ1_a)+2];
		i_set[mtz_num].T_set 			= temp33;															// in sec.
		
		temp16 = ((uint16_t)collector[temp32+(Data1_MTZ1_Imtz_a-Data1_MTZ1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_MTZ1_Imtz_a-Data1_MTZ1_a+1)]) * 100;
		i_set[mtz_num].trshld[0] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
		i_set[mtz_num].k_retrn[0] 		= 95;																// in %
	}

	// KAM1..KAM3 settings
	uint32_t adr_kam[3] = {Data1_KAM1_a, Data1_KAM2_a, Data1_KAM3_a};
	comp_num_t kam[3] = {KAM_1_cmp, KAM_2_cmp, KAM_3_cmp};
	for(int n=0; n<3; n++)
	{
		temp32 = adr_kam[n];
		comp_num_t kam_num = kam[n];
		temp8 = collector[temp32+0];
		i_set[kam_num].main_enbl 		= ((temp8 & (1<<Data1_KAM1_Mode_On_bit)) != 0);
		i_set[kam_num].add1_enbl 		= ((temp8 & (1<<Data1_KAM1_Mode_BlocRPO_bit)) != 0);
		i_set[kam_num].add2_enbl 		= ((temp8 & (1<<Data1_KAM1_Mode_BlocPusk_bit)) != 0);
		i_set[kam_num].dir_enbl 		= collector[temp32+(Data1_KAM1_NAPR_a-Data1_KAM1_a)];
		temp16 	= ((uint16_t)collector[temp32+(Data1_KAM1_Pub_a-Data1_KAM1_a)]) << 8;
		temp16 += (uint16_t)collector[temp32+(Data1_KAM1_Pub_a-Data1_KAM1_a)+1];
		i_set[kam_num].trshld[0] 		= temp16;														// in Watt(?)
		temp16 	= ((uint16_t)collector[temp32+(Data1_KAM1_Plb_a-Data1_KAM1_a)]) << 8;
		temp16 += (uint16_t)collector[temp32+(Data1_KAM1_Plb_a-Data1_KAM1_a)+1];
		i_set[kam_num].trshld[1] 		= temp16;														// in Watt(?)
		i_set[kam_num].trshld[2] 		= (uint16_t)collector[temp32+(Data1_KAM1_Pmin_a-Data1_KAM1_a)];	// in Watt(?)

		temp16 = ((uint16_t)collector[temp32+(Data1_KAM1_Kub_a-Data1_KAM1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_KAM1_Kub_a-Data1_KAM1_a+1)]) * 100;
		i_set[kam_num].k_retrn[0] 		= (uint32_t)(temp16 + (temp17>>8));								// in %
		temp16 = ((uint16_t)collector[temp32+(Data1_KAM1_Klb_a-Data1_KAM1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_KAM1_Klb_a-Data1_KAM1_a+1)]) * 100;
		i_set[kam_num].k_retrn[1] 		= (uint32_t)(temp16 + (temp17>>8));								// in %
		i_set[kam_num].k_retrn[2] 		= 95;															// in %
	}

	// ZNZ1..ZNZ3 settings
	uint32_t adr_znz[3] = {Data1_ZNZ1_a, Data1_ZNZ2_a, Data1_ZNZ3_a};
	comp_num_t znz[3] = {ZNZ_1_cmp, ZNZ_2_cmp, ZNZ_3_cmp};
	for(int n=0; n<3; n++)
	{
		temp32 = adr_znz[n];
		comp_num_t znz_num = znz[n];
		temp8 = collector[temp32+(Data1_ZNZ1_Mode_a-Data1_ZNZ1_a)];
		i_set[znz_num].dir_enbl 		= ((temp8 & (1<<Data1_ZNZ1_Mode_wUp_bit)) != 0);
		i_set[znz_num].add1_enbl 		= ((temp8 & (1<<Data1_ZNZ1_Mode_wIo_bit)) != 0);
		i_set[znz_num].add2_enbl 		= ((temp8 & (1<<Data1_ZNZ1_Mode_wUo_bit)) != 0);
		i_set[znz_num].main_enbl 		= collector[temp32+(Data1_ZNZ1_BlocBNN_a-Data1_ZNZ1_a)];

		temp16 	= ((uint16_t)collector[temp32+(Data1_ZNZ1_Fms_a-Data1_ZNZ1_a)]) << 8;
		temp16 += (uint16_t)collector[temp32+(Data1_ZNZ1_Fms_a-Data1_ZNZ1_a)+1];
		i_set[znz_num].ang_set[0] 		= temp16;															// in deg.
		i_set[znz_num].ang_set[1] 		= ((uint16_t)collector[temp32+(Data1_ZNZ1_Fw_a-Data1_ZNZ1_a)]) / 2;	// in deg.
		i_set[znz_num].ang_set[2] 		= (uint16_t)(i_set[znz_num].ang_set[1] + collector[Data2_GYST_a]);	// in deg.

		temp33 = ((uint32_t)collector[temp32+(Data1_ZNZ1_Iy_a-Data1_ZNZ1_a)]) * 1000;
		temp34 = ((uint32_t)collector[temp32+(Data1_ZNZ1_Iy_a-Data1_ZNZ1_a+1)]) << 8;
		temp34 += (uint32_t)collector[temp32+(Data1_ZNZ1_Iy_a-Data1_ZNZ1_a+2)];
		temp34 *= 1000;
		i_set[znz_num].trshld[0] 		= (((uint32_t)(temp33 + (temp34>>16))) * K_TA0) / 1000;				// in rel. units
		i_set[znz_num].k_retrn[0] 		= 95;																// in %

		temp16 = ((uint16_t)collector[temp32+(Data1_ZNZ1_Uy_a-Data1_ZNZ1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_ZNZ1_Uy_a-Data1_ZNZ1_a+1)]) * 100;
		i_set[znz_num].trshld[1] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 100;				// in rel. units
		i_set[znz_num].k_retrn[1] 		= 95;																// in %

		temp16 = ((uint16_t)collector[temp32+(Data1_ZNZ1_Uy0_a-Data1_ZNZ1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_ZNZ1_Uy0_a-Data1_ZNZ1_a+1)]) * 100;
		i_set[znz_num].trshld[2] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 100;				// in rel. units
	}

	// OBR1..OBR2 settings
	uint32_t adr_obr[2] = {Data1_OBR1_a, Data1_OBR2_a};
	comp_num_t obr[2] = {OBR_1_cmp, OBR_2_cmp};
	for(int n=0; n<2; n++)
	{
		temp32 = adr_obr[n];
		comp_num_t obr_num = obr[n];
		i_set[obr_num].main_enbl 		= collector[temp32+(Data1_OBR1_On_a-Data1_OBR1_a)];
		i_set[obr_num].add1_enbl 		= collector[temp32+(Data1_OBR1_Mode_a-Data1_OBR1_a)];
		
		temp16 = ((uint16_t)collector[temp32+(Data1_OBR1_Iobr_a-Data1_OBR1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_OBR1_Iobr_a-Data1_OBR1_a+1)]) * 100;
		i_set[obr_num].trshld[0] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
		i_set[obr_num].k_retrn[0] 		= 95;																// in %
		temp16 = ((uint16_t)collector[temp32+(Data1_OBR1_I2divI1_a-Data1_OBR1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_OBR1_I2divI1_a-Data1_OBR1_a+1)]) * 100;
		i_set[obr_num].trshld[1] 		= (uint32_t)(temp16 + (temp17>>8));									// in %
		i_set[obr_num].k_retrn[1] 		= 95;																// in %
	}
	
	// ZN1..ZN5 settings
	uint32_t adr_zn[5] = {Data1_ZN1_a, Data1_ZN2_a, Data1_ZN3_a, Data1_ZN4_a, Data1_ZN5_a};
	comp_num_t zn[5] = {ZN_1_cmp, ZN_2_cmp, ZN_3_cmp, ZN_4_cmp, ZN_5_cmp};
	for(int n=0; n<5; n++)
	{
		temp32 = adr_zn[n];
		comp_num_t zn_num = zn[n];
		i_set[zn_num].main_enbl = collector[temp32+(Data1_ZN1_Mode_a-Data1_ZN1_a)];
		temp8 = collector[temp32+(Data1_ZN1_BF_a-Data1_ZN1_a)];
		i_set[zn_num].add1_enbl 		= ((temp8 & (1<<Data1_ZN1_BF_BlocBNN_bit)) != 0);
		i_set[zn_num].add2_enbl 		= ((temp8 & (1<<Data1_ZN1_BF_Logics_bit)) != 0);
		
		temp16 = ((uint16_t)collector[temp32+(Data1_ZN1_U_a-Data1_ZN1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_ZN1_U_a-Data1_ZN1_a+1)]) * 100;
		i_set[zn_num].trshld[0] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 100;				// in rel. units
		i_set[zn_num].trshld[1] 		= i_set[zn_num].trshld[0];											// in rel. units
		i_set[zn_num].k_retrn[0] 		= 95;																// in %
		i_set[zn_num].k_retrn[1] 		= 105;																// in %
	}

	// ZF1..ZF2 settings
	uint32_t adr_zf[2] = {Data1_ZC1_a, Data1_ZC2_a};
	comp_num_t zf[2] = {ZF_1_cmp, ZF_2_cmp};
	for(int n=0; n<2; n++)
	{
		temp32 = adr_zf[n];
		comp_num_t zf_num = zf[n];
		i_set[zf_num].main_enbl 		= collector[temp32+(Data1_ZC1_Mode_a-Data1_ZC1_a)];
		i_set[zf_num].add1_enbl 		= collector[temp32+(Data1_ZC1_BlocRPO_a-Data1_ZC1_a)];
		
		temp16 = ((uint16_t)collector[temp32+(Data1_ZC1_Fsr_a-Data1_ZC1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_ZC1_Fsr_a-Data1_ZC1_a+1)]) * 100;
		i_set[zf_num].trshld[0] 		= ((uint32_t)(temp16 + (temp17>>8)));								// in Hz*100
		temp16 = ((uint16_t)collector[temp32+(Data1_ZC1_pFret_a-Data1_ZC1_a)]) * 100;
		temp17 = ((uint16_t)collector[temp32+(Data1_ZC1_pFret_a-Data1_ZC1_a+1)]) * 100;
		i_set[zf_num].k_retrn[0] 		= ((uint32_t)(temp16 + (temp17>>8)));								// in Hz*100
	}

	// UFMIN settings
	temp16 = ((uint16_t)collector[Data1_Common_UFmin_a]) * 10;
	temp17 = ((uint16_t)collector[Data1_Common_UFmin_a+1]) * 10;
	i_set[UF_MIN_cmp].trshld[0] 		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 10;					// in rel. units
	i_set[UF_MIN_cmp].k_retrn[0] 		= 105;																// in %
	
	// VMB settings
	i_set[VMB_cmp].main_enbl 			= collector[Data1_Common_VMB_a];
	i_set[VMB_cmp].trshld[0] 			= collector[Data1_Common_Uvmb_a] * K_TV;							// in rel. units
	i_set[VMB_cmp].trshld[1] 			= i_set[VMB_cmp].trshld[0];											// in rel. units
	i_set[VMB_cmp].k_retrn[0] 			= 95;																// in %
	i_set[VMB_cmp].k_retrn[1] 			= 105;																// in %
	
	// ZMT settings
	temp8 = collector[Data1_ZMT_Mode_a];
	i_set[ZMT_cmp].main_enbl 			= ((temp8 & (1<<Data1_ZMT_Mode_On_bit)) != 0);
	i_set[ZMT_cmp].add1_enbl 			= ((temp8 & (1<<Data1_ZMT_Mode_StartControl_bit)) != 0);
	temp16 = ((uint16_t)collector[Data1_ZMT_IyL_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ZMT_IyL_a+1]) * 100;
	i_set[ZMT_cmp].trshld[1] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp16 = ((uint16_t)collector[Data1_ZMT_IyU_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ZMT_IyU_a+1]) * 100;
	i_set[ZMT_cmp].trshld[2] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp33 = ((uint32_t)collector[Data1_ZMT_Klb_a]) * 1000;
	temp34 = ((uint32_t)collector[Data1_ZMT_Klb_a+1]) << 8;
	temp34 += (uint32_t)collector[Data1_ZMT_Klb_a+2];
	temp34 *= 1000;
	i_set[ZMT_cmp].k_retrn[1] 			= ((uint32_t)(temp33 + (temp34>>16)));								// in %*10
	temp33 = ((uint32_t)collector[Data1_ZMT_Kub_a]) * 1000;
	temp34 = ((uint32_t)collector[Data1_ZMT_Kub_a+1]) << 8;
	temp34 += (uint32_t)collector[Data1_ZMT_Kub_a+2];
	temp34 *= 1000;
	i_set[ZMT_cmp].k_retrn[2] 			= ((uint32_t)(temp33 + (temp34>>16)));								// in %*10
	
	// ZNR settings
	temp8 = collector[Data1_ZNR_Mode_a];
	i_set[ZNR_cmp].main_enbl 			= ((temp8 & (1<<Data1_ZNR_Mode_On_bit)) != 0);
	i_set[ZNR_cmp].add1_enbl 			= ((temp8 & (1<<Data1_ZNR_Mode_StartControl_bit)) != 0);
	i_set[ZNR_cmp].trshld[0] 			= collector[Data1_ZNR_divI_a];										// in %
	temp16 = ((uint16_t)collector[Data1_ZNR_IyL_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ZNR_IyL_a+1]) * 100;
	i_set[ZNR_cmp].trshld[1] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp33 = ((uint32_t)collector[Data1_ZNR_K_a]) * 1000;
	temp34 = ((uint32_t)collector[Data1_ZNR_K_a+1]) << 8;
	temp34 += (uint32_t)collector[Data1_ZNR_K_a+2];
	temp34 *= 1000;
	i_set[ZNR_cmp].k_retrn[0] 			= (uint32_t)(temp33 + (temp34>>16));								// in %*10
	i_set[ZNR_cmp].k_retrn[1] 			= 95;																// in %

	// ZVS settings
	i_set[ZVS_cmp].main_enbl 			= collector[Data1_PLS_Mode_a];
	temp33 = ((uint32_t)collector[Data1_PLS_CosFiC_a]) * 1000;
	temp34 = ((uint32_t)collector[Data1_PLS_CosFiC_a+1]) * 1000;
	i_set[ZVS_cmp].trshld[0] 			= (uint32_t)(temp33 + (temp34>>8));									// in %*10
	temp33 = ((uint32_t)collector[Data1_PLS_CosFiL_a]) * 1000;
	temp34 = ((uint32_t)collector[Data1_PLS_CosFiL_a+1]) * 1000;
	i_set[ZVS_cmp].trshld[1] 			= (uint32_t)(temp33 + (temp34>>8));									// in %*10
	
	// IPD settings
	i_set[IPD_cmp].add1_enbl 			= collector[Data1_ISM_BVK_a];
	temp16 = ((uint16_t)collector[Data1_ISM_IL_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ISM_IL_a+1]) * 100;
	i_set[IPD_cmp].trshld[0] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp16 = ((uint16_t)collector[Data1_ISM_IU_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ISM_IU_a+1]) * 100;
	i_set[IPD_cmp].trshld[1] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp33 = ((uint32_t)collector[Data1_ISM_Tst_a])<<16;
	temp33 += ((uint32_t)collector[Data1_ISM_Tst_a+1])<<8;
	i_set[IPD_cmp].T_set 				= temp33 + (uint32_t)collector[Data1_ISM_Tst_a+2];					// in sec.
	temp33 = ((uint32_t)collector[Data1_ISM_Tst_k_a])<<8;
	i_set[MOT_ON_cmp].T_set 			= temp33 + (uint32_t)collector[Data1_ISM_Tst_k_a+1];				// in sec.

	// ZZP&ZBR settings
	i_set[ZZP_cmp].main_enbl 			= collector[Data1_ZZPBR_Mode_a];
	temp16 = ((uint16_t)collector[Data1_ZZPBR_Ist_a]) * 100;
	temp17 = ((uint16_t)collector[Data1_ZZPBR_Ist_a+1]) * 100;
	i_set[ZZP_cmp].trshld[0] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp33 = ((uint32_t)collector[Data1_ZZPBR_Ton_a])<<16;
	temp33 += ((uint32_t)collector[Data1_ZZPBR_Ton_a+1])<<8;
	i_set[ZZP_cmp].T_set 				= temp33 + (uint32_t)collector[Data1_ZZPBR_Ton_a+2];				// in msec.
	temp33 = ((uint32_t)collector[Data1_ZZPBR_Tbloc_a])<<16;
	temp33 += ((uint32_t)collector[Data1_ZZPBR_Tbloc_a+1])<<8;
	i_set[ZBR_cmp].T_set 				= temp33 + (uint32_t)collector[Data1_ZZPBR_Tbloc_a+2];				// in msec.

	// BNN settings
	temp8 = collector[Data2_BNN1_Mode_a];
	i_set[BNN1_cmp].main_enbl 			= ((temp8 & (1<<Data2_BNN1_Mode_OnUunb_bit)) != 0);
	i_set[BNN1_cmp].add1_enbl 			= ((temp8 & (1<<Data2_BNN1_Mode_OnZS_bit)) != 0);
	i_set[BNN1_cmp].add2_enbl 			= ((temp8 & (1<<Data2_BNN1_Mode_OnIS_bit)) != 0);
	i_set[BNN1_cmp].add3_enbl 			= ((temp8 & (1<<Data2_BNN1_Mode_OnDS_bit)) != 0);
	i_set[BNN1_cmp].trshld[0] 			= collector[Data2_BNN1_Ubnn_a] * K_TV;								// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Uzs_a]) * 10;
	temp17 = ((uint16_t)collector[Data2_BNN1_Uzs_a+1]) * 10;
	i_set[BNN1_cmp].trshld[1]			= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 10;					// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Izs_a]) * 100;
	temp17 = ((uint16_t)collector[Data2_BNN1_Izs_a+1]) * 100;
	i_set[BNN1_cmp].trshld[2]			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA0) / 100;				// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Uis_a]) * 10;
	temp17 = ((uint16_t)collector[Data2_BNN1_Uis_a+1]) * 10;
	i_set[BNN1_EXT1_cmp].trshld[0]		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 10;					// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Iis_a]) * 100;
	temp17 = ((uint16_t)collector[Data2_BNN1_Iis_a+1]) * 100;
	i_set[BNN1_EXT1_cmp].trshld[1]		= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Uds_a]) * 10;
	temp17 = ((uint16_t)collector[Data2_BNN1_Uds_a+1]) * 10;
	i_set[BNN1_EXT1_cmp].trshld[2]		= (((uint32_t)(temp16 + (temp17>>8))) * K_TV) / 10;					// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Imax_a]) * 100;
	temp17 = ((uint16_t)collector[Data2_BNN1_Imax_a+1]) * 100;
	i_set[BNN1_EXT2_cmp].trshld[0]		= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	temp16 = ((uint16_t)collector[Data2_BNN1_Imin_a]) * 100;
	temp17 = ((uint16_t)collector[Data2_BNN1_Imin_a+1]) * 100;
	i_set[BNN1_EXT2_cmp].trshld[1]		= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 100;				// in rel. units
	i_set[BNN1_EXT2_cmp].trshld[2]		= (70 * K_TV);														// in rel. units
	i_set[BNN1_cmp].k_retrn[0] 			= 95;																// in %
	i_set[BNN1_cmp].k_retrn[1] 			= 95;																// in %
	i_set[BNN1_cmp].k_retrn[2] 			= 95;																// in %
	i_set[BNN1_EXT1_cmp].k_retrn[0] 	= 95;																// in %
	i_set[BNN1_EXT1_cmp].k_retrn[1] 	= 105;																// in %
	i_set[BNN1_EXT1_cmp].k_retrn[2] 	= 105;																// in %
	i_set[BNN1_EXT2_cmp].k_retrn[0] 	= 105;																// in %
	i_set[BNN1_EXT2_cmp].k_retrn[1] 	= 95;																// in %
	i_set[BNN1_EXT2_cmp].k_retrn[2] 	= 105;																// in %

	// TZP settings
	i_set[TZP_EMRG_cmp].main_enbl 		= collector[Data1_TZP_Mode_a];
	i_set[TZP_EMRG_cmp].trshld[0] 		= (uint32_t)collector[Data1_TZP_Eoff_a];							// in rel. units
	i_set[TZP_EMRG_cmp].k_retrn[0] 		= ((uint32_t)collector[Data1_TZP_Eon_a] * 100) / i_set[TZP_EMRG_cmp].trshld[0];	// in rel. units
	i_set[TZP_WARN_cmp].trshld[0] 		= (uint32_t)collector[Data1_TZP_Eal_a];								// in %
	i_set[TZP_WARN_cmp].k_retrn[0] 		= 95;																// in %
	
	// APV settings
	temp8 = collector[Data1_APV_FL_a];
	i_set[APV_cmp].main_enbl 			= ((temp8 & (1<<Data1_APV_FL_BlocI_bit)) != 0);
	temp16 = ((uint16_t)collector[Data1_APV_Ibl_a]) * 10;
	temp17 = ((uint16_t)collector[Data1_APV_Ibl_a+1]) * 10;
	i_set[APV_cmp].trshld[0] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 10;					// in rel. units
	i_set[APV_cmp].k_retrn[0] 			= 95;																// in rel. units
	
	// UROV settings
	temp8 = collector[Data1_UROV_FL_a];
	i_set[UROV_cmp].main_enbl 			= ((temp8 & (1<<Data1_UROV_FL_PuskI_bit)) != 0);
	temp16 = ((uint16_t)collector[Data1_UROV_Isrb_a]) * 10;
	temp17 = ((uint16_t)collector[Data1_UROV_Isrb_a+1]) * 10;
	i_set[UROV_cmp].trshld[0] 			= (((uint32_t)(temp16 + (temp17>>8))) * K_TA) / 10;					// in rel. units
	i_set[UROV_cmp].k_retrn[0] 			= 95;																// in rel. units
}


//--------------------------- Delaied trashold of comparators ( us) ---------------------------
void TrigShmidt4Compar	(
						uint32_t *compar, 
						uint32_t *fin_compar
						)
{
	uint32_t tmp_msk;
	static uint8_t tr_cnt[64];
	
	for(int k=0; k<2; k++)
	{
		for(int i=0; i<32; i++)
		{
			tmp_msk = (uint32_t)(1<<i);
			if(compar[k] & tmp_msk)
			{
				if((fin_compar[k] & tmp_msk) == 0)
				{
					tr_cnt[32*k+i]++;
					if(tr_cnt[32*k+i] > 1) 
						fin_compar[k] |= tmp_msk;
					else 
						fin_compar[k] &= ~tmp_msk;
				}
				else 
					fin_compar[k] |= tmp_msk;
			}
			else
			{
				tr_cnt[32*k+i] = 0;
				fin_compar[k] &= ~tmp_msk;
			}
		}	
	}
}


//--------------------- Packing comparator's states in sending array ( us) --------------------
void PackCmpr4Txd	(
					uint32_t *compar,								// array of variables that store comparator's states
					uint8_t *tx_dat									// pointer on array with transmitted data
					)
{
	uint8_t temp8[6], cmp_indx, byte_indx, bit_indx;
	uint32_t mask;
	
	comp_num_t src[40] = {	MTZ_1_cmp, 			// 0
							MTZ_2_cmp, 			// 1 
							MTZ_3_cmp, 			// 2 
							MTZ_4_cmp, 			// 3 
							KAM_1_cmp, 			// 4 
							KAM_2_cmp, 			// 5 
							KAM_3_cmp, 			// 6 
							ZNZ_1_cmp,			// 7

							ZNZ_2_cmp,			// 8
							ZNZ_3_cmp,			// 9
							OBR_1_cmp,			// 10
							OBR_2_cmp,			// 11
							DO_cmp,				// 12
							DT_cmp,				// 13
							DN_cmp,				// 14
							ZMT_cmp,			// 15

							ZNR_cmp,			// 16
							ZN_1_cmp,			// 17
							ZN_2_cmp,			// 18
							ZN_3_cmp,			// 19
							ZN_4_cmp,			// 20
							ZN_5_cmp,			// 21
							ZF_1_cmp,			// 22
							ZF_2_cmp,			// 23

							ZZP_cmp,			// 24
							ZBR_cmp,			// 25
							TZP_EMRG_cmp,		// 26
							TZP_WARN_cmp,		// 27
							UROV_cmp,			// 28
							ZVS_cmp,			// 29
							APV_cmp,			// 30
							BNN1_cmp,			// 31

							MTZ_1T_cmp, 		// 32
							MTZ_2T_cmp, 		// 33 
							MTZ_3T_cmp, 		// 34 
							MTZ_4T_cmp, 		// 35 
							MOT_ON_cmp, 		// 36 
							IPD_cmp, 			// 37 
							BNN2_cmp, 			// 38 
							LAST_cmp	};		// 39

	uint8_t dst[40] = 	{	ToCPU_Compar_B1_MTZ1_bit, 	// 0.0
							ToCPU_Compar_B1_MTZ2_bit, 	// 0.1 
							ToCPU_Compar_B1_MTZ3_bit, 	// 0.2 
							ToCPU_Compar_B1_MTZ4_bit, 	// 0.3 
							ToCPU_Compar_B1_KAM1_bit, 	// 0.4 
							ToCPU_Compar_B1_KAM2_bit, 	// 0.5 
							ToCPU_Compar_B1_KAM3_bit, 	// 0.6 
							ToCPU_Compar_B1_ZNZ1_bit, 	// 0.7
		
							ToCPU_Compar_B1_ZNZ2_bit, 	// 1.0
							ToCPU_Compar_B1_ZNZ3_bit, 	// 1.1
							ToCPU_Compar_B1_OBR1_bit, 	// 1.2
							ToCPU_Compar_B1_OBR2_bit, 	// 1.3
							ToCPU_Compar_B1_DO_bit, 	// 1.4
							ToCPU_Compar_B1_DT_bit, 	// 1.5
							ToCPU_Compar_B1_DN_bit, 	// 1.6
							ToCPU_Compar_B1_ZMT_bit, 	// 1.7
		
							ToCPU_Compar_B1_ZNR_bit, 	// 2.0
							ToCPU_Compar_B1_ZN1_bit, 	// 2.1
							ToCPU_Compar_B1_ZN2_bit, 	// 2.2
							ToCPU_Compar_B1_ZN3_bit, 	// 2.3
							ToCPU_Compar_B1_ZN4_bit, 	// 2.4
							ToCPU_Compar_B1_ZN5_bit, 	// 2.5
							ToCPU_Compar_B1_ZC1_bit, 	// 2.6
							ToCPU_Compar_B1_ZC2_bit, 	// 2.7
		
							ToCPU_Compar_B1_ZZP_bit, 	// 3.0
							ToCPU_Compar_B1_ZBR_bit, 	// 3.1
							ToCPU_Compar_B1_Overheat_bit, 		// 3.2
							ToCPU_Compar_B1_OverheatAlarm_bit, 	// 3.3
							ToCPU_Compar_B1_UROV_bit, 	// 3.4
							ToCPU_Compar_B1_PLS_bit, 	// 3.5
							ToCPU_Compar_B1_APV_bit, 	// 3.6
							ToCPU_Compar_B1_BNN1_bit, 	// 3.7
		
							ToCPU_Compar_B1_MTZ1W_bit, 	// 4.0
							ToCPU_Compar_B1_MTZ2W_bit, 	// 4.1
							ToCPU_Compar_B1_MTZ3W_bit, 	// 4.2
							ToCPU_Compar_B1_MTZ4W_bit, 	// 4.3
							ToCPU_Compar_B1_WorkM_bit, 	// 4.4
							ToCPU_Compar_B1_StartM_bit, // 4.5
							ToCPU_Compar_B1_BNN2_bit, 	// 4.6
							39	}; 						// 4.7
	
	comp_num_t 	src_b[3] = 	{VMB_cmp, UF_MIN_cmp, DECR_U_cmp};					
	uint8_t 	dst_b[3] = 	{ToCPU_Info_Bs_VMB_bit, ToCPU_Info_Bs_Ufmin_bit, ToCPU_Info_Bs_Decr_U_bit};

	// sent comparators
	for(int i=0; i<40; i++)
	{
		byte_indx = dst[i] / 8;
		bit_indx = dst[i] % 8;

		if(src[i] > 31)
		{
			mask = 1<<(src[i]-32);
			cmp_indx = 1;
		}	
		else
		{
			mask = 1<<src[i];
			cmp_indx = 0;
		}

		if(compar[cmp_indx] & mask) 
			temp8[byte_indx] |= (1 << bit_indx);
		else 
			temp8[byte_indx] &= ~(1 << bit_indx);
	}
	for(int k=0; k<5; k++)
		*(tx_dat+TX_CMPR+k) = temp8[k];

	// sent blockings
	for(int j=0; j<3; j++)
	{
		byte_indx = 5 + (dst_b[j] / 8);
		bit_indx = dst_b[j] % 8;

		if(src_b[j] > 31)
		{
			mask = 1<<(src_b[j]-32);
			cmp_indx = 1;
		}	
		else
		{
			mask = 1<<src_b[j];
			cmp_indx = 0;
		}

		if(compar[cmp_indx] & mask) 
			temp8[byte_indx] |= (1 << bit_indx);
		else 
			temp8[byte_indx] &= ~(1 << bit_indx);
	}
	*(tx_dat+TX_BLCK+0)=temp8[5];
}


//------------------- Calculation of parameters (breaking currents)(  us) ---------------------
void CalcVectBreakCur	(
						spectr_t *target_val,						// pointer on array of structures that contain datas for vectors calculated for 1st harmonics of directly measured signals
						setngs_t *coef, 							// pointer on structures that contains coeffitients
						uint32_t *break_cur,							// pointer on array that contains datas for breaking currents vectors - result
						prtct_set_t *i_set							// pointer on array of structures that contain datas for protect settings
						)
{
	uint32_t temp5, temp32;
	
	for(phases_t j=ph_A; j<=ph_C; j++)
	{
		temp5 = coef->k_t[0] * target_val[j].harm1.ef_val + coef->k_t[1] * target_val[j+3].harm1.ef_val;
		break_cur[j] = temp5/100;

		if(break_cur[j]<coef->i_t0)
			temp32 = coef->i_dt0;
		else if(break_cur[j]>=coef->i_t0 && break_cur[j]<coef->i_tlim) 
			temp32 = coef->i_dt0 + ((break_cur[j] - coef->i_t0) * coef->k_br) / 100;
		else 
			temp32 = coef->i_dt0 + ((coef->i_tlim - coef->i_t0) * coef->k_br) / 100; 
		i_set[DT_cmp].trshld[j] 		= temp32;											// in rel. units    
		i_set[DT_cmp].k_retrn[j] 		= 95;												// in %  		
		
		if(i_set[DT_cmp].trshld[j] <= coef->i_do) 
			i_set[DO_cmp].trshld[j] 	= coef->i_do;										// in rel. units  
		else 
			i_set[DO_cmp].trshld[j] 	= i_set[DT_cmp].trshld[j];							// in rel. units  
		temp32 = i_set[DT_cmp].trshld[j]*i_set[DT_cmp].k_retrn[j];
		if(temp32 <= coef->i_do * 95) 
			i_set[DO_cmp].k_retrn[j] 	= (coef->i_do * 95) / i_set[DO_cmp].trshld[j];		// in %  
		else 
			i_set[DO_cmp].k_retrn[j] 	= temp32 / i_set[DO_cmp].trshld[j];					// in %		
	}
}





