#include "process_candidate.h"

uint32_t cand_request_state = 0;
cand_pressed_key_t pressed[CAND_PRESSED_KEY_MAX];
keypos_t requestor = (keypos_t) {.row = 0xFF, .col = 0xFF };
    

void set_candidate(uint8_t layer, keypos_t key)
{
    cand_request_state |= 1UL << layer;
    requestor = key;
}

uint8_t get_cand_layer(keypos_t key) {
    for (int8_t i = 31; i >= 0; i--) {
        if (cand_request_state & (1UL<<i)) {
            uint16_t keycode = keymap_key_to_keycode(i, key);
            if (keycode != KC_TRNS) { return i;}
        }
    }
    return 0;
}

uint16_t process_candidate(keyrecord_t *record)
{
    dprintf("process_candidate start\n");
    if (cand_request_state == 0) {
        return 0;
    }

    dprintf("requests not empty\n");
    keypos_t key = record->event.key;
    bool key_pressed = record->event.pressed;
    uint8_t cand_layer = get_cand_layer(key);

    uint16_t keycode = 0;
    uint32_t pressed_layers = 0;
    for (int8_t i = 0; i < CAND_PRESSED_KEY_MAX; i++) {
        bool zerolayer = (pressed[i]).layer == 0;
        if (key_pressed && zerolayer && keycode == 0) {
            pressed[i].layer = cand_layer;
            pressed[i].key = key;
            pressed_layers |= 1UL << pressed[i].layer;
            keycode = keymap_key_to_keycode(cand_layer, key);
            continue;
        }
        bool samekey = key.row == pressed[i].key.row
            && key.col == pressed[i].key.col;
        bool samelayer = pressed[i].layer == cand_layer;
        if (!key_pressed && samelayer && samekey) {
            keycode = keymap_key_to_keycode(cand_layer, key);
            pressed[i].layer = 0;
            continue;
        }
        if (!zerolayer) {
            pressed_layers |= 1UL << pressed[i].layer;
        }
    }
    if (key.row == requestor.row && key.col == requestor.col) {
        requestor = (keypos_t) {.row = 0xFF, .col = 0xFF };
    } else {
        cand_request_state = pressed_layers;
    }
    dprintf("keycode returned %d\n", keycode);
    return keycode;
}
