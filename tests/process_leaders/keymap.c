 /* Copyright 2018 Alex Olkhovskiy
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

enum foobar {
  LD_LEADER1 = SAFE_RANGE,
  LD_LEADER2,
  SEQ_1,
  SEQ_2,
  SEQ_3,
  SEQ_4
};

enum test_layers {
  _LAYER1,
  _LAYER_REF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER1] = {
    /* { 0 ,       1 ,          2 ,     3 ,     4 ,     5 ,     6 ,     7 ,     8 ,     9 ,       } */
    { KC_Q ,       KC_W ,       KC_E ,  KC_R ,  KC_T  , KC_Y , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { LD_LEADER1 , LD_LEADER2 , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO ,      KC_NO ,      KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO ,      KC_NO ,      KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
 } ,               

  [_LAYER_REF] = {
    //{ 0 ,   1 ,     2 ,     3 ,     4 ,     5 ,     6 ,     7 ,     8 ,     9 ,       }
    { KC_A ,  KC_S ,  KC_NO , KC_NO , KC_NO , KC_G ,  KC_H ,  KC_NO , KC_NO , KC_NO } ,
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } ,
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } ,
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } ,
 } ,
 };

#ifdef LEADERS_ENABLE

uint16_t* user_definitions[]  = {
  (uint16_t[]){3, LD_LEADER1, SEQ_1},
  (uint16_t[]){5, LD_LEADER2, KC_E, KC_R, SEQ_2 },
  (uint16_t[]){5, LD_LEADER2, KC_E, KC_T, SEQ_3 },
  (uint16_t[]){5, LD_LEADER2, KC_E, KC_TRNS, SEQ_4 },
  (uint16_t[]){1}
};

void leaders_init_user(void) {
  keyseq_set_definitions(user_definitions);
}

void keyseq_press_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case SEQ_1:
    if (record->event.pressed) {
      register_code16(KC_1);
      return ;
    } else {
      unregister_code16(KC_1);
      return ;
    }
  case SEQ_2:
    if (record->event.pressed) {
      register_code16(KC_2);
      return ;
    } else {
      unregister_code16(KC_2);
      return ;
    }
  case SEQ_3:
    if (record->event.pressed) {
      register_code16(KC_3);
      return ;
    } else {
      unregister_code16(KC_3);
      return ;
    }
  case SEQ_4: {
    uint16_t ref_kc = keymap_key_to_keycode(_LAYER_REF, record->event.key);
    if (record->event.pressed) {
      register_code16(ref_kc);
      return ;
    } else {
      unregister_code16(ref_kc);
      return ;
    }
  }
  }
}

#endif
