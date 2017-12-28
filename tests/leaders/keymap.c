/* Copyright 2017 Fred Sundvik
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  LD_TEST,
};
// Don't rearrange keys as existing tests might rely on the order
// Col2, Row 0 has to be KC_NO, because tests rely on it

#define COMBO1 RSFT(LCTL(KC_O))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        // 0    1      2      3        4        5        6       7            8      9
        {KC_A,  LD_TEST,  KC_NO, KC_LSFT, KC_RSFT, KC_LCTL, COMBO1, SFT_T(KC_P), M(0),  KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,       KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,       KC_NO, KC_NO},
        {KC_C,  KC_D,  KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,       KC_NO, KC_NO},
    },
    [1] = {
        // 0    1      2      3        4        5        6       7            8      9
      { KC_A ,  KC_B ,  KC_C ,  KC_D ,  KC_E ,  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
      { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
      { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
      { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    } , 
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
        case 0:
            return MACRO(D(LSFT), T(H), U(LSFT), T(E), T(L), T(L), T(O), T(SPACE), W(100), 
            D(LSFT), T(W), U(LSFT), I(10), T(O), T(R), T(L), T(D), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LD_TEST:
      if (record->event.pressed) {
        register_code16(KC_B);
      } else {
        unregister_code16(KC_B);
      }
      return false;
      break;
  }
  return true;
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}


LEADERS_EXTERNS();
leader_t leaders[] = {
  (leader_t) {
    .keycode = LD_TEST,
    .oneshot = false
  },
  /* terminator */
  (leader_t) {
    .keycode = KC_NO
  }
};

void leaders_init_user(void) {
  leaders_ref_layer = 1;
}
