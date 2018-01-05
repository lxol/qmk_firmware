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
#define PARTIAL_MATCH 1
#define DO_NOT_MATCH 0


uint16_t leaders_match(uint8_t leader_idx, uint16_t* seq, const uint16_t*** config);
/* typedef bool (*chain_fun) () */
uint16_t leaders_match_user(uint16_t leader, uint8_t idx);


/* bool linkeq(uint8_t beg, uint8_t pos, keypos_t key); */

#endif
