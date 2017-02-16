#ifndef PROCESS_SUBLAYER_H
#define PROCESS_SUBLAYER_H

#include "quantum.h"

/* maximum number of simulteneously pressed keys */
#define SUBLAYER_PRESSED_KEY_MAX 6

typedef struct {
    uint8_t layer;
    keypos_t key;
} sublayer_pressed_key_t;

void set_sublayer(uint8_t layer, keypos_t key);
void process_candidate(keyrecord_t *record);


#endif
