//*********************************************************************************************
//                                      Gpio_control.h
//*********************************************************************************************

#ifndef __GPIO_CONTROL__
#define __GPIO_CONTROL__

//---------------------------------------------------------------------------------------------
//                                     Include section
//---------------------------------------------------------------------------------------------
#include "stm32f10x.h"
#include "settings.h"


//---------------------------------------------------------------------------------------------
//                                     Typedef section
//---------------------------------------------------------------------------------------------
typedef enum {
	I_AH_MES = 0,
	I_BH_MES,
	I_CH_MES,
	I_AK_MES,
	I_BK_MES,
	I_CK_MES,
	I_0_MES,
	U_A_MES,
	U_B_MES,
	U_C_MES,
	U_0_MES,
	U_F_MES
} chan_mes_t;


typedef enum {
	I_AH_BAS = 0,
	I_BH_BAS,
	I_CH_BAS,
	I_AK_BAS,
	I_BK_BAS,
	I_CK_BAS,
	I_0_BAS,
	U_A_BAS,
	U_B_BAS,
	U_C_BAS,
	U_0_BAS,

		U_AB_BAS,
		U_BC_BAS,
		U_CA_BAS,
	NONE = 0xff
} chan_bas_t;


typedef enum {
	I_AH_ROT = 0,
	I_BH_ROT,
	I_CH_ROT,
	I_AK_ROT,
	I_BK_ROT,
	I_CK_ROT,
	I_0_ROT,
	U_A_ROT,
	U_B_ROT,
	U_C_ROT,
	U_0_ROT,

		U_AB_ROT,
		U_BC_ROT,
		U_CA_ROT,
			I_DA_ROT,
			I_DB_ROT,
			I_DC_ROT,
} chan_rot_t;


typedef enum {
	Z_ST = 0x00UL,
	P_UP = 0x01UL,
    P_DN = 0x02UL,
} pupd_t;


typedef enum {
	PSH_PULL = 0,
	OPN_DRN,
} outp_t;


typedef enum {
	SLOW = 0x02UL,
	MEDI = 0x01UL,
    FAST = 0x03UL,
} outsp_t;



//---------------------------------------------------------------------------------------------
//                                      Define section
//---------------------------------------------------------------------------------------------
#define CHNL_MESR				12
#define CHNL_LINE				3
#define CHNL_BASE				CHNL_MESR + CHNL_LINE - 1
#define CHNL_IDIFF				3
#define CHNL_ROTD				CHNL_MESR + CHNL_LINE + CHNL_IDIFF - 1


#define COM_DATABUS_MASK		((uint32_t)(1UL<<D0_COM_Pin | 1UL<<D1_COM_Pin | 1UL<<D2_COM_Pin | 1UL<<D3_COM_Pin | 1UL<<D4_COM_Pin | 1UL<<D5_COM_Pin | 1UL<<D6_COM_Pin | 1UL<<D7_COM_Pin))
#define RAM_DATABUS_MASK		COM_DATABUS_MASK


// ADC pins
#define D0_ADC_Pin			0
#define D1_ADC_Pin			1
#define D2_ADC_Pin			2
#define D3_ADC_Pin			3
#define D4_ADC_Pin			4
#define D5_ADC_Pin			5
#define D6_ADC_Pin			6
#define D7_ADC_Pin			7
#define D8_ADC_Pin			8
#define D9_ADC_Pin			9
#define D10_ADC_Pin			10
#define D11_ADC_Pin			11
#define D12_ADC_Pin			12
#define D13_ADC_Pin			13
#define D14_ADC_Pin			14
#define D15_ADC_Pin			15

#define CS1_ADC_Pin			0
#define CS2_ADC_Pin			1
#define RD_ADC_Pin			7
#define CONVST1_ADC_Pin		3
#define CONVST2_ADC_Pin		4

// ADC ports
#define DATA_ADC_Port		D0_ADC_Port
#define D0_ADC_Port			GPIOB
#define D1_ADC_Port			GPIOB
#define D2_ADC_Port			GPIOB
#define D3_ADC_Port			GPIOB
#define D4_ADC_Port			GPIOB
#define D5_ADC_Port			GPIOB
#define D6_ADC_Port			GPIOB
#define D7_ADC_Port			GPIOB
#define D8_ADC_Port			GPIOB
#define D9_ADC_Port			GPIOB
#define D10_ADC_Port		GPIOB
#define D11_ADC_Port		GPIOB
#define D12_ADC_Port		GPIOB
#define D13_ADC_Port		GPIOB
#define D14_ADC_Port		GPIOB
#define D15_ADC_Port		GPIOB

#define CS1_ADC_Port		GPIOA
#define CS2_ADC_Port		GPIOA
#define RD_ADC_Port			GPIOA
#define CONVST1_ADC_Port	GPIOA
#define CONVST2_ADC_Port	GPIOA

// RAM pins
#define A0_RAM_Pin			0
#define A1_RAM_Pin			1
#define A2_RAM_Pin			2
#define A3_RAM_Pin			3
#define A4_RAM_Pin			4
#define A5_RAM_Pin			5
#define A6_RAM_Pin			6
#define A7_RAM_Pin			7
#define A8_RAM_Pin			8
#define A9_RAM_Pin			9
#define A10_RAM_Pin			10
#define A11_RAM_Pin			11
#define A12_RAM_Pin			12
#define A13_RAM_Pin			13
#define A14_RAM_Pin			14
#define A15_RAM_Pin			15
#define A16_RAM_Pin			0
#define A17_RAM_Pin			1
#define A18_RAM_Pin			2
#define A19_RAM_Pin			3

#define D0_RAM_Pin			0
#define D1_RAM_Pin			1
#define D2_RAM_Pin			2
#define D3_RAM_Pin			3
#define D4_RAM_Pin			4
#define D5_RAM_Pin			5
#define D6_RAM_Pin			6
#define D7_RAM_Pin			7

#define CS_RAM_Pin			2
#define WR_RAM_Pin			6
#define RD_RAM_Pin			7
#define CLK1_RAM_Pin		5
#define CLK2_RAM_Pin		15

// RAM ports
#define ADR_RAM_Port		A0_RAM_Port
#define A0_RAM_Port			GPIOB
#define A1_RAM_Port			GPIOB
#define A2_RAM_Port			GPIOB
#define A3_RAM_Port			GPIOB
#define A4_RAM_Port			GPIOB
#define A5_RAM_Port			GPIOB
#define A6_RAM_Port			GPIOB
#define A7_RAM_Port			GPIOB
#define A8_RAM_Port			GPIOB
#define A9_RAM_Port			GPIOB
#define A10_RAM_Port		GPIOB
#define A11_RAM_Port		GPIOB
#define A12_RAM_Port		GPIOB
#define A13_RAM_Port		GPIOB
#define A14_RAM_Port		GPIOB
#define A15_RAM_Port		GPIOB
#define A16_RAM_Port		GPIOB
#define A17_RAM_Port		GPIOB
#define A18_RAM_Port		GPIOB
#define A19_RAM_Port		GPIOB

#define DATA_RAM_Port		D0_RAM_Port
#define D0_RAM_Port			GPIOB
#define D1_RAM_Port			GPIOB
#define D2_RAM_Port			GPIOB
#define D3_RAM_Port			GPIOB
#define D4_RAM_Port			GPIOB
#define D5_RAM_Port			GPIOB
#define D6_RAM_Port			GPIOB
#define D7_RAM_Port			GPIOB

#define CS_RAM_Port			GPIOA
#define WR_RAM_Port			GPIOA
#define RD_RAM_Port			GPIOA
#define CLK1_RAM_Port		GPIOA
#define CLK2_RAM_Port		GPIOA

// COM pins
#define D0_COM_Pin			0
#define D1_COM_Pin			1
#define D2_COM_Pin			2
#define D3_COM_Pin			3
#define D4_COM_Pin			4
#define D5_COM_Pin			5
#define D6_COM_Pin			6
#define D7_COM_Pin			7

#define BUS_EN_Pin			13
#define INT_ATM_Pin			8
#define RD_ATM_Pin			12
#define IN_STM_Pin			11
#define DATA_STM_Pin		10

// COM ports
#define DATA_COM_Port		D0_COM_Port
#define D0_COM_Port			GPIOB
#define D1_COM_Port			GPIOB
#define D2_COM_Port			GPIOB
#define D3_COM_Port			GPIOB
#define D4_COM_Port			GPIOB
#define D5_COM_Port			GPIOB
#define D6_COM_Port			GPIOB
#define D7_COM_Port			GPIOB

#define BUS_EN_Port			GPIOC
#define INT_ATM_Port		GPIOA
#define RD_ATM_Port			GPIOA
#define IN_STM_Port			GPIOA
#define DATA_STM_Port		GPIOA
#define CNTR_COM_Port		INT_ATM_Port

// Uf channel
#define U_F_Pin				9
#define U_F_Port			GPIOA


// USART1 pins
//#define TXD1_Pin			9
//#define RXD1_Pin			10

// USART1 ports
//#define USART1_Port			TXD1_Port
//#define TXD1_Port			GPIOA
//#define RXD1_Port			GPIOA

// BUTTON
//#define BUT_Pin				9
//#define BUT_Port			GPIOA


// LED
#define LED_Pin				9
#define LED_Port			GPIOC

// PPS
#define PPS_Pin				12
#define PPS_Port			GPIOC



//---------------------------------------------------------------------------------------------
//                                           Macros
//---------------------------------------------------------------------------------------------
//Output control
#define SET_PIN(port, pin)	    port->BSRR = (uint32_t)(1UL<<pin)
#define RESET_PIN(port, pin)    port->BSRR = (uint32_t)(1UL<<(pin+16))

//Input polling
#define TEST_PIN(port, pin)		(port->IDR & (uint32_t)(1UL<<pin))

//Pullup - float
#define PIN_PULLUP(port, pin)	(port->ODR | (uint32_t)(1UL<<pin))
#define PIN_FLOAT(port, pin)	(port->ODR & ~((uint32_t)(1UL<<pin)))

#define RESET_BUS()				AdcDataBusAsInput()

//Setup ADC control lines
#define RESET_ADC_CTRL()		SetAsPpOutput(CS1_ADC_Port, CS1_ADC_Pin, 1);	\
								SetAsPpOutput(CS2_ADC_Port, CS2_ADC_Pin, 1);	\
								SetAsPpOutput(RD_ADC_Port, RD_ADC_Pin, 1);	\
								SetAsPpOutput(CONVST1_ADC_Port, CONVST1_ADC_Pin, 0);	\
								SetAsPpOutput(CONVST2_ADC_Port, CONVST2_ADC_Pin, 0)

//Setup RAM control lines
#define RESET_RAM_CTRL()		SetAsPpOutput(CS_RAM_Port, CS_RAM_Pin, 0);	\
								SetAsPpOutput(WR_RAM_Port, WR_RAM_Pin, 1);	\
								SetAsPpOutput(RD_RAM_Port, RD_RAM_Pin, 1);	\
								SetAsPpOutput(CLK1_RAM_Port, CLK1_RAM_Pin, 0);	\
								SetAsPpOutput(CLK2_RAM_Port, CLK2_RAM_Pin, 0)

//Setup COM control lines for transmit
#define SETUP_TXD_CTRL()		CNTR_COM_Port->BSRR = (uint32_t)((1UL<<(DATA_STM_Pin+16)) | (1UL<<INT_ATM_Pin));	\
								CNTR_COM_Port->CRH &= (uint32_t)~((0x0fU<<(4*(RD_ATM_Pin-8))) | (0x0fU<<(4*(IN_STM_Pin-8))) | (0x0fU<<(4*(DATA_STM_Pin-8))) | (0x0fU<<(4*(INT_ATM_Pin-8))));	\
								CNTR_COM_Port->CRH |= (uint32_t)((0x04U<<(4*(RD_ATM_Pin-8))) | (0x04U<<(4*(IN_STM_Pin-8))) | (0x02U<<(4*(DATA_STM_Pin-8))) | (0x02U<<(4*(INT_ATM_Pin-8))))

/* 								SetAsZInput(RD_ATM_Port, RD_ATM_Pin);				\
 * 								SetAsZInput(IN_STM_Port, IN_STM_Pin);				\
 * 								SetAsPpOutput(DATA_STM_Port, DATA_STM_Pin, 0);		\
 * 								SetAsPpOutput(INT_ATM_Port, INT_ATM_Pin, 1)
 * 								SetAsPpOutput(BUS_EN_Port, BUS_EN_Pin, 1);
 */

//Setup COM control lines for recieve
#define SETUP_RXD_CTRL()		CNTR_COM_Port->BSRR = (uint32_t)((1UL<<(RD_ATM_Pin+16)) | (1UL<<INT_ATM_Pin));	\
								CNTR_COM_Port->CRH &= (uint32_t)~((0x0fU<<(4*(RD_ATM_Pin-8))) | (0x0fU<<(4*(IN_STM_Pin-8))) | (0x0fU<<(4*(DATA_STM_Pin-8))) | (0x0fU<<(4*(INT_ATM_Pin-8))));	\
								CNTR_COM_Port->CRH |= (uint32_t)((0x02U<<(4*(RD_ATM_Pin-8))) | (0x04U<<(4*(IN_STM_Pin-8))) | (0x04U<<(4*(DATA_STM_Pin-8))) | (0x02U<<(4*(INT_ATM_Pin-8))))

/* 								SetAsPpOutput(RD_ATM_Port, RD_ATM_Pin, 0);			\
 * 								SetAsZInput(IN_STM_Port, IN_STM_Pin);				\
 * 								SetAsZInput(DATA_STM_Port, DATA_STM_Pin);			\
 * 								SetAsPpOutput(INT_ATM_Port, INT_ATM_Pin, 1)
 * 								//SetAsPpOutput(BUS_EN_Port, BUS_EN_Pin, 1);
 */


#define OFF_TXRX_CTRL()			SetAsZInput(DATA_STM_Port, DATA_STM_Pin);			\
								SetAsZInput(IN_STM_Port, IN_STM_Pin);				\
								SetAsZInput(RD_ATM_Port, RD_ATM_Pin);				\
								SetAsZInput(INT_ATM_Port, INT_ATM_Pin)

#define LED_OFF()				RESET_PIN(LED_Port, LED_Pin)
#define LED_ON()				SET_PIN(LED_Port, LED_Pin)


//----------------------------------------------------------------------------------------------
//                                    Function's prototypes
//----------------------------------------------------------------------------------------------
void SetAsInput(GPIO_TypeDef *, uint32_t, uint32_t);
void SetAsZInput(GPIO_TypeDef *, uint32_t);
void SetAsPpOutput(GPIO_TypeDef *, uint8_t, uint32_t);
void SetAsOdOutput(GPIO_TypeDef *, uint8_t, uint32_t);
void RamAdrBusAsOutput(void);
void RamDataBusAsInput(void);
void RamDataBusAsOutput(void);
void AdcDataBusAsInput(void);
void ComDataBusAsInput(void);
void ComDataBusAsOutput(void);
uint8_t RxByteByBus(void);
uint16_t RxWordByBus(void);
void TxByteByBus(uint8_t data_8);
void TxByteByBus1(uint8_t data_8);
void TxWordByBus(uint16_t data_16);

void GpioInit(void);
//void LedCtrl(uint8_t);

#endif
