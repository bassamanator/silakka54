#include QMK_KEYBOARD_H

// NOTE {modifier}_{key}_{Q,E}; Q = querty, E = enthium
// NOTE in many instances, KC_CAPS and KC_ESC are used interchangeably while i adjust to the new layout
// NOTE max variable length should not exceed 7 characters

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
    _MOUSE = 2,
    _FUN = 3,
    _SYM = 4,
    _GAMING = 5,
    _QUERTY = 6,
    _UTIL = 7,
};

// #define LT1_O_Q LT(_NAV, KC_O)
#define LT1_Y_E LT(_NAV, KC_Y)
#define LT2_O_E LT(_MOUSE, KC_O)
#define LT3_D_E LT(_FUN, KC_D)
#define LT4_P_E LT(_SYM, KC_P)
#define LT5_Z_E LT(_GAMING, KC_Z)
#define LT6_F_E LT(_QUERTY, KC_F)
#define LT7_V_E LT(_UTIL, KC_V)
#define L_BASE DF(0)
// #define FIND LCTL(KC_F)
#define FIND C(KC_F)
#define TRM_CP LCTL(LSFT(KC_C))
#define TRM_PST LCTL(LSFT(KC_V))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ENTHIUM] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , LT1_Y_E, LT2_O_E, KC_U   , KC_EQL ,                            KC_X   , KC_L   , LT3_D_E, LT4_P_E, LT5_Z_E, KC_BSLS,
        KC_B    , GUI_C_E, ALT_I_E, CTL_A_E, SFT_E_E, KC_MINS,                            KC_K   , SFT_H_E, CTL_T_E, ALT_N_E, GUI_S_E, KC_W   ,
        KC_DEL  , KC_QUOT, KC_COMM, KC_DOT , KC_SCLN, KC_SLSH,                            KC_J   , KC_M   , KC_G   , LT6_F_E, LT7_V_E, KC_ENT ,
                                            KC_ENT  , KC_SPC , KC_CAPS,          KC_NO  , KC_R   , KC_NO
    ),
    [_NAV] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_BSPC,
        KC_TRNS , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_ESC , KC_NO  ,
        KC_NO   , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO  ,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_INS ,
        KC_NO   , KC_NO  , KC_CUT , KC_COPY, KC_PSTE, FIND   ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , L_BASE , QK_LLCK
    ),
    [_MOUSE] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , MS_BTN2, KC_NO  , MS_BTN1, KC_NO  ,                            MS_WHLU, MS_BTN1, MS_UP  , MS_BTN2, MS_WHLL, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR, KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , L_BASE , QK_LLCK
    ),
    [_FUN] = LAYOUT(
        KC_NO   , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , L_BASE , QK_LLCK
    ),
    [_SYM] = LAYOUT(
        KC_TILD , KC_EXLM, KC_AT  , KC_LPRN, KC_RPRN, KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_HASH , KC_DLR , KC_PERC, KC_LCBR, KC_RCBR, KC_PLUS,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_CIRC , KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_UNDS,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_DQUO, KC_LABK, KC_RABK, KC_QUES, KC_COLN,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , L_BASE , QK_LLCK
    ),
    [_GAMING] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_LCTL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                            KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                            KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_LGUI , KC_CAPS, KC_ENT ,          KC_SPC , L_BASE , QK_LLCK
    ),
    [_QUERTY] = LAYOUT(
        KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                            KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_LCTL , GUI_A_Q, ALT_S_Q, CTL_D_Q, SFT_F_Q, KC_G   ,                            KC_H   , SFT_J_Q, CTL_K_Q, ALT_L_Q, GI_SN_Q, KC_QUOT,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                            KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_LGUI , KC_CAPS, KC_ENT ,          KC_SPC , L_BASE , QK_LLCK
    ),
    [_UTIL] = LAYOUT(
        KC_NO   , QK_RBT , QK_BOOT, KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_NO  , TRM_CP , TRM_PST, KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_R    , KC_E   , KC_I   , KC_S   , KC_U   , KC_B   ,                            KC_NO  , KC_NO  , KC_NO  , KC_RALT, KC_NO  , KC_NO  ,
        KC_NO   , KC_NO  , KC_CUT , KC_COPY, KC_PSTE, FIND   ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS,
                                            KC_TRNS , KC_TRNS, KC_TRNS,         KC_PSCR , L_BASE , QK_LLCK
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

// Define lighting layers for the internal LED
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}    // Light the single LED (LED 0) red when caps lock is active
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}   // Light the single LED (LED 0) blue when layer 1 is active
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}  // Light the single LED (LED 0) green when layer 2 is active
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE} // Light the single LED (LED 0) purple when layer 3 is active
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE} // Light the single LED (LED 0) orange when layer 4 is active
);

const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN}   // Light the single LED (LED 0) cyan when layer 5 is active
);

const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW} // Light the single LED (LED 0) yellow when layer 6 is active
);

const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_MAGENTA} // Light the single LED (LED 0) magenta when layer 7 is active
);

// Layer priority: caps lock > layer 7 > layer 6 > layer 5 > layer 4 > layer 3 > layer 2 > layer 1
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,    // Layer 1: Layer 1 indicator (priority 1)
    my_layer2_layer,    // Layer 2: Layer 2 indicator (priority 2)
    my_layer3_layer,    // Layer 3: Layer 3 indicator (priority 3)
    my_layer4_layer,    // Layer 4: Layer 4 indicator (priority 4)
    my_layer5_layer,    // Layer 5: Layer 5 indicator (priority 5)
    my_layer6_layer,    // Layer 6: Layer 6 indicator (priority 6)
    my_layer7_layer,    // Layer 7: Layer 7 indicator (priority 7)
    my_capslock_layer   // Caps lock indicator (highest priority)
);

// Forward declarations
static void apply_layer_color(uint8_t layer);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    // Restore layer states from EEPROM
    rgblight_reload_from_eeprom();
    // Ensure LED reflects the current highest layer on startup
    apply_layer_color(get_highest_layer(layer_state));
}

// Track caps lock state locally so layer updates can respect it
static bool caps_active = false;

static void set_layer0_led_off(void) {
    rgblight_setrgb_at(0, 0, 0, 0);
}

static void apply_layer_color(uint8_t layer) {
    switch (layer) {
        case 0: // base
            set_layer0_led_off();
            break;
        case 1: // blue
            rgblight_setrgb_at(0, 0, 255, 0);
            break;
        case 2: // green
            rgblight_setrgb_at(0, 255, 0, 0);
            break;
        case 3: // purple
            rgblight_setrgb_at(128, 0, 128, 0);
            break;
        case 4: // orange
            rgblight_setrgb_at(255, 165, 0, 0);
            break;
        case 5: // cyan
            rgblight_setrgb_at(0, 255, 255, 0);
            break;
        case 6: // yellow
            rgblight_setrgb_at(255, 255, 0, 0);
            break;
        case 7: // magenta
            rgblight_setrgb_at(255, 0, 255, 0);
            break;
        default:
            set_layer0_led_off();
            break;
    }
}

// Enable/disable caps-lock indicator
bool led_update_user(led_t led_state) {
    caps_active = led_state.caps_lock;
    if (caps_active) {
        // Force red regardless of active layer
        rgblight_setrgb_at(255, 0, 0, 0);
    } else {
        // Restore color for current layer
        apply_layer_color(get_highest_layer(layer_state));
    }
    return true;
}

// Enable/disable layers based on layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    // When caps lock is active we keep the red indicator; otherwise update
    if (caps_active) {
        // nothing to do for layer colors while caps is active
        return state;
    }
    // Apply color for the current highest layer
    apply_layer_color(get_highest_layer(state));
    return state;
}