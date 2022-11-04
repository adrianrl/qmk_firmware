/*
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

#include "lily58.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{
    // Key Matrix to LED Index

    // Left side
    { 11, 10,  9,  8,  7,  6 },
    { 12, 13, 14, 15, 16, 17 },
    { 23, 22, 21, 20, 19, 18 },
    { 24, 25, 26, 27, 28, 29 },
    { NO_LED, 34, 33, 32, 31, 30 },

    // Right side
    { 46, 45, 44, 43, 42, 41 },
    { 47, 48, 49, 50, 51, 52 },
    { 58, 57, 56, 55, 54, 53 },
    { 59, 60, 61, 62, 63, 64 },
    { NO_LED, 69, 68, 67, 66, 65 }
}, {
    // LED Index to Physical Position

    // Left side
    // Underglow
    { 85, 8 },               { 51, 6 },              { 17, 12 },
    { 17, 47 },              { 51, 54 },             { 85, 59 },

    // Matrix
    { 85, 5 },  { 68, 3 },   { 51, 0 },  { 34, 3 },  { 17, 7 },  { 0, 8 },
    { 0, 24 },  { 17, 23 },  { 34, 19 }, { 51, 16 }, { 68, 19 }, { 85, 21 },
    { 85, 37 }, { 68, 35 },  { 51, 32 }, { 34, 35 }, { 17, 39 }, { 0, 40 },
    { 0, 56 },  { 17, 55 },  { 34, 51 }, { 51, 48 }, { 68, 51 }, { 85, 53 },
    { 96, 45 }, { 102, 64 }, { 77, 66 }, { 59, 64 }, { 42, 64 },

    // Right side
    // Underglow
    { 136, 8 },               { 170, 6 },               { 204, 12 },
    { 204, 48 },              { 170, 48 },              { 136, 48 },

    // Matrix
    { 136, 5 },  { 153, 3 },  { 170, 0 },  { 187, 3 },  { 204, 7 },  { 221, 8 },
    { 221, 24 }, { 204, 23 }, { 187, 19 }, { 170, 16 }, { 153, 19 }, { 136, 21 },
    { 136, 37 }, { 153, 35 }, { 170, 32 }, { 187, 35 }, { 204, 39 }, { 221, 40 },
    { 221, 56 }, { 204, 55 }, { 187, 51 }, { 170, 48 }, { 153, 51 }, { 136, 53 },
    { 119, 45 }, { 113, 64 }, { 145, 66 }, { 162, 64 }, { 179, 64 }
}, {
    // LED Index to Flag

    // Left side
    2, 2, 2, 2, 2, 2,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 1, 1, 1, 1,

    // Right side
    2, 2, 2, 2, 2, 2,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 1, 1, 1, 1,
}};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
