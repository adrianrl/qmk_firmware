#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void on_master_encoder_update(bool clockwise);
void on_slave_encoder_update(bool clockwise);

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        on_master_encoder_update(clockwise);
    } else {
        on_slave_encoder_update(clockwise);
    }

    return true;
}
