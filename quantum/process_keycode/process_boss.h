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

bool process_boss(uint16_t keycode, keyrecord_t *record);

void boss_start(void);
void boss_end(void);
void boss_reset(void);

#define SEQ_BOSS_ONE_KEY(key) if (boss_sequence[0] == (key) && boss_sequence[1] == 0 && boss_sequence[2] == 0 && boss_sequence[3] == 0 && boss_sequence[4] == 0)
#define SEQ_BOSS_TWO_KEYS(key1, key2) if (boss_sequence[0] == (key1) && boss_sequence[1] == (key2) && boss_sequence[2] == 0 && boss_sequence[3] == 0 && boss_sequence[4] == 0)
#define SEQ_BOSS_THREE_KEYS(key1, key2, key3) if (boss_sequence[0] == (key1) && boss_sequence[1] == (key2) && boss_sequence[2] == (key3) && boss_sequence[3] == 0 && boss_sequence[4] == 0)
#define SEQ_BOSS_FOUR_KEYS(key1, key2, key3, key4) if (boss_sequence[0] == (key1) && boss_sequence[1] == (key2) && boss_sequence[2] == (key3) && boss_sequence[3] == (key4) && boss_sequence[4] == 0)
#define SEQ_BOSS_FIVE_KEYS(key1, key2, key3, key4, key5) if (boss_sequence[0] == (key1) && boss_sequence[1] == (key2) && boss_sequence[2] == (key3) && boss_sequence[3] == (key4) && boss_sequence[4] == (key5))

#define BOSS_EXTERNS() extern uint8_t bossing; extern uint16_t boss_time; extern uint16_t boss_sequence[5]; extern uint8_t boss_sequence_size
/* #define BOSS_DICTIONARY() if (bossing) */

#endif
