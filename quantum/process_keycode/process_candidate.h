#ifndef PROCESS_CANDIDATE_H
#define PROCESS_CANDIDATE_H

#include "quantum.h"

/* maximum number of simulteneously pressed keys */
#define CANDIDATE_PRESSED_MAX 6

typedef struct {
    uint8_t layer;
    uint8_t row;
    uint8_t col;
} candidate_pressed_t;

void set_candidate(uint8_t layer);
void process_candidate( keyrecord_t *record);


#endif
