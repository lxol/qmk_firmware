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
/* void boss_state_reset(void); */
void boss_state_init(uint16_t keycode, keypos_t key);
void boss_state_clear_sequence(void);
bool boss_seq_has (uint16_t keycode, ...);

#define BOSS_SEQ(...) if (boss_seq_has(__VA_ARGS__))

typedef struct {
  uint16_t sequence[BOSS_SEQ_MAX];
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

#define IS_BOSSING(boss_keycode) \
  if (boss_state.keycode == boss_keycode && (boss_state.momentary || boss_state.oneshot))

#define BOSS_EXTERNS() extern uint8_t bossing;\
  extern boss_t boss_state; \
  extern boss_range_t boss_range; \
  extern uint8_t boss_ref_layer; \
  extern uint16_t boss_sequence[BOSS_SEQ_MAX]; 

/* #define BOSSING_LAYER(boss_keycode, layer )                 \ */
/*   if (bossing == (boss_keycode - 1 + 1) || \ */
/*       boss_queue == (boss_keycode - 1 + 1)) { \ */
/*     if (boss_sequence[0] != 0 \ */
/*         && boss_sequence[1] == 0 \ */
/*         && boss_sequence[2] == 0 \ */
/*         && boss_sequence[3] == 0 \ */
/*         && boss_sequence[4] == 0) \ */
/*       { \ */
/*         uint16_t keypos_keycode = keymap_key_to_keycode(layer, boss_keypos); \ */
/*         register_code(keypos_keycode); \ */
/*         unregister_code(keypos_keycode);     \ */
/*         boss_queue = 0;  \ */
/*         boss_reset(); \ */
/*         return;  \ */
/*       } \ */
/*   } */

#endif
