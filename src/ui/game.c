
/**
 * @file game.c
 * @brief Entry point of game
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "shared_context.h"
#include "nbgl_debug.h"
#include "nbgl_layout.h"
#include "nbgl_touch.h"
#include "lcx_rng.h"
#include "words.h"
#include "string.h"
#include <stdbool.h>
#include <stdint.h>
#include "nbgl_types.h"

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
extern const int scoreIdx;
extern const int headerIdx;
extern const int errorIdx;

extern int userScore;
extern char userScoreStr[8];
#define SCORE_FMT "%2d / 24"

void pickWord() {
  wordIdx = cx_rng_u32_range(0, WORDS_NB);
  PRINTF("Word to find: '%s' idx:%u length:%u\n", wordList[wordIdx], wordIdx,
      strlen(wordList[wordIdx]));
}

void onGuessPress() {
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  nbgl_button_t* scoreButton = screen->children[scoreIdx];
  nbgl_text_area_t* errorText = screen->children[errorIdx];

  if (userWordIdx < 5) {
    io_seproxyhal_play_tune(TUNE_ERROR);
    return;
  }

  if (checkIfCorrectWord(userWord) != true) {
    PRINTF("incorrect\n");
    io_seproxyhal_play_tune(TUNE_ERROR);
    errorText->text = "Unknown word";
    nbgl_redrawObject((nbgl_obj_t *)errorText, NULL, false);
    nbgl_refreshSpecial(FULL_COLOR_PARTIAL_REFRESH);
    return;
  };

  if (compareWords(screenChildren, userTries, userWord, wordList[wordIdx]) == true) {
    PRINTF("finished\n");
    io_seproxyhal_play_tune(TUNE_SUCCESS);
    //WIN
    resetGameSet(screen);
    userTries = 0;
    pickWord();
    if (userScore < 24) {
      int newUserScore = N_storage.userScore + 1;
      nvm_write((void*) &N_storage.userScore, (void*) &newUserScore, sizeof(int));
      //++userScore;
      snprintf(userScoreStr, sizeof(userScoreStr), SCORE_FMT, N_storage.userScore);
      nbgl_redrawObject((nbgl_obj_t *)scoreButton, NULL, false);
    }
  } else {
    if (userTries >= 5) {
      PRINTF("lost\n");
      //LOST
      lost();
      return;
    }
    userTries++;
  }

  memset(userWord, '\0', sizeof(userWord));
  userWordIdx = 0;
  //nbgl_screenRedraw();
  //nbgl_refreshSpecial(FULL_COLOR_PARTIAL_REFRESH);
  PRINTF("playsound\n");
  io_seproxyhal_play_tune(TUNE_TAP_NEXT);
}

static void selectLetterCb(char letter) {
  io_seproxyhal_play_tune(TUNE_TAP_CASUAL);

  // Get word line
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  nbgl_container_t* letterSet = screen->children[0];
  nbgl_container_t* letterLine = letterSet->children[userTries];
  nbgl_text_area_t* errorText = screen->children[errorIdx];
  bool postInc = false;
  
  io_seproxyhal_play_tune(TUNE_TAP_CASUAL);

  if (strcmp(errorText->text, "") != 0) {
    PRINTF("cleaning error\n");
    errorText->text = "";
    nbgl_redrawObject((nbgl_obj_t *)errorText, NULL, false);
  }

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

  nbgl_redrawObject((nbgl_obj_t *)letterButton, NULL, false);
  nbgl_refreshSpecial(FULL_COLOR_PARTIAL_REFRESH);
  //nbgl_refresh();
  //nbgl_screenRedraw();
}

// function called when any of the container is touched
static void touchCallback(nbgl_obj_t *obj, nbgl_touchType_t eventType) {
  if (eventType != TOUCHED) {
    return;
  }
  PRINTF("Touched\n");
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  if (obj == screen->children[guessIdx]) {
    PRINTF("Guess\n");

    onGuessPress();
    // TODO: If correct...
    // if (userScore < 24) {
    //   ++userScore;
    //   snprintf(userScoreStr, sizeof(userScoreStr), SCORE_FMT, userScore);
    //   nbgl_screenRedraw();
    // }
  } else if (obj == screen->children[headerIdx]) {
    PRINTF("Exit header\n");
    app_quit();
  } else {
    PRINTF("unknown object touched: %p\n", obj);
  }
}

void onStart(void) {
  PRINTF("%s\n", __func__);

  if (N_storage.initialized != 0x01) {
      PRINTF("init1\n");
        internal_storage_t storage;
        storage.initialized = 0x01;
        storage.userScore = 0;
        nvm_write((void*) &N_storage, (void*) &storage, sizeof(internal_storage_t));
  } else {
          PRINTF("save already init\n");
        // internalStorage_t storage;
        // storage.dataAllowed = 0x00;
        // storage.initialized = 0x01;
        // storage.userScore = 44;
        // nvm_write((void*) &N_storage, (void*) &storage, sizeof(internalStorage_t));

        // int newUserScore = 42;
        // storage.dataAllowed = 0x00;
        // storage.initialized = 0x01;
        // storage.userScore = 44;
        // nvm_write((void*) &N_storage, (void*) &storage, sizeof(internalStorage_t));
        // nvm_write((void *) N_u2f.privateHmacKey, (void *) key, sizeof(N_u2f.privateHmacKey));
  }

  pickWord();

  // Reset user entry
  memset(userWord, '\0', sizeof(userWord));
  userWordIdx = 0;
  userTries = 0;

  nbgl_screenSet(&screenChildren, 1, NULL, touchCallback);

  screenChildren[0] = (nbgl_obj_t*)createGame(nbTries, nbLetters);

  // create keyboard
  nbgl_keyboard_t* keyboard = (nbgl_keyboard_t *) nbgl_objPoolGet(KEYBOARD, 0);
  keyboard->obj.alignmentMarginY = 1;
  keyboard->obj.alignment = BOTTOM_MIDDLE;
  keyboard->borderColor = LIGHT_GRAY;
  keyboard->lettersOnly = true;
  keyboard->casing = LOCKED_UPPER_CASE;
  keyboard->mode = MODE_LETTERS;
  keyboard->callback = selectLetterCb;
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  screen->children[5] = (nbgl_obj_t*)keyboard;

  nbgl_screenRedraw();
  nbgl_refresh();
}
