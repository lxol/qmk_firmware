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

// extern "C" {
//   void memorize_press(keypos_t key, uint16_t keycode);
// }

class Leaders : public TestFixture {};

TEST_F(Leaders, First ) {
    // TestDriver driver;
    // InSequence s;

    keypos_t key1 = (keypos_t) {
      .col = 1,
      .row = 2
    };
    LEADERS_EXTERNS();
    leaders_press_t ld = (leaders_press_t) {
      .key = key1,
        .leader = KC_NO 
        };
    leaders_init();
    ASSERT_EQ(press_state, 0) << "press_state should be 0 after init";
    memorize_press(key1,  1);
    ASSERT_EQ(press_state, 1) << "the first bit should be 1 after first memorizing";
    unmemorize_press(key1);
    ASSERT_EQ(press_state, 0) << "press_state == 0 after unmemorizing";
    // leaders_init();
    // memorize_press(keypos_t key, uint16_t keycode);
    // press_key(7, 0);

    // // Tapping keys does nothing on press
    // EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    // run_one_scan_loop();
    // release_key(7, 0);
}
