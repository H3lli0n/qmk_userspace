/* Copyright 2023 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Myriad boilerplate
#define MYRIAD_ENABLE

/// Vial-specific settings

// Increase the EEPROM size for layout options
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

// Default is 2, needed because keymap has 7 layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define VIAL_KEYBOARD_UID {0xB3, 0x8D, 0x94, 0xDA, 0xB3, 0xD7, 0xDC, 0x3D}

#define VIAL_UNLOCK_COMBO_ROWS { 3, 9 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 5 }

// RGBs
#define RGBLIGHT_SPLIT
#define RGBLIGHT_SLEEP
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define VIAL_TAP_DANCE_ENTRIES 15

/* Luna Pet by helltm */
/* Glcdfont for layers state */
#ifdef OLED_ENABLE
#    undef OLED_FONT_H
#    define OLED_FONT_H "keyboards/splitkb/elora/keymaps/hellion/glcdfont.c"
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#    undef OLED_TIMEOUT
#    define OLED_TIMEOUT 300000
#    define OLED_UPDATE_INTERVAL 10
#    define ANIM_SIZE 32
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40
#    define ANIM_FRAME_DURATION 200
#    define PET_ROWS            3
#endif

#ifdef WPM_ENABLE
#    define SPLIT_WPM_ENABLE
#endif
