#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LEFT,
  _RAISEFUN,
  _RAISE,
  _FUN,
  _SYM,
  _NUM,
  _NUMBERS,
  _ARROWS,
  _MOUSE
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER  _QWERTY

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  /* RIGHT, */
  RAISE,
  FUN,
  MOUSE,
  BACKLIT,
  LD_SYMBOLS, 
  LD_RAISE, 
  
  SEQ_SYMBOLS,
  SEQ_RAISE,
  SEQ_IE,
  SEQ_ID,
  SEQ_IC,
  SEQ_2LSFT,


  
  LD_SYM_PREFIX_I, 
  LD_ARROWS,
  SEQ_LSFT,
  SEQ_LSFT_O,
  SEQ_OE,
  SEQ_OD,
  SEQ_OC,
  SEQ_SYM_PREFIX_I,
  SEQ_SYM_PREFIX_I_E,
  SEQ_SYM_PREFIX_I_IE,
  SEQ_ARROWS,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"


/* #undef LEADER_TIMEOUT */
/* #define LEADER_TIMEOUT 2000 */
// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALTDEL LCTL(LALT(KC_DEL))

/* #define LEADER_TIMEOUT 300 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  { KC_ESC ,  KC_Q ,    KC_W , KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,     KC_I ,    KC_O ,   KC_P ,    KC_MINS } , 
  { KC_TAB ,  KC_A ,    KC_S , KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,     KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } , 
  { XXXXXXX , KC_Z ,    KC_X , KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,     KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } , 
  { XXXXXXX , KC_RGUI , FUN ,  KC_LGUI , KC_LSFT , KC_LALT , KC_SPC , LD_RAISE , KC_LCTL , RAISE ,  KC_RGUI , KC_ENT }
 } , 
[_RAISE] = { 
  { KC_GRV , KC_1 , KC_2 , KC_3 , KC_4 , KC_5 ,     KC_6 ,    KC_7 ,    KC_8 ,       KC_9 ,    KC_0 ,    _______ } , 
  { _______ ,   KC_LBRC , KC_RBRC , LD_ARROWS , XXXXXXX , KC_BSPC , KC_EQL ,  KC_ENT ,  LD_SYMBOLS , _______ , _______ , _______ } , 
  { KC_TILD ,   KC_EXLM , KC_AT ,   KC_HASH ,   KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR ,    _______ , _______ , _______ } , 
  { CALTDEL ,   KC_DEL ,  _______ , _______ ,   _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ }
 } ,            

/* [_MAIN] = { */
/*   { KC_GRV , KC_1 ,    KC_2 ,    KC_3 ,      KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,       KC_9 ,    KC_0 ,    _______ } ,  */
/*   { _______ , KC_LBRC , KC_RBRC , _______ , LD_OS_TEST , KC_BSPC , KC_EQL ,  KC_ENT ,    LD_OS_SYM , LD_OS_NUM , _______ , _______ } ,  */
/*   { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,     KC_PERC , KC_CIRC , KC_AMPR ,   KC_ASTR ,   _______ ,   _______ , _______ } ,  */
/*   { CALTDEL , KC_DEL ,  _______ , _______ , _______ ,    _______ , KC_SPC ,  LD_MO_SYM , _______ ,   _______ ,   _______ , _______ } */
/*  } ,           */

/* [_FUN] = {  */
/*   { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,   */
/*   { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } ,  */
/*   { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } ,  */
/*   { AG_NORM ,      AG_SWAP ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ } */
/*  } ,                */
[_FUN] = { 
  { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,  
  { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } , 
  { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } , 
  { _______ ,      _______ ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ }
 } ,               

[_SYM] = { 
  { XXXXXXX , KC_GRV ,  KC_QUOT , KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , KC_TILD , KC_DQUO , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
 } ,

[_NUM ] = {
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,   _______  ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______ } ,
  { _______ , KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______ ,    _______ , _______ , _______ , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } ,
[_NUMBERS] = {
  { _______ ,  _______ , _______ , _______ , _______ , _______ , KC_1 ,     KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_BSPC } ,
  { _______ , _______ , _______ , _______ , _______ , KC_BSPC , KC_6 ,     KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  KC_MINS , KC_EQL ,  KC_DOT ,  KC_SLSH , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_SPACE , _______ , _______ , _______ , _______ , _______ }
 } ,

[_ARROWS] = {
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGDN , KC_PGUP , XXXXXXX ,  XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,  XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , _______ , _______ , _______ , _______ , XXXXXXX ,  XXXXXXX , XXXXXXX }
 } ,                 

[_MOUSE] = {
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , _______ } ,
  { _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 }

 };
/* const uint16_t PROGMEM fn_actions[] = { */
/*   [0] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_DEL) // Ctrl+Alt+Delete */
/*  }; */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case RAISE:
      if (record->event.pressed) {
        xprintf("           RAISE ON\r\n");
        layer_on(_RAISE);
      } else {
        xprintf("           RAISE OFF\r\n");
        layer_off(_RAISE);
      }
      return false;
      break;
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
  (uint16_t[]){5, LD_SYMBOLS, KC_I, KC_E, SEQ_IE },
  (uint16_t[]){5, LD_SYMBOLS, KC_I, KC_D, SEQ_ID },
  (uint16_t[]){5, LD_SYMBOLS, KC_I, KC_C, SEQ_IC },
  (uint16_t[]){4, LD_SYMBOLS, KC_TRNS, SEQ_SYMBOLS },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_E, SEQ_IE },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_D, SEQ_ID },
  (uint16_t[]){6, LD_RAISE, KC_K, KC_I, KC_C, SEQ_IC },
  (uint16_t[]){5, LD_RAISE, KC_K, KC_TRNS, SEQ_SYMBOLS },
  (uint16_t[]){4, LD_RAISE, KC_TRNS, SEQ_RAISE },
  /* (uint16_t[]){3, KC_LSFT, SEQ_LSFT }, */
  /* /\* (uint16_t[]){5, KC_LSFT, KC_LSFT, KC_O,  SEQ_LSFT_O }, *\/ */
  /* (uint16_t[]){4, KC_LSFT, KC_LSFT,  SEQ_2LSFT }, */
  (uint16_t[]){1}
};

void leaders_init_user(void) {
  keyseq_set_definitions(user_definitions);
}

bool keyseq_press_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
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
  case SEQ_IE:
    if (record->event.pressed) {
      SEND_STRING("{}");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_ID:
    if (record->event.pressed) {
      SEND_STRING("()");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_IC:
    if (record->event.pressed) {
      SEND_STRING("[]");
      register_code16(KC_LEFT);
      unregister_code16(KC_LEFT);
      return false;
    } else {
      return false;
    }
  case SEQ_LSFT:
    if (record->event.pressed) {
      keyseq_push(KC_NO);
      keyseq_set_oneshot();
      return true;
    } else {
      return true;
    }
  case SEQ_2LSFT:
    if (record->event.pressed) {
      register_code16(KC_A);
      return false;
    } else {
      unregister_code16(KC_A);
      return false;
    }
  }    
  return false;
}

/*   case SEQ_IE: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("{}"); */
/*       register_code16(KC_LEFT); */
/*       unregister_code16(KC_LEFT); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_OE: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("{}"); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_IIE: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("{}"); */
/*       register_code16(KC_LEFT); */
/*       unregister_code16(KC_LEFT); */
/*       register_code16(KC_ENT); */
/*       unregister_code16(KC_ENT); */
/*       register_code16(KC_ENT); */
/*       unregister_code16(KC_ENT); */
/*       register_code16(KC_UP); */
/*       unregister_code16(KC_UP); */
/*       register_code16(KC_TAB); */
/*       unregister_code16(KC_TAB); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_ID: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("()"); */
/*       register_code16(KC_LEFT); */
/*       unregister_code16(KC_LEFT); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_OD: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("()"); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_IC: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("[]"); */
/*       register_code16(KC_LEFT); */
/*       unregister_code16(KC_LEFT); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_OC: */
/*     if (record->event.pressed) { */
/*       SEND_STRING("[]"); */
/*       return false; */
/*     } else { */
/*       return false; */
/*     } */
/*     break; */
/*   case SEQ_ARROWS: */
/*     if (record->event.pressed) { */
/*       uint16_t kc = keymap_key_to_keycode(_ARROWS, record->event.key); */
/*       register_code16(kc); */
/*       return false; break; */
/*     } else { */
/*       uint16_t kc = keymap_key_to_keycode(_ARROWS, record->event.key); */
/*       unregister_code16(kc); */
/*       return false; break; */
/*     } */
/*     break; */
/*   } */
/*   return false; */

/* } */
#endif
