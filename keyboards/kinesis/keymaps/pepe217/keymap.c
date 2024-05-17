// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "pepe217.h"

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_sethsv_range(0, 0, 0, 0, 4);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case ENGRAM:
        rgblight_sethsv_at (0x00,  0x00, 0x00, 3);
        break;
    case NUMPAD:
        rgblight_sethsv_at (HSV_GREEN, 3);
        break;
    case SYMBOL:
        rgblight_sethsv_at (HSV_RED, 3);
        break;
    case FUNCTION:
        rgblight_sethsv_at (HSV_WHITE, 3);
        break;
    case CURSOR:
        rgblight_sethsv_at (HSV_ORANGE, 3);
        break;
    case MISC:
        rgblight_sethsv_at (HSV_BLUE, 3);
        break;
    case QWERTY:
        rgblight_sethsv_at (0x00,  0x00, 0x00, 3);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_at (0x00,  0x00, 0x00, 3);
        break;
    }
  return state;
}
/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [ENGRAM] = LAYOUT(
    CW_TOGG,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  TO(0),  TG(QWERTY),    QK_BOOT,
    KC_LCTL,       KC_3,     KC_2,     KC_1,     KC_0,     KC_4,                                                                      KC_9,     KC_5,     KC_6,     KC_7,     KC_8,     KC_LSFT,
        KC_TILD, KC_B, KC_Y, C_S_T(KC_O), KC_U, KC_QUOT,                                                                                   KC_ESC, KC_L, C_S_T(KC_D), KC_W, KC_V, KC_Z,
        KC_UNDS, LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMM,                                                 KC_DOT, RSFT_T(KC_H), RCTL_T(KC_T), RALT_T(KC_S), RGUI_T(KC_N), KC_Q,
    KC_LT, KC_G, KC_X, KC_J, KC_K, KC_SLSH,                                                                   KC_COLN, KC_R, KC_M, KC_F, KC_P, KC_EQL,
                  KC_LBRC,  KC_RBRC,  KC_LEFT,  KC_RIGHT,                                                                                        KC_UP,   KC_DOWN,  KC_GRV,  KC_BSLS,
                                                      TG(NUMPAD),  ALT_TAB,                                             CLT_TAB,  OSL(SYMBOL),
                                                                KC_PGDN,                                               KC_PGUP,
                                             KC_BSPC,  KC_TAB,   OSL(FUNCTION),                                               QK_REP,  LT(MISC, KC_ENTER), KC_SPC
  ),
  [NUMPAD] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                                                      KC_CIRC,  KC_DLR,   KC_HASH,  KC_AT,    KC_EXLM,  KC_PIPE,
        KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_CIRC,                            KC_PERC, KC_7, KC_8, KC_9, KC_COLN, K,
        KC_PIPE, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                         KC_PPLS, KC_4, KC_5, KC_6, KC_MINS, J,
    KC_A, KC_B, KC_C, KC_D, KC_E, KC_F,                                                                      KC_PAST, KC_1, KC_2, KC_3, KC_SLSH, G,
              KC_NO,   KC_F,   KC_E,  KC_D,                                                                                       KC_EQL,   KC_DOT,   KC_LPRN,  KC_RPRN,
                                                      KC_TRNS,  KC_TRNS,                                               KC_LT,  KC_GT,
                                                                TG(NUMPAD),                                               KC_COMM,
                                            KC_BSPC,  KC_DEL,   TG(NUMPAD),                                                KC_NO,  KC_ENTER, KC_P0
  ),
  [SYMBOL] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_NO,    QK_BOOT,
    KC_TILD,   KC_GRV,     KC_LPRN,     KC_RPRN,     KC_SCLN,     KC_COMM,                                                                      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_EXLM, KC_LCBR, LARRW, PARENS, KC_RCBR, HOME, KC_ESC, KC_BSPC, KC_TAB, KC_SPC, KC_ENT, KC_LSFT,
        KC_HASH, KC_CIRC, KC_EQL, KC_MINS, KC_DLR, KC_ASTR, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LCTL|MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), KC_LCTL,
    KC_AT, KC_LT, KC_PIPE, KC_PLUS, KC_GT, KC_BSLS,                                                                      KC_SCLN, KC_DEL, LSFT(KC_TAB), KC_LPRN, KC_RPRN, KC_EQL,
              KC_AMPR,   KC_LBRC,   KC_RBRC,  KC_PLUS,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_QUES,  KC_DOT,                                               KC_RGUI,  VIM_SAVE,
                                                                KC_COLN,                                               KC_PGUP,
                                            KC_PERC,  KC_SCLN,   TG(SYMBOL),                                                KC_PGDN,  KC_ENTER, KC_SPC
  ),

  [FUNCTION] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                                                      KC_NO,     KC_NO,     KC_NO,  KC_NO,   KC_NO,  KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                 OSM(MOD_LALT), KC_F7, KC_F8, KC_F9, KC_F10, OSM(MOD_LSFT|MOD_LALT),
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                 OSM(MOD_LCTL), KC_F4, KC_F5, KC_F6, KC_F11, OSM(MOD_LSFT),
    KC_NO,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                                                      OSM(MOD_LCTL|MOD_LALT), KC_F1, KC_F2, KC_F3, KC_F12, OSM(MOD_LCTL|MOD_LSFT),
              KC_NO,   KC_NO,   KC_NO,  KC_NO,                                                                                       KC_NO,    KC_PSCR,  KC_KB_VOLUME_UP,  KC_KB_VOLUME_DOWN,
                                                      KC_NO,  KC_NO,                                               KC_NO,  CW_TOGG,
                                                                KC_NO,                                               KC_NO,
                                            KC_NO,  KC_NO,   TG(FUNCTION),                                                KC_NO,  KC_NO, KC_NO
  ),

  [CURSOR] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                         KC_INS,   KC_DEL,    KC_TAB,  KC_SPC,  KC_ENTER,    KC_ESC,
        LGUI(KC_1), KC_8, KC_7, KC_6, KC_5, KC_9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LGUI(KC_2), KC_3, KC_2, KC_1, KC_0, KC_4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LGUI(KC_3), LCTL(KC_4), LCTL(KC_3), LCTL(KC_2), LCTL(KC_1), LCTL(KC_5), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
             KC_NO,    KC_NO,    KC_NO,     KC_NO,                                                                                      KC_NO,    KC_NO,  KC_NO,  KC_NO,
                                                      LSFT(KC_INS),  KC_LSFT,                                               KC_NO,  KC_NO,
                                                              KC_NO,                                               KC_NO,
                                             KC_NO,  KC_NO,   KC_NO,                                               KC_NO,  KC_NO, KC_NO
  ),

  [MISC] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_9,    KC_8,    KC_7,     KC_6,    KC_5,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_3,    KC_2,    KC_1,     KC_0,    KC_4,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   LCTL(KC_4),    LCTL(KC_3),    LCTL(KC_2),     LCTL(KC_1),    LCTL(KC_5),                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
             RCS(KC_C), RCS(KC_V), KC_LEFT, KC_RGHT,                                                                                       KC_NO,    KC_NO,  KC_NO,  KC_NO,
                                                      LSFT(KC_INS),  KC_NO,                                               COPY_NEW_TAB,  VIM_SAVE,
                                                              KC_NO,                                               KC_NO,
                                             KC_NO,  KC_NO,   KC_NO,                                               KC_NO,  KC_NO, KC_NO
  ),
  [QWERTY] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TG(QWERTY),    QK_BOOT,
    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_GRV,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  KC_LALT,                                               KC_RGUI,  KC_RCTL,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  KC_ENTER, KC_SPC
  ),

  // [FUNCTION] = LAYOUT(
    // KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    QK_NO,
    // KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    // KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    // KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    // KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    //          KC_NO,    KC_NO,    KC_NO,     KC_NO,                                                                                      KC_NO,    KC_NO,  KC_NO,  KC_NO,
    //                                                   KC_NO,  KC_NO,                                               KC_NO,  KC_NO,
    //                                                           KC_NO,                                               KC_NO,
    //                                          KC_NO,  KC_NO,   KC_NO,                                               KC_NO,  KC_NO, KC_NO
  // ),
};
