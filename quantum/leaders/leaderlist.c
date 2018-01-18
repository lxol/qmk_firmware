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
#include "leaders/leaderlist.h"

uint16_t current_leader;
uint32_t leader_sentinels;

void init_leaderlist() {
  curenet_leader = 0x0000;
  leade_sentinels = 0x00000000;
}

void set_current_leader(uint16_t l) {
  current_leader = l;
  return ;
}

void set_leader_sentinels(uint32_t s) {
  leader_sentinels = s;
  return;
}

void remove_sentinels(uint32_t s) {
  leader_sentinels &= ~s;
  return ;
}

bool remove_leader() {
  if (leader_sentinel == 0) {
    current_leader = 0x0000;
  }
  return true;
}

uint16_t get_leader(void) {
  return current_leader;
}
