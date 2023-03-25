 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
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

#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "color.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight/rgblight.h"
#endif
#include "quantum/process_keycode/process_tap_dance.h"
#include "quantum/keycode.h"

extern uint8_t is_master;

enum layers {
    _QWERTY,
    _XCODE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Tap Dance declarations
enum {
    TD_LBRACKETS,
    TD_RBRACKETS,
    TD_XCQO,
};

enum custom_keycodes {
    KC_MCTRL = SAFE_RANGE,
    KC_LNCHPD,
    MACRO_XCQO, // Xcode Quick Open
};

#define XCODE TT(_XCODE)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

// #ifdef TAP_DANCE_ENABLE
// #undef TAPPING_TERM
// #define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LBRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_LBRC),
    [TD_RBRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_RCBR, KC_RBRC),
    // [TD_XCQO] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_O)))
    // [TD_XCQO] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, MACRO_XCQO),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  {   |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  }   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER| LGUI | /Space  /       \Enter \  |RAISE |BackSP| LCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,   KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
TD(TD_LBRACKETS), KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD(TD_RBRACKETS),
        KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,   KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,   KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                    KC_LALT, LOWER,  KC_LGUI, KC_SPC,   KC_ENT,   KC_BSPC, RAISE, KC_LCTL
),
/* XCODE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  {   |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  }   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER| LGUI | /Space  /       \Enter \  |RAISE |BackSP| LCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_XCODE] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER| LGUI | /Space  /       \Enter \  |RAISE |BackSP| LCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  🔅  |  🔆   |  🎛  |  🖥  |      |                    |      |  ⏪  |  ⏯  |  ⏭  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER| LGUI | /Space  /       \Enter \  |RAISE |BackSP| LCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, KC_BRID, KC_BRIU, KC_MCTRL,KC_LNCHPD, _______,                     _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |SPEED+|      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |SPEED-|      |-------|    |-------|      | MODE-| MODE+| HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LOWER| LGUI | /Space  /       \Enter \  |RAISE |BackSP| LCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,TO(_QWERTY),CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPI, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
  XXXXXXX, XXXXXXX, TG(_XCODE),    XXXXXXX, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD,RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

#ifdef RGBLIGHT_LAYERS
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_WHITE}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_PURPLE},
    {0, 6, HSV_WHITE }
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {43, 2, HSV_GREEN},
    {35, 6, HSV_ORANGE},
    {45, 6, HSV_MAGENTA}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    return state;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);

    #ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(0, layer_state_cmp(state, _ADJUST));
    #endif

    return state;
}

#include "raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);

    const uint8_t mode = data[0];

    switch (mode) {
        case 3:
            rgb_matrix_step_noeeprom();
            break;

        case 4:
            rgb_matrix_step_reverse_noeeprom();
            break;

        case 5:
            keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
            break;

        case 6:
            keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
            break;

        case 7: {
            const uint8_t cpu_load = data[2];
            const uint8_t used_ram = data[4];
            const uint8_t total_ram = data[6];
            const bool has_battery = data[11] == 10;
            char cpu_str[4];
            char used_ram_str[3];
            char total_ram_str[3];

            itoa(cpu_load, cpu_str, 10);
            itoa(used_ram, used_ram_str, 10);
            itoa(total_ram, total_ram_str, 10);

            if (is_keyboard_master()) {
                oled_clear();
                const uint8_t hour = data[8];
                const uint8_t minutes = data[10];
                char hour_str[3];
                char minutes_str[3];

                itoa(hour, hour_str, 10);
                itoa(minutes, minutes_str, 10);

                if (hour < 10) {
                    oled_write_char('0', false);
                }

                oled_write(hour_str, false);
                oled_write_char(':', false);

                if (minutes < 10) {
                    oled_write_char('0', false);
                }

                oled_write(minutes_str, false);

                if (has_battery) {
                    for (size_t i = 5; i < (OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH) - 9; i++) {
                        oled_write_char(' ', false);
                    }

                    const uint8_t percent = data[12];
                    oled_write(get_u8_str(percent, ' '), false);
                    oled_write_char((char) 37, false); // % symbol
                    oled_write_char(' ', false);
                    oled_write_char((char) data[13], false);    // battery icon left
                    oled_write_char((char) data[14], false);    // battery icon right
                    oled_write_char((char) data[15], false);    // bolt if charging
                }

                oled_advance_page(true);
                oled_advance_page(true);
                oled_write_P(PSTR("CPU "), false);
                oled_write(get_u8_str(cpu_load, ' '), false);
                oled_write_char((char) 37, false); // % symbol
                oled_write_P(PSTR("   RAM "), false);
                oled_write(used_ram_str, false);
                oled_write_P(PSTR("/"), false);
                oled_write_ln(total_ram_str, false);
            }

            break;
        }

        default:
            break;
    }

    update_tri_layer_state(layer_state, _RAISE, _LOWER, _ADJUST);
}

const char *on_render_layer_state(layer_state_t layer) {
    switch (get_highest_layer(layer)) {
        case _QWERTY:
            return PSTR("QRTY");
        case _LOWER:
            return PSTR("LOW");
        case _RAISE:
            return PSTR("HIGH");
        case _ADJUST:
            return PSTR("ADJ");
        case _XCODE:
            return PSTR("XCODE");
        default:
            return PSTR("Undefined");
    }
}

void on_render_status_main(void) {}
void on_render_status_secondary(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_MCTRL:
        if (record->event.pressed) {
            host_consumer_send(0x29F);
        } else {
            host_consumer_send(0);
        }

        return false;

    case KC_LNCHPD:
        if (record->event.pressed) {
            host_consumer_send(0x2A0);
        } else {
            host_consumer_send(0);
        }

        return false;

    case KC_RSFT:
        if (get_highest_layer(layer_state) == _XCODE) {
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_O));
                wait_ms(250);
            } else {
                clear_keyboard();
            }

            return false;
        }

    case KC_3:
        if (get_highest_layer(layer_state) == _RAISE) {
            if (record->event.pressed) {
            } else {
                clear_keyboard();
            }

            return false;
        }

    case KC_4:
        if (get_highest_layer(layer_state) == _RAISE) {
            if (record->event.pressed) {
            } else {
                clear_keyboard();
            }

            return false;
        }

    case KC_F5: case KC_F6:
        if (get_highest_layer(layer_state) == _RAISE) {
            if (record->event.pressed) {
                if (keycode == KC_F6) {
                    SEND_STRING("public func <#name#>(<#params#>) {\n<#code#>");
                } else {
                    SEND_STRING("func <#name#>(<#params#>) {\n<#code#>");
                }

                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_TAB));
                clear_keyboard();
            } else {
                clear_keyboard();
            }

            return false;
        }
    }

    return true;
}

void set_backlight_color(uint8_t led_min, uint8_t led_max, RGB rgb) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
HSV current_backlight = { 0, 0, 255 };
uint8_t rgb_max_value = 150;
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t matrix_val = rgb_matrix_get_val();

    if (matrix_val > 0) {
        matrix_val = (matrix_val + 32) > rgb_max_value ? rgb_max_value : matrix_val + 32;
    }

    HSV hsv = { 0, 0, matrix_val };

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case _QWERTY:
            // HSV_WHITE
            hsv.h = 0;
            hsv.s = 0;
            set_backlight_color(led_min, led_max, hsv_to_rgb(hsv));
            break;

        case _XCODE:
            // HSV_BLUE
            hsv.h = 170;
            hsv.s = 255;
            set_backlight_color(led_min, led_max, hsv_to_rgb(hsv));
            break;

        default: {
            hsv.h = current_backlight.h;
            hsv.s = current_backlight.s;

            set_backlight_color(led_min, led_max, hsv_to_rgb(hsv));
            break;
        }
    }

    current_backlight.h = hsv.h;
    current_backlight.s = hsv.s;
    current_backlight.v = matrix_val;

    return true;
}

// Rotary encoder related code
void on_master_encoder_update(bool clockwise) {
    if (IS_LAYER_ON(_RAISE)) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

void on_slave_encoder_update(bool clockwise) {
    if (IS_LAYER_ON(_LOWER)) {
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}
