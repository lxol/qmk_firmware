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

/* uint16_t current_leader; */
uint32_t keyseq_sentinels;
uint16_t keyseq_codes[LEADERS_SEQ_MAX];
uint8_t keyseq_index;

const uint16_t** keyseq_definitions;

void keyseq_init(const uint16_t** user_keyseq_definitions) {
  keyseq_definitions = user_keyseq_definitions;
  keyseq_sentinels = 0x00000000;
  keyseq_index = 0;
}

bool keyseq_reset() {
  if (keyseq_sentinels == 0x00000000) {
    keyseq_index = 0;
    return true;
  }
  return false;
}

void keyseq_push(uint16_t keycode) {
  keyseq_codes[keyseq_index++] = keycode;
}

uint16_t keyseq_pop() {
  if (keyseq_index == 0) {return 0x0000;}
  return keyseq_codes[keyseq_index--];
}

KEYSEQ_CMP keyseq_compare() {
  uint16_t i = 0;
  do {
    if (keyseq_definitions[i][0] == KEYSEQ_END) {
      /* KEYSEQ_END terminates the list of definition */
      return KEYSEQ_MISS;
    }
    if (keyseq_definitions[i][0] != keyseq_codes[0]) {
      i++;
      continue;
    }
    uint8_t j = 1;
    do  {
      if (keyseq_definitions[i][j+1] == KEYSEQ_END) {
        return  KEYSEQ_EQUAL;
      }
      if (j == keyseq_index) {
        return KEYSEQ_PARTIAL;
      }
      if (keyseq_definitions[i][j] == KC_TRNS) {
        j++;
        continue;
      }
      if (keyseq_definitions[i][j] == keyseq_codes[j]) {
        j++;
        continue;
      }
      return KEYSEQ_MISS;
    } while (true);
    i++;
  } while (true);
  /* return DO_NOT_MATCH; */
}

uint32_t keyseq_set_sentinels(uint32_t user_keyseq_sentinels) {
  keyseq_sentinels = user_keyseq_sentinels;
  return keyseq_sentinels;
}

uint32_t keyseq_remove_sentinels(uint32_t user_keyseq_sentinels) {
  keyseq_sentinels &= ~user_keyseq_sentinels;
  return keyseq_sentinels;
}
