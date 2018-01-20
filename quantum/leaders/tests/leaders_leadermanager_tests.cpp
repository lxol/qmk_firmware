/* Copyright 2017 Alex Olkhovskiy
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
#include "gtest/gtest.h"
#include <cstdarg>
#include "quantum_keycodes.h"
extern "C" {
#include "leaders/leadermanager.h"
}

enum foobar {
  LD_FIRST = SAFE_RANGE,
  LD_LEADER1,
  LD_LEADER2,
  LD_LEADER3,
  LD_LEADER4,
  LD_LAST,
  SEQ_IE,
  SEQ_OT,
  SEQ_IIE,
  SEQ_IEE,
  SEQ_LAYER_1
};

const uint16_t* my_keyseq_definitions[]  = {
  (uint16_t[]){0x0000, LD_LEADER1, KC_E, SEQ_IE, KEYSEQ_END },
  (uint16_t[]){0x0000, LD_LEADER2, KC_E, KC_A,  SEQ_IEE, KEYSEQ_END},
  (uint16_t[]){0x0000, LD_LEADER3, KC_TRNS, SEQ_IE, KEYSEQ_END },
  (uint16_t[]){0x0000, LD_LEADER4, KC_A, KC_TRNS, KC_B, SEQ_IE, KEYSEQ_END },
  (uint16_t[]){0xffff}
};


class Leadermanager : public testing::Test {

public:
  Leadermanager() {
    keyseq_init(my_keyseq_definitions);
  }
  virtual ~Leadermanager() {
  }

};

TEST_F(Leadermanager, no_match_test_1 ) {
  // no match
  keyseq_push(KC_A);
  keyseq_push(KC_B);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 0);
  ASSERT_EQ(pos.row, 4);
  ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MISS);
}

TEST_F(Leadermanager, no_match_test_2 ) {
  // (uint16_t[]){0x0000, LD_LEADER1,  KC_E, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER1);
  keyseq_push(KC_F);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 1);
  ASSERT_EQ(pos.row, 0);
  // ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MISS);
}

TEST_F(Leadermanager, partial_match_test ) {
  // (uint16_t[]){0x0000, LD_LEADER1,  KC_E, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER1);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 1);
  ASSERT_EQ(pos.row, 0);
  // ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_PARTIAL);
}

TEST_F(Leadermanager, partial_match_test2 ) {
  // (uint16_t[]){0x0000, LD_LEADER2, KC_E, KC_A,  SEQ_IEE, KEYSEQ_END},
  keyseq_push(LD_LEADER2);
  keyseq_push(KC_E);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 2);
  ASSERT_EQ(pos.row, 1);
  // ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_PARTIAL);
}

TEST_F(Leadermanager, match_test1 ) {
  // (uint16_t[]){0x0000, LD_LEADER2, KC_E, KC_A,  SEQ_IEE, KEYSEQ_END},
  keyseq_push(LD_LEADER2);
  keyseq_push(KC_E);
  keyseq_push(KC_A);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 3);
  ASSERT_EQ(pos.row, 1);
  // ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MATCH);
}

TEST_F(Leadermanager, match_with_transitives_test1 ) {
  // (uint16_t[]){0x0000, LD_LEADER3, KC_TRNS, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER3);
  keyseq_push(KC_E);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 2);
  ASSERT_EQ(pos.row, 2);
  ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MATCH);
}

TEST_F(Leadermanager, match_with_transitives_test2 ) {
  // (uint16_t[]){0x0000, LD_LEADER4, KC_A, KC_TRNS, KC_B, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER4);
  keyseq_push(KC_A);
  keyseq_push(KC_F);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 3);
  ASSERT_EQ(pos.row, 3);
  ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_PARTIAL);
}

TEST_F(Leadermanager, transitives_test3 ) {
  // (uint16_t[]){0x0000, LD_LEADER4, KC_A, KC_TRNS, KC_B, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER4);
  keyseq_push(KC_A);
  keyseq_push(KC_F);
  keyseq_push(KC_B);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 4);
  ASSERT_EQ(pos.row, 3);
  ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MATCH);
}

TEST_F(Leadermanager, transitives_test4 ) {
  // (uint16_t[]){0x0000, LD_LEADER4, KC_A, KC_TRNS, KC_B, SEQ_IE, KEYSEQ_END },
  keyseq_push(LD_LEADER4);
  keyseq_push(KC_A);
  keyseq_push(KC_F);
  keyseq_push(KC_K);
  keyseq_pos_t pos = keyseq_match_position();
  ASSERT_EQ(pos.col, 3);
  ASSERT_EQ(pos.row, 3);
  // ASSERT_EQ(keyseq_match_state(pos), KEYSEQ_MISS);
}
