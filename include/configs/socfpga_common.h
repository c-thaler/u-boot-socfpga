/*
 * Copyright (C) 2012 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_SOCFPGA_CYCLONE5_COMMON_H__
#define __CONFIG_SOCFPGA_CYCLONE5_COMMON_H__

#define CONFIG_SYS_GENERIC_BOARD

/* Virtual target or real hardware */
#undef CONFIG_SOCFPGA_VIRTUAL_TARGET

#define CONFIG_ARMV7
#define CONFIG_SYS_THUMB_BUILD

#define CONFIG_SOCFPGA

/*
 * High level configuration
 */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_MISC_INIT_R
#define CONFIG_SYS_NO_FLASH
#define CONFIG_CLOCKS

#define CONFIG_FIT
#define CONFIG_OF_LIBFDT
#define CONFIG_SYS_BOOTMAPSZ		(64 * 1024 * 1024)

#define CONFIG_TIMESTAMP		/* Print image info with timestamp */

/*
 * Memory configurations
 */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0x0
#define CONFIG_SYS_MALLOC_LEN		(10 * 1024 * 1024)
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		PHYS_SDRAM_1_SIZE

#define CONFIG_SYS_INIT_RAM_ADDR	0xFFFF0000
#define CONFIG_SYS_INIT_RAM_SIZE	(0x10000 - 0x100)
#define CONFIG_SYS_INIT_SP_ADDR					\
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_RAM_SIZE -	\
	GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#ifdef CONFIG_SOCFPGA_VIRTUAL_TARGET
#define CONFIG_SYS_TEXT_BASE		0x08000040
#else
#define CONFIG_SYS_TEXT_BASE		0x01000040
#endif

/*
 * U-Boot general configurations
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O buffer size */
#define CONFIG_SYS_PBSIZE	\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
						/* Print buffer size */
#define CONFIG_SYS_MAXARGS	32		/* Max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
						/* Boot argument buffer size */
#define CONFIG_VERSION_VARIABLE			/* U-BOOT version */
#define CONFIG_AUTO_COMPLETE			/* Command auto complete */
#define CONFIG_CMDLINE_EDITING			/* Command history etc */
#define CONFIG_SYS_HUSH_PARSER

/*
 * Cache
 */
#define CONFIG_SYS_ARM_CACHE_WRITEALLOC
#define CONFIG_SYS_CACHELINE_SIZE 32
#define CONFIG_SYS_L2_PL310
#define CONFIG_SYS_PL310_BASE		SOCFPGA_MPUL2_ADDRESS

/*
 * Ethernet on SoC (EMAC)
 */
#if defined(CONFIG_CMD_NET) && !defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)
#define CONFIG_DESIGNWARE_ETH
#define CONFIG_NET_MULTI
#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_MII
#define CONFIG_AUTONEG_TIMEOUT		(15 * CONFIG_SYS_HZ)
#define CONFIG_PHYLIB
#define CONFIG_PHY_GIGE
#endif

/*
 * FPGA Driver
 */
#ifdef CONFIG_CMD_FPGA
#define CONFIG_FPGA
#define CONFIG_FPGA_ALTERA
#define CONFIG_FPGA_SOCFPGA
#define CONFIG_FPGA_COUNT		1
#endif

/*
 * L4 OSC1 Timer 0
 */
/* This timer uses eosc1, whose clock frequency is fixed at any condition. */
#define CONFIG_SYS_TIMERBASE		SOCFPGA_OSC1TIMER0_ADDRESS
#define CONFIG_SYS_TIMER_COUNTS_DOWN
#define CONFIG_SYS_TIMER_COUNTER	(CONFIG_SYS_TIMERBASE + 0x4)
#ifdef CONFIG_SOCFPGA_VIRTUAL_TARGET
#define CONFIG_SYS_TIMER_RATE		2400000
#else
#define CONFIG_SYS_TIMER_RATE		25000000
#endif

/*
 * L4 Watchdog
 */
#ifdef CONFIG_HW_WATCHDOG
#define CONFIG_DESIGNWARE_WATCHDOG
#define CONFIG_DW_WDT_BASE		SOCFPGA_L4WD0_ADDRESS
#define CONFIG_DW_WDT_CLOCK_KHZ		25000
#define CONFIG_HW_WATCHDOG_TIMEOUT_MS	12000
#endif

/*
 * MMC Driver
 */
#ifdef CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_GENERIC_MMC
#define CONFIG_DWMMC
#define CONFIG_SOCFPGA_DWMMC
#define CONFIG_SOCFPGA_DWMMC_FIFO_DEPTH	1024
#define CONFIG_SOCFPGA_DWMMC_DRVSEL	3
#define CONFIG_SOCFPGA_DWMMC_SMPSEL	0
/* FIXME */
/* using smaller max blk cnt to avoid flooding the limited stack we have */
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	256	/* FIXME -- SPL only? */
#define CONFIG_PL330_DMA
#endif

/*
 * Serial Driver
 */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#define CONFIG_SYS_NS16550_COM1		SOCFPGA_UART0_ADDRESS
#ifdef CONFIG_SOCFPGA_VIRTUAL_TARGET
#define CONFIG_SYS_NS16550_CLK		1000000
#else
#define CONFIG_SYS_NS16550_CLK		100000000
#endif
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200

/*
 * U-Boot environment
 */
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_SYS_CONSOLE_ENV_OVERWRITE
#define CONFIG_ENV_SIZE			4096

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0/* device 0 */
#define CONFIG_ENV_OFFSET		512/* just after the MBR */


/*
 * SPL
 */
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SPL_RAM_DEVICE
#define CONFIG_SPL_TEXT_BASE		0xFFFF0000
#define CONFIG_SPL_STACK		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SPL_MALLOC_SIZE		(5 * 1024)	/* FIXME */
#define CONFIG_SYS_SPL_MALLOC_START	((unsigned long) (&__malloc_start))
#define CONFIG_SYS_SPL_MALLOC_SIZE	(&__malloc_end - &__malloc_start)
/* SPL max size */
#define CONFIG_SPL_MAX_SIZE		(64 * 1024)

#define CHUNKSZ_CRC32			(1 * 1024)	/* FIXME: ewww */
#define CONFIG_CRC32_VERIFY

/* Linker script for SPL */
#define CONFIG_SPL_LDSCRIPT	"arch/arm/cpu/armv7/socfpga/u-boot-spl.lds"

#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT

#ifdef CONFIG_SPL_BUILD
#undef CONFIG_PARTITIONS
#endif

/*
 * Support for FAT partition if boot from SDMMC
 */
#if (CONFIG_PRELOADER_BOOT_FROM_SDMMC == 1 && CONFIG_PRELOADER_FAT_SUPPORT == 1)
/* MMC with FAT partition support */
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_FS_FAT
#endif

/*
 * Enable memory padding in case SDRAM ECC is enabled
 */
#define CONFIG_SPL_SDRAM_ECC_PADDING	32

/* Stack size for SPL */
#ifdef CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_STACK_SIZE		(5 * 1024)
/*
 * New stack size which located within SDRAM after SDRAM is available.
 * FYI, 128kB stack can support fatload up to 7MB bootloader image
 */
#define CONFIG_SPL_SDRAM_STACK_SIZE	(128 * 1024)
#else
#define CONFIG_SPL_STACK_SIZ		(4 * 1024)
#endif


#endif	/* __CONFIG_SOCFPGA_CYCLONE5_COMMON_H__ */
