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

#ifndef PROCESS_LEADERS_H
#define PROCESS_LEADERS_H

#include "quantum.h"

#ifndef LEADERS_SEQ_MAX
#define LEADERS_SEQ_MAX  5
#endif

#ifndef LEADERS_PRESSED_MAX
#define LEADERS_PRESSED_MAX  5
#endif

#ifndef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER 0
#endif

#ifndef LEADERS_MAX
#define LEADERS_MAX  10
#endif

bool process_leaders(uint16_t keycode, keyrecord_t *record);



typedef struct {
  keypos_t key;
  uint16_t leader;
} leaders_press_t;


typedef struct {
  uint16_t keycode;
  bool oneshot;
  uint8_t reference_layer;
} leader_t;

bool is_leading(uint16_t keycode);

#if PLATFORM!=TEST
bool match_sequence(uint8_t num, ...);
#endif

typedef struct {
  uint16_t leader_keycode;
  keypos_t leader_key;
  uint16_t keycode_sequence[LEADERS_SEQ_MAX];
  keypos_t key_sequence[LEADERS_SEQ_MAX];
  uint8_t sequence_size;
  keypos_t pressed_keys[LEADERS_PRESSED_MAX];
  uint16_t pressed_leader[LEADERS_PRESSED_MAX];
  uint8_t pressed_state;
  bool oneshot;
  bool momentary;
  bool layer;
  uint8_t layer_num;
} leaders_state_t;


#define LEADERS_SEQ_LAYER(layer)                                        \
  uint16_t keycode = keymap_key_to_keycode(layer, leaders_state.key_sequence[leaders_state.sequence_size - 1]); \
  if (keycode == KC_NO || keycode == KC_TRNS) {                         \
    return false;                                                       \
  }                                                                     \
  register_code16(keycode);                                             \
  unregister_code16(keycode);

#ifdef __cplusplus
extern "C" {
#endif
void leaders_init(void);
void memorize_press(keypos_t key, uint16_t keycode);
void unmemorize_press(keypos_t key);
leaders_press_t recall_press(keypos_t key);
#ifdef __cplusplus
}
#endif

#define LEADERS_EXTERNS()                       \
  extern leaders_state_t leaders_state;         \
  extern leaders_press_t leaders_presses[];         \
  extern uint16_t press_state;                      \
  extern uint8_t foo_layer;                     \
  extern leader_t leaders[];                    \
  extern uint8_t leaders_ref_layer;


#endif
