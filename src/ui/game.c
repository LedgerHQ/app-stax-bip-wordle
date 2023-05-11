
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
static const int nbTries = 6;
static const int nbLetters = WORD_MAX_LENGTH;

char userLetters[nbTries][nbLetters][2] = {0};

int userTries = 0;
int userWordIdx = 0;
char userWord[nbLetters + 1];

extern const int guessIdx;
extern const int headerIdx;
extern int userScore;
extern char userScoreStr[8];
#define SCORE_FMT "%2d / 24"

void pickWord() {
  wordIdx = cx_rng_u32_range(0, WORDS_NB);
  PRINTF("Word to find: '%s' idx:%u length:%u\n", wordList[wordIdx], wordIdx,
      strlen(wordList[wordIdx]));
}

static void selectLetterCb(char letter) {
  // Get word line
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  nbgl_container_t* letterSet = screen->children[0];
  nbgl_container_t* letterLine = letterSet->children[userTries];
  bool postInc = false;

  if (letter == 0x08) {
    // BACK BUTTON
    PRINTF("%s: BACK BUTTON\n", __func__);
    if (userWordIdx > 0) {
      --userWordIdx;
      letter = '\0';
      //postInc = false;
    } else {
      return;
    }
  } else {
    PRINTF("%s: '%c'\n", __func__, letter);
    if (userWordIdx < sizeof(userWord) - 1) {
      //letter = '\0';
      postInc = true;
    } else {
      return;
    }
  }

  // Get & update letter cell (button)
  nbgl_button_t* letterButton = letterLine->children[userWordIdx];
  letterButton->text = userLetters[userTries][userWordIdx];
  userLetters[userTries][userWordIdx][0] = letter;
  userLetters[userTries][userWordIdx][1] = '\0';
  userWord[userWordIdx] = letter;
  if (postInc)
    ++userWordIdx;
  PRINTF("User word '%s'\n", userWord);

  // DEBUG: pick a new word of each letter selected
  pickWord();

  nbgl_screenRedraw();
}

// function called when any of the container is touched
static void touchCallback(nbgl_obj_t *obj, nbgl_touchType_t eventType) {
  if (eventType != TOUCHED) {
    return;
  }
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  if (obj == screen->children[guessIdx]) {
    PRINTF("Guess\n");

    // TODO: If correct...
    if (userScore < 24) {
      ++userScore;
      snprintf(userScoreStr, sizeof(userScoreStr), SCORE_FMT, userScore);
      nbgl_screenRedraw();
    }
  } else if (obj == screen->children[headerIdx]) {
    PRINTF("Exit header\n");
    app_quit();
  } else {
    PRINTF("unknown object touched: %p\n", obj);
  }
}

void onStart(void) {
  PRINTF("%s\n", __func__);

  // Reset user entry
  memset(userWord, '\0', sizeof(userWord));
  userWordIdx = 0;
  userTries = 0;

  nbgl_screenSet(&screenChildren, 1, NULL, touchCallback);

  screenChildren[0] = (nbgl_obj_t*)createGame(nbTries, nbLetters);

  // create keyboard
  nbgl_keyboard_t* keyboard = nbgl_objPoolGet(KEYBOARD, 0);
  keyboard->alignmentMarginY = 1;
  keyboard->alignment = BOTTOM_MIDDLE;
  keyboard->borderColor = LIGHT_GRAY;
  keyboard->lettersOnly = true;
  keyboard->casing = LOCKED_UPPER_CASE;
  keyboard->mode = MODE_LETTERS;
  keyboard->callback = selectLetterCb;
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  screen->children[4] = (nbgl_obj_t*)keyboard;

  nbgl_screenRedraw();
  nbgl_refresh();
}
