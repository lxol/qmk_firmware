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
#include "leaders/press_state.h"

typedef struct {
  keypos_t key;
  uint16_t keycode;
} leaders_press_t;

uint16_t press_state;
leaders_press_t presses[LD_PRESS_MAX];

void init_press_state(void) {
  press_state = 0UL;
}

uint16_t press_state_get(void) {
  return press_state;
}

void press_state_put(keypos_t key, uint16_t keycode) {
  for (int8_t i = 0; i < LD_PRESS_MAX; i ++) {
    if (press_state & (1U << i)) {
      continue;
    }
    press_state |= (1U << i);
    presses[i].key = key;
    presses[i].keycode = keycode;
    return;
  }
  press_state = 0U;
}

uint8_t press_state_biton16(uint16_t bits)
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
  uint8_t l = press_state_biton16(press_state);
  for (int8_t i = 0; i < l; i++) {
    if (press_state & (1U << i)) {
      if (KEYEQ(presses[i].key, key)) {
        return i;
      }
    }
  }
  return LD_PRESS_MAX;
}

uint16_t press_state_remove(keypos_t key) {
  uint8_t idx = find_press(key);
  if (idx == LD_PRESS_MAX) {return KC_NO;}
  press_state &= ~(1U << idx);
  return presses[idx].keycode;
}

/* bool unmemorize_press_by_idx(uint8_t idx) { */
/*   if (idx == LD_PRESS_MAX) {return false;} */
/*   press_state &= ~(1U << idx); */
/*   return true; */
/* } */

/* leaders_press_t recall_press(keypos_t key) { */
/*   uint8_t idx = find_press(key); */
/*   if (idx == LD_PRESS_MAX) { */
/*     return (leaders_press_t) { */
/*       .key = leaders_no_key, */
/*         .leader = KC_NO, */
/*         .keycode = KC_NO */
/*     }; */
/*   } */
/*   return presses[idx]; */
/* } */


/* leaders_press_t recall_press_by_idx(uint8_t idx) { */
/*   if (idx == LD_PRESS_MAX) { */
/*     return (leaders_press_t) { */
/*       .key = leaders_no_key, */
/*         .leader = KC_NO, */
/*         .keycode = KC_NO */
/*     }; */
/*   } */
/*   return presses[idx]; */
/* } */
