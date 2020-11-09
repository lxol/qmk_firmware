/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
/* #include "muse.h" */

extern keymap_config_t keymap_config;


enum planck_layers {
  _QWERTY,
  _RAISE,
  _LOWER,
  _LOWER2,
  _DOUBLERAISE,
  _FUN,
  _NUM,
  _SYM
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER  _QWERTY

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  LOWER,
  FUN,
  LD_RAISE,
  LD_LOWER,
  LD_LOWER2,
  LD_NUM,

  SEQ_SYMBOLS,
  SEQ_RAISE,
  SEQ_LOWER,
  SEQ_LOWER2,
  SEQ_DOUBLERAISE,
  SEQ_TRIPLERAISE,
  SEQ_FUN,
  SEQ_NUM,
  SEQ_DOUBLELOWER,
  SEQ_CBRCPAIR,
  SEQ_PRNPAIR,
  SEQ_BRCPAIR,
  SEQ_QUOTPAIR,
  SEQ_DQUOTPAIR,
  DYNAMIC_MACRO_RANGE,
};
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define KC_XPST LCTL(LSFT(KC_V))  // paste clipboard
#define KC_XCOP LCTL(LSFT(KC_C))  // copy to clipboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
   KC_ESC ,  KC_Q ,    KC_W ,     KC_E ,     KC_R ,    KC_T ,     KC_Y ,   KC_U ,     KC_I ,    KC_O ,    KC_P ,    KC_MINS  ,
   KC_TAB ,  KC_A ,    KC_S ,     KC_D ,     KC_F ,    KC_G ,     KC_H ,   KC_J ,     KC_K ,    KC_L ,    KC_SCLN , KC_QUOT  ,
   KC_TILD , KC_Z ,    KC_X ,     KC_C ,     KC_V ,    KC_B ,     KC_N ,   KC_M ,     KC_COMM , KC_DOT ,  KC_SLSH , KC_PLUS  ,
   KC_XPST , LD_NUM ,  LD_LOWER2, KC_RGUI,   KC_LSFT,  KC_LALT,   KC_SPC , LD_RAISE , KC_LCTL,  KC_RGUI , LD_NUM ,  KC_ENT 
                               ),

[_RAISE] = LAYOUT_planck_grid (
   KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    KC_MINS  ,
   XXXXXXX , XXXXXXX , XXXXXXX , KC_LSFT , KC_RGUI , KC_BSPC , KC_EQL ,  KC_ENT ,  XXXXXXX , XXXXXXX , KC_SCLN , KC_QUOT  ,
   KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_COMM , KC_DOT ,  KC_SLSH , KC_PLUS  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RGUI , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
                               ),

[_DOUBLERAISE] = LAYOUT_planck_grid (
   KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    KC_MINS  ,
   XXXXXXX , KC_LCBR , KC_RCBR , KC_LPRN , KC_RPRN , KC_BSPC,  KC_LEFT , KC_DOWN ,  KC_UP ,   KC_RIGHT , KC_LBRC , KC_RBRC  ,
   XXXXXXX , XXXXXXX , XXXXXXX , KC_LBRC , KC_RBRC , KC_PIPE,  XXXXXXX , KC_PGDOWN, KC_PGUP , KC_LCBR ,  KC_RCBR , KC_END  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
                                     ), 

[_LOWER] = LAYOUT_planck_grid (
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , XXXXXXX , XXXXXXX  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_CIRC , KC_AMPR , KC_ASTR , XXXXXXX ,  XXXXXXX , XXXXXXX  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC ,  XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX
                               ), 

[_LOWER2] = LAYOUT_planck_grid (
   XXXXXXX , XXXXXXX , XXXXXXX , KC_LCBR , KC_RCBR , KC_BSLS,  KC_HOME , XXXXXXX ,  XXXXXXX , KC_LPRN ,  KC_RPRN , KC_BSPC  ,
   XXXXXXX , XXXXXXX , XXXXXXX , KC_LPRN , KC_RPRN , KC_BSPC,  KC_LEFT , KC_DOWN ,  KC_UP ,   KC_RIGHT , KC_LBRC , KC_RBRC  ,
   XXXXXXX , XXXXXXX , XXXXXXX , KC_LBRC , KC_RBRC , KC_PIPE,  XXXXXXX , KC_PGDOWN, KC_PGUP , KC_LCBR ,  KC_RCBR , KC_END  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LALT , KC_SPC ,  XXXXXXX ,  XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX
                               ), 

[_FUN] = LAYOUT_planck_grid(
   KC_F12 ,  KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
 ) ,

[_NUM] = LAYOUT_planck_grid(
   XXXXXXX , KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    XXXXXXX , KC_1 ,    KC_2 ,    KC_3 ,    KC_0 ,    KC_MINS ,
   XXXXXXX , KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    XXXXXXX , KC_4 ,    KC_5 ,    KC_6 ,    KC_EQL ,  XXXXXXX ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_7 ,    KC_8 ,    KC_9 ,    XXXXXXX , KC_PLUS ,
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
 ) ,


[_SYM] = LAYOUT_planck_grid (
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,
   XXXXXXX , KC_LBRC , KC_RBRC ,  KC_LPRN , KC_RPRN , KC_BSPC , KC_LEFT , KC_ENT ,  XXXXXXX , KC_RIGHT ,XXXXXXX , XXXXXXX  ,
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,
   XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
 )
};


#ifdef LEADERS_ENABLE

uint16_t* user_definitions[]  = {
  (uint16_t[]){6, LD_RAISE, KC_K,     KC_I,    KC_E, SEQ_CBRCPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K,     KC_I,    KC_D, SEQ_PRNPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K,     KC_I,    KC_C, SEQ_BRCPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K,     KC_I,    KC_QUOT, SEQ_QUOTPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K,     KC_I,    KC_SCLN, SEQ_DQUOTPAIR },
  (uint16_t[]){5, LD_RAISE, KC_K,     KC_TRNS, SEQ_SYMBOLS },
  (uint16_t[]){5, LD_RAISE, KC_A,     KC_TRNS, SEQ_FUN },
  /* (uint16_t[]){5, LD_RAISE, LD_RAISE, LD_RAISE, SEQ_TRIPLERAISE }, */
  (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_DOUBLERAISE },
  (uint16_t[]){4, LD_RAISE, KC_TRNS,  SEQ_RAISE },
  (uint16_t[]){5, LD_LOWER, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){4, LD_LOWER, KC_TRNS,  SEQ_LOWER },
  //(uint16_t[]){4, LD_LOWER2, LD_LOWER2,  SEQ_ALT },
  (uint16_t[]){4, LD_LOWER2, LD_LOWER2, SEQ_DOUBLELOWER },
  (uint16_t[]){4, LD_LOWER2, KC_TRNS,  SEQ_LOWER2 },
  (uint16_t[]){4, LD_NUM, KC_TRNS,  SEQ_NUM },
  (uint16_t[]){1}
};

void leaders_init_user(void) {
  keyseq_set_definitions(user_definitions);
}

bool keyseq_press_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case SEQ_LOWER:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_LOWER, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_LOWER, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }

  case SEQ_LOWER2:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_LOWER2, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      case KC_LALT:
        register_code16(kc);
        return false;
      default:
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_LOWER2, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      case KC_LALT:
        unregister_code16(kc);
        return false;
      default:
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_NUM:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_NUM, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      case KC_LALT:
        register_code16(kc);
        return false;
      default:
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_NUM, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      case KC_LALT:
        unregister_code16(kc);
        return false;
      default:
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_SYMBOLS:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_SYM, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_SYM, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_RAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      /* case KC_SPC: */
      /*   register_code16(kc); */
      /*   return true; */
      /* case KC_RALT: */
      /*   register_code16(kc); */
      /*   return true; */
      /* case KC_RSFT: */
      /*   register_code16(kc); */
      /*   return true; */
      /* case KC_RGUI: */
      /*   register_code16(kc); */
      /*   return true; */
      default:
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      switch (kc) {
      case KC_NO:
        return false;
      /* case KC_SPC: */
      /*   unregister_code16(kc); */
      /*   return false; */
      /* case KC_RALT: */
      /*   unregister_code16(kc); */
      /*   return false; */
      /* case KC_RSFT: */
      /*   unregister_code16(kc); */
      /*   return true; */
      /* case KC_RGUI: */
      /*   unregister_code16(kc); */
      /*   return true; */
      default:
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_DOUBLERAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      if (kc==KC_1||kc==KC_2||kc==KC_3||kc==KC_4||kc==KC_5||kc==KC_6||kc==KC_7||kc==KC_8||kc==KC_9||kc==KC_0) {
        register_code16(KC_RGUI);
      }
      register_code16(kc);
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      unregister_code16(kc);
      if (kc==KC_1||kc==KC_2||kc==KC_3||kc==KC_4||kc==KC_5||kc==KC_6||kc==KC_7||kc==KC_8||kc==KC_9||kc==KC_0) {
        unregister_code16(KC_RGUI);
      }
      return false;
    }
  case SEQ_FUN:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_FUN, record->event.key);
      register_code16(kc);
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_FUN, record->event.key);
      unregister_code16(kc);
      return false;
    }
  case SEQ_DOUBLELOWER:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      register_code16(KC_RGUI);
      register_code16(KC_MINS);
      unregister_code16(KC_MINS);
      unregister_code16(KC_RGUI);
      register_code16(kc);
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      unregister_code16(kc);
      register_code16(KC_ESC);
      unregister_code16(KC_ESC);
      return false;
    }
  case SEQ_CBRCPAIR:
    if (record->event.pressed) {
      SEND_STRING("{}");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_PRNPAIR:
    if (record->event.pressed) {
      SEND_STRING("()");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_BRCPAIR:
    if (record->event.pressed) {
      SEND_STRING("[]");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_QUOTPAIR:
    if (record->event.pressed) {
      register_code16(KC_QUOT);
      unregister_code16(KC_QUOT);
      register_code16(KC_QUOT);
      unregister_code16(KC_QUOT);
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_DQUOTPAIR:
    if (record->event.pressed) {
      SEND_STRING("\"\"");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  }
  return false;
}

#endif
