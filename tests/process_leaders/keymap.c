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
  LD_LEADER3,
  SEQ_AB,
  SEQ_A,
  SEQ_OT,
  SEQ_IIE,
  SEQ_IEE,
  SEQ_LAYER_1
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {

    //{ 0 ,     1 ,       2 ,     3 ,     4 ,     5 ,          6 ,          7 ,          8 ,     9 ,       }
    { KC_A ,    KC_B ,    KC_C ,  KC_D ,  KC_E ,  LD_LEADER1 , LD_LEADER2 , LD_LEADER3 , KC_NO , KC_NO } , 
    { KC_NO ,   KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO ,      KC_NO ,      KC_NO ,      KC_NO , KC_NO } , 
    { KC_NO ,   KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO ,      KC_NO ,      KC_NO ,      KC_NO , KC_NO } , 
    { KC_NO ,   KC_NO ,   KC_NO , KC_NO , KC_NO , KC_NO ,      KC_NO ,      KC_NO ,      KC_NO , KC_NO } , 
    /* //{ 0 ,  1 ,       2 ,     3 ,     4 ,     5 ,          6 ,          7 ,          8 ,     9 ,       } */
    /* { KC_A , LD_TEST , LD_TEST2 , LD_TEST3 , KC_RSFT , KC_LCTL , COMBO1 , SFT_T(KC_P) , M(0) ,  KC_NO } ,  */
    /* { KC_NO , KC_NO ,   KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
    /* { KC_NO , KC_NO ,   KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
    /* { KC_C ,  KC_D ,    KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
  } ,          
  [1] = { 
    //{ 0 ,   1 ,     2 ,     3 ,     4 ,     5 ,     6 ,     7 ,     8 ,     9 ,       }
    { KC_A ,  KC_B ,  KC_C ,  KC_D ,  KC_E ,  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
  } ,          

};

#ifdef LEADERS_ENABLE

#define LD_FIRST LD_LEADER1
#define LD_LAST LD_LEADER3

uint16_t* leader1_seq[]  = {
  /* (const uint16_t[]){1, KC_T,  SEQ_AB }, */
  ( uint16_t[]){2, KC_A, KC_B, SEQ_AB },
  ( uint16_t[]){3, KC_I, KC_E, KC_E, SEQ_IEE},
  ( uint16_t[]){0}
};

uint16_t*  leader2_seq[]  = {
  ( uint16_t[]){2, KC_O, KC_T, SEQ_OT},
  ( uint16_t[]){1, KC_A, SEQ_A},
  /* (const uint16_t[]){2, KC_I, KC_E, SEQ_}, */
  ( uint16_t[]){0}
};

uint16_t*  leader3_seq[]  = {
  ( uint16_t[]){1, KC_TRNS, SEQ_LAYER_1 },
  ( uint16_t[]){0}
};

uint16_t** sequence_config[LD_LAST - LD_FIRST + 1];

void leaders_init_user(void) {
    sequence_config[LD_LEADER1 - LD_FIRST] = leader1_seq; 
    sequence_config[LD_LEADER2 - LD_FIRST] = leader2_seq; 
    sequence_config[LD_LEADER3 - LD_FIRST] = leader3_seq; 

    leaders_range(LD_FIRST, LD_LAST);
    set_ref_layer(0);
    leadermanager_set_config(sequence_config);
}

bool process_leaders_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case LD_LEADER1:
    if (record->event.pressed) {
      register_code16(KC_T);
      return false;
    } else {
      unregister_code16(KC_T);
      return false; 
    }
    break;
  case SEQ_AB:
    if (record->event.pressed) {
      register_code16(KC_I);
      return false; break;
    } else {
      unregister_code16(KC_I);
      return false; break;
    }
  case SEQ_A:
    if (record->event.pressed) {
      register_code16(KC_U);
      return false; break;
    } else {
      unregister_code16(KC_U);
      return false; break;
    }
  }
  return false;
}

#endif
