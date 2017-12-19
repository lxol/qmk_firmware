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

uint8_t boss_ref_layer = BOSS_REFERENCE_LAYER;

boss_range_t boss_range = (boss_range_t) {.mo_first = KC_NO,
                                          .mo_last = KC_NO,
                                          .os_first = KC_NO,
                                          .os_last = KC_NO};

keypos_t boss_no_key = (keypos_t) {
  .row = MATRIX_ROWS,
  .col = MATRIX_COLS
};
/* void boss_state_print(void) { */
/*   xprintf("BOSS STATE:\r\n"); */
/*   xprintf("   boss_state.key row:%d, col: %d\r\n", boss_state.key.row, boss_state.key.col); */
/*   xprintf("   boss_state.seq_key row:%d, col: %d\r\n", boss_state.seq_key.row, boss_state.seq_key.col); */
/*   xprintf("   boss_state.oneshot :%d\r\n", boss_state.oneshot); */
/*   xprintf("   boss_state.keycode :%d\r\n", boss_state.keycode); */
/*   xprintf("   boss_state.sequence_size :%d\r\n", boss_state.sequence_size); */
/*   for (uint8_t i = 0; i < BOSS_SEQ_MAX; ++i) */
/*     xprintf("        boss_state.keycode_seq[%d] keycode: %d\r\n", i, boss_state.keycode_seq[i]); */
/* } */

bool process_boss(uint16_t keycode, keyrecord_t *record) {
  //TODO: control presses and releases  -- too complicated

  //TODO: add a delay to a potential boss key on the layer
  //      to deal with out of order but almost at the same time
  //      pressings

  // ignore modifiers
  // TODO: make it configurable
  /* boss_state_print(); */
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

  /* Manage boss key press */
  if (record->event.pressed) {
    bool is_mo_boss_pressed = keycode >= boss_range.mo_first && keycode <= boss_range.mo_last;
    bool is_os_boss_pressed = keycode >= boss_range.os_first && keycode <= boss_range.os_last;
    if (is_mo_boss_pressed || is_os_boss_pressed) {
      boss_state_init(keycode, record->event.key);
      boss_state.oneshot = is_os_boss_pressed;
      boss_state.momentary = true;
      return false;
    }
  }

  /* Manage boss key release */
  if (!record->event.pressed) {
    bool is_boss_released = boss_state.momentary && KEYEQ(boss_state.key, record->event.key);
    if (is_boss_released) {
      boss_state.momentary = false;
      return false;
    }
  }

  bool bossing_mode = boss_state.momentary || boss_state.oneshot;
  /* Keep track all keys pressed under bossing mode */
  if (bossing_mode && record->event.pressed) {
    for (uint8_t i = 0; i < BOSS_PRESSED_MAX; i++) {
      if (KEYEQ(boss_state.key_pressed_seq[i], boss_no_key)) {
        boss_state.key_pressed_seq[i] = record->event.key;
        xprintf("ADD pressed: row: pos: %d, %d, col %d\r\n", i, record->event.key.row, record->event.key.col);
        break;
      }
    }
  }
  
  /* Keys pressed in bossing_mode should not progress. */
  if (!record->event.pressed) {
    for (uint8_t i = 0; i < BOSS_PRESSED_MAX; i++) {
      if (KEYEQ(boss_state.key_pressed_seq[i], record->event.key)) {
        boss_state.key_pressed_seq[i] = boss_no_key;
        xprintf("RELEASE  pos: %d, row: %d, col %d \r\n", i, record->event.key.row, record->event.key.col);
        return false;
      }
    }
    return true;
  }

  /* This is a guard for unmanaged sequences.*/
  /* Start from scratch, when sequence reaches the maximum size.  */
  if (record->event.pressed && bossing_mode && boss_state.sequence_size == BOSS_SEQ_MAX ) {
    boss_state_clear_sequence();
    boss_state.oneshot = false;
    /* return false; */
  }

  /* Update boss_state with pressed key info. */
  if (record->event.pressed && bossing_mode ) {
    uint16_t ref_kc = keymap_key_to_keycode(boss_ref_layer, record->event.key);
    uint8_t i = boss_state.sequence_size++;
    boss_state.keycode_seq[i] = ref_kc;
    boss_state.key_seq[i] = record->event.key;
    return false;
  }
  return true;
}

void boss_state_clear_sequence(void) {
  for (uint8_t i = 0; i < BOSS_SEQ_MAX; ++i) {
    boss_state.keycode_seq[i] = KC_NO;
    boss_state.key_seq[i] = (keypos_t) {
      .row = MATRIX_ROWS + 1,
      .col = MATRIX_COLS + 1};
  }
  boss_state.sequence_size = 0;
}

void boss_state_init(uint16_t keycode, keypos_t key) {
  boss_state_clear_sequence();
  boss_state.keycode = keycode;
  boss_state.key = key;
  // TODO: wrap oneshot in #ifdef BOSS_ONESHOT ???
  // it it can be manage in user space
  boss_state.oneshot = true;
  boss_state.momentary = true;
  boss_state.time = timer_read();
}

void boss_state_init_pressed(void) {
  for (uint8_t i = 0; i < BOSS_PRESSED_MAX; i++) {
    boss_state.key_pressed_seq[i] = boss_no_key;
  }
}
/* bool boss_seq_cmp(uint8_t num, ...) { */
/*   if (num > BOSS_SEQ_MAX) {return false;} */
/*   va_list ap; */
/*   bool match = true; */
/*   va_start(ap, num); */
/*   uint16_t kc, seq_kc; */
/*   for (uint8_t i = 0; i < num; i++) { */
/*     seq_kc = boss_state.keycode_seq[i]; */
/*     if (seq_kc == KC_NO) {return false;} */
/*     kc = va_arg(ap, uint16_t); */
/*     match = match && (kc == seq_kc || kc == KC_TRNS); */
/*   } */
/*   va_end(ap); */
/*   return match; */
/* } */

bool boss_seq_match(uint8_t num, ...) {
  if (num != boss_state.sequence_size) {
    return false;
  }
  bool result = true;
  va_list ap;
  uint16_t kc, seq_kc;
  va_start(ap, num);
  for (uint8_t i = 0; i < num; i++) {
    seq_kc = boss_state.keycode_seq[i];
    kc = va_arg(ap, uint16_t);
    if (kc != seq_kc && kc != KC_TRNS) {
      result = false;
      break;
    };
  }
  va_end(ap);
  return result;
}



/* uint16_t boss_last_seq_keycode(uint8_t layer) { */
/*   uint16_t keycode = keymap_key_to_keycode(layer, boss_state.key_seq[boss_state.sequence_size - 1]); */
/*   if (keycode == KC_NO || keycode == KC_TRNS) { */
/*     return KC_NO; */
/*   }  */
/*   /\* boss_register_code(keycode); *\/ */
/*   /\* boss_unregister_code(keycode); *\/ */
/*   return keycode; */
/* } */

void boss_register_code(uint16_t keycode) {
  if ((keycode >= boss_range.mo_first
       && keycode <= boss_range.mo_last)
      || (keycode >= boss_range.os_first
          && keycode <= boss_range.os_last)) {
     boss_state_init(keycode, boss_state.key_seq[boss_state.sequence_size - 1]);
     return;
  }
  register_code16(keycode);
  return;
}
void boss_unregister_code(uint16_t keycode) {
  if ((keycode >= boss_range.mo_first
       && keycode <= boss_range.mo_last)
      || (keycode >= boss_range.os_first
          && keycode <= boss_range.os_last)) {
     return;
  }
  unregister_code16(keycode);
  return;
}

#endif
