#include QMK_KEYBOARD_H
#include "pepe217.h"

enum layers {
    ENGRAM= 0,
    SYMBOL,
    NUMBER,
    FKEYS,
    CURSOR,
}

// tmux leader key
#define TMUX_L  LTCL(KC_B)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ENGRAM]= LAYOUT(
     ALT_TAB, KC_Q  ,  KC_Y   ,  LT(CURSOR, KC_O)  ,   KC_U ,   KC_COLN,                                      KC_X,   KC_L ,  LT(SYMBOL,KC_D) ,   KC_W ,  KC_Z , CTL_TAB,
    KC_B,  MT(MOD_LGUI, KC_C),  MT(MOD_LALT, KC_I),  MT(MOD_LCTL, KC_E),  MT(MOD_LSFT, KC_A),  KC_COMM,  KC_K,   MT(MOD_RSFT, KC_H),  MT(MOD_RCTL, KC_T),  MT(MOD_RALT, KC_N),  MT(MOD_RGUI, KC_S),  KC_V,
     TMUX_L  ,KC_QUOT,KC_MINUS ,  KC_EQL, KC_DOT ,   KC_SLSH,  KC_ESC, CW_TOGG,     KC_DEL  , KC_ENT, KC_J,   KC_M ,KC_G, KC_P ,KC_F, TMUX_L,
                               KC_LBRC, KC_RBRC, KC_SPC , KC_TAB   , TG(NUMBER),     TG(FKEYS)    , KC_BSPC ,KC_R, KC_LPRN, KC_RPRN
    ),
    [SYMBOL] = LAYOUT(
        KC_EXLM, KC_COMM, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUES,                 KC_SCLN, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_NO,
        KC_HASH, KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR, KC_ASTR,             KC_DOT, KC_BSPC, KC_TAB, KC_SPACE, KC_ENTER, KC_NO,
    KC_TILDE, KC_LT, KC_PIPE, KC_MINUS, KC_GT, KC_AT,                                                                      KC_BSLS, KC_DEL, LSFT(KC_TAB), KC_NO, KC_NO, KC_NO,

    ),
    [CURSOR] = LAYOUT(
        LGUI(KC_1), KC_8, KC_7, KC_6, KC_0, KC_9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LGUI(KC_2), KC_4, KC_3, KC_2, KC_1, KC_5, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, KC_NO,
        LGUI(KC_3), LCTL(KC_4), LCTL(KC_3), LCTL(KC_2), LCTL(KC_1), LCTL(KC_5), KC_NO, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_NO,
    ),
};
