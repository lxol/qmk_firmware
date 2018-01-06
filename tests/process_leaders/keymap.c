 /* Copyright 2018 Alex Olkhovskiy
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

#include "quantum.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {

    //{ 0 ,   1 ,     2 ,     3 ,     4 ,     5 ,     6 ,     7 ,     8 ,     9 ,       }
    { KC_A ,  KC_B ,  KC_C ,  KC_D ,  KC_E ,  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    /* //{ 0 ,   1 ,       2 ,        3 ,        4 ,       5 ,       6 ,      7 ,           8 ,     9 ,       } */
    /* { KC_A ,  LD_TEST , LD_TEST2 , LD_TEST3 , KC_RSFT , KC_LCTL , COMBO1 , SFT_T(KC_P) , M(0) ,  KC_NO } ,  */
    /* { KC_NO , KC_NO ,   KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
    /* { KC_NO , KC_NO ,   KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
    /* { KC_C ,  KC_D ,    KC_NO ,    KC_NO ,    KC_NO ,   KC_NO ,   KC_NO ,  KC_NO ,       KC_NO , KC_NO } ,  */
 } ,          
  [1] = { 
    //{ 0 ,   1 ,     2 ,     3 ,     4 ,     5 ,     6 ,     7 ,     8 ,     9 ,       }
    { KC_A ,  KC_B ,  KC_C ,  KC_D ,  KC_E ,  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
    { KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO } , 
 } ,          
 };

