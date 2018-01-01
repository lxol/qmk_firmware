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

keypos_t root_key = (keypos_t) {
  .row = 0xFF,
  .col = 0xFF
};
/* keychain_t free_links[KEYCHAIN_MAX]; */

void keychain_init(void) {
  first_idx = 0;
  last_idx = 0;
  free_idx = 1;
  links[0] = (keychain_t) {
    .next = KEYCHAIN_MAX,
    .key = root_key
    
  };
  for (int8_t i = 1; i < KEYCHAIN_MAX; i++) {
    links[i] = (keychain_t) {
      .next = i + 1,
    };
  }
}
