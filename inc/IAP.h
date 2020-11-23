/*
 * IAP.h
 *
 *  Created on: 1 de oct. de 2017
 *      Author: Cristian
 */

#ifndef IAP_H_
#define IAP_H_

#include "aplicacion.h"

/* IAP Command Status Codes */
#define IAP_STA_CMD_SUCCESS 								0
#define IAP_STA_INVALID_COMMAND 							1
#define IAP_STA_SRC_ADDR_ERROR 								2
#define IAP_STA_DST_ADDR_ERROR 								3
#define IAP_STA_SRC_ADDR_NOT_MAPPED 						4
#define IAP_STA_DST_ADDR_NOT_MAPPED 						5
#define IAP_STA_COUNT_ERROR 								6
#define IAP_STA_INVALID_SECTOR 								7
#define IAP_STA_SECTOR_NOT_BLANK							8
#define IAP_STA_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION 	9
#define IAP_STA_COMPARE_ERROR 								10
#define IAP_STA_BUSY 										11
#define IAP_STA_INVALD_PARAM 								12

uint32_t u32IAP_EraseSectors(uint32_t u32StartSector, uint32_t u32EndSector);
uint32_t u32IAP_PrepareSectors(uint32_t u32StartSector, uint32_t u32EndSector);
uint32_t u32IAP_CopyRAMToFlash(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len);
uint32_t u32IAP_Compare(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len, uint32_t *pu32Offset);

void interrupciones(uint8_t);


/* IAP Command Definitions */
#define	IAP_CMD_PREPARE_SECTORS			50
#define	IAP_CMD_COPY_RAM_TO_FLASH		51
#define	IAP_CMD_ERASE_SECTORS			52
#define	IAP_CMD_BLANK_CHECK_SECTORS		53
#define	IAP_CMD_READ_PART_ID			54
#define	IAP_CMD_READ_BOOT_ROM_VERSION	55
#define	IAP_CMD_COMPARE					56
#define	IAP_CMD_REINVOKE_ISP			57
#define IAP_CMD_READ_SERIAL_NUMBER		58

/* IAP boot ROM location and access function */
#define IAP_ROM_LOCATION				0x1FFF1FF1UL
#define IAP_EXECUTE_CMD(a, b)			((void (*)())(IAP_ROM_LOCATION))(a, b)


#endif /* IAP_H_ */
