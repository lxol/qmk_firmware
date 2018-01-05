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
#ifndef PRESSSTATE_H
#define PRESSSTATE_H


#define LD_PRESS_MAX 16
#include "keyboard.h"

#include "keycode.h"

typedef struct {
  keypos_t key;
  uint16_t leader;
  uint16_t keycode;
} leaders_press_t;

void memorize_press(keypos_t key, uint16_t keycode, uint16_t leader);
bool unmemorize_press(keypos_t key);
leaders_press_t recall_press(keypos_t key);

#endif
