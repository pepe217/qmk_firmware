#include QMK_KEYBOARD_H
#include "pepe217.h"

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
	misc_layer,
	cursor_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(ENGRAM, layer_state_cmp(state, ENGRAM));
    rgblight_set_layer_state(NUMPAD, layer_state_cmp(state, NUMPAD));
    rgblight_set_layer_state(SYMBOL, layer_state_cmp(state, SYMBOL));
    rgblight_set_layer_state(FUNCTION, layer_state_cmp(state, FUNCTION));
    rgblight_set_layer_state(CURSOR, layer_state_cmp(state, CURSOR));
    rgblight_set_layer_state(MISC, layer_state_cmp(state, MISC));
	return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ENGRAM] = LAYOUT_split_3x6_5(
		KC_TILD, KC_B, KC_Y, C_S_T(KC_O), KC_U, KC_QUOT,					 														 	 KC_ESC, KC_L, RCS(KC_D), KC_W, KC_V, KC_Z,
		KC_SLSH, LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMM,												 KC_DOT, RSFT_T(KC_H), RCTL_T(KC_T), RALT_T(KC_S), RGUI_T(KC_N), KC_Q,
		KC_LPRN, KC_G, KC_X, KC_J, KC_K, KC_UNDS,								 TG(NUMPAD), ALT_TAB,		   CLT_TAB,OSL(SYMBOL), KC_COLN, KC_R, KC_M, KC_F, KC_P, KC_EQL,
						     KC_LBRC, KC_RBRC, KC_BSPC, KC_TAB, OSL(FUNCTION), 					QK_REP, LT(MISC,KC_ENT), KC_SPC, KC_UP, KC_DOWN
	),
	[NUMPAD] = LAYOUT_split_3x6_5(
		KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_CIRC,							KC_PERC, KC_7, KC_8, KC_9, KC_COLN, K,
		KC_PIPE, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,				 		KC_PPLS, KC_4, KC_5, KC_6, KC_MINS, J,
		KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, TG(NUMPAD), KC_TILD,	KC_LT, KC_GT, KC_PAST, KC_1, KC_2, KC_3, KC_SLSH, G,
						  KC_LEFT, KC_RGHT, KC_BSPC, KC_W, KC_B,    KC_COMM, KC_ENT, KC_0, KC_PEQL, KC_PDOT
	),
	[SYMBOL] = LAYOUT_split_3x6_5(
		KC_EXLM, KC_LCBR, LARRW, PARENS, KC_RCBR, HOME, KC_ESC, KC_BSPC, KC_TAB, KC_SPC, KC_ENT, KC_LSFT,
		KC_HASH, KC_CIRC, KC_EQL, KC_MINS, KC_DLR, KC_ASTR, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LCTL|MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), KC_LCTL,
		KC_AT, KC_LT, KC_PIPE, KC_PLUS, KC_GT, KC_BSLS, DIR_UP, KC_TILD, COPY_NEW_TAB, VIM_SAVE, KC_SCLN, KC_DEL, LSFT(KC_TAB), KC_LPRN, KC_RPRN, KC_EQL,
								KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_COLN, TG(SYMBOL), KC_NO, KC_NO, KC_NO, KC_NO
	),
	[FUNCTION] = LAYOUT_split_3x6_5(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 								OSM(MOD_LALT), KC_F7, KC_F8, KC_F9, KC_F10, OSM(MOD_LSFT|MOD_LALT),
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 								OSM(MOD_LCTL), KC_F4, KC_F5, KC_F6, KC_F11, OSM(MOD_LSFT),
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LCTL|MOD_LALT), KC_F1, KC_F2, KC_F3, KC_F12, OSM(MOD_LCTL|MOD_LSFT),
							 RCS(KC_C), RCS(KC_V), LCTL(KC_C), LCTL(KC_V), KC_TRNS, KC_TRNS, CW_TOGG, KC_PSCR, KC_VOLU, KC_VOLD
	),
	[MISC] = LAYOUT_split_3x6_5(
		LGUI(KC_1), KC_8, KC_7, KC_6, KC_5, KC_9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		LGUI(KC_2), KC_3, KC_2, KC_1, KC_0, KC_4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		LGUI(KC_3), LCTL(KC_4), LCTL(KC_3), LCTL(KC_2), LCTL(KC_1), LCTL(KC_5), LSFT(KC_INS), KC_LSFT, COPY_NEW_TAB, VIM_SAVE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
		RCS(KC_C), RCS(KC_V), LCTL(KC_C), LCTL(KC_V), KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
	),
	[CURSOR] = LAYOUT_split_3x6_5(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
	),
};
