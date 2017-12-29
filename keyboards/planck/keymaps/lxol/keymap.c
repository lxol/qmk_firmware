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
  _MAIN,
  _FUN,
  _SYM,
  _NUM,
  _NUMBERS,
  _ARROWS,
  _MOUSE
};

#undef LEADERS_REFERENCE_LAYER
#define LEADERS_REFERENCE_LAYER = _QUERTY

enum planck_keycodes {
  LEFT = SAFE_RANGE,
  /* RIGHT, */
  RAISE,
  FUN,
  MOUSE,
  BACKLIT,
  LD_OS_CTL_X,
  LD_ARROWS,
  LD_LAYER_SYM,
  LD_MO_RAISE,
  LD_MO_SYM,
  LD_OS_MAIN,
  LD_OS_NUM,
  LD_OS_TEST,
  LD_TEST2,
  LD_OS_SYM,
  LD_EMACS_SUPER,
  LD_EMACS_HYPER,
  LD_SUPER,
  LD_ARROWS1,
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
  { KC_ESC ,   KC_Q ,  KC_W , KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,  KC_I ,    KC_O ,   KC_P ,    KC_MINS } , 
  { KC_TAB ,   KC_A ,  KC_S , KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,  KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } , 
  { LD_SUPER , KC_Z ,  KC_X , KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,  KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } , 
  { XXXXXXX ,  MOUSE , FUN ,  KC_LGUI , KC_LSFT , KC_LALT , KC_SPC , RAISE , KC_LCTL , LEFT ,   KC_BSPC , KC_ENT }
 } ,           

[_RAISE] = { 
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,      KC_4 ,           KC_5 ,           KC_6 ,    KC_7 ,    KC_8 ,         KC_9 ,     KC_0 ,    _______ } ,        
  { _______ , KC_LBRC , KC_RBRC , LD_ARROWS , LD_OS_CTL_X ,    KC_BSPC ,        KC_EQL ,  KC_ENT ,  LD_LAYER_SYM , _______ , _______ , _______ } , 
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH ,   KC_DLR ,         KC_PERC ,        KC_CIRC , KC_AMPR , KC_ASTR ,      _______ ,  _______ , _______ } ,        
  { CALTDEL , KC_DEL ,  _______ , _______ ,   _______ , _______ , _______ , _______ , _______ ,      _______ ,  _______ , _______ }
 } ,          

[_MAIN] = { 
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,      KC_4 ,           KC_5 ,           KC_6 ,    KC_7 ,    KC_8 ,      KC_9 ,      KC_0 ,    _______ } , 
  { _______ , KC_LBRC , KC_RBRC , _______ , LD_OS_TEST , KC_BSPC , KC_EQL ,  KC_ENT ,    LD_OS_SYM , LD_OS_NUM , _______ , _______ } , 
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,     KC_PERC , KC_CIRC , KC_AMPR ,   KC_ASTR ,   _______ ,   _______ , _______ } , 
  { CALTDEL , KC_DEL ,  _______ , _______ , _______ ,    _______ , KC_SPC ,  LD_MO_SYM , _______ ,   _______ ,   _______ , _______ }
 } ,          

[_FUN] = { 
  { KC_F12 ,       KC_F1 ,           KC_F2 ,           KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,  
  { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } , 
  { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } , 
  { AG_NORM ,      AG_SWAP ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ }
 } ,               

[_SYM] = { 
  { XXXXXXX , KC_GRV ,  KC_QUOT , KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , KC_TILD , KC_DQUO , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT ,  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , KC_LBRC , KC_RBRC , KC_PIPE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } , 
  { XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_TRNS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX }
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
    /* case LEFT: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_LEFT); */
    /*   } else { */
    /*     layer_off(_LEFT); */
    /*   } */
    /*   return false; */
    /*   break; */
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

LEADERS_EXTERNS();
leader_t leaders[] = {
  (leader_t) {
    .keycode = LD_LAYER_SYM,
    .oneshot = true,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_ARROWS,
    .oneshot = false,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_EMACS_HYPER,
    .oneshot = true,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_EMACS_SUPER,
    .oneshot = true,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_OS_CTL_X,
    .oneshot = true,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_SUPER,
    .oneshot = false,
    .reference_layer = _QWERTY
  },
  /* terminator */
  (leader_t) {
    .keycode = KC_NO
  }
};

void leaders_init_user(void) {
  /* leaders_ref_layer = biton32(default_layer_state); */
}

bool process_leader_press_user(void) {
  if (ld_leader_eq(LD_SUPER)) {
    register_code16(KC_LGUI);
  }
  if (ld_leader_eq(LD_ARROWS)) {
    layer_on(_ARROWS);
  }
  return false;
}

bool process_leader_release_user(void) {
  if (ld_leader_eq(LD_SUPER)) {
    unregister_code16(KC_LGUI);
  }

  if (ld_leader_eq(LD_ARROWS)) {
    layer_off(_ARROWS);
  }
  
  return false;
}

bool process_sequence_release_user(void) {
  if (ld_leader_eq(LD_SUPER)) {
    return true;
  }

  if (ld_leader_eq(LD_ARROWS)) {
    return true;
  }

  if (ld_leader_eq(LD_EMACS_SUPER)) {
    return true;
  }

  if (ld_leader_eq(LD_EMACS_HYPER)) {
    return true;
  }
  
  return false;
}

bool process_sequence_press_user(void) {
  /* Emacs translates "C-x @ s" to super */
  if (is_leading(LD_EMACS_SUPER)) {
    register_code16(KC_LCTL);
    register_code16(KC_X);
    unregister_code16(KC_X);
    unregister_code16(KC_LCTL);
    register_code16(KC_AT);
    unregister_code16(KC_AT);
    register_code16(KC_S);
    unregister_code16(KC_S);
    leaders_state.sequence_size = 0;
    ld_remove_current_leader_oneshot();
    return true;
  }

  if (is_leading(LD_EMACS_HYPER)) {
    register_code16(KC_LCTL);
    register_code16(KC_X);
    unregister_code16(KC_X);
    unregister_code16(KC_LCTL);
    register_code16(KC_AT);
    unregister_code16(KC_AT);
    register_code16(KC_H);
    unregister_code16(KC_H);
    leaders_state.sequence_size = 0;
    ld_remove_current_leader_oneshot();
    return true;
  }
  
  if (is_leading(LD_SUPER)) {
    leaders_state.sequence_size = 0;
    return true;
  }

  if (is_leading(LD_ARROWS)) {
    leaders_state.sequence_size = 0;
    return true;
  }


  if (is_leading(LD_MO_RAISE)) {
    if (peq(1, KC_TRNS)) {
      LEADERS_SEQ_LAYER(_RAISE)
        leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }
  }

  if (is_leading(LD_LAYER_SYM)) {

    if (peq(1, KC_I)) {
      if (peq(2, KC_S)) {
        SEND_STRING("\"\"");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2, KC_O)) {
        SEND_STRING("works11!");
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2, KC_W)) {
        SEND_STRING("''");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2, KC_W)) {
        SEND_STRING("``");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2, KC_E)) {
        SEND_STRING("{}");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2, KC_D)) {
        SEND_STRING("()");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }

      if (peq(2, KC_C)) {
        SEND_STRING("[]");
        register_code16(KC_LEFT);
        unregister_code16(KC_LEFT);
        leaders_state.sequence_size = 0;
        ld_remove_current_leader_oneshot();
        return false;                 
      }
      if (peq(2,  KC_I)) {
        if (peq(3,  KC_E)) {
          SEND_STRING("{}");
          register_code16(KC_LEFT);
          unregister_code16(KC_LEFT);
          register_code16(KC_ENT);
          unregister_code16(KC_ENT);
          register_code16(KC_ENT);
          unregister_code16(KC_ENT);
          register_code16(KC_UP);
          unregister_code16(KC_UP);
          register_code16(KC_TAB);
          unregister_code16(KC_TAB);
          leaders_state.sequence_size = 0;
          ld_remove_current_leader_oneshot();
          return false;                 
        }
      }
    }

    if (peq(1,  KC_TRNS)) {
      LEADERS_SEQ_LAYER(_SYM)
        leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }
  }

  if (is_leading(LD_OS_NUM)) {
    if (peq(1,  KC_TRNS)) {
      LEADERS_SEQ_LAYER(_NUM)
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }
  }


  if (is_leading(LD_OS_CTL_X)) {
    if (peq(1,  KC_J)) {
      register_code16(KC_LCTL);
      register_code16(KC_X);
      unregister_code16(KC_X);
      unregister_code16(KC_LCTL);
      register_code16(KC_1);
      unregister_code16(KC_1);
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }

    if (peq(1,  KC_K)) {
      register_code16(KC_LCTL);
      register_code16(KC_X);
      unregister_code16(KC_X);
      unregister_code16(KC_LCTL);
      register_code16(KC_2);
      unregister_code16(KC_2);
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }

    if (peq(1,  KC_L)) {
      register_code16(KC_LCTL);
      register_code16(KC_X);
      unregister_code16(KC_X);
      unregister_code16(KC_LCTL);
      register_code16(KC_3);
      unregister_code16(KC_3);
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }

    if (peq(1,  KC_O)) {
      register_code16(KC_LCTL);
      register_code16(KC_X);
      unregister_code16(KC_X);
      unregister_code16(KC_LCTL);
      register_code16(KC_O);
      unregister_code16(KC_O);
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }

    /* ignore other keys  */
    if (peq(1,  KC_TRNS)) {
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      leaders_state.sequence_size = 0;
      ld_remove_current_leader_oneshot();
      return false;                 
    }
  }

  return false;
}

#endif
