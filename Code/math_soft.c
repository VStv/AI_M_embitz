//*********************************************************************************************
//                                       Math_soft.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "math_soft.h"


//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------
//------------------------------ Table of Vector's Phase Angle --------------------------------
const uint8_t ATAN_TAB[65] = {	0,	1,	2,	3,	4,	4,	5,	6,	7,	8,	
								9,	10,	11,	11,	12,	13,	14,	15,	16,	17,	
								17,	18,	19,	20,	21,	21,	22,	23,	24,	24,	
								25,	26,	27,	27,	28,	29,	29,	30,	31,	31,	
								32,	33,	33,	34,	35,	35,	36,	36,	37,	37,	
								38,	39,	39,	40,	40,	41,	41,	42,	42,	43,	
								43,	44,	44,	45,	45	};

								
//--------------------------------- Table of Sinus 0..90 deg ----------------------------------
const int16_t SINUS_TAB[91] = {	0,		17,		35,		53,		71,		89,		107,	124,	142,	160,
								177,	195,	212,	230,	247,	265,	282,	299,	316,	333,	
								350,	366,	383,	400,	416,	432,	448,	464,	480,	496,	
								512,	527,	542,	557,	572,	587,	601,	616,	630,	644,	
								658,	671,	685,	698,	711,	724,	736,	748,	760,	772,	
								784,	795,	806,	817,	828,	838,	848,	858,	868,	877,	
								886,	895,	904,	912,	920,	928,	935,	942,	949,	955,
								962,	968,	973,	979,	984,	989,	993,	997,	1001,	1005,	
								1008,	1011,	1014,	1016,	1018,	1020,	1021,	1022,	1023,	1023,	1024	};

								
//-------------------------------- Table of Exponent 0.0...4.0 --------------------------------
const uint16_t EXP_TAB[EXP_TAB_SIZE] = {10000,	9048,	8187,	7408,	6703,	6065,	5488,	4965,	4493,	4065,	
										3678,	3328,	3011,	2725,	2465,	2231,	2018,	1826,	1652,	1495,	
										1353,	1224,	1108,	1002,	907,	820,	742,	672,	608,	550,	
										497,	450,	407,	368,	333,	301,	273,	247,	223,	202,	183	};

										
//----------------- Table of arguments for chart 2..7 values finding (band 1) -----------------
const uint32_t ARG_2_7_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	11000,	11052,	11104,	11156,	11208,	11260,	11312,	11364,	11416,	11468,	
															11520,	11572,	11624,	11676,	11728,	11780,	11832,	11884,	11936,	11988,	
															12040,	12092,	12144,	12196,	12248,	12300,	12352,	12404,	12456,	12508,	
															12560,	12612,	12664,	12716,	12768,	12820,	12872,	12924,	12976,	13028,	
															13080,	13132,	13184,	13236,	13288,	13340,	13392,	13444,	13496,	13548,	13600	};


//----------------- Table of arguments for chart 2..7 values finding (band 2) -----------------
const uint32_t ARG_2_7_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	13500,	13885,	14271,	14657,	15042,	15428,	15814,	16200,	16585,	16971,	
															17357,	17742,	18128,	18514,	18900,	19285,	19671,	20057,	20442,	20828,	
															21214,	21600,	21985,	22371,	22757,	23142,	23528,	23914,	24300,	24685,	
															25071,	25457,	25842,	26228,	26614,	27000,	27385,	27771,	28157,	28542,	
															28928,	29314,	29700,	30085,	30471,	30857,	31242,	31628,	32014,	32400,	
															32785,	33171,	33557,	33942,	34328,	34714,	35100,	35485,	35871,	36257,	
															36642,	37028,	37414,	37800,	38185,	38571,	38957,	39342,	39728,	40114,	40500	};


//----------------- Table of arguments for chart 2..7 values finding (band 3) -----------------
const uint32_t ARG_2_7_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	40000, 	47000, 	54000, 	61000, 	68000, 	75000, 	82000, 	89000, 	96000, 	103000, 110000	};


//---------------------------- Table of chart 2 values (band 1) -------------------------------
const uint32_t CHART_2_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	73374, 	69911, 	66774, 	63919, 	61310, 	58916, 	56711, 	54675, 	52787, 	51034,
															49400, 	47874, 	46445, 	45105, 	43846, 	42660, 	41541, 	40484, 	39483, 	38535,
															37635, 	36780, 	35966, 	35190, 	34450, 	33744, 	33068, 	32422, 	31803, 	31210,
															30640, 	30094, 	29568, 	29063, 	28576, 	28107, 	27656, 	27220, 	26799, 	26393,
															26000, 	25621, 	25253, 	24898, 	24553, 	24220, 	23896, 	23582, 	23278, 	22982, 	22695	};


//---------------------------- Table of chart 2 values (band 2) -------------------------------
const uint32_t CHART_2_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	23255, 	21253, 	19611, 	18238, 	17073, 	16072, 	15202, 	14440, 	13765, 	13163,
															12624, 	12138, 	11696, 	11294, 	10926, 	10588, 	10276, 	9987,  	9719,  	9470,
															9237,	9019,	8815,	8623,	8442,	8272,	8111,	7958,	7814,	7676,
															7545,	7421,	7302,	7189,	7081,	6977,	6878,	6783,	6692,	6604,	
															6520,	6438,	6360,	6285,	6212,	6142,	6074,	6009,	5946,	5884,
															5825,	5767,	5712,	5658,	5605,	5554,	5505,	5457,	5410,	5364,	
															5320,	5277,	5235,	5194,	5154,	5115,	5077,	5040,	5004,	4969,	4934	};


//---------------------------- Table of chart 2 values (band 3) -------------------------------
const uint32_t CHART_2_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	4979,	4453,	4081,	3801,	3582,	3404,	3257,	3132,	3025,	2932,	2849	};


//---------------------------- Table of chart 3 values (band 1) -------------------------------
const uint32_t CHART_3_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	134999,	128326,	122282,	116782,	111754,	107142,	102896,	98973,	95338,	91961,	
															88815,	85877,	83128,	80548,	78124,	75842,	73689,	71656,	69731,	67907,	
															66176,	64531,	62966,	61475,	60053,	58695,	57397,	56156,	54967,	53827,	
															52734,	51684,	50675,	49705,	48771,	47872,	47005,	46169,	45362,	44583,	
															43831,	43103,	42399,	41718,	41058,	40419,	39799,	39198,	38615,	38049,	37500	};


//---------------------------- Table of chart 3 values (band 2) -------------------------------
const uint32_t CHART_3_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	38571,	34742,	31605,	28987,	26770,	24868,	23218,	21774,	20498,	19364,	
															18349,	17435,	16608,	15855,	15168,	14538,	13958,	13423,	12927,	12467,	
															12038,	11637,	11263,	10912,	10582,	10271,	9978,	9702,	9440,	9192,	
															8957,	8733,	8521,	8318,	8125,	7941,	7764,	7596,	7435,	7280,	
															7132,	6989,	6852,	6721,	6594,	6472,	6355,	6241,	6132,	6026,	
															5924,	5826,	5730,	5638,	5549,	5462,	5378,	5297,	5218,	5141,	
															5067,	4994,	4924,	4856,	4789,	4725,	4662,	4600,	4541,	4482,	4426	};


//---------------------------- Table of chart 3 values (band 3) -------------------------------
const uint32_t CHART_3_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	4500,	3648,	3068,	2647,	2327,	2076,	1875,	1708,	1569,	1451,	1350	};


//---------------------------- Table of chart 4 values (band 1) -------------------------------
const uint32_t CHART_4_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	380952,	361227,	343365,	327113,	312265,	298645,	286109,	274532,	263808,	253847,	
															244570,	235910,	227807,	220209,	213072,	206353,	200018,	194036,	188376,	183015,	
															177929,	173098,	168503,	164128,	159956,	155975,	152172,	148535,	145053,	141718,	
															138519,	135449,	132501,	129666,	126940,	124315,	121787,	119349,	116999,	114730,	
															112539,	110421,	108374,	106394,	104478,	102622,	100824,	99082,	97392,	95752,	94161	};


//---------------------------- Table of chart 4 values (band 2) -------------------------------
const uint32_t CHART_4_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	97264,	86194,	77165,	69667,	63347,	57953,	53300,	49248,	45691,	42546,	
															39747,	37242,	34988,	32951,	31102,	29418,	27877,	26464,	25164,	23964,	
															22854,	21824,	20867,	19975,	19143,	18365,	17636,	16952,	16310,	15705,	
															15134,	14596,	14088,	13606,	13150,	12718,	12308,	11918,	11546,	11193,	
															10856,	10535,	10229,	9936,	9655,	9387,	9131,	8885,	8649,	8423,	
															8205,	7997,	7796,	7603,	7418,	7239,	7067,	6901,	6741,	6586,	
															6437,	6293,	6154,	6020,	5890,	5764,	5643,	5525,	5411,	5300,	5193	};


//---------------------------- Table of chart 4 values (band 3) -------------------------------
const uint32_t CHART_4_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	5333,	3793,	2840,	2209,	1768,	1447,	1207,	1022,	877,	761,	666		};


//---------------------------- Table of chart 5 values (band 1) -------------------------------
const uint32_t CHART_5_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	33333,	28630,	24772,	21577,	18909,	16663,	14759,	13135,	11740,	10536,	
															9491,	8580,	7782,	7080,	6460,	5910,	5421,	4984,	4593,	4242,	
															3926,	3640,	3382,	3147,	2934,	2739,	2561,	2399,	2250,	2112,	
															1986,	1870,	1763,	1663,	1571,	1486,	1407,	1333,	1264,	1200,	
															1140,	1084,	1032,	983,	937,	894,	854,	815,	780,	746,	714		};


//---------------------------- Table of chart 5 values (band 2) -------------------------------
const uint32_t CHART_5_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	777,	568,	427,	330,	259,	208,	169,	139,	116,	98,	
															83,		71,		62,		54,		47,		41,		36,		32,		29,		26,	
															23,		21,		19,		17,		16,		14,		13,		12,		11,		10,	
															9,		9,		8,		7,		7,		6,		6,		5,		5,		5,	
															4,		4,		4,		4,		3,		3,		3,		3,		3,		2,	
															2,		2,		2,		2,		2,		2,		2,		2,		1,		1,	
															1,		1,		1,		1,		1,		1,		1,		1,		1,		1,		1		};


//---------------------------- Table of chart 5 values (band 3) -------------------------------
const uint32_t CHART_5_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	1,		0,		0,		0,		0,		0,		0,		0,		0,		0,		0		};


//---------------------------- Table of chart 6 values (band 1) -------------------------------
const uint32_t CHART_6_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	79367,	72445,	66419,	61138,	56483,	52357,	48681,	45391,	42435,	39768,	
															37352,	35158,	33157,	31329,	29652,	28111,	26691,	25380,	24166,	23040,	
															21994,	21019,	20111,	19262,	18467,	17722,	17023,	16366,	15748,	15165,	
															14615,	14095,	13604,	13139,	12698,	12279,	11882,	11504,	11145,	10803,	
															10477,	10166,	9869,	9585,	9314,	9055,	8806,	8568,	8340,	8122,	7912	};


//---------------------------- Table of chart 6 values (band 2) -------------------------------
const uint32_t CHART_6_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	8323,	6895,	5815,	4977,	4313,	3777,	3338,	2973,	2667,	2408,	
															2185,	1993,	1826,	1680,	1551,	1437,	1335,	1245,	1163,	1089,	
															1023,	962,	907,	857,	811,	769,	730,	694,	660,	629,	
															601,	574,	549,	526,	504,	483,	464,	446,	429,	413,	
															398,	384,	371,	358,	346,	334,	324,	313,	303,	294,	
															285,	277,	269,	261,	253,	246,	240,	233,	227,	221,	
															215,	210,	204,	199,	194,	190,	185,	181,	176,	172,	169		};


//---------------------------- Table of chart 6 values (band 3) -------------------------------
const uint32_t CHART_6_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	174,	119,	87,		66,		53,		43,		36,		30,		26,		22,		19		};


//---------------------------- Table of chart 7 values (band 1) -------------------------------
const uint32_t CHART_7_B1_TAB[CHART_2_7_B1_TAB_SIZE] = { 	166666,	158037,	150222,	143112,	136615,	130657,	125172,	120107,	115416,	111058,	
															106999,	103210,	99665,	96341,	93219,	90279,	87508,	84890,	82414,	80069,	
															77844,	75730,	73720,	71806,	69981,	68239,	66575,	64984,	63461,	62001,	
															60602,	59259,	57969,	56729,	55536,	54388,	53281,	52215,	51187,	50194,	
															49235,	48309,	47414,	46547,	45709,	44897,	44110,	43348,	42609,	41891,	41195	};


//---------------------------- Table of chart 7 values (band 2) -------------------------------
const uint32_t CHART_7_B2_TAB[CHART_2_7_B2_TAB_SIZE] = { 	42553,	37710,	33759,	30479,	27714,	25354,	23319,	21546,	19990,	18614,	
															17389,	16293,	15307,	14416,	13607,	12870,	12196,	11578,	11009,	10484,	
															9998,	9548,	9129,	8739,	8375,	8035,	7716,	7416,	7135,	6871,	
															6621,	6386,	6163,	5953,	5753,	5564,	5384,	5214,	5051,	4897,	
															4749,	4609,	4475,	4347,	4224,	4107,	3994,	3887,	3784,	3685,	
															3590,	3498,	3411,	3326,	3245,	3167,	3091,	3019,	2949,	2881,	
															2816,	2753,	2692,	2633,	2577,	2522,	2468,	2417,	2367,	2319,	2272	};


//---------------------------- Table of chart 7 values (band 3) -------------------------------
const uint32_t CHART_7_B3_TAB[CHART_2_7_B3_TAB_SIZE] = { 	2333,	1659,	1242,	966,	773,	633,	528,	447,	383,	333,	291		};


//-------------------- Table of arguments for 35.5*ln(x) values finding -----------------------
const uint16_t ARG_LOG_TAB[LOG_TAB_SIZE] = 	{ 	1001,	1138,	1276,	1413,	1551,	1688,	1826,	1963,	2101,	2238,	
												2376,	2513,	2651,	2788,	2926,	3063,	3201,	3338,	3476,	3613,	
												3751,	3888,	4026,	4163,	4301,	4438,	4576,	4713,	4851,	4988,	
												5126,	5263,	5401,	5538,	5676,	5813,	5951,	6088,	6226,	6363,	6501	};

										
//---------------------------- Table of 35.5*1000*ln(x) values --------------------------------
const uint32_t LOG_TAB[LOG_TAB_SIZE] = 		{ 	35,		4589,	8652,	12272,	15580,	18585,	21375,	23943,	26355,	28598,	
												30722,	32712,	34610,	36399,	38114,	39738,	41302,	42790,	44228,	45601,	
												46931,	48205,	49443,	50631,	51789,	52902,	53989,	55036,	56061,	57049,	
												58018,	58954,	59873,	60762,	61636,	62483,	63316,	64124,	64920,	65692,	66454	};


//------------------------- Arrays of pointers on constant tables -----------------------------
const uint32_t *ARG_2_7_TAB[3] = {ARG_2_7_B1_TAB, ARG_2_7_B2_TAB, ARG_2_7_B3_TAB};
const uint32_t *CHART_2_TAB[3] = {CHART_2_B1_TAB, CHART_2_B2_TAB, CHART_2_B3_TAB};
const uint32_t *CHART_3_TAB[3] = {CHART_3_B1_TAB, CHART_3_B2_TAB, CHART_3_B3_TAB};
const uint32_t *CHART_4_TAB[3] = {CHART_4_B1_TAB, CHART_4_B2_TAB, CHART_4_B3_TAB};
const uint32_t *CHART_5_TAB[3] = {CHART_5_B1_TAB, CHART_5_B2_TAB, CHART_5_B3_TAB};
const uint32_t *CHART_6_TAB[3] = {CHART_6_B1_TAB, CHART_6_B2_TAB, CHART_6_B3_TAB};
const uint32_t *CHART_7_TAB[3] = {CHART_7_B1_TAB, CHART_7_B2_TAB, CHART_7_B3_TAB};

const uint32_t **CHART_2_7_TAB[6] = {CHART_2_TAB, CHART_3_TAB, CHART_4_TAB, CHART_5_TAB, CHART_6_TAB, CHART_7_TAB};

//const uint32_t *BAND_1_TAB[6] = {CHART_2_B1_TAB, CHART_3_B1_TAB, CHART_4_B1_TAB, CHART_5_B1_TAB, CHART_6_B1_TAB, CHART_7_B1_TAB};
//const uint32_t *BAND_2_TAB[6] = {CHART_2_B2_TAB, CHART_3_B2_TAB, CHART_4_B2_TAB, CHART_5_B2_TAB, CHART_6_B2_TAB, CHART_7_B2_TAB};
//const uint32_t *BAND_3_TAB[6] = {CHART_2_B3_TAB, CHART_3_B3_TAB, CHART_4_B3_TAB, CHART_5_B3_TAB, CHART_6_B3_TAB, CHART_7_B3_TAB};


										
//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//------------ Finding index of maximum (minimum) element of array (  us) ---------------------
uint16_t FindExtrElem	(											// result - index of max. element
						uint32_t *arr_val,							// pointer on array of values
						uint16_t arr_size,							// array size
						uint8_t min_max
						)
{
	int indx = 0;
	
	if(min_max == MINIM)
	{
		for(int i=1; i<arr_size; i++)
		{
			if(*(arr_val+i) < *(arr_val+indx)) 
				indx = i;
		}
	}
	else
	{
		for(int i=1; i<arr_size; i++)
		{
			if(*(arr_val+i) > *(arr_val+indx)) 
				indx = i;
		}
	}
	return (uint16_t)indx;
}


//---------------------------- Finding of maximum value (  us) --------------------------------
//uint32_t FindMax(
//				uint32_t *arr_val								// pointer on array of values
//				)
//{
//	uint32_t temp32;
//	
//	temp32 = *arr_val;
//	if(temp32 < *(arr_val+1)) 
//		temp32 = *(arr_val+1);
//	if(temp32 < *(arr_val+2)) 
//		temp32 = *(arr_val+2);
//	return temp32;
//}


////-------------------- Finding index of maximum element of array (  us) -----------------------
//uint16_t FindMaxElem(											// result - index of max. element
//					uint32_t *arr_val,							// pointer on array of values
//					uint16_t arr_size							// array size
//					)
//{
//	int indx;
//	
//	indx = 0;
//	for(int i=1; i<arr_size; i++)
//	{
//		if(*(arr_val+i) > *(arr_val+indx)) 
//			indx = i;
//	}
//	return (uint16_t)indx;
//}


////---------------------------- Finding of minimum value (  us) --------------------------------
//uint32_t FindMin(
//				uint32_t *arr_val								// pointer on array of values
//				)
//{
//	uint32_t temp32;
//	
//	temp32 = *arr_val;
//	if(temp32 > *(arr_val+1)) 
//		temp32 = *(arr_val+1);
//	if(temp32 > *(arr_val+2)) 
//		temp32 = *(arr_val+2);
//	return temp32;
//}


////-------------------- Finding index of minimum element of array (  us) -----------------------
//uint16_t FindMinElem(											// result - index of min. element
//					uint32_t *arr_val,							// pointer on array of values
//					uint16_t arr_size							// array size
//					)
//{
//	int indx;
//	
//	indx = 0;
//	for(int i=1; i<arr_size; i++)
//	{
//		if(*(arr_val+i) < *(arr_val+indx)) 
//			indx = i;
//	}
//	return (uint16_t)indx;
//}


//-------------------------------- Computing of Square root -----------------------------------
uint32_t SqRoot	(
				uint32_t arg
				)
{
	uint32_t rslt, temp, div;

	if(arg == 0) return 0;
	rslt = arg;
	if(arg & 0xFFFF0000)
	{
		if(arg & 0xFF000000) div = 0x00003FFF;
		else div = 0x000003FF; 
	}
	else
	{
		if(arg & 0x0000FF00) div = 0x0000003F; 
		else div = (arg > 4) ? 0x00000007 : arg;
	}
	while(1)
	{
		temp = arg/div + div; 
		div = temp >> 1; 
		div += temp & 0x00000001; 
		if(rslt > div) 
			rslt = div; 
		else 
		{
			if((arg / rslt == rslt - 1) && (arg % rslt == 0)) 
				rslt--;
			return rslt; 
		}
	}	
}
      

////----------------------------- Computing of Effective Value ----------------------------------
//void EfVal	(
//			vect_t *vect
//			)
//{ 
//	uint32_t temp;
//	int32_t temp_re, temp_im;
//	
//	temp_re = vect->re;
//	temp_im = vect->im;
//	temp = (temp_re * temp_re + temp_im * temp_im)>>1;
//	vect->ef_val = SqRoot(temp);
//}

////----------------------- Computing of Vector's Phase Angle (1 us) ----------------------------
//void PhaseAngle	(
//				vect_t *vect,
//				uint32_t Vng
//				)
//{
//    uint8_t quad;
//	uint16_t ang;
//	uint32_t temp;
//	int32_t temp_re, temp_im;
//	
//	temp_re = vect->re;
//	temp_im = vect->im;

//	// check magnitude min value
//	if(vect->ef_val < Vng) 
//	{
//		vect->phase = 0xffff;
//		return;
//	}
//	// check angles 0, 90, 180, 270
//	if(temp_re == 0)
//	{
//		if(temp_im == 0)
//		{
//			vect->phase = 0xffff; 
//			return;
//		}			
//		else if(temp_im > 0) 
//			{
//				vect->phase = 90; 
//				return;
//			}
//			else
//			{
//				vect->phase = 270; 
//				return;
//			}
//		}
//	else
//	{
//		if(temp_re > 0)
//		{
//			if(temp_im == 0)
//			{
//				vect->phase = 0; 
//				return;
//			}
//		}
//		else
//		{
//			if(temp_im == 0)
//			{
//				vect->phase = 180; 
//				return;
//			}
//		}
//	}
//	// quad defining and go to absolute value
//    if(temp_re > 0)
//    {
//        if(temp_im > 0) quad = 1;
//        else
//        {
//            quad = 4;
//            temp_im = 0 - temp_im;
//        }
//    }
//    else
//    {
//        temp_re = 0 - temp_re;
//        if(temp_im > 0) quad = 2;
//        else
//        {
//            quad = 3;
//            temp_im = 0 - temp_im;
//        }
//    }
//    // calculate tangence or cotangence, in dependence on biggest component, then - angle based on quad
//    if(temp_re >= temp_im)
//    {
//        temp = temp_im << 6;												// tangence
//        temp = temp/temp_re;
//        ang = (uint16_t)ATAN_TAB[temp];										// finding angle value using table and offset
//    }
//    else
//    {
//        temp = temp_re << 6;												// cotangence
//        temp = temp/temp_im;
//        ang = (uint16_t)ATAN_TAB[temp];										// finding angle value using table and offset	
//        ang = 90 - ang;
//    } 
//    switch(quad)
//    {
//        case 2:
//            ang = 180 - ang;
//            break;
//        case 3:
//            ang = 180 + ang;
//            break;
//        case 4:
//            ang = 360 - ang;
//            break;
//        default: 
//            ang = ang;
//            break;
//    }
//	vect->phase = ang;
//    return;
//}

//------------------------ Computing of Vector's Parameters (1 us) ----------------------------
void VectParam	(
				vect_t *vect,
				uint32_t Vng,
				par_set_t settings
				)
{
    int quad;
	uint16_t ang;
	uint32_t temp;
	int32_t temp_re, temp_im;

	if((settings == W_EF_VAL)||(settings == W_PHASE_ANG))
	{	
		temp_re = vect->re;
		temp_im = vect->im;

		// computing magnitude and effective value
		temp = (temp_re * temp_re + temp_im * temp_im)>>1;
		vect->ef_val = SqRoot(temp);

		// computing phase angle
		if(settings == W_PHASE_ANG)
		{
			// check magnitude min value
			if(vect->ef_val < Vng) 
			{
				vect->phase = 0xffff;
				return;
			}
			// check angles 0, 90, 180, 270
			if(temp_re == 0)
			{
				if(temp_im == 0)
				{
					vect->phase = 0xffff; 
					return;
				}			
				else if(temp_im > 0) 
					{
						vect->phase = 90; 
						return;
					}
					else
					{
						vect->phase = 270; 
						return;
					}
				}
			else
			{
				if(temp_re > 0)
				{
					if(temp_im == 0)
					{
						vect->phase = 0; 
						return;
					}
				}
				else
				{
					if(temp_im == 0)
					{
						vect->phase = 180; 
						return;
					}
				}
			}
			// quad defining and go to absolute value
			if(temp_re > 0)
			{
				if(temp_im > 0) quad = 1;
				else
				{
					quad = 4;
					temp_im = 0 - temp_im;
				}
			}
			else
			{
				temp_re = 0 - temp_re;
				if(temp_im > 0) quad = 2;
				else
				{
					quad = 3;
					temp_im = 0 - temp_im;
				}
			}
			// calculate tangence or cotangence, in dependence on biggest component, then - angle based on quad
			if(temp_re >= temp_im)
			{
				temp = temp_im << 6;												// tangence
				temp = temp/temp_re;
				ang = (uint16_t)ATAN_TAB[temp];										// finding angle value using table and offset
			}
			else
			{
				temp = temp_re << 6;												// cotangence
				temp = temp/temp_im;
				ang = (uint16_t)ATAN_TAB[temp];										// finding angle value using table and offset	
				ang = 90 - ang;
			} 
			switch(quad)
			{
				case 2:
					ang = 180 - ang;
					break;
				case 3:
					ang = 180 + ang;
					break;
				case 4:
					ang = 360 - ang;
					break;
				default: 
					ang = ang;
					break;
			}
			vect->phase = ang;
			return;
		}
		else
		{
			vect->phase = 0xffff;
			return;
		}
	}
	else 
	{
		vect->ef_val = 0xffffffff;
		vect->phase = 0xffff;
		return;
	}
}


//----------------------------------- Computing of sinus --------------------------------------
int16_t Sinus	(
				uint16_t ang
				)
{
	// value of angle is not correct
	if(ang == 0xffff) 
		return 0;
	
	// get angle to band 0...360deg
	while(ang >= 360) 
		ang -= 360;
	
	// for 0..90 band
	if(ang <= 90) 		
		return (int16_t)SINUS_TAB[ang];
	// for 91..180 band
	else if(ang <= 180) 
		return (int16_t)SINUS_TAB[180-ang];
	// for 181..270 band
	else if(ang <= 270) 
		return 0xffff - (int16_t)SINUS_TAB[ang-180] + 1;
	// for 271..359 band
	else  				
		return 0xffff - (int16_t)SINUS_TAB[360-ang] + 1;
}


//--------------------------------- Computing of cosinus --------------------------------------
int16_t Cosin	(
				uint16_t ang
				)
{
	// value of angle is not correct
	if(ang == 0xffff) 
		return 0;
	
	// get angle to band 0...360deg
	while(ang >= 360) 
		ang -= 360;
	
	// for 0..90 band
	if(ang <= 90) 		
		return (int16_t)SINUS_TAB[90-ang];
	// for 91..180 band
	else if(ang <= 180) 
		return 0xffff - (int16_t)SINUS_TAB[ang-90] + 1;
	// for 181..270 band
	else if(ang <= 270) 
		return 0xffff - (int16_t)SINUS_TAB[270-ang] + 1;
	// for 271..359 band
	else  				
		return (int16_t)SINUS_TAB[ang-270];
}

//--------------------------------- Quadratic interpolation -----------------------------------
int32_t QuadInterp	(
					int32_t *tab_x, 
					int32_t *tab_y, 
					int32_t band_wdth,
					uint16_t tab_size,
					int32_t arg
					)
{
	int32_t temp32_1, temp32_2;
	int64_t temp64;
	
	temp64 = ((int64_t)tab_y[1] - (int64_t)tab_y[0]) * ((int64_t)arg - (int64_t)tab_x[0]) * (tab_size - 1);
	temp32_1 = (int32_t)(temp64 / band_wdth);
	temp64 = ((int64_t)tab_y[2] - 2*((int64_t)tab_y[1]) + (int64_t)tab_y[0]) * ((int64_t)arg - (int64_t)tab_x[0]) * ((int64_t)arg - (int64_t)tab_x[1]) * (tab_size - 1) * (tab_size - 1);
	temp32_2 = (int32_t)(temp64 / band_wdth / band_wdth / 2);
	return (tab_y[0] + temp32_1 + temp32_2);
}


//---------------------- Getting of value of time-current chart 2...7 -------------------------
error_t FindValTcc2_7	(
						uint32_t arg,										// !!!!! (max(I)/Iust)*10000 !!!!!!
						tcc_t tcc_num,
						int32_t *res
						)
{
	uint32_t begin, end, width;
	int band;
	uint16_t indx, size; 
	uint32_t ppp, sss, aaa;
	uint32_t tab_func[3], tab_arg[3];
	
	// check boundary
//	if(arg < (uint32_t)ARG_2_7_B1_TAB[0])										//
//		return VALUE_IS_LESS_THEN_POSSIBLE;										//
	if(arg < (uint32_t)ARG_2_7_B1_TAB[0])	
		arg = (uint32_t)ARG_2_7_B1_TAB[0];
	if(arg >= (uint32_t)ARG_2_7_B3_TAB[CHART_2_7_B3_TAB_SIZE-2]) 
		arg = (uint32_t)ARG_2_7_B3_TAB[CHART_2_7_B3_TAB_SIZE-2] - 1;
	
	// find appropriate band 
	if(arg < (uint32_t)ARG_2_7_B2_TAB[0]) 
	{
		band = 0;
		size = CHART_2_7_B1_TAB_SIZE;
		begin = (uint32_t)ARG_2_7_B1_TAB[0];
		end = (uint32_t)ARG_2_7_B1_TAB[size-2];	
	}
	else if(arg < (uint32_t)ARG_2_7_B3_TAB[0]) 
	{
		band = 1;
		size = CHART_2_7_B2_TAB_SIZE;
		begin = (uint32_t)ARG_2_7_B2_TAB[0];
		end = (uint32_t)ARG_2_7_B2_TAB[size-2];	
	}
	else 
	{
		band = 2;
		size = CHART_2_7_B3_TAB_SIZE;
		begin = (uint32_t)ARG_2_7_B3_TAB[0];
		end = (uint32_t)ARG_2_7_B3_TAB[size-2];	
	}

	// find index
	width = end - begin;
	ppp = (arg - begin) * (size-2);
	indx = (uint16_t)(ppp / width);

	// find adress of appropriate band in argument table
	aaa = *((uint32_t *)ARG_2_7_TAB + band);
	
	// find adress of appropriate band in appropriate chart
	sss = *((uint32_t *)CHART_2_7_TAB + (tcc_num - TCC_2));
	ppp = *((uint32_t *)sss + band);

	for(int i=0; i<3; i++)
	{
		// find appropriate argument datas
		tab_arg[i] = *((uint32_t *)aaa + indx + i);

		// find appropriate datas in chart
		tab_func[i] = *((uint32_t *)ppp + indx + i);
	}

	*res = QuadInterp((int32_t *)tab_arg, (int32_t *)tab_func, width, size-1, (int32_t)arg);
	return RES_OK;
}


//--------------------- Finding of 35.5*ln(x) (1.001...6.501) for TTC 8 -----------------------
error_t FindLn 	(
				uint16_t arg,
				int32_t *res
				)
{
	uint16_t begin, end, indx, temp16;
	uint32_t width, temp32;
	int32_t tab_func[3], tab_arg[3];
	
	// check boundary
	begin = (uint16_t)ARG_LOG_TAB[0];
	end = (uint16_t)ARG_LOG_TAB[LOG_TAB_SIZE-2];
	if(arg < begin)	
		return VALUE_IS_LESS_THEN_POSSIBLE;
	else if(arg >= end) 
		return VALUE_IS_GREATER_THEN_POSSIBLE;
	else
	{
		width = (uint32_t)(end - begin);
		temp32 = (((uint32_t)arg) - ((uint32_t)begin)) * (LOG_TAB_SIZE-2);
		indx = (uint16_t)(temp32 / width);
		for(int i=0; i<3; i++)
		{
			temp16 = (uint16_t)ARG_LOG_TAB[indx+i];
			tab_arg[i] = (int32_t)temp16;
			tab_func[i] = (int32_t)((uint32_t)LOG_TAB[indx+i]);
		}
		temp32 = (int32_t)arg;
		*res = QuadInterp(tab_arg, tab_func, width, LOG_TAB_SIZE-1, temp32);
		return RES_OK;
	}
}


//------------------------------------ Finding of exp(-x) -------------------------------------
error_t FindExp	(
				uint16_t arg,
				uint16_t *res
				)
{
	// check boundary
	if(arg >= EXP_TAB_SIZE) return VALUE_IS_GREATER_THEN_POSSIBLE;
	else
	{
		*res = (uint16_t)EXP_TAB[arg];
		return RES_OK;
	}
}


