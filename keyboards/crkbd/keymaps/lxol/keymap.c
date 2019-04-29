#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

/* enum lxol_layers { */
/*   _QWERTY, */
/*   _LEFT, */
/*   _RAISE, */
/*   _LOWER, */
/*   _DEEP, */
/*   _DOUBLERAISE, */
/*   _DOUBLELOWER, */
/*   _FUN, */
/*   _PAIRS, */
/*   _TMUX, */
/*   _SYM, */
/*   _MODIFIER, */
/*   _MOUSE */
/* }; */


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
[_SYM] = LAYOUT(\
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , KC_LEFT , KC_RIGHT , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
   XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,\
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX \
 ) 
};

int RGB_current_mode;

/* void persistent_default_layer_set(uint16_t default_layer) { */
/*   eeconfig_update_default_layer(default_layer); */
/*   default_layer_set(default_layer); */
/* } */

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
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
#endif//SSD1306OLED

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*   if (record->event.pressed) { */
/* #ifdef SSD1306OLED */
/*     set_keylog(keycode, record); */
/* #endif */
/*     // set_timelog(); */
/*   } */

/*   switch (keycode) { */
/*     case QWERTY: */
/*       if (record->event.pressed) { */
/*         persistent_default_layer_set(1UL<<_QWERTY); */
/*       } */
/*       return false; */
/*       break; */
/*     case LOWER: */
/*       if (record->event.pressed) { */
/*         layer_on(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case RAISE: */
/*       if (record->event.pressed) { */
/*         layer_on(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case ADJUST: */
/*         if (record->event.pressed) { */
/*           layer_on(_ADJUST); */
/*         } else { */
/*           layer_off(_ADJUST); */
/*         } */
/*         return false; */
/*         break; */
/*     case RGB_MOD: */
/*       #ifdef RGBLIGHT_ENABLE */
/*         if (record->event.pressed) { */
/*           rgblight_mode(RGB_current_mode); */
/*           rgblight_step(); */
/*           RGB_current_mode = rgblight_config.mode; */
/*         } */
/*       #endif */
/*       return false; */
/*       break; */
/*     case RGBRST: */
/*       #ifdef RGBLIGHT_ENABLE */
/*         if (record->event.pressed) { */
/*           eeconfig_update_rgblight_default(); */
/*           rgblight_enable(); */
/*           RGB_current_mode = rgblight_config.mode; */
/*         } */
/*       #endif */
/*       break; */
/*   } */
/*   return true; */
/* } */

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
