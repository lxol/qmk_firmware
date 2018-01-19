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

extern uint16_t ld_test;
class Leaders : public TestFixture {};

// TEST_F(Leaders, no_leaders) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
//     press_key(0, 0);
//     keyboard_task();
//     release_key(0, 0);
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     keyboard_task();
// }

// TEST_F(Leaders, leader_press_release) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_T)));
//     press_key(5, 0); //LD_LEADER1
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(5, 0); //LD_LEADER1
//     keyboard_task();
// }

// TEST_F(Leaders, leader_press_sequence) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     ASSERT_EQ(leaders_seq_debug_get_at(0), 0);
//     press_key(5, 0); //LD_LEADER1
//     keyboard_task();
//     ASSERT_EQ(leaders_seq_debug_get_at(0), 0);
//     release_key(5, 0); //LD_LEADER1
//     keyboard_task();
//     ASSERT_EQ(leaders_seq_debug_get_at(0), 0);
//     press_key(0, 0); //KC_A
//     keyboard_task();
//     ASSERT_EQ(leaders_seq_debug_get_at(1), KC_A);
//     ASSERT_EQ(leaders_seq_debug_get_at(0), 1);
//     release_key(0, 0); //KC_A release
//     keyboard_task();
//     ASSERT_EQ(leaders_seq_debug_get_at(1), KC_A);
//     ASSERT_EQ(leaders_seq_debug_get_at(0), 1);
//     uint16_t leader = get_leader();
//     ASSERT_EQ(leader, SAFE_RANGE);
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_I)));
//     press_key(1, 0); //KC_B
//     keyboard_task();
//     ASSERT_EQ(leaders_seq_debug_get_at(2), KC_B);
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0); //KC_B
//     keyboard_task();
//     leader = get_leader();
//     ASSERT_EQ(leader, KC_NO);
//     // the leader should be released after that
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
//     press_key(0, 0); //KC_A
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0); //KC_A
//     keyboard_task();
// }

// TEST_F(Leaders, oneshot) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     press_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     release_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
//     press_key(0, 0); //KC_A
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0); //KC_A
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
//     press_key(0, 0); //KC_A
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0); //KC_A
//     keyboard_task();
// }

TEST_F(Leaders, momentary) {
    TestDriver driver;
    InSequence s;
    leaders_init();

    press_key(6, 0); //LD_LEADER2
    keyboard_task();

    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
    press_key(0, 0); //KC_A
    keyboard_task();

    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    release_key(0, 0); //KC_A
    keyboard_task();

    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
    press_key(0, 0); //KC_A
    keyboard_task();

    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    // release_key(0, 0); //KC_A
    // keyboard_task();

    // release_key(6, 0); //LD_LEADER2
    // keyboard_task();

    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
    // press_key(0, 0); //KC_A
    // keyboard_task();
    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    // release_key(0, 0); //KC_A
    // keyboard_task();
}

// TEST_F(Leaders, layers) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     press_key(7, 0); //LD_LEADER3
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
//     press_key(4, 0); 
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(4, 0);
//     keyboard_task();

//     press_key(9, 0);
//     keyboard_task();
//     release_key(9, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();

//     press_key(9, 0);
//     keyboard_task();
//     release_key(9, 0);
//     keyboard_task();
//     press_key(9, 0);
//     keyboard_task();
//     release_key(9, 0);
//     keyboard_task();
// }

// TEST_F(Leaders, leader_multiple_press1) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     press_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     release_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     press_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     release_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
//     press_key(0, 0); //KC_A
//     keyboard_task();
// }

// TEST_F(Leaders, leader_multiple_press2) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     press_key(7, 0); //LD_LEADER3
//     keyboard_task();
//     release_key(7, 0); //LD_LEADER3
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_X)));
//     press_key(7, 0); //LD_LEADER3
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(7, 0); //LD_LEADER3
//     keyboard_task();
// }

// TEST_F(Leaders, leader_leader_chain) {
//     TestDriver driver;
//     InSequence s;
//     leaders_init();
//     press_key(5, 0); //LD_LEADER1
//     keyboard_task();
//     release_key(5, 0); //LD_LEADER1
//     keyboard_task();
//     press_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_U)));
//     press_key(0, 0); 
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0); 
//     keyboard_task();
//     release_key(6, 0); //LD_LEADER2
//     keyboard_task();
//     uint16_t leader = get_leader();
//     ASSERT_EQ(leader, KC_NO);
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
//     press_key(0, 0); //KC_A
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0); 
//     keyboard_task();
// }
