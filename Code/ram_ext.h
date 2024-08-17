//*********************************************************************************************
//                                        Ram_ext.h
//*********************************************************************************************

#ifndef __RAM_EXT__
#define __RAM_EXT__

//---------------------------------------------------------------------------------------------
//                                     Include section
//---------------------------------------------------------------------------------------------
#include "stm32F10x.h"
#include "gpio_control.h"

//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define SEL_ADR_LOW()	CLK2_RAM_Port->BSRR = (uint32_t)(1U<<(CLK2_RAM_Pin+16)); 	\
						CLK1_RAM_Port->BSRR = (uint32_t)(1U<<CLK1_RAM_Pin);		\
						__ASM("NOP");												\
						CLK1_RAM_Port->BSRR = (uint32_t)(1U<<(CLK1_RAM_Pin+16))

#define SEL_ADR_HIGH()	CLK1_RAM_Port->BSRR = (uint32_t)(1U<<(CLK1_RAM_Pin+16)); 	\
						CLK2_RAM_Port->BSRR = (uint32_t)(1U<<CLK2_RAM_Pin);		\
						__ASM("NOP");												\
						CLK2_RAM_Port->BSRR = (uint32_t)(1U<<(CLK2_RAM_Pin+16))


//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef struct {
	uint8_t 	ram_flag;
	uint16_t	ram_crc;
	uint8_t 	ram_scan[128];
	uint8_t 	ram_buf[1024];
	uint8_t 	nothing2;
} ram_test_t;


//----------------------------------------------------------------------------------------------
//                                  Function's prototypes
//----------------------------------------------------------------------------------------------
void ReadByteFromRam(uint32_t, uint8_t *);
void WriteByteToRam(uint32_t, uint8_t *);
void ReadWordFromRam(uint32_t, uint32_t *);
void WriteWordToRam(uint32_t, uint32_t *);
void ReadArrayFromRam(uint32_t, uint8_t *, uint32_t);
void WriteArrayToRam(uint32_t, uint8_t *, uint32_t);



#endif
