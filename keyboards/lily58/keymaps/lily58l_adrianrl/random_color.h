#include "quantum/rgb_matrix/rgb_matrix.h"

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(random_color)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

HSV random_rgb_matrix[RGBLED_NUM] = {};

static bool random_color(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        uint8_t matrix_sat = rgb_matrix_get_sat();
        uint8_t matrix_val = rgb_matrix_get_val();

        srand(timer_read());

        for (uint8_t i = led_min; i < RGBLED_NUM; i++) {
            HSV hsv = {rand() % 256, matrix_sat, matrix_val};
            random_rgb_matrix[i] = hsv;
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }

        return rgb_matrix_check_finished_leds(RGBLED_NUM);
    }

    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
    srand(timer_read());

    for (uint8_t i = led_min; i < RGBLED_NUM; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
        HSV hsv = random_rgb_matrix[i];
        hsv.h += qsub8(rand() % 128, offset);
        hsv.s = rgb_matrix_get_sat();
        hsv.v = rgb_matrix_get_val();
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        random_rgb_matrix[i] = hsv;
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(RGBLED_NUM);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif //RGB_MATRIX_KEYREACTIVE_ENABLED
