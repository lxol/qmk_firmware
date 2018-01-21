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
uint16_t keyseq_sentinels;
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
  keyseq_index = 1;
  return false;
}

uint8_t keyseq_get_index() {
  return keyseq_index;
}
void keyseq_set_index(uint8_t index) {
  keyseq_index = index;
}

void keyseq_push(uint16_t keycode) {
  keyseq_codes[keyseq_index++] = keycode;
}

uint16_t keyseq_pop() {
  if (keyseq_index == 0) {return 0x0000;}
  return keyseq_codes[keyseq_index--];
}

uint16_t keyseq_get_definition(uint8_t row, uint8_t col) {
  return keyseq_definitions[row][col];
}

KEYSEQ_STATE keyseq_match_state(keyseq_pos_t pos) {
  uint16_t val = keyseq_definitions[pos.row][pos.col];
  if (pos.col == 0 && val == 0xffff) {
    return KEYSEQ_MISS;
  }
  if ((pos.col + 1) < keyseq_index ) {
    return KEYSEQ_MISS;
  }
  bool is_terminator = keyseq_definitions[pos.row][pos.col + 2] == KEYSEQ_END;
  if (is_terminator) {
    return KEYSEQ_MATCH;
  } else {
    return KEYSEQ_PARTIAL;
  }
}

keyseq_pos_t keyseq_match_position(void) {
  uint16_t i = 0;
  do {
    if (keyseq_definitions[i][0] == 0xffff) {
      return (keyseq_pos_t) {.col = 0, .row = i};
    }
    if (keyseq_definitions[i][1] != keyseq_codes[0]) {
      i++;
      continue;
    }
    uint8_t j = 2;
    do  {
      if (keyseq_definitions[i][j+1] == KEYSEQ_END) {
        return (keyseq_pos_t) {.col = j-1, .row = i};
      }
      if (j == keyseq_index + 1) {
        return (keyseq_pos_t) {.col = j-1, .row = i};
      }
      if (keyseq_definitions[i][j] == KC_TRNS) {
        j++;
        continue;
      }
      if (keyseq_definitions[i][j] == keyseq_codes[j-1]) {
        j++;
        continue;
      }
      return (keyseq_pos_t) {.col = j-1, .row = i };
    } while (true);
    i++;
  } while (true);
}

uint16_t keyseq_set_sentinels(uint32_t user_keyseq_sentinels) {
  keyseq_sentinels = user_keyseq_sentinels;
  return keyseq_sentinels;
}

uint16_t keyseq_remove_sentinels(uint32_t user_keyseq_sentinels) {
  keyseq_sentinels &= ~user_keyseq_sentinels;
  return keyseq_sentinels;
}
