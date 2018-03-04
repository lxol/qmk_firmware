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
uint16_t momentary_sentinels;
bool oneshot_sentinel;
uint16_t keyseq_codes[LEADERS_SEQ_MAX];

uint16_t** keyseq_definitions;

uint8_t keyseq_index;
uint8_t ref_layer;

__attribute__ ((weak))
void leaders_init_user(void) {
}

__attribute__ ((weak))
void keyseq_set_definitions(uint16_t* k[]) {
  keyseq_definitions = k;
}

__attribute__ ((weak))
void keyseq_press_user(uint16_t keycode, bool pressed) {
}

__attribute__ ((weak))
void keyseq_release_user(uint16_t keycode) {
}

void leaders_init() {
  init_press_state();
  momentary_sentinels = 0x0000;
  oneshot_sentinel = true;
  keyseq_index = 0;
  leaders_init_user();
}

void keyseq_push(uint16_t keycode) {
  momentary_sentinels |= (1U << keyseq_index );
  keyseq_codes[keyseq_index++] = keycode;
}

void keyseq_reset_oneshot() {
  if (momentary_sentinels == 0) {
    oneshot_sentinel = true;
    keyseq_index = 0;
  } else {
    oneshot_sentinel = false;
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

void keyseq_reset_momentary(uint8_t pos) {
  momentary_sentinels &= ~(1U << (pos - 1));
  if (oneshot_sentinel) {
    return;
  }
  if (momentary_sentinels == 0) {
    keyseq_index = 0;
    oneshot_sentinel = true;
  } else {
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keyseq_push(keycode);
    uint16_t i = 0;
    do {
      uint8_t size = keyseq_definitions[i][0];
      if (size == 1) {
        /* reset, as we reach the end of the definition */
        momentary_sentinels = 0x0000;
        oneshot_sentinel = true;
        keyseq_index = 0;
        /* press_state_put( */
        /*                 (press_t) { */
        /*                   .key=record->event.key, */
        /*                     .ignore=true, */
        /*                     }); */
        return true;
      }
      uint8_t j = 1;
      do  {
        if (size < (keyseq_index + 2)) {
          break;
        }
        /* partial match  */
        if (j > 1 && j > keyseq_index) {
          press_state_put(
                          (press_t) {
                            .key=record->event.key,
                              .pos = j - 1, 
                              .ignore=true,
                            });
          return false;
        }
        if (keyseq_definitions[i][j] != keyseq_codes[j-1] && 
            keyseq_definitions[i][j] != KC_TRNS) {
          break;
        }
        if (j == size - 2) {
          /* bingo!  */
          keyseq_reset_oneshot();
          uint16_t k = keyseq_definitions[i][j+1];
          keyseq_press_user(k, true);
          press_state_put(
                          (press_t) {
                            .key=record->event.key,
                              .keycode=k,
                              .ignore=false,
                              .pos = j 
                            });
          return false;
        }
        j++;
        /* TODO: set momentary sentinel position */
      } while (true);
      i++;
    } while (true);
  } else {
    uint8_t idx = find_press(record->event.key);
    if (idx == LD_PRESS_MAX) {
      return true;
    }
    press_t press = press_state_get_press(idx);
    press_state_remove_by_idx(idx);
    keyseq_reset_momentary(press.pos);
    if (press.ignore) {
      return false;
    }
    keyseq_press_user(press.keycode, false);
    return false;
  }
  return true;
}

#endif
