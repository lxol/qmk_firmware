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
#include "leaders/leadermanager.h"

/* uint16_t current_leader; */
uint16_t keyseq_sentinels;
uint16_t momentary_sentinels;
bool oneshot_sentinel;
uint16_t keyseq_codes[LEADERS_SEQ_MAX];
uint8_t keyseq_index;

__attribute__ ((weak))
void keyseq_press_user(uint16_t keycode) {
}

__attribute__ ((weak))
void keyseq_release_user(uint16_t keycode) {
}

const uint16_t** keyseq_definitions;

void keyseq_init(const uint16_t** user_keyseq_definitions) {
  keyseq_definitions = user_keyseq_definitions;
  /* keyseq_sentinels = 0x00000000; */
  momentary_sentinels = 0x0000;
  oneshot_sentinel = true;
  keyseq_index = 0;
}

void keyseq_push(uint16_t keycode) {
  momentary_sentinels |= (1U << keyseq_index );
  keyseq_codes[keyseq_index++] = keycode;
}

void keyseq_reset_oneshot() {
  if (momentary_sentinels == 0) {
    oneshot_sentinel = true;
    keyseq_index = 0;
  } else {
    oneshot_sentinel = false;
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

void keyseq_reset_momentary(uint8_t pos) {
  momentary_sentinels &= ~(1U << (pos - 1));
  if (oneshot_sentinel) {
    return;
  }
  if (momentary_sentinels == 0) {
    keyseq_index = 0;
  } else {
    keyseq_index = 1 + biton16(momentary_sentinels);
  }
  return ;
}

void keyseq_on_matches(bool press) {
  uint16_t i = 0;
  do {
    if (keyseq_definitions[i][0] == 0xffff) {
      return;
    }
    uint8_t j = 0;
    do  {
      if (keyseq_definitions[i][j] != keyseq_codes[j] &&
          keyseq_definitions[i][j] != KC_TRNS) {
        break;
      }
      if (keyseq_definitions[i][j+1] == KEYSEQ_END) {
        if (press) {
          keyseq_press_user(keyseq_definitions[i][j]);
        } else {
          /* TODO: reset momentary sentinel */
          keyseq_release_user(keyseq_definitions[i][j]);
        }
      }
      /* TODO: set momentary sentinel position */
    } while (true);
    i++;
  } while (true);
}

/* bool keyseq_reset() { */
/*   if (keyseq_sentinels == 0x00000000) { */
/*     keyseq_index = 0; */
/*     return true; */
/*   } */
/*   keyseq_index = 1; */
/*   return false; */
/* } */

/* bool keyseq_set(uint16_t leader) { */
/*   /\* find sentinels for the leader *\/ */
/*   /\*  *\/ */

/*   uint16_t i = 0; */
/*   do { */

/*     i++; */
/*   } while (true); */
/*   if (keyseq_sentinels == 0x00000000) { */
/*     keyseq_index = 0; */
/*     return true; */
/*   } */
/*   keyseq_index = 1; */
/*   return false; */
/* } */


/* uint8_t keyseq_get_index() { */
/*   return keyseq_index; */
/* } */
/* void keyseq_set_index(uint8_t index) { */
/*   keyseq_index = index; */
/* } */


/* uint16_t keyseq_pop() { */
/*   if (keyseq_index == 0) {return 0x0000;} */
/*   return keyseq_codes[keyseq_index--]; */
/* } */

/* uint16_t keyseq_get_definition(uint8_t row, uint8_t col) { */
/*   return keyseq_definitions[row][col]; */
/* } */

/* KEYSEQ_STATE keyseq_match_state(keyseq_pos_t pos) { */
/*   uint16_t val = keyseq_definitions[pos.row][pos.col]; */
/*   if (pos.col == 0 && val == 0xffff) { */
/*     return KEYSEQ_MISS; */
/*   } */
/*   if ((pos.col + 1) <= keyseq_index ) { */
/*     return KEYSEQ_MISS; */
/*   } */
/*   bool is_terminator = keyseq_definitions[pos.row][pos.col + 2] == KEYSEQ_END; */
/*   if (!is_terminator) { */
/*     return KEYSEQ_PARTIAL; */
/*   } */
/*   /\* TODO: check if  PREFIX *\/ */
/*   /\* do { *\/ */
/*   /\*   if (keyseq_definitions[i][0] == 0xffff) { *\/ */
/*   /\*     return (keyseq_pos_t) {.col = 0, .row = i}; *\/ */
/*   /\*   } *\/ */
/*   /\* } *\/ */
/*   return KEYSEQ_MATCH; */
/* } */

/* keyseq_pos_t keyseq_match_position(void) { */
/*   uint16_t i = 0; */
/*   do { */
/*     if (keyseq_definitions[i][0] == 0xffff) { */
/*       return (keyseq_pos_t) {.col = 0, .row = i}; */
/*     } */
/*     if (keyseq_definitions[i][1] != keyseq_codes[0]) { */
/*       i++; */
/*       continue; */
/*     } */
/*     uint8_t j = 2; */
/*     do  { */
/*       if (keyseq_definitions[i][j+1] == KEYSEQ_END) { */
/*         return (keyseq_pos_t) {.col = j-1, .row = i}; */
/*       } */
/*       if (j == keyseq_index + 1) { */
/*         return (keyseq_pos_t) {.col = j-1, .row = i}; */
/*       } */
/*       if (keyseq_definitions[i][j] == KC_TRNS) { */
/*         j++; */
/*         continue; */
/*       } */
/*       if (keyseq_definitions[i][j] == keyseq_codes[j-1]) { */
/*         j++; */
/*         continue; */
/*       } */
/*       return (keyseq_pos_t) {.col = j-1, .row = i }; */
/*     } while (true); */
/*     i++; */
/*   } while (true); */
/* } */

/* uint16_t keyseq_set_sentinels(uint32_t user_keyseq_sentinels) { */
/*   keyseq_sentinels = user_keyseq_sentinels; */
/*   return keyseq_sentinels; */
/* } */

/* uint16_t keyseq_remove_sentinels(uint32_t user_keyseq_sentinels) { */
/*   keyseq_sentinels &= ~user_keyseq_sentinels; */
/*   return keyseq_sentinels; */
/* } */

