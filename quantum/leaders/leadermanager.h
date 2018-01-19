/* Copyright 2017 Alex Olkhovskiy
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
#ifndef LEADEMANAGER_H
#define LEADEMANAGER_H

#include "keyboard.h"
#include "keycode.h"

#ifndef LEADERS_SEQ_MAX
#define LEADERS_SEQ_MAX 10
#endif

#define PARTIAL_MATCH 254
#define DO_NOT_MATCH 255

/* define sentinels */
#define KEYSEQ_MOMENTARY  0b1
#define KEYSEQ_ONESHOT    0b10
#define KEYSEQ_SENTINEL1  0b100
#define KEYSEQ_SENTINEL2  0x1000
#define KEYSEQ_SENTINEL3  0x10000
#define KEYSEQ_SENTINEL4  0x100000
#define KEYSEQ_SENTINEL5  0x1000000
#define KEYSEQ_SENTINEL6  0x10000000

#define KEYSEQ_END  0x0000

/* void key(const uint16_t** config[]); */

typedef struct {
    uint16_t col;
    uint16_t row;
} keyseq_pos_t;

typedef enum {
  KEYSEQ_EQUAL = 0,	
  KEYSEQ_PARTIAL,
  KEYSEQ_MISS
} KEYSEQ_CMP;

void keyseq_init(const uint16_t** user_keyseq_definitions);
bool keyseq_reset(void);
uint8_t keyseq_get_index(void);
void keyseq_push(uint16_t keycode);
uint16_t keyseq_pop(void);
KEYSEQ_CMP keyseq_compare(void);
keyseq_pos_t keyseq_position(void);


/* uint16_t leaders_match(uint8_t leader_idx); */
/* void leaders_seq_put(uint16_t keycode); */
/* void leaders_seq_reset(void); */
/* void leaders_seq_remove_last(void); */

/* void init_leadermanager(void); */
/* void set_leader(uint16_t l); */
/* void set_leader_sentinels(uint32_t s); */
/* void remove_leader_sentinels(uint32_t s); */
/* bool remove_leader(void); */
/* uint16_t get_leader(void); */

/* uint16_t leaders_seq_debug_get_at(uint8_t index); */

#endif
