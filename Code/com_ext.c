//*********************************************************************************************
//                                        Com_ext.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "com_ext.h"

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//------------------------------ Data transmitting to CPU () ----------------------------------
uint32_t TxRxCpu(
				uint8_t *tx_data, 
				uint8_t *tx_vol,
				uint32_t *tx_vol_fact,
				uint8_t *rx_data,
				uint32_t *rx_vol_fact
				)
{
	register uint32_t cnt, i;											// nsby1 - number_send_byte, temp

	// Transmit data to CPU
	// Reset INT_ATM, RD_ATM, IN_STM, DATA_STM
	// RD_ATM - INPUT, DATA_STM - OUTPUT, IN_STM - INPUT, INT_ATM - OUTPUT
	// RD_ATM = "0", IN_STM = "1", DATA_STM = "0"
	SETUP_TXD_CTRL();
	ComDataBusAsOutput();

	if(!(TEST_PIN(IN_STM_Port, IN_STM_Pin)))
	{
		RESET_PIN(INT_ATM_Port, INT_ATM_Pin);	
		usDelay(100);
		SET_PIN(INT_ATM_Port, INT_ATM_Pin);	
		ComDataBusAsInput();			
		SETUP_TXD_CTRL();
		*tx_vol_fact = (uint32_t)(-1);
		*rx_vol_fact = (uint32_t)(-1);
		return 1;
	}
	
	RESET_PIN(INT_ATM_Port, INT_ATM_Pin);	
	cnt = 0;
	while((TEST_PIN(IN_STM_Port, IN_STM_Pin)))
	{
        if(++cnt > T_NO_MAX)
		{
			SET_PIN(INT_ATM_Port, INT_ATM_Pin);	
			ComDataBusAsInput();			
			SETUP_TXD_CTRL();
			*tx_vol_fact = (uint32_t)(-1);
			*rx_vol_fact = (uint32_t)(-1);
			return 2;
		}
	}
	if((cnt < T_NO_MIN) || !(TEST_PIN(RD_ATM_Port, RD_ATM_Pin)))							// if READ_ATM = 0 - stop transmitting 
	{
		SET_PIN(INT_ATM_Port, INT_ATM_Pin);	
		ComDataBusAsInput();
		SETUP_TXD_CTRL();
		*tx_vol_fact = (uint32_t)(-1);
		*rx_vol_fact = (uint32_t)(-1);
		return 3;
	}
	RESET_PIN(BUS_EN_Port, BUS_EN_Pin);	  													// reset BUS_EN	
	for(i = 0; i < *tx_vol; i++)
	{
		DATA_COM_Port->ODR = tx_data[i];	
		SET_PIN(DATA_STM_Port, DATA_STM_Pin); 												// set DATA_STM		
		__NOP();__NOP();__NOP();__NOP();//__NOP();__NOP();__NOP();//
		if(!(TEST_PIN(RD_ATM_Port, RD_ATM_Pin))) 											// if READ_ATM = 0 - stop transmitting 
			break;
		RESET_PIN(DATA_STM_Port, DATA_STM_Pin);												// reset DATA_STM
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
	*tx_vol_fact = i;
	SET_PIN(BUS_EN_Port, BUS_EN_Pin);
	RESET_PIN(DATA_STM_Port, DATA_STM_Pin);
	SET_PIN(INT_ATM_Port, INT_ATM_Pin);	
	ComDataBusAsInput();																	// low part of bus - INPUT	
	
//----------------------------------------------------
	// Receive data from CPU
	// Reset INT_ATM, RD_ATM, IN_STM, DATA_STM
	// RD_ATM - OUTPUT; DATA_STM - INPUT; IN_STM - INPUT; INT_ATM - OUTPUT;
	// RD_ATM = "0", IN_STM = "1", DATA_STM = "0", INT_ATM_Pin = "1"
	SETUP_RXD_CTRL();
	cnt = 0;
	while(TEST_PIN(IN_STM_Port, IN_STM_Pin))
	{
        if(++cnt > T1_RX)
		{
			SETUP_TXD_CTRL();																// Reset INT_ATM, RD_ATM, IN_STM, DATA_STM - Z_state;
			*rx_vol_fact = (uint32_t)(-1);
			return 4;
		}
	}
	RESET_PIN(BUS_EN_Port, BUS_EN_Pin);														// reset BUS_EN  	
	SET_PIN(RD_ATM_Port, RD_ATM_Pin);														// set READ_ATM
	i = 0;
	while(!(TEST_PIN(IN_STM_Port, IN_STM_Pin)) && (i < ToAI_Length))  						// While IN_STM = 0 - receive bytes  
	{			
		cnt = 0;
		while(!(TEST_PIN(DATA_STM_Port, DATA_STM_Pin)) && (++cnt < T2_RX));
		if(cnt >= T2_RX)
			break;
		rx_data[i++] = (uint8_t)(DATA_COM_Port->IDR & COM_DATABUS_MASK);
		cnt = 0;
		while(TEST_PIN(DATA_STM_Port, DATA_STM_Pin) && (++cnt < T3_RX));
		if(cnt >= T3_RX)
			break;
    }
	*rx_vol_fact = i;
    SET_PIN(BUS_EN_Port, BUS_EN_Pin);														// set BUS_EN	
	RESET_PIN(RD_ATM_Port, RD_ATM_Pin);														// reset READ_ATM
	OFF_TXRX_CTRL();	//SETUP_TXD_CTRL();																		// Reset INT_ATM, RD_ATM, IN_STM, DATA_STM - Z_state;
	return 0;
}		





