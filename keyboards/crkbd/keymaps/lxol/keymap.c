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
  SEQ_SFT_ALT,
  SEQ_SFT_ALT_CTL,
  SEQ_TMUX1,
  SEQ_TMUX2,
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
  KC_ESC ,   KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,             KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS, \
  KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,             KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT, \
  LD_LOWER , KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,             KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS, \
                                    LD_LOWER ,   KC_LSFT, KC_LALT ,   KC_SPC , LD_RAISE ,   KC_LCTL  \
   ),\
[_RAISE] = LAYOUT( \
  KC_GRV ,                      KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    XXXXXXX , \
  XXXXXXX ,                     SEQ_CTLALT , SEQ_SFT_ALT , XXXXXXX , XXXXXXX , KC_BSPC ,  KC_ENT ,  XXXXXXX , SEQ_SFT_ALT , SEQ_CTLALT, XXXXXXX , \
  KC_TILD ,                     KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_RCTL , KC_RALT , KC_RSFT , KC_RGUI , XXXXXXX , \
                      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
  ) ,                           \
[_DOUBLERAISE] = LAYOUT( \
  XXXXXXX ,  KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS  ,\
  KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT  ,\
  XXXXXXX ,  KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS  ,\
   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
                         ), \
[_LOWER] = LAYOUT( \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LPRN , KC_LBRC , KC_RBRC , KC_RPRN ,  KC_EQL ,  KC_PLUS  , \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ESC , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_PIPE ,  XXXXXXX   , \
  XXXXXXX , KC_LGUI , KC_LSFT , KC_LALT , KC_LCTL , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX ,  XXXXXXX  , \
  XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC ,  XXXXXXX , XXXXXXX \
),\
[_FUN] = LAYOUT( \
   KC_F12 ,          KC_F1 ,          KC_F2 ,          KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,  \
   KC_F12 ,          KC_F1 ,          KC_F2 ,          KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,  \
   XXXXXXX ,         XXXXXXX ,        XXXXXXX ,        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , \
           XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  \
 ) ,                  \
[_SYM] = LAYOUT(\
   XXXXXXX , KC_MINS , KC_PLUS ,  KC_LPRN , KC_RPRN , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , KC_LEFT , KC_RIGHT , KC_LCBR , KC_RCBR , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , KC_UNDS ,  KC_EQL ,  KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX \
 )
};

#ifdef LEADERS_ENABLE

uint16_t* user_definitions[]  = {
  /* (uint16_t[]){4, LD_RAISE, KC_SCLN, SEQ_VIM_CLI }, */
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_E, SEQ_PRNPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_D, SEQ_CBRCPAIR },
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
  (uint16_t[]){5, LD_LOWER, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){4, LD_LOWER, LD_LOWER, SEQ_DOUBLELOWER },
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
      switch (kc) {
      case SEQ_CTLALT:
        register_code16(KC_LCTL);
        register_code16(KC_LALT);
        return false;
      case SEQ_SFT_ALT:
        register_code16(KC_LALT);
        register_code16(KC_LSFT);
        return false;
      case KC_NO:
        return false;
      default:   
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_RAISE, record->event.key);
      switch (kc) {
      case SEQ_CTLALT:
        unregister_code16(KC_LALT);
        unregister_code16(KC_LCTL);
        return false;
      case SEQ_SFT_ALT:
        unregister_code16(KC_LSFT);
        unregister_code16(KC_LALT);
        return false;
      case KC_NO:
        return false;
      default:   
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
      //uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      /* if (kc != KC_NO ) { */
      register_code16(KC_RGUI);
        // register_code16(kc);
      /* } */
      return false ;
    } else {
      //uint16_t kc = keymap_key_to_keycode(_QWERTY, record->event.key);
      /* if (kc != KC_NO) { */
        //unregister_code16(kc);
      unregister_code16(KC_RGUI);
      /* } */
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
  case SEQ_CTLALT:
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
  }
  return false;
}

#endif


void matrix_init_keymap(void) {
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

#ifdef SSD1306OLED

const char *read_logo(void);
char modifier_state_str[24];
char host_led_state_str[24];


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


/* void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) { */
/*   if (memcmp(dest->display, source->display, sizeof(dest->display))) { */
/*     memcpy(dest->display, source->display, sizeof(dest->display)); */
/*     dest->dirty = true; */
/*   } */
/* } */

const char press_state_to_name[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};
#endif


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_270;
  }
}


void render_status(void) {

  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();

  oled_write_P(PSTR("Mods:"), false);
  oled_write_P( (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL ) ? PSTR(" CTL ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI  ) ? PSTR(" GUI ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT  ) ? PSTR(" ALT ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? PSTR(" SFT ") : PSTR("     "), false);


  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(PSTR("Lock:"), false);
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);
}



void oled_task_user(void) {
  if (is_master) {
    render_status();
  } else {

  oled_write_P(PSTR("Seq: "), false);
  uint8_t l = keyseq_index_get();
  for (int8_t i = 0; i < l; i++) {

    uint16_t* keyseq_keycodes = keyseq_codes_get();
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

  }
}

#endif
