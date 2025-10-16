// Copyright 2025 HLB
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
    _MEDIA,
    _GAME,
    _MAC
};

enum hlbKeycodes {
    LAY_INDIC_RGB = QK_KB_0,
};

/* Data structure*/
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} kb_config_t;

/* Predefined colors */
const hsv_t OFF_COLOR = {HSV_OFF};
const hsv_t CONF_CHANGED_COLOR = {HSV_WHITE};
const hsv_t LAYER_FN_COLOR = {HSV_PURPLE};
const hsv_t LAYER_MEDIA_COLOR = {HSV_ORANGE};
const hsv_t LAYER_GAMING_COLOR = {HSV_CYAN};
const hsv_t LAYER_MAC_COLOR = {HSV_RED};
const hsv_t LAYER_INDIC_COLOR = {HSV_WHITE};
const hsv_t CAPS_INDIC_COLOR = {HSV_GREEN};

/* Feature toggle blink duration */
const uint16_t RGB_BLINK_DURATION = 1000;
const uint8_t RGB_INDICATOR_LED_IDX = 18;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// main layer
[_BASE] = LAYOUT_all(
  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,       KC_6,      KC_7,      KC_8,      KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,       KC_Y,      KC_U,      KC_I,      KC_O,       KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,       KC_H,      KC_J,      KC_K,      KC_L,       KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
  KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,       KC_B,      KC_N,      KC_M,      KC_COMM,    KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
  KC_LCTL,  KC_LGUI,  KC_LALT,            KC_SPC,               KC_SPC,               KC_SPC,                KC_RALT, KC_RGUI, KC_RCTL),

// basic function layer
[_FN] = LAYOUT_all(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,   KC_TRNS,   KC_HOME,   KC_UP,     KC_END,      KC_PGUP,  KC_VOLU,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_TRNS,   KC_TRNS,   KC_LEFT,   KC_DOWN,   KC_RIGHT,    KC_PGDN,  KC_VOLD,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_PSCR,  KC_MUTE,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,              KC_TRNS,              KC_TRNS,               MO(2),    KC_TRNS, KC_TRNS),

// rgb/media layer
[_MEDIA] = LAYOUT_all(
  KC_TRNS,  KC_MPRV,  KC_MNXT,  KC_MPLY,  KC_VOLU,   KC_VOLD,   KC_MUTE,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
  RM_TOGG,  RM_NEXT,  RM_HUEU,  RM_SATU,  RM_SPDU,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  RM_PREV, RM_HUED,  RM_SATD,  RM_SPDD,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS,  RM_VALU,  RM_VALD,  KC_TRNS,   KC_TRNS,   QK_BOOT,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,              KC_TRNS,              KC_TRNS,               KC_TRNS,  KC_TRNS, KC_TRNS),
};

/* keyboard preference */
kb_config_t kb_config;

/* handling user indicator mode change */
uint8_t layerIndicatorChanged = 0;

/* Managing RGB leds and preferences */

/* Initial data container */
void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  kb_config.raw = 0;
  kb_config.rgb_layer_change = false; // We want this enabled by default
  eeconfig_update_kb(kb_config.raw); // Write default value to EEPROM now
}

/* Read indicator preference */
void keyboard_post_init_kb(void) {
    // Read the user config from EEPROM
    kb_config.raw = eeconfig_read_kb();
}

/* Activate LED for indicator */
void keyboard_pre_init_kb(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    keyboard_pre_init_user();
}

/* Update user preference on layer indicator*/
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_user(keycode, record);

    switch (keycode) {
    case LAY_INDIC_RGB:
      if (record->event.pressed) {
        kb_config.rgb_layer_change ^= 1; // Toggles the status
        eeconfig_update_kb(kb_config.raw); // Writes the new status to EEPROM

        //We need a led status update
        layerIndicatorChanged = 1;
      }
      return false; // Skip all further processing of this key

    default:
      return true; // Process all other keycodes normally
  }
}

/* Managing indicator color based on state and layer */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //default
    rgb_t rgbValue = hsv_to_rgb(OFF_COLOR);

    //Handling user mode toggle by updating indicator LED for few seconds
    if (layerIndicatorChanged == 1){
        //White color to warm
        rgb_t rgbValue = hsv_to_rgb(CONF_CHANGED_COLOR);
        RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
        //Few seconds before getting back to normal
        wait_ms(RGB_BLINK_DURATION);
        //Default state
        rgbValue = hsv_to_rgb(OFF_COLOR);
        RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
        //Done
        layerIndicatorChanged = 0;
    }

    //Capslock
    if (host_keyboard_led_state().caps_lock) {
        rgbValue = hsv_to_rgb(CAPS_INDIC_COLOR);
    } else if(kb_config.rgb_layer_change) {
        //Color depending current activated layer
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _FN:
                rgbValue = hsv_to_rgb(LAYER_FN_COLOR);
                break;
            case _MEDIA:
                rgbValue = hsv_to_rgb(LAYER_MEDIA_COLOR);
                break;
            case _GAME:
                rgbValue = hsv_to_rgb(LAYER_GAMING_COLOR);
                break;
            case _MAC:
                rgbValue = hsv_to_rgb(LAYER_MAC_COLOR);
                break;
            default:
                break;
        }
    }

    //Update indicator LED
    RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
    return false;
}
