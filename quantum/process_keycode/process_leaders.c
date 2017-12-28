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

__attribute__ ((weak))
void leaders_init_user(void) {}

__attribute__ ((weak))
bool process_sequence_press_user(void) {return false;}

__attribute__ ((weak))
bool process_sequence_release_user(void) {return false;}

__attribute__ ((weak))
bool process_leader_press_user(void) {return false;}

__attribute__ ((weak))
bool process_leader_release_user(void) {return false;}

leader_t leaders[LEADERS_MAX];
leaders_state_t leaders_state;

leaders_press_t leaders_presses[16];
uint16_t press_state;

uint8_t leaders_ref_layer = LEADERS_REFERENCE_LAYER;

keypos_t leaders_no_key = (keypos_t) {
  .row = MATRIX_ROWS,
  .col = MATRIX_COLS
};

void leaders_init(void) {
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    leaders_state.pressed_keys[i] = leaders_no_key;
  }
  leaders_state.layer = false;
  leaders_ref_layer = biton32(default_layer_state);
  leaders_init_user(); 
}

bool process_leader_press(void) {
  return process_leader_press_user();
}

bool process_leader_release(void) {
  return process_leader_release_user();
}

bool process_sequence_press(void) {
  return process_sequence_press_user();
}

bool process_sequence_release(void) {
  return process_sequence_release_user();
}

uint8_t leader_index(uint16_t keycode) {
  for (uint8_t i = 0; i < LEADERS_MAX; i++) {
    if (leaders[i].keycode  == keycode ) {
      return i;
    }
  }
  return LEADERS_MAX;
}

bool match_sequence(uint8_t num, ...) {
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

bool is_leading(uint16_t keycode) {
  return (leaders_state.sequence_size != 0)
    && (leaders_state.momentary || leaders_state.oneshot)
    && (leaders_state.leader_keycode == keycode );
}

void memorize_press(keypos_t key, uint16_t keycode) {
  for (int8_t i = 0; i < 16; i ++) {
    if (press_state & (1U << i)) {
      continue;
    }
    press_state |= (1U << i);
    leaders_presses[i].key = key;
    leaders_presses[i].leader = keycode;
    /* break; */
    return;
  }
  press_state = 0U;
}

uint8_t leaders_biton16(uint16_t bits)
{
    uint8_t n = 0;
    if (bits >> 8) { bits >>= 8; n += 8;}
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    if (bits)      { n += 1;}
    return n;
}

uint8_t find_press(keypos_t key) {
  uint8_t l = leaders_biton16(press_state);
  for (int8_t i = 0; i < l; i++) {
    if (press_state & (1U << i)) {
      if (KEYEQ(leaders_presses[i].key, key)) {
        return i;
      }
    }
  }
  return 16;
}

void unmemorize_press(keypos_t key) {
  uint8_t idx = find_press(key);
  if (idx == 16) {return;}
  press_state &= ~(1U << idx);
}

leaders_press_t recall_press(keypos_t key) {
  uint8_t idx = find_press(key);
  if (idx == 16) {
    return (leaders_press_t) {
      .key = leaders_no_key,
        .leader = KC_NO
    };
  }
  return leaders_presses[idx];
}

bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  // TODO: make it configurable
  /* if (keycode == KC_LCTL || */
  /*     keycode == KC_RCTL || */
  /*     keycode == KC_LGUI || */
  /*     keycode == KC_RGUI || */
  /*     keycode == KC_LSFT || */
  /*     keycode == KC_RSFT || */
  /*     keycode == KC_LALT || */
  /*     keycode == KC_RALT ) { */
  /*   return true; */
  /* } */

  /* Manage layer leader key press. */
  uint8_t lix = leader_index(keycode);
  /* if (record->event.pressed) { */
  /*   bool is_layer_leader_pressed = lix != LEADERS_MAX && leaders[lix].toggle_layer; */
  /*   if (is_layer_leader_pressed) { */
  /*     uint8_t layer_num = leaders[lix].toggle_layer_number; */
  /*     leaders_state.leader_keycode = keycode; */
  /*     leaders_state.leader_key = record->event.key; */
  /*     leaders_state.layer = true; */
  /*     leaders_state.momentary = true; */
  /*     leaders_state.oneshot = leaders[lix].oneshot; */
  /*     leaders_state.layer_num = layer_num; */
  /*     layer_on(layer_num); */
  /*     return process_sequence_press(); */
  /*   } */
  /* } */
  /* Manage layer leader key release. */
  /* if (!record->event.pressed) { */
  /*   bool is_layer_leader_released = leaders_state.layer && KEYEQ(leaders_state.leader_key, record->event.key); */
  /*   if (is_layer_leader_released) { */
  /*     leaders_state.layer = false; */
  /*     leaders_state.momentary = false; */
  /*     uint8_t layer_num = leaders_state.layer_num; */
  /*     layer_off(layer_num); */
  /*     return process_sequence_press(); */
  /*   } */
  /* } */

  /* Manage leaders key press */
  if (record->event.pressed) {
    bool is_mo_leader_pressed = lix != LEADERS_MAX;
    bool is_os_leader_pressed = lix != LEADERS_MAX && leaders[lix].oneshot;
    if (is_mo_leader_pressed || is_os_leader_pressed) {
      leaders_state.sequence_size = 0;
      leaders_state.leader_keycode = keycode;
      leaders_state.leader_key = record->event.key;
      leaders_state.momentary = true;
      leaders_state.oneshot = is_os_leader_pressed;
      leaders_state.layer = false;

#ifdef BACKLIGHT_ENABLE
      backlight_set(2);
#endif
      return process_leader_press();
    }
  }

  /* Manage leaders key release */
  if (!record->event.pressed) {
    bool is_leader_released = leaders_state.momentary && KEYEQ(leaders_state.leader_key, record->event.key);
    if (is_leader_released) {
      leaders_state.momentary = false;
#ifdef BACKLIGHT_ENABLE
      backlight_set(0);
#endif
      return process_leader_release();
    }
  }

  bool leading_mode = leaders_state.momentary || leaders_state.oneshot || leaders_state.layer;
  /* Keep track of all keys pressed under leading mode */
  if (leading_mode && record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.pressed_keys[i], leaders_no_key)) {
        leaders_state.pressed_keys[i] = record->event.key;
        break;
      }
    }
  }

  /* Keys pressed in leading_mode should not progress. */
  if (!record->event.pressed) {
    for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
      if (KEYEQ(leaders_state.pressed_keys[i], record->event.key)) {
        leaders_state.pressed_keys[i] = leaders_no_key;
        if (leaders_state.layer) {
          return true;
        }
        return process_sequence_release();
      }
    }
    return true;
  }

  /* This is a guard for unmanaged sequences.*/
  /* Start from scratch, when sequence reaches the maximum size.  */
  if (record->event.pressed && leading_mode && leaders_state.sequence_size == LEADERS_SEQ_MAX ) {
    leaders_state.sequence_size = 0;
    leaders_state.oneshot = false;
  }

  /* Update leaders_state with pressed key info. */
  if (record->event.pressed && leading_mode ) {
    uint16_t ref_kc = keymap_key_to_keycode(leaders_ref_layer, record->event.key);
    uint8_t i = leaders_state.sequence_size++;
    leaders_state.keycode_sequence[i] = ref_kc;
    leaders_state.key_sequence[i] = record->event.key;
    if (leaders_state.layer) {
      return true;
    }
    return process_sequence_press();
  }
  return true;
}


#endif
