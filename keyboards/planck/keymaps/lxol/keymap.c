#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LEFT,
  _RAISE,
  _LOWER,
  _DOUBLERAISE,
  _DOUBLELOWER,
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

  SEQ_SYMBOLS,
  SEQ_RAISE,
  SEQ_LOWER,
  SEQ_PAIRS,
  SEQ_DOUBLERAISE,
  SEQ_FUN,
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
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALTDEL LCTL(LALT(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  { KC_ESC ,   KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS } ,
  { KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } ,
  { LD_LOWER , KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } ,
  { FUN ,      KC_LGUI , KC_RGUI,  LD_LOWER , KC_LSFT , KC_LALT , KC_SPC , LD_RAISE , KC_LCTL , KC_DEL , KC_RGUI , KC_ENT }
 } ,

[_RAISE] = {
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    XXXXXXX } ,
  { XXXXXXX , KC_GRV , KC_ESC ,   KC_ESC,   KC_ESC,   KC_BSPC , KC_EQL ,  KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { CALTDEL , KC_DEL ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

[_DOUBLERAISE] = {
  { XXXXXXX ,  KC_Q ,    KC_W ,    KC_E ,     KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS } ,
  { KC_TAB ,   KC_A ,    KC_S ,    KC_D ,     KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } ,
  { XXXXXXX ,  KC_Z ,    KC_X ,    KC_C ,     KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } ,
  { XXXXXXX ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

[_LOWER] = {
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN ,  KC_UNDS } ,
  { XXXXXXX , KC_TILD , KC_ESC , KC_ESC , KC_ESC , KC_BSPC , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_COLON , KC_DQT } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LCBR , KC_LBRC , KC_RBRC , KC_RCBR ,  KC_BSLS , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC ,  XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX }
 } ,

/* [_DOUBLELOWER] = { */
/*   { XXXXXXX , KC_Q ,    KC_W ,    KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,    KC_I ,    KC_O ,    KC_P ,    KC_MINS } , */
/*   { KC_TAB ,  KC_A ,    KC_S ,    KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,    KC_K ,    KC_L ,    KC_SCLN , KC_QUOT } , */
/*   { XXXXXXX , KC_Z ,    KC_X ,    KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,    KC_COMM , KC_DOT ,  KC_SLSH , KC_PLUS } , */
/*   { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } */
/*  } , */

[_FUN] = {
  { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,
  { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX },
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

  /* { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } , */
  /* { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } , */
  /* { _______ ,      _______ ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ } */

[_PAIRS] = {
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_I ,    KC_LPRN , KC_RPRN , KC_PIPE } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LCBR , KC_RCBR , KC_BSLS } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LBRC , KC_RBRC , KC_EQL } ,
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

[_SYM] = {
  { XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , KC_LEFT , KC_RIGHT , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX ,  KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

[_MODIFIER] = {
  { XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , SEQ_GUIALT , SEQ_CTLGUI , SEQ_CTLALT , XXXXXXX , XXXXXXX , SEQ_CTLALT , SEQ_CTLGUI , SEQ_GUIALT , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX } ,
  { XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX , XXXXXXX ,    XXXXXXX ,    XXXXXXX ,    XXXXXXX , XXXXXXX }
 } ,

[_MOUSE] = {
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , _______ } ,
  { _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 }

 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  switch (keycode) {
    /* case RAISE: */
    /*   if (record->event.pressed) { */
    /*     xprintf("           RAISE ON\r\n"); */
    /*     layer_on(_RAISE); */
    /*   } else { */
    /*     xprintf("           RAISE OFF\r\n"); */
    /*     layer_off(_RAISE); */
    /*   } */
    /*   return false; */
    /*   break; */
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
      } else {
        layer_off(_MOUSE);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case FUN:
      if (record->event.pressed) {
        layer_on(_FUN);
      } else {
        layer_off(_FUN);
      }
      return false;
      break;
  }
  return true;
}


#ifdef LEADERS_ENABLE

uint16_t* user_definitions[]  = {
  (uint16_t[]){4, LD_RAISE, KC_SCLN, SEQ_VIM_CLI },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_E, SEQ_CBRCPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_D, SEQ_PRNPAIR },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_C, SEQ_BRCPAIR },
  /* (uint16_t[]){5, LD_RAISE, KC_F, KC_TRNS, SEQ_DOUBLERAISE }, */
  /* (uint16_t[]){5, LD_RAISE, KC_D, KC_TRNS, SEQ_DOUBLERAISE }, */
  (uint16_t[]){5, LD_RAISE, KC_K, KC_TRNS, SEQ_SYMBOLS },
  /* (uint16_t[]){6, LD_RAISE, LD_RAISE, KC_LSFT, KC_K, SEQ_EXPAND }, */
  /* (uint16_t[]){6, LD_RAISE, LD_RAISE, KC_LSFT, KC_J, SEQ_CONTRACT }, */
  (uint16_t[]){5, LD_RAISE, KC_SPC, KC_TRNS, SEQ_FUN },
  (uint16_t[]){5, LD_RAISE, LD_RAISE, KC_TRNS, SEQ_DOUBLERAISE },
  /* (uint16_t[]){5, LD_RAISE, LD_LOWER, KC_TRNS, SEQ_LOWER }, */
  /* (uint16_t[]){5, LD_RAISE, KC_L, KC_TRNS, SEQ_MODIFIERS }, */
  (uint16_t[]){4, LD_RAISE, KC_TRNS, SEQ_RAISE },
  /* (uint16_t[]){5, LD_LOWER, LD_LOWER, KC_TRNS, SEQ_DOUBLELOWER }, */
  (uint16_t[]){5, LD_LOWER, LD_RAISE, KC_TRNS, SEQ_RAISE },
  (uint16_t[]){4, LD_LOWER, KC_TRNS, SEQ_LOWER },
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
  case SEQ_DOUBLELOWER:
    if (record->event.pressed) {
      uint16_t kc = keymap_key_to_keycode(_DOUBLELOWER, record->event.key);
      if (kc != KC_NO ) {
        register_code16(KC_RGUI);
        register_code16(kc);
      }
      return false ;
    } else {
      uint16_t kc = keymap_key_to_keycode(_DOUBLELOWER, record->event.key);
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
