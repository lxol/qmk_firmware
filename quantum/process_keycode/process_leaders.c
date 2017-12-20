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

leaders_state_t leaders_state;
uint8_t foo_layer;

uint8_t leaders_ref_layer = LEADERS_REFERENCE_LAYER;

leaders_range_t leaders_range = (leaders_range_t) {.momentary_first = KC_NO,
                                          .momentary_last = KC_NO,
                                          .oneshot_first = KC_NO,
                                          .oneshot_last = KC_NO};

keypos_t leaders_no_key = (keypos_t) {
  .row = MATRIX_ROWS,
  .col = MATRIX_COLS
};
/* void leaders_state_print(void) { */
/*   xprintf("LEADERS STATE:\r\n"); */
/*   xprintf("   leaders_state.leader_key row:%d, col: %d\r\n", leaders_state.leader_key.row, leaders_state.leader_key.col); */
/*   xprintf("   leaders_state.seq_key row:%d, col: %d\r\n", leaders_state.seq_key.row, leaders_state.seq_key.col); */
/*   xprintf("   leaders_state.oneshot :%d\r\n", leaders_state.oneshot); */
/*   xprintf("   leaders_state.leader_keycode :%d\r\n", leaders_state.leader_keycode); */
/*   xprintf("   leaders_state.sequence_size :%d\r\n", leaders_state.sequence_size); */
/*   for (uint8_t i = 0; i < LEADERS_SEQ_MAX; ++i) */
/*     xprintf("        leaders_state.keycode_sequence[%d] keycode: %d\r\n", i, leaders_state.keycode_sequence[i]); */
/* } */

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  //TODO: control presses and releases

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

  /* Ignore configured keycodes */
  bool is_in_ignore_range = keycode >= leaders_range.ignore_first && keycode <= leaders_range.ignore_last;
  if (is_in_ignore_range) {
    if (record->event.pressed) {
      xprintf("PRESSED IGNORED\r\n");
    } else {
      xprintf("RELEASED IGNORED\r\n");
    }
    return true;
  }

  /* Manage layer leader key press. */
  if (record->event.pressed) {
    bool is_layer_leader_pressed = keycode >= leaders_range.layer_first && keycode <= leaders_range.layer_last;
    if (is_layer_leader_pressed) {
      uint8_t layer_num = keycode - leaders_range.layer_first;
      xprintf("PRESSED LAYER LEADER\r\n");
      xprintf(" arrow layer pressed : %d\r\n", foo_layer);
      xprintf(" layer_num : %d\r\n", layer_num);
      leaders_state.leader_keycode = keycode;
      leaders_state.leader_key = record->event.key;
      leaders_state.layer = true;
      leaders_state.layer_num = layer_num;
      layer_on(layer_num);
      return false;
    }
  }
  /* Manage layer leader key release. */
  if (!record->event.pressed) {
    bool is_layer_leader_released = leaders_state.layer && KEYEQ(leaders_state.leader_key, record->event.key);
    if (is_layer_leader_released) {
      xprintf("RELEASED LAYER LEADER\r\n");
      xprintf(" arrow layer : %d\r\n", foo_layer);
      leaders_state.layer = false;
      uint8_t layer_num = leaders_state.layer_num;
      xprintf(" release layer_num : %d\r\n", layer_num);
      layer_off(layer_num);
      return false;
    }
  }

  /* No leaders processing in layer mode */
  if (leaders_state.layer) {
    xprintf("     KEY UNDER LAYER LEADER\r\n");
    return true;
  }

  /* /\* Manage layer leader key press. *\/ */
  /* if (record->event.pressed) { */
  /*   bool is_layer_leader_pressed = keycode >= leaders_range.layer_first && keycode <= leaders_range.layer_last; */
  /*   if (is_layer_leader_pressed) { */
  /*     leaders_state.layer = true; */
  /*     layer_on(8); */
  /*     return false; */
  /*   } */
  /* } */
  /* /\* Manage layer leader key release. *\/ */
  /* if (!record->event.pressed) { */
  /*   bool is_layer_leader_released = leaders_state.layer && KEYEQ(leaders_state.leader_key, record->event.key); */
  /*   if (is_layer_leader_released) { */
  /*     leaders_state.layer = false; */
  /*     layer_off(8); */
  /*     return false; */
  /*   } */
  /* } */

  /* Manage leaders key press */
  if (record->event.pressed) {
    bool is_mo_leader_pressed = keycode >= leaders_range.momentary_first && keycode <= leaders_range.momentary_last;
    bool is_os_leader_pressed = keycode >= leaders_range.oneshot_first && keycode <= leaders_range.oneshot_last;
    if (is_mo_leader_pressed || is_os_leader_pressed) {
      leaders_state_init(keycode, record->event.key);
      leaders_state.oneshot = is_os_leader_pressed;
      leaders_state.momentary = true;
      return false;
    }
  }

  /* Manage leaders key release */
  if (!record->event.pressed) {
    bool is_leader_released = leaders_state.momentary && KEYEQ(leaders_state.leader_key, record->event.key);
    if (is_leader_released) {
      leaders_state.momentary = false;
      return false;
    }
  }

  bool leading_mode = leaders_state.momentary || leaders_state.oneshot;
  /* Keep track all keys pressed under leading mode */
  if (leading_mode && record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.pressed_keys[i], leaders_no_key)) {
        leaders_state.pressed_keys[i] = record->event.key;
        xprintf("ADD pressed: row: pos: %d, %d, col %d\r\n", i, record->event.key.row, record->event.key.col);
        break;
      }
    }
  }

  /* Keys pressed in leading_mode should not progress. */
  if (!record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.pressed_keys[i], record->event.key)) {
        leaders_state.pressed_keys[i] = leaders_no_key;
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
    leaders_state.keycode_sequence[i] = ref_kc;
    leaders_state.key_sequence[i] = record->event.key;
    return false;
  }
  return true;
}

void leaders_state_clear_sequence(void) {
  for (uint8_t i = 0; i < LEADERS_SEQ_MAX; ++i) {
    leaders_state.keycode_sequence[i] = KC_NO;
    leaders_state.key_sequence[i] = (keypos_t) {
      .row = MATRIX_ROWS + 1,
      .col = MATRIX_COLS + 1};
  }
  leaders_state.sequence_size = 0;
}

void leaders_state_init(uint16_t keycode, keypos_t key) {
  leaders_state_clear_sequence();
  leaders_state.leader_keycode = keycode;
  leaders_state.leader_key = key;
  // TODO: wrap oneshot in #ifdef LEADERS_ONESHOT ???
  // it it can be manage in user space
  leaders_state.oneshot = true;
  leaders_state.momentary = true;
  leaders_state.time = timer_read();
}

void leaders_state_init_pressed(void) {
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    leaders_state.pressed_keys[i] = leaders_no_key;
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
    seq_kc = leaders_state.keycode_sequence[i];
    kc = va_arg(ap, uint16_t);
    if (kc != seq_kc && kc != KC_TRNS) {
      result = false;
      break;
    };
  }
  va_end(ap);
  return result;
}

void leaders_register_code(uint16_t keycode) {
  bool is_momentary = (keycode >= leaders_range.momentary_first
                       && keycode <= leaders_range.momentary_last);
  bool is_oneshot = (keycode >= leaders_range.oneshot_first
                     && keycode <= leaders_range.oneshot_last);
  if (is_momentary || is_oneshot) {
     /* leaders_state_init(keycode, leaders_state.key_sequence[leaders_state.sequence_size - 1]); */
     keypos_t new_leader_key = leaders_state.key_sequence[leaders_state.sequence_size - 1];
     leaders_state_clear_sequence();
     leaders_state.leader_keycode = keycode;
     leaders_state.leader_key = new_leader_key;
     leaders_state.oneshot = is_oneshot;
     leaders_state.momentary = true;
     leaders_state.time = timer_read();
     return;
  }
  register_code16(keycode);
  return;
}
void leaders_unregister_code(uint16_t keycode) {
  bool is_momentary = (keycode >= leaders_range.momentary_first
                       && keycode <= leaders_range.momentary_last);
  bool is_oneshot = (keycode >= leaders_range.oneshot_first
                     && keycode <= leaders_range.oneshot_last);
  if (is_momentary || is_oneshot) {
    return;
  }
  unregister_code16(keycode);
  return;
}

#endif
