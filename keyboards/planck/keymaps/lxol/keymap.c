/*  -*-  eval: (turn-on-orgtbl); -*-
 * lxol planck Layout
 */

#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum planck_layers {
    _QWERTY,
    _SUBLEFT,
    _SUBRIGHT,
    _FS,
    _LOWER,
    _RAISE,
    _SYMBOLS,
    _RIGHT,
    _LEFT,
    _ESC,
    _ADJUST
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    BACKLIT,
    SUB_LR,
    SUB_LEFT,
    SUB_RIGHT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define I_____I SUB_TRNS
#define XXXXXXX KC_NO
#define I3_MOD KC_RALT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = {
        {KC_TAB  ,KC_Q   ,KC_W   ,KC_E    ,KC_R    ,KC_T    ,KC_Y   ,KC_U    ,KC_I    ,KC_O   ,KC_P    ,KC_BSPC}  ,
        {KC_FN0  ,KC_A   ,KC_S   ,KC_D    ,KC_F    ,KC_G    ,KC_H   ,KC_J    ,KC_K    ,KC_L   ,KC_FN1  , KC_ENT } ,
        {KC_LSFT ,KC_Z   ,KC_X   ,KC_C    ,KC_V    ,KC_B    ,KC_N   ,KC_M    ,KC_COMM ,KC_DOT ,KC_SLSH ,KC_RSFT } ,
        {KC_F24  ,KC_MEH ,KC_MEH ,KC_LGUI ,KC_LCTL ,SUB_RIGHT ,KC_SPC, SUB_LEFT,KC_LGUI ,KC_MEH ,KC_MEH   ,KC_RGUI}
    },

    [_LOWER] = {
        {KC_F12,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11},
        {KC_PIPE, KC_1,     KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    _______},
        {_______, _______,  _______,  _______, _______, KC_ENT,   _______, _______, _______, _______,  _______, _______},
        {_______, _______,  _______,  _______, _______, _______,  _______, _______, _______, KC_DEL,   _______, _______}
    },

    [_RAISE] = {
        {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS},
        {KC_PIPE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
        {_______, _______, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

    [_RIGHT] = {
        {_______ , _______ , _______ , _______      , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______} ,
        {_______ , _______ ,I3_MOD   , KC_LGUI      , KC_LCTL , _______ , _______ , _______ , _______ , _______ , _______ , _______} ,
        {_______ , _______ , _______ , MO(_SYMBOLS) , MO(_FS) , _______ , _______ , _______ , _______ , _______ , _______ , _______} ,
        {_______ , _______ , _______ , _______      , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______} 
    }            ,
    
    [_LEFT] = {
        {_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LCTL , KC_LGUI , I3_MOD  , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LGUI , KC_RALT , KC_LGUI , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______}

    },

    /* numeric keypad */
    [_SUBLEFT] = {
        {KC_GRV  , KC_1    , KC_2    , KC_3    ,  KC_4   , KC_5   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______} ,
        /* {KC_NO   , KC_NO   , _______ , KC_NO   , KC_LSFT , KC_NO  , KC_NO   , KC_RSFT , KC_NO   , KC_NO   , KC_SCLN , KC_QUOT} , */
        {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS},
        {KC_RSFT , KC_BSLS , KC_LBRC , KC_RBRC , KC_MINS , KC_EQL , KC_SCLN , KC_QUOT , _______ , _______ , _______ , KC_RSFT} ,
        {_______ , _______ , _______ , _______ , KC_NO , _______ , _______ ,KC_NO, _______ , _______ , _______ , _______} 

    },

    [_SUBRIGHT] = {
        {KC_GRV  , KC_1    , KC_2    , KC_3    ,  KC_4   , KC_5   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______} ,
        {KC_TILD, KC_QUOT, KC_DQT,   KC_SCLN, KC_COLN,  KC_MINS, KC_UNDS, KC_AMPR, KC_ASTR, KC_LPRN, KC_SCLN, KC_QUOT},
        {KC_BSLS , KC_QUOT , KC_SCLN , KC_LBRC  , KC_RBRC , KC_MINS   , KC_PLUS  , KC_LCBR , KC_RCBR , KC_COLN , KC_DQT ,  KC_EQL}   ,
        {_______ , _______ , _______ , _______   ,  KC_NO  , _______ , _______, KC_NO , _______ , _______ , _______ , _______} 

    },

    /*     [_SUBRIGHT] = { */
    /*     {_______ , _______ , _______   ,   KC_SCLN , KC_QUOT  , _______ , _______ , KC_MINS , KC_EQL ,  _______ , _______ , _______}   , */
    /*     {KC_GRV  , KC_1    ,    KC_2 ,    KC_3   ,    KC_4 ,    KC_5  ,    KC_6 ,    KC_7 ,    KC_8 ,    KC_9 ,    KC_0 , KC_BSLS} , */
    /*     {_______ , _______ , _______ , _______   , KC_LBRC , _______   , _______  , KC_RBRC , _______ , _______ , _______ , KC_RSFT}   , */
    /*     {_______ , _______ , _______ , _______   , _______ , KC_NO    , KC_LSFT , _______ , _______ , _______ , _______ , _______}  */

    /* }, */

    
    [_FS] = {
        {_______ , _______ , _______ , _______ , _______ , _______ , KC_F12  , KC_F7  , KC_F8   , KC_F9   , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , KC_F11  , KC_F4  , KC_F5   , KC_F6   , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , KC_F12  , KC_F1  , KC_F2   , KC_F3   , _______ , _______} ,
        {_______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_F10 , _______ , _______ , _______ , _______} 

    },
    [_SYMBOLS] = {
        {_______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}

    },
    [_ESC] = {
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {KC_QUOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN, _______},
        {KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT},
        {_______, _______, _______, _______, _______, KC_ESC , _______, KC_ESC , _______, _______, _______, _______}

    },

    [_ADJUST] = {
        {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
        {_______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______},
        {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
  [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_SCLN)
};



void persistant_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SUB_LR:
        if (record->event.pressed) {
            //sublayer_keep_on = true;
            set_sublayer(_RIGHT, record->event.key);
            set_sublayer(_LEFT, record->event.key);
            set_sublayer(_ESC, record->event.key);
        } else {
            //sublayer_keep_on = false;
        }
        return false;
        break;
    case SUB_LEFT:
        if (record->event.pressed) {
            //sublayer_keep(true);
            sublayer_store_press(_SUBLEFT, record->event.key);
            set_sublayer(_SUBLEFT, record->event.key);
        } else {
            //sublayer_keep(false);
        }
        return false;
        break;
    case SUB_RIGHT:
        if (record->event.pressed) {
            //sublayer_keep(true);
            sublayer_store_press(_SUBRIGHT, record->event.key);
            set_sublayer(_SUBRIGHT, record->event.key);
        } else {
            //sublayer_keep(false);
        }
        return false;
        break;

    }

    return true;
}

void matrix_init_user(void) {

}
