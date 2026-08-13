/* Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "action_layer.h"
#include "action_tapping.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include <cyboard.h>

enum layer_names {
    _BASE,
    _SYMBOLS,
    _NUMBERS,
    _NAVIGATION,
    _GAMING,
    _HOTKEYS,
    _GAMING_OTHER,
    _TRACKBALL = 9
};

enum custom_keycodes {
    ENT_TYPE = SAFE_RANGE,
    ESC_TYPE = SAFE_RANGE+1,
};

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    if (data[0] == 0x87) {
        layer_move(_GAMING);
    } else if (data[0] == 0x86) {
        layer_move(_BASE);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_TRACKBALL);
    set_auto_mouse_enable(true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case _GAMING:
        case _HOTKEYS:
        case _GAMING_OTHER:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }

    return state;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(8, KC_PDOT):
        case LT(_SYMBOLS, KC_BSPC):
        case LT(_NUMBERS, KC_ENT):
        case LCTL_T(KC_ESC):
        case LCTL_T(KC_DEL):
            return true;
        default:
            return false;
    }
}

/* bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         case LT(_NAVIGATION, KC_Z): */
/*         case LT(_NAVIGATION, KC_EQL): */
/*             return true; */
/*         default: */
/*             return false; */
/*     } */
/* } */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_fun_custom(
        KC_NO,       KC_F1,                    KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                     KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                     KC_F11,
        KC_NO,       KC_1,                     KC_2,  KC_3,  KC_4,  KC_5,  KC_6,                                      KC_6,  KC_7,  KC_8,  KC_9,  KC_0,                       KC_F12,
        KC_ESC,      KC_Q,                     KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,                                      KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,                       KC_NO,
        KC_TAB,      KC_A,                     KC_S,  KC_D,  KC_F,  KC_G,  KC_H,                                      KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,                    KC_QUOT,
        MO(_HOTKEYS), LT(_NAVIGATION, KC_Z),   KC_X,  KC_C,  KC_V,  KC_B,                                             KC_N,  KC_M,  KC_COMM, KC_DOT, LT(_NAVIGATION, KC_SLSH), KC_ENT,

                                KC_LGUI, KC_LALT,    KC_SPC, MO(_NUMBERS), TG(_TRACKBALL),    TG(_GAMING_OTHER), LT(_NUMBERS, KC_ENT), LT(_SYMBOLS, KC_BSPC),    KC_LALT, KC_LGUI,
                                                    LCTL_T(KC_ESC), KC_LSFT, KC_MEH, TG(_GAMING),    RM_TOGG, KC_CAPS, KC_LSFT, LCTL_T(KC_DEL)
    ),

    [_SYMBOLS] = LAYOUT_fun_custom(
        _______, _______,    _______,       _______,       _______,       _______,       _______,                                  _______,          _______,        _______,       _______,       _______,         _______,
        _______, KC_NO,      KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,                                    KC_NO,            LSFT(KC_NUBS), LSFT(KC_8),    KC_NO,         KC_NO,           _______,
        _______, LSFT(KC_3), LSFT(KC_7),    LSFT(KC_LBRC), LSFT(KC_RBRC), KC_NO,         KC_NO,                                    LSFT(KC_NUHS),    KC_GRV,         LSFT(KC_EQL), KC_NUHS,       LSFT(KC_GRV),   _______,
        _______, LSFT(KC_5), LSFT(KC_4),    LSFT(KC_9),    LSFT(KC_0),    KC_NO,         KC_NO,                                    LSFT(KC_1),       LSFT(KC_2),    KC_MINS,       KC_EQL,        LSFT(KC_SCLN),  LSFT(KC_QUOT),
        _______, KC_SLSH,    LSFT(KC_6),    KC_LBRC,       KC_RBRC,       KC_NO,                                                   _______,          LSFT(KC_MINS), LSFT(KC_COMM), LSFT(KC_DOT), KC_NUBS,         _______,

                                _______, _______,    _______, _______, _______,    _______, _______, _______,    _______, _______,
                                                _______, _______, _______, _______,    TO(_BASE), _______, _______, _______
    ),

    [_NUMBERS] = LAYOUT_fun_custom(
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PEQL, KC_NO,   KC_NO,                             KC_NUM,  KC_PSLS, KC_PAST, KC_PEQL, KC_NO,   _______,
        _______, KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_NO,                             KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
        _______, KC_P0,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_NO,                             KC_P0,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_NO,                                     KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_NO,   _______,

                                _______, _______,    KC_BSPC, KC_ENT, TG(_NUMBERS),    KC_SPC, KC_ENT, KC_BSPC,    _______, _______,
                                                LT(8, KC_PDOT), KC_P0, KC_DEL, KC_SPC,    TO(_BASE), KC_DEL, KC_0, LT(8, KC_PDOT)
    ),

    [_NAVIGATION] = LAYOUT_fun_custom(
        _______, _______, _______, _______, _______,  _______,  _______,                           _______,   _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______,  _______,  _______,                           _______,   _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______,  _______,  _______,                           KC_INSERT,  KC_PSCR, KC_SCRL, KC_PAUSE, _______, _______,
        _______, _______, KC_LEFT, KC_UP,   KC_DOWN,  KC_RIGHT, _______,                           KC_LEFT,    KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, KC_HOME, KC_PGUP, KC_PGDN,  KC_END,                                     KC_HOME,    KC_PGDN, KC_PGUP, KC_END,   _______, _______,

                                _______, _______,    LCTL(KC_LALT), KC_NO, KC_NO,    KC_NO, KC_NO, LCTL(KC_LALT),    _______, _______,
                                                KC_LCTL, KC_LSFT, LCTL(KC_LSFT), KC_NO,    KC_LSFT, LCTL(KC_LSFT), KC_LSFT, KC_LCTL
    ),

    [_GAMING] = LAYOUT_fun_custom(
        KC_F9,  KC_F4,   KC_6, KC_7, KC_8, KC_9, KC_0,                             KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_F10, KC_F5,   KC_1, KC_2, KC_3, KC_4, KC_5,                             KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5,  KC_F12,
        KC_ESC, KC_H,    KC_Q, KC_W, KC_E, KC_R, KC_T,                             _______, _______, _______, _______, _______, _______,
        KC_TAB, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                             _______, _______, _______, _______, _______, _______,
        _______, KC_LALT, KC_Z, KC_X, KC_C, KC_V,                                  _______, _______, _______, _______, _______, _______,

                                KC_Y, KC_B,    KC_SPC, KC_DEL, KC_CAPS,    KC_NO, _______, _______,    _______, _______,
                                            KC_LCTL, KC_LALT, KC_MEH, TG(_GAMING),    TO(_BASE), _______, _______, _______
    ),

    [_HOTKEYS] = LAYOUT_fun_custom(
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                             _______, _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_NO,                             _______, _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_NO,                             _______, _______, _______, _______, _______, _______,
        _______, KC_NO,   KC_F13,  KC_F14,  KC_F15,  KC_F16,                                    _______, _______, _______, _______, _______, _______,

                                _______, _______,    _______, _______, _______,    _______, _______, _______,    _______, _______,
                                                _______, _______, _______, _______,    TO(_BASE), _______, _______, _______
    ),

    [_GAMING_OTHER] = LAYOUT_fun_custom(
        _______,  _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______,  _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______,  _______, _______,
        ESC_TYPE, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______,  _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______,  _______, _______,
        _______,  _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, ENT_TYPE, _______,

                                _______, _______,    _______, _______, _______,    ENT_TYPE, _______, _______,    _______, _______,
                                                _______, _______, TO(_BASE), _______,    _______, _______, _______, _______
    ),

    [7] = LAYOUT_fun_custom(
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,

                                _______, _______,    _______, _______, _______,    _______, _______, _______,    _______, _______,
                                                _______, _______, _______, _______,    _______, _______, _______, _______
    ),

    [8] = LAYOUT_fun_custom(
        _______, _______,    _______,    _______,    _______,    _______,    _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______,    _______,    _______,    _______,    _______,    _______,                           _______, _______, _______, _______, _______, _______,
        _______, LCTL(KC_Q), LCTL(KC_W), LCTL(KC_E), LCTL(KC_R), LCTL(KC_T), LCTL(KC_Y),                        _______, _______, _______, _______, _______, _______,
        _______, LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G), LCTL(KC_H),                        _______, _______, _______, _______, _______, _______,
        _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),                                   _______, _______, _______, _______, _______, _______,

                                _______, _______,    _______, _______, _______,    _______, _______, _______,    _______, _______,
                                                _______, _______, _______, _______,    _______, _______, _______, _______
    ),

    [_TRACKBALL] = LAYOUT_fun_custom(
        _______, _______, _______,                         _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                         _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                         KC_BTN4, KC_BTN5, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, RIGHT_DRAGSCROLL_MODE_TOGGLE,    KC_BTN2, KC_BTN1, KC_BTN3, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                         _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,

                                _______, _______,    _______, _______, _______,    _______, _______, _______,    _______, _______,
                                                _______, _______, _______, _______,    _______, _______, _______, _______
    )
};
