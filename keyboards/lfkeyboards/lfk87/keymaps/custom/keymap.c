#include "lfk87.h"
#include "issi.h"
#include "lighting.h"
#include "action_layer.h"

//Define a shorter 'transparent' key code to make the keymaps more compact
#define KC_TR KC_TRNS

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    WINLOCK,      // 0x02 Windows key disabled
    FUNC,         // 0x04
    SETTINGS,     // 0x08
};

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
    // Layer     Mask           Red     Green   Blue
    {0x00000000, 0xFFFFFFFF, {0xFF, 0x00, 0x00}}, // base layer - green
    {0x00000002, 0xFFFFFFFE, {0xFF, 0x1F, 0x00}}, // winlock layer - orange
    {0x00000004, 0xFFFFFFFC, {0xFF, 0x6F, 0x00}}, // function layer - yellow
    {0x00000008, 0xFFFFFFE8, {0xFF, 0x00, 0xFF}}, // settings layer - magenta
    {0xFFFFFFFF, 0xFFFFFFFF, {0xFF, 0xFF, 0xFF}}, // unknown layer - REQUIRED - white
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[VANILLA] = KEYMAP(
    /* Keymap VANILLA: (Base Layer) Default Layer
    * ,-----------------------------------------------------------.  ,--------------.
    * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
    * |-----------------------------------------------------------|  |--------------|
    * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
    * |-----------------------------------------------------------|  |--------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
    * |-----------------------------------------------------------|  `--------------'
    * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
    * |-----------------------------------------------------------|       ,----.
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |       | Up |
    * |-----------------------------------------------------------|  ,--------------.
    * |Ctrl|Gui |Alt |      Space            |Alt |Func|Menu|Ctrl |  |Left|Down|Righ|
    * `-----------------------------------------------------------'  `--------------'
    */
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS, \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DELETE, KC_END, KC_PGDN, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,  \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(FUNC), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[WINLOCK] = KEYMAP(
    /* Keymap WINLOCK: Windows-Key-Disabled Layer
    * ,-------------------------------------------------------------.  ,--------------.
    * |     |  |   |   |   |  |   |   |   |   |   |   |   |   |     |  |    |    |    |
    * |-------------------------------------------------------------|  |--------------|
    * |   |   |   |   |   |   |   |   |   |   |   |   |   |         |  |    |    |    |
    * |-------------------------------------------------------------|  |--------------|
    * |     |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
    * |-------------------------------------------------------------|  `--------------'
    * |       |   |   |   |   |   |   |   |   |   |   |   |         |
    * |-------------------------------------------------------------|       ,----.
    * |        |   |   |   |   |   |   |    |   |   |  |            |       |    |
    * |-------------------------------------------------------------'  ,--------------.
    * |    |    |    |                             |    |     |     |  |    |    |    |
    * `-------------------------------------------------------------'  `--------------'
    */
    KC_TR,   KC_TR, KC_TR, KC_TR, KC_TR,    KC_TR, KC_TR, KC_TR, KC_TR,    KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,   KC_TR,   KC_TR, \
    KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,  KC_TR,   KC_TR,   KC_TR, \
    KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,   KC_TR,   KC_TR, \
    KC_TR,   KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,       KC_TR, \
    KC_TR,    KC_TR,  KC_TR,  KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,          KC_TR,           KC_TR, \
    KC_TR, KC_NO, KC_TR,                    KC_TR,                         KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,   KC_TR,   KC_TR),

[FUNC] = KEYMAP(
        /* Keymap FUNCTION: Function Layer
        * ,-------------------------------------------------------------.  ,--------------.
        * |     |  |   |   |   |  |   |   |   |   |   |   |   |   |     |  |    |    |    |
        * |-------------------------------------------------------------|  |--------------|
        * |   |   |   |   |   |   |   |   |   |   |   |   |   |         |  |Prev|Play|Next|
        * |-------------------------------------------------------------|  |--------------|
        * |     |   |   |   |   |   |   |   |   |   |   |   |   |       |  |Mute| V- | V+ |
        * |-------------------------------------------------------------|  `--------------'
        * |       |   |   |   |   |   |   |   |   |   |   |   |         |
        * |-------------------------------------------------------------|       ,----.
        * |        |   |   |   |   |   |   |    |   |   |  |TG(SETTINGS)|       |    |
        * |-------------------------------------------------------------'  ,--------------.
        * |    |    |    |                             |    |     |     |  |    |    |    |
        * `-------------------------------------------------------------'  `--------------'
        */
        KC_TR,   KC_TR, KC_TR, KC_TR, KC_TR,    KC_TR, KC_TR, KC_TR, KC_TR,    KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,   KC_TR,   KC_TR, \
    KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,  KC_MPRV, KC_MPLY, KC_MNXT, \
    KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_UP, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,  KC_MUTE, KC_VOLD, KC_VOLU, \
    KC_TR,   KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,       KC_TR, \
    KC_TR,    KC_TR,  KC_TR,  KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,   TG(SETTINGS),           KC_TR, \
    KC_TR, TG(WINLOCK), KC_TR,              KC_TR,                         KC_TR, KC_TR, KC_TR, KC_TR,  KC_TR,   KC_TR,   KC_TR),

[SETTINGS] = KEYMAP(
    /* Keymap SETTINGS: Settings Layer
    * ,-------------------------------------------------------------.  ,--------------.
    * |FN0  |  |   |   |   |  |   |   |   |   |   |   |   |   |     |  |    |    |    |
    * |-------------------------------------------------------------|  |--------------|
    * |FN0 |   |   |   |   |   |   |   |   |  |   |   |   |      |  |  |    |    |    |
    * |-------------------------------------------------------------|  |--------------|
    * |      |   |   |   |   |   |   |   |   |   |   |   |  |       |  |    |    |    |
    * |-------------------------------------------------------------|  `--------------'
    * |       |   |   |   |   |   |   |   |   |   |   |   |  RESET  |
    * |-------------------------------------------------------------|       ,----.
    * |        |   |   |   |   |   |   |   |   |   |   |            |       |    |
    * |-------------------------------------------------------------'  ,--------------.
    * |    |    |    |                             |    |     |     |  |    |    |    |
    * `-------------------------------------------------------------'  `--------------'
    */
    KC_FN0,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO,   KC_NO,   KC_NO,
    KC_FN0,KC_NO,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO,  KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            RESET,
    KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MU_TOG, KC_NO, KC_NO, KC_NO,                 KC_NO,           KC_NO,
    KC_NO, KC_NO, KC_NO,                  KC_NO,                           KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),                   // FN1 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),                    // FN2 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),                   // FN3 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),                  // FN4 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),                        // FN5 - Toggle audio click
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
    }
    return MACRO_NONE;
};


void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if(eeconfig_read_default_layer() > 1){
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
