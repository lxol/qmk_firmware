// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSE,
  _SUB_LOWER,
  _SUB_RAISE
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  MOUSE,
  SUB_LOWER,
  SUB_RAISE,
  SUB_LR
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  { KC_ESC ,  KC_Q ,    KC_W ,  KC_E ,    KC_R ,   KC_T ,    KC_Y ,   KC_U ,  KC_I ,    KC_O ,    KC_P ,    KC_BSPC } , 
  { KC_TAB ,  KC_A ,    KC_S ,  KC_D ,    KC_F ,   KC_G ,    KC_H ,   KC_J ,  KC_K ,    KC_L ,    KC_SCLN , KC_ENT } ,  
  { KC_LSFT , KC_Z ,    KC_X ,  KC_C ,    KC_V ,   KC_B ,    KC_N ,   KC_M ,  KC_COMM , KC_DOT ,  KC_SLSH , KC_RSFT } , 
  { KC_F24 ,  KC_F23 ,  MOUSE , KC_LALT , LOWER ,  KC_LGUI , KC_SPC , RAISE , KC_RCTL , KC_RALT , SUB_LR ,  _______ }
 } ,          

[_LOWER] = { 
  { KC_TILD , KC_EXLM , KC_AT , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_MINS , KC_EQL ,  KC_BSPC } , 
  { KC_DEL ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BSLS , KC_QUOT , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } ,

[_RAISE] = {
  { KC_GRV ,  KC_1 ,    KC_2 ,    KC_3 ,    KC_4 ,    KC_5 ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 ,    KC_BSPC } , 
  { _______ , KC_LBRC , KC_RBRC , _______ , _______ , _______ , _______ , KC_LPRN , KC_RPRN , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LCBR , KC_RCBR , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
 } ,          

[_MOUSE] = { 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_D , KC_WH_U , _______ , _______ , KC_BSPC } , 
  { _______ , _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN3 , KC_BTN2 , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }
} ,

[_SUB_RAISE] = {
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , KC_LGUI , KC_LSFT , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } 
 } ,          

[_SUB_LOWER] = {
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_RSFT , KC_LCTL , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ } , 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ }

    },

 };

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
  [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_SCLN)
};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
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
    case SUB_LOWER:
      if (record->event.pressed) {
        //sublayer_keep(true);
        sublayer_store_press(_LOWER, record->event.key);
        set_sublayer(_LOWER, record->event.key);
      } else {
        //sublayer_keep(false);
      }
      return false;
      break;
    case SUB_RAISE:
      if (record->event.pressed) {
        //sublayer_keep(true);
        sublayer_store_press(_RAISE, record->event.key);
        set_sublayer(_RAISE, record->event.key);
      } else {
        //sublayer_keep(false);
      }
      return false;
      break;

    case SUB_LR:
      if (record->event.pressed) {
        //sublayer_keep(true);
        //sublayer_store_press(_SUB_RAISE, record->event.key);
        set_sublayer(_SUB_LOWER, record->event.key);
        set_sublayer(_SUB_RAISE, record->event.key);
        set_sublayer(_RAISE, record->event.key);
      } else {
        //sublayer_keep(false);
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
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
