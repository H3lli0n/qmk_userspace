# SPDX-License-Identifier: GPL-2.0-or-later

ifeq ($(strip $(VIALRGB_ENABLE)), yes)
  SRC += H3lli0n.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += H3lli0n.c
endif