/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for PixiePro board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX6QPIXIEPRO_COMMON_CONFIG_H
#define __MX6QPIXIEPRO_COMMON_CONFIG_H

#include "mx6_common.h"

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_SYS_GENERIC_BOARD

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(10 * SZ_1M)

#define CONFIG_BOARD_LATE_INIT

#define CONFIG_MXC_UART

#if defined(CONFIG_CMD_FUSE) || defined(CONFIG_IMX6_THERMAL)
#define CONFIG_MXC_OCOTP
#endif

/* MMC Configs */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR      0

#define CONFIG_BOUNCE_BUFFER

#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#ifdef CONFIG_DM_ETH
#define CONFIG_ETHPRIME			"eth0"
#else
#define CONFIG_ETHPRIME			"FEC"
#endif
#define CONFIG_FEC_MXC_PHYADDR		1

#define CONFIG_PHYLIB
#define CONFIG_PHY_ATHEROS

/* I2C Configs */
#ifndef CONFIG_DM_I2C
#define CONFIG_SYS_I2C
#endif
#ifdef CONFIG_CMD_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_I2C_SPEED		100000
#endif

/* PMIC */
#ifndef CONFIG_DM_PMIC
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08
#endif

#ifdef CONFIG_CMD_SF
#define CONFIG_MXC_SPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED		20000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#endif

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX              1
#define CONFIG_BAUDRATE                        115200

/* Command definition */

#undef CONFIG_CMD_IMLS

#ifdef CONFIG_BOOTDELAY
#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY               1
#endif 

#ifdef CONFIG_LOADADDR
#undef CONFIG_LOADADDR
#define CONFIG_LOADADDR                0x10008000
#endif


#ifdef CONFIG_SUPPORT_EMMC_BOOT
#define EMMC_ENV \
	"emmcdev=2\0" \
	"update_emmc_firmware=" \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"if ${get_cmd} ${update_sd_firmware_filename}; then " \
			"if mmc dev ${emmcdev} 1; then "	\
				"setexpr fw_sz ${filesize} / 0x200; " \
				"setexpr fw_sz ${fw_sz} + 1; "	\
				"mmc write ${loadaddr} 0x2 ${fw_sz}; " \
			"fi; "	\
		"fi\0"
#else
#define EMMC_ENV ""
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=/boot/boot.scr\0" \
	"image=/boot/zImage\0" \
	"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"fdt_addr=0x12000000\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"console=" CONSOLE_DEV "\0" \
	"fdt_high=0xffffffff\0"	  \
	"initrd_high=0xffffffff\0" \
	"vmalloc_size=200M\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=2\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	"update_sd_firmware=" \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"if mmc dev ${mmcdev}; then "	\
			"if ${get_cmd} ${update_sd_firmware_filename}; then " \
				"setexpr fw_sz ${filesize} / 0x200; " \
				"setexpr fw_sz ${fw_sz} + 1; "	\
				"mmc write ${loadaddr} 0x2 ${fw_sz}; " \
			"fi; "	\
		"fi\0" \
	EMMC_ENV	  \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot} vmalloc=${vmalloc_size}\0 " \
	"loadbootscript=" \
		"ext4load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=ext4load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=ext4load mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0"

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev};" \
	"if mmc rescan; then " \
		"if run loadbootscript; then " \
		"run bootscript; " \
		"else " \
			"if run loadimage; then " \
				"run mmcboot; " \
			"else run netboot; " \
			"fi; " \
		"fi; " \
	"else run netboot; fi"

#define CONFIG_ARP_TIMEOUT     200UL

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT_HUSH_PS2     "> "
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START       0x10000000
#define CONFIG_SYS_MEMTEST_END         0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH     0x10800000

#define CONFIG_SYS_LOAD_ADDR           CONFIG_LOADADDR


/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS           1
#define PHYS_SDRAM                     MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE          PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
 
#define CONFIG_ENV_SIZE			(8 * 1024)

#ifndef CONFIG_SYS_DCACHE_OFF
#endif

#ifndef CONFIG_SPL
#define CONFIG_USBD_HS

#ifndef CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#endif
#define CONFIG_USB_GADGET_VBUS_DRAW	2




/* USB Device Firmware Update support */

#endif

#endif                         /* __MX6QPIXIEPRO_COMMON_CONFIG_H */
