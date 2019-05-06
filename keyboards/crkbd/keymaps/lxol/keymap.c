#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef OLED_DRIVER_ENABLE
  #include "oled_driver.h"
#endif

#include "leaders/press_state.h"
#include "process_leaders.h"
extern keymap_config_t keymap_config;


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;


enum custom_keycodes {
  LEFT = SAFE_RANGE,
  RAISE,
  LOWER,
  FUN,
  MOUSE,
  BACKLIT,
  LD_RAISE,
  LD_PAIRS,
  LD_LOWER,
  LD_DEEP,

  SEQ_SYMBOLS,
  SEQ_RAISE,
  SEQ_LOWER,
  SEQ_DEEP,
  SEQ_PAIRS,
  SEQ_DOUBLERAISE,
  SEQ_FUN,
  SEQ_CTL_SFT_FUN,
  SEQ_CTL_SFT_QWERTY,
  SEQ_CTL_ALT_QWERTY,
  SEQ_DOUBLELOWER,
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
  SEQ_TMUX1,
  SEQ_TMUX2,
  SEQ_SFT_ALT_CTL,
  SEQ_CTL_X_SFT_CTL_ALT,
  SEQ_CTL_X_CTL_ALT,
  SEQ_CTL_C_CTL_ALT,
  SEQ_CTL_C_SFT_CTL_ALT,
  DYNAMIC_MACRO_RANGE,
};

enum lxol_crkbd_keycodes {
  _QWERTY,
  _LEFT,
  _RAISE,
  _LOWER,
  _DEEP,
  _DOUBLERAISE,
  _DOUBLELOWER,
  _FUN,
  _PAIRS,
  _TMUX,
  _SYM,
  _MODIFIER,
  _MOUSE
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER  _QWERTY

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
                   KC_ESC ,   KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS, \
                   KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT, \
                   LD_LOWER , KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS, \
                               LD_LOWER , KC_LSFT , KC_LALT , KC_SPC , LD_RAISE , KC_LCTL  \
                    ),\
[_RAISE] = LAYOUT( \
                  KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    XXXXXXX   ,\
                  XXXXXXX ,  KC_ESC ,  KC_ESC ,   KC_ESC,   KC_ESC,   KC_BSPC , KC_EQL ,  KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,\
                  KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , XXXXXXX , XXXXXXX , XXXXXXX   ,\
                                      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
 ) ,\
[_DOUBLERAISE] = LAYOUT( \
  XXXXXXX ,  KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS  ,\
  KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT  ,\
  XXXXXXX ,  KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS  ,\
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
                         ), \
[_LOWER] = LAYOUT( \
  XXXXXXX , XXXXXXX , XXXXXXX , KC_END  , XXXXXXX , XXXXXXX , KC_SPC ,  XXXXXXX , KC_INS ,  KC_LPRN ,  KC_RPRN ,   KC_DEL  ,  \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_LBRC , KC_RBRC   , \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGDN , KC_PGUP , XXXXXXX ,  XXXXXXX ,  XXXXXXX  , \
   XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC ,  XXXXXXX , XXXXXXX \
),\
[_FUN] = LAYOUT( \
   KC_F12 ,          KC_F1 ,          KC_F2 ,          KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,  \
   KC_F12 ,          KC_F1 ,          KC_F2 ,          KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,  \
   XXXXXXX ,         XXXXXXX ,        XXXXXXX ,        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , \
           XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
 ) ,                  \
[_SYM] = LAYOUT(\
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , KC_LEFT , KC_RIGHT , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX \
 ) 
};

#ifdef LEADERS_ENABLE

uint16_t* user_definitions[]  = {
  (uint16_t[]){4, LD_RAISE, KC_SCLN, SEQ_VIM_CLI },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_E, SEQ_CBRCPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_D, SEQ_PRNPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_C, SEQ_BRCPAIR },
  (uint16_t[]){5, LD_RAISE, KC_K, KC_TRNS, SEQ_SYMBOLS },
  (uint16_t[]){7, LD_RAISE, LD_RAISE, KC_SPC, KC_SPC, KC_TRNS, SEQ_CTL_C_SFT_CTL_ALT },
  (uint16_t[]){6, LD_RAISE, LD_RAISE, KC_SPC, KC_TRNS, SEQ_CTL_C_CTL_ALT },
  (uint16_t[]){6, LD_RAISE, KC_SPC, KC_SPC, KC_TRNS, SEQ_CTL_X_SFT_CTL_ALT },
  (uint16_t[]){5, LD_RAISE, KC_SPC, KC_TRNS, SEQ_CTL_X_CTL_ALT },
  (uint16_t[]){6, LD_RAISE, KC_F, KC_S, KC_TRNS, SEQ_CTL_SFT_FUN },
  (uint16_t[]){5, LD_RAISE, KC_F, KC_TRNS, SEQ_FUN },
  (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_DOUBLERAISE },
  (uint16_t[]){4, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){5, LD_LOWER, LD_LOWER, KC_TRNS, SEQ_DOUBLELOWER },
  (uint16_t[]){5, LD_LOWER, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){4, LD_LOWER, KC_TRNS, SEQ_LOWER },

  (uint16_t[]){5, LD_DEEP, KC_I, KC_O, SEQ_PRNPAIR },
  (uint16_t[]){5, LD_DEEP, KC_I, KC_L, SEQ_BRCPAIR },
  (uint16_t[]){5, LD_DEEP, KC_I, KC_DOT, SEQ_CBRCPAIR },
  (uint16_t[]){4, LD_DEEP, KC_TRNS, SEQ_DEEP },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_O, SEQ_PRNPAIR },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_L, SEQ_CBRCPAIR },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_DOT, SEQ_BRCPAIR },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_SCLN, SEQ_QUOTPAIR },
  (uint16_t[]){5, LD_PAIRS, KC_I, KC_QUOT, SEQ_DQUOPAIR },
  (uint16_t[]){4, LD_PAIRS, KC_TRNS, SEQ_PAIRS },
  (uint16_t[]){1}
};

void leaders_init_user(void) {
  keyseq_set_definitions(user_definitions);
}

void set_press_state_str(void);
bool keyseq_press_user(uint16_t keycode, keyrecord_t *record) {

  set_press_state_str();
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
  case SEQ_DEEP:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DEEP, record->event.key);
      if (kc != KC_NO) {
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_DEEP, record->event.key);
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
  case SEQ_DOUBLERAISE:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLERAISE, record->event.key);
      register_code16(KC_RGUI);
      register_code16(KC_SLSH);
      unregister_code16(KC_SLSH);
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
  case SEQ_CTL_SFT_FUN:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_FUN, record->event.key);
      register_code16(KC_LSFT);
      register_code16(KC_LCTL);
      register_code16(kc);
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_FUN, record->event.key);
      unregister_code16(kc);
      unregister_code16(KC_LCTL);
      unregister_code16(KC_LSFT);
      return false;
    }
  case SEQ_CTL_ALT_QWERTY:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      register_code16(KC_LALT);
      register_code16(KC_LCTL);
      register_code16(kc);
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      unregister_code16(kc);
      unregister_code16(KC_LCTL);
      unregister_code16(KC_LALT);
      return false;
    }
  case SEQ_CTL_SFT_QWERTY:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      register_code16(KC_LCTL);
      register_code16(KC_LSFT);
      register_code16(kc);
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      unregister_code16(kc);
      unregister_code16(KC_LSFT);
      unregister_code16(KC_LCTL);
      return false;
    }
  case SEQ_DOUBLELOWER:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO ) {
        register_code16(KC_RGUI);
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
        unregister_code16(KC_RGUI);
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
  case SEQ_CTL_X_CTL_ALT:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_X);
        unregister_code16(KC_X);
        unregister_code16(KC_LCTL);
        register_code16(KC_LALT);
        register_code16(KC_LCTL);
        /* register_code16(KC_LSFT); */
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
        /* unregister_code16(KC_LSFT); */
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LALT);
      }
      return false;
    }
  case SEQ_CTL_X_SFT_CTL_ALT:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_X);
        unregister_code16(KC_X);
        unregister_code16(KC_LCTL);
        register_code16(KC_LALT);
        register_code16(KC_LCTL);
        register_code16(KC_LSFT);
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
        unregister_code16(KC_LSFT);
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LALT);
      }
      return false;
    }
  case SEQ_CTL_C_CTL_ALT:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_C);
        unregister_code16(KC_C);
        unregister_code16(KC_LCTL);
        register_code16(KC_LALT);
        register_code16(KC_LCTL);
        /* register_code16(KC_LSFT); */
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
        /* unregister_code16(KC_LSFT); */
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LALT);
      }
      return false;
    }
  case SEQ_CTL_C_SFT_CTL_ALT:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_C);
        unregister_code16(KC_C);
        unregister_code16(KC_LCTL);
        register_code16(KC_LALT);
        register_code16(KC_LCTL);
        register_code16(KC_LSFT);
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
        unregister_code16(KC_LSFT);
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LALT);
      }
      return false;
    }
  case SEQ_TMUX1:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_TMUX, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_A);
        unregister_code16(KC_A);
        unregister_code16(KC_LCTL);
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_TMUX, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
      return false;
    }
  case SEQ_TMUX2:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        register_code16(KC_LCTL);
        register_code16(KC_A);
        unregister_code16(KC_A);
        unregister_code16(KC_LCTL);
        register_code16(kc);
      }
      return false;
    } else {
      uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      if (kc != KC_NO) {
        unregister_code16(kc);
      }
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


void matrix_init_keymap(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif

  #ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.

const char *read_logo(void);
char layer_state_str[24];
char modifier_state_str[24];
char host_led_state_str[24];
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;
int press_state_str_idx = 0;

// const char *read_mode_icon(bool swap);
// void set_timelog(void);
// const char *read_timelog(void);

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }
  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}


const char* read_modifier_state(void) {
  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();

  snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods:%s %s %s %s",
    (modifiers & MOD_MASK_CTRL || one_shot & MOD_MASK_CTRL) ? "CTL" : "   ",
    (modifiers & MOD_MASK_GUI || one_shot & MOD_MASK_GUI) ? "GUI" : "   ",
    (modifiers & MOD_MASK_ALT || one_shot & MOD_MASK_ALT) ? "ALT" : "   ",
    (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? "SFT" : "   "
  );

  return modifier_state_str;
}

const char *read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();

  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
    (leds & (1 << USB_LED_NUM_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_CAPS_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_SCROLL_LOCK)) ? "on" : "- "
  );

  return host_led_state_str;
}

const char* read_layer_state(void) {
  switch (biton32(layer_state)) {
    case _QWERTY:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise  ");
      break;
    case _LOWER:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower  ");
      break;
    case _RAISE:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise ");
      break;
    default:
      switch (biton32(default_layer_state)) {
        case _QWERTY:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty ");
          break;
        case _LOWER:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: LOWER");
          break;
      }
      break;
  }

    return layer_state_str;
}

void matrix_scan_keymap(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    //If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_modifier_state());
    // matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

const char press_state_to_name[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};
char press_state_str[8] = {};
void set_press_state_str() {

  uint16_t current_press_state = press_state_get();
  uint8_t l = biton16(current_press_state);
  for (int8_t i = 0; i <= l; i++) {
    uint16_t keycode = press_state_get_press(i).keycode  ;
    if (keycode < 60) {
      press_state_str[i] = press_state_to_name[keycode];
    } else {
      press_state_str[i] = 'G';
    }
  }
  for (int8_t i = l; i <= sizeof(press_state_str); i++) {
      press_state_str[i] = ' ';
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_SLASH:
    case KC_F1 ... KC_F12:
    case KC_INSERT ... KC_UP:
    case KC_KP_SLASH ... KC_KP_DOT:
    case KC_F13 ... KC_F24:
    if (record->event.pressed) {
      set_keylog(keycode, record);
    }
      break;
    // set_timelog();
  }
  return true;
}

#endif


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_270;
    //return rotation;
  }
}

void render_crkbd_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
  oled_write_P(crkbd_logo, false);
}


void render_status(void) {

  /* oled_write_P(PSTR("Layer"), false); */
  /* switch (biton32(layer_state)) { */
  /*   case 0: */
  /*     oled_write_P(PSTR("Base "), false); */
  /*     break; */
  /*   case _RAISE: */
  /*     oled_write_P(PSTR("Raise"), false); */
  /*     break; */
  /*   case _DOUBLERAISE: */
  /*     oled_write_P(PSTR("Doubleraise"), false); */
  /*     break; */
  /*   case _LOWER: */
  /*     oled_write_P(PSTR("LOWER"), false); */
  /*     break; */
  /*   default: */
  /*     oled_write_P(PSTR("Unkn "), false); */
  /*     break; */
  /* } */
  /* oled_write_P(PSTR("Lyout"), false); */
  /* switch (biton32(default_layer_state)) { */
  /*   case _QWERTY: */
  /*     oled_write_P(PSTR("QWRTY"), false); */
  /*     break; */
  /*   case _RAISE: */
  /*     oled_write_P(PSTR("RAISE"), false); */
  /*     break; */
  /*   case _DOUBLERAISE: */
  /*     oled_write_P(PSTR("DBLRAISE"), false); */
  /*     break; */
  /*   case _LOWER: */
  /*     oled_write_P(PSTR("LOWER"), false); */
  /*     break; */
  /*   case _FUN: */
  /*     oled_write_P(PSTR("FUN"), false); */
  /*     break; */
  /*   case _SYM: */
  /*     oled_write_P(PSTR("SYM"), false); */
  /*     break; */
  /* } */

  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();

  oled_write_P(PSTR("Mods:"), false);
  oled_write_P( (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL ) ? PSTR(" CTL ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI  ) ? PSTR(" GUI ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT  ) ? PSTR(" ALT ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? PSTR(" SFT ") : PSTR("     "), false);


  /* oled_write_P(PSTR("BTMGK"), false); */
  /* static const char PROGMEM mode_logo[4][4] = { */
  /*   {0x95,0x96,0x0a,0}, */
  /*   {0xb5,0xb6,0x0a,0}, */
  /*   {0x97,0x98,0x0a,0}, */
  /*   {0xb7,0xb8,0x0a,0} }; */

  /* if (keymap_config.swap_lalt_lgui != false) { */
    /* oled_write_P(mode_logo[0], false); */
    /* oled_write_P(mode_logo[1], false); */
  /* } else { */
    /* oled_write_P(mode_logo[2], false); */
    /* oled_write_P(mode_logo[3], false); */
  /* } */

  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(PSTR("Lock:"), false);
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);
}


char chain_str[8] = {};
/* void set_chain_str() { */
/*   // update keylog */
/*   snprintf(chain_str, sizeof(chain_str), "%d", press_state_get()) */

/*   // update keylogs */
/*   /\* if (keylogs_str_idx == sizeof(keylogs_str) - 1) { *\/ */
/*   /\*   keylogs_str_idx = 0; *\/ */
/*   /\*   for (int i = 0; i < sizeof(keylogs_str) - 1; i++) { *\/ */
/*   /\*     keylogs_str[i] = ' '; *\/ */
/*   /\*   } *\/ */
/*   /\* } *\/ */

/*   /\* keylogs_str[keylogs_str_idx] = name; *\/ */
/*   /\* keylogs_str_idx++; *\/ */
/* } */

void oled_task_user(void) {
  if (is_master) {
    render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {

    /* snprintf(chain_str, sizeof(chain_str), "%d", press_state_get()); */
    /* oled_write_P(PSTR(chain_str), false); */
    /* press_state_str[0] = '6'; */
    /* press_state_str[1] = '5'; */
    /* press_state_str[3] = '0'; */

    //uint16_t current_press_state = press_state_get();

  oled_write_P(PSTR("Seq: "), false);
  uint8_t l = keyseq_index_get();
  for (int8_t i = 0; i < l; i++) {
    /* uint16_t keycode = press_state_get_press(i).keycode  ; */
    
    uint16_t* keyseq_keycodes = keyseq_codes_get();
    /* uint16_t keycode = keymap_key_to_keycode(_QWERTY, keyseq_keycodes[i]); */
    uint16_t keycode = keyseq_keycodes[i];

    if (keycode < 60) {
      oled_write_P(PSTR("  "), false);
      oled_write_char(press_state_to_name[keycode], false);
      oled_write_ln("", false);
    } else {
      switch (keycode) {
      case LD_RAISE:
        oled_write_P(PSTR("RAISE"), false);
        /* oled_write_ln("RAISE", false); */
        break;
      case LD_LOWER:
        oled_write_P(PSTR("LOWER"), false);
        /* oled_write_ln("LOWER", false); */
        break;
      default:
        oled_write_char('G',  false);
        oled_write_ln("", false);
        break;
      }
    }
  }

  for (int8_t i = l; i < 6; i++) {
        oled_write_P(PSTR("     "), false);
  }

  oled_write_P(PSTR("Press"), false);
  oled_write_P(PSTR("     "), false);
  uint16_t press_state  = press_state_get();
  press_t* presses =  presses_get();
  for (int8_t i = 0; i < LD_PRESS_MAX; i ++) {
    if (press_state & (1U << i)) {
      uint16_t keycode = keymap_key_to_keycode(_QWERTY, presses[i].key);
      if (keycode < 60) {
        /* oled_write_P(PSTR("  "), false); */
        oled_write_char(press_state_to_name[keycode], false);
        /* oled_write_ln("", false); */
      } else {
        switch (keycode) {
        case LD_RAISE:
          oled_write_P(PSTR("r"), false);
          break;
        case LD_LOWER:
          oled_write_P(PSTR("l"), false);
          break;
        default:
          oled_write_P(PSTR("u"), false);
          break;
        }
      }
      continue ;
    } else {
        oled_write_P(PSTR(" "), false);
        continue ;
    }
  }

  /* for (int8_t i = l; i <= sizeof(press_state_str); i++) { */
  /*     press_state_str[i] = ' '; */
  /* } */
    /* oled_write_ln(press_state_str, false); */
    /* oled_write_ln("qwe", false); */
    /* oled_write_ln("qwe", true); */
    //oled_write_P(PSTR("asdfasd"), false);
    
    //render_crkbd_logo();
    //oled_scroll_left();  // Turns on scrolling
  }
}

#endif

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case ALT_T(KC_A):
      return TAPPING_TERM + 100;
    default:
      return TAPPING_TERM;
  }
}

