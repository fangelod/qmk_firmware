/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "rgb_matrix_map.h"

#define MODS_ALT_MASK (MOD_BIT(KC_LALT)) // Make ALT layer for encoder use 
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)) // Make CTRL layer for encoder use

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)      BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DELETE,        KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,          KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),


};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MODS_ALT_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    } else if (get_mods() & MODS_CTRL_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    } else if (IS_LAYER_ON(1)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        if (clockwise) {
          tap_code(KC_MNXT);
        } else {
          tap_code(KC_MPRV);
        }
    }
    return false;
}
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
void loop_colorset(const uint8_t *indices, int array_size, uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < array_size; i++) {
        rgb_matrix_set_color(indices[i], red, green, blue);
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case 1:
            rgb_matrix_set_color(LED_DEL, 255, 255, 255);
            rgb_matrix_set_color(LED_BSLS, 255, 255, 255);
            break;
        default:
            loop_colorset(LED_REGION_MAIN, (sizeof(LED_REGION_MAIN) / sizeof(LED_REGION_MAIN[0])), 255, 255, 255)
            loop_colorset(LED_REGION_FUNCTION_ROW, (sizeof(LED_REGION_FUNCTION_ROW) / sizeof(LED_REGION_FUNCTION_ROW[0])), 255, 0, 0)
            loop_colorset(LED_REGION_PAGE_ACTIONS, (sizeof(LED_REGION_PAGE_ACTIONS) / sizeof(LED_REGION_PAGE_ACTIONS[0])), 0, 0, 255)
            loop_colorset(LED_REGION_LEFT_STRIP, (sizeof(LED_REGION_LEFT_STRIP) / sizeof(LED_REGION_LEFT_STRIP[0])), 255, 255, 255);
            loop_colorset(LED_REGION_RIGHT_STRIP, (sizeof(LED_RIGHT_STRIP) / sizeof(LED_REGION_RIGHT_STRIP[0])), 255, 255, 255)
            break;
    }
    

    // if caps lock is on, set left led strip to red
    bool caps = host_keyboard_led_state().caps_lock;
    if (caps) {
        loop_colorset(LED_REGION_LEFT_STRIP, (sizeof(LED_REGION_LEFT_STRIP) / sizeof(LED_REGION_LEFT_STRIP[0])), 255, 0, 0);
        rgb_matrix_set_color(LED_CAPS, 255, 0, 0);
    }
}

#endif // RGB_MATRIX_ENABLE