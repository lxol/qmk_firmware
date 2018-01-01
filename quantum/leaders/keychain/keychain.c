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
#include "leaders/keychain/keychain.h"

keychain_t links[KEYCHAIN_MAX];
uint8_t first_idx;
uint8_t last_idx;
uint8_t free_idx;
uint8_t size;

/* keypos_t root_key = (keypos_t) { */
/*   .row = 0xFF, */
/*   .col = 0xFF */
/* }; */
/* keychain_t free_links[KEYCHAIN_MAX]; */

void keychain_init(void) {
  size = 0;
  /* first_idx = KEYCHAIN_MAX; */
  /* last_idx = KEYCHAIN_MAX; */
  free_idx = 0;
  for (int8_t i = 0; i < KEYCHAIN_MAX; i++) {
    links[i] = (keychain_t) {
      .next = i + 1,
    };
  }
}

uint8_t keychain_add(keypos_t key) {
  if (size == 0) {
    first_idx = free_idx;
  } else {
    links[last_idx].next = free_idx;
  }
  last_idx = free_idx;
  free_idx = links[free_idx].next;
  links[last_idx].key = key;
  links[last_idx].next = KEYCHAIN_MAX;
  size++;
  return last_idx;
}

uint8_t keychain_size(void) {
  return size; 
}

uint8_t keychain_first(void) {
  return first_idx; 
}

uint8_t keychain_last(void) {
  return last_idx;
}

void keychain_free(uint8_t idx) {
  uint8_t i = idx;
  while (links[i].next != KEYCHAIN_MAX) {
    i = links[i].next;
  }
  links[i].next = free_idx;
  free_idx = idx;
  size = 0;
}
