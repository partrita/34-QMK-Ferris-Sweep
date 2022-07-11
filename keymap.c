#include QMK_KEYBOARD_H

enum tap_dance_codes {
  DANCE_01,
  DANCE_02,
  DANCE_03,
//  DANCE_04, UNUSED
  DANCE_05,
  DANCE_06,
  DANCE_15,
  DANCE_31,
  DANCE_32,
//  DANCE_33, UNUSED
  DANCE_54,
  DANCE_55,
  DANCE_56,
  DANCE_57,
  DANCE_58,
  DANCE_59,
  DANCE_60,
  DANCE_63,
  BKSL_HME,
  PIPE_END,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TD(DANCE_06),   KC_W,   KC_E,   KC_R,   KC_T,                                                KC_Y,   KC_U,    KC_I,      KC_O,     TD(DANCE_01),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_A,   KC_S, MT(MOD_LALT,KC_D),  MT(MOD_LGUI,KC_F),   KC_G,                                 KC_H,   MT(MOD_LGUI,KC_J),  MT(MOD_LALT,KC_K),  KC_L, TD(DANCE_02),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      MT(MOD_LGUI,KC_Z),   KC_X,   KC_C,   KC_V,   KC_B,                                           KC_N,   KC_M,    TD(DANCE_03),    KC_DOT,    TD(DANCE_05),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_SPACE,  KC_LSFT,                                                                          KC_ENT, TO(1)
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
  ),

  [1] = LAYOUT(
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_ESC,  KC_AT,  LSFT(KC_3),   TD(DANCE_31),   KC_PERC,                                      KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_SCOLON,    KC_BSPC,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_TAB, KC_EQL,   KC_QUOT,   KC_GRV,   TD(DANCE_32),                                         TD(BKSL_HME),    LSFT(KC_LBRC),    LSFT(KC_RBRC),    TD(PIPE_END),   KC_ENTER,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_TILD, LALT(LSFT(KC_2)),  KC_HAEN,  KC_HAEN,  KC_HAEN,                                           KC_LBRC,  KC_LPRN,  KC_RPRN,  KC_RBRC,  TO(2),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TO(0),  OSM(MOD_LSFT),                                                                       KC_RALT, TO(3)
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
  ),

  [2] = LAYOUT(
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_ESC,  LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_MINS),                               KC_MINS,   KC_7,  KC_8,  KC_9,  KC_BSPC,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      KC_TAB, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,  LSFT(KC_EQL),                   KC_EQL,    KC_4,  KC_5,  KC_6,  KC_ENTER,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      RESET,  KC_KP_ASTERISK, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_KP_DOT,                     KC_0,      KC_1,  KC_2,  KC_3,  TO(3),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TO(0), KC_LGUI,                                                                              KC_RALT, TO(1)
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
  ),

  [3] = LAYOUT(
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TD(DANCE_54),   KC_MS_WH_LEFT,  KC_MS_UP,       KC_MS_WH_RIGHT, TD(DANCE_55),                LGUI(KC_LBRACKET), LCTL(LSFT(KC_TAB)), RCTL(KC_TAB), LGUI(KC_RBRACKET), KC_TRANSPARENT,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TD(DANCE_56),   KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    MT(MOD_LGUI,KC_DEL),         TD(DANCE_60), MT(MOD_RGUI,KC_DOWN), MT(MOD_RALT,KC_UP), TD(DANCE_63), KC_ENTER,
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TD(DANCE_58),   KC_MS_BTN2,     KC_MS_WH_UP,    KC_MS_WH_DOWN, KC_HAEN,               KC_MS_BTN1,  KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   TO(2),
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
      TO(0),  KC_TRANSPARENT,                                                                      KC_RALT,  TO(1)
  //  ---------------------------------------------------------------------------------------      ---------------------------------------------------------------------------------------
  )
};

extern bool g_suspend_state;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

typedef struct {
  bool is_press_action;
  uint8_t step;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  DOUBLE_SINGLE_TAP,
  MORE_TAPS
};

static tap dance_state = {
  .is_press_action = true,
  .step = 0
};

// DANCE_01
void on_dance_01(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_01_dance_step(qk_tap_dance_state_t *state);
void dance_01_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_01_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_01(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_P);
    tap_code16(KC_P);
    tap_code16(KC_P);
  }
  if(state->count > 3) {
    tap_code16(KC_P);
  }
}

uint8_t dance_01_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
  if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_01_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_01_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_P); break;
    case SINGLE_HOLD: register_code16(KC_BSPC); break;
    case DOUBLE_TAP: register_code16(KC_BSPC); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_P);
  }
}

void dance_01_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_P); break;
    case SINGLE_HOLD: unregister_code16(KC_BSPC); break;
    case DOUBLE_TAP: unregister_code16(KC_BSPC); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_P); break;
  }
  dance_state.step = 0;
}

// DANCE_02
void on_dance_02(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_02_dance_step(qk_tap_dance_state_t *state);
void dance_02_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_02_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_02(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_MINS);
    tap_code16(KC_MINS);
    tap_code16(KC_MINS);
  }
  if(state->count > 3) {
    tap_code16(KC_MINS);
  }
}

uint8_t dance_02_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_02_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_02_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_MINS); break;
    case SINGLE_HOLD: register_code16(KC_MINS); break;
    case DOUBLE_TAP: register_code16(KC_MINS); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_MINS);
  }
}

void dance_02_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_MINS); break;
    case SINGLE_HOLD: unregister_code16(KC_MINS); break;
    case DOUBLE_TAP: unregister_code16(KC_MINS); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINS); break;
  }
  dance_state.step = 0;
}

// DANCE_03
void on_dance_03(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_03_dance_step(qk_tap_dance_state_t *state);
void dance_03_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_03_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_03(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_COMM);
    tap_code16(KC_COMM);
    tap_code16(KC_COMM);
  }
  if(state->count > 3) {
    tap_code16(KC_COMM);
  }
}

uint8_t dance_03_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_03_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_03_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_COMM); break;
    case SINGLE_HOLD: register_code16(KC_HAEN); break;
    case DOUBLE_TAP: register_code16(KC_SCLN); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_COMM);
  }
}

void dance_03_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_COMM); break;
    case SINGLE_HOLD: unregister_code16(KC_HAEN); break;
    case DOUBLE_TAP: unregister_code16(KC_SCLN); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_COMM); break;
  }
  dance_state.step = 0;
}

// DANCE_04
void on_dance_04(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_04_dance_step(qk_tap_dance_state_t *state);
void dance_04_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_04_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_04(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_DOT);
    tap_code16(KC_DOT);
    tap_code16(KC_DOT);
  }
  if(state->count > 3) {
    tap_code16(KC_DOT);
  }
}

uint8_t dance_04_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_04_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_04_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_DOT); break;
    case SINGLE_HOLD: register_code16(KC_QUOT); break;
    case DOUBLE_TAP: register_code16(KC_DOT); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT);
  }
}

void dance_04_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_DOT); break;
    case SINGLE_HOLD: unregister_code16(KC_QUOT); break;
    case DOUBLE_TAP: unregister_code16(KC_DOT); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
  }
  dance_state.step = 0;
}

// DANCE_05
void on_dance_05(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_05_dance_step(qk_tap_dance_state_t *state);
void dance_05_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_05_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_05(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_SLASH);
    tap_code16(KC_SLASH);
    tap_code16(KC_SLASH);
  }
  if(state->count > 3) {
    tap_code16(KC_SLASH);
  }
}

uint8_t dance_05_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_05_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_05_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_SLASH); break;
    case SINGLE_HOLD: register_code16(S(KC_1)); break;
    case DOUBLE_TAP: register_code16(KC_SLASH); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH);
  }
}

void dance_05_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_SLASH); break;
    case SINGLE_HOLD: unregister_code16(S(KC_1)); break;
    case DOUBLE_TAP: unregister_code16(KC_SLASH); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
  }
  dance_state.step = 0;
}

// DANCE_06
void on_dance_06(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_06_dance_step(qk_tap_dance_state_t *state);
void dance_06_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_06_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_06(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_Q);
    tap_code16(KC_Q);
    tap_code16(KC_Q);
  }
  if(state->count > 3) {
    tap_code16(KC_Q);
  }
}

uint8_t dance_06_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_06_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_06_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_Q); break;
    case SINGLE_HOLD: register_code16(S(KC_ESC)); break;
    case DOUBLE_TAP: register_code16(KC_Q); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_Q);
  }
}

void dance_06_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_Q); break;
    case SINGLE_HOLD: unregister_code16(S(KC_ESC)); break;
    case DOUBLE_TAP: unregister_code16(KC_Q); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_Q); break;
  }
  dance_state.step = 0;
}

// DANCE_15
void on_dance_15(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_15_dance_step(qk_tap_dance_state_t *state);
void dance_15_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_15_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_15(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_SPACE);
    tap_code16(KC_SPACE);
    tap_code16(KC_SPACE);
  }
  if(state->count > 3) {
    tap_code16(KC_SPACE);
  }
}

uint8_t dance_15_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_15_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_15_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_SPACE); break;
    case SINGLE_HOLD: register_code16(KC_UNDS); break;
    case DOUBLE_TAP: register_code16(KC_SPACE); register_code16(KC_SPACE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_SPACE); register_code16(KC_SPACE);
  }
}

void dance_15_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_SPACE); break;
    case SINGLE_HOLD: unregister_code16(KC_UNDS); break;
    case DOUBLE_TAP: unregister_code16(KC_SPACE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
  }
  dance_state.step = 0;
}

// DANCE_31
void on_dance_31(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_31_dance_step(qk_tap_dance_state_t *state);
void dance_31_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_31_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_31(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(LSFT(KC_4));
    tap_code16(LSFT(KC_4));
    tap_code16(LSFT(KC_4));
  }
  if(state->count > 3) {
    tap_code16(LSFT(KC_4));
  }
}

uint8_t dance_31_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_31_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_31_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(LSFT(KC_4)); break;
    case SINGLE_HOLD: register_code16(LCTL(LGUI(LSFT(KC_4)))); break;
    case DOUBLE_TAP: register_code16(LSFT(KC_4)); register_code16(LSFT(KC_4)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(LSFT(KC_4)); register_code16(LSFT(KC_4));
  }
}

void dance_31_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(LSFT(KC_4)); break;
    case SINGLE_HOLD: unregister_code16(LCTL(LGUI(LSFT(KC_4)))); break;
    case DOUBLE_TAP: unregister_code16(LSFT(KC_4)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(LSFT(KC_4)); break;
  }
  dance_state.step = 0;
}

// DANCE_32
void on_dance_32(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_32_dance_step(qk_tap_dance_state_t *state);
void dance_32_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_32_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_32(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_QUOTE);
    tap_code16(KC_QUOTE);
    tap_code16(KC_QUOTE);
  }
  if(state->count > 3) {
    tap_code16(KC_QUOTE);
  }
}

uint8_t dance_32_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_32_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_32_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_QUOTE); break;
    case SINGLE_HOLD: register_code16(LGUI(KC_QUOTE)); break;
    case DOUBLE_TAP: register_code16(KC_GRAVE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_QUOTE); register_code16(KC_QUOTE);
  }
}

void dance_32_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_QUOTE); break;
    case SINGLE_HOLD: unregister_code16(LGUI(KC_QUOTE)); break;
    case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
  }
  dance_state.step = 0;
}

// DANCE_33
void on_dance_33(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_33_dance_step(qk_tap_dance_state_t *state);
void dance_33_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_33_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_33(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(LALT(KC_3));
    tap_code16(LALT(KC_3));
    tap_code16(LALT(KC_3));
  }
  if(state->count > 3) {
    tap_code16(LALT(KC_3));
  }
}

uint8_t dance_33_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_33_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_33_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(LALT(KC_3)); break;
    case SINGLE_HOLD: register_code16(LALT(LSFT(KC_2))); break;
    case DOUBLE_TAP: register_code16(LALT(KC_3)); register_code16(LALT(KC_3)); break;
    case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_3)); register_code16(LALT(KC_3));
  }
}

void dance_33_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(LALT(KC_3)); break;
    case SINGLE_HOLD: unregister_code16(LALT(LSFT(KC_2))); break;
    case DOUBLE_TAP: unregister_code16(LALT(KC_3)); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_3)); break;
  }
  dance_state.step = 0;
}

// DANCE_54
void on_dance_54(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_54_dance_step(qk_tap_dance_state_t *state);
void dance_54_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_54_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_54(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_ESC);
    tap_code16(KC_ESC);
    tap_code16(KC_ESC);
  }
  if(state->count > 3) {
    tap_code16(KC_ESC);
  }
}

uint8_t dance_54_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
      if (state->interrupted || !state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
  } else if (state->count == 2) {
      if (state->interrupted) return DOUBLE_SINGLE_TAP;
      else if (state->pressed) return DOUBLE_HOLD;
      else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_54_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_54_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_ESC); break;
    case SINGLE_HOLD: register_code16(LALT(LGUI(KC_ESC))); break;
    case DOUBLE_TAP: register_code16(KC_ESC); register_code16(KC_ESC); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_ESC); register_code16(KC_ESC);
  }
}

void dance_54_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_ESC); break;
    case SINGLE_HOLD: unregister_code16(LALT(LGUI(KC_ESC))); break;
    case DOUBLE_TAP: unregister_code16(KC_ESC); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESC); break;
  }
  dance_state.step = 0;
}

// DANCE_55
void on_dance_55(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_55_dance_step(qk_tap_dance_state_t *state);
void dance_55_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_55_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_55(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_Q);
    tap_code16(KC_Q);
    tap_code16(KC_Q);
  }
  if(state->count > 3) {
    tap_code16(KC_Q);
  }
}

uint8_t dance_55_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_55_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_55_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_Q); break;
    case SINGLE_HOLD: register_code16(KC_H); break;
    case DOUBLE_TAP: register_code16(KC_Q); register_code16(KC_Q); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_Q); register_code16(KC_Q);
  }
}

void dance_55_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_Q); break;
    case SINGLE_HOLD: unregister_code16(KC_H); break;
    case DOUBLE_TAP: unregister_code16(KC_Q); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_Q); break;
  }
  dance_state.step = 0;
}

// DANCE_56
void on_dance_56(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_56_dance_step(qk_tap_dance_state_t *state);
void dance_56_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_56_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_56(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_TAB);
    tap_code16(KC_TAB);
    tap_code16(KC_TAB);
  }
  if(state->count > 3) {
    tap_code16(KC_TAB);
  }
}

uint8_t dance_56_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_56_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_56_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_TAB); break;
    case SINGLE_HOLD: register_code16(LGUI(KC_TAB)); break;
    case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
  }
}

void dance_56_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_TAB); break;
    case SINGLE_HOLD: unregister_code16(LGUI(KC_TAB)); break;
    case DOUBLE_TAP: unregister_code16(KC_TAB); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
  }
  dance_state.step = 0;
}

// DANCE_57
void on_dance_57(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_57_dance_step(qk_tap_dance_state_t *state);
void dance_57_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_57_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_57(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_DELETE);
    tap_code16(KC_DELETE);
    tap_code16(KC_DELETE);
  }
  if(state->count > 3) {
    tap_code16(KC_DELETE);
  }
}

uint8_t dance_57_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_57_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_57_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_DELETE); break;
    case SINGLE_HOLD: register_code16(LCTL(KC_K)); break;
    case DOUBLE_TAP: register_code16(KC_DELETE); register_code16(KC_DELETE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_DELETE); register_code16(KC_DELETE);
  }
}

void dance_57_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_DELETE); break;
    case SINGLE_HOLD: unregister_code16(LCTL(KC_K)); break;
    case DOUBLE_TAP: unregister_code16(KC_DELETE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_DELETE); break;
  }
  dance_state.step = 0;
}

// DANCE_58
void on_dance_58(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_58_dance_step(qk_tap_dance_state_t *state);
void dance_58_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_58_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_58(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_GRAVE);
    tap_code16(KC_GRAVE);
    tap_code16(KC_GRAVE);
  }
  if(state->count > 3) {
    tap_code16(KC_GRAVE);
  }
}

uint8_t dance_58_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_58_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_58_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_GRAVE); break;
    case SINGLE_HOLD: register_code16(LGUI(KC_GRAVE)); break;
    case DOUBLE_TAP: register_code16(KC_GRAVE); register_code16(KC_GRAVE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_GRAVE); register_code16(KC_GRAVE);
  }
}

void dance_58_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_GRAVE); break;
    case SINGLE_HOLD: unregister_code16(LGUI(KC_GRAVE)); break;
    case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
  }
  dance_state.step = 0;
}

// DANCE_59
void on_dance_59(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_59_dance_step(qk_tap_dance_state_t *state);
void dance_59_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_59_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_59(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_SPACE);
    tap_code16(KC_SPACE);
    tap_code16(KC_SPACE);
  }
  if(state->count > 3) {
    tap_code16(KC_SPACE);
  }
}

uint8_t dance_59_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_59_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_59_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_SPACE); break;
    case SINGLE_HOLD: register_code16(LGUI(KC_O)); break;
    case DOUBLE_TAP: register_code16(KC_SPACE); register_code16(KC_SPACE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_SPACE); register_code16(KC_SPACE);
  }
}

void dance_59_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_SPACE); break;
    case SINGLE_HOLD: unregister_code16(LGUI(KC_O)); break;
    case DOUBLE_TAP: unregister_code16(KC_SPACE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
  }
  dance_state.step = 0;
}

// DANCE_60
void on_dance_60(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_60_dance_step(qk_tap_dance_state_t *state);
void dance_60_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_60_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_60(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_LEFT);
    tap_code16(KC_LEFT);
    tap_code16(KC_LEFT);
  }
  if(state->count > 3) {
    tap_code16(KC_LEFT);
  }
}

uint8_t dance_60_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_60_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_60_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_LEFT); break;
    case SINGLE_HOLD: register_code16(LALT(KC_LEFT)); break;
    case DOUBLE_TAP: register_code16(KC_LEFT); register_code16(KC_LEFT); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT); register_code16(KC_LEFT);
  }
}

void dance_60_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_LEFT); break;
    case SINGLE_HOLD: unregister_code16(LGUI(KC_LEFT)); break;
    case DOUBLE_TAP: unregister_code16(KC_LEFT); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
  }
  dance_state.step = 0;
}

// DANCE_63
void on_dance_63(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_63_dance_step(qk_tap_dance_state_t *state);
void dance_63_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_63_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_63(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_RIGHT);
    tap_code16(KC_RIGHT);
    tap_code16(KC_RIGHT);
  }
  if(state->count > 3) {
    tap_code16(KC_RIGHT);
  }
}

uint8_t dance_63_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_63_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = dance_63_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_RIGHT); break;
    case SINGLE_HOLD: register_code16(LGUI(KC_RIGHT)); break;
    case DOUBLE_TAP: register_code16(KC_RIGHT); register_code16(KC_RIGHT); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT); register_code16(KC_RIGHT);
  }
}

void dance_63_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_RIGHT); break;
    case SINGLE_HOLD: unregister_code16(LALT(KC_RIGHT)); break;
    case DOUBLE_TAP: unregister_code16(KC_RIGHT); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
  }
  dance_state.step = 0;
}

// BKSL_HME
void on_bksl_hme(qk_tap_dance_state_t *state, void *user_data);
uint8_t bksl_hme_dance_step(qk_tap_dance_state_t *state);
void bksl_hme_finished(qk_tap_dance_state_t *state, void *user_data);
void bksl_hme_reset(qk_tap_dance_state_t *state, void *user_data);

void on_bksl_hme(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_BSLS);
    tap_code16(KC_BSLS);
    tap_code16(KC_BSLS);
  }
  if(state->count > 3) {
    tap_code16(KC_BSLS);
  }
}

uint8_t bksl_hme_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void bksl_hme_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = bksl_hme_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_BSLS); break;
    case SINGLE_HOLD: register_code16(KC_HOME); break;
    case DOUBLE_TAP: register_code16(KC_BSLS); register_code16(KC_BSLS); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLS); register_code16(KC_BSLS);
  }
}

void bksl_hme_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_BSLS); break;
    case SINGLE_HOLD: unregister_code16(KC_HOME); break;
    case DOUBLE_TAP: unregister_code16(KC_BSLS); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLS); break;
  }
  dance_state.step = 0;
}

// PIPE_END
void on_pipe_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t pipe_end_dance_step(qk_tap_dance_state_t *state);
void pipe_end_finished(qk_tap_dance_state_t *state, void *user_data);
void pipe_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_pipe_end(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 3) {
    tap_code16(KC_PIPE);
    tap_code16(KC_PIPE);
    tap_code16(KC_PIPE);
  }
  if(state->count > 3) {
    tap_code16(KC_PIPE);
  }
}

uint8_t pipe_end_dance_step(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void pipe_end_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = pipe_end_dance_step(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_PIPE); break;
    case SINGLE_HOLD: register_code16(KC_END); break;
    case DOUBLE_TAP: register_code16(KC_PIPE); register_code16(KC_PIPE); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_PIPE); register_code16(KC_PIPE);
  }
}

void pipe_end_reset(qk_tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_TAP: unregister_code16(KC_PIPE); break;
    case SINGLE_HOLD: unregister_code16(KC_END); break;
    case DOUBLE_TAP: unregister_code16(KC_PIPE); break;
    case DOUBLE_SINGLE_TAP: unregister_code16(KC_PIPE); break;
  }
  dance_state.step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [DANCE_01] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_01, dance_01_finished, dance_01_reset),
  [DANCE_02] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_02, dance_02_finished, dance_02_reset),
  [DANCE_03] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_03, dance_03_finished, dance_03_reset),
//  [DANCE_04] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_04, dance_04_finished, dance_04_reset),
  [DANCE_05] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_05, dance_05_finished, dance_05_reset),
  [DANCE_06] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_06, dance_06_finished, dance_06_reset),
  [DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),
  [DANCE_31] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_31, dance_31_finished, dance_31_reset),
  [DANCE_32] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_32, dance_32_finished, dance_32_reset),
//  [DANCE_33] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_33, dance_33_finished, dance_33_reset),
  [DANCE_54] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_54, dance_54_finished, dance_54_reset),
  [DANCE_55] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_55, dance_55_finished, dance_55_reset),
  [DANCE_56] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_56, dance_56_finished, dance_56_reset),
  [DANCE_57] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_57, dance_57_finished, dance_57_reset),
  [DANCE_58] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_58, dance_58_finished, dance_58_reset),
  [DANCE_59] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_59, dance_59_finished, dance_59_reset),
  [DANCE_60] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_60, dance_60_finished, dance_60_reset),
  [DANCE_63] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_63, dance_63_finished, dance_63_reset),
  [BKSL_HME] = ACTION_TAP_DANCE_FN_ADVANCED(on_bksl_hme, bksl_hme_finished, bksl_hme_reset),
  [PIPE_END] = ACTION_TAP_DANCE_FN_ADVANCED(on_pipe_end, pipe_end_finished, pipe_end_reset),
};

