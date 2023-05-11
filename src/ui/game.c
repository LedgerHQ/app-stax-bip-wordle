
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
#include "nbgl_touch.h"
#include "lcx_rng.h"
#include "words.h"
#include "string.h"

// Index of the word to find in the wordList, generated randomly.
uint32_t wordIdx = 0;
static nbgl_obj_t **screenChildren;

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

  nbgl_screenSet(&screenChildren, 1, NULL, NULL);

  screenChildren[0] = (nbgl_obj_t*)createGame(6);

  // create keyboard
  nbgl_keyboard_t* keyboard = nbgl_objPoolGet(KEYBOARD, 0);
  keyboard->alignmentMarginY = 1;
  keyboard->alignment = BOTTOM_MIDDLE;
  keyboard->borderColor = LIGHT_GRAY;
  keyboard->lettersOnly = true;
  keyboard->casing = LOCKED_UPPER_CASE;
  keyboard->mode = MODE_LETTERS;
  keyboard->callback = selectLetterCb;
  ((nbgl_container_t *)screenChildren[0])->children[2] = (nbgl_obj_t*)keyboard;

  nbgl_screenRedraw();
  nbgl_refresh();
}
