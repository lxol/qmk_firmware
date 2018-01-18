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

// const uint16_t LEADER1 = 1;
// const uint16_t LEADER2 = 2;
// const uint16_t LEADER3 = 3;

enum foobar {
  LD_FIRST = SAFE_RANGE,
  LD_LEADER1,
  LD_LEADER2,
  LD_LEADER3,
  LD_LAST,
  SEQ_IE,
  SEQ_OT,
  SEQ_IIE,
  SEQ_IEE,
  SEQ_LAYER_1
};

// const uint16_t* leader1[]  = {
//   (uint16_t[]){2, KC_I, KC_E, SEQ_IE },
//   (uint16_t[]){3, KC_I, KC_E, KC_E, SEQ_IEE},
//   (uint16_t[]){0}
// };

// const uint16_t*  leader2[]  = {
//   (uint16_t[]){2, KC_O, KC_T, SEQ_OT},
//   (uint16_t[]){2, KC_I, KC_E, SEQ_IE},
//   (uint16_t[]){0}
// };

// const uint16_t*  leader3[]  = {
//   (uint16_t[]){1, KC_TRNS, SEQ_LAYER_1 },
//   (uint16_t[]){0}
// };

// const uint16_t** config[LD_LAST- LD_FIRST -1];

class Leadermanager : public testing::Test {

public:
  Leadermanager() {
    keyseq_reset();
    // init_leadermanager();
    // config[LD_LEADER1 - LD_FIRST - 1 ] = leader1; 
    // config[LD_LEADER2 - LD_FIRST - 1] = leader2; 
    // config[LD_LEADER3 - LD_FIRST - 1] = leader3; 
    // leadermanager_set_config(config);
    // leaders_seq_reset();
  }

  virtual ~Leadermanager() {
  }

};

TEST_F(Leadermanager, no_match_test ) {
  // leaders_seq_put(KC_A);
  // leaders_seq_put(KC_B);
  // ASSERT_EQ(leaders_match(0), DO_NOT_MATCH );
}

// TEST_F(Leadermanager, match_test ) {
//   leaders_seq_put(KC_I);
//   leaders_seq_put(KC_E);
//   leaders_seq_put(KC_E);
//   ASSERT_EQ(leaders_match(0), SEQ_IEE );
// }

// TEST_F(Leadermanager, partial_match_test ) {
//   leaders_seq_put(KC_I);
//   uint16_t t = leaders_match(0);
//   ASSERT_EQ(t, PARTIAL_MATCH );
// }

// TEST_F(Leadermanager, transparent_match_test ) {
//   leaders_seq_put(KC_I);
//   ASSERT_EQ(leaders_match(2), SEQ_LAYER_1 );
// }

// TEST_F(Leadermanager, leader_works ) {
//   ASSERT_EQ(get_leader(), KC_NO);
// }

// TEST_F(Leadermanager, set_leader_works ) {
//   set_leader(LEADER1);
//   ASSERT_EQ(get_leader(), LEADER1);
//   remove_leader();
//   ASSERT_EQ(get_leader(), 0x0000);
// }

// TEST_F(Leadermanager, remove_leader_with_matching_guard ) {
//   set_leader(LEADER1);
//   set_leader_sentinels(MOMENTARY_SENTINEL);
//   remove_leader();
//   ASSERT_EQ(get_leader(), LEADER1);
//   remove_leader_sentinels(MOMENTARY_SENTINEL);
//   remove_leader();
//   ASSERT_EQ(get_leader(), 0x0000);
// }

// TEST_F(Leadermanager, remove_leader_with_2_sentinels ) {
//   set_leader(LEADER1);
//   set_leader_sentinels(MOMENTARY_SENTINEL | ONESHOT_SENTINEL);
//   remove_leader();
//   ASSERT_EQ(get_leader(), LEADER1);
//   remove_leader_sentinels(MOMENTARY_SENTINEL);
//   remove_leader();
//   ASSERT_EQ(get_leader(), LEADER1);
//   remove_leader_sentinels(ONESHOT_SENTINEL);
//   remove_leader();
//   ASSERT_EQ(get_leader(), 0x0000);
// }
