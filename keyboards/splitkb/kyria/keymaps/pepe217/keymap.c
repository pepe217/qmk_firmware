#include QMK_KEYBOARD_H
#include "pepe217.h"

#define NUM_LEDS 62

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_sethsv_range (HSV_BLUE, 0, NUM_LEDS);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case ENGRAM:
        rgblight_sethsv_range (HSV_BLUE, 0, NUM_LEDS);
        break;
    case NUMPAD:
        rgblight_sethsv_range (HSV_GREEN, 0, NUM_LEDS);
        break;
    case SYMBOL:
        rgblight_sethsv_range (HSV_RED, 0, NUM_LEDS);
        break;
    case FUNCTION:
        rgblight_sethsv_range (HSV_WHITE, 0, NUM_LEDS);
        break;
    case CURSOR:
        rgblight_sethsv_range (HSV_ORANGE, 0, NUM_LEDS);
        break;
    case QWERTY:
        rgblight_sethsv_range (0x00,  0x00, 0x00, 0, NUM_LEDS);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_range (0x00,  0x00, 0x00, 0, NUM_LEDS);
        break;
    }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ENGRAM]= LAYOUT(
    OSM(MOD_LSFT), KC_Q,          KC_Y,          KC_O,          KC_U,   KC_EQL,  KC_X,  KC_L,   KC_D,          KC_W,          KC_Z,          OSM(MOD_RSFT),
    KC_BSPC,  MT(MOD_LGUI, KC_C),  MT(MOD_LALT, KC_I),  MT(MOD_LCTL, KC_A),  MT(MOD_LSFT, KC_E),  KC_MINUS,  KC_K,   MT(MOD_RSFT, KC_H),  MT(MOD_RCTL, KC_T),  MT(MOD_RALT, KC_N),  MT(MOD_RGUI, KC_S),  KC_ENT,
    KC_B,KC_QUOT, LT(NUMPAD, KC_COMM), LT(CURSOR,KC_DOT), KC_COLN, KC_SLSH, LT(FUNCTION, KC_ESC), KC_RPRN, KC_HOME, KC_END, KC_J,   KC_M ,LT(SYMBOL,KC_G), LT(MOUSE, KC_P) ,KC_V, KC_F,
        KC_PGDN, KC_DOWN, LT(CURSOR, KC_SPC), LT(NUMPAD, KC_TAB), KC_LPRN,   KC_DEL , KC_BSPC ,LT(MOUSE, KC_R), KC_UP, KC_PGUP
    ),
    [SYMBOL] = LAYOUT(
        KC_NO, KC_EXLM, KC_LCBR, KC_RCBR, KC_HASH, KC_GRV,                   KC_TILDE, OSM(MOD_RSFT), OSM(MOD_RCTL), OSM(MOD_RALT), OSM(MOD_RGUI), KC_NO,
        KC_NO, KC_CIRC, KC_LPRN, KC_RPRN, KC_DLR, KC_TILDE,              KC_DOT, KC_BSPC, KC_TAB, KC_SPACE, KC_ENTER, KC_NO,
        QK_LLCK, KC_AMPR   ,KC_LBRC, KC_RBRC, KC_PAST, KC_AT, KC_BSLS, KC_DOT, KC_NO, KC_NO,                          KC_BSLS, KC_DEL, LSFT(KC_TAB), KC_INS, KC_ESC, QK_LLCK,
               KC_NO,KC_PIPE ,KC_PERC   ,KC_SCLN    ,SM   ,               KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
    ),
    [NUMPAD] = LAYOUT(
        KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_BSPC, KC_O,                       G, KC_7, KC_8, KC_9, KC_COLN, KC_PERC,
        OSM(MOD_LSFT), KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_X,                K, KC_4, KC_5, KC_6, KC_MINS, KC_PLUS,
        KC_E, SELA, KC_NO, KC_NO, FIND, KC_F,                   KC_NO, KC_NO,                   KC_NO, KC_NO, J, KC_1, KC_2, KC_3, KC_SLSH, KC_ASTR,
                KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS,   KC_TRNS   ,KC_0   ,KC_LBRC   ,KC_RBRC
    ),
    [CURSOR] = LAYOUT(
        CG_SWAP, KC_8, KC_7, KC_6, KC_0, KC_9,                                                                   CUT, LSFT(KC_TAB), UNDO, REDO, KC_TAB, CG_NORM,
        OSM(MOD_LSFT), KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, COPY,                                                      COPY, KC_LEFT ,KC_DOWN,KC_UP , KC_RIGHT, TO(ENGRAM),
        KC_E, SELA, KC_NO, KC_NO, FIND, PASTE,                  LSFT(KC_TAB), KC_TAB,         LALT(KC_6), LALT(KC_5), PASTE, KC_HOME,KC_PGDN,KC_PGUP , KC_END, KC_NO,
                REDO   ,FINDP   ,FINDN   ,KC_TRNS   ,KC_NO   , KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS
    ),
    [MOUSE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO,       KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [FUNCTION] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO,       KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};
