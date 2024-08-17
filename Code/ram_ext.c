//*********************************************************************************************
//                                        Ram_ext.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "ram_ext.h"

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//-------------------------- Read byte from external RAM (11us) -------------------------------
void ReadByteFromRam(
					uint32_t AdrRAM,		// start adress in SRAM where data reads from 
					uint8_t *pData8			// pointer on variable in MCU RAM where data reads to
					)
{
//	uint32_t adress = AdrRAM;
											// Set Bus for adress output
	RamAdrBusAsOutput();
											// Set adress on the Bus
	TxWordByBus((uint16_t)AdrRAM);
	SEL_ADR_LOW();
	TxWordByBus((uint16_t)(AdrRAM>>16));
	SEL_ADR_HIGH();
											// Set Bus for data input
	RamDataBusAsInput();
											// Set control signals (CS_SRAM = 1, RD_RAM = 0)
	SET_PIN(CS_RAM_Port, CS_RAM_Pin);
	RESET_PIN(RD_RAM_Port, RD_RAM_Pin);
	__ASM("NOP");__ASM("NOP");//__ASM("NOP");	
											// Receive data from RAM
	*pData8 = RxByteByBus();
											// Return control signals (RD_RAM = 1, CS_SRAM = 0)
	SET_PIN(RD_RAM_Port, RD_RAM_Pin);
	RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
											// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}

//--------------------------- Write byte from external RAM (11us) -----------------------------
void WriteByteToRam	(
					uint32_t AdrRAM, 		// start adress in SRAM where data writes to 
					uint8_t *pData8			// pointer on variable in MCU RAM where data writes from
					)
{
//	uint32_t adress = AdrRAM;
											// Set Bus for adress output
	RamAdrBusAsOutput();
											// Set adress on the Bus
	TxWordByBus((uint16_t)AdrRAM);
	SEL_ADR_LOW();
	TxWordByBus((uint16_t)(AdrRAM>>16));
	SEL_ADR_HIGH();
											// Set Bus for data output
	RamDataBusAsOutput();
											// Set control signals (CS_SRAM = 1, WR_RAM = 0)
	SET_PIN(CS_RAM_Port, CS_RAM_Pin);
	RESET_PIN(WR_RAM_Port, WR_RAM_Pin);
	__ASM("NOP");__ASM("NOP");//__ASM("NOP");	
											// Transmit data to RAM
	 TxByteByBus(*pData8);
											// Return control signals (WR_RAM = 1, CS_SRAM = 0)
	SET_PIN(WR_RAM_Port, WR_RAM_Pin);
	RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
											// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}

//-------------------------- Read int word from external RAM (30us) ---------------------------
void ReadWordFromRam(
					uint32_t AdrRAM,			// start adress in SRAM where data reads from 
					uint32_t *pData32			// pointer on variable in MCU RAM where data reads to
					)
{
	uint8_t *pData8;
	pData8 = (uint8_t *)pData32;
	uint32_t adress = AdrRAM;

	for(uint32_t i=0; i<4; i++)
	{
												// Set Bus for adress output
		RamAdrBusAsOutput();
												// Set adress on the Bus
		TxWordByBus((uint16_t)adress);
		SEL_ADR_LOW();
		TxWordByBus((uint16_t)(adress>>16));
		SEL_ADR_HIGH();
												// Set Bus for data input
		RamDataBusAsInput();
												// Set control signals (CS_SRAM = 1, RD_RAM = 0)
		SET_PIN(CS_RAM_Port, CS_RAM_Pin);
		RESET_PIN(RD_RAM_Port, RD_RAM_Pin);
		__ASM("NOP");__ASM("NOP");//__ASM("NOP");	 
												// Receive data from RAM
		*pData8++ = RxByteByBus();
												// Return control signals (RD_RAM = 1, CS_SRAM = 0)
		SET_PIN(RD_RAM_Port, RD_RAM_Pin);
		RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
		adress++;
	}
												// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}

//------------------------- Write int word to external RAM (31us) -----------------------------
void WriteWordToRam	(
					uint32_t AdrRAM, 			// start adress in SRAM where data writes to 
					uint32_t *pData32			// pointer on variable in MCU RAM where data writes from
					)
{
	uint8_t *pData8;
	pData8 = (uint8_t *)pData32;
	uint32_t adress = AdrRAM;

	for(uint32_t i=0; i<4; i++)
	{
												// Set Bus for adress output
		RamAdrBusAsOutput();
												// Set adress on the Bus
		TxWordByBus((uint16_t)adress);
		SEL_ADR_LOW();
		TxWordByBus((uint16_t)(adress>>16));
		SEL_ADR_HIGH();
												// Set Bus for data output
		RamDataBusAsOutput();
												// Set control signals (CS_SRAM = 1, RD_RAM = 0)
		SET_PIN(CS_RAM_Port, CS_RAM_Pin);
		RESET_PIN(WR_RAM_Port, WR_RAM_Pin);
		__ASM("NOP");__ASM("NOP");//__ASM("NOP");	 
												// Transmit data to RAM
		TxByteByBus(*pData8++);
												// Return control signals (WR_RAM = 1, CS_SRAM = 0)
		SET_PIN(WR_RAM_Port, WR_RAM_Pin);
		RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
		adress++;
	}
												// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}

//---------------- Read byte array from external RAM (1B - 11us, 50B - 324us) -----------------
void ReadArrayFromRam	(
						uint32_t AdrRAM,		// start adress in SRAM where data reads from
						uint8_t *pData8,		// pointer on array in MCU RAM where data reads to
						uint32_t cnt			// amount of data that writes
						)
{
	uint32_t adress = AdrRAM;

	for(uint32_t i=0; i<cnt; i++)
	{
												// Set Bus for adress output
		RamAdrBusAsOutput();
												// Set adress on the Bus
		TxWordByBus((uint16_t)adress);
		SEL_ADR_LOW();
		TxWordByBus((uint16_t)(adress>>16));
		SEL_ADR_HIGH();
												// Set Bus for data input
		RamDataBusAsInput();
												// Set control signals (CS_SRAM = 1, RD_RAM = 0)
		SET_PIN(CS_RAM_Port, CS_RAM_Pin);
		RESET_PIN(RD_RAM_Port, RD_RAM_Pin);
		__ASM("NOP");__ASM("NOP");//__ASM("NOP");	
												// Receive data from RAM
		*pData8++ = RxByteByBus();
												// Return control signals (RD_RAM = 1, CS_SRAM = 0)
		SET_PIN(RD_RAM_Port, RD_RAM_Pin);
		RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
		adress++;
	}
												// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}


//----------------- Write byte array to external RAM (1B - 11us, 50B - 331us) -----------------
void WriteArrayToRam(
					uint32_t AdrRAM,			// start adress in SRAM where data writes to 
					uint8_t *pData8,			// pointer on array in MCU RAM where data writes from
					uint32_t cnt				// amount of data bytes that writes
					)
{
	uint32_t adress = AdrRAM;

	for(uint32_t i=0; i<cnt; i++)
	{
												// Set Bus for adress output
		RamAdrBusAsOutput();
												// Set adress on the Bus
		TxWordByBus((uint16_t)adress);
		SEL_ADR_LOW();
		TxWordByBus((uint16_t)(adress>>16));
		SEL_ADR_HIGH();
												// Set Bus for data output
		RamDataBusAsOutput();
												// Set control signals (CS_SRAM = 1, RD_RAM = 0)
		SET_PIN(CS_RAM_Port, CS_RAM_Pin);
		RESET_PIN(WR_RAM_Port, WR_RAM_Pin);
		__ASM("NOP");__ASM("NOP");//__ASM("NOP");	 
												// Transmit data to RAM
		TxByteByBus(*pData8++);
												// Return control signals (WR_RAM = 1, CS_SRAM = 0)
		SET_PIN(WR_RAM_Port, WR_RAM_Pin);
		RESET_PIN(CS_RAM_Port, CS_RAM_Pin);
		adress++;
	}
												// Return Bus and control lines
	RESET_RAM_CTRL();
	RESET_BUS();
}




