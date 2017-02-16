#include "process_candidate.h"

uint32_t cand_request_state = 0;
cand_pressed_key_t pressed[CAND_PRESSED_KEY_MAX];
keypos_t requestor = (keypos_t) {.row = 0xFF, .col = 0xFF };
uint8_t dirty = 0;
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

void process_candidate(keyrecord_t *record)
{
    dprintf("process_candidate start\n");
    dprintf("LAYER state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    if (dirty) {
        dprintf("DIRTY\n");
        layer_off(dirty);
        dirty = 0;
    }
  
    if (!cand_request_state) {
            dprintf("no requests\n");
            return;
        }
    keypos_t key = record->event.key;
    bool key_pressed = record->event.pressed;
    uint8_t cand_layer = get_cand_layer(key);
    dprintf("layer Pressed %d\n", cand_layer);

    // switch off all requested layer first
    layer_and(~cand_request_state);
    dprintf("clear LAYER state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    dprintf("cand request state before: %08lX(%u)\n", cand_request_state, biton32(cand_request_state));
    if (!(requestor.col == key.col && requestor.row == key.row)) {
        cand_request_state = 0;
    }
    int8_t count = 0;
    bool stored = false;
    for (int8_t i = 0; i < CAND_PRESSED_KEY_MAX; i++) {
        bool zerolayer = (pressed[i]).layer == 0;
        /* if (zerolayer && stored) { */
        /*     continue; */
        /* } */
        if (key_pressed && cand_layer != 0 && zerolayer && !stored) {
            pressed[i].layer = cand_layer;
            pressed[i].key = key;
            cand_request_state |= 1UL << cand_layer;
            stored = true;
            count++;
            layer_on(cand_layer);
            //layer_on(cand_layer);
            //*keycode = keymap_key_to_keycode(cand_layer, key);
            dprintf("layer pressed layer %d\n", cand_layer);
            continue;
        }
        
        bool samekey = key.row == pressed[i].key.row
            && key.col == pressed[i].key.col;
        bool samelayer = pressed[i].layer == cand_layer;
        if (!key_pressed && !zerolayer && samelayer && samekey && cand_layer !=0 )  {
            pressed[i].layer = 0;
            count--;
            layer_on(cand_layer);
            dprintf("layer releasedpressed layer %d\n", cand_layer);
            continue;
        }
        
        if (!zerolayer) {
            if (samelayer) {
                count++;
            } else {
                cand_request_state |= 1UL << pressed[i].layer;
            }
        }
    }
    if (cand_layer !=0 ) {
        if (count >= 0) {
            cand_request_state |= 1UL << cand_layer;
            dprintf("set cand layerlayer %d\n", cand_layer);
        }
        else {
            dprintf("remove  cand layer next step %d\n", cand_layer);
            dirty = cand_layer;}
    }
    dprintf("layer after state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    dprintf("cand request state after: %08lX(%u)\n", cand_request_state, biton32(cand_request_state));
    return;
}
