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

#ifdef LEADERS_ENABLE

#include "process_leaders.h"

__attribute__ ((weak))
void leaders_start(void) {}

__attribute__ ((weak))
void leaders_end(void) {}

leaders_t leaders_state;

uint8_t leaders_ref_layer = LEADERS_REFERENCE_LAYER;

leaders_range_t leaders_range = (leaders_range_t) {.mo_first = KC_NO,
                                          .mo_last = KC_NO,
                                          .os_first = KC_NO,
                                          .os_last = KC_NO};

keypos_t leaders_no_key = (keypos_t) {
  .row = MATRIX_ROWS,
  .col = MATRIX_COLS
};
/* void leaders_state_print(void) { */
/*   xprintf("LEADERS STATE:\r\n"); */
/*   xprintf("   leaders_state.key row:%d, col: %d\r\n", leaders_state.key.row, leaders_state.key.col); */
/*   xprintf("   leaders_state.seq_key row:%d, col: %d\r\n", leaders_state.seq_key.row, leaders_state.seq_key.col); */
/*   xprintf("   leaders_state.oneshot :%d\r\n", leaders_state.oneshot); */
/*   xprintf("   leaders_state.keycode :%d\r\n", leaders_state.keycode); */
/*   xprintf("   leaders_state.sequence_size :%d\r\n", leaders_state.sequence_size); */
/*   for (uint8_t i = 0; i < LEADERS_SEQ_MAX; ++i) */
/*     xprintf("        leaders_state.keycode_seq[%d] keycode: %d\r\n", i, leaders_state.keycode_seq[i]); */
/* } */

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  //TODO: control presses and releases  -- too complicated

  //TODO: add a delay to a potential leaders key on the layer
  //      to deal with out of order but almost at the same time
  //      pressings

  // ignore modifiers
  // TODO: make it configurable
  /* leaders_state_print(); */
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

  /* Manage leaders key press */
  if (record->event.pressed) {
    bool is_mo_leaders_pressed = keycode >= leaders_range.mo_first && keycode <= leaders_range.mo_last;
    bool is_os_leaders_pressed = keycode >= leaders_range.os_first && keycode <= leaders_range.os_last;
    if (is_mo_leaders_pressed || is_os_leaders_pressed) {
      leaders_state_init(keycode, record->event.key);
      leaders_state.oneshot = is_os_leaders_pressed;
      leaders_state.momentary = true;
      return false;
    }
  }

  /* Manage leaders key release */
  if (!record->event.pressed) {
    bool is_leaders_released = leaders_state.momentary && KEYEQ(leaders_state.key, record->event.key);
    if (is_leaders_released) {
      leaders_state.momentary = false;
      return false;
    }
  }

  bool leading_mode = leaders_state.momentary || leaders_state.oneshot;
  /* Keep track all keys pressed under leading mode */
  if (leading_mode && record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.key_pressed_seq[i], leaders_no_key)) {
        leaders_state.key_pressed_seq[i] = record->event.key;
        xprintf("ADD pressed: row: pos: %d, %d, col %d\r\n", i, record->event.key.row, record->event.key.col);
        break;
      }
    }
  }
  
  /* Keys pressed in leading_mode should not progress. */
  if (!record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.key_pressed_seq[i], record->event.key)) {
        leaders_state.key_pressed_seq[i] = leaders_no_key;
        xprintf("RELEASE  pos: %d, row: %d, col %d \r\n", i, record->event.key.row, record->event.key.col);
        return false;
      }
    }
    return true;
  }

  /* This is a guard for unmanaged sequences.*/
  /* Start from scratch, when sequence reaches the maximum size.  */
  if (record->event.pressed && leading_mode && leaders_state.sequence_size == LEADERS_SEQ_MAX ) {
    leaders_state_clear_sequence();
    leaders_state.oneshot = false;
  }

  /* Update leaders_state with pressed key info. */
  if (record->event.pressed && leading_mode ) {
    uint16_t ref_kc = keymap_key_to_keycode(leaders_ref_layer, record->event.key);
    uint8_t i = leaders_state.sequence_size++;
    leaders_state.keycode_seq[i] = ref_kc;
    leaders_state.key_seq[i] = record->event.key;
    return false;
  }
  return true;
}

void leaders_state_clear_sequence(void) {
  for (uint8_t i = 0; i < LEADERS_SEQ_MAX; ++i) {
    leaders_state.keycode_seq[i] = KC_NO;
    leaders_state.key_seq[i] = (keypos_t) {
      .row = MATRIX_ROWS + 1,
      .col = MATRIX_COLS + 1};
  }
  leaders_state.sequence_size = 0;
}

void leaders_state_init(uint16_t keycode, keypos_t key) {
  leaders_state_clear_sequence();
  leaders_state.keycode = keycode;
  leaders_state.key = key;
  // TODO: wrap oneshot in #ifdef LEADERS_ONESHOT ???
  // it it can be manage in user space
  leaders_state.oneshot = true;
  leaders_state.momentary = true;
  leaders_state.time = timer_read();
}

void leaders_state_init_pressed(void) {
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    leaders_state.key_pressed_seq[i] = leaders_no_key;
  }
}

bool leaders_seq_match(uint8_t num, ...) {
  if (num != leaders_state.sequence_size) {
    return false;
  }
  bool result = true;
  va_list ap;
  uint16_t kc, seq_kc;
  va_start(ap, num);
  for (uint8_t i = 0; i < num; i++) {
    seq_kc = leaders_state.keycode_seq[i];
    kc = va_arg(ap, uint16_t);
    if (kc != seq_kc && kc != KC_TRNS) {
      result = false;
      break;
    };
  }
  va_end(ap);
  return result;
}

/* uint16_t leaders_last_seq_keycode(uint8_t layer) { */
/*   uint16_t keycode = keymap_key_to_keycode(layer, leaders_state.key_seq[leaders_state.sequence_size - 1]); */
/*   if (keycode == KC_NO || keycode == KC_TRNS) { */
/*     return KC_NO; */
/*   }  */
/*   /\* leaders_register_code(keycode); *\/ */
/*   /\* leaders_unregister_code(keycode); *\/ */
/*   return keycode; */
/* } */

void leaders_register_code(uint16_t keycode) {
  if ((keycode >= leaders_range.mo_first
       && keycode <= leaders_range.mo_last)
      || (keycode >= leaders_range.os_first
          && keycode <= leaders_range.os_last)) {
     leaders_state_init(keycode, leaders_state.key_seq[leaders_state.sequence_size - 1]);
     return;
  }
  register_code16(keycode);
  return;
}
void leaders_unregister_code(uint16_t keycode) {
  if ((keycode >= leaders_range.mo_first
       && keycode <= leaders_range.mo_last)
      || (keycode >= leaders_range.os_first
          && keycode <= leaders_range.os_last)) {
     return;
  }
  unregister_code16(keycode);
  return;
}

#endif
