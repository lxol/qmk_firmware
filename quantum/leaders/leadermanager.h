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

#define MOMENTARY_SENTINEL  0x0001
#define ONESHOT_SENTINEL  0x0002

/* void key(const uint16_t** config[]); */

typedef enum {
  KEYSEQ_ALIGNED = 0,	
  KEYSEQ_PARTIALY_ALIGNED,
  KEYSEQ_UNALIGNED
} KEYSEQ_ALIGNMENT;

void keyseq_init(void);
bool keyseq_reset(void);
void keyseq_push(uint16_t keycode);
uint16_t keyseq_pop(void);
void keyseq_set_definitions(const uint16_t** user_keyseq_definitions);
KEYSEQ_ALIGNMENT keyseq_check_alignment(void);



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
