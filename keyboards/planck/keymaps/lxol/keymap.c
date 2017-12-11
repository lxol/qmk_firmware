#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"


extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LEFT,
  /* _RIGHT, */
  _RAISEFUN,
  _RAISE,
  _FUN,
  _MOUSE
};

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  /* RIGHT, */
  RAISE,
  FUN,
  MOUSE,
  BACKLIT,
  DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 2000
// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define CALTDEL LCTL(LALT(KC_DEL))

/* #define LEADER_TIMEOUT 300 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  { KC_ESC ,  KC_Q ,  KC_W , KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,  KC_I ,    KC_O ,   KC_P ,    KC_MINS } , 
  { KC_TAB ,  KC_A ,  KC_S , KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,  KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } , 
  { KC_LEAD , KC_Z ,  KC_X , KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,  KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } , 
  { XXXXXXX , MOUSE , FUN ,  KC_LGUI , KC_LSFT , KC_LALT , KC_SPC , RAISE , KC_LCTL , LEFT ,   KC_BSPC , KC_ENT }
 } ,          

[_RAISE ] = { 
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______ } , 
  { _______ , _______ , KC_LBRC , KC_LPRN , KC_LCBR , KC_BSPC , KC_EQL ,  KC_ENT ,  KC_BOSS , _______ , _______ , _______ } , 
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , _______ , _______ , _______ } , 
  { CALTDEL , KC_DEL ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } ,          

[_FUN] = { 
  { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,  
  { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } , 
  { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } , 
  { AG_NORM ,      AG_SWAP ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ }
 } ,               

[_LEFT] = { 
  { _______ ,      _______ ,         _______ ,         KC_LCBR , KC_RCBR , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , KC_LPRN , KC_RPRN , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , KC_LBRC , KC_RBRC , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } 
 } ,          

[_MOUSE] = { 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , _______ } , 
  { _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 }
/* [_LEFT] = { */
/*   { DYN_REC_STOP , DYN_REC_START1 , DYN_REC_START2 , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGDN , KC_PGUP , XXXXXXX ,  _______ , _______ } ,  */
/*   { XXXXXXX ,      BACKLIT ,         XXXXXXX ,         XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } ,  */
/*   { _______ ,      XXXXXXX ,         XXXXXXX ,         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , _______ ,  _______ , _______ } ,  */
/*   { _______ ,      BL_DEC ,          BL_INC ,          _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  KC_DEL ,  _______ } */
/* *  } ,                *\/ */

/* [_RIGHT] = {  */
/*   { _______ , DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_LBRC , KC_RBRC , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,  */
/*   { XXXXXXX , XXXXXXX ,         XXXXXXX ,         KC_LCBR , KC_RCBR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,  */
/*   { _______ , XXXXXXX ,         XXXXXXX ,         KC_LPRN , KC_RPRN , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ } ,  */
/*   { _______ , _______ ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } /\*  *\/ */
/*  } ,           */




 };

/* const uint16_t PROGMEM fn_actions[] = { */
/*   [0] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_DEL) // Ctrl+Alt+Delete */
/*  }; */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  switch (keycode) {
    /* case RAISE: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_RAISE); */
    /*     update_tri_layer(_RAISE, _FUN, _RAISEFUN); */
    /*   } else { */
    /*     layer_off(_RAISE); */
    /*     update_tri_layer(_RAISE, _FUN, _RAISEFUN); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case FUN: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_FUN); */
    /*     update_tri_layer(_RAISE, _FUN, _RAISEFUN); */
    /*   } else { */
    /*     layer_off(_FUN); */
    /*     update_tri_layer(_RAISE, _FUN, _RAISEFUN); */
    /*   } */
    /*   return false; */
    /*   break; */
    case LEFT:
      if (record->event.pressed) {
        layer_on(_LEFT);
      } else {
        layer_off(_LEFT);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
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


LEADER_EXTERNS();
BOSS_EXTERNS();
/* boss_layer = _FUN; */
/* boss_layer = _FU; */
void matrix_scan_user(void) {

  if (bossing) {
   
    SEQ_BOSS_ONE_KEY(KC_E) {
      SEND_STRING("{");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }
    SEQ_BOSS_ONE_KEY(KC_R) {
      SEND_STRING("}");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }

    SEQ_BOSS_ONE_KEY(KC_D) {
      SEND_STRING("(");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }
    SEQ_BOSS_ONE_KEY(KC_F) {
      SEND_STRING(")");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }

    SEQ_BOSS_ONE_KEY(KC_C) {
      SEND_STRING("[");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }
    SEQ_BOSS_ONE_KEY(KC_V) {
      SEND_STRING("]");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }
    SEQ_BOSS_ONE_KEY(KC_S) {
      SEND_STRING("\"");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }

    SEQ_BOSS_ONE_KEY(KC_A) {
      SEND_STRING("'");
      /* bossing = false; */
      boss_sequence_size = 0;
      boss_sequence[0] = 0;
      boss_sequence[1] = 0;
      boss_sequence[2] = 0;
      boss_sequence[3] = 0;
      boss_sequence[4] = 0;
      /* boss_end(); */
    }
  }
  if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT) {
      leading = false;
      leader_end();
  }
  if (leading ) {
  /* LEADER_DICTIONARY() { */
    /* leading = false; */
    /* leader_end(); */

    /* SEQ_ONE_KEY(KC_F) { */
    /*   register_code(KC_S); */
    /*   unregister_code(KC_S); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_ONE_KEY(KC_F) { */
    /*   register_code(KC_LPRN); */
    /*   unregister_code(KC_LPRN); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    SEQ_ONE_KEY(KC_S) {
      SEND_STRING("[]");
      leading = false;
      leader_end();
    }

    SEQ_ONE_KEY(KC_D) {
      SEND_STRING("()");
      leading = false;
      leader_end();
    }

    SEQ_ONE_KEY(KC_F) {
      SEND_STRING("{}");
      leading = false;
      leader_end();
    }

    /* SEQ_TWO_KEYS(KC_D, KC_D) { */
    /*   SEND_STRING("("); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_D, KC_F) { */
    /*   SEND_STRING("()"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_THREE_KEYS(KC_I, KC_D, KC_F) { */
    /*   SEND_STRING("()"); */
    /*   register_code(KC_LEFT); */
    /*   unregister_code(KC_LEFT); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_ONE_KEY(KC_R) { */
    /*   SEND_STRING("}"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_E, KC_E) { */
    /*     SEND_STRING("{"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_E, KC_R) { */
    /*     SEND_STRING("{}"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_THREE_KEYS(KC_I, KC_E, KC_R) { */
    /*   SEND_STRING("{}"); */
    /*   register_code(KC_LEFT); */
    /*   unregister_code(KC_LEFT); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_ONE_KEY(KC_V) { */
    /*   SEND_STRING("]"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_C, KC_C) { */
    /*     SEND_STRING("["); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_C, KC_V) { */
    /*     SEND_STRING("[]"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */
    /* SEQ_THREE_KEYS(KC_I, KC_C, KC_V) { */
    /*   SEND_STRING("[]"); */
    /*   register_code(KC_LEFT); */
    /*   unregister_code(KC_LEFT); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_ONE_KEY(KC_J) { */
    /*   SEND_STRING("'"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_TWO_KEYS(KC_K, KC_J) { */
    /*     SEND_STRING("''"); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */

    /* SEQ_THREE_KEYS(KC_L, KC_K, KC_J) { */
    /*   SEND_STRING("''"); */
    /*   register_code(KC_LEFT); */
    /*   unregister_code(KC_LEFT); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */
    /* SEQ_TWO_KEYS(KC_A, KC_S) { */
    /*   register_code(KC_H); */
    /*   unregister_code(KC_H); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */
    /* SEQ_THREE_KEYS(KC_A, KC_S, KC_D) { */
    /*   register_code(KC_LGUI); */
    /*   register_code(KC_S); */
    /*   unregister_code(KC_S); */
    /*   unregister_code(KC_LGUI); */
    /*   leading = false; */
    /*   leader_end(); */
    /* } */
  }
}
/* void matrix_scan_user(void) { */
/*   LEADER_DICTIONARY() { */
/*     leading = false; */
/*     leader_end(); */

/*     SEQ_ONE_KEY(KC_F) { */
/*       register_code(KC_S); */
/*       unregister_code(KC_S); */
/*     } */
/*     SEQ_ONE_KEY(KC_1) { */
/*       register_code(KC_QUOT); */
/*       unregister_code(KC_QUOT); */
/*     } */
/*     SEQ_TWO_KEYS(KC_RPRN, KC_1) { */
/*       SEND_STRING("''"); */
/*     } */

/*     SEQ_TWO_KEYS(KC_A, KC_S) { */
/*       register_code(KC_H); */
/*       unregister_code(KC_H); */
/*     } */
/*     SEQ_THREE_KEYS(KC_A, KC_S, KC_D) { */
/*       register_code(KC_LGUI); */
/*       register_code(KC_S); */
/*       unregister_code(KC_S); */
/*       unregister_code(KC_LGUI); */
/*     } */
/*   } */
/* } */
