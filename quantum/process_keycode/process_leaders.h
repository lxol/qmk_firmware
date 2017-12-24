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
void leaders_init(void);
void clear_sequence(void);
bool leaders_seq_match(uint8_t num, ...);

typedef struct {
  uint16_t leader_keycode;
  keypos_t leader_key;
  uint16_t keycode_sequence[LEADERS_SEQ_MAX];
  keypos_t key_sequence[LEADERS_SEQ_MAX];
  uint8_t sequence_size;
  keypos_t pressed_keys[LEADERS_PRESSED_MAX];
  bool oneshot;
  bool momentary;
  bool layer;
  uint8_t layer_num;
} leaders_state_t;

typedef struct {
  uint16_t keycode;
  bool oneshot;
  bool toggle_layer;
  uint8_t toggle_layer_number;
  uint8_t reference_layer;
} leader_t;


#define IS_LEADING(leaders_keycode)                             \
  if ((leaders_state.sequence_size != 0)                        \
      && (leaders_state.momentary || leaders_state.oneshot)     \
      && (leaders_state.leader_keycode == leaders_keycode ))

#define BEGIN_SEQ(...) if (leaders_seq_match(__VA_ARGS__)) {

#define END_SEQ                                 \
  clear_sequence();               \
  leaders_state.oneshot = false;                \
  return false;                                 \
  }


#define LEADERS_SEQ_LAYER(layer)                                        \
  uint16_t keycode = keymap_key_to_keycode(layer, leaders_state.key_sequence[leaders_state.sequence_size - 1]); \
  if (keycode == KC_NO || keycode == KC_TRNS) {                         \
    return false;                                                       \
  }                                                                     \
  register_code16(keycode);                                             \
  unregister_code16(keycode);


#define LEADERS_EXTERNS()                       \
  extern leaders_state_t leaders_state;         \
  extern uint8_t foo_layer;                     \
  extern leader_t leaders[];                    \
  extern uint8_t leaders_ref_layer;


#endif
