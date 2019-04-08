#
# (C) Copyright 2013 Freescale Semiconductor, Inc.
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-y  := pixiepro.o
obj-$(CONFIG_POWER_PFUZE100)	+= ../../freescale/common/pfuze.o
obj-$(CONFIG_DM_PMIC_PFUZE100)	+= ../../freescale/common/pfuze_dm.o

ifeq ($(CONFIG_PIXIEPRO_EMMCTARGET),y)
KBUILD_CFLAGS  += -DUSE_PIXIEPRO_EMMCTARGET=1
endif

