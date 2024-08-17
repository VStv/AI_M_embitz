//*********************************************************************************************
//                                          Flash.c
//*********************************************************************************************
//
//---------------------------------------------------------------------------------------------
//                                     Include section 
//---------------------------------------------------------------------------------------------
#include "flash.h"


//---------------------------------------------------------------------------------------------
//                                        Functions
//---------------------------------------------------------------------------------------------
//--------------------------- Unlocking MCU flash memory (  us) -------------------------------
void FlashUnLock(void)
{
	while(FLASH->CR & FLASH_CR_LOCK)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}
}


//---------------------------- Locking MCU flash memory (  us) --------------------------------
void FlashLock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}



void FlashErasePage(uint32_t StartAdr)
{
	//ѕредварительное стирание страницы FLASH пам€ти контроллера
	while (FLASH->SR & FLASH_SR_BSY){};
	if (FLASH->SR & FLASH_SR_EOP)
	{
		FLASH->SR = FLASH_SR_EOP;
	}
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = StartAdr;
	FLASH->CR |= FLASH_CR_STRT;
	while (!(FLASH->SR & FLASH_SR_EOP)){};
	FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~FLASH_CR_PER;	
}



////-------------------------- Erasing MCU flash memory page (  us) -----------------------------
//void FlashErasePage	(
//					uint32_t StartAdr
//					)
//{
//	FLASH->CR |= FLASH_CR_PER;
//	FLASH->AR = StartAdr;
//	FLASH->CR |= FLASH_CR_STRT;
//	while(FLASH->SR & FLASH_SR_BSY);
//	FLASH->CR &= ~FLASH_CR_PER;	
//}




void FlashWritePage(uint32_t StartAdr, uint16_t * pBufW, uint16_t count)
{
	register uint32_t i;
//	//ѕредварительное стирание страницы FLASH пам€ти контроллера
//	FlashErasePage(StartAdr);
	//«апись данных во FLASH пам€ти контроллера	
	while (FLASH->SR & FLASH_SR_BSY){};	
	if (FLASH->SR & FLASH_SR_EOP)
	{
		FLASH->SR = FLASH_SR_EOP;
	}
	
	FLASH->CR |= FLASH_CR_PG;

	for (i = 0;i < count;i++) 
	{
		*(volatile uint16_t *)(StartAdr + i * 2) = pBufW[i];
		while (!(FLASH->SR & FLASH_SR_EOP)){};
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR &= ~(FLASH_CR_PG);	
}

////------------------------- Wrighting MCU flash memory page (  us) ----------------------------
//void FlashWritePage	(
//					uint32_t StartAdr, 
//					uint16_t *pBufW, 
//					uint16_t count
//					)
//{
//	register uint32_t i;
//	
//	FLASH->CR |= FLASH_CR_PG;
//	for(i=0; i<count; i++) 
//	{
//		*(__IO uint16_t *)(StartAdr + i * 2) = pBufW[i];
//		while(FLASH->SR & FLASH_SR_BSY);
//	}
//	FLASH->CR &= ~(FLASH_CR_PG);
//}



void FlashWriteCell(uint32_t Adres, uint16_t Val)
{	
	FLASH->CR |= FLASH_CR_PG;
	*(volatile uint16_t *)Adres = Val;
	while (!(FLASH->SR & FLASH_SR_EOP)){};
	FLASH->SR = FLASH_SR_EOP;  
	FLASH->CR &= ~(FLASH_CR_PG);  
}

////----------------------------- Wrighting MCU flash cell (  us) -------------------------------
//void FlashWriteCell	(
//					uint32_t Adres, 
//					uint16_t Val
//					)
//{	
//	FLASH->CR |= FLASH_CR_PG;
//	*(__IO uint16_t *)Adres = Val;
//	while(FLASH->SR & FLASH_SR_BSY);
//	FLASH->CR &= ~(FLASH_CR_PG);  
//}


//-------------------------- Reading MCU flash memory page (  us) -----------------------------
void ReadBufFlash	(
					uint32_t StartAdr, 
					uint16_t *pBufR, 
					uint16_t count
					)
{
	register uint32_t i;
	for(i=0; i<count; i++)
	{
		pBufR[i] = *(volatile uint16_t *)(StartAdr + i*2);
	}
}


//-------------------------- Reading MCU flash memory page (  us) -----------------------------
uint16_t ReadWordFlash	(
						uint32_t Adres
						)
{
	register uint16_t res;
	
	res = *(volatile uint16_t *)Adres;
	return res;
}





//---------------------------------------------------------------------------------------------
//                                    Privat functions
//---------------------------------------------------------------------------------------------

