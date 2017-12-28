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

extern "C" {
#include "process_leaders.h"
}
using testing::_;
using testing::InSequence;

class Presses : public TestFixture {};

TEST_F(Presses, First ) {
  // fixtures
  keypos_t keys[20];
  for (int8_t i; i < 20; i++) {
    keys[i] = (keypos_t) {
      .col = i,
      .row = i
    };
  }

  LEADERS_EXTERNS();
  leaders_init();
  ASSERT_EQ(press_state, 0) << "press_state should be 0 after init";
  memorize_press(keys[0],  1);
  ASSERT_EQ(press_state, 1) << "the first bit should be 1 after first memorizing";
  unmemorize_press(keys[0]);
  ASSERT_EQ(press_state, 0) << "press_state == 0 after unmemorizing";
  memorize_press(keys[0],  0);
  memorize_press(keys[1],  1);
  memorize_press(keys[2],  2);
  memorize_press(keys[3],  3);
  unmemorize_press(keys[1]);
  // ASSERT_EQ(press_state, 0b0000000000000101) << "memorizing/unmemorizing";
  ASSERT_EQ(press_state, 0b1101) << "memorizing/unmemorizing";
  ASSERT_EQ(recall_press(keys[2]).key.row, 2) << "recall pressed key";

  ASSERT_EQ(recall_press(keys[2]).key.col, 2) << "recall pressed key";
  ASSERT_EQ(recall_press(keys[2]).leader, 2) << "recall pressed key";

  leaders_init();
  for (uint8_t i; i < 16; i ++) {
    memorize_press(keys[i],  i);
  }
  ASSERT_EQ(press_state, 0b1111111111111111) << "memorizing max 16 presses";
  // memorize_press(keys[0],  1);
  unmemorize_press(keys[10]);
  ASSERT_EQ(press_state, 0b1111101111111111) << "unmemorizing when max 16 presses";
  memorize_press(keys[10],  10);
  ASSERT_EQ(press_state, 0b1111111111111111) << "memorizing again when 15 presses";
  memorize_press(keys[17],  10);
  ASSERT_EQ(press_state, 0) << "memorizing when max 16 presses should reset press_state";

}
