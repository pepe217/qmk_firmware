#include QMK_KEYBOARD_H

#define QWERTY 6
#define ENGRAM 0
#define NUMPAD 1
#define SYMBOL 2
#define FUNCTION 3
#define CURSOR 4 
#define MISC 5

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool is_clt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
uint16_t clt_tab_timer = 0;     // we will be using them soon.
enum custom_keycodes {          // Make sure have the awesome keycode ready

  ALT_TAB = SAFE_RANGE,
  VIM_SAVE,
  COPY_NEW_TAB,
  CLT_TAB,
  HOME,
};


// shift key overrides
const key_override_t comma_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_LPRN);
const key_override_t dot_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_RPRN);
// const key_override_t lparen_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LABK);
// const key_override_t rparen_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RABK);


const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_override, &dot_override,
    NULL // Null terminate the array of overrides!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case HOME:
		SEND_STRING("~/");
		break;
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
      SEND_STRING(SS_TAP(X_ESC) ":w" SS_TAP(X_ENTER));
      break;
    case COPY_NEW_TAB:
      SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL(SS_TAP(X_V)) SS_TAP(X_ENTER));
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
  if (is_clt_tab_active) {
    if (timer_elapsed(clt_tab_timer) > 1000) {
      unregister_code(KC_LCTL);
      is_clt_tab_active = false;
    }
  }
}

// layer colors
const rgblight_segment_t PROGMEM engram_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_OFF}
);
const rgblight_segment_t PROGMEM numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_GREEN}
);
const rgblight_segment_t PROGMEM symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_WHITE}
);
const rgblight_segment_t PROGMEM cursor_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM misc_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    engram_layer,
	numpad_layer,
	symbol_layer,
	function_layer,
	cursor_layer,
	misc_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, ENGRAM));
    rgblight_set_layer_state(1, layer_state_cmp(state, NUMPAD));
    rgblight_set_layer_state(2, layer_state_cmp(state, SYMBOL));
    rgblight_set_layer_state(3, layer_state_cmp(state, FUNCTION));
    rgblight_set_layer_state(4, layer_state_cmp(state, CURSOR));
    rgblight_set_layer_state(5, layer_state_cmp(state, MISC));
	return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ENGRAM] = LAYOUT_split_3x6_5(
		KC_DEL, KC_B, KC_Y, KC_O, KC_U, KC_QUOT,					 														 	 KC_ESC, KC_L, KC_D, KC_W, KC_V, KC_Z,
		KC_SLSH, LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMM,												 KC_DOT, RSFT_T(KC_H), RCTL_T(KC_T), RALT_T(KC_S), RGUI_T(KC_N), KC_Q,
		KC_SCLN, KC_G, KC_X, KC_J, KC_K, KC_UNDS,								 CLT_TAB, OSL(FUNCTION),		   ALT_TAB,OSL(MISC), KC_COLN, KC_R, KC_M, KC_F, KC_P, KC_EQL,
						     KC_LEFT, KC_RGHT, KC_BSPC, LT(FUNCTION,KC_TAB), TG(NUMPAD), 					OSL(SYMBOL), LT(SYMBOL,KC_ENT), KC_SPC, KC_UP, KC_DOWN
	),
	[NUMPAD] = LAYOUT_split_3x6_5(
		KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_CIRC,							KC_PERC, KC_7, KC_8, KC_9, KC_COLN, KC_K,
		KC_PIPE, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,				 		KC_PPLS, KC_4, KC_5, KC_6, KC_MINS, KC_J,
		KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, LCTL(KC_Z), KC_TILD,	KC_LT, KC_GT, KC_PAST, KC_1, KC_2, KC_3, KC_SLSH, LSFT(KC_G),
		KC_LEFT, KC_RGHT, KC_BSPC, LT(FUNCTION,KC_TAB), KC_TRNS, KC_COMM, KC_PENT, KC_P0, KC_PEQL, KC_PDOT
	),
	[SYMBOL] = LAYOUT_split_3x6_5(
		KC_EXLM, KC_LBRC, KC_QUOT, KC_DQUO, KC_RBRC, KC_QUES, KC_ESC, KC_BSPC, KC_TAB, KC_SPC, KC_ENT, KC_NO,
		KC_HASH, KC_CIRC, KC_EQL, KC_MINS, KC_DLR, KC_ASTR, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LCTL|MOD_LSFT), OSM(KC_LALT), OSM(KC_LGUI), KC_NO,
		KC_AT, KC_LT, KC_PIPE, HOME, KC_GT, KC_SLSH, KC_TILD, KC_BSLS, KC_TRNS, KC_NO, KC_SCLN, KC_DEL, LSFT(KC_TAB), KC_LPRN, KC_RPRN, KC_EQL,
		KC_AMPR, KC_LCBR, KC_RCBR, KC_PERC, KC_GRV, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
	),
	[FUNCTION] = LAYOUT_split_3x6_5(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 								OSM(MOD_LALT), KC_F7, KC_F8, KC_F9, KC_F10, OSM(MOD_LSFT|MOD_LALT),
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 								OSM(MOD_LCTL), KC_F4, KC_F5, KC_F6, KC_F11, OSM(MOD_LSFT),
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LCTL|MOD_LALT), KC_F1, KC_F2, KC_F3, KC_F12, OSM(MOD_LCTL|MOD_LSFT),
							 KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, CW_TOGG, KC_PSCR, KC_VOLU, KC_VOLD
	),
	[CURSOR] = LAYOUT_split_3x6_5(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
	),
	[MISC] = LAYOUT_split_3x6_5(
		LGUI(KC_1), KC_9, KC_8, KC_7, KC_6, KC_5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		LGUI(KC_2), KC_3, KC_2, KC_1, KC_0, KC_4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		LGUI(KC_3), LCTL(KC_4), LCTL(KC_3), LCTL(KC_2), LCTL(KC_1), LCTL(KC_5), LSFT(KC_INS), KC_NO, COPY_NEW_TAB, VIM_SAVE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, 
		RCS(KC_C), RCS(KC_V), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
	)
};