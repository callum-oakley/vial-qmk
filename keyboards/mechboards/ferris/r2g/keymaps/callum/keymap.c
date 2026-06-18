#include QMK_KEYBOARD_H

#define LA_NAV MO(NAV)
#define LA_LSYM MO(LSYM)
#define LA_RSYM MO(RSYM)
#define LA_FN MO(FN)
#define LOCK LCMD(LCTL(KC_Q))
#define CLOSE LCMD(KC_W)
#define TAB_L LCMD(LSFT(KC_LBRC))
#define TAB_R LCMD(LSFT(KC_RBRC))
#define FRESH LCMD(KC_R)
#define BACK LCMD(KC_LBRC)
#define FWD LCMD(KC_RBRC)

enum layers {
    BASE,
    NAV,
    LSYM,
    RSYM,
    FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2_enc(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   LA_LSYM, LA_NAV,     KC_SPC,  LA_RSYM,
                                            _______,    _______
    ),

    [NAV] = LAYOUT_split_3x5_2_enc(
        LOCK,    CLOSE,   TAB_L,   TAB_R,   _______,    _______, KC_BSPC, KC_UP,   KC_DEL,  KC_TAB,
        KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, KC_ESC,     KC_ESC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,
        LA_FN,   FRESH,   BACK,    FWD,     _______,    _______, KC_VOLD, KC_VOLU, KC_MPLY, _______,
                                   _______, _______,    _______, _______,
                                            _______,    _______
    ),

    [LSYM] = LAYOUT_split_3x5_2_enc(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       _______, _______, _______, _______, _______,
        KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, KC_ESC,     _______, _______, _______, _______, _______,
        KC_CAPS, KC_GRV,  KC_MINS, KC_EQL,  _______,    _______, _______, _______, _______, _______,
                                   _______, _______,    _______, _______,
                                            _______,    _______
    ),

    [RSYM] = LAYOUT_split_3x5_2_enc(
        _______, _______, _______, _______, _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______, _______, _______, _______,    KC_ESC,  KC_RSFT, KC_RCMD, KC_RALT, KC_RCTL,
        _______, _______, _______, _______, _______,    _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_BSLS,
                                   _______, _______,    _______, _______,
                                            _______,    _______
    ),

    [FN] = LAYOUT_split_3x5_2_enc(
        _______, _______, _______, _______, _______,    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,
        _______, RM_TOGG, RM_PREV, RM_NEXT, _______,    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,
        _______, _______, _______, _______, QK_BOOT,    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,
                                   _______, _______,    _______, _______,
                                            _______,    _______
    )
};
