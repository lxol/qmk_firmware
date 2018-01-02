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
#include "leaders/keychain.h"

#ifndef LEADERS_SEQ_MAX
#define LEADERS_SEQ_MAX  5
#endif

#ifndef LEADERS_PRESSED_MAX
#define LEADERS_PRESSED_MAX  5
#endif

/* #ifndef LD_PRESS_MAX */
#define LD_PRESS_MAX 16
/* #endif */

#ifndef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER 0
#endif

#ifndef LEADERS_MAX
#define LEADERS_MAX  10
#endif

bool process_leaders(uint16_t keycode, keyrecord_t *record);
bool is_leading(uint16_t keycode);

typedef struct {
  /* keypos_t leader_key; */
  uint16_t keycode_sequence[LEADERS_SEQ_MAX];
  keypos_t key_sequence[LEADERS_SEQ_MAX];
  uint8_t sequence_size;
  bool layer;
  uint8_t layer_num;
} leaders_state_t;

typedef struct {
  uint16_t keycode;
  bool oneshot;
  uint8_t reference_layer;
} leader_t;

typedef struct {
  keypos_t key;
  uint16_t leader;
  uint16_t keycode;
} leaders_press_t;

#ifdef __cplusplus
extern "C" {
#endif
  void leaders_init(void);
  void memorize_press(keypos_t key, uint16_t keycode, uint16_t leader);
  bool unmemorize_press(keypos_t key);
  leaders_press_t recall_press(keypos_t key);
  void ld_add_leader(uint16_t keycode);
  /* void ld_remove_leader(uint16_t keycode); */
  uint16_t ld_current_leader(void);
  bool peq(uint8_t num, uint16_t keycode);
  leaders_press_t recall_press_by_idx(uint8_t idx);
  bool ld_leader_eq(uint16_t keycode);
  void ld_remove_current_leader_oneshot(void);
  void ld_remove_leader_oneshot(uint16_t keycode);
  void ld_remove_leader_momentary(uint16_t keycode);
  void ld_remove_leader_force(uint16_t keycode);
#ifdef __cplusplus
}
#endif


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
  extern uint16_t press_state;                     \
  extern uint16_t ld_leaders[];                     \
  extern bool ld_oneshot;                           \
  extern bool ld_momentary;                         \
  extern uint8_t ld_leader_index;                   \
  extern leader_t leaders[];                    \
  extern uint8_t leaders_ref_layer;


#endif
