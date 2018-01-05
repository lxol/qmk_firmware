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
  LD_LAST,
  SEQ_IE,
  SEQ_OT,
  SEQ_IIE,
  SEQ_IEE
};

const uint16_t* leader1[]  = {
  (uint16_t[]){2, KC_I, KC_E, SEQ_IE },
  (uint16_t[]){3, KC_I, KC_E, KC_E, SEQ_IEE},
  (uint16_t[]){0}
};

const uint16_t*  leader2[]  = {
  (uint16_t[]){2, KC_O, KC_T, SEQ_OT},
  (uint16_t[]){2, KC_I, KC_E, SEQ_IE},
  (uint16_t[]){0}
};

const uint16_t** config[LD_LAST- LD_FIRST -1];

class Leadermanager : public testing::Test {

public:
  Leadermanager() {
    // init_leaderlist();
    config[LD_LEADER1 - LD_FIRST - 1 ] = leader1; 
    config[LD_LEADER2 - LD_FIRST - 1] = leader2; 
  }

  virtual ~Leadermanager() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

};

TEST_F(Leadermanager, no_match_test ) {
  uint16_t seq[] = {2, KC_A, KC_B};
  uint16_t t = leaders_match(0, seq, config);
  ASSERT_EQ(t, DO_NOT_MATCH );
}

TEST_F(Leadermanager, match_test ) {
  uint16_t seq[] = {3, KC_I, KC_E, KC_E };
  uint16_t t = leaders_match(0, seq, config);
  ASSERT_EQ(t, SEQ_IEE );
}

TEST_F(Leadermanager, partial_match_test ) {
  uint16_t seq[] = {2, KC_I };
  uint16_t t = leaders_match(0, seq, config);
  ASSERT_EQ(t, PARTIAL_MATCH );
}
