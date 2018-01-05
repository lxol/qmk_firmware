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
#include "leaders/pressstate.h"

uint16_t press_state;
leaders_press_t leaders_presses[LD_PRESS_MAX];

keypos_t leaders_no_key = (keypos_t) {
  .row = 10,
  .col = 10
};

void memorize_press(keypos_t key, uint16_t keycode, uint16_t leader) {
  for (int8_t i = 0; i < LD_PRESS_MAX; i ++) {
    if (press_state & (1U << i)) {
      continue;
    }
    press_state |= (1U << i);
    leaders_presses[i].key = key;
    leaders_presses[i].keycode = keycode;
    leaders_presses[i].leader = leader;
    /* break; */
    return;
  }
  press_state = 0U;
}

uint8_t leaders_biton16(uint16_t bits)
{
    uint8_t n = 0;
    if (bits >> 8) { bits >>= 8; n += 8;}
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    if (bits)      { n += 1;}
    return n;
}

uint8_t find_press(keypos_t key) {
  if (press_state == 0) {return LD_PRESS_MAX;}
  uint8_t l = leaders_biton16(press_state);
  for (int8_t i = 0; i < l; i++) {
    if (press_state & (1U << i)) {
      if (KEYEQ(leaders_presses[i].key, key)) {
        return i;
      }
    }
  }
  return LD_PRESS_MAX;
}

bool unmemorize_press(keypos_t key) {
  uint8_t idx = find_press(key);
  if (idx == LD_PRESS_MAX) {return false;}
  press_state &= ~(1U << idx);
  return true;
}

bool unmemorize_press_by_idx(uint8_t idx) {
  if (idx == LD_PRESS_MAX) {return false;}
  press_state &= ~(1U << idx);
  return true;
}

leaders_press_t recall_press(keypos_t key) {
  uint8_t idx = find_press(key);
  if (idx == LD_PRESS_MAX) {
    return (leaders_press_t) {
      .key = leaders_no_key,
        .leader = KC_NO,
        .keycode = KC_NO
    };
  }
  return leaders_presses[idx];
}


leaders_press_t recall_press_by_idx(uint8_t idx) {
  if (idx == LD_PRESS_MAX) {
    return (leaders_press_t) {
      .key = leaders_no_key,
        .leader = KC_NO,
        .keycode = KC_NO
    };
  }
  return leaders_presses[idx];
}
