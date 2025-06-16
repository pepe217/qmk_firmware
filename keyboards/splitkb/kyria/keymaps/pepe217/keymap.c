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
     TMUX_L  , KC_Q  ,  KC_Y   ,  KC_U  ,   KC_O, KC_SLSH,                                      KC_X,   KC_L ,  KC_D ,   KC_W ,  KC_Z , TMUX_L  ,
    KC_B,  MT(MOD_LGUI, KC_C),  MT(MOD_LALT, KC_I),  MT(MOD_LCTL, KC_E),  MT(MOD_LSFT, KC_A),  KC_COMM,  KC_K,   MT(MOD_RSFT, KC_H),  MT(MOD_RCTL, KC_T),  MT(MOD_RALT, KC_N),  MT(MOD_RGUI, KC_S),  KC_V,
        QK_LLCK,KC_QUOT, KC_MINUS, LT(CURSOR,KC_EQL),KC_DOT, KC_COLN, KC_ESC, KC_RBRC,                         CW_TOGG, KC_ENT, KC_J,   KC_M ,LT(SYMBOL,KC_G), KC_P ,KC_F, QK_LLCK,
        KC_LPRN, KC_RPRN, LT(CURSOR, KC_SPC), LT(NUMPAD, KC_TAB), KC_LBRC,   KC_DEL , KC_BSPC ,LT(MOUSE, KC_R), KC_LBRC, KC_RBRC
    ),
    [SYMBOL] = LAYOUT(
        KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_HASH, KC_EXLM,                   KC_GRV, KC_DEL, LSFT(KC_TAB), KC_INS, KC_ESC, KC_NO,
        KC_NO, KC_CIRC, KC_ASTR, KC_DQT, KC_DLR, KC_TILDE,                  KC_DQT, KC_BSPC, KC_TAB, KC_SPACE, KC_ENTER, KC_NO,
        KC_NO, KC_LT, KC_PIPE, KC_GRV, KC_GT, KC_AT,       TESTS  , DEVMONO,   DT_DOWN,  DT_UP ,DT_PRNT,KC_QUOT, KC_NO, AC_TOGG, KC_NO, KC_TRNS,
               KC_AMPR   , KC_BSLS,KC_PERC   ,KC_SCLN    ,SM   ,               KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
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
