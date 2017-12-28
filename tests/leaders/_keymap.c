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

enum test_layers {
  _MAIN,
  _RAISE
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER = _MAIN

enum test_keycodes {
  LEFT = SAFE_RANGE,
  LD_TEST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = {
        // 0    1      2      3        4        5        6       7            8      9
        { KC_A ,    KC_B ,  KC_NO , KC_LSFT , KC_NO , KC_LCTL , KC_NO , KC_NO , KC_NO , KC_NO } , 
        { LD_TEST , KC_NO , KC_NO , KC_NO ,   KC_NO , KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO } , 
        { KC_NO ,   KC_NO , KC_NO , KC_NO ,   KC_NO , KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO } , 
        { KC_C ,    KC_D ,  KC_NO , KC_NO ,   KC_NO , KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO } , 
 } ,                
 };

LEADERS_EXTERNS();

leader_t leaders[] = {
  (leader_t) {
    .keycode = LD_TEST,
    .oneshot = true
  },
  /* terminator */
  (leader_t) {
    .keycode = KC_NO
  }
};

void leaders_init_user(void) {
  leaders_ref_layer = biton32(default_layer_state);
}

bool process_sequence_press_user(void) {
  if (is_leading(LD_TEST)) {
    register_code16(KC_Z);
  }
  return false;
}
