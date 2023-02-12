#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdlib.h>
#include "drivers/oled/oled_driver.h"
#include "quantum/quantum_keycodes.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_270;
    }
}

const char *on_render_layer_state(layer_state_t layer);
void on_render_status_main(void);
void on_render_status_secondary(void);

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_ln_P(on_render_layer_state(layer_state), false);
}

void render_keylock_status(led_t led_state) {
    oled_write_ln_P(PSTR("Lock"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_logo(void) {
}

void render_status_secondary(void) {
    render_logo();
    on_render_status_secondary();
}

void render_status_main(void) {
    // Show keyboard layout
    render_default_layer_state();
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show host keyboard led status
    render_keylock_status(host_keyboard_led_state());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show modifier status
    render_mod_status(get_mods());
    on_render_status_main();

#ifdef WPM_ENABLE
    oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("WPM"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status_secondary();
    } else {
        render_status_main();
    }

    return false;
}
