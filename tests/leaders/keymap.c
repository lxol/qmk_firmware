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

enum test_keycodes {
  LEFT = SAFE_RANGE,
  LD_TEST,
  LD_TEST2,
  LD_TEST3
};
uint16_t ld_test = LD_TEST;
uint16_t ld_test2 = LD_TEST2;
uint16_t ld_test3 = LD_TEST3;

// Don't rearrange keys as existing tests might rely on the order
// Col2, Row 0 has to be KC_NO, because tests rely on it

#define COMBO1 RSFT(LCTL(KC_O))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        // 0    1      2      3        4        5        6       7            8      9
        { KC_A ,  LD_TEST , LD_TEST2 , LD_TEST3 ,  KC_RSFT , KC_LCTL , COMBO1 , SFT_T(KC_P) , M(0) ,  KC_NO } , 
        { KC_NO , KC_NO ,   KC_NO ,       KC_NO , KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } , 
        { KC_NO , KC_NO ,   KC_NO ,       KC_NO , KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } , 
        { KC_C ,  KC_D ,    KC_NO ,       KC_NO , KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO} , 
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

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*   switch (keycode) { */
/*     case LD_TEST: */
/*       if (record->event.pressed) { */
/*         register_code16(KC_B); */
/*       } else { */
/*         unregister_code16(KC_B); */
/*       } */
/*       return false; */
/*       break; */
/*   } */
/*   return true; */
/* } */

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}


LEADERS_EXTERNS();
leader_t leaders[] = {
  (leader_t) {
    .keycode = LD_TEST,
    .oneshot = true
  },
  (leader_t) {
    .keycode = LD_TEST2,
    .oneshot = true
  },
  /* terminator */
  (leader_t) {
    .keycode = KC_NO
  }
};

void leaders_init_user(void) {
  leaders_ref_layer = 1;
}

bool process_sequence_press_user(void) {
  if (is_leading(LD_TEST)) {
    if (peq(1, KC_A)) {
      register_code16(KC_B);
      /* unregister_code16(KC_B); */
      /* ld_remove_leader_oneshot(LD_TEST); */
      ld_remove_current_leader_oneshot();
      leaders_state.sequence_size = 0;
    }
    return false;
  }
  return true;
}

bool process_sequence_release_user(uint16_t leader, uint16_t keycode) {
  if (leader == LD_TEST) {
    if (keycode == KC_A) {
      unregister_code16(KC_B);
      return false;
    }
  }
  return true;
}

bool process_leader_press_user(uint16_t leader) {
  if (leader == LD_TEST3) {
    register_code16(KC_Y);
  }
  return false;
}

bool process_leader_release_user(uint16_t leader) {
  if (leader == LD_TEST3) {
    unregister_code16(KC_Y);
  }
  return false;
}
