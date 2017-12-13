/* Copyright 2016 Jack Humbert
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

#ifndef DISABLE_BOSS

#include "process_boss.h"

__attribute__ ((weak))
void boss_start(void) {}

__attribute__ ((weak))
void boss_end(void) {}

// Boss key stuff
uint8_t bossing = 0;
uint16_t boss_time = 0;
/* uint8_t boss_layer = 0; */

uint16_t boss_sequence[5] = {0, 0, 0, 0, 0};
uint8_t boss_sequence_size = 0;

uint8_t boss_layer;
keypos_t boss_keypos;

uint8_t boss_queue = 0;                /*  */
/* layer = biton32(layer_state); */
bool process_boss(uint16_t keycode, keyrecord_t *record) {
  // Boss key set-up
  if (record->event.pressed) {
    if (bossing == 0
        && keycode >= KC_BOSS1
        && keycode < (KC_BOSS1 + 10)) {
      boss_layer = biton32(layer_state);
      boss_start();
      bossing = keycode - KC_BOSS1 + 1;
      boss_time = timer_read();
      boss_reset();
      boss_queue = bossing;
      return false;
    }
    if (bossing > 0 || boss_queue > 0) {
      /* if (boss_queue > 0) {boss_queue = 0;} */
      uint8_t default_layer = biton32(default_layer_state);
      boss_keypos = record->event.key;
      uint16_t default_keycode = keymap_key_to_keycode(default_layer, boss_keypos);
      boss_sequence[boss_sequence_size] = default_keycode;
      boss_sequence_size++;
      return false;
    }
  } else {
    keypos_t key = record->event.key;
    uint16_t boss_keycode = keymap_key_to_keycode(boss_layer, key);
    if (bossing > 0
        && boss_keycode == (KC_BOSS1 + bossing - 1)) { 
        /* && boss_keycode < (KC_BOSS1 + 10)) { */
      /* boss_end(); */
      bossing = 0;
      return false;
    }
  }
  return true;
}

void boss_reset(void) {
  boss_sequence_size = 0;
  boss_sequence[0] = 0;
  boss_sequence[1] = 0;
  boss_sequence[2] = 0;
  boss_sequence[3] = 0;
  boss_sequence[4] = 0;

}
#endif
