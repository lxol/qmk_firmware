#include "process_sublayer.h"

uint32_t sublayer_state = 0;
sublayer_pressed_key_t sublayer_keys[SUBLAYER_PRESSED_KEY_MAX];
keypos_t request_key = (keypos_t) {.row = 0xFF, .col = 0xFF };
uint8_t release_codes = 0;
uint8_t dirty_sublayer = 0;
bool sublayer_pressed = false;
void set_sublayer(uint8_t layer, keypos_t key)
{
    sublayer_state |= 1UL << layer;
    request_key = key;
}
void set_sublayer_release_code(uint8_t code) {
    release_codes = code;
}

uint8_t get_sublayer(keypos_t key) {
    for (int8_t i = 31; i >= 0; i--) {
        if (sublayer_state & (1UL<<i)) {
            uint16_t keycode = keymap_key_to_keycode(i, key);
            if (keycode != KC_TRNS) { return i;}
        }
    }
    return 0;
}

void process_sublayer(keyrecord_t *record)
{
    dprintf("LAYER state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    if (dirty_sublayer) {
        layer_off(dirty_sublayer);
        dirty_sublayer = 0;
        unregister_code(release_codes);
    }

    if (!sublayer_state) {
        return;
    }
    keypos_t key = record->event.key;
    bool key_pressed = record->event.pressed;
    uint8_t sublayer = get_sublayer(key);
    
    // switch off all requested layers
    layer_and(~sublayer_state);
    //if (!sublayer) { return;}
    // key that sets sublayer_state shouldn't clear it
    if (sublayer_pressed) {
        request_key = (keypos_t) {.row = 0xFF, .col = 0xFF };
    }
    if (request_key.col == key.col && request_key.row == key.row)  {
        if (!key_pressed) {
            // and after release it can be used as a normal sublayer key
            request_key = (keypos_t) {.row = 0xFF, .col = 0xFF };
        }
    } else {
        sublayer_state = 0;
    }

    int8_t count = 0;
    bool stored = false;
    for (int8_t i = 0; i < SUBLAYER_PRESSED_KEY_MAX; i++) {
        bool zerolayer = (sublayer_keys[i]).layer == 0;
        if (key_pressed && zerolayer && !stored) {
            sublayer_pressed = true;
            sublayer_keys[i].layer = sublayer;
            sublayer_keys[i].key = key;
            sublayer_state |= 1UL << sublayer;
            stored = true;
            count++;
            layer_on(sublayer);
            continue;
        }
        if (zerolayer) {continue;}
        bool samekey = key.row == sublayer_keys[i].key.row
            && key.col == sublayer_keys[i].key.col;
        bool samelayer = sublayer_keys[i].layer == sublayer;
        if (!key_pressed && samelayer && samekey)  {
            sublayer_keys[i].layer = 0;
            count--;
            layer_on(sublayer);
            continue;
        }
        if (samelayer) {
          count++;
        } else {
          sublayer_state |= 1UL << sublayer_keys[i].layer;
        }

    }
    if (count >= 0) {
      sublayer_state |= 1UL << sublayer;
    }
    else {
      dirty_sublayer = sublayer;
    }

    return;
}

void sublayer_store_press(int8_t sublayer, keypos_t key) {
  for (int8_t i = 0; i < SUBLAYER_PRESSED_KEY_MAX; i++) {
        if ((sublayer_keys[i]).layer == 0) {
            sublayer_keys[i].layer = sublayer;
            sublayer_keys[i].key = key;
            break;
        }
  }
}

