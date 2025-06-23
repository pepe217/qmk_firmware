#include "pepe217.h"

bool     is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool     is_clt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
uint16_t clt_tab_timer     = 0;     // we will be using them soon.

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t* key_overrides[] = {
    &delete_key_override,
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
};

const uint16_t PROGMEM kj_combo[] = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM rb_combo[] = {KC_R, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
  [KJ_ESC] = COMBO(kj_combo, KC_ESC),
  [R_BSPC] = COMBO(rb_combo, CW_TOGG),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int os_keycode;
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
            // allow cmd+tab to work when in gui swap mode
            os_keycode = KC_LALT;
            if (mod_config(MOD_LGUI) == MOD_LCTL){
                os_keycode = KC_LGUI;
            }
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(os_keycode);
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
        case VIM_CTRL_O:
            // corrects for ctrl/gui swap to send ctrl+o always
            if (record->event.pressed) {
                if (mod_config(MOD_LGUI) == MOD_LCTL){
                    SEND_STRING(SS_LGUI("o"));
                } else {
                    SEND_STRING(SS_LCTL("o"));
                }
            }
            return false;
        case MAC_COLON:
            // sends actual semicolon which karabiner then swaps to colon
            if (record->event.pressed) {
                if (mod_config(MOD_LGUI) == MOD_LCTL){
                    SEND_STRING(";");
                } else {
                    SEND_STRING(":");
                }
            }
            return false;
        case MAC_SCOLON:
            // sends actual colon which karabiner then swaps to semicolon
            if (record->event.pressed) {
                if (mod_config(MOD_LGUI) == MOD_LCTL){
                    SEND_STRING(":");
                } else {
                    SEND_STRING(";");
                }
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
        // allow cmd+tab to work when in gui swap mode
        int keycode = KC_LALT;
        if (mod_config(MOD_LGUI) == MOD_LCTL){
            keycode = KC_LGUI;
        }
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(keycode);
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
