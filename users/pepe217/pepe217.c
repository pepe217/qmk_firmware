#include "pepe217.h"

bool     is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool     is_clt_tab_active = false; // ADD this near the beginning of keymap.c
bool     is_gui_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
uint16_t clt_tab_timer     = 0;     // we will be using them soon.
uint16_t gui_tab_timer     = 0;     // we will be using them soon.

const key_override_t coln_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN); // Shift : is ;
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t* key_overrides[] = {
    &coln_key_override,
    &delete_key_override,
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift OS, twice for Caps Word
  [SHIFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LSFT), CW_TOGG)
};

const uint16_t PROGMEM kj_combo[] = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM rb_combo[] = {KC_R, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
  [KJ_ESC] = COMBO(kj_combo, KC_ESC),
  [R_BSPC] = COMBO(rb_combo, CW_TOGG),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case TESTS:
            if (record->event.pressed) {
                SEND_STRING("tests.");
            }
            return false;
        case DEVMONO:
            if (record->event.pressed) {
                SEND_STRING("cd devel/monorepo");
            }
            return false;
        case SM:
            if (record->event.pressed) {
                SEND_STRING("station_members.");
            }
            return false;
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
        case GUI_TAB:
            if (record->event.pressed) {
                if (!is_gui_tab_active) {
                    is_gui_tab_active = true;
                    register_code(KC_LGUI);
                }
                gui_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CLT_TAB:
            if (record->event.pressed) {
                if (!is_clt_tab_active) {
                    is_clt_tab_active = true;
                    register_code(KC_LCTL);
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

void matrix_scan_user(void) {
    // The very important timers.
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
    if (is_gui_tab_active) {
        if (timer_elapsed(gui_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_gui_tab_active = false;
        }
    }
}
