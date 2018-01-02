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
#include "leaders/keychain.h"
}

KEYCHAIN_EXTERNS();

class Keychain : public testing::Test {
public:
  Keychain() {
    keychain_init();
  }

  virtual ~Keychain() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  keypos_t key1 = (keypos_t) {
    .col = 1,
    .row = 1
  };

  keypos_t key2 = (keypos_t) {
    .col = 1,
    .row = 1
  };

  bool keychain_match_user(uint16_t leader, uint8_t idx) {
    return true;
  }
};

TEST_F(Keychain, init_works ) {
  ASSERT_EQ(free_idx, 0) << "init sets free index to 0";
  ASSERT_EQ(keychain_size(), 0) << "init sets size of the active chain to 0";
}

TEST_F(Keychain, keychain_add_works ) {
  uint8_t idx = keychain_add(key1);
  ASSERT_EQ(idx, 0) << "";
  ASSERT_EQ(free_idx, 1);
  ASSERT_EQ(first_idx, 0);
  ASSERT_EQ(last_idx, 0);
  ASSERT_EQ(keychain_size(), 1);
}

TEST_F(Keychain, keychain_free_works ) {
  uint8_t first_idx = keychain_add(key1);
  keychain_add(key2);
  keychain_free(first_idx);
  ASSERT_EQ(first_idx, 0);
  ASSERT_EQ(keychain_size(), 0);
}

TEST_F(Keychain, keychain_has_next_works ) {
  uint8_t idx1 = keychain_add(key1);
  uint8_t idx2 = keychain_add(key2);
  ASSERT_EQ(keychain_has_next(idx1), true);
  ASSERT_EQ(keychain_has_next(idx2), false);
}
