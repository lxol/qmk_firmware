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
#include "leaders/leaderlist.h"

uint32_t leaders[LEADERS_MAX];
/* uint16_t leaders_momentary[LEADERS_MAX]; */
uint8_t leader_index;

void init_leaderlist() {
  for (uint8_t i = 0; i < LEADERS_MAX; i ++) {
    leaders[i] = 0x00000000;
  }
  leader_index = 0;
}

uint8_t add_leader(uint16_t keycode) {
  leaders[leader_index++] = keycode;
  return leader_index;
}

bool add_guards(uint16_t keycode, uint16_t guards) {
  for (uint8_t i = 0; i < leader_index; i++) {
    if ((leaders[i] & 0x0000ffff) == keycode) {
      leaders[i] = leaders[i] | ((uint32_t) guards  << 16);
      return true;
    }
  }
  return false;
}
bool remove_guards(uint16_t keycode, uint16_t guards) {
  for (uint8_t i = 0; i < leader_index; i++) {
    if ((leaders[i] & 0x0000ffff) == keycode) {
      leaders[i] = leaders[i] & ~((uint32_t) guards << 16);
      return true;
    }
  }
  return false;
}

bool remove_leader(uint16_t keycode) {
  for (uint8_t i = 0; i < leader_index; i++) {

    if (leaders[i] != keycode) {
      continue;
    }
    /* squash */
    for (uint8_t j = i; j < (leader_index - 1); j++) {
      leaders[j] ^= leaders[j+1];
      leaders[j+1] ^= leaders[j];
      leaders[j] ^= leaders[j+1];
    }
    leader_index--;
    return true;
  }
  return false;
}

/* bool leader_eq(uint16_t keycode) { */
/*   if (leader_index == 0) {return false;} */
/*   if (leaders[leader_index - 1] == keycode) { */
/*     return true; */
/*   } */
/*   return false; */
/* } */

uint16_t current_leader(void) {
  if (leader_index == 0) {return KC_NO;}
  return leaders[leader_index - 1] & 0x0000ffff;
}
