#ifndef PROCESS_CANDIDATE_H
#define PROCESS_CANDIDATE_H

#include "quantum.h"

/* maximum number of simulteneously pressed keys */
#define CAND_PRESSED_KEY_MAX 6

typedef struct {
    uint8_t layer;
    keypos_t key;
} cand_pressed_key_t;

void set_candidate(uint8_t layer);
uint16_t process_candidate( keyrecord_t *record);


#endif
