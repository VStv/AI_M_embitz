//*********************************************************************************************
//                                        Selfprog.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "selfprog.h"


//---------------------------------------------------------------------------------------------
//                                    Tables of Constants
//---------------------------------------------------------------------------------------------
//--------------------------------- Table for CRC founding ------------------------------------
const uint16_t CRC16Table[]=
{
	0x0000, 0xC1C0, 0x81C1, 0x4001, 0x01C3, 0xC003, 0x8002, 0x41C2,
	0x01C6, 0xC006, 0x8007, 0x41C7, 0x0005, 0xC1C5, 0x81C4, 0x4004,
	0x01CC, 0xC00C, 0x800D, 0x41CD, 0x000F, 0xC1CF, 0x81CE, 0x400E,
	0x000A, 0xC1CA, 0x81CB, 0x400B, 0x01C9, 0xC009, 0x8008, 0x41C8,
	0x01D8, 0xC018, 0x8019, 0x41D9, 0x001B, 0xC1DB, 0x81DA, 0x401A,
	0x001E, 0xC1DE, 0x81DF, 0x401F, 0x01DD, 0xC01D, 0x801C, 0x41DC,
	0x0014, 0xC1D4, 0x81D5, 0x4015, 0x01D7, 0xC017, 0x8016, 0x41D6,
	0x01D2, 0xC012, 0x8013, 0x41D3, 0x0011, 0xC1D1, 0x81D0, 0x4010,
	0x01F0, 0xC030, 0x8031, 0x41F1, 0x0033, 0xC1F3, 0x81F2, 0x4032,
	0x0036, 0xC1F6, 0x81F7, 0x4037, 0x01F5, 0xC035, 0x8034, 0x41F4,
	0x003C, 0xC1FC, 0x81FD, 0x403D, 0x01FF, 0xC03F, 0x803E, 0x41FE,
	0x01FA, 0xC03A, 0x803B, 0x41FB, 0x0039, 0xC1F9, 0x81F8, 0x4038,
	0x0028, 0xC1E8, 0x81E9, 0x4029, 0x01EB, 0xC02B, 0x802A, 0x41EA,
	0x01EE, 0xC02E, 0x802F, 0x41EF, 0x002D, 0xC1ED, 0x81EC, 0x402C,
	0x01E4, 0xC024, 0x8025, 0x41E5, 0x0027, 0xC1E7, 0x81E6, 0x4026,
	0x0022, 0xC1E2, 0x81E3, 0x4023, 0x01E1, 0xC021, 0x8020, 0x41E0,
	0x01A0, 0xC060, 0x8061, 0x41A1, 0x0063, 0xC1A3, 0x81A2, 0x4062,
	0x0066, 0xC1A6, 0x81A7, 0x4067, 0x01A5, 0xC065, 0x8064, 0x41A4,
	0x006C, 0xC1AC, 0x81AD, 0x406D, 0x01AF, 0xC06F, 0x806E, 0x41AE,
	0x01AA, 0xC06A, 0x806B, 0x41AB, 0x0069, 0xC1A9, 0x81A8, 0x4068,
	0x0078, 0xC1B8, 0x81B9, 0x4079, 0x01BB, 0xC07B, 0x807A, 0x41BA,
	0x01BE, 0xC07E, 0x807F, 0x41BF, 0x007D, 0xC1BD, 0x81BC, 0x407C,
	0x01B4, 0xC074, 0x8075, 0x41B5, 0x0077, 0xC1B7, 0x81B6, 0x4076,
	0x0072, 0xC1B2, 0x81B3, 0x4073, 0x01B1, 0xC071, 0x8070, 0x41B0,
	0x0050, 0xC190, 0x8191, 0x4051, 0x0193, 0xC053, 0x8052, 0x4192,
	0x0196, 0xC056, 0x8057, 0x4197, 0x0055, 0xC195, 0x8194, 0x4054,
	0x019C, 0xC05C, 0x805D, 0x419D, 0x005F, 0xC19F, 0x819E, 0x405E,
	0x005A, 0xC19A, 0x819B, 0x405B, 0x0199, 0xC059, 0x8058, 0x4198,
	0x0188, 0xC048, 0x8049, 0x4189, 0x004B, 0xC18B, 0x818A, 0x404A,
	0x004E, 0xC18E, 0x818F, 0x404F, 0x018D, 0xC04D, 0x804C, 0x418C,
	0x0044, 0xC184, 0x8185, 0x4045, 0x0187, 0xC047, 0x8046, 0x4186,
	0x0182, 0xC042, 0x8043, 0x4183, 0x0041, 0xC181, 0x8180, 0x4040 
};


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//--------------------------------- CRC founding (  us) ---------------------------------------
uint16_t CalcCRC16	(
					uint8_t *Buff,
					uint32_t len,
					uint16_t initCRC
					)
{
	register uint16_t j, crc;
	
	crc = initCRC;
	for (j = 0; j < len; j++) 
		crc = ((crc << 8) ^ CRC16Table[(crc >> 8) ^ Buff[j]]);
	return crc;
}
	


//--------------------------------- CPU command processing -------------------------------------
uint8_t CommandProcessFw(																		// 0- OK, 1- wrong block number, 2- wrong cntrSum, 3- empty or wrong command, 4- wrong ID
						uint32_t recv_amnt,
						uint8_t *rx_data,
						firmw_upd_t	*fw_ctrl
						)
{
	volatile uint8_t cntrSum = 0, state = 0; 

	switch(rx_data[RX_COMAND + fw_ctrl->ai_type_shft])
	{
		case 0xc0:
		// Command - jump to receive firmware mode, data - no
			INIT_FIRMW_UPDATE((*fw_ctrl));
			break;
		
		case 0xc1:
		// Command - receive firmware, data - firmware bytes
			if(rx_data[RX_FRMW_STT + fw_ctrl->ai_type_shft] != 0 && rx_data[RX_FRMW_STT + fw_ctrl->ai_type_shft] != 1)	// received ID is wrong, repeat request
				return 4;

			for(volatile int n1=(RX_COMAND + fw_ctrl->ai_type_shft); n1<recv_amnt; n1++) 								// check sum
				cntrSum ^= rx_data[n1];
			if(cntrSum)
				return 2;																								// cntrSum is wrong

			if(rx_data[RX_FRMW_STT + fw_ctrl->ai_type_shft] == 0)														// ID == 0
			{
				fw_ctrl->blk_amount = (((uint16_t)rx_data[RX_FRMW_BLK_H + fw_ctrl->ai_type_shft])<<8) | ((uint16_t)rx_data[RX_FRMW_BLK_L + fw_ctrl->ai_type_shft]);
				fw_ctrl->full_crc = (((uint16_t)rx_data[RX_FRMW_CRC_H + fw_ctrl->ai_type_shft])<<8) | ((uint16_t)rx_data[RX_FRMW_CRC_L + fw_ctrl->ai_type_shft]);
				fw_ctrl->fw_size = 	(((uint32_t)rx_data[RX_FRMW_LNG_3 + fw_ctrl->ai_type_shft])<<24) | 
									(((uint32_t)rx_data[RX_FRMW_LNG_2 + fw_ctrl->ai_type_shft])<<16) | 
									(((uint32_t)rx_data[RX_FRMW_LNG_1 + fw_ctrl->ai_type_shft])<<8) | 
									((uint32_t)rx_data[RX_FRMW_LNG_0 + fw_ctrl->ai_type_shft]);
				fw_ctrl->cur_sram_adr = ADR_FIRMW_STRG;
				fw_ctrl->cur_blk_num = 0;
				fw_ctrl->wr_mark_flag = 0;
				fw_ctrl->err = 0;
				fw_ctrl->cur_crc = 0xffff;
				fw_ctrl->cntr_crc = 0xffff;
				WriteByteToRam(ADR_FIRMW_LENGTH, rx_data+RX_FRMW_LNG_3 + fw_ctrl->ai_type_shft);
				WriteByteToRam(ADR_FIRMW_LENGTH+1, rx_data+RX_FRMW_LNG_2 + fw_ctrl->ai_type_shft);
				WriteByteToRam(ADR_FIRMW_LENGTH+2, rx_data+RX_FRMW_LNG_1 + fw_ctrl->ai_type_shft);
				WriteByteToRam(ADR_FIRMW_LENGTH+3, rx_data+RX_FRMW_LNG_0 + fw_ctrl->ai_type_shft);
				WriteByteToRam(ADR_FIRMW_CRC, rx_data+RX_FRMW_CRC_H + fw_ctrl->ai_type_shft);
				WriteByteToRam(ADR_FIRMW_CRC+1, rx_data+RX_FRMW_CRC_L + fw_ctrl->ai_type_shft);
			}
			else 																										// ID == 1
			{
				if(fw_ctrl->cur_blk_num == ((((uint16_t)rx_data[RX_FRMW_CURBLK_H + fw_ctrl->ai_type_shft])<<8) | ((uint16_t)rx_data[RX_FRMW_CURBLK_L + fw_ctrl->ai_type_shft])))
				{
					for(volatile int i=RX_FRMW_DAT + fw_ctrl->ai_type_shft; i<(recv_amnt-1); i++)
						fw_ctrl->wr_buf[i-(RX_FRMW_DAT + fw_ctrl->ai_type_shft)] = rx_data[i];							// from receive buffer to write buffer
				}
				else
					return 1;																							// received block number is wrong
			}
			break;
		
		case 0xa0:
		default:
		// nothing to do
			return 3;
	}
	return state;
}


//------------------- Processing firmware receive & saving in SRAM (  us) ---------------------
void FirmwUpdate(
				uint32_t *rx_amnt,
				uint8_t *rx_data,
				uint32_t *tx_amnt,
				uint8_t *tx_data,
				firmw_upd_t	*fw_ctrl
				)
{
	static uint8_t fw_status;
	uint16_t Buf[IN_FW_UPD_SAVE_AREA_VOL/2];
	uint8_t rd_err;
	uint8_t temp8;
//	uint32_t res;

	switch(fw_ctrl->upd_stage)
	{
		case CMND_C0:
			switch(fw_ctrl->step)
			{
				case 0:
					fw_ctrl->step = 1;
					break;

				case 1:
					fw_ctrl->step = 2;
					break;

				case 2:
					// Forms tx buffer
					tx_data[TX_BUF_START] = 0x02;
					tx_data[TX_BUF_START+1] = 3;
					tx_data[TX_BUF_START+2] = tx_data[0] ^ tx_data[1];

					// Clear rx buffer
					for(volatile int i=0; i<(RX_BUF_SIZE+4); i++)
						rx_data[i] = 0;
					fw_ctrl->step = 3;
					break;

				case 3:
					// Transmit content of tx buffer & receive data in rx buffer
					__disable_irq();
					/*res =*/ TxRxCpu(tx_data, &tx_data[TX_BUF_START+1], tx_amnt, rx_data, rx_amnt);
					__enable_irq();
					fw_ctrl->step = 4;
					break;

				case 4:
					fw_ctrl->ai_type_shft = SearchAiType(rx_data);
					fw_status = CommandProcessFw(*rx_amnt, rx_data, fw_ctrl);
					fw_ctrl->step = 5;
					break;

				case 5:
					if(!fw_status && rx_data[RX_COMAND + fw_ctrl->ai_type_shft]==0xc1 && rx_data[RX_FRMW_STT + fw_ctrl->ai_type_shft]==0)
						fw_ctrl->upd_stage = CMND_C1;
					if(fw_ctrl->fw_size > MAX_FRMW_SIZE)
					{
						fw_ctrl->upd_stage = FINALIZE;
						fw_ctrl->err = 0xff;
					}
					fw_ctrl->step = 0;
					break;

				default:
					fw_ctrl->step = 1;
					break;
			}
			break;

		case CMND_C1:
			switch(fw_ctrl->step)
			{
				case 0:
					fw_ctrl->step = 1;
					break;

				case 1:
					fw_ctrl->step = 2;
					break;

				case 2:
					// Forms tx buffer
					tx_data[TX_BUF_START] = 0x03;
					tx_data[TX_BUF_START+1] = 5;
					tx_data[TX_FRMW_CURBLK_H] = (uint8_t)((fw_ctrl->cur_blk_num)>>8);
					tx_data[TX_FRMW_CURBLK_L] = (uint8_t)fw_ctrl->cur_blk_num;
					tx_data[TX_FRMW_CURBLK_H+2] = tx_data[0] ^ tx_data[1] ^ tx_data[2] ^ tx_data[3];

					// Clear rx buffer
					for(volatile int i=0; i<(RX_BUF_SIZE + 4); i++)
						rx_data[i] = 0;
					fw_ctrl->step = 3;
					break;

				case 3:
					// Transmit content of tx buffer & receive data in rx buffer
					__disable_irq();
					/*res =*/ TxRxCpu(tx_data, &tx_data[TX_BUF_START+1], tx_amnt, rx_data, rx_amnt);
					__enable_irq();
					fw_ctrl->step = 4;
					break;

				case 4:
					fw_status = CommandProcessFw(*rx_amnt, rx_data, fw_ctrl);								// if command & block # are OK, block send to wr_buf
					fw_ctrl->step = 5;
					break;

				case 5:
					if(!fw_status && rx_data[RX_COMAND + (fw_ctrl->ai_type_shft)]==0xc1 && rx_data[RX_FRMW_STT + fw_ctrl->ai_type_shft]==1)		// if data block is in wr_buf, write it to SRAM
					{
						WriteArrayToRam(fw_ctrl->cur_sram_adr, fw_ctrl->wr_buf,	*rx_amnt - (FRMW_SERV_DAT + fw_ctrl->ai_type_shft));
						fw_ctrl->step = 6;
					}
					else
						fw_ctrl->step = 0;
					break;

				case 6:
					ReadArrayFromRam(fw_ctrl->cur_sram_adr, fw_ctrl->rd_buf, *rx_amnt - (FRMW_SERV_DAT + fw_ctrl->ai_type_shft));				// read data block from SRAM
					rd_err = 0;
					for(volatile int i=0; i<(*rx_amnt - (FRMW_SERV_DAT + fw_ctrl->ai_type_shft)); i++)											// compare data
					{
						if(fw_ctrl->rd_buf[i]!= fw_ctrl->wr_buf[i])
							rd_err++;
					}
					if(!rd_err)																													// if data are right
					{
						fw_ctrl->cur_crc = CalcCRC16(fw_ctrl->wr_buf, (*rx_amnt - (FRMW_SERV_DAT + fw_ctrl->ai_type_shft)), fw_ctrl->cur_crc); 	// update current CRC16
						fw_ctrl->cur_sram_adr += (*rx_amnt - (FRMW_SERV_DAT + fw_ctrl->ai_type_shft));											// increase SRAM address for next data block
						(fw_ctrl->cur_blk_num)++;															// next data block #
						if(fw_ctrl->cur_blk_num >= fw_ctrl->blk_amount)										// if last data block processed
						{
							if(fw_ctrl->cur_crc != fw_ctrl->full_crc)										// check CRC16
								fw_ctrl->err |= 0x02;														// mark write error, if CRC16 is wrong
							fw_ctrl->debug_field = fw_ctrl->cur_sram_adr - ADR_FIRMW_STRG;
							INIT_FIRMW_CHECK((*fw_ctrl));													// go to firmware check
						}
						else
							fw_ctrl->step = 1;																// if it's not last block
					}
					else
						fw_ctrl->step = 1;
					break;

				default:
					fw_ctrl->step = 1;
					break;
			}
			break;

		case CHECK_FW_IN_SRAM:
			if(fw_ctrl->step != 2)
			{
				if(fw_ctrl->fw_size <= 0)
				{
					if(fw_ctrl->cntr_crc != fw_ctrl->full_crc)												// compare with full CRC16
						fw_ctrl->err |= 0x04;																// mark write error, if not equal
					if(fw_ctrl->cntr_crc != fw_ctrl->cur_crc)												// compare with current CRC16
						fw_ctrl->err |= 0x08;																// mark write error, if not equal
					FIN_FIRMW_UPDATE((*fw_ctrl));															// go to firmware check
					break;
				}
				if(fw_ctrl->fw_size >= 128)																	// read data block from SRAM
					temp8 = 128;
				else
					temp8 = fw_ctrl->fw_size;
				ReadArrayFromRam(fw_ctrl->cur_sram_adr, fw_ctrl->rd_buf, temp8);
				fw_ctrl->cntr_crc = CalcCRC16(fw_ctrl->rd_buf, temp8, fw_ctrl->cntr_crc);
				fw_ctrl->fw_size -= temp8;
				fw_ctrl->cur_sram_adr += temp8;
			}
			switch(fw_ctrl->step)
			{
				case 0:
					fw_ctrl->step = 1;
					break;

				case 1:
					// Forms tx buffer
					tx_data[TX_BUF_START] = 0x03;
					tx_data[TX_BUF_START+1] = 5;
					tx_data[TX_FRMW_CURBLK_H] = (uint8_t)((fw_ctrl->blk_amount - 1)>>8);
					tx_data[TX_FRMW_CURBLK_L] = (uint8_t)(fw_ctrl->blk_amount - 1);
					tx_data[TX_FRMW_CURBLK_H+2] = tx_data[0] ^ tx_data[1] ^ tx_data[2] ^ tx_data[3];
					fw_ctrl->step = 2;
					break;

				case 2:
					// Transmit content of tx buffer & receive data in rx buffer
					__disable_irq();
					/*res =*/ TxRxCpu(tx_data, &tx_data[TX_BUF_START+1], tx_amnt, rx_data, rx_amnt);
					__enable_irq();
					fw_ctrl->step = 3;
					break;

				case 3:
					fw_ctrl->step = 4;
					break;

				case 4:
					fw_ctrl->step = 5;
					break;

				case 5:
					fw_ctrl->step = 0;
					break;

				default:
					fw_ctrl->step = 0;
					break;
			}
			break;

		case FINALIZE:
			switch(fw_ctrl->step)
			{
				case 0:
					if(fw_ctrl->wr_mark_flag == 0x0f)
					{
						ReadBufFlash(ADR_FMWR_MARKS_PAGE_FLASH, Buf, IN_FW_UPD_SAVE_AREA_VOL/2);
						Buf[(ADR_FMWR_RECEIVED_MARK - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)FMWR_RECEIVED;
						Buf[(ADR_FMWR_LOADED_MARK - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)(-1);
						Buf[(ADR_FRMW_FULL_CRC - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->full_crc;
						Buf[(ADR_FRMW_CUR_CRC - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->cur_crc;
						Buf[(ADR_FRMW_CNTR_CRC - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->cntr_crc;
						Buf[(ADR_FRMW_LAST_CRC - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)(-1);
						Buf[(ADR_FRMW_LEN_BLCK - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->cur_blk_num;
						Buf[(ADR_FRMW_ERROR - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->err;
						Buf[(ADR_FRMW_LEN_BYTE - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)fw_ctrl->debug_field;
						Buf[(ADR_FRMW_LEN_BYTE + 2 - ADR_FMWR_MARKS_PAGE_FLASH)/2] = (uint16_t)((fw_ctrl->debug_field)>>16);
						STOP_SYSTICK();
						FlashUnLock();
						FlashErasePage(ADR_FMWR_MARKS_PAGE_FLASH);
						FlashWritePage(ADR_FMWR_MARKS_PAGE_FLASH, Buf, IN_FW_UPD_SAVE_AREA_VOL/2);
						FlashLock();
						START_SYSTICK();
						fw_ctrl->wr_mark_flag = 0;
					}
					fw_ctrl->step = 1;
					break;

				case 1:
					// Forms tx buffer
					tx_data[TX_BUF_START] = 0x01;
					tx_data[TX_BUF_START+1] = 4;
					tx_data[TX_FRMW_ERR] = (uint8_t)fw_ctrl->err;
					tx_data[TX_FRMW_ERR+1] = tx_data[0] ^ tx_data[1] ^ tx_data[2];

					// Clear rx buffer
					for(volatile int i=0; i<RX_BUF_SIZE+4; i++)
						rx_data[i] = 0;

					fw_ctrl->step = 2;
					break;

				case 2:
					// Transmit content of tx buffer & receive data in rx buffer
					__disable_irq();
					/*res =*/ TxRxCpu(tx_data, &tx_data[TX_BUF_START+1], tx_amnt, rx_data, rx_amnt);
					__enable_irq();
					fw_ctrl->step = 3;
					break;

				case 3:
					fw_status = CommandProcessFw(*rx_amnt, rx_data, fw_ctrl);						
					fw_ctrl->step = 4;
					break;

				case 4:
					fw_ctrl->step = 5;
					break;

				case 5:
				default:
					fw_ctrl->step = 0;
					break;
			}
			break;

		default:																							// A0 & other
			break;
	}
}




//------------------- AI searching to define data receiving protocol (  us) -------------------
uint8_t SearchAiType(
					uint8_t *rx_data
					)
{
	if(rx_data[RX_COMAND + 4] == 0xC1)
		return 4;
	else
		return 0;
}

