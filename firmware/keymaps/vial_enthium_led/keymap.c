#include QMK_KEYBOARD_H

// NOTE {modifier}_{key}_{Q,E}; Q = querty, E = enthium
// NOTE in many instances, KC_CAPS and KC_ESC are used interchangeably while i adjust to the new layout
// NOTE max variable length should not exceed 7 characters

// NOTE There are 8 layers on this keyboard, 0 to 7, but 9 are defined in `my_rgb_layers`. This is to prevent the rp2040
// led from staying on (red) at startup.

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
    _BASE = 0,
    _GAMING = 1,
    _NAV = 2,
    _MOUSE = 3,
    _FUN = 4,
    _SYM = 5,
    _BLANK_TRNS = 6,
    _UTIL = 7,
};

#define LT1_Z_E LT(_GAMING, KC_Z)
#define LT2_Y_E LT(_NAV, KC_Y)
#define LT3_O_E LT(_MOUSE, KC_O)
#define LT4_P_E LT(_FUN, KC_P)
#define LT4_O_Q LT(_FUN, KC_O) // qwerty/gaming
#define LT6_F_E LT(_BLANK_TRNS, KC_F)
#define LT7_V_E LT(_UTIL, KC_V)
#define LM_SYM MO(_SYM)

#define CUT C(KC_X)
#define COPY C(KC_C)
#define PASTE C(KC_V)
#define FIND C(KC_F)
#define SELALL C(KC_A)
#define TRM_CP LCTL(LSFT(KC_C)) // terminal copy
#define TRM_PST LCTL(LSFT(KC_V)) // terminal paste
#define SAVE C(KC_S)
#define KRUN LSA(KC_F2)
#define TTY1 LCA(KC_F1)
#define TTY2 LCA(KC_F2)
#define TTY3 LCA(KC_F3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , LT2_Y_E, LT3_O_E, KC_U   , KC_EQL ,                            KC_X   , KC_L   , KC_D   , LT4_P_E, LT1_Z_E, KC_BSLS,
        KC_B    , GUI_C_E, ALT_I_E, CTL_A_E, SFT_E_E, KC_MINS,                            KC_K   , SFT_H_E, CTL_T_E, ALT_N_E, GUI_S_E, KC_W   ,
        KC_DEL  , KC_QUOT, KC_COMM, KC_DOT , KC_SCLN, KC_SLSH,                            KC_J   , KC_M   , KC_G   , LT6_F_E, LT7_V_E, KC_ENT ,
                                            KC_ENT  , KC_SPC , KC_ESC ,         LM_SYM  , KC_R   , KC_F5
    ),
    [_GAMING] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                            KC_Y   , KC_U   , KC_I   , LT4_O_Q, KC_P   , KC_BSLS,
        KC_LCTL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                            KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                            KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_ENT  , KC_SPC , KC_ESC ,         LM_SYM  , KC_NO  , QK_LLCK
    ),
    [_NAV] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            CW_TOGG, KC_VOLD, KC_VOLU, KC_NO  , KC_PSCR, KC_BSPC,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_CAPS, KC_NO  ,
        KC_NO   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO  ,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_INS ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_TRNS,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_NO   , KC_NO  , QK_LLCK
    ),
    [_MOUSE] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KRUN   , TTY1   , TTY2   , TTY3   , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            MS_WHLL, MS_BTN1, MS_UP  , MS_BTN2, MS_WHLU, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            MS_WHLR, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_NO   , KC_NO  , QK_LLCK
    ),
    [_FUN] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , KC_NO  , QK_LLCK
    ),
    [_SYM] = LAYOUT(
        KC_GRV  , KC_SCLN, KC_LPRN, KC_RPRN, KC_COLN, KC_PERC,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_EXLM , KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_QUES,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_HASH , KC_CIRC, KC_MINS, KC_PLUS, KC_DLR , KC_ASTR,                            KC_NO  , KC_LSFT, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_TILD , KC_LABK, KC_AMPR, KC_PIPE, KC_RABK, KC_SLSH,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_AT   , KC_QUOT, KC_BSLS,         KC_NO   , KC_NO  , QK_LLCK
    ),
    [_BLANK_TRNS] = LAYOUT(
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS , KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_UTIL] = LAYOUT(
        KRUN    , QK_RBT , QK_BOOT, KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_PSCR, KC_NO  ,
        SAVE    , SELALL ,  KC_NO , TRM_CP , TRM_PST, KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_R    , KC_E   , KC_I   , KC_S   , KC_U   , KC_B   ,                            KC_NO  , KC_NO  , KC_NO  , KC_RALT, KC_NO  , KC_NO  ,
        KC_NO   , SELALL , CUT    , COPY   , PASTE  , FIND   ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_NO   , KC_NO  , QK_LLCK
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
    //                                         KC_TRNS , KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
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

enum rgb_layers {
    RGB_LAYER_0,
    RGB_LAYER_1,
    RGB_LAYER_2,
    RGB_LAYER_3,
    RGB_LAYER_4,
    RGB_LAYER_5,
    RGB_LAYER_6,
    RGB_LAYER_7,
    RGB_LAYER_CAPS
};

// Define lighting layers for the RP2040 LED
const rgblight_segment_t PROGMEM rgb_l0[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_OFF});

const rgblight_segment_t PROGMEM rgb_l1[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BLUE});

const rgblight_segment_t PROGMEM rgb_l2[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PINK});

const rgblight_segment_t PROGMEM rgb_l3[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});

const rgblight_segment_t PROGMEM rgb_l4[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});

const rgblight_segment_t PROGMEM rgb_l5[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});

const rgblight_segment_t PROGMEM rgb_l6[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});

const rgblight_segment_t PROGMEM rgb_l7[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});

const rgblight_segment_t PROGMEM rgb_caps[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});    

// The capslock layer has the highest priority
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_l0,
    rgb_l1,
    rgb_l2,
    rgb_l3,
    rgb_l4,
    rgb_l5,
    rgb_l6,
    rgb_l7,
    rgb_caps
);

// QMK callback function that runs at the end of the keyboard initialization process
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_layers = my_rgb_layers;
}

// Global vars
static uint8_t current_layer = 0;
static bool caps_lock = false;
static bool caps_word = false;

static void rgb_render_state(void) {
    bool caps = caps_lock || caps_word;

    // Base layers
    rgblight_set_layer_state(RGB_LAYER_0, current_layer == 0 && !caps);
    rgblight_set_layer_state(RGB_LAYER_1, current_layer == 1 && !caps);
    rgblight_set_layer_state(RGB_LAYER_2, current_layer == 2 && !caps);
    rgblight_set_layer_state(RGB_LAYER_3, current_layer == 3 && !caps);
    rgblight_set_layer_state(RGB_LAYER_4, current_layer == 4 && !caps);
    rgblight_set_layer_state(RGB_LAYER_5, current_layer == 5 && !caps);
    rgblight_set_layer_state(RGB_LAYER_6, current_layer == 6 && !caps);
    rgblight_set_layer_state(RGB_LAYER_7, current_layer == 7 && !caps);

    // Caps overrides everything
    rgblight_set_layer_state(RGB_LAYER_CAPS, caps);
}

// Called automatically when Caps Word state changes
void caps_word_set_user(bool active) {
    caps_word = active;
    rgb_render_state();
}

// Called when any LED state changes (caps lock, num lock, scroll lock)
bool led_update_user(led_t led_state) {
    caps_lock = led_state.caps_lock;
    rgb_render_state();
    return true;
}

// Update LED when layers change (unless overridden by caps states)
layer_state_t layer_state_set_user(layer_state_t state) {
    current_layer = get_highest_layer(state);
    rgb_render_state();
    return state;
}
