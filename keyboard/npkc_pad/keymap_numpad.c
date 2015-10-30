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
        FN0,  FN1,  FN2,  PMNS, \
        P7,   P8,   P9,   PPLS, \
        P4,   P5,   P6,         \
        P1,   P2,   P3,   PENT, \
        P0,         PDOT        \
    ),
};
const uint16_t PROGMEM fn_actions[] PROGMEM = {
  [0] = ACTION_BACKLIGHT_INCREASE(),
  [1] = ACTION_BACKLIGHT_DECREASE(),
  [2] = ACTION_BACKLIGHT_TOGGLE(),
};
