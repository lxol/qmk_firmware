#include "process_candidate.h"

uint32_t candidate_requests = 0;
candidate_pressed_t pressed[CANDIDATE_PRESSED_MAX] = {0};

void set_candidate(uint8_t layer) {
    candidate_requests |= 1UL << layer;
}

void process_candidate(keyrecord_t *record) {
  return;
}
