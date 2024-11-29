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
    KC_ESC, KC_PGUP,       KC_PGDN,    LCTL(4),    LCTL(3),    LCTL(2),    LCTL(1),    ALT_TAB,     CLT_TAB,     KC_RIGHT,    KC_LEFT, LGUI(KC_1),   LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),  KC_PSCR,  OSL(FUNCTION),    QK_BOOT,
    OSM(MOD_LCTL),  KC_4,          KC_3,          KC_2,          KC_1,          KC_5,     KC_9,     KC_0,          KC_6,          KC_7,          KC_8,          OSM(MOD_RCTL),
    LCTL(KC_B), KC_B,          KC_Y,          KC_O,          KC_U,   KC_COLN,  KC_X,  KC_L,   KC_D,          KC_W,          KC_V,          KC_UNDS,
    KC_Q,  KC_C,  KC_I,  KC_E,  KC_A,  KC_COMM,  KC_K,   KC_H,  KC_T,  KC_N,  KC_S,  KC_Z,
   SHIFT_CAPS,  KC_QUOT, KC_MINUS, KC_EQUAL, KC_DOT, KC_SLSH,                                                                   KC_J, KC_M, KC_G, KC_P, KC_F, SHIFT_CAPS,
                    KC_GRV,  KC_LBRC, KC_RBRC,  KC_BSLS,                                                                                        KC_UP,   KC_DOWN,  KC_LPRN,  KC_RPRN,
                                                      KC_ESC,  QK_REP,                                             QK_REP,  KC_BSPC,
                                                                OSM(MOD_LALT),                                               OSM(MOD_RALT),
                                             KC_SPC,  KC_TAB,   TG(NUMPAD),                                               OSL(SYMBOL),  KC_ENT, KC_R
  ),
  [NUMPAD] = LAYOUT(
    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                                                      KC_TILDE, KC_CIRC,  KC_HASH,  KC_DLR,     KC_EXLM,  KC_PIPE,
        KC_A, SHIFT_CAPS, LCTL(LS(KC_Z)), LCTL(KC_Z),KC_BSPC, KC_D,                            G, KC_7, KC_8, KC_9, KC_COLN, KC_PERC,
        KC_B, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_E,                         K, KC_4, KC_5, KC_6, KC_MINS, KC_PLUS,
    KC_C, LCTL(KC_A), KC_NO, KC_NO, KC_X, KC_F,                                                                      J, KC_1, KC_2, KC_3, KC_SLSH, KC_PAST,
              KC_NO,   KC_NO,   KC_NO,  KC_UNDS,                                                                                       KC_LBRC,   KC_LPRN,   KC_RPRN,  KC_RBRC,
                                                      LCTL(LSFT(KC_C)),  LCTL(LSFT(KC_V)),                                               KC_LT,  KC_EQL,
                                                                LALT(KC_INS),                                               KC_GT,
                                            KC_BSPC,  KC_ESC,   TG(NUMPAD),                                                KC_COMM,  KC_DOT, KC_0
  ),
  [SYMBOL] = LAYOUT(
    KC_ESC,   LGUI(KC_UP),    LGUI(KC_LEFT),    LSFT(LGUI(KC_LEFT)),    LSFT(LGUI(KC_RIGHT)),    LGUI(KC_RIGHT),    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_NO,    QK_BOOT,
    KC_TILD,   KC_GRV,     KC_LPRN,     KC_RPRN,     KC_SCLN,     KC_COMM,                                                                      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_EXLM, KC_LCBR, LARRW, PARENS, KC_RCBR, HOME,                 KC_SCLN, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_NO,
        KC_HASH, KC_CIRC, KC_EQL, KC_MINS, KC_DLR, KC_ASTR,             KC_DOT, KC_BSPC, KC_TAB, KC_SPACE, KC_ENTER, KC_NO,
    KC_AT, KC_LT, KC_PIPE, KC_PLUS, KC_GT, REPLAY_MACRO,                                                                      KC_BSLS, KC_DEL, LSFT(KC_TAB), KC_NO, KC_NO, KC_NO,
              KC_AMPR,   KC_LBRC,   KC_RBRC,  DIR_UP,                                                                                       KC_TRNS,    KC_TRNS,  KC_TRNS,  VIM_SAVE,
                                                      KC_BSLS,  KC_DOT,                                               KC_NO,  VIM_SAVE,
                                                                KC_PAST,                                               KC_NO,
                                            KC_PERC,  KC_SCLN,   KC_COLON,                                                TG(SYMBOL),  KC_ENTER, VIM_SAVE
  ),

  [FUNCTION] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   LALT(KC_4),    LALT(KC_3), LALT(KC_2), LALT(KC_1), LALT(KC_5),                                                                      KC_NO,     KC_NO,     KC_NO,  KC_NO,   KC_NO,  KC_NO,
        LALT(KC_TAB), LGUI(KC_4),    LGUI(KC_3), LGUI(KC_2), LGUI(KC_1), LGUI(KC_5),                                 OSM(MOD_LALT), KC_F7, KC_F8, KC_F9, KC_F10, OSM(MOD_LSFT|MOD_LALT),
        KC_CAPS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                                 OSM(MOD_LCTL), KC_F4, KC_F5, KC_F6, KC_F11, OSM(MOD_LSFT),
    KC_X, LCTL(LSFT(KC_Z)), KC_NO, KC_NO, LCTL(KC_C), LCTL(KC_V),                                                                      OSM(MOD_LCTL|MOD_LALT), KC_F1, KC_F2, KC_F3, KC_F12, OSM(MOD_LCTL|MOD_LSFT),
              KC_NO,   KC_NO,   KC_NO,  LCTL(KC_Z),                                                                                       KC_KB_MUTE,    KC_PSCR,  KC_KB_VOLUME_DOWN,  KC_KB_VOLUME_UP,
                                                      LCTL(LSFT(KC_C)),  LCTL(LSFT(KC_V)),                                               KC_NO,  CW_TOGG,
                                                                LALT(KC_INS),                                               KC_NO,
                                            KC_BSPC,  KC_ESC,   TG(FUNCTION),                                                KC_NO,  KC_NO, KC_NO
  ),

 [CURSOR] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                         KC_INS,   KC_DEL,    KC_TAB,  KC_SPC,  KC_ENTER,    KC_ESC,
        LGUI(KC_1), KC_8, KC_7, KC_6, KC_0, KC_9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LGUI(KC_2), KC_4, KC_3, KC_2, KC_1, KC_5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
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
    KC_ESC, KC_F1,       KC_F2,    KC_PGUP,    KC_PGDN,    KC_F5,    LCTL(KC_B), ALT_TAB,     CLT_TAB,     OSM(MOD_LGUI),         LGUI(KC_1), LGUI(KC_2),   LGUI(KC_3), LGUI(KC_4), KC_PSCR,   TO(0),  TG(QWERTY),    QK_BOOT,
    KC_EQL,   KC_4,          KC_3,          KC_2,          KC_1,          KC_5,     KC_9,     KC_0,          KC_6,          KC_7,          KC_8,          KC_MINS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    KC_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_GRV,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      OSM(MOD_LSFT),  OSM(MOD_LCTL),                                             OSM(MOD_RCTL),  OSM(MOD_RSFT),
                                                                OSM(MOD_LALT),                                               OSM(MOD_RALT),
                                             KC_BSPC,  KC_TAB,   TG(NUMPAD),                                               QK_REP,  KC_ENT, LT(MISC, KC_SPC)
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
