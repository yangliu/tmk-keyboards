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
      NLCK, PSLS, PAST, PMNS, \
      P7,   P8,   P9,   PPLS, \
      P4,   P5,   P6,         \
      P1,   P2,   P3,   PENT, \
      FN0,         PDOT       \
    ),
    KEYMAP( \
      FN12, FN13, FN14, FN15, \
      FN21, UP,   FN19, FN18, \
      LEFT, DOWN, RGHT,       \
      VOLD, MUTE, VOLU, FN17, \
      FN31,       FN20        \
    ),
    KEYMAP( \
      FN12, FN13, FN14, NO,   \
      NO,   UP,   NO,   PGUP, \
      LEFT, DOWN, RGHT,       \
      HOME, NO,   END,  PGDN, \
      FN31,       FN15        \
    ),
    KEYMAP( \
      BTN1, BTN3, BTN2, NO,   \
      NO,   MS_U, NO,   WH_U, \
      MS_L, MS_D, MS_R,       \
      WH_L, NO,   WH_R,  WH_D,\
      FN31,       NO          \
    ),

    KEYMAP( \
      FN1,  FN2,  FN3,  FN4, \
      NO,   NO,   NO,   FN18,\
      FN5,  FN6,  FN7,       \
      NO,   NO,   NO,   FN17,\
      FN31,       FN11       \
    ),

};
const uint16_t PROGMEM fn_actions[] PROGMEM = {
  [0]  = ACTION_LAYER_TAP_KEY(4, KC_P0),
  [1]  = ACTION_LAYER_SET(0, ON_RELEASE),
  [2]  = ACTION_LAYER_SET(1, ON_RELEASE),
  [3]  = ACTION_LAYER_SET(2, ON_RELEASE),
  [4]  = ACTION_LAYER_SET(3, ON_RELEASE),
  [5]  = ACTION_BACKLIGHT_DECREASE(),
  [6]  = ACTION_BACKLIGHT_TOGGLE(),
  [7]  = ACTION_BACKLIGHT_INCREASE(),
  [8]  = ACTION_NO,
  [9]  = ACTION_NO,
  [10] = ACTION_NO,
  [11] = ACTION_MODS_KEY(MOD_LALT, KC_L),
  [12] = ACTION_MODS_KEY(MOD_LGUI, KC_X),
  [13] = ACTION_MODS_KEY(MOD_LGUI, KC_C),
  [14] = ACTION_MODS_KEY(MOD_LGUI, KC_V),
  [15] = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_V),
  [16] = ACTION_MODS_KEY(MOD_LGUI, KC_S),
  [17] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_P),
  [18] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_LEFT),
  [19] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_RGHT),
  [20] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT | MOD_LALT, KC_L),
  [21] = ACTION_MODS_KEY(MOD_LCTL, KC_UP),
  [22] = ACTION_NO,
  [23] = ACTION_NO,
  [24] = ACTION_NO,
  [25] = ACTION_NO,
  [26] = ACTION_NO,
  [27] = ACTION_NO,
  [28] = ACTION_NO,
  [29] = ACTION_NO,
  [30] = ACTION_NO,
  [31] = ACTION_LAYER_MOMENTARY(4),

};
