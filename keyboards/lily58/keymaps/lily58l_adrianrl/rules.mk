BOOTLOADER = atmel-dfu  # Puchi-C

EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
WPM_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
SPLIT_TRANSPORT = mirror
RAW_ENABLE = yes
SPLIT_KEYBOARD = yes
RGB_MATRIX_CUSTOM_USER = yes
MOUSEKEY_ENABLE = no

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += features/oled.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += features/encoder.c
endif
