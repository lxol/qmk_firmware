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
#include "leaders/press_state.h"

/* bool press_state_mods_guarded = false; */
/* uint16_t press_state_mods = 0x0000; */

/* uint16_t get_press_state_mods() { */
/*   return press_state_mods; */
/* } */
/* void set_press_state_mods(uint16_t mods) { */
/*   press_state_mods |= mods; */
/* } */

/* void remove_press_state_mods(uint16_t mods) { */
/*   press_state_mods &= ~mods; */
/* } */

/* void press_state_guard_mods() { */
/*   press_state_mods_guarded = true; */
/* } */

/* void press_state_unguard_mods() { */
/*   press_state_mods_guarded = false; */
/* } */

/* bool press_state_is_mods_guraded() { */
/*   return press_state_mods_guarded; */
/* } */

uint16_t press_state;
press_t presses[LD_PRESS_MAX];

bool release_guard = false;

uint16_t releases[LD_RELEASES_MAX];

uint16_t delayed_releases[LD_RELEASES_MAX];

void replace_keycode(uint16_t from, uint16_t to,  uint16_t *array) {
  for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) {
    if (array[i] != from) {
      continue;
    }
    releases[i] = to;
    return;
  }
  return;
}

void press_state_replace_releases_keycode(uint16_t from, uint16_t to) {
  replace_keycode(from, to, releases);
}

void press_state_replace_delayed_releases_keycode(uint16_t from, uint16_t to) {
  replace_keycode(from, to, delayed_releases);
}

void press_state_init_releases() {
  for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) {
    releases[i] = KC_NO;
  }
}

void press_state_init_delayed_releases() {
  for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) {
    delayed_releases[i] = KC_NO;
  }
}

bool press_state_releases_has_keycode(uint16_t keycode) {
  for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) {
    if (releases[i] == keycode) {
      return true;
    }
  }
  return false;
}

bool press_state_delayed_releases_is_empty(uint16_t keycode) {
  for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) {
    if (delayed_releases[i] != KC_NO) {
      return false;
    }
  }
  return true;
}

uint16_t* press_state_get_delayed_release(void) {
  return delayed_releases;
}
/* void press_state_release_put(uint16_t keycode) { */
/*   for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) { */
/*     if (releases[i] != KC_NO) { */
/*       continue; */
/*     } */
/*     releases[i] = keycode; */
/*     return; */
/*   } */
/*   return; */
/* } */

/* void press_state_delayed_release_put(uint16_t keycode) { */
/*   for (int8_t i = 0; i < LD_RELEASES_MAX; i ++) { */
/*     if (delayed_releases[i] != KC_NO) { */
/*       continue; */
/*     } */
/*     delayed_releases[i] = keycode; */
/*     return; */
/*   } */
/*   return; */
/* } */

press_t* presses_get() {
  return presses;
}

void init_press_state(void) {
  press_state = 0UL;
}

uint16_t press_state_get(void) {
  return press_state;
}

void press_state_put(press_t press) {
  for (int8_t i = 0; i < LD_PRESS_MAX; i ++) {
    if (press_state & (1U << i)) {
      continue;
    }
    press_state |= (1U << i);
    presses[i] = press;
    return;
  }
  return;
}

uint8_t find_press(keypos_t key) {
  if (press_state == 0) {return LD_PRESS_MAX;}
  uint8_t l = biton16(press_state);
  for (int8_t i = 0; i <= l; i++) {
    if (press_state & (1U << i)) {
      if (KEYEQ(presses[i].key, key)) {
        return i;
      }
    }
  }
  return LD_PRESS_MAX;
}

press_t press_state_get_press(uint8_t idx) {
  return presses[idx];
}

bool press_state_remove_by_idx(uint8_t idx) {
  if (idx == LD_PRESS_MAX) {return false;}
  press_state &= ~(1U << idx);
  return true;
}
