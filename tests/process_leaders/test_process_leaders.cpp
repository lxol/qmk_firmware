/* Copyright 2017 Fred Sundvik
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

#include "test_common.hpp"

using testing::_;
using testing::InSequence;

LEADERMANAGER_EXTERNS();

// extern uint16_t* keyseq_definitions[];


// uint16_t** _keyseq_definitions[]  = {

//   (uint16_t[]){0xffff}
// };


// extern const uint16_t* keyseq_definitions[] =

//    (const uint16_t*) {
//     // (uint16_t[3]){KC_A, KC_B, KC_C },
//     (uint16_t[1]){0xffff}
//   };
// // extern "C" {
//   {
//     (uint16_t []){KC_A, KC_B, KC_C},
//     (uint16_t[]){0xffff}
//   };
// // }

keypos_t key = (keypos_t) {
  // .col = 0,
  // .row = 0
};
keyevent_t press_event = keyevent_t {
  .key = key,
  .pressed = true
};

keyrecord_t pressed_record = (keyrecord_t) {
  .event = press_event
};
// typedef struct {
//     keypos_t key;
//     bool     pressed;
//     uint16_t time;
// } keyevent_t;
// typedef struct {
//     keyevent_t  event;
// #ifndef NO_ACTION_TAPPING
//     tap_t tap;
// #endif
// } keyrecord_t;
// keys[i] = (xxxos_t) {
//   .col = i,
//   .row = i
// };
class ProcessLeadersTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    leaders_init();
    // keyseq_definitions = _keyseq_definitions;
  }
};

TEST_F(ProcessLeadersTest, process_leaders_basic_test) {
  process_leaders(KC_A, &pressed_record);
  ASSERT_EQ(keyseq_index, 0);
  ASSERT_EQ(momentary_sentinels, 0);
  ASSERT_EQ(oneshot_sentinel, true);
}

TEST_F(ProcessLeadersTest, process_leaders_basic_match_test) {
  
  // keyseq_definitions  = (const uint16_t*) {
  //   // (uint16_t[3]){KC_A, KC_B, KC_C },
  //   (uint16_t[1]){0xffff}
  // };

// // extern "C" {
  // fixtures
  // test
  process_leaders(KC_A, &pressed_record);
}
