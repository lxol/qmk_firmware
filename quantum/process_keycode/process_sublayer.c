#include "process_sublayer.h"

uint32_t sublayer_state = 0;
sublayer_pressed_key_t pressed[SUBLAYER_PRESSED_KEY_MAX];
keypos_t request_key = (keypos_t) {.row = 0xFF, .col = 0xFF };
uint8_t dirty_sublayer = 0;
void set_sublayer(uint8_t layer, keypos_t key)
{
    sublayer_state |= 1UL << layer;
    request_key = key;
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
    dprintf("process_candidate start\n");
    dprintf("LAYER state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    if (dirty_sublayer) {
        dprintf("DIRTY_SUBLAYER\n");
        layer_off(dirty_sublayer);
        dirty_sublayer = 0;
    }
  
    if (!sublayer_state) {
            dprintf("no requests\n");
            return;
        }
    keypos_t key = record->event.key;
    bool key_pressed = record->event.pressed;
    uint8_t sublayer = get_sublayer(key);
    dprintf("layer Pressed %d\n", sublayer);

    // switch off all requested layer first
    layer_and(~sublayer_state);
    dprintf("clear LAYER state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    dprintf("cand request state before: %08lX(%u)\n", sublayer_state, biton32(sublayer_state));
    if (!(request_key.col == key.col && request_key.row == key.row)) {
        sublayer_state = 0;
    } else if (!key_pressed)  {
        request_key = (keypos_t) {.row = 0xFF, .col = 0xFF };
    }
        
    int8_t count = 0;
    bool stored = false;
    for (int8_t i = 0; i < SUBLAYER_PRESSED_KEY_MAX; i++) {
        bool zerolayer = (pressed[i]).layer == 0;
        /* if (zerolayer && stored) { */
        /*     continue; */
        /* } */
        if (key_pressed && sublayer != 0 && zerolayer && !stored) {
            pressed[i].layer = sublayer;
            pressed[i].key = key;
            sublayer_state |= 1UL << sublayer;
            stored = true;
            count++;
            layer_on(sublayer);
            //layer_on(sublayer);
            //*keycode = keymap_key_to_keycode(sublayer, key);
            dprintf("layer pressed layer %d\n", sublayer);
            continue;
        }
        
        bool samekey = key.row == pressed[i].key.row
            && key.col == pressed[i].key.col;
        bool samelayer = pressed[i].layer == sublayer;
        if (!key_pressed && !zerolayer && samelayer && samekey && sublayer !=0 )  {
            pressed[i].layer = 0;
            count--;
            layer_on(sublayer);
            dprintf("layer releasedpressed layer %d\n", sublayer);
            continue;
        }
        
        if (!zerolayer) {
            if (samelayer) {
                count++;
            } else {
                sublayer_state |= 1UL << pressed[i].layer;
            }
        }
    }
    if (sublayer !=0 ) {
        if (count >= 0) {
            sublayer_state |= 1UL << sublayer;
            dprintf("set cand layerlayer %d\n", sublayer);
        }
        else {
            dprintf("remove  cand layer next step %d\n", sublayer);
            dirty_sublayer = sublayer;}
    }
    dprintf("layer after state:        %08lX(%u)\n", layer_state, biton32(layer_state));
    dprintf("cand request state after: %08lX(%u)\n", sublayer_state, biton32(sublayer_state));
    return;
}
