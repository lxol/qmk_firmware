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
extern "C" {
#include "leaders/leaderlist.h"
}


class Leaderlist : public testing::Test {
  
public:
  Leaderlist() {
    init_leaderlist();
  }

  virtual ~Leaderlist() {
    // You can do clean-up work that doesn't throw exceptions here.
  }
  const uint16_t LEADER1 = 1;
  const uint16_t LEADER2 = 2;
  const uint16_t LEADER3 = 3;
};

TEST_F(Leaderlist, init_works ) {
  ASSERT_EQ(current_leader(), KC_NO);
}

TEST_F(Leaderlist, add_leader_works ) {
  add_leader(LEADER1);
  ASSERT_EQ(current_leader(), LEADER1);
}

TEST_F(Leaderlist, remove_leader_oneshot_works ) {
  add_leader(KC_A);
  add_leader(KC_B);
  // ASSERT_EQ(current_leader(), KC_A);
}
