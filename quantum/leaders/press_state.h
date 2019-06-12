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
#ifndef PRESS_STATE_H
#define PRESS_STATE_H


#define LD_PRESS_MAX 16
#define LD_RELEASES_MAX 8 
#include "keyboard.h"

#include "keycode.h"
#include "util.h"

typedef struct {
  keypos_t key;
  uint16_t keycode;
  bool ignore;
  uint16_t sentinels;
  uint8_t pos;
} press_t;

void init_press_state(void);
uint16_t press_state_get(void);
uint8_t find_press(keypos_t key);
bool press_state_remove_by_idx(uint8_t idx);
void press_state_put(press_t press);
press_t press_state_get_press(uint8_t idx);
press_t* presses_get(void);

void press_state_replace_releases_keycode(uint16_t from, uint16_t to);
void press_state_replace_delayed_releases_keycode(uint16_t from, uint16_t to);
void press_state_init_releases(void);
void press_state_init_delayed_releases(void);
bool press_state_releases_has_keycode(uint16_t keycode);
bool press_state_delayed_releases_is_empty(uint16_t keycode);
uint16_t* press_state_get_delayed_release(void);
/* uint16_t get_press_state_mods(void); */
/* void set_press_state_mods(uint16_t mods); */
/* void remove_press_state_mods(uint16_t mods); */

/* void press_state_guard_mods(void); */

/* void press_state_unguard_mods(void); */

/* bool press_state_is_mods_guraded(void); */

/* #define M_RSFT 0x0001 */
/* #define M_LSFT 0x0002 */
/* #define M_RCTL 0x0004 */
/* #define M_LCTL 0x0008 */
/* #define M_RALT 0x0010 */
/* #define M_LALT 0x0020 */
/* #define M_RGUI 0x0040 */
/* #define M_LGUI 0x0080 */
/* #define M_MOD1 0x0100 */
/* #define M_MOD2 0x0200 */
/* #define M_MOD3 0x0400 */
/* #define M_MOD4 0x0800 */
/* #define M_MOD5 0x1000 */
/* #define M_MOD6 0x2000 */
/* #define M_MOD7 0x4000 */
/* #define M_MOD8 0x8000 */

#endif
