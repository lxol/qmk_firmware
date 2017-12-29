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
// #include "action_tapping.h"

using testing::_;
using testing::InSequence;

extern uint16_t ld_test;
class NewLeader : public TestFixture {};

TEST_F(NewLeader, Leader_Basic_Test) {
    TestDriver driver;
    InSequence s;
    LEADERS_EXTERNS();
    ASSERT_EQ(ld_leader_index, 0) << "initial index should be 0";
    press_key(1, 0);
    keyboard_task();
    ASSERT_EQ(ld_leaders[0], ld_test) << "ld_leaders[0] should contain LD_TEST";
    ASSERT_EQ(press_state, 0b1) << "leader press should be memorized";
    ASSERT_EQ(ld_leader_index, 1) << "ld_leader_index should be 1";
    release_key(1, 0);
    keyboard_task();
    ASSERT_EQ(ld_leader_index, 1) << "index should stay the same after first unmemorize ";
    ASSERT_EQ(ld_oneshot, true) << "leader relase doesn't trigger oneshot protection";
    ASSERT_EQ(press_state, 0) << "leader press should be forgotten";
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
    press_key(0, 0);
    keyboard_task();
    ASSERT_EQ(ld_leader_index, 0) << "leader index should be cleared after first match";
}

TEST_F(NewLeader, Leader_Momentary_Test) {
    TestDriver driver;
    InSequence s;

    LEADERS_EXTERNS();

    press_key(1, 0); // press leader
    keyboard_task();

    press_key(0, 0); // press key under leader
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
    keyboard_task();

    release_key(0, 0); // release key under leader
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();

    release_key(1, 0); // release leader key
    keyboard_task();

    ASSERT_EQ(ld_oneshot, false) << "one shot should be cleared";
    ASSERT_EQ(ld_leader_index, 0) << "leader index should be cleared after first match";

    press_key(0, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
    keyboard_task();

}

TEST_F(NewLeader, Two_Leaders_Test) {
    TestDriver driver;
    InSequence s;

    LEADERS_EXTERNS();

    press_key(1, 0); // press leader LD_TEST
    keyboard_task();
    press_key(2, 0); // press LD_TEST2
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_Y)));
    press_key(3, 0); // press LD_TEST3
    keyboard_task();
    ASSERT_EQ(ld_oneshot, true) << "3 leader presses leave ld_onshot on";
    ASSERT_EQ(ld_leader_index, 3) << "ld_leader_index = 3 after 3 leaders presses";
}
