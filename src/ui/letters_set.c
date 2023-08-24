/*********************
 *      INCLUDES
 *********************/
#include "shared_context.h"
#include "nbgl_debug.h"
#include "nbgl_use_case.h"

int userScore = 0;
//const char * const scoreFmt = "%2d / 24";
#define SCORE_FMT "%2d / 24"
char userScoreStr[8] = {0}; // "xx / 24"

const int guessIdx = 1;
const int scoreIdx = 2;
const int headerIdx = 3;
const int errorIdx = 4;

void resetGameSet(nbgl_container_t* screen) {
  nbgl_container_t* letterSet = screen->children[0];
  int lineNb = 0;

  while (lineNb < 6) {
    nbgl_container_t* letterLine = letterSet->children[lineNb];
    int letterNb = 0;

    while (letterNb < 5) {
      nbgl_button_t* letterButton = letterLine->children[letterNb];
      
      letterButton->text = " ";
      letterButton->innerColor = WHITE;
      letterButton->borderColor = LIGHT_GRAY;
      letterButton->foregroundColor = BLACK;
      letterButton->obj.area.width = 40;
      letterButton->obj.area.height = 40;
      letterButton->radius = 1;
      letterButton->obj.alignmentMarginX = 8;
      letterButton->fontId = BAGL_FONT_INTER_REGULAR_24px;

      ++letterNb;
    }
    ++lineNb;
  }

  nbgl_screenRedraw();
  nbgl_refresh();
}

static nbgl_button_t* createButton() {
  nbgl_button_t *backButton = nbgl_objPoolGet(BUTTON, 0);
  backButton->text = " ";
  backButton->innerColor = WHITE;
  backButton->borderColor = LIGHT_GRAY;
  backButton->foregroundColor = BLACK;
  backButton->obj.area.width = 40;
  backButton->obj.area.height = 40;
  backButton->radius = 1;
  backButton->obj.alignmentMarginX = 8;

  return backButton;
}

static nbgl_container_t* createCharLine(int index, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->obj.area.height = 40;
  container->layout = HORIZONTAL;
  container->nbChildren = nbLetters;
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);
  container->obj.alignment = TOP_LEFT;
  container->obj.alignmentMarginX = 76;
  container->obj.area.width = SCREEN_WIDTH - container->obj.alignmentMarginX;
  container->obj.alignmentMarginY = index * (40 + 12) + 80;

  int i;
  for (i = 0; i < nbLetters; ++i)
  {
    container->children[i] = (nbgl_obj_t*)createButton();
  }

  return container;
}

nbgl_container_t* createSet(int nbTries, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->obj.area.width = SCREEN_WIDTH;
  container->obj.area.height = 60 * nbTries;
  container->obj.alignment = TOP_MIDDLE;
  container->layout = VERTICAL;
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

  container->obj.area.width = SCREEN_WIDTH;
  container->obj.area.height = SCREEN_HEIGHT;
  container->obj.alignment = TOP_MIDDLE;
  container->nbChildren = 6; // letter set conatiner + guess button + score button + exit header + error text + keyboard
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);

  container->children[0] = (nbgl_obj_t*)createSet(nbTries, nbLetters);

  nbgl_button_t *guessButton = nbgl_objPoolGet(BUTTON, 0);
  guessButton->text = "Guess";
  guessButton->innerColor = BLACK;
  guessButton->borderColor = BLACK;
  guessButton->foregroundColor = WHITE;
  guessButton->obj.area.width = 174;
  guessButton->obj.area.height = 64;
  guessButton->radius = 4;
  guessButton->obj.alignment = TOP_LEFT;
  guessButton->obj.alignmentMarginX = 204;
  guessButton->obj.alignmentMarginY = 424;
  guessButton->obj.touchMask = (1<<TOUCHED);
  container->children[guessIdx] = (nbgl_obj_t*)guessButton;

  nbgl_button_t *scoreButton = nbgl_objPoolGet(BUTTON, 0);
  scoreButton->text = userScoreStr;
  scoreButton->innerColor = WHITE;
  scoreButton->borderColor = LIGHT_GRAY;
  scoreButton->foregroundColor = DARK_GRAY;
  scoreButton->obj.area.width = 174;
  scoreButton->obj.area.height = 64;
  scoreButton->radius = 4;
  scoreButton->obj.alignment = TOP_LEFT;
  scoreButton->obj.alignmentMarginX = 22;
  scoreButton->obj.alignmentMarginY = 424;
  container->children[scoreIdx] = (nbgl_obj_t*)scoreButton;
  snprintf(userScoreStr, sizeof(userScoreStr), SCORE_FMT, N_storage.userScore);

  nbgl_text_area_t *exitHeader = (nbgl_text_area_t *)nbgl_objPoolGet(TEXT_AREA,0);
  exitHeader->textColor = BLACK;
  exitHeader->text = "BIP Wordle";
  exitHeader->fontId = BAGL_FONT_INTER_SEMIBOLD_24px;
  exitHeader->obj.area.height = 80;
  exitHeader->obj.alignment = TOP_LEFT;
  exitHeader->obj.alignmentMarginX = 140;
  exitHeader->obj.area.width = SCREEN_WIDTH - exitHeader->obj.alignmentMarginX;
  exitHeader->obj.touchMask = (1<<TOUCHED);
  container->children[headerIdx] = (nbgl_obj_t*)exitHeader;

  nbgl_text_area_t *errorText = (nbgl_text_area_t *)nbgl_objPoolGet(TEXT_AREA, 0);
  errorText->textColor = BLACK;
  errorText->text = "";
  errorText->fontId = BAGL_FONT_INTER_REGULAR_24px;
  errorText->obj.area.width = 174;
  errorText->obj.area.height = 32;
  errorText->obj.alignment = TOP_MIDDLE;
  //errorText->obj.alignmentMarginX = 22;
  errorText->obj.alignmentMarginY = 388;
  container->children[errorIdx] = (nbgl_obj_t*)errorText;

  return container;
}
