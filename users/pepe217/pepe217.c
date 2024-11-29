#include "pepe217.h"
#include "features/custom_shift_keys.h"

bool     is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool     is_clt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
uint16_t clt_tab_timer     = 0;     // we will be using them soon.

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_RPRN},  // Shift . is )
    {KC_COMM, KC_LPRN}, // Shift , is (
    {KC_UNDS, KC_MINS}, // Shift _ is -
    {KC_COLN, KC_SCLN}, // Shift : is ;
    {KC_BSPC, KC_DEL}, // Shift : is ;
    {KC_LT, KC_GT},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift OS, twice for Caps Word
  [SHIFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LSFT), CW_TOGG)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // for custom shift keys
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case NEXT_TAB:
            if (record->event.pressed) {
                SEND_STRING(":tabnext");
            }
            return false;
        case REPLAY_MACRO:
            if (record->event.pressed) {
                SEND_STRING("@q");
            }
            return false;
        case J:
            if (record->event.pressed) {
                SEND_STRING("j");
                layer_invert(NUMPAD);
            }
            return false;
        case K:
            if (record->event.pressed) {
                SEND_STRING("k");
                layer_invert(NUMPAD);
            }
            return false;
        case G:
            if (record->event.pressed) {
                SEND_STRING("G");
                layer_invert(NUMPAD);
            }
            return false;
        case LARRW:
            if (record->event.pressed) {
                SEND_STRING(" -> ");
            }
            return false;
        case PARENS:
            if (record->event.pressed) {
                SEND_STRING("()");
            }
            return false;
        case HOME:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;
        case CLT_TAB:
            if (record->event.pressed) {
                if (!is_clt_tab_active) {
                    is_clt_tab_active = true;
                    unregister_code(KC_LCTL);
                }
                clt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
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
        case VIM_SAVE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESC) ":w" SS_TAP(X_ENTER));
            }
            return false;
        case COPY_NEW_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENTER));
            }
            return false;
		case DIR_UP:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
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
    if (is_clt_tab_active) {
        if (timer_elapsed(clt_tab_timer) > 1000) {
            unregister_code(KC_LCTL);
            is_clt_tab_active = false;
        }
    }
}
