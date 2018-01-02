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


uint16_t leaders[LEADERS_MAX];
bool oneshot;
bool momentary;
uint8_t leader_index;

void init_leaderlist(void) {
  for (uint8_t i = 0; i < LEADERS_MAX; i ++) {
    leaders[i] = KC_NO;
  }
  leader_index = 0;
}

void add_leader(uint16_t keycode) {
  leaders[leader_index++] = keycode;
  oneshot = true;
  momentary = true;
  return;
}


void remove_leader(uint16_t keycode, bool want_oneshot, bool want_momentary) {
  for (uint8_t i = 0; i < leader_index; i++) {
    if (leaders[i] != keycode) {
      continue;
    }
    if (i == (leader_index - 1)) {
      if (want_oneshot && !want_momentary) {
        if (momentary) {
          /* Remove oneshot protection. */
          oneshot = false;
          break;
        } else {
          /*  */
            leader_index--;
            oneshot = false; /* Lower leader already used its oneshot protection. */
            momentary = true; /* Lower leader can only be momentary, otherwise it could've gone already. */
            break;
        }
      } else if (!want_oneshot && want_momentary) {
        if (oneshot) {
          /* Can not remove the leader but indicate that we no longer hold it. */
          momentary = false;
        } else {
          leader_index--;
          momentary = true;
          oneshot = false;
          break;
        }
      } else if (want_oneshot && want_momentary) {
          leader_index--;
          momentary = true;
          oneshot = false;
      }
      break;
    }
    /* swap */
    for (uint8_t j = i; j < (leader_index - 1); j++) {
      leaders[j] ^= leaders[j+1];
      leaders[j+1] ^= leaders[j];
      leaders[j] ^= leaders[j+1];
    }
    leader_index--;
    break;
  }
  return;
}

void remove_leader_oneshot(uint16_t keycode) {
  remove_leader(keycode, true, false);
}

void remove_leader_momentary(uint16_t keycode) {
  remove_leader(keycode, false, true);
}

void remove_leader_force(uint16_t keycode) {
  remove_leader(keycode, true, true);
}

void remove_current_leader_oneshot(void) {
  if (leader_index == 0) {return;}
  remove_leader_oneshot(leaders[leader_index -1]);
}

bool leader_eq(uint16_t keycode) {
  if (leader_index == 0) {return false;}
  if (leaders[leader_index - 1] == keycode) {
    return true;
  }
  return false;
}

uint16_t current_leader(void) {
  if (leader_index == 0) {return KC_NO;}
  return leaders[leader_index - 1];
}
