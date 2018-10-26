// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2
enum planck_layers {
  _QWERTY,
  _LEFT,
  _RAISE,
  _RAISE1,
  _RAISE2,
  _LOWER,
  _LOWER1,
  _DOUBLERAISE,
  _FUN,
  _PAIRS,
  _SYM,
  _MODIFIER,
  _MOUSE
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER  _QWERTY

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  RAISE,
  LOWER,
  FUN,
  MOUSE,
  BACKLIT,
  LD_RAISE,
  LD_PAIRS,
  LD_LOWER,
  LD_LOWER1,
  LD_SYM,

  SEQ_SYMBOLS,
  SEQ_RAISE,
  SEQ_RAISE1,
  SEQ_RAISE2,
  SEQ_LOWER,
  SEQ_LOWER1,
  SEQ_PAIRS,
  SEQ_DOUBLERAISE,
  SEQ_MODIFIERS,
  SEQ_LEFT,
  SEQ_RIGHT,
  SEQ_VIM_CLI,
  SEQ_UP,
  SEQ_DOWN,
  SEQ_CBRCPAIR,
  SEQ_PRNPAIR,
  SEQ_BRCPAIR,
  SEQ_QUOTPAIR,
  SEQ_DQUOPAIR,
  SEQ_EXPAND,
  SEQ_CONTRACT,
  SEQ_CTLALT,
  SEQ_CTLGUI,
  SEQ_GUIALT,
  DYNAMIC_MACRO_RANGE,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALTDEL LCTL(LALT(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    KC_ESC, LD_LOWER1, LD_LOWER1,  KC_LSFT, KC_LALT,  KC_, KC_ESC, LD_SPC,  LD_RAISE, KC_LCTL, XXXXXXX, KC_ENT
  ),

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */

  [_RAISE] = LAYOUT( /* [> RAISE <] */
    KC_1, KC_2,   KC_3,   KC_4, KC_5,                              KC_6, KC_7,    KC_8,   KC_9, KC_0 ,
    KC_TAB, KC_GRV, KC_LBRC, KC_RBRC, KC_BSPC,                    KC_ESC, KC_ENT,    XXXXXXX,   KC_QUOT, XXXXXXX,
    KC_EXLM, KC_AT,   KC_HASH,   KC_DLR, KC_PERC,                  KC_CIRC, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX ,
    /* KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   KC_EQL, KC_BSLS, */
    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

  /* [_LOWER] = LAYOUT( /\* [> RAISE <] *\/ */
  /*   KC_EXLM, KC_AT,   KC_HASH,   KC_DLR, KC_PERC,                  KC_CIRC, KC_AMPR,    KC_ASTR,   XXXXXXX, XXXXXXX , */
  /*   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX, */
  /*   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX, */
  /*   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX), */

  [_DOUBLERAISE] = LAYOUT( /* [> RAISE <] */
    XXXXXXX, KC_AT,   KC_UP,   KC_LCBR, KC_RCBR,                   KC_PGUP, KC_7,    KC_8,   KC_9, KC_ASTR ,
    KC_HASH, KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,                    KC_PGDN, KC_4,    KC_5,   KC_6, KC_PLUS ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3, KC_BSLS ,
    TG(_LW), KC_INS,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  XXXXXXX, KC_DOT, KC_0, KC_EQL  ),


  [_LOWER] = LAYOUT( /* [> RAISE <] */
    KC_EXLM, KC_AT,   KC_HASH,   KC_DLR, KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR,   KC_PLUS, KC_MINS ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  ),

  [_LOWER1] = LAYOUT( /* [> RAISE <] */
    XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,                KC_EQL, KC_MINS,    KC_PLUS,   KC_DEL, KC_BSPC,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_LEFT, KC_DOWN,    KC_UP,   KC_RIGHT, KC_ENT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  ),

  [_RAISE1] = LAYOUT( /* [> RAISE <] */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_MINS, KC_PLUS, KC_BSPC,                    XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_UNDS, KC_EQL,  XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  ),

  [_RAISE2] = LAYOUT( /* [> RAISE <] */
    KC_GRV,  KC_UNDS, KC_LCBR, KC_RCBR, KC_PIPE,                   XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    KC_TILD, KC_MINS, KC_LPRN, KC_RPRN, KC_BSPC,                    XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    KC_EQL,  KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  ),

  [_SYM] = LAYOUT( 
    XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  )
  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  /* [_LW] = LAYOUT( /\* [> LOWER <] *\/ */
  /*   KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10  , */
  /*   KC_DELT, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOWN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11  , */
  /*   KC_NO,   KC_VOLU, KC_NO,   KC_NO,   RESET,                     KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12  , */
  /*   KC_NO,   KC_VOLD, KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  TO(_QW), KC_PSCR, KC_SLCK, KC_PAUS ) /\*  *\/ */
 };

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};

#ifdef LEADERS_ENABLE
uint16_t* user_definitions[]  = {
  (uint16_t[]){4, LD_RAISE, KC_SCLN, SEQ_VIM_CLI },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_E, SEQ_CBRCPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_D, SEQ_PRNPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_C, SEQ_BRCPAIR },
  /* (uint16_t[]){5, LD_RAISE, KC_F, KC_TRNS, SEQ_DOUBLERAISE }, */
  /* (uint16_t[]){5, LD_RAISE, KC_D, KC_TRNS, SEQ_DOUBLERAISE }, */
  /* (uint16_t[]){5, LD_RAISE, KC_K, KC_TRNS, SEQ_SYMBOLS }, */
  (uint16_t[]){5, LD_RAISE, KC_M, KC_TRNS, SEQ_RAISE2 },
  (uint16_t[]){5, LD_RAISE, KC_COMM, KC_TRNS, SEQ_RAISE2 },
  (uint16_t[]){5, LD_RAISE, KC_K, KC_TRNS, SEQ_RAISE2 },
  /* (uint16_t[]){5, LD_RAISE, KC_J, KC_TRNS, SEQ_RAISE2 }, */
  /* (uint16_t[]){6, LD_RAISE, LD_RAISE, KC_LSFT, KC_K, SEQ_EXPAND }, */
  /* (uint16_t[]){6, LD_RAISE, LD_RAISE, KC_LSFT, KC_J, SEQ_CONTRACT }, */
  /* (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_DOUBLERAISE }, */
  (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_RAISE2 },
  /* (uint16_t[]){5, LD_RAISE, KC_L, KC_TRNS, SEQ_MODIFIERS }, */
  (uint16_t[]){4, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){4, LD_LOWER, KC_TRNS, SEQ_LOWER },
  (uint16_t[]){4, LD_LOWER1, KC_TRNS, SEQ_LOWER1 },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_O, SEQ_PRNPAIR },
  /* (uint16_t[]){5, LD_PAIRS, KC_I, KC_P, SEQ_PRNPAIR }, */
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_L, SEQ_CBRCPAIR },
  /* (uint16_t[]){5, LD_PAIRS, KC_I, KC_SCLN, SEQ_CBRCPAIR }, */
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_DOT, SEQ_BRCPAIR },
  /* (uint16_t[]){5, LD_PAIRS, KC_I, KC_SLSH, SEQ_BRCPAIR }, */
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_SCLN, SEQ_QUOTPAIR },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_QUOT, SEQ_DQUOPAIR },
  (uint16_t[]){4, LD_PAIRS, KC_TRNS, SEQ_PAIRS },
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
  case SEQ_LOWER1:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_LOWER1, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_LOWER1, record->event.key);
      if (kc != KC_NO) {
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
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_RAISE1:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_RAISE1, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE1, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_RAISE2:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_RAISE2, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE2, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_DOUBLERAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      if (kc != KC_NO && record->event.key.row == 0) {
        register_code16(KC_RGUI);
        register_code16(kc);
        unregister_code16(kc);
        unregister_code16(KC_RGUI);
      } else {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      if (kc != KC_NO && record->event.key.row != 0) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_PAIRS:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_PAIRS, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_PAIRS, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_VIM_CLI:
    if (record->event.pressed) {
      register_code16(KC_ESC);
      unregister_code16(KC_ESC);
      register_code16(KC_COLN);
      unregister_code16(KC_COLN);
    } 
    return false;
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
      SEND_STRING("''");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_DQUOPAIR:
    if (record->event.pressed) {
      SEND_STRING("\"\"");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
    // emacs er/expand-region C-s-u C-s-d
  case SEQ_EXPAND:
    if (record->event.pressed) {
      register_code16(KC_LGUI);
      register_code16(KC_LCTL);
      register_code16(KC_U);
      return false;
    } else {
      unregister_code16(KC_U);
      unregister_code16(KC_LCTL);
      unregister_code16(KC_LGUI);
      return false;
    }
  case SEQ_CONTRACT:
    if (record->event.pressed) {
      register_code16(KC_LGUI);
      register_code16(KC_LCTL);
      register_code16(KC_D);
      return false;
    } else {
      unregister_code16(KC_D);
      unregister_code16(KC_LCTL);
      unregister_code16(KC_LGUI);
      return false;
    }
  case SEQ_MODIFIERS: {
    uint16_t kc = keymap_key_to_keycode(_MODIFIER, record->event.key);
    if (record->event.pressed) {
      switch (kc) {
      case SEQ_CTLALT:
        register_code16(KC_LCTL);
        register_code16(KC_LALT);
        return false;
      case SEQ_CTLGUI:
        register_code16(KC_LCTL);
        register_code16(KC_LGUI);
        return false;
      case SEQ_GUIALT:
        register_code16(KC_LGUI);
        register_code16(KC_LALT);
        return false;
      }
      return false;
    } else {
      switch (kc) {
      case SEQ_CTLALT:
        unregister_code16(KC_LALT);
        unregister_code16(KC_LCTL);
        return false;
      case SEQ_CTLGUI:
        unregister_code16(KC_LGUI);
        unregister_code16(KC_LCTL);
        return false;
      case SEQ_GUIALT:
        unregister_code16(KC_LALT);
        unregister_code16(KC_LGUI);
        return false;
      }
      return false;
    }}
  }
  return false;
}

#endif
