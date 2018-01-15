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
uint16_t first_leader;
uint16_t last_leader;

uint8_t ref_layer;

__attribute__ ((weak))
void leaders_init_user(void) {}

__attribute__ ((weak))
bool process_leaders_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void leaders_range(uint16_t first, uint16_t last) {
  first_leader = first;
  last_leader = last;
}

void leaders_init(void) {
  init_leaderlist();
  init_press_state();
  leaders_init_user();
}

void set_ref_layer(uint8_t layer) {
  ref_layer = layer; 
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  /* leader key */
  /* no sequence leader key */
  /* sequence key */
  if (record->event.pressed) {
    if (keycode >= first_leader && keycode <= last_leader) {
      add_leader(keycode);
    }
    /* no leader -> normal processing */
    if (current_leader() == KC_NO) {
      return true;
    } 
    
    /* leader mode after this line */
    uint16_t ldr = current_leader();
    /* keep all presses. */
    if (ldr == keycode) {
      press_state_put(record->event.key, keycode);
      leaders_seq_reset();
      return process_leaders_user(ldr, record);
    } else {
      uint16_t kc = keymap_key_to_keycode(ref_layer, record->event.key);
      /* kc = KC_T; */
      leaders_seq_put(kc);
      uint16_t match_kc = leaders_match(ldr -  first_leader);
      if (match_kc == PARTIAL_MATCH) {
        press_state_put(record->event.key, KC_NO);
        /* return false; */
      } else if (match_kc == DO_NOT_MATCH) {
        leaders_seq_reset();
        remove_leader_oneshot(ldr);
        press_state_put(record->event.key, KC_NO);
      } else {
        if (match_kc < LEADERS_LAYER_MAX) {
          uint16_t layer_kc = keymap_key_to_keycode(match_kc, record->event.key);
          if (layer_kc == KC_NO) {
            leaders_seq_remove_last();
            press_state_put(record->event.key, KC_NO);
            return false;
          } else {
            match_kc = layer_kc;
          }
        }
        press_state_put(record->event.key, match_kc);
        leaders_seq_reset();
        remove_leader_oneshot(ldr);
        return process_leaders_user(match_kc, record);
      }
    }
    return false;
    /* return process_leaders_user(keycode, record); */
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
    remove_leader_momentary(kc);
    return process_leaders_user(kc, record);
  }
  return true;
}

#endif
