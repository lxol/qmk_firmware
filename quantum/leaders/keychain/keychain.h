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
#ifndef KEYCHAIN_H
#define KEYCHAIN_H

#include "keyboard.h"

#ifndef KEYCHAIN_MAX
#define KEYCHAIN_MAX 50
#endif

void keychain_init(void);

/* Removes first element of the active chain */
/* uint8_t keychain_remove_first(void); */

/* Removes last element of the active chain */
/* uint8_t keychain_remove_last(void); */

/* Append the specified element to the end of the active chain */
uint8_t keychain_add(keypos_t key);

/* Returns the number of elements in the active chain  */
uint8_t keychain_size(void);

/* Return the position of the first element in the active chain */
uint8_t keychain_first(void);

/* Return the position of the last element in the active chain */
uint8_t keychain_last(void);

/* free the chain starting from the specified position */
void keychain_free(uint8_t pos);

typedef struct {
  uint8_t next;
  keypos_t key;
} keychain_t;

#ifdef __cplusplus
#define KEYCHAIN_EXTERNS()                      \
  extern keychain_t links[];                    \
  extern uint8_t first_idx;                     \
  extern uint8_t last_idx;                      \
  extern uint8_t free_idx;                     
#endif

#endif
