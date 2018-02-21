/* Copyright 2016 Alex Olkhovskiy
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

#ifdef LEADERS_ENABLE

#include "process_leaders.h"

#include "print.h"

/* #include "debug.h" */
uint16_t momentary_sentinels;
bool oneshot_sentinel;
uint16_t keyseq_codes[LEADERS_SEQ_MAX];

/* array of pointers to uint16_t (first element of the array) */

uint16_t** keyseq_definitions;
/* uint16_t* keyseq_definitions[]  = { */
/*   /\* (uint16_t[]){KC_A, KC_B, KEYSEQ_END }, *\/ */
/*   (uint16_t[]){0xffff} */
/* }; */

uint8_t keyseq_index;
uint8_t ref_layer;

__attribute__ ((weak))
void keyseq_definitionsinit(uint16_t* k[]) {
  keyseq_definitions = k;
  /* uint16_t foo1[1] = (uint16_t[]) {0xffff}; */
  /* keyseq_definitions = &foo1[0]; */
  /* keyseq_definitions[0]  = { */
  /*   (uint16_t[]){0xffff} */
  /* }; */
}

__attribute__ ((weak))
void keyseq_press_user(uint16_t keycode) {
}

__attribute__ ((weak))
void keyseq_release_user(uint16_t keycode) {
}

/* void leaders_init(const uint16_t** user_keyseq_definitions) { */
/*   keyseq_definitions = user_keyseq_definitions; */
/* void set_keyseq_definitions(uint16_t* kd[]) { */
/*   keyseq_definitions = kd; */
/* } */

void leaders_init() {
  /* keyseq_definitions = _keyseq_definitions; */
  
  init_press_state();
  /* momentary_sentinels = strlen(foobaraaa); */
  momentary_sentinels = 0x0000;
  oneshot_sentinel = true;
  keyseq_index = 0;
}

void keyseq_push(uint16_t keycode) {
  momentary_sentinels |= (1U << keyseq_index );
  keyseq_codes[keyseq_index++] = keycode;
}

void keyseq_reset_oneshot() {
  if (momentary_sentinels == 0) {
    oneshot_sentinel = true;
    keyseq_index = 0;
  } else {
    oneshot_sentinel = false;
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

void keyseq_reset_momentary(uint8_t pos) {
  momentary_sentinels &= ~(1U << (pos - 1));
  if (oneshot_sentinel) {
    return;
  }
  if (momentary_sentinels == 0) {
    keyseq_index = 0;
  } else {
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

/* void set_ref_layer(uint8_t layer) { */
/*   ref_layer = layer; */
/* } */

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    uint16_t i = 0;
    do {
      if (keyseq_definitions[i][0] == 0xffff) {
        /* break; */
        return false;
      }
      uint8_t j = 0;
      uint8_t size = sizeof(keyseq_definitions[i]);
      do  {
        if (size != keyseq_index) {
          break;
        }
        if (keyseq_definitions[i][j] != keyseq_codes[j] &&
            keyseq_definitions[i][j] != KC_TRNS) {
          break;
        }
        if (i == size) {
          keyseq_press_user(keyseq_definitions[i][j]);
          return false;
        }
        /* TODO: set momentary sentinel position */
      } while (true);
      i++;
    } while (true);
  } else {
  }
  return true;
}

#endif
