/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-3-03       FYChou       First version
*
******************************************************************************/

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

/* ===================== Flash device Configuration ========================= */
#if defined(RT_USING_SFUD)
extern struct fal_flash_dev nor_flash0;

/* -flash device table------------------------------------------------------- */
#define FAL_FLASH_DEV_TABLE                                                    \
{                                                                              \
    &nor_flash0,                                                               \
}
#else
#define FAL_FLASH_DEV_TABLE                                                    \
{                                                                              \
    0                                                                          \
}
#endif

/* ====================== Partition Configuration ============================ */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table------------------------------------------------------------ */
#define FAL_PART_TABLE                                                         \
{                                                                              \
    {FAL_PART_MAGIC_WORD, "preload",    FAL_USING_NOR_FLASH_DEV_NAME,            0, 4*1024*1024,  0}, \
    {FAL_PART_MAGIC_WORD, "rtthread0",  FAL_USING_NOR_FLASH_DEV_NAME, 4*1024*1024,  4*1024*1024,  0}, \
    {FAL_PART_MAGIC_WORD, "rtthread1",  FAL_USING_NOR_FLASH_DEV_NAME, 8*1024*1024,  4*1024*1024,  0}, \
    {FAL_PART_MAGIC_WORD, "filesystem", FAL_USING_NOR_FLASH_DEV_NAME, 12*1024*1024, 20*1024*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
