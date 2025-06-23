#pragma once

#include "quantum.h"
#define ENGRAM 0
#define NUMPAD 7
#define SYMBOL 2
#define FUNCTION 3
#define MISC 4
#define CURSOR 5
#define QWERTY 6
#define MOUSE 8
#define SYSTEM 9

// Custom key defines
#define TMUX_L  LCTL(KC_B) // tmux leader key
#define COPY  LCTL(KC_C)
#define CUT  LCTL(KC_X)
#define PASTE  LCTL(KC_V)
#define FIND  LCTL(KC_F)
#define UNDO  LCTL(KC_Z)
#define REDO  LSFT(LCTL(KC_Z))
#define SELA  LCTL(KC_A)
#define FINDN  LCTL(KC_G)
#define FINDP  LSFT(LCTL(KC_G))

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    VIM_SAVE,
    COPY_NEW_TAB,
    CLT_TAB,
    HOME,
    LARRW,
    J,
    K,
    G,
    PARENS,
	DIR_UP,
    NEXT_TAB,
    REPLAY_MACRO,
    TESTS,
    SM,
    DEVMONO,
    VIM_CTRL_O,
    MAC_COLON,
    MAC_SCOLON,
};

enum combos {
  KJ_ESC,
  R_BSPC,
};
