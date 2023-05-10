
/**
 * @file game.c
 * @brief Entry point of game
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "nbgl_debug.h"
#include "nbgl_layout.h"

static void selectLetterCb(char letter) {
  if (letter == 0x08) {
    // BACK BUTTON
    PRINTF("%s: BACK BUTTON\n", __func__);
  } else {
    PRINTF("%s: '%c'/0x%x\n", __func__, letter, letter);
  }
}

void onStart(void) {
  PRINTF("%s\n", __func__);
  nbgl_layoutDescription_t layoutDescription = {};
  nbgl_layout_t *layout = nbgl_layoutGet(&layoutDescription);

  nbgl_layoutKbd_t kbdInfo = {
    .lettersOnly = true,
    .casing = LOCKED_UPPER_CASE,
    .mode = MODE_LETTERS,
    .callback = selectLetterCb,
  };
  nbgl_layoutAddKeyboard(layout, &kbdInfo);
  nbgl_layoutDraw(layout);
}
