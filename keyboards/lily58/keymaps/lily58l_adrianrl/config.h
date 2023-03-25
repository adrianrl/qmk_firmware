/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roesner (keycapsss.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */
#define MASTER_LEFT

#define ENCODER_RESOLUTION 3
#define ENCODER_DIRECTION_FLIP
#define SPLIT_OLED_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
#define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
#define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by
#define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#define RGBLIGHT_LAYERS

#elif RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#define RGB_MATRIX_SPLIT RGBLED_SPLIT
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10

#define RGB_MATRIX_KEYPRESSES
#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
#define DISABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#ifdef RGB_MATRIX_CUSTOM_USER
    #define RGB_MATRIX_CUSTOM_RANDOM_COLOR
#endif
#endif

#ifdef OLED_FONT_H
    #undef OLED_FONT_H
#endif
#define OLED_FONT_H "features/glcdfont_lily.c"

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
