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
#include "action_tapping.h"

using testing::_;
using testing::InSequence;

class Leaders : public TestFixture {};

TEST_F(Leaders, BasicLeaderTest) {
    TestDriver driver;
    InSequence s;

    press_key(1, 0);
    keyboard_task();
    release_key(1, 0);
    keyboard_task();
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
    press_key(0, 0);
    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    // keyboard_task();
    // press_key(0, 0);
    keyboard_task();
    // keyboard_task();
    // First we get the key press
    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_P)));
    // // Then the release
    // EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    // run_one_scan_loop();
}

