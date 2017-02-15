/*  -*-  eval: (turn-on-orgtbl); -*-
 * lxol HHKB Layout
 */


#include "hhkb.h"
#define PREVENT_STUCK_MODIFIERS

#define _______ KC_TRNS
#define XXXXXXX KC_NO


// layers
enum hhkb_layers {
  BASE,
  HHKB,
  MOUSE,
  _SUBLAYER_LEFT,
  _SUBLAYER_RIGHT,

};


#define CTL_ESC KC_FN1
#define OSL_LEFT KC_FN4
#define OSL_RIGHT KC_FN5
#define MODR_CTL KC_FN6

enum my_keycodes {
  QWERTY = SAFE_RANGE,
  SP_START,
  CAND_FOO
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = KEYMAP(  // layer 0 : default

KC_ESC         ,KC_1        ,KC_2 ,KC_3 ,KC_4 ,KC_5 ,KC_6 ,KC_7 ,KC_8    ,KC_9   ,KC_0           ,KC_MINS        ,KC_EQL        ,KC_BSLS ,KC_GRV , \
ALT_T(KC_TAB)  ,/**/KC_Q        ,KC_W ,KC_E ,KC_R ,KC_T ,KC_Y ,KC_U ,KC_I    ,KC_O   ,KC_P           ,KC_LBRC        ,KC_RBRC       ,KC_BSPC , \
CTL_T(KC_SCLN) ,KC_A        ,KC_S ,KC_D ,KC_F ,KC_G ,KC_H ,KC_J ,KC_K    ,KC_L   ,CTL_ESC      ,KC_QUOT , ALT_T(KC_ENT) , \
//CTL_T(KC_SCLN) ,KC_A        ,KC_S ,KC_D ,KC_F ,KC_G ,KC_H ,KC_J ,KC_K    ,KC_L   ,MY_MOD_R       ,CTL_ESC,ALT_T(KC_ENT) ,
KC_LSFT        ,KC_Z        ,KC_X ,KC_C ,KC_V ,KC_B ,KC_N ,KC_M ,KC_COMM ,KC_DOT ,KC_SLSH        ,KC_RSFT   ,MO(HHKB)      , \
/*             ,*/KC_RALT ,OSL_LEFT/* ,     , */  , KC_SPC /* ,     ,     ,*/      , CAND_FOO ,DEBUG) ,


  [MOUSE] = KEYMAP(

DF(BASE) ,KC_F1 ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12 ,KC_NO ,KC_NO ,\
KC_TAB   ,KC_NO ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_WH_D ,KC_WH_U ,KC_RGHT ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO ,\
KC_LCTL  ,KC_NO ,KC_ACL0 ,KC_ACL1 ,KC_ACL2 ,KC_NO   ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,KC_BTN1 ,KC_NO   ,KC_ENT ,\
KC_LSFT  ,KC_NO ,KC_NO   ,KC_NO   ,KC_NO   ,KC_BTN3 ,KC_BTN2 ,KC_BTN1 ,KC_BTN3 ,KC_BTN2 ,KC_NO   ,KC_RSFT ,KC_NO  ,\
KC_NO    ,KC_NO ,KC_TRNS ,KC_NO   ,KC_NO),


  [HHKB] = KEYMAP(

KC_PWR  ,KC_F1         ,KC_F2   ,KC_F3   ,KC_F4    ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_INS  ,KC_DEL ,\
KC_CAPS ,KC_TRNS ,UC(0x03BB) ,KC_TRNS ,KC_TRNS  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_UP   ,KC_TRNS ,KC_BSPC , \
KC_TRNS ,KC_VOLD       ,KC_VOLU ,KC_MUTE ,KC_TRNS  ,KC_TRNS ,KC_PAST ,KC_PSLS ,KC_HOME ,KC_PGUP ,KC_LEFT ,KC_RGHT ,KC_PENT ,\
KC_LSFT ,KC_TRNS       ,KC_TRNS ,KC_TRNS ,KC_TRNS  ,KC_TRNS ,KC_PPLS ,KC_PMNS ,KC_END  ,KC_PGDN ,KC_DOWN ,KC_RSFT ,KC_TRNS , \
KC_TRNS ,KC_TRNS       ,KC_TRNS ,KC_TRNS ,KC_TRNS),

    [_SUBLAYER_LEFT] = KEYMAP(
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,\
KC_NO   ,KC_NO   ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______   ,_______ ,_______  ,_______  ,_______  ,\
_______  ,_______  ,KC_LSFT  ,KC_LALT  ,KC_LCTL  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,\
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,\
_______  ,_______  ,_______  ,_______  ,_______ ),

    [_SUBLAYER_RIGHT] = KEYMAP(
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,\
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,KC_NO   ,KC_NO   ,\
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,KC_LCTL  ,KC_LALT  ,KC_LSFT ,_______  ,_______  ,_______  ,\
_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______  ,\
_______  ,_______  ,_______  ,_______  ,_______ )

};


const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT),      // RControl with tap Enter*
  [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ESC),
  [3] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_SCLN)
};


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    debug_enable = true;
    set_unicode_input_mode(UC_LNX);
    //sublayer_left = _SUBLAYER_LEFT;
    //sublayer_right = _SUBLAYER_RIGHT;
}


/* bool leftp(keypos_t key) { */
/*   dprintf("col: %d row: %d\n", key.col, key.row); */

/*   if ( */
/*       (key.row > 3) || */
/*       //(key.row == 2 && key.col == 1) || # KC_6 left for me */
/*       (key.row == 2 && key.col == 2) || */
/*       (key.row == 2 && key.col == 5) || */
/*       (key.row == 2 && key.col == 6)  */
/*       ) { */
/*     dprintln("right"); */
/*     return false; */
/*   }  else { */
/*     dprintln("left"); */
/*     dprintf("number of keys: %d\n",  matrix_key_count()); */
/*     return true; */
/*   } */
/* } */

/* enum split_states { */
/*   SP_STATE_NO, */
/*   SP_STATE_INIT, */
/*   SP_STATE_LEFT, */
/*   SP_STATE_RIGHT */
/* }; */

/* split_state = SP_STATE_NO; */




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* if (split_state == SP_STATE_INIT) { */
  /*   if (leftp(record->event.key)) { */
  /*     split_state = SP_STATE_LEFT; */
  /*   } else { */
  /*     split_state = SP_STATE_RIGHT; */
  /*   } */
  /* } */

  switch (keycode) {
  case DEBUG:
    if (record->event.pressed) {
      //process_tmp_layer_on_release(record);
    }
    return true;
    break;

  case CAND_FOO:
    if (record->event.pressed) {
        dprintf("sublayers sets\n");
        set_candidate(_SUBLAYER_RIGHT, record->event.key);
        set_candidate(_SUBLAYER_LEFT, record->event.key);
    }
    return true;
    break;
  }

  //sh  bool is_left = leftp(record->event.key);
  return true;
}


void startup_user()
{

}

void shutdown_user()
{

}
