// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
 
#include QMK_KEYBOARD_H

#define QWERTY 6
#define ENGRAM 0
#define SYMBOL 2
#define NUMPAD 1
#define FUNCTION 3
#define CURSOR 4 
#define MISC 5

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
enum custom_keycodes {          // Make sure have the awesome keycode ready

  ALT_TAB = SAFE_RANGE,
};

// shift key overrides
const key_override_t comma_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_LPRN);
const key_override_t dot_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RPRN);
const key_override_t lparen_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LABK);
const key_override_t rparen_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RABK);


const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_override, &dot_override, &lparen_override, &rparen_override,
    NULL // Null terminate the array of overrides!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
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

  [ENGRAM] = LAYOUT(
    CW_TOGG,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TG(QWERTY),    QK_BOOT,
    KC_EQL,       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     CW_TOGG,
    KC_GRV,       KC_B,     KC_Y,     KC_O,     KC_U,     KC_QUOT,                                                                   KC_EQL,  KC_L,     KC_D,     KC_W,     KC_V,     KC_Z,
    KC_SLSH,      MT(MOD_LGUI, KC_C),     MT(MOD_LALT, KC_I),     MT(MOD_LCTL, KC_E),     MT(MOD_LSFT, KC_A),     KC_COMM,          KC_DOT,   MT(MOD_RSFT, KC_H),     MT(MOD_RCTL, KC_T),     MT(MOD_RALT, KC_S),     MT(MOD_RGUI, KC_N),     KC_Q,
    KC_COLN,    KC_G,     KC_X,     KC_J,     KC_K,     KC_UNDS,                                                                   KC_ESC,  KC_R,     KC_M,     KC_F,     KC_P,     KC_SCLN,
                  KC_DEL,  KC_BSLS,  KC_LEFT,  KC_RIGHT,                                                                                        KC_UP,   KC_DOWN,  KC_LBRC,  KC_RBRC,  
                                                      LALT(KC_TAB),  TG(NUMPAD),                                             OSL(MISC),  OSL(SYMBOL),
                                                                OSL(CURSOR),                                               KC_PGUP,
                                             KC_BSPC,  KC_TAB,   OSL(FUNCTION),                                               KC_PGDN,  LT(MISC, KC_ENTER), LT(SYMBOL, KC_SPC)
  ),

  [SYMBOL] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_NO,    QK_BOOT,
    KC_TILD,   KC_GRV,     KC_LPRN,     KC_RPRN,     KC_SCLN,     KC_COMM,                                                                      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
    KC_EXLM,   KC_LCBR,     KC_QUOT,     KC_DQUO,     KC_RCBR,     KC_QUES,                                                                      KC_SCLN,     KC_RSFT,     KC_RCTL,     KC_RALT,     KC_P,     KC_BSLS,
    KC_HASH,  KC_CIRC,     KC_EQL,     KC_UNDS,     KC_DLR,     KC_ASTR,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_AT,  KC_LT,     KC_PIPE,     KC_MINS,     KC_GT,     KC_SLSH,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_AMPR,   KC_LBRC,   KC_RBRC,  KC_PLUS,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_ASTR,  KC_PERC,                                               KC_RGUI,  KC_RCTL,
                                                                KC_SCLN,                                               KC_PGUP,
                                            KC_BSLS,  KC_DOT,   TG(SYMBOL),                                                KC_PGDN,  KC_ENTER, KC_SPC
  ),

  [NUMPAD] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                                                      KC_CIRC,  KC_DLR,   KC_HASH,  KC_AT,    KC_EXLM,  KC_PIPE,
    KC_TAB,   OSM(MOD_LSFT),    RCS(KC_Z),    RCTL(KC_Z),     KC_BSPC,    KC_A,                                                                      KC_PERC,  KC_P7,    KC_P8,    KC_P9,    KC_COLN,  KC_K,
    KC_NO,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_RSFT,     KC_B,                                                                      KC_PLUS,  KC_P4,    KC_P5,    KC_P6,    KC_MINS,  KC_J,
    KC_NO, KC_NO,KC_NO,     KC_NO,     KC_UNDS,     KC_C,                                                                      KC_ASTR,  KC_P1,    KC_P2,    KC_P3,    KC_SLSH,  KC_G,
              KC_NO,   KC_NO,   KC_NO,  KC_NO,                                                                                       KC_EQL,   KC_DOT,   KC_LPRN,  KC_RPRN,
                                                      KC_D,  KC_E,                                               KC_LT,  KC_GT,
                                                                KC_F,                                               KC_COMM,
                                            KC_BSPC,  KC_DEL,   TG(NUMPAD),                                                KC_NO,  KC_DOT, KC_P0
  ),

  [FUNCTION] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                                                      KC_NO,     KC_NO,     KC_NO,  KC_NO,   KC_NO,  KC_NO,
    KC_INS,   OSM(MOD_LSFT),    RCS(KC_Z),    RCTL(KC_Z),     KC_BSPC,     KC_NO,                                                      OSM(MOD_LALT),KC_F7,     KC_F8,     KC_F9,     KC_F10,     KC_F13,     
    CW_TOGG,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_RSFT,     KC_NO,                                                                      OSM(MOD_LSFT),    KC_F4,     KC_F5,     KC_F6,     KC_F11,     KC_F14,
    KC_NO,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                                                      OSM(MOD_LCTL),      KC_F1,     KC_F2,     KC_F3,     KC_F12,  KC_F15,
              KC_NO,   KC_NO,   KC_NO,  KC_NO,                                                                                       OSM(MOD_LCTL|MOD_LSFT),    OSM(MOD_LALT|MOD_LSFT),  OSM(MOD_LALT|MOD_LSFT|MOD_LCTL),  KC_NO,
                                                      KC_NO,  KC_NO,                                               KC_NO,  KC_NO,
                                                                KC_NO,                                               KC_NO,
                                            KC_NO,  KC_NO,   TG(FUNCTION),                                                KC_NO,  KC_NO, KC_NO
  ),

  [CURSOR] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_ESC,   KC_ENTER,    KC_SPC, KC_TAB, KC_DEL, KC_INS,                                         KC_INS,   KC_DEL,    KC_TAB,  KC_SPC,  KC_ENTER,    KC_ESC,
    KC_NO,   OSM(MOD_LSFT),    RCS(KC_Z),    RCTL(KC_Z),     KC_BSPC,    RCTL(KC_X),                                                                   RCTL(KC_X),   KC_BSPC,    RCTL(KC_Z),  RCS(KC_Z),  OSM(MOD_LSFT),    KC_NO,
    CW_TOGG,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_RSFT,    RCTL(KC_C),                                                                   RCTL(KC_C),   KC_LEFT,  KC_UP,  KC_DOWN,  KC_RIGHT,    RCTL(KC_L),
    RCTL(KC_J),   RCTL(KC_A),    KC_NO,    KC_NO,     RCTL(KC_F),    RCTL(KC_V),                                                                   RCTL(KC_V),   KC_HOME,    KC_PGUP, KC_PGDN,  KC_END,    RCTL(KC_J),
             KC_NO,    KC_NO,    KC_NO,     KC_NO,                                                                                      KC_NO,    KC_NO,  KC_NO,  KC_NO,
                                                      RALT(KC_TAB),  RGUI(KC_TAB),                                               KC_NO,  KC_NO,
                                                              KC_NO,                                               KC_NO,
                                             KC_NO,  KC_NO,   KC_NO,                                               KC_NO,  KC_NO, KC_NO
  ),

  [MISC] = LAYOUT(
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,    KC_NO,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_9,    KC_8,    KC_7,     KC_6,    KC_5,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_3,    KC_2,    KC_1,     KC_0,    KC_4,                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   LGUI(KC_1),    LGUI(KC_2),    LGUI(KC_3),     LGUI(KC_4),    LGUI(KC_5),                                                                   KC_NO,   KC_NO,    KC_NO,  KC_NO,  KC_NO,    KC_NO,
             KC_NO,    KC_NO,    KC_NO,     KC_NO,                                                                                      KC_NO,    KC_NO,  KC_NO,  KC_NO,
                                                      KC_NO,  KC_NO,                                               KC_NO,  KC_NO,
                                                              KC_NO,                                               KC_NO,
                                             KC_NO,  KC_NO,   KC_NO,                                               KC_NO,  KC_NO, KC_NO
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
