/* Copyright 2016 Jack Humbert
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

#ifdef BOSS_ENABLE

#include "process_boss.h"

__attribute__ ((weak))
void boss_start(void) {}

__attribute__ ((weak))
void boss_end(void) {}

boss_t boss_state;
uint8_t boss_ref_layer = 0;
/* uint8_t boss_ref_layer = biton32(default_layer_state); */
keypos_t no_key = (keypos_t) {
  .row = MATRIX_ROWS + 1,
  .col = MATRIX_COLS + 1
};

// Boss key stuff
uint8_t bossing = 0;
uint16_t boss_time = 0;
/* uint8_t boss_layer = 0; */

uint16_t boss_sequence[5] = {0, 0, 0, 0, 0};
uint8_t boss_sequence_size = 0;

uint8_t boss_layer;
keypos_t boss_keypos;
keypos_t boss_current_keypos;

uint8_t boss_queue = 0;                /*  */

void boss_init() {
  boss_state_reset();
}

void boss_state_print(void) {
  xprintf("BOSS STATE:\r\n");
  xprintf("   boss_state.key row:%d, col: %d\r\n", boss_state.key.row, boss_state.key.col);
  xprintf("   boss_state.oneshot :%d\r\n", boss_state.oneshot);
  xprintf("   boss_state.keycode :%d\r\n", boss_state.keycode);
  xprintf("   boss_state.sequence_size :%d\r\n", boss_state.sequence_size);
  for (uint8_t i = 0; i < 5; ++i)
    xprintf("        boss_state.sequence[%d] keycode: %d\r\n", i, boss_state.sequence[i]);
}

/* layer = biton32(layer_state); */
bool process_boss(uint16_t keycode, keyrecord_t *record) {
  //TODO: control presses and releases  -- too complicated

  //TODO: add a delay to a potential boss key on the layer
  //      to deal with out of order but almost at the same time
  //      pressings

  // ignore modifiers
  // TODO: make it configurable
  /* print("print \r\n" ); */
  /* printf("printf process boss, keycode %d \r\n", keycode  ); */
 
  keypos_t foo = record->event.key;
  boss_state_print();
  xprintf("KEY keycode %d row: %d col: %d pressed: %d \r\n", keycode, foo.row, foo.col, record->event.pressed    );
  xprintf(" INFO bossing %d row: %d col: %d queue: %d, boss_layer: %d \r\n", bossing, boss_keypos.row, boss_keypos.col, boss_queue, boss_layer    );
  if (keycode == KC_LCTL ||
      keycode == KC_RCTL ||
      keycode == KC_LGUI ||
      keycode == KC_RGUI ||
      keycode == KC_LSFT ||
      keycode == KC_RSFT ||
      keycode == KC_LALT ||
      keycode == KC_RALT ) {
    return true;
  }
  // Boss key set-up
/* #define KEYEQ(keya, keyb)       ((keya).row == (keyb).row && (keya).col == (keyb).col) */
  if (record->event.pressed) {
    if (keycode >= KC_BOSS1 && keycode < (KC_BOSS1 + 10)) {
      xprintf("  START BOSSING \r\n"  );
      boss_state_reset();
      boss_state.keycode = keycode;
      boss_state.key = record->event.key;
      // TODO: wrap oneshot in #ifdef BOSS_ONESHOT
      boss_state.oneshot = true;
      boss_state.momentary = true;
      boss_state.time = timer_read();
      return false;
    }
    if (boss_state.momentary || boss_state.oneshot) {
      xprintf("  PRESS non-boss KEY UNDER BOSSING \r\n"  );
      uint16_t boss_ref_keycode = keymap_key_to_keycode(boss_ref_layer, record->event.key);
      boss_state.sequence[boss_state.sequence_size++] = boss_ref_keycode;
      return false;
    }
  } else {
    if (boss_state.momentary && KEYEQ(boss_state.key, record->event.key)) { 
      xprintf("  RELEASE bossing KEY UNDER BOSSING \r\n"  );
      boss_state.momentary = false;
      /* boss_state_reset(); */
      return false;
    }
    
    if (boss_state.momentary || boss_state.oneshot) {
      xprintf("  RELEASE non bossing KEY UNDER BOSSING \r\n"  );
      return  false;
    }
  }
  xprintf("    not affected by bossing \r\n");
  return true;
}

void boss_reset(void) {
  boss_sequence_size = 0;
  boss_sequence[0] = 0;
  boss_sequence[1] = 0;
  boss_sequence[2] = 0;
  boss_sequence[3] = 0;
  boss_sequence[4] = 0;
}

void boss_state_clear_sequence(void) {
  for (uint8_t i = 0; i < 5; ++i)
    boss_state.sequence[i] = 0;
  boss_state.sequence_size = 0;
}

void boss_state_reset(void) {
  for (uint8_t i = 0; i < 5; ++i)
    boss_state.sequence[i] = 0;
  boss_state.sequence_size = 0;
  boss_state.oneshot = false;
  boss_state.momentary = false;
  boss_state.key = no_key;
  boss_state.keycode = 0;
  boss_state.time = timer_read();
}

#endif
