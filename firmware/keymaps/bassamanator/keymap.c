#include QMK_KEYBOARD_H

// NOTE {modifier}_{key}_{Q,E}; Q = querty, E = enthium

// Left-hand home row mods; QUERTY
#define GUI_A_Q LGUI_T(KC_A)
#define ALT_S_Q LALT_T(KC_S)
#define CTL_D_Q LCTL_T(KC_D)
#define SFT_F_Q LSFT_T(KC_F)

// Right-hand home row mods; QUERTY
#define SFT_J_Q RSFT_T(KC_J)
#define CTL_K_Q RCTL_T(KC_K)
#define ALT_L_Q LALT_T(KC_L)
#define GUI_SCLN_Q RGUI_T(KC_SCLN)

// Left-hand home row mods; ENTHIUM
#define GUI_C_E LGUI_T(KC_C)
#define ALT_I_E LALT_T(KC_I)
#define CTL_A_E LCTL_T(KC_A)
#define SFT_E_E LSFT_T(KC_E)

// Right-hand home row mods; ENTHIUM
#define SFT_H_E RSFT_T(KC_H)
#define CTL_T_E RCTL_T(KC_T)
#define ALT_N_E LALT_T(KC_N)
#define GUI_S_E RGUI_T(KC_S)

#define LT_1_Y LT(1, KC_Y)

enum layers {
    _QUERTY,
    _QUERTY_ADJ,
    _ENTHIUM,
    _NAV,
    // _FUN,
    // _SYM,
    // _UTIL,
    // _MOUSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // [_QUERTY] = LAYOUT(
    //     QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
    //     KC_LCTL, GUI_A_Q,   ALT_S_Q,   CTL_D_Q,   SFT_F_Q,   KC_G,                               KC_H,    SFT_J_Q,   CTL_K_Q,   ALT_L_Q,   GUI_SCLN_Q, KC_QUOT,
    //     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
    //                                         KC_LGUI, MO(1), KC_SPC,              KC_ENT,  KC_RCTL, KC_RALT
    // ),
    // [_QUERTY_ADJ] = LAYOUT(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
    //     KC_LCTL, GUI_A_Q,   ALT_S_Q,   CTL_D_Q,   SFT_F_Q,   KC_G,                               KC_H,    SFT_J_Q,   CTL_K_Q,   ALT_L_Q,   GUI_SCLN_Q, KC_QUOT,
    //     KC_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
    //                                         KC_LGUI, MO(1), KC_SPC,              KC_ENT,  KC_RCTL, KC_RALT
    // ),
    [_ENTHIUM] = LAYOUT(
        KC_TAB  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_NO   , KC_Q   , LT_1_Y , KC_O   , KC_U   , KC_EQL ,                            KC_X   , KC_L   , KC_D   , KC_W   , KC_Z   , KC_BSLS,
        KC_B    , GUI_C_E, ALT_I_E, CTL_A_E, SFT_E_E, KC_MINS,                            KC_K   , SFT_H_E, CTL_T_E, ALT_N_E, GUI_S_E, KC_F   ,
        KC_NO   , KC_QUOT, KC_COMM, KC_DOT , KC_SCLN, KC_SLSH,                            KC_J   , KC_M   , KC_G   , KC_P   , KC_V   , KC_ENT ,
                                            KC_NO   ,   MO(1), KC_SPC ,         QK_GESC , KC_R   , QK_LEAD
    ),
    [_NAV] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_BSPC,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_HOME, KC_UP  , KC_END , KC_PGUP, KC_NO  ,
        KC_NO   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO  ,                            KC_NO  , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_DEL , KC_CAPS, KC_INS , KC_NO  , KC_ENT ,
                                            KC_NO   , KC_NO  , KC_SPC ,         QK_GESC , KC_NO  , QK_LLCK
    ),
    [_FUN] = LAYOUT(
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_PGUP, KC_PGDN, KC_HOME, KC_END,  KC_DEL,  KC_F12,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [_SYM] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [_BLANK] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [_BLANK_NC] = LAYOUT(
        KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_NO  , KC_NO  , KC_NO  ,           KC_NO  ,  KC_NO  ,  KC_NO  
    ),
    [_UTIL] = LAYOUT(
        QK_BOOT,  QK_RBT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    )
};

// NOTE For modifiers, reduce tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return TAPPING_TERM - 100;
        default:
            return TAPPING_TERM;
    }
}

/* https://docs.qmk.fm/features/key_overrides#simple-example */
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t capslock_key_override = ko_make_basic(MOD_MASK_GUI, KC_TAB, KC_CAPS);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &delete_key_override,
    &capslock_key_override
};

// NOTE leader key
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_1)) {
        // Leader, a, s => GUI+S
        tap_code16(TG(1));
    }
}