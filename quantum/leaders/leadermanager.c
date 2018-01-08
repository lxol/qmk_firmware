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

uint16_t sequence[LEADERS_SEQ_MAX];

const uint16_t*** sequence_config;

uint8_t sequence_size = 0;

void leaders_seq_put(uint16_t keycode) {
  sequence[sequence_size++] = keycode;
}

void leaders_seq_reset() {
  sequence_size = 0;
}

void leadermanager_set_config(const uint16_t*** config) {
  sequence_config = config;
}

uint16_t leaders_match(uint8_t leader_idx, uint16_t* seq, const uint16_t*** config) {
  if (seq[0] == 0) {
    return PARTIAL_MATCH;
  }
  uint16_t result = DO_NOT_MATCH;
  uint16_t i = 0;
  do {
    uint16_t size = config[leader_idx][i][0];
    if (size == 0) {
      return result;
    }
    uint16_t seq_size = seq[0];
    if (size < seq_size) {
      i++;
      continue;
    }
    uint16_t j = 1;
    do  {
      uint16_t kc = config[leader_idx][i][j];
      if (j == size + 1) {
        return  kc;
      }
      if (seq[j] == kc || kc == KC_TRNS) {
        result = PARTIAL_MATCH;
      } else {
        break;
      }
      j++;
    } while (true);
    i++;
  } while (true);
  return DO_NOT_MATCH;
}
