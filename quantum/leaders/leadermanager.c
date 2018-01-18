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

void keyseq_init() {
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

void keyseq_set_definitions(const uint16_t** user_keyseq_definitions) {
  keyseq_definitions = user_keyseq_definitions;
}

KEYSEQ_ALIGNMENT keyseq_check_alignment() {
  if (keyseq_index == 0) {
    return KEYSEQ_PARTIALY_ALIGNED;
  }
  return KEYSEQ_ALIGNED;
  /* uint16_t result = DO_NOT_MATCH; */
  /* uint16_t i = 0; */
  /* uint16_t seq_size = sequence[0]; */
  /* do { */
  /*   uint16_t size = seq_config[leader_idx][i][0]; */
  /*   if (size == 0) { */
  /*     return result; */
  /*   } */
  /*   if (size < seq_size) { */
  /*     i++; */
  /*     continue; */
  /*   } */
  /*   uint16_t j = 1; */
  /*   do  { */
  /*     uint16_t kc = seq_config[leader_idx][i][j]; */
  /*     if (j == size + 1) { */
  /*       return  kc; */
  /*     } */
  /*     if (j == seq_size + 1) {return result;} */
  /*     if (sequence[j] == kc || kc == KC_TRNS) { */
  /*       result = PARTIAL_MATCH; */
  /*     } else { */
  /*       break; */
  /*     } */
  /*     j++; */
  /*   } while (true); */
  /*   i++; */
  /* } while (true); */
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
