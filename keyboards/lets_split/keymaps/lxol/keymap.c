#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum custom_layers {
  _QWERTY
  ,_LEFT
  ,_RIGHT
  ,_RAISE
  ,_FUN
  ,_MOUSE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE
  ,LEFT
  ,RIGHT
  ,RAISE
  ,FUN
  ,MOUSE
  ,LT_ESC = LT(_RAISE, KC_ESC)
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KEYMAP (                                                  \
  KC_ESC ,  KC_Q ,    KC_W ,    KC_E ,  KC_R ,    KC_T ,    KC_Y ,   KC_U ,  KC_I ,    KC_O ,   KC_P ,    KC_MINS, \
  KC_TAB ,  KC_A ,    KC_S ,    KC_D ,  KC_F ,    KC_G ,    KC_H ,   KC_J ,  KC_K ,    KC_L ,   KC_SCLN , KC_QUOT,\
  LEFT , KC_Z ,    KC_X ,    KC_C ,  KC_V ,    KC_B ,    KC_N ,   KC_M ,  KC_COMM , KC_DOT , KC_SLSH , RIGHT, \
  KC_PLUS ,  MOUSE ,   FUN ,     KC_LGUI , KC_LSFT , KC_LALT , KC_SPC , RAISE , KC_LCTL , KC_DEL, KC_BSPC , KC_ENT \
 ) ,

  [_LEFT] =  KEYMAP (                                                  \
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______  , \
   _______ , _______ , _______ , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE  , \
   _______ , _______ , _______ , _______ , _______ , _______ , KC_NO , LCTL(KC_MINS) , _______ , _______ ,  _______ , _______  , \
   KC_CAPS , BL_DEC ,  BL_INC ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  KC_DEL ,  _______ \
 ) ,
  
  [_RIGHT] =  KEYMAP (                                                  \
   _______ , _______ , _______ , KC_LBRC , KC_RBRC , _______ , _______ , _______ , _______ , _______ ,  _______ , _______  , \
   _______ , _______ , _______ , KC_LCBR , KC_RCBR , _______ , _______ , _______ , _______ , _______ ,  _______ , _______  , \
   _______ , _______ , _______ , KC_LPRN , KC_RPRN , _______ , _______ , _______ , _______ , _______ ,  _______ , _______  , \
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ ,  _______ \
 ) ,

  [_RAISE ] =  KEYMAP (                                                 \
   KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______  ,\
   _______ , KC_LBRC , KC_RBRC , KC_LPRN , KC_RPRN , KC_BSPC , KC_EQL , KC_ENT ,  _______ , _______ , _______ , _______  ,\
   KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , _______ , _______ , _______  ,\
   KC_FN0 ,  KC_DEL ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  \
 ) ,

  [_FUN] =  KEYMAP (                                                    \
   KC_F12   , KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11  ,\
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  ,\
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_VOLU , _______  ,\
   KC_F8 ,   KC_F9 ,   _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_VOLD , KC_MPLY \
 ) ,

  [_MOUSE] =  KEYMAP (                                                  \
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , _______  , \
   _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______  , \
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______  , \
   _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
)

};


const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_MODS_KEY(MOD_LALT | MOD_LCTL, KC_DEL) // Ctrl+Alt+Delete
 };


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LEFT:
      if (record->event.pressed) {
        layer_on(_LEFT);
      } else {
        layer_off(_LEFT);
      }
      return false;
      break;
    case RIGHT:
      if (record->event.pressed) {
        layer_on(_RIGHT);
      } else {
        layer_off(_RIGHT);
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


