
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
#include "lcx_rng.h"
#include "words.h"
#include "string.h"

// Index of the word to find in the wordList, generated randomly.
uint32_t wordIdx = 0;

void pickWord() {
  wordIdx = cx_rng_u32_range(0, WORDS_NB);
  PRINTF("Word to find: '%s' idx:%u length:%u\n", wordList[wordIdx], wordIdx,
      strlen(wordList[wordIdx]));
}

static void selectLetterCb(char letter) {
  if (letter == 0x08) {
    // BACK BUTTON
    PRINTF("%s: BACK BUTTON\n", __func__);
  } else {
    PRINTF("%s: '%c'/0x%x\n", __func__, letter, letter);
  }

  // DEBUG: pick a new word of each letter selected
  pickWord();
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
