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
keychain_t free_links[KEYCHAIN_MAX];

void keychain_init(void) {
  for (int8_t i = 0; i < KEYCHAIN_MAX; i++) {
    free_links[i] = (keychain_t) {
      .next = i + 1,
    };
  }
}
