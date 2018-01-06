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

#ifdef LEADERS_ENABLE

#include "process_leaders.h"

uint16_t first_leader;
uint16_t last_leader;

__attribute__ ((weak))
void leaders_init_user(void) {}

void leaders_range(uint16_t first, uint16_t last) {
  first_leader = first;
  last_leader = last;
}
void leaders_init(void) {
  init_leaderlist();
  init_press_state();
  leaders_init_user();
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (keycode >= first_leader && keycode <= last_leader) {
      add_leader(keycode);
    }
  }
  if (!record->event.pressed) {

  }
  return true;
}

#endif
