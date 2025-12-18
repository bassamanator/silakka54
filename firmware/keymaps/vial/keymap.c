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
#define GI_SN_Q RGUI_T(KC_SCLN)

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

enum layers {
    _ENTHIUM = 0,
    _NAV = 1,
    _FUN = 2,
    _MOUSE = 3,
    _SYM = 4,
    _BLANK = 5,
    _QUERTY = 6,
    _UTIL = 7,
};

// #define LT1_O_Q LT(_NAV, KC_O)
#define LT1_Y_E LT(_NAV, KC_Y)
#define LT2_D_E LT(_FUN, KC_D)
#define LT3_O_E LT(_MOUSE, KC_O)
#define LT4_W_E LT(_SYM, KC_W)
#define LT6_Z_E LT(_QUERTY, KC_Z)
#define LT7_V_E LT(_UTIL, KC_V)
#define L_BASE DF(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ENTHIUM] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , LT1_Y_E, LT3_O_E, KC_U   , KC_EQL ,                            KC_X   , KC_L   , LT2_D_E, LT4_W_E, LT6_Z_E   , KC_BSLS,
        KC_B    , GUI_C_E, ALT_I_E, CTL_A_E, SFT_E_E, KC_MINS,                            KC_K   , SFT_H_E, CTL_T_E, ALT_N_E, GUI_S_E, KC_F   ,
        KC_DEL   , KC_QUOT, KC_COMM, KC_DOT , KC_SCLN, KC_SLSH,                            KC_J   , KC_M   , KC_G   , KC_P   , LT7_V_E, KC_ENT ,
                                            KC_NO   , KC_ESC , KC_SPC ,          KC_R  , KC_NO   , KC_NO
    ),
    [_NAV] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
        KC_TRNS , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_CAPS, KC_NO  ,
        KC_NO   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO  ,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_INS ,
        KC_NO   , KC_NO  , KC_CUT , KC_COPY, KC_PSTE, KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_NO   , KC_TRNS, KC_TRNS ,         KC_PSCR, L_BASE , QK_LLCK
    ),
    [_FUN] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_TRNS , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_NO   , KC_TRNS, KC_TRNS ,         KC_PSCR, L_BASE , QK_LLCK
    ),
    [_MOUSE] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
        KC_NO   , KC_NO  , KC_BTN2, KC_NO  , KC_BTN1, KC_NO  ,                            KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_L, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_NO   , KC_TRNS, KC_TRNS,          KC_NO  , L_BASE, QK_LLCK
    ),
    [_SYM] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_LPRN  , KC_RPRN  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_LCBR  , KC_RCBR  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_LBRC  , KC_RBRC  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_LABK  , KC_RABK  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_NO   , KC_NO  , KC_NO  ,          KC_NO  , L_BASE , QK_LLCK
    ),
    [_BLANK] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_NO   , KC_NO  , KC_NO  ,          KC_NO  , KC_NO  , KC_NO
    ),    
    [_QUERTY] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W  , KC_E , KC_R   , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_LCTL , GUI_A_Q, ALT_S_Q, CTL_D_Q, SFT_F_Q, KC_G   ,                            KC_H   , SFT_J_Q, CTL_K_Q, ALT_L_Q, GI_SN_Q, KC_QUOT,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                            KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_LGUI , KC_ESC, KC_SPC ,         KC_NO , L_BASE , QK_LLCK
    ),
    [_UTIL] = LAYOUT(
        KC_NO   , QK_RBT , QK_BOOT, KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_R    , KC_E   , KC_I   , KC_S   , KC_U   , KC_B   ,                            KC_NO  , KC_NO  , KC_NO  , KC_RALT, KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_NO   , KC_NO  , KC_NO  ,          KC_PSCR, L_BASE , QK_LLCK
    ),
    // [_BLANK_NC] = LAYOUT(
    //     KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //     KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //     KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //     KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //                                         KC_NO   , KC_NO  , KC_NO  ,          KC_NO  , KC_NO  , KC_NO
    // ),
    // [_BLANK_TRNS] = LAYOUT(
    //     KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //     KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //     KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //     KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    //                                         KC_TRNS , KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
    // )
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 
                       'L', 'L', 'L',  'R', 'R', 'R'
    );
