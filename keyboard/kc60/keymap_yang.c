#include "keymap_common.h"

// Yang's custom keymap based on poker3
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space            |Alt |Gui |Ctrl |Fn1 |
     * `-----------------------------------------------------------'
     */
KEYMAP_ANSI(
    FN2, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
    FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,      ENT,  \
    LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,      RSFT, \
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,RCTL, FN1),
    /* Keymap 1: Mac Default Layer
     * ,-----------------------------------------------------------.
     * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Alt |Gui |      Space            |Gui |Alt |Ctrl |Fn1 |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        FN2, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,      ENT,  \
        LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,      RSFT, \
        LCTL,LALT,LGUI,          SPC,                     RGUI,RALT,RCTL, FN1),
    /* Keymap 2: Fn0 Layer
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |     |   |Up |   |Cal|Ins|   |PgUp|  |   |Psc|Slk|Pau|     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |Lef|Dow|Up |Rig|   |   |        |
     * |-----------------------------------------------------------|
     * |        |Fn3|Fn4|Fn5|   |  |PgDn|   |VoD|Mut|VoU|          |
     * |-----------------------------------------------------------|
     * |    |    |    |Fn6                     |App |Hom |    |End |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        TRNS,TRNS,UP,  TRNS,CALC,INS ,TRNS,PGUP,TRNS, TRNS,PSCR,SLCK,PAUS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,      TRNS, \
        TRNS,     FN3, FN4, FN5, TRNS, TRNS, PGDN,TRNS,VOLD,MUTE,VOLU,    TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                     APP, HOME,TRNS,END),
    /* Keymap 3: Fn1 Layer
     * ,-----------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |
     * |-----------------------------------------------------------|
     * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |Lef|Dow|Up |Rig|   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |Up        |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Fn7 |Left|Down|Rig |
     * `-----------------------------------------------------------'
     */
    KEYMAP_ANSI(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS,TRNS,TRNS,TRNS,  \
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,      TRNS, \
        TRNS,    TRNS,TRNS,TRNS, TRNS, TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,      UP, \
        TRNS,TRNS,TRNS,         TRNS,                     FN6, LEFT,DOWN,RGHT),
};




/* id for user defined function/macro */
enum function_id {
    SHIFT_ESC,
};

enum macro_id {
    ALT_TAB,ALT_TAB2,
};


#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t shift_esc_shift_mask;

    switch (id) {
        case SHIFT_ESC:
            shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
            if (record->event.pressed) {
                if (shift_esc_shift_mask) {
                    add_key(KC_GRV);
                    send_keyboard_report();
                } else {
                    add_key(KC_ESC);
                    send_keyboard_report();
                }
            } else {
                if (shift_esc_shift_mask) {
                    del_key(KC_GRV);
                    send_keyboard_report();
                } else {
                    del_key(KC_ESC);
                    send_keyboard_report();
                }
            }
            break;
    }
}


/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case ALT_TAB:
            return (record->event.pressed ? MACRO( D(LSFT) ,T(H) , U(LSFT), T(E), T(L), T(L), T(O), END ) :MACRO( END ));
        case ALT_TAB2:
            return (record->event.pressed ? MACRO(D(LSFT),T(A),T(S),T(D),U(LSFT),T(F),T(G),T(H), END ) :MACRO( END ));

    }
    return MACRO_NONE;
}

/*
 * Fn action definition
 */

const uint16_t fn_actions[] PROGMEM = {
    /* Poker2 Layout */
    [0] = ACTION_LAYER_TAP_KEY(2, KC_CAPS),
    [1] = ACTION_LAYER_ON(3, ON_RELEASE),
    [2] = ACTION_FUNCTION(SHIFT_ESC),
    [3] = ACTION_BACKLIGHT_DECREASE(),
    [4] = ACTION_BACKLIGHT_TOGGLE(),
    [5] = ACTION_BACKLIGHT_INCREASE(),
    [6] = ACTION_LAYER_OFF(3, ON_RELEASE),
};
