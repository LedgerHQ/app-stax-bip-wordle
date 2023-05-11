/*********************
 *      INCLUDES
 *********************/
#include "nbgl_debug.h"
#include "nbgl_use_case.h"

int userScore = 0;
#define SCORE_FMT "%2d / 24"
char userScoreStr[8] = {0}; // "xx / 24"

static nbgl_button_t* createButton() {
  nbgl_button_t *backButton = nbgl_objPoolGet(BUTTON, 0);
  backButton->text = " ";
  backButton->innerColor = WHITE;
  backButton->borderColor = LIGHT_GRAY;
  backButton->foregroundColor = BLACK;
  backButton->width = 40;
  backButton->height = 40;
  backButton->radius = 1;
  backButton->alignmentMarginX = 8;

  return backButton;
}

static nbgl_container_t* createCharLine(int index, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->height = 40;
  container->layout = HORIZONTAL;
  container->touchMask = (1<<TOUCHED);
  container->nbChildren = nbLetters;
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);
  container->alignment = TOP_LEFT;
  container->alignmentMarginX = 84;
  container->width = SCREEN_WIDTH - container->alignmentMarginX;
  container->alignmentMarginY = index * (40 + 12) + 80;

  int i;
  for (i = 0; i < nbLetters; ++i)
  {
    container->children[i] = (nbgl_obj_t*)createButton();
  }

  return container;
}

nbgl_container_t* createSet(int nbTries, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->width = SCREEN_WIDTH;
  container->height = 60 * nbTries;
  container->alignment = TOP_MIDDLE;
  container->layout = VERTICAL;
  container->touchMask = (1<<TOUCHED);
  container->nbChildren = nbTries;
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);

  int i;
  for (i = 0; i < nbTries; ++i)
  {
    container->children[i] = (nbgl_obj_t*)createCharLine(i, nbLetters);
  }

  return container;
}

nbgl_container_t* createGame(int nbTries, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->width = SCREEN_WIDTH;
  container->height = SCREEN_HEIGHT;
  container->alignment = TOP_MIDDLE;
  //container->layout = VERTICAL;
  container->touchMask = (1<<TOUCHED);
  container->nbChildren = 4; // letter set conatiner + guess button + score button + keyboard
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);
  
  container->children[0] = (nbgl_obj_t*)createSet(nbTries, nbLetters);

  nbgl_button_t *guessButton = nbgl_objPoolGet(BUTTON, 0);
  guessButton->text = "Guess";
  guessButton->innerColor = BLACK;
  guessButton->borderColor = BLACK;
  guessButton->foregroundColor = WHITE;
  guessButton->width = 174;
  guessButton->height = 64;
  guessButton->radius = 4;
  guessButton->alignment = TOP_LEFT;
  guessButton->alignmentMarginX = 204;
  guessButton->alignmentMarginY = 405;
  container->children[1] = (nbgl_obj_t*)guessButton;

  nbgl_button_t *scoreButton = nbgl_objPoolGet(BUTTON, 0);
  scoreButton->text = userScoreStr;
  scoreButton->innerColor = WHITE;
  scoreButton->borderColor = LIGHT_GRAY;
  scoreButton->foregroundColor = DARK_GRAY;
  scoreButton->width = 174;
  scoreButton->height = 64;
  scoreButton->radius = 4;
  scoreButton->alignment = TOP_LEFT;
  scoreButton->alignmentMarginX = 22;
  scoreButton->alignmentMarginY = 405;
  container->children[2] = (nbgl_obj_t*)scoreButton;

  snprintf(userScoreStr, sizeof(userScoreStr), SCORE_FMT, userScore);

  return container;
}
