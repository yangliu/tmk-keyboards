#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    // KEYMAP( \
    //     NLCK, PSLS, PAST, PMNS, \
    //     P7,   P8,   P9,   PPLS, \
    //     P4,   P5,   P6,         \
    //     P1,   P2,   P3,   PENT, \
    //     P0,         PDOT        \
    // ),
    KEYMAP( \
        FN0,  PSLS,  PAST,  PMNS, \
        P7,   P8,   P9,   PPLS, \
        P4,   P5,   P6,         \
        P1,   P2,   P3,   PENT, \
        P0,         PDOT        \
    ),
    KEYMAP( \
        TRNS,  FN1,  FN2,  FN3, \
        FN4,   FN5,   FN6,   FN7, \
        FN8,   FN9,   FN10,         \
        FN11,   FN12,   FN13,   FN14, \
        FN15,         FN16        \
    ),
};
const uint16_t PROGMEM fn_actions[] PROGMEM = {
  [0] = ACTION_LAYER_MOMENTARY(1),
  [1] = ACTION_BACKLIGHT_INCREASE(),
  [2] = ACTION_BACKLIGHT_DECREASE(),
  [3] = ACTION_BACKLIGHT_TOGGLE(),
  [4] = ACTION_BACKLIGHT_TOGGLE(),
  [5] = ACTION_BACKLIGHT_TOGGLE(),
  [6] = ACTION_BACKLIGHT_TOGGLE(),
  [7] = ACTION_BACKLIGHT_TOGGLE(),
  [8] = ACTION_BACKLIGHT_TOGGLE(),
  [9] = ACTION_BACKLIGHT_TOGGLE(),
  [10] = ACTION_BACKLIGHT_TOGGLE(),
  [11] = ACTION_BACKLIGHT_TOGGLE(),
  [12] = ACTION_BACKLIGHT_TOGGLE(),
  [13] = ACTION_BACKLIGHT_TOGGLE(),
  [14] = ACTION_BACKLIGHT_TOGGLE(),
  [15] = ACTION_BACKLIGHT_TOGGLE(),
  [16] = ACTION_BACKLIGHT_TOGGLE(),

};
