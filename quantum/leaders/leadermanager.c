/* Copyright 2017 Alex Olkhovskiy
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
#include "leaders/leadermanager.h"

__attribute__ ((weak))
leaders_match_t leaders_match_user(uint16_t leader, uint8_t idx) {
  return DO_NOT_MATCH;
}

/* bool linkeq(uint8_t beg, uint8_t num, keypos_t key) { */

/*   return false; */
/* } */

/* void leader_action1(void); */
/* void leader_action2(void); */
/* void leader_action3(void); */

/* void leader_actions(uint16_t action_index) { */
/*   static  void (* const pf[3]) (void) = */
/*     { */
/*       leader_action1, leader_action2, leader_action3 */
/*     }; */
/*   return (*pf[action_index])(); */
/* } */

/* enum foobar { */
/*   LD_IIE,  */
/*   LD_IEE,  */
/*   LD_IE, */
/*   LD_E, */
/*   LD_R, */
/*   LD_D, */
/*   LD_F, */
/*   LD_LAST */
/* }; */

/* const uint16_t* names1[] = { */

/*   (uint16_t[]){KC_I,KC_E, KC_E, LD_IEE, KC_NO}, */
/*   (uint16_t[]){KC_I, KC_E, LD_IIE, KC_NO}, */
/*   (uint16_t[]){KC_NO} */
  
/* }; */

/* const uint16_t* names2[] = { */

/*   (uint16_t[]){1,2}, */
/*   (uint16_t[]){KC_I, KC_E} */
  
/* }; */

/* const uint16_t** fo[10]; */

void bar1qq(uint16_t a) {
  
} 
void foo1(void) {
  /* fo[1] = names1; */
  /* fo[2] = names2; */
  /* uint16_t a; */
  /* for (int8_t i = 0; i < 10; i++) { */
  /*   /\* a = fo[LEADER][SEQUENCE_NUMBER][KEY_POSITION IN SEQUENCE]; *\/ */
  /*   a = fo[i][0][1]; */
  /* } */
  /* for (uint8_t i = 0; i < 10; i++) { */
  /*   a = fo[i][0]; */
  /* } */
  /* bar1qq(a); */
  /* const uint8_t bar[LL_IIE] PROGMEM = {KC_I, KC_I}; */

  /* const uint8_t *bar[] = {LD_IIE, LD_IE}; */
  /* for (uint8_t i = 0; i < 2; i++) { */
  /*   layer_on(bar[i][1]); */
  /* } */
}

/* uint16_t  *seqs[LD_LAST]; */
/* seqs[LD_IIE] = {KC_I, KC_I, KC_E, KC_NO}; */

/* const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20}; */
