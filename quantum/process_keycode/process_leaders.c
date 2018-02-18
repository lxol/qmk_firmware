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

#include "print.h"

/* #include "debug.h" */
uint8_t ref_layer;

const uint16_t** keyseq_definitions;

__attribute__ ((weak))
void keyseq_press_user(uint16_t keycode) {
}

__attribute__ ((weak))
void keyseq_release_user(uint16_t keycode) {
}

void leaders_init(const uint16_t** user_keyseq_definitions) {
  keyseq_definitions = user_keyseq_definitions;
  keyseq_init();
  init_press_state();
  /* leaders_init_user(); */
}

void set_ref_layer(uint8_t layer) {
  ref_layer = layer;
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {

    /* uint16_t i = 0; */
    /* do { */
    /*   if (keyseq_definitions[i][0] == 0xffff) { */
    /*     return; */
    /*   } */
    /*   uint8_t j = 0; */
    /*   do  { */
    /*     if (keyseq_definitions[i][j] != keyseq_codes[j] && */
    /*         keyseq_definitions[i][j] != KC_TRNS) { */
    /*       break; */
    /*     } */
    /*     if (keyseq_definitions[i][j+1] == KEYSEQ_END) { */
    /*       if (press) { */
    /*         keyseq_press_user(keyseq_definitions[i][j]); */
    /*       } else { */
    /*         /\* TODO: reset momentary sentinel *\/ */
    /*         keyseq_release_user(keyseq_definitions[i][j]); */
    /*       } */
    /*     } */
    /*     /\* TODO: set momentary sentinel position *\/ */
    /*   } while (true); */
    /*   i++; */
    /* } while (true); */
  } else {
  }
  return true;
}

#endif
