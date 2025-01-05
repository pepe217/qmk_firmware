#pragma once

#include "quantum.h"
#define ENGRAM 0
#define NUMPAD 7
#define SYMBOL 2
#define FUNCTION 3
#define MISC 4
#define CURSOR 5
#define QWERTY 6
#define MAC_ENGRAM 1

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
    GUI_TAB,
    TESTS,
    SM,
};

//Tap Dance Declarations
enum {
  SHIFT_CAPS = 0
};

