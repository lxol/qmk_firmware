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
void leaders_start(void) {}

__attribute__ ((weak))
void leaders_end(void) {}

leader_t leaders[LEADERS_MAX];

__attribute__ ((weak))
bool leaders_sequence_user(void) {return true;}

uint8_t leaders_sequence_size = 0;
leaders_state_t leaders_state;
uint8_t foo_layer;

uint8_t leaders_ref_layer = LEADERS_REFERENCE_LAYER;

/* leaders_range_t leaders_range = (leaders_range_t) {.momentary_first = KC_NO, */
/*                                           .momentary_last = KC_NO, */
/*                                           .oneshot_first = KC_NO, */
/*                                           .oneshot_last = KC_NO}; */

keypos_t leaders_no_key = (keypos_t) {
  .row = MATRIX_ROWS,
  .col = MATRIX_COLS
};

bool on_release(pressed_key_t pressed_key) {
  return true;
}
uint8_t foo = 0;
void leaders_init(void) {
  foo = 15;
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    leaders_pressed_keys[i] = (pressed_key_t) {
      .released = true,
    };
    xprintf("        init released:  %d\r\n", i );
  }
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX ; i++) {
    active_leaders[i] = (active_leader_t) {
      .momentary = false,
      .oneshot = false,
      .time = 0
    };
  }
  leaders_sequence_size = 0;
  return;
}

void store_pressed_key(pressed_key_t pressed_key) {
  pressed_key.released = false;
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    if (leaders_pressed_keys[i].released) {
      leaders_pressed_keys[i] = pressed_key;
      xprintf("   stored %d i: %d row: %d col: %d\r\n", pressed_key.keycode, i, pressed_key.key.row, pressed_key.key.col );
      return;
    }
  }
  xprintf("   ERROR: overflow, can not store pressed \r\n" );
  return;
}

uint8_t pressed_key_index(keypos_t key) {
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    if (!leaders_pressed_keys[i].released
        && KEYEQ(leaders_pressed_keys[i].key, key)) {
      leaders_pressed_keys[i].released = true;
      xprintf("   removed pressed i: %d, row: %d  col: %d\r\n", i, key.row, key.col );
      return i;
    }
  }
  return LEADERS_PRESSED_MAX;
}

bool store_active(active_leader_t active_leader) {
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX; i++) {
    if (active_leaders[i].momentary || active_leaders[i].oneshot) {
      continue;
    }
    active_leaders[i] = active_leader;
    xprintf("    stored active: %d, row: %d  col: %d\r\n", i, active_leader.key.row, active_leader.key.col );
    return true;
  }
  xprintf("   ERROR: overflow, can not store active leader \r\n" );
  return false;
}

bool momentary_off(keypos_t key) {
  xprintf("   momentary off : %d col: %d\r\n", key.row, key.col  );
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX; i++) {
    xprintf("          i: %d : %d col: %d\r\n", active_leaders[i].key.row, active_leaders[i].key.col  );
    if (active_leaders[i].momentary &&
        KEYEQ(active_leaders[i].key, key)) {
      active_leaders[i].momentary = false;
      xprintf("   switched off momentary for : %d col: %d\r\n", key.row, key.col  );
      return true;
    }
  }
  return false;
}

bool oneshot_off(keypos_t key) {
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX; i++) {
    if (active_leaders[i].oneshot &&
        KEYEQ(active_leaders[i].key, key)) {
      active_leaders[i].oneshot = false;
      return true;
    }
  }
  return false;
}

uint8_t recent_active_leader_index(void) {
  uint8_t index = ACTIVE_LEADERS_MAX;
  uint32_t cur_time = timer_read32();
  uint32_t diff_min = UINT32_MAX;
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX; i++) {
    if (!active_leaders[i].momentary && !active_leaders[i].oneshot) {
      continue;
    }
    uint32_t diff = TIMER_DIFF_32(cur_time, active_leaders[i].time);
    if (diff < diff_min) {
      index = i;
    }
  }
  return index;
}

uint8_t leader_index(uint16_t keycode) {
  for (uint8_t i = 0; i < LEADERS_MAX; i++) {
    if (leaders[i].keycode  == keycode ) {
      return i;
    }
  }
  return LEADERS_MAX;
}

void sequence_push(void) {

}
void sequence_clear(void) {
}

bool process_leaders_pressed(uint16_t keycode, keyrecord_t *record) {
    xprintf(" \r\n" );
    xprintf(" \r\n" );
    xprintf("    PROCESS: keycode: %d, row: %d  col: %d\r\n", keycode, record->event.key.row, record->event.key.col );
  /* Check if leader key pressed. */
  uint8_t lix = leader_index(keycode);
  if (lix != LEADERS_MAX) {
    store_active(
                 (active_leader_t) {
                   .leader = leaders[lix],
                     .momentary = true,
                     .key = record->event.key,
                     
                     /* .oneshot = leaders[lix].oneshot, */
                     .oneshot = false,
                     .time = timer_read32()
                     });
  }
  uint8_t aix = recent_active_leader_index();
  if (aix != ACTIVE_LEADERS_MAX) {
    store_pressed_key(
                      (pressed_key_t) {
                        .released = false,
                          .key = record->event.key,
                          .keycode = keycode,
                          .is_leader = lix == LEADERS_MAX? false:true,
                          .leader = active_leaders[aix].leader
                          }
                      );
  }
  return true;
}

bool process_leaders_released(keypos_t key) {
  uint8_t pki = pressed_key_index(key);
  if (pki == LEADERS_PRESSED_MAX) {
    /* pressed not in leading mode */
    return true;
  }
  pressed_key_t pressed_key =  leaders_pressed_keys[pki];
  if (pressed_key.is_leader) {
    xprintf("   active " );
    momentary_off(pressed_key.key);
  }
  xprintf("   key released row: %d col: %d\r\n", pressed_key.key.row, pressed_key.key.col  );
  leaders_pressed_keys[pki].released = true;
  return false;
}

/* void release_leader(keypos_t key) { */

/* } */


bool process_leaders(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    return process_leaders_pressed(keycode, record);
  }
  else {
    return process_leaders_released(record->event.key);
  }
}






















bool _process_leaders_pressed(uint16_t keycode, keyrecord_t *record) {

  /* Act on leader key press. */
  uint8_t i = 0;
  do {
    if (keycode != leaders[i].keycode) { continue; }
    /* Leader key pressed! */
    /* Create an active_leader and put it to active_leaders */
    bool leader_activated = false;
    for (uint8_t j = 0; j < ACTIVE_LEADERS_MAX; j++) {
      if (active_leaders[j].momentary || active_leaders[j].oneshot) { continue; }
      /*  */
      active_leaders[j] = (active_leader_t) {
        .leader = leaders[i],
        .momentary = true,
        .oneshot = leaders[i].oneshot,
        .time = timer_read32()
      };
      xprintf("   put leader to active_leaders: %d %s\r\n", keycode, i );
      leader_activated = true;
      break;
    }
    if (leader_activated) {
      break;
    } else {
      xprintf("   active_leaders overflow !!!!\r\n");
      /* TODO: control overflow here */
    }
  } while (leaders[i++].keycode != KC_NO || i == LEADERS_MAX);

  /* Check if in leading mode. */
  /* The most recent active leader wins. */
  bool leading_mode = false;
  uint8_t active_leader_index;
  uint32_t cur_time = timer_read32();
  uint32_t diff_min = UINT32_MAX;
  for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX; i++) {
    if (active_leaders[i].momentary || active_leaders[i].oneshot) {
      uint32_t diff = TIMER_DIFF_32(cur_time, active_leaders[i].time);
      if (diff < diff_min) {
        leading_mode = true;
        active_leader_index = 0;
      };
    }
  }

  /* Nothing to do here. We are not in leading mode. */
  if (!leading_mode) {
    return true;
  }

  active_leader_t active_leader = active_leaders[active_leader_index];
  /* active_leaders[0] = active_leader; */

  /* time to record sequence and pressed keys */

  /* This is a guard for unmanaged sequences.*/
  /* Start from scratch, when sequence reaches the maximum size.  */
  if (leaders_sequence_size == LEADERS_SEQ_MAX ) {
    leaders_sequence_size = 0;
    active_leader.oneshot = false;
  }

  uint8_t ref_layer = active_leader.leader.reference_layer;
  uint16_t ref_kc = keymap_key_to_keycode(ref_layer, record->event.key);
  leaders_sequence[leaders_sequence_size++] = (sequence_key_t) {
    .keycode = ref_kc,
    .leader = active_leader.leader

  };


  return false;
    /* leaders_state.keycode_sequence[i] = ref_kc; */
    /* leaders_state.key_sequence[i] = record->event.key; */
    /* return leaders_state.layer; */

  /* return leaders_sequence_user(); */
}

bool _process_leaders_released(uint16_t keycode, keyrecord_t *record) {
  for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) {
    pressed_key_t pressed_key = leaders_pressed_keys[i];
    if (!pressed_key.released && KEYEQ(pressed_key.key, record->event.key)) {
      if (pressed_key.is_leader) {

        for (uint8_t i = 0; i < ACTIVE_LEADERS_MAX ; i++) {
          if (active_leaders[i].leader.keycode == pressed_key.keycode) {
            active_leaders[i].momentary = false;
            // TODO: remove!!! should be managed in user space
            active_leaders[i].oneshot = false;
            xprintf("   remove leader from active_leaders: %d %d\r\n", keycode, i );
            break;
          }
        }
        /* remove from leaders */
      } else {
            xprintf("   non released:%d\r\n", pressed_key.keycode);
      }
      return false;
    }
  }
  /* Key was not under leading mode management. Let it go. */
  return true;
}


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

/* bool process_leaders(uint16_t keycode, keyrecord_t *record) { */

/*   // ignore modifiers */
/*   // TODO: make it configurable */
/*   /\* leaders_state_print(); *\/ */
/*   if (keycode == KC_LCTL || */
/*       keycode == KC_RCTL || */
/*       keycode == KC_LGUI || */
/*       keycode == KC_RGUI || */
/*       keycode == KC_LSFT || */
/*       keycode == KC_RSFT || */
/*       keycode == KC_LALT || */
/*       keycode == KC_RALT ) { */
/*     return true; */
/*   } */


/*   /\* Manage layer leader key press. *\/ */
/*   if (record->event.pressed) { */
/*     bool is_layer_leader_pressed = keycode >= leaders_range.layer_first && keycode <= leaders_range.layer_last; */
/*     if (is_layer_leader_pressed) { */
/*       uint8_t layer_num = keycode - leaders_range.layer_first; */
/*       /\* xprintf(" arrow layer pressed : %d\r\n", foo_layer); *\/ */
/*       xprintf(" layer_num : %d\r\n", layer_num); */
/*       leaders_state.leader_keycode = keycode; */
/*       leaders_state.leader_key = record->event.key; */
/*       leaders_state.layer = true; */
/*       leaders_state.momentary = true; */
/*       leaders_state.oneshot = true; */
/*       leaders_state.layer_num = layer_num; */
/*       layer_on(layer_num); */
/*       xprintf("PRESSED LAYER LEADER %d\r\n", layer_num); */
/*       return false; */
/*     } */
/*   } */
/*   /\* Manage layer leader key release. *\/ */
/*   if (!record->event.pressed) { */
/*     bool is_layer_leader_released = leaders_state.layer && KEYEQ(leaders_state.leader_key, record->event.key); */
/*     if (is_layer_leader_released) { */
/*       /\* xprintf(" arrow layer : %d\r\n", foo_layer); *\/ */
/*       leaders_state.layer = false; */
/*       leaders_state.momentary = false; */
/*       uint8_t layer_num = leaders_state.layer_num; */
/*       xprintf(" release layer_num : %d\r\n", layer_num); */
/*       layer_off(layer_num); */
/*       return false; */
/*     } */
/*   } */

/*   /\* Manage leaders key press *\/ */
/*   if (record->event.pressed) { */
/*     bool is_mo_leader_pressed = keycode >= leaders_range.momentary_first && keycode <= leaders_range.momentary_last; */
/*     bool is_os_leader_pressed = keycode >= leaders_range.oneshot_first && keycode <= leaders_range.oneshot_last; */
/*     if (is_mo_leader_pressed || is_os_leader_pressed) { */
/*       leaders_state_init(keycode, record->event.key); */
/*       leaders_state.oneshot = is_os_leader_pressed; */
/*       leaders_state.momentary = true; */
/*       leaders_state.layer = false; */

/* #ifdef BACKLIGHT_ENABLE */
/*       backlight_set(2); */
/* #endif */
/*       return false; */
/*     } */
/*   } */

/*   /\* Manage leaders key release *\/ */
/*   if (!record->event.pressed) { */
/*     bool is_leader_released = leaders_state.momentary && KEYEQ(leaders_state.leader_key, record->event.key); */
/*     if (is_leader_released) { */
/*       leaders_state.momentary = false; */
/* #ifdef BACKLIGHT_ENABLE */
/*       backlight_set(0); */
/* #endif */
/*       return false; */
/*     } */
/*   } */

/*   bool leading_mode = leaders_state.momentary || leaders_state.oneshot || leaders_state.layer; */
/*   /\* Keep track all keys pressed under leading mode *\/ */
/*   if (leading_mode && record->event.pressed) { */
/*     for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) { */
/*       if (KEYEQ(leaders_state.pressed_keys[i], leaders_no_key)) { */
/*         leaders_state.pressed_keys[i] = record->event.key; */
/*         xprintf("ADD pressed: row: pos: %d, %d, col %d\r\n", i, record->event.key.row, record->event.key.col); */
/*         break; */
/*       } */
/*     } */
/*   } */

/*   /\* Keys pressed in leading_mode should not progress. *\/ */
/*   if (!record->event.pressed) { */
/*     for (uint8_t i = 0; i < LEADERS_PRESSED_MAX; i++) { */
/*       if (KEYEQ(leaders_state.pressed_keys[i], record->event.key)) { */
/*         leaders_state.pressed_keys[i] = leaders_no_key; */
/*         xprintf("RELEASE  pos: %d, row: %d, col %d \r\n", i, record->event.key.row, record->event.key.col); */
/*         return leaders_state.layer; */
/*       } */
/*     } */
/*     xprintf("   RELEASE UNMANAGED  row: %d, col %d \r\n",  record->event.key.row, record->event.key.col); */
/*     return true; */
/*   } */

/*   /\* This is a guard for unmanaged sequences.*\/ */
/*   /\* Start from scratch, when sequence reaches the maximum size.  *\/ */
/*   if (record->event.pressed && leading_mode && leaders_state.sequence_size == LEADERS_SEQ_MAX ) { */
/*     leaders_state_clear_sequence(); */
/*     leaders_state.oneshot = false; */
/*   } */

/*   /\* Update leaders_state with pressed key info. *\/ */
/*   if (record->event.pressed && leading_mode ) { */
/*     uint16_t ref_kc = keymap_key_to_keycode(leaders_ref_layer, record->event.key); */
/*     uint8_t i = leaders_state.sequence_size++; */
/*     leaders_state.keycode_sequence[i] = ref_kc; */
/*     leaders_state.key_sequence[i] = record->event.key; */
/*     return leaders_state.layer; */
/*   } */
/*   return true; */
/* } */

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

/* void leaders_register_code(uint16_t keycode) { */
/*   bool is_momentary = (keycode >= leaders_range.momentary_first */
/*                        && keycode <= leaders_range.momentary_last); */
/*   bool is_oneshot = (keycode >= leaders_range.oneshot_first */
/*                      && keycode <= leaders_range.oneshot_last); */
/*   if (is_momentary || is_oneshot) { */
/*      /\* leaders_state_init(keycode, leaders_state.key_sequence[leaders_state.sequence_size - 1]); *\/ */
/*      keypos_t new_leader_key = leaders_state.key_sequence[leaders_state.sequence_size - 1]; */
/*      leaders_state_clear_sequence(); */
/*      leaders_state.leader_keycode = keycode; */
/*      leaders_state.leader_key = new_leader_key; */
/*      leaders_state.oneshot = is_oneshot; */
/*      leaders_state.momentary = true; */
/*      leaders_state.time = timer_read(); */
/*      return; */
/*   } */
/*   register_code16(keycode); */
/*   return; */
/* } */
/* void leaders_unregister_code(uint16_t keycode) { */
/*   bool is_momentary = (keycode >= leaders_range.momentary_first */
/*                        && keycode <= leaders_range.momentary_last); */
/*   bool is_oneshot = (keycode >= leaders_range.oneshot_first */
/*                      && keycode <= leaders_range.oneshot_last); */
/*   if (is_momentary || is_oneshot) { */
/*     return; */
/*   } */
/*   unregister_code16(keycode); */
/*   return; */
/* } */

#endif
