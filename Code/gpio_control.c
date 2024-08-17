//*********************************************************************************************
//                                      Gpio_control.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "gpio_control.h"

//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//------------------------ Input with pullup (pulldown) resistor ------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware independent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SetAsInput	(
				GPIO_TypeDef *port, 
				uint32_t pin, 
				uint32_t updown
				)
{
//	uint32_t temp;
	
	if(pin < 8)
	{	
		port->CRL &= (uint32_t)~(0x0fU<<(4*pin));
		port->CRL |= (uint32_t)(0x08U<<(4*pin)); 
	}
	else
	{	
		port->CRH &= (uint32_t)~(0x0fU<<(4*(pin-8)));
		port->CRH |= (uint32_t)(0x08U<<(4*(pin-8)));
	}
	__disable_irq();
//	temp = port->ODR;
	if(updown) port->ODR |= (uint32_t)(1<<pin);
	else port->ODR &= (uint32_t)~(1<<pin);
//	port->ODR = (uint32_t)temp;
	__enable_irq();
}																								

//---------------------------------- Input with Z-state ---------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware independent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SetAsZInput(
				GPIO_TypeDef *port, 
				uint32_t pin 
				)
{
	if(pin < 8)
	{	
		port->CRL &= (uint32_t)~(0x0fU<<(4*pin));
		port->CRL |= (uint32_t)(0x04U<<(4*pin)); 
	}
	else
	{	
		port->CRH &= (uint32_t)~(0x0fU<<(4*(pin-8)));
		port->CRH |= (uint32_t)(0x04U<<(4*(pin-8)));
	}
}																								
																 			 
//-------------------------------------- Output settings --------------------------------------
// !!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware independent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SetAsPpOutput	(
					GPIO_TypeDef *port, 
					uint8_t pin, 
					uint32_t init
					)
{
	if(init) port->BSRR = (uint32_t)(1<<pin);
	else port->BSRR = (uint32_t)(1<<(pin+16));
	if(pin < 8)
	{	
		port->CRL &= (uint32_t)~(0x0fU<<(4*pin));
		port->CRL |= (uint32_t)(0x02U<<(4*pin)); // 0x03U
	}
	else
	{	
		port->CRH &= (uint32_t)~(0x0fU<<(4*(pin-8)));
		port->CRH |= (uint32_t)(0x02U<<(4*(pin-8))); // 0x03U
	}
}																								

//-------------------------------------- Output settings --------------------------------------
// !!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware independent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SetAsOdOutput	(
					GPIO_TypeDef *port, 
					uint8_t pin, 
					uint32_t init
					)
{
	if(init) port->BSRR = (uint32_t)(1<<pin);
	else port->BSRR = (uint32_t)(1<<(pin+16));
	if(pin < 8)
	{	
		port->CRL &= (uint32_t)~(0x0fU<<(4*pin));
		port->CRL |= (uint32_t)(0x06U<<(4*pin));  // 0x07U
	}
	else
	{	
		port->CRH &= (uint32_t)~(0x0fU<<(4*(pin-8)));
		port->CRH |= (uint32_t)(0x06U<<(4*(pin-8)));  // 0x07U
	}
}																								

//-------------------------------- RAM Adress Bus settings ------------------------------------
// !!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - A0...A15(A19) - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - A0...A7 - must locate in range 0...7 and A8...A15 - must locate in range 8...15 (if not - it is need repairing of function)
void RamAdrBusAsOutput(void)
{
	__disable_irq();
	ADR_RAM_Port->ODR &= (uint32_t)~((1<<A0_RAM_Pin)|			// Reset output data register
									(1<<A1_RAM_Pin)|
									(1<<A2_RAM_Pin)|
									(1<<A3_RAM_Pin)|
									(1<<A4_RAM_Pin)|
									(1<<A5_RAM_Pin)|
									(1<<A6_RAM_Pin)|
									(1<<A7_RAM_Pin)|
									(1<<A8_RAM_Pin)|
									(1<<A9_RAM_Pin)|
									(1<<A10_RAM_Pin)|
									(1<<A11_RAM_Pin)|
									(1<<A12_RAM_Pin)|
									(1<<A13_RAM_Pin)|
									(1<<A14_RAM_Pin)|
									(1<<A15_RAM_Pin));
	__enable_irq();
	ADR_RAM_Port->CRL &= (uint32_t)~((0x0fU<<(4*A0_RAM_Pin))|	// Set lines as output (first - clear, then - set mode)
                                    (0x0fU<<(4*A1_RAM_Pin))|
                                    (0x0fU<<(4*A2_RAM_Pin))|
                                    (0x0fU<<(4*A3_RAM_Pin))|
                                    (0x0fU<<(4*A4_RAM_Pin))|
                                    (0x0fU<<(4*A5_RAM_Pin))|
                                    (0x0fU<<(4*A6_RAM_Pin))|
                                    (0x0fU<<(4*A7_RAM_Pin)));
	ADR_RAM_Port->CRH &= (uint32_t)~((0x0fU<<(4*(A8_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A9_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A10_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A11_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A12_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A13_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A14_RAM_Pin-8)))|
                                    (0x0fU<<(4*(A15_RAM_Pin-8))));
	ADR_RAM_Port->CRL |= (uint32_t) ((0x02U<<(4*A0_RAM_Pin))|
                                    (0x02U<<(4*A1_RAM_Pin))|
                                    (0x02U<<(4*A2_RAM_Pin))|
                                    (0x02U<<(4*A3_RAM_Pin))|
                                    (0x02U<<(4*A4_RAM_Pin))|
                                    (0x02U<<(4*A5_RAM_Pin))|
                                    (0x02U<<(4*A6_RAM_Pin))|
                                    (0x02U<<(4*A7_RAM_Pin)));
	ADR_RAM_Port->CRH |= (uint32_t)((0x02U<<(4*(A8_RAM_Pin-8)))|
                                    (0x02U<<(4*(A9_RAM_Pin-8)))|
                                    (0x02U<<(4*(A10_RAM_Pin-8)))|
                                    (0x02U<<(4*(A11_RAM_Pin-8)))|
                                    (0x02U<<(4*(A12_RAM_Pin-8)))|
                                    (0x02U<<(4*(A13_RAM_Pin-8)))|
                                    (0x02U<<(4*(A14_RAM_Pin-8)))|
                                    (0x02U<<(4*(A15_RAM_Pin-8))));
}

//----------------------------- RAM Data Bus settings (input) ---------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - D0...D7 - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - D0...D7 - must locate in range 0...7 (if not - it is need repairing of function)
void RamDataBusAsInput(void)
{
	DATA_RAM_Port->CRL &= (uint32_t)~((0x0fU<<(4*D0_RAM_Pin))|		// Set lines as input (first - clear, then - set mode)
                                    (0x0fU<<(4*D1_RAM_Pin))|
                                    (0x0fU<<(4*D2_RAM_Pin))|
                                    (0x0fU<<(4*D3_RAM_Pin))|
                                    (0x0fU<<(4*D4_RAM_Pin))|
                                    (0x0fU<<(4*D5_RAM_Pin))|
                                    (0x0fU<<(4*D6_RAM_Pin))|
                                    (0x0fU<<(4*D7_RAM_Pin)));
	DATA_RAM_Port->CRL |= (uint32_t)((0x08U<<(4*D0_RAM_Pin))|
                                    (0x08U<<(4*D1_RAM_Pin))|
                                    (0x08U<<(4*D2_RAM_Pin))|
                                    (0x08U<<(4*D3_RAM_Pin))|
                                    (0x08U<<(4*D4_RAM_Pin))|
                                    (0x08U<<(4*D5_RAM_Pin))|
                                    (0x08U<<(4*D6_RAM_Pin))|
                                    (0x08U<<(4*D7_RAM_Pin)));
	__disable_irq();
	DATA_RAM_Port->ODR |= (uint32_t)((1<<D0_RAM_Pin)|				// Switch on pull-up resistors
									(1<<D1_RAM_Pin)|
									(1<<D2_RAM_Pin)|
									(1<<D3_RAM_Pin)|
									(1<<D4_RAM_Pin)|
									(1<<D5_RAM_Pin)|
									(1<<D6_RAM_Pin)|
									(1<<D7_RAM_Pin));
	__enable_irq();
}

//---------------------------- RAM Data Bus settings (output) ---------------------------------
// !!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - D0...D7 - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - D0...D7 - must locate in range 0...7 (if not - it is need repairing of function)
void RamDataBusAsOutput(void)
{
	__disable_irq();
	DATA_RAM_Port->ODR &= (uint32_t)~((1<<D0_RAM_Pin)|				// Reset output data register
									(1<<D1_RAM_Pin)|
									(1<<D2_RAM_Pin)|
									(1<<D3_RAM_Pin)|
									(1<<D4_RAM_Pin)|
									(1<<D5_RAM_Pin)|
									(1<<D6_RAM_Pin)|
									(1<<D7_RAM_Pin));
	__enable_irq();
	DATA_RAM_Port->CRL &= (uint32_t)~((0x0fU<<(4*D0_RAM_Pin))|		// Set lines as output (first - clear, then - set mode)
                                    (0x0fU<<(4*D1_RAM_Pin))|
                                    (0x0fU<<(4*D2_RAM_Pin))|
                                    (0x0fU<<(4*D3_RAM_Pin))|
                                    (0x0fU<<(4*D4_RAM_Pin))|
                                    (0x0fU<<(4*D5_RAM_Pin))|
                                    (0x0fU<<(4*D6_RAM_Pin))|
                                    (0x0fU<<(4*D7_RAM_Pin)));
	DATA_RAM_Port->CRL |= (uint32_t)((0x02U<<(4*D0_RAM_Pin))|
                                    (0x02U<<(4*D1_RAM_Pin))|
                                    (0x02U<<(4*D2_RAM_Pin))|
                                    (0x02U<<(4*D3_RAM_Pin))|
                                    (0x02U<<(4*D4_RAM_Pin))|
                                    (0x02U<<(4*D5_RAM_Pin))|
                                    (0x02U<<(4*D6_RAM_Pin))|
                                    (0x02U<<(4*D7_RAM_Pin)));
}


//---------------------------------- ADC Bus settings -----------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - D0...D15 - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - D0...D7 - must locate in range 0...7 and D8...D15 - must locate in range 8...15 (if not - it is need repairing of function)
void AdcDataBusAsInput(void)
{
	DATA_ADC_Port->CRL &= (uint32_t)~((0x0fU<<(4*D0_ADC_Pin))|				// Set lines as input (first - clear, then - set mode)
                                    (0x0fU<<(4*D1_ADC_Pin))|
                                    (0x0fU<<(4*D2_ADC_Pin))|
                                    (0x0fU<<(4*D3_ADC_Pin))|
                                    (0x0fU<<(4*D4_ADC_Pin))|
                                    (0x0fU<<(4*D5_ADC_Pin))|
                                    (0x0fU<<(4*D6_ADC_Pin))|
                                    (0x0fU<<(4*D7_ADC_Pin)));
	DATA_ADC_Port->CRH &= (uint32_t)~((0x0fU<<(4*(D8_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D9_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D10_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D11_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D12_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D13_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D14_ADC_Pin-8)))|
                                    (0x0fU<<(4*(D15_ADC_Pin-8))));
	DATA_ADC_Port->CRL |= (uint32_t)((0x08U<<(4*D0_ADC_Pin))|
                                    (0x08U<<(4*D1_ADC_Pin))|
                                    (0x08U<<(4*D2_ADC_Pin))|
                                    (0x08U<<(4*D3_ADC_Pin))|
                                    (0x08U<<(4*D4_ADC_Pin))|
                                    (0x08U<<(4*D5_ADC_Pin))|
                                    (0x08U<<(4*D6_ADC_Pin))|
                                    (0x08U<<(4*D7_ADC_Pin)));
	DATA_ADC_Port->CRH |= (uint32_t)((0x08U<<(4*(D8_ADC_Pin-8)))|
                                    (0x08U<<(4*(D9_ADC_Pin-8)))|
                                    (0x08U<<(4*(D10_ADC_Pin-8)))|
                                    (0x08U<<(4*(D11_ADC_Pin-8)))|
                                    (0x08U<<(4*(D12_ADC_Pin-8)))|
                                    (0x08U<<(4*(D13_ADC_Pin-8)))|
                                    (0x08U<<(4*(D14_ADC_Pin-8)))|
                                    (0x08U<<(4*(D15_ADC_Pin-8))));
	__disable_irq();
	DATA_ADC_Port->ODR |= (uint32_t)((1<<D0_ADC_Pin)|						// Switch on pull-up resistors
									(1<<D1_ADC_Pin)|
									(1<<D2_ADC_Pin)|
									(1<<D3_ADC_Pin)|
									(1<<D4_ADC_Pin)|
									(1<<D5_ADC_Pin)|
									(1<<D6_ADC_Pin)|
									(1<<D7_ADC_Pin)|
									(1<<D8_ADC_Pin)|
									(1<<D9_ADC_Pin)|
									(1<<D10_ADC_Pin)|
									(1<<D11_ADC_Pin)|
									(1<<D12_ADC_Pin)|
									(1<<D13_ADC_Pin)|
									(1<<D14_ADC_Pin)|
									(1<<D15_ADC_Pin));
	__enable_irq();
}


//--------------------------- Communication Bus settings (input) ------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - D0...D7 - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - D0...D7 - must locate in range 0...7 (if not - it is need repairing of function)
void ComDataBusAsInput(void)
{
	DATA_COM_Port->CRL &= (uint32_t)~((0x0fU<<(4*D0_COM_Pin))|		// Set lines as input (first - clear, then - set mode)
                                    (0x0fU<<(4*D1_COM_Pin))|
                                    (0x0fU<<(4*D2_COM_Pin))|
                                    (0x0fU<<(4*D3_COM_Pin))|
                                    (0x0fU<<(4*D4_COM_Pin))|
                                    (0x0fU<<(4*D5_COM_Pin))|
                                    (0x0fU<<(4*D6_COM_Pin))|
                                    (0x0fU<<(4*D7_COM_Pin)));
	DATA_COM_Port->CRL |= (uint32_t)((0x08U<<(4*D0_COM_Pin))|
                                    (0x08U<<(4*D1_COM_Pin))|
                                    (0x08U<<(4*D2_COM_Pin))|
                                    (0x08U<<(4*D3_COM_Pin))|
                                    (0x08U<<(4*D4_COM_Pin))|
                                    (0x08U<<(4*D5_COM_Pin))|
                                    (0x08U<<(4*D6_COM_Pin))|
                                    (0x08U<<(4*D7_COM_Pin)));
	__disable_irq();
	DATA_COM_Port->ODR |= (uint32_t)((1<<D0_COM_Pin)|				// Switch on pull-up resistors
									(1<<D1_COM_Pin)|
									(1<<D2_COM_Pin)|
									(1<<D3_COM_Pin)|
									(1<<D4_COM_Pin)|
									(1<<D5_COM_Pin)|
									(1<<D6_COM_Pin)|
									(1<<D7_COM_Pin));
	__enable_irq();
}

//-------------------------- Communication Bus settings (output) ------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!!! Function is hardware dependent !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 1 - D0...D7 - must be same port (for example Port B) (if not - it is need repairing of function)
// 2 - D0...D7 - must locate in range 0...7 (if not - it is need repairing of function)
void ComDataBusAsOutput(void)
{
	__disable_irq();
	DATA_COM_Port->ODR &= ~((uint32_t)((1<<D0_COM_Pin)|						// Reset output data register
									(1<<D1_COM_Pin)|
									(1<<D2_COM_Pin)|
									(1<<D3_COM_Pin)|
									(1<<D4_COM_Pin)|
									(1<<D5_COM_Pin)|
									(1<<D6_COM_Pin)|
									(1<<D7_COM_Pin)));
	__enable_irq();
	DATA_COM_Port->CRL &= ~((uint32_t)((0x0fU<<(4*D0_COM_Pin))|				// Set lines as output (first - clear, then - set mode)
                                    (0x0fU<<(4*D1_COM_Pin))|
                                    (0x0fU<<(4*D2_COM_Pin))|
                                    (0x0fU<<(4*D3_COM_Pin))|
                                    (0x0fU<<(4*D4_COM_Pin))|
                                    (0x0fU<<(4*D5_COM_Pin))|
                                    (0x0fU<<(4*D6_COM_Pin))|
                                    (0x0fU<<(4*D7_COM_Pin))));
	DATA_COM_Port->CRL |= (uint32_t)((0x02U<<(4*D0_COM_Pin))|
                                    (0x02U<<(4*D1_COM_Pin))|
                                    (0x02U<<(4*D2_COM_Pin))|
                                    (0x02U<<(4*D3_COM_Pin))|
                                    (0x02U<<(4*D4_COM_Pin))|
                                    (0x02U<<(4*D5_COM_Pin))|
                                    (0x02U<<(4*D6_COM_Pin))|
                                    (0x02U<<(4*D7_COM_Pin)));
}

//---------------------------------- Recieve byte by bus --------------------------------------
uint8_t RxByteByBus(void)
{
//	uint16_t temp16;
//    uint8_t temp8 = 0;
//    
//    temp16 = DATA_ADC_Port->IDR;
//    if(temp16 & (uint16_t)(1<<D0_ADC_Pin)) temp8 |= 0x01;
//    else temp8 &= ~0x01;
//    if(temp16 & (uint16_t)(1<<D1_ADC_Pin)) temp8 |= 0x02;
//    else temp8 &= ~0x02;
//    if(temp16 & (uint16_t)(1<<D2_ADC_Pin)) temp8 |= 0x04;
//    else temp8 &= ~0x04;
//    if(temp16 & (uint16_t)(1<<D3_ADC_Pin)) temp8 |= 0x08;
//    else temp8 &= ~0x08;
//    if(temp16 & (uint16_t)(1<<D4_ADC_Pin)) temp8 |= 0x10;
//    else temp8 &= ~0x10;
//    if(temp16 & (uint16_t)(1<<D5_ADC_Pin)) temp8 |= 0x20;
//    else temp8 &= ~0x20;
//    if(temp16 & (uint16_t)(1<<D6_ADC_Pin)) temp8 |= 0x40;
//    else temp8 &= ~0x40;
//    if(temp16 & (uint16_t)(1<<D7_ADC_Pin)) temp8 |= 0x80;
//    else temp8 &= ~0x80;
//    return temp8;
	
	uint32_t temp32 = DATA_ADC_Port->IDR;
    return (uint8_t)temp32;
}

//---------------------------------- Recieve word by bus --------------------------------------
uint16_t RxWordByBus(void)
{
//	uint16_t temp1, temp2 = 0;
//    
//    temp1 = DATA_ADC_Port->IDR;
//    if(temp1 & (uint16_t)(1<<D0_ADC_Pin)) temp2 |= 0x0001;
//    else temp2 &= ~0x0001;
//    if(temp1 & (uint16_t)(1<<D1_ADC_Pin)) temp2 |= 0x0002;
//    else temp2 &= ~0x0002;
//    if(temp1 & (uint16_t)(1<<D2_ADC_Pin)) temp2 |= 0x0004;
//    else temp2 &= ~0x0004;
//    if(temp1 & (uint16_t)(1<<D3_ADC_Pin)) temp2 |= 0x0008;
//    else temp2 &= ~0x0008;
//    if(temp1 & (uint16_t)(1<<D4_ADC_Pin)) temp2 |= 0x0010;
//    else temp2 &= ~0x0010;
//    if(temp1 & (uint16_t)(1<<D5_ADC_Pin)) temp2 |= 0x0020;
//    else temp2 &= ~0x0020;
//    if(temp1 & (uint16_t)(1<<D6_ADC_Pin)) temp2 |= 0x0040;
//    else temp2 &= ~0x0040;
//    if(temp1 & (uint16_t)(1<<D7_ADC_Pin)) temp2 |= 0x0080;
//    else temp2 &= ~0x0080;
//    if(temp1 & (uint16_t)(1<<D8_ADC_Pin)) temp2 |= 0x0100;
//    else temp2 &= ~0x0100;
//    if(temp1 & (uint16_t)(1<<D9_ADC_Pin)) temp2 |= 0x0200;
//    else temp2 &= ~0x0200;
//    if(temp1 & (uint16_t)(1<<D10_ADC_Pin)) temp2 |= 0x0400;
//    else temp2 &= ~0x0400;
//    if(temp1 & (uint16_t)(1<<D11_ADC_Pin)) temp2 |= 0x0800;
//    else temp2 &= ~0x0800;
//    if(temp1 & (uint16_t)(1<<D12_ADC_Pin)) temp2 |= 0x1000;
//    else temp2 &= ~0x1000;
//    if(temp1 & (uint16_t)(1<<D13_ADC_Pin)) temp2 |= 0x2000;
//    else temp2 &= ~0x2000;
//    if(temp1 & (uint16_t)(1<<D14_ADC_Pin)) temp2 |= 0x4000;
//    else temp2 &= ~0x4000;
//    if(temp1 & (uint16_t)(1<<D15_ADC_Pin)) temp2 |= 0x8000;
//    else temp2 &= ~0x8000;
//    return temp2;

	uint32_t temp32;
    
    temp32 = DATA_ADC_Port->IDR;
    return (uint16_t)temp32;
}

//---------------------------------- Transmit byte by bus -------------------------------------
void TxByteByBus(
				uint8_t data_8
				)
{
//    uint8_t temp8; 
//    uint16_t temp16;
//    
//    temp16 = DATA_RAM_Port->ODR;
//	temp8 = data_8;
//    if(temp8 & 0x01) temp16 |= (uint16_t)(1<<D0_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D0_RAM_Pin));
//    if(temp8 & 0x02) temp16 |= (uint16_t)(1<<D1_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D1_RAM_Pin));
//    if(temp8 & 0x04) temp16 |= (uint16_t)(1<<D2_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D2_RAM_Pin));
//    if(temp8 & 0x08) temp16 |= (uint16_t)(1<<D3_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D3_RAM_Pin));
//    if(temp8 & 0x10) temp16 |= (uint16_t)(1<<D4_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D4_RAM_Pin));
//    if(temp8 & 0x20) temp16 |= (uint16_t)(1<<D5_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D5_RAM_Pin));
//    if(temp8 & 0x40) temp16 |= (uint16_t)(1<<D6_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D6_RAM_Pin));
//    if(temp8 & 0x80) temp16 |= (uint16_t)(1<<D7_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D7_RAM_Pin));
//	__disable_irq();
//    DATA_RAM_Port->ODR = temp16;
//    __enable_irq();

    uint32_t temp32;
    
    temp32 = DATA_RAM_Port->ODR;
	temp32 &= 0xffffff00;
	temp32 |= (uint32_t)data_8;
	__disable_irq();
    DATA_RAM_Port->ODR = temp32;
    __enable_irq();
}

////---------------------------------- Transmit byte by bus -------------------------------------
//void TxByteByBus1	(
//					uint8_t data_8
//					)
//{
//    uint8_t temp8; 
//    uint16_t temp16;
//    
//    temp16 = DATA_RAM_Port->ODR;
//	
//	temp8 = data_8;

//    if(temp8 & 0x01) temp16 |= (uint16_t)(1<<D0_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D0_RAM_Pin));
//    if(temp8 & 0x02) temp16 |= (uint16_t)(1<<D1_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D1_RAM_Pin));
//    if(temp8 & 0x04) temp16 |= (uint16_t)(1<<D2_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D2_RAM_Pin));
//    if(temp8 & 0x08) temp16 |= (uint16_t)(1<<D3_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D3_RAM_Pin));
//    if(temp8 & 0x10) temp16 |= (uint16_t)(1<<D4_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D4_RAM_Pin));
//    if(temp8 & 0x20) temp16 |= (uint16_t)(1<<D5_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D5_RAM_Pin));
//    if(temp8 & 0x40) temp16 |= (uint16_t)(1<<D6_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D6_RAM_Pin));
//    if(temp8 & 0x80) temp16 |= (uint16_t)(1<<D7_RAM_Pin);
//    else temp16 &= ~((uint16_t)(1<<D7_RAM_Pin));

//	__disable_irq();
//    DATA_RAM_Port->ODR = temp8;
//    __enable_irq();
//}

//---------------------------------- Transmit word by bus -------------------------------------
void TxWordByBus(
				uint16_t data_16
				)
{
//	uint16_t temp1, temp2;
//    
//    temp2 = DATA_RAM_Port->ODR;
//    temp1 = data_16;
//    if(temp1 & 0x0001) temp2 |= (uint16_t)(1<<A0_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A0_RAM_Pin));
//    if(temp1 & 0x0002) temp2 |= (uint16_t)(1<<A1_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A1_RAM_Pin));
//    if(temp1 & 0x0004) temp2 |= (uint16_t)(1<<A2_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A2_RAM_Pin));
//    if(temp1 & 0x0008) temp2 |= (uint16_t)(1<<A3_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A3_RAM_Pin));
//    if(temp1 & 0x0010) temp2 |= (uint16_t)(1<<A4_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A4_RAM_Pin));
//    if(temp1 & 0x0020) temp2 |= (uint16_t)(1<<A5_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A5_RAM_Pin));
//    if(temp1 & 0x0040) temp2 |= (uint16_t)(1<<A6_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A6_RAM_Pin));
//    if(temp1 & 0x0080) temp2 |= (uint16_t)(1<<A7_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A7_RAM_Pin));
//    
//    if(temp1 & 0x0100) temp2 |= (uint16_t)(1<<A8_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A8_RAM_Pin));
//    if(temp1 & 0x0200) temp2 |= (uint16_t)(1<<A9_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A9_RAM_Pin));
//    if(temp1 & 0x0400) temp2 |= (uint16_t)(1<<A10_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A10_RAM_Pin));
//    if(temp1 & 0x0800) temp2 |= (uint16_t)(1<<A11_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A11_RAM_Pin));
//    if(temp1 & 0x1000) temp2 |= (uint16_t)(1<<A12_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A12_RAM_Pin));
//    if(temp1 & 0x2000) temp2 |= (uint16_t)(1<<A13_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A13_RAM_Pin));
//    if(temp1 & 0x4000) temp2 |= (uint16_t)(1<<A14_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A14_RAM_Pin));
//    if(temp1 & 0x8000) temp2 |= (uint16_t)(1<<A15_RAM_Pin);
//    else temp2 &= ~((uint16_t)(1<<A15_RAM_Pin));
//	__disable_irq();
//    ADR_RAM_Port->ODR = temp2;
//    __enable_irq();

	uint32_t temp32;
    
    temp32 = DATA_RAM_Port->ODR;
	temp32 &= 0xffff0000;
	temp32 |= (uint32_t)data_16;
	__disable_irq();
    ADR_RAM_Port->ODR = temp32;
    __enable_irq();
}


//----------------------------------- GPIO initialization -------------------------------------
void GpioInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  									// Clock for Port A switch on
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;  									// Clock for Port B switch on
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  									// Clock for Port C switch on
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN);  									//| RCC_APB2ENR_USART1EN Clock for alt. func. switch on
	
	AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;			    			// SW interface setting

	GPIOA->CRL &= ~(GPIO_CRL_MODE | GPIO_CRL_CNF);							// Clearing port's config. reg.
	GPIOA->CRH &= ~(GPIO_CRL_MODE | GPIO_CRL_CNF);							// Clearing port's config. reg.
	GPIOB->CRL &= ~(GPIO_CRL_MODE | GPIO_CRL_CNF);
	GPIOB->CRH &= ~(GPIO_CRH_MODE | GPIO_CRH_CNF);
	GPIOC->CRH &= ~(GPIO_CRH_MODE | GPIO_CRH_CNF);
	GPIOC->CRL &= ~(GPIO_CRH_MODE | GPIO_CRH_CNF);

//	GPIOC->CRL |= 0x0000000A; 												/* ƒвухтактный выход  2 ћ√ц  */
	RESET_BUS();															// Set lines of adr. bus as input (Port B)
	RESET_ADC_CTRL();														// Set ADC control lines as output (Port A)
	RESET_RAM_CTRL();														// Set RAM control lines as output (Port A) 
	OFF_TXRX_CTRL();														// Set Z-state for COM control lines (Port A) 
	SetAsPpOutput(BUS_EN_Port, BUS_EN_Pin, 1);
	
	SetAsPpOutput(LED_Port, LED_Pin, 0);
}


////--------------------------------------- LED control -----------------------------------------
//void LedCtrl(
//			uint8_t state
//			)
//{
//	static uint16_t temp2;
//	
//	switch(state)
//	{
//		case 1:
//			LED_ON();
//			break;
//		case 2:
//			temp2++;
//			if(temp2>=150)
//			{
//				if(TEST_PIN(LED_Port, LED_Pin)) LED_OFF();
//				else LED_ON();
//				temp2 = 0;
//			}
//			break;
//		case 3:
//			temp2++;
//			if(temp2<5) LED_ON();
//			else LED_OFF();
//			if(temp2>=1000) temp2 = 0;
//			break;
//		default:
//			LED_OFF();
//			break;
//	}
//}



