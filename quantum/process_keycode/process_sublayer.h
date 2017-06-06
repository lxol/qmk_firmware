#ifndef PROCESS_SUBLAYER_H
#define PROCESS_SUBLAYER_H

#include "quantum.h"

/* maximum number of simulteneously pressed keys */
#define SUBLAYER_PRESSED_KEY_MAX 6

typedef struct {
    uint8_t layer;
    keypos_t key;
    bool exit_on_release;
} sublayer_pressed_key_t;

void set_sublayer(uint8_t layer, keypos_t key);
void set_sublayer_release_code(uint8_t code);
void process_sublayer(keyrecord_t *record);
void sublayer_store_press(int8_t sublayer, keypos_t key);

#endif
