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
uint8_t ref_layer;

__attribute__ ((weak))
void leaders_init_user(void) {}

__attribute__ ((weak))
void keyseq_first_user(uint16_t keycode, keyrecord_t *record) {
}

__attribute__ ((weak))
void keyseq_around_last_user(uint16_t keycode, keyrecord_t *record) {
}

__attribute__ ((weak))
void keyseq_last_user(uint16_t keycode, keyrecord_t *record) {
}

void leaders_init(void) {
  /* keyseq_init(); */
  init_press_state();
  leaders_init_user();
}

void set_ref_layer(uint8_t layer) {
  ref_layer = layer;
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (keyseq_get_index() == 0) {
      keyseq_push(keycode);
    } else {
      uint16_t kc = keymap_key_to_keycode(ref_layer, record->event.key);
      keyseq_push(kc);
    }
    keyseq_pos_t dpos = keyseq_match_position();
    KEYSEQ_STATE keyseq_state = keyseq_match_state(dpos);
    
    switch(keyseq_state) {
    case KEYSEQ_MISS: {
      keyseq_reset();
      return true;
    }
    case KEYSEQ_PARTIAL: {
      if (keyseq_get_index() == 1) {
        keyseq_set_sentinels(keyseq_get_definition(dpos.row, 0));
        press_state_put(record->event.key, keycode);
        keyseq_first_user(keycode, record);
      } else 
        press_state_put(record->event.key, KC_NO);
      }
      return false;
    case KEYSEQ_MATCH: {
      if (keyseq_get_index() == 1) {
        keyseq_set_sentinels(keyseq_get_definition(dpos.row,0));
        press_state_put(record->event.key, keyseq_get_definition(dpos.row, dpos.col + 1));
        keyseq_first_user(keycode, record);
        keyseq_last_user(keyseq_get_definition(dpos.row, dpos.col + 1), record);
      } else {
        press_state_put(record->event.key, keyseq_get_definition(dpos.row, dpos.col + 1));
        keyseq_last_user(keyseq_get_definition(dpos.row, dpos.col + 1), record);
      }
      return false;
    }
    }
  }
  if (!record->event.pressed) {
    if (press_state_get() == 0UL) {return true;}
    uint8_t idx = find_press(record->event.key);
    if (idx == LD_PRESS_MAX) {
      return true;
    }
    uint16_t kc = press_state_remove_by_idx(idx);
    if (kc == KC_NO) {
      return false;
    }
    keyseq_remove_sentinels(KEYSEQ_MOMENTARY);
    keyseq_reset();
    keyseq_last_user(kc, record);
    return false;
  }
  return true;
}

#endif
