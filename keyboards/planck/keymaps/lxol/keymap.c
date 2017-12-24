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
  LD_OS_ARROWS,
  LD_LAYER_SYM,
  LD_MO_RAISE,
  LD_MO_SYM,
  LD_OS_MAIN,
  LD_OS_NUM,
  LD_OS_TEST,
  LD_TEST2,
  LD_OS_SYM,
  DYNAMIC_MACRO_RANGE,
};


/* #define LD_LAYER_SYM  (LD_LAYER_FIRST + _SYM) */
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
  { KC_ESC ,        KC_Q ,  KC_W , KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,       KC_I ,    KC_O ,   KC_P ,    KC_MINS } ,
  { KC_TAB ,        KC_A ,  KC_S , KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,       KC_K ,    KC_L ,   KC_SCLN , KC_QUOT } ,
  { LD_OS_TEST , KC_Z ,  KC_X , KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,       KC_COMM , KC_DOT , KC_SLSH , KC_PLUS } ,
  { XXXXXXX ,       MOUSE , FUN ,  KC_LGUI , KC_LSFT , KC_LALT , KC_SPC , RAISE , KC_LCTL , LEFT ,   KC_BSPC , KC_ENT }
 } ,

[_RAISE] = {
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,          KC_4 ,        KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,         KC_9 ,      KC_0 ,    _______ } ,
  { _______ , KC_LBRC , KC_RBRC , LD_OS_TEST , LD_OS_CTL_X , KC_BSPC , KC_EQL ,  KC_ENT ,  LD_LAYER_SYM , LD_OS_NUM , _______ , _______ } ,
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH ,       KC_DLR ,      KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR ,      _______ ,   _______ , _______ } ,
  { CALTDEL , KC_DEL ,  _______ , _______ ,       _______ ,     _______ , _______ , _______ , _______ ,      _______ ,   _______ , _______ }
 } ,

[_MAIN] = {
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,     KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,      KC_9 ,      KC_0 ,    _______ } ,
  { _______ , KC_LBRC , KC_RBRC , _______ , LD_OS_TEST , KC_BSPC , KC_EQL ,  KC_ENT ,  LD_OS_SYM , LD_OS_NUM , _______ , _______ } ,
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,        KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR ,   _______ ,   _______ , _______ } ,
  { CALTDEL , KC_DEL ,  _______ , _______ , _______ ,       _______ , KC_SPC , LD_MO_SYM , _______ ,   _______ ,   _______ , _______ }
 } ,

[_FUN] = {
  { KC_F12 ,  KC_F1 ,   KC_F2 ,   KC_F3 , KC_F4 , KC_F5 , KC_F6 ,    KC_F7 ,   KC_F8 ,   KC_F9 ,    KC_F10 ,  KC_F11 } ,
  { DYN_REC_STOP , DYN_REC_START1 ,  DYN_REC_START2 ,  BACKLIT , BL_DEC ,  BL_INC ,  KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } ,
  { KC_CAPS ,      DYN_MACRO_PLAY1 , DYN_MACRO_PLAY2 , KC_VOLU , KC_VOLD , KC_MPLY , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } ,
  { AG_NORM ,      AG_SWAP ,         _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ }
 } ,

[_SYM] = {
  { XXXXXXX , KC_GRV ,  KC_QUOT , KC_LCBR , KC_RCBR , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
  { XXXXXXX , KC_TILD , KC_DQUO , KC_LPRN , KC_RPRN , KC_BSPC , XXXXXXX , KC_ENT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX } ,
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
  { _______ , _______ , _______ , _______ , _______ , _______ , XXXXXXX ,  KC_EQL , XXXXXXX , XXXXXXX ,  XXXXXXX , KC_BSPC } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_LEFT ,  KC_DOWN , KC_UP ,   KC_RIGHT , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ , _______ ,  _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_SPACE , _______ , _______ , _______ ,  _______ , _______ }
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
    .toggle_layer = true,
    .toggle_layer_number = _SYM,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_TEST2,
    .oneshot = true,
    .toggle_layer = false,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_OS_TEST,
    .oneshot = true,
    .toggle_layer = false,
    .reference_layer = _QWERTY
  },
  (leader_t) {
    .keycode = LD_OS_CTL_X,
    .oneshot = true,
    .toggle_layer = false,
    .reference_layer = _QWERTY
  },
  /* terminator */
  (leader_t) {
    .keycode = KC_NO
  }
};

void leaders_init_user(void) {
  leaders_ref_layer = biton32(default_layer_state);
}

bool process_sequence_user(void) {

  IS_LEADING(LD_OS_TEST) {
    BEGIN_SEQ(1, KC_Y)
      SEND_STRING("It works!");
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_Y)
      SEND_STRING("2 keys works");
    END_SEQ


      if (leaders_seq_match(1, KC_TRNS)) {
        /* ignore key unless it is managed by layer. */
        uint16_t key = keymap_key_to_keycode(leaders_state.layer_num, leaders_state.key_sequence[leaders_state.sequence_size - 1]);
        if (key != KC_NO) {
          leaders_state_clear_sequence();
          leaders_state.oneshot = false;
        }
      }

  }

  IS_LEADING(LD_MO_RAISE) {
    BEGIN_SEQ(1, KC_TRNS)
      LEADERS_SEQ_LAYER(_RAISE)
    END_SEQ
  }

  IS_LEADING(LD_LAYER_SYM) {

    BEGIN_SEQ(2, KC_I, KC_S)
      SEND_STRING("\"\"");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_W)
      SEND_STRING("''");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_Q)
      SEND_STRING("``");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_E)
      SEND_STRING("{}");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ

    BEGIN_SEQ(3, KC_I, KC_I, KC_E)
      SEND_STRING("{}");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
      leaders_register_code(KC_ENT);
      leaders_unregister_code(KC_ENT);
      leaders_register_code(KC_ENT);
      leaders_unregister_code(KC_ENT);
      leaders_register_code(KC_UP);
      leaders_unregister_code(KC_UP);
      leaders_register_code(KC_TAB);
      leaders_unregister_code(KC_TAB);
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_D)
      SEND_STRING("()");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ

    BEGIN_SEQ(2, KC_I, KC_C)
      SEND_STRING("[]");
      leaders_register_code(KC_LEFT);
      leaders_unregister_code(KC_LEFT);
    END_SEQ


      if (leaders_seq_match(1, KC_TRNS)) {
        /* ignore key unless it is managed by layer. */
        uint16_t key = keymap_key_to_keycode(leaders_state.layer_num, leaders_state.key_sequence[leaders_state.sequence_size - 1]);
        if (key != KC_NO) {
          leaders_state_clear_sequence();
          leaders_state.oneshot = false;
        }
      }
    /* BEGIN_SEQ(1, KC_TRNS) */
    /*   LEADERS_SEQ_LAYER(_SYM) */
    /* END_SEQ */
      //TODO: optional to ignore wrong presses
    /* leaders_state.sequence_size--; */
  }

  IS_LEADING(LD_OS_NUM) {
    BEGIN_SEQ(1, KC_TRNS)
      LEADERS_SEQ_LAYER(_NUM)
    END_SEQ
  }

  IS_LEADING(LD_OS_MAIN) {
    BEGIN_SEQ(1, KC_TRNS)
      LEADERS_SEQ_LAYER(_MAIN)
    END_SEQ
  }

  IS_LEADING(LD_OS_CTL_X) {
    BEGIN_SEQ(1, KC_J)
      leaders_register_code(KC_LCTL);
      leaders_register_code(KC_X);
      leaders_unregister_code(KC_X);
      leaders_unregister_code(KC_LCTL);
      leaders_register_code(KC_1);
      leaders_unregister_code(KC_1);
    END_SEQ

    BEGIN_SEQ(1, KC_K)
      leaders_register_code(KC_LCTL);
      leaders_register_code(KC_X);
      leaders_unregister_code(KC_X);
      leaders_unregister_code(KC_LCTL);
      leaders_register_code(KC_2);
      leaders_unregister_code(KC_2);
    END_SEQ

    BEGIN_SEQ(1, KC_L)
      leaders_register_code(KC_LCTL);
      leaders_register_code(KC_X);
      leaders_unregister_code(KC_X);
      leaders_unregister_code(KC_LCTL);
      leaders_register_code(KC_3);
      leaders_unregister_code(KC_3);
    END_SEQ

    BEGIN_SEQ(1, KC_O)
      leaders_register_code(KC_LCTL);
      leaders_register_code(KC_X);
      leaders_unregister_code(KC_X);
      leaders_unregister_code(KC_LCTL);
      leaders_register_code(KC_O);
      leaders_unregister_code(KC_O);
    END_SEQ

    /* ignore other keys  */
    BEGIN_SEQ(1, KC_TRNS)
      leaders_state_clear_sequence();
      leaders_state.oneshot = false;
    END_SEQ
  }

  /* IS_LEADING(LD_OS_NUM) { */
  /*   LEADERS_SEQ(1, KC_TRNS) */
  /*     SEND_STRING("()"); */
  /*     /\* leaders_send_last(_NUM); *\/ */

  /*     /\* LEADERS_SEQ_LAYER(_NUM) *\/ */
  /*   END_SEQ */
  /* } */

  return false;
}

#endif
