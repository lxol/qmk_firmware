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
#ifndef LEADERLIST_H
#define LEADERLIST_H


#include "keyboard.h"
#include "keycode.h"


#ifndef LEADERS_MAX
#define LEADERS_MAX  10
#endif

typedef struct {
  uint16_t keycode;
  bool oneshot;
  uint8_t reference_layer;
} leader_t;

void init_leaderlist(void);
uint16_t current_leader(void);
void add_leader(uint16_t keycode);
void remove_leader(uint16_t keycode, bool want_oneshot, bool want_momentary);
void remove_leader_oneshot(uint16_t keycode);
void remove_leader_momentary(uint16_t keycode);
void remove_leader_force(uint16_t keycode);

#endif
