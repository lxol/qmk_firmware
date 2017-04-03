#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSE,
  _LEFT
};

enum planck_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  MOUSE,
  LEFT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  { KC_ESC ,  KC_Q ,    KC_W ,    KC_E ,    KC_R ,    KC_T ,    KC_Y ,   KC_U ,  KC_I ,    KC_O ,    KC_P ,    KC_MINS } , 
  { KC_TAB ,  KC_A ,    KC_S ,    KC_D ,    KC_F ,    KC_G ,    KC_H ,   KC_J ,  KC_K ,    KC_L ,    KC_SCLN , KC_QUOT } , 
  { LEFT ,    KC_Z ,    KC_X ,    KC_C ,    KC_V ,    KC_B ,    KC_N ,   KC_M ,  KC_COMM , KC_DOT ,  KC_SLSH , KC_EQL } ,  
  { KC_F24 ,  MOUSE ,   LOWER ,   LOWER ,   KC_LSFT , KC_LGUI , KC_SPC , RAISE , KC_LCTL , KC_LCTL , KC_BSPC , KC_ENT }
 } ,          

[_LOWER] = { 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_PGDN , KC_PGUP , _______ ,  _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP ,   KC_RIGHT , KC_BSLS , KC_PIPE } , 
  { KC_F1 ,   KC_F2 ,   KC_F3 ,   KC_F4 ,   KC_F5 ,   KC_F6 ,   KC_F7 ,   KC_F8 ,   KC_F9 ,   KC_F10 ,   KC_F11 ,  KC_F12 } ,  
  { KC_CAPS , BL_DEC ,  BL_INC ,  _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_VOLD ,  KC_VOLU , KC_MPLY }
 } ,          

[_RAISE ] = { 
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    _______ } , 
  { KC_PLUS , KC_LBRC , KC_RBRC , KC_LPRN , KC_RPRN , KC_BSPC , KC_MINS , KC_ENT ,  KC_LCBR , KC_RCBR , _______ , _______ } , 
  { KC_TILD , KC_EXLM , KC_AT ,   KC_HASH , KC_DLR ,  KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , _______ , _______ , _______ } , 
  { _______ , KC_DEL ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } ,          

[_MOUSE] = { 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , KC_BSPC } ,
  { _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______ } ,
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
} ,

[_LEFT] = {
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_LCBR , KC_QUOT , KC_DQT ,  KC_RCBR , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_LPRN , KC_MINS , KC_PLUS , KC_RPRN , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , KC_LBRC , KC_EQL ,  KC_UNDS , KC_RBRC , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } 
 };


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
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
    case LEFT:
      if (record->event.pressed) {
        layer_on(_LEFT);
      } else {
        layer_off(_LEFT);
      }
      return false;
      break;
  }
  return true;
}

