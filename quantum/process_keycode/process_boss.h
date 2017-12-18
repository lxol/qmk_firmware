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

#ifndef PROCESS_BOSS_H
#define PROCESS_BOSS_H

#include "quantum.h"

#ifndef BOSS_SEQ_MAX
#define BOSS_SEQ_MAX  5
#endif

#ifndef BOSS_REFERENCE_LAYER
#define BOSS_REFERENCE_LAYER 0
#endif

bool process_boss(uint16_t keycode, keyrecord_t *record);
void boss_start(void);
void boss_end(void);
void boss_state_init(uint16_t keycode, keypos_t key);
void boss_state_clear_sequence(void);
bool boss_seq_cmp (uint8_t num, ...);
void boss_seq_layer(uint8_t layer, uint8_t num, ...);

typedef struct {
  uint16_t keycode_seq[BOSS_SEQ_MAX];
  keypos_t key_seq[BOSS_SEQ_MAX];
  uint8_t sequence_size;
  uint16_t keycode;
  keypos_t key;
  keypos_t seq_key;
  bool oneshot;
  bool momentary;
  uint16_t time;
} boss_t;

typedef struct {
  uint16_t mo_first;
  uint16_t mo_last;
  uint16_t os_first;
  uint16_t os_last;
} boss_range_t;

#define BOSS_SEQ(...) if (boss_seq_cmp(__VA_ARGS__))

#define BOSS_SEQ_LAYER(...) boss_seq_layer(__VA_ARGS__);

#define IS_BOSSING(boss_keycode) \
  if (boss_state.keycode == boss_keycode && (boss_state.momentary || boss_state.oneshot))

#define BOSS_EXTERNS() \
  extern boss_t boss_state; \
  extern boss_range_t boss_range; \
  extern uint8_t boss_ref_layer; \
  extern void boss_state_init(uint16_t keycode, keypos_t key);


#endif
