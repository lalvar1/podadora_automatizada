/*
 * IAP.c
 *
 *  Created on: 1 de oct. de 2017
 *      Author: Cristian
 */


#include "IAP.h"

/*****************************************************************************
** Function name:	u32IAP_PrepareSectors
**
** Description:		Prepares sector(s) for erasing or write operations. This
** 					command must be executed before executing the "Copy RAM to
** 					Flash" or "Erase Sector(s)" commands.
**
** Parameters:		u32StartSector - Number of first sector to prepare.
** 					u32EndSector - Number of last sector to prepare.
**
** Returned value:	Status code returned by IAP ROM function.
**
******************************************************************************/
uint32_t u32IAP_PrepareSectors(uint32_t u32StartSector, uint32_t u32EndSector)
{
	uint32_t u32Status;
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	if (u32EndSector < u32StartSector)
	{
		u32Status = IAP_STA_INVALD_PARAM;
	}
	else
	{
		au32Command[0] = IAP_CMD_PREPARE_SECTORS;
		au32Command[1] = u32StartSector;
		au32Command[2] = u32EndSector;

		IAP_EXECUTE_CMD(au32Command, au32Result);

		u32Status = au32Result[0];
	}
	return u32Status;
}

/*****************************************************************************
** Function name:	u32IAP_CopyRAMToFlash
**
** Description:		Program the flash memory with data stored in RAM.
**
** Parameters:	   	u32DstAddr - Destination Flash address, should be a 256
**                               byte boundary.
**			 		u32SrcAddr - Source RAM address, should be a word boundary
**			 		u32Len     - Number of 8-bit bytes to write, must be 256
**								 512, 1024, or 4096.
*
** Returned value:	Status code returned by IAP ROM function.
**
******************************************************************************/
uint32_t u32IAP_CopyRAMToFlash(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len)
{
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_COPY_RAM_TO_FLASH;
	au32Command[1] = u32DstAddr;
	au32Command[2] = u32SrcAddr;
	au32Command[3] = u32Len;
	au32Command[4] = 100000;	/* Core clock frequency in kHz */

	IAP_EXECUTE_CMD(au32Command, au32Result);

	return au32Result[0];
}

/*****************************************************************************
** Function name:	u32IAP_EraseSectors
**
** Description:		Erase a sector or multiple sectors of on-chip Flash memory.
**
** Parameters:		u32StartSector - Number of first sector to erase.
** 					u32EndSector - Number of last sector to erase.
*
** Returned value:	Status code returned by IAP ROM function.
**
******************************************************************************/
uint32_t u32IAP_EraseSectors(uint32_t u32StartSector, uint32_t u32EndSector)
{
	uint32_t u32Status;
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	if (u32EndSector < u32StartSector)
	{
		u32Status = IAP_STA_INVALD_PARAM;
	}
	else
	{
		au32Command[0] = IAP_CMD_ERASE_SECTORS;
		au32Command[1] = u32StartSector;
		au32Command[2] = u32EndSector;
		au32Command[3] = 100000;	/* Core clock frequency in kHz */

		IAP_EXECUTE_CMD(au32Command, au32Result);

		u32Status = au32Result[0];
	}
	return u32Status;
}


/*****************************************************************************
** Function name:	u32IAP_Compare
**
** Description:		Compares the memory contents at two locations.
**
** Parameters:		u32Len - Number of bytes to compare, must be a multiple of 4.
**					pu32Offset - Offset of the first mismatch if the Status Code is COMPARE_ERROR
**
** Returned value:	Status code returned by IAP ROM function.
**
******************************************************************************/
uint32_t u32IAP_Compare(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len, uint32_t *pu32Offset)
{
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_COMPARE;
	au32Command[1] = u32DstAddr;
	au32Command[2] = u32SrcAddr;
	au32Command[3] = u32Len;

	IAP_EXECUTE_CMD(au32Command, au32Result);

	if (au32Result[0] == IAP_STA_COMPARE_ERROR)
	{
		if (pu32Offset != 0)
		{
			*pu32Offset = au32Result[1];
		}
	}
	return au32Result[0];
}

void interrupciones(uint8_t estado)
{
	if(estado==OFF)
	{
		ICER0=ISER0;
	}
	if(estado==ON)
	{
		ISER0=iser;
	}

}

