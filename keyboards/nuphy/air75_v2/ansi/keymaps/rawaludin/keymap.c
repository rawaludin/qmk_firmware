/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TOG_VIM:
            if (record->event.pressed) {
                toggle_vim_mode();
            }
            return false;  // Skip all further processing of this key
    }

    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    return true; // Process all other keycodes normally
}

bool process_insert_mode_user(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed && keycode == LCTL(KC_W)) {
        tap_code16(LALT(KC_BSPC));
        return false;
    }
    return true;
}

bool process_normal_mode_user(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed && keycode == LCTL(KC_D)) {
        tap_code(KC_PGDN);
        return false;
    }
    if (record->event.pressed && keycode == LCTL(KC_U)) {
        tap_code(KC_PGUP);
        return false;
    }
    if (record->event.pressed && keycode == KC_SLSH) {
        tap_code16(LGUI(KC_F));
        insert_mode();
        return false;
    }
    return true;
}

// Left-hand home row mods QWERTY
#define HOME_A LALT_T(KC_A)
#define HOME_S LCTL_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods QWERTY
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L RCTL_T(KC_L)
#define HOME_SCLN LALT_T(KC_SCLN)

// Left-hand home row mods COLEMAK
#define HOME_CM_A LALT_T(KC_A)
#define HOME_CM_R LCTL_T(KC_R)
#define HOME_CM_S LGUI_T(KC_S)
#define HOME_CM_T LSFT_T(KC_T)

// Right-hand home row mods COLEMAK
#define HOME_CM_N RSFT_T(KC_N)
#define HOME_CM_E RGUI_T(KC_E)
#define HOME_CM_I RCTL_T(KC_I)
#define HOME_CM_O LALT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer Mac Colemak
[0] = LAYOUT_75_ansi(
    KC_ESC,     KC_BRID,   KC_BRIU,     KC_MCTL,   MAC_SEARCH, MAC_VOICE,   MAC_DND,   KC_MPRV,    KC_MPLY,     KC_MNXT,   KC_MUTE,    KC_VOLD,    KC_VOLU,     MAC_PRTA,   DF(5),      KC_DEL,
    KC_GRV,     KC_1,      KC_2,        KC_3,      KC_4,       KC_5,        KC_6,      KC_7,       KC_8,        KC_9,      KC_0,       KC_MINS,    KC_EQL,                  KC_BSPC,    KC_PGUP,
    KC_TAB,     KC_Q,      KC_W,        KC_F,      KC_P,       KC_G,        KC_J,      KC_L,       KC_U,        KC_Y,      HOME_SCLN,  KC_LBRC,    KC_RBRC,                 KC_BSLS,    KC_PGDN,
    KC_ESC,     HOME_CM_A, HOME_CM_R,   HOME_CM_S, HOME_CM_T,  KC_D,        KC_H,      HOME_CM_N,  HOME_CM_E,   HOME_CM_I, HOME_CM_O,  KC_QUOT,                             KC_ENT,     KC_HOME,
    SC_LSPO,               KC_Z,        KC_X,      KC_C,       KC_V,        KC_B,      KC_K,       KC_M,        KC_COMM,   KC_DOT,     KC_SLSH,                 SC_RSPC,    KC_UP,      KC_END,
    TOG_VIM,    KC_LALT,   KC_LGUI,                                         LT(8, KC_SPC),                      KC_RGUI,   MO(1),      KC_RCTL,                 KC_LEFT,    KC_DOWN,    KC_RGHT),

// layer Mac Fn
[1] = LAYOUT_75_ansi(
    _______,    KC_F1,      KC_F2,      KC_F3,     KC_F4,      KC_F5,       KC_F6,     KC_F7,      KC_F8,       KC_F9,     KC_F10,     KC_F11,     KC_F12,      SYS_PRT,    _______,    _______,
    _______,    LNK_BLE1,   LNK_BLE2,   LNK_BLE3,  LNK_RF,     _______,     _______,   _______,    _______,     _______,   _______,    _______,    _______,                 _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    DEV_RESET,  SLEEP_MODE,              BAT_SHOW,   _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                             _______,    _______,
    _______,                _______,    _______,   RGB_TEST,   _______,     BAT_NUM,   _______,    MO(4),       RGB_SPD,   RGB_SPI,    _______,                 _______,    RGB_VAI,    _______,
    _______,    _______,    _______,                                        _______,                            _______,   MO(1),      _______,                 RGB_MOD,    RGB_VAD,    RGB_HUI),

// layer win
[2] = LAYOUT_75_ansi(
    KC_ESC,     KC_F1,     KC_F2,       KC_F3,     KC_F4,      KC_F5,       KC_F6,     KC_F7,      KC_F8,       KC_F9,     KC_F10,     KC_F11,     KC_F12,      KC_PSCR,    KC_INS,     KC_DEL,
    KC_GRV,     KC_1,      KC_2,        KC_3,      KC_4,       KC_5,        KC_6,      KC_7,       KC_8,        KC_9,      KC_0,       KC_MINS,    KC_EQL,                  KC_BSPC,    KC_PGUP,
    KC_TAB,     KC_Q,      KC_W,        KC_E,      KC_R,       KC_T,        KC_Y,      KC_U,       KC_I,        KC_O,      KC_P,       KC_LBRC,    KC_RBRC,                 KC_BSLS,    KC_PGDN,
    KC_CAPS,    KC_A,      KC_S,        KC_D,      KC_F,       KC_G,        KC_H,      KC_J,       KC_K,        KC_L,      KC_SCLN,    KC_QUOT,                             KC_ENT,     KC_HOME,
    KC_LSFT,               KC_Z,        KC_X,      KC_C,       KC_V,        KC_B,      KC_N,       KC_M,        KC_COMM,   KC_DOT,     KC_SLSH,                 KC_RSFT,    KC_UP,      KC_END,
    KC_LCTL,    KC_LGUI,   KC_LALT,                                         KC_SPC,                             KC_RALT,   MO(3),      KC_RCTL,                 KC_LEFT,    KC_DOWN,    KC_RGHT),

// layer win Fn
[3] = LAYOUT_75_ansi(
    _______,    KC_BRID,    KC_BRIU,    _______,   _______,    _______,     _______,   KC_MPRV,    KC_MPLY,     KC_MNXT,   KC_MUTE,    KC_VOLD,    KC_VOLU,     _______,    _______,    _______,
    _______,    LNK_BLE1,   LNK_BLE2,   LNK_BLE3,  LNK_RF,     _______,     _______,   _______,    _______,     _______,   _______,    _______,    _______,                 _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    DEV_RESET,  SLEEP_MODE,              BAT_SHOW,   _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                             _______,    _______,
    _______,                _______,    _______,   RGB_TEST,   _______,     BAT_NUM,   _______,    MO(4),       RGB_SPD,   RGB_SPI,    _______,                 _______,    RGB_VAI,    _______,
    _______,    _______,    _______,                                        _______,                            _______,   MO(3),      _______,                 RGB_MOD,    RGB_VAD,    RGB_HUI),

// layer 4 Sidelight
[4] = LAYOUT_75_ansi(
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                             _______,    _______,
    _______,                _______,    _______,   _______,    _______,     _______,   _______,    _______,     SIDE_SPD,  SIDE_SPI,   _______,                 _______,    SIDE_VAI,   _______,
    _______,    _______,    _______,                                        _______,                            _______,   MO(4),      _______,                 SIDE_MOD,   SIDE_VAD,   SIDE_HUI),

// layer Mac QWERTY
[5] = LAYOUT_75_ansi(
    KC_ESC,     KC_BRID,   KC_BRIU,     KC_MCTL,   MAC_SEARCH, MAC_VOICE,   MAC_DND,   KC_MPRV,    KC_MPLY,     KC_MNXT,   KC_MUTE,    KC_VOLD,    KC_VOLU,     MAC_PRTA,   DF(0),     KC_DEL,
    KC_GRV,     KC_1,      KC_2,        KC_3,      KC_4,       KC_5,        KC_6,      KC_7,       KC_8,        KC_9,      KC_0,       KC_MINS,    KC_EQL,                  KC_BSPC,    KC_PGUP,
    KC_TAB,     KC_Q,      KC_W,        KC_E,      KC_R,       KC_T,        KC_Y,      KC_U,       KC_I,        KC_O,      KC_P,       KC_LBRC,    KC_RBRC,                 KC_BSLS,    KC_PGDN,
    KC_ESC,     HOME_A,    HOME_S,      HOME_D,    HOME_F,     KC_G,        KC_H,      HOME_J,     HOME_K,      HOME_L,    HOME_SCLN,  KC_QUOT,                             KC_ENT,     KC_HOME,
    SC_LSPO,               KC_Z,        KC_X,      KC_C,       KC_V,        KC_B,      KC_N,       KC_M,        KC_COMM,   KC_DOT,     KC_SLSH,                 SC_RSPC,    KC_UP,      KC_END,
    KC_LCTL,      KC_LALT,   KC_LGUI,                                         KC_SPC,                             KC_RGUI,   MO(6),      KC_RCTL,                 KC_LEFT,    KC_DOWN,    KC_RGHT),

// layer Mac Fn
[6] = LAYOUT_75_ansi(
    _______,    KC_F1,      KC_F2,      KC_F3,     KC_F4,      KC_F5,       KC_F6,     KC_F7,      KC_F8,       KC_F9,     KC_F10,     KC_F11,     KC_F12,      SYS_PRT,    _______,    _______,
    _______,    LNK_BLE1,   LNK_BLE2,   LNK_BLE3,  LNK_RF,     _______,     _______,   _______,    _______,     _______,   _______,    _______,    _______,                 _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    DEV_RESET,  SLEEP_MODE,              BAT_SHOW,   _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                             _______,    _______,
    _______,                _______,    _______,   RGB_TEST,   _______,     BAT_NUM,   _______,    MO(7),       RGB_SPD,   RGB_SPI,    _______,                 _______,    RGB_VAI,    _______,
    _______,    _______,    _______,                                        _______,                            _______,   MO(6),      _______,                 RGB_MOD,    RGB_VAD,    RGB_HUI),

// layer 7 Sidelight
[7] = LAYOUT_75_ansi(
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                             _______,    _______,
    _______,                _______,    _______,   _______,    _______,     _______,   _______,    _______,     SIDE_SPD,  SIDE_SPI,   _______,                 _______,    SIDE_VAI,   _______,
    _______,    _______,    _______,                                        _______,                            _______,   MO(7),      _______,                 SIDE_MOD,   SIDE_VAD,   SIDE_HUI),

// layer 8 Numpad
[8] = LAYOUT_75_ansi(
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    _______,    _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,     _______,                _______,    _______,
    _______,    KC_7,       KC_8,       KC_9,      KC_0,       KC_5,        KC_6,      KC_1,       KC_2,        KC_3,      KC_4,       _______,                             _______,    _______,
    _______,                _______,    _______,   _______,    _______,     _______,   _______,    _______,     _______,   _______,    _______,                 _______,    _______,    _______,
    _______,    _______,    _______,                                        MO(8),                              _______,   _______,    _______,                 _______,    _______,    _______)
};
