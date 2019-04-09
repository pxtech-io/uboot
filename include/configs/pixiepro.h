/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for PixiePro board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __PIXIEPRO_CONFIG_H
#define __PIXIEPRO_CONFIG_H

#define CONFIG_MACH_TYPE	3529
#define CONFIG_MXC_UART_BASE	UART4_BASE
#define CONSOLE_DEV				"ttymxc3"
#ifndef CONFIG_DEFAULT_FDT_FILE
#define CONFIG_DEFAULT_FDT_FILE	"/boot/imx6-pixiepro.dtb"
#endif
#define CONFIG_MMCROOT			"/dev/mmcblk2p2"

#ifdef PHYS_SDRAM_SIZE
#undef PHYS_SDRAM_SIZE
#endif

#if defined(CONFIG_MX6QP)
#ifdef  CONFIG_TARGET_PIXIEPRO_4G
#define PHYS_SDRAM_SIZE		(3840ul * 1024 * 1024)
#else
#define PHYS_SDRAM_SIZE		(2u * 1024 * 1024 * 1024)
#endif
#elif defined(CONFIG_MX6Q)
#define PHYS_SDRAM_SIZE		(2u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6DL)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6SOLO)
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#endif


#ifdef CONFIG_USB
/* USB Configs */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET	/* For OTG port */
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS	0
#endif

#include "imx6pixiepro_common.h"

#define CONFIG_SYS_FSL_USDHC_NUM	2
#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_OFFSET (896 * 1024)
#endif


/* NAND flash command */
#ifdef  CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_TRIMFFS

/* NAND stuff */
#define CONFIG_NAND_MXS
#define CONFIG_SYS_MAX_NAND_DEVICE     1
#define CONFIG_SYS_NAND_BASE           0x40000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION

/* DMA stuff, needed for GPMI/MXS NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8
#endif
#endif


