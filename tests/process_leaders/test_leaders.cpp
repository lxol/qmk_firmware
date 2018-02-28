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
class KeyseqTest : public TestFixture {};

TEST_F(KeyseqTest, test1) {
    TestDriver driver;
    InSequence s;
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_W)));
    press_key(1, 0);
    keyboard_task();
    release_key(1, 0);
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_1)));
    press_key(0, 1);
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    release_key(0, 1);
    keyboard_task();
}

// TEST_F(KeyseqTest, leader_simple_sequence_oneshot) {
//     leaders_init();
//     keyseq_set_definitions(definitions);
//     TestDriver driver;
//     InSequence s;
//     press_key(0, 1); //LD_LEADER1
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_L)));
//     press_key(0, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_Z)));
//     press_key(0, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(0, 0);
//     keyboard_task();
//     release_key(0, 1); //release LD_LEADER1
//     keyboard_task();
// }

// TEST_F(KeyseqTest, leader_simple_sequence_momentary) {
//     leaders_init();
//     keyseq_set_definitions(definitions);
//     TestDriver driver;
//     InSequence s;
//     // leaders_init();
//     press_key(1, 1); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();

//     release_key(1, 1); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_X)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();
// }

// TEST_F(KeyseqTest, leader_test3) {
//     leaders_init();
//     keyseq_set_definitions(definitions);
//     TestDriver driver;
//     InSequence s;
//     // leaders_init();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
//     press_key(2, 0);
//     keyboard_task();
//     press_key(1, 1); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K,KC_C)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K)));
//     release_key(2, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_K)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();

//     release_key(1, 1); //LD_LEADER2
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_X)));
//     press_key(1, 0);
//     keyboard_task();
//     EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
//     release_key(1, 0);
//     keyboard_task();
// }
