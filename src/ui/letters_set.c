/*********************
 *      INCLUDES
 *********************/
#include "nbgl_debug.h"
#include "nbgl_use_case.h"
// #include "nbgl_touch.h"
// #include "lcx_rng.h"
// #include "glyphs.h"
// #include "menu.h"
// #include "os.h"
// #include "io.h"

static nbgl_button_t* createButton(char *letter, int x, int y) {
  nbgl_button_t *backButton = nbgl_objPoolGet(BUTTON, 0);
  backButton->text = letter;
  backButton->innerColor = WHITE;
  backButton->borderColor = LIGHT_GRAY;
  backButton->foregroundColor = BLACK;
  backButton->width = 40;
  backButton->height = 40;
  backButton->radius = 1;
  backButton->alignmentMarginX = 8;
  //backButton->alignmentMarginY = y;


// nbgl_button_t backButton = {
//     .type = BUTTON,                           // Type of object, MANDATORY
//     .innerColor = WHITE,                      // Color used inside of the button, MANDATORY
//     .borderColor = LIGHT_GRAY,                // Color used for border, MANDATORY
//     .foregroundColor = BLACK,                 // Color used for text and/or icon, MANDATORY
//     .width = 128,                             // Width in pixels, MANDATORY
//     .height = 64,                             // Height in pixels, MANDATORY
//     .radius = 32,                             // Radius of corners in pixels, can be null
//     .text = "Back",                           // Text of the button, if NULL, only an icon
//     .fontId = BAGL_FONT_INTER_REGULAR_24,     // Font used for text, if text is not null
//     .icon = &C_leftArrow32px,                 // Icon of the button, if NULL, only text
//     .alignmentMarginX = 20,                   // Horizontal margin (see layout & alignment)
//     .alignmentMarginY = 20,                   // Vertical margin (see layout & alignment)
//     .alignment = TOP_LEFT,                    // Type of alignment (see layout & alignment)
//     .alignTo = NULL,                          // Alignment reference, if NULL, use parent (see layout & alignment)
//     .touchMask = (1<<VALUE_CHANGED)           // Types of touchscreen events that we want to receive
//     };

  return backButton;
}

static nbgl_container_t* createCharLine(int index, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->width = SCREEN_WIDTH;
  container->height = 40;
  container->alignment = TOP_LEFT;
  container->layout = HORIZONTAL;
  container->touchMask = (1<<TOUCHED);
  container->nbChildren = nbLetters;
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);
  container->alignmentMarginY = index * 44;

  int i;
  for (i = 0; i < nbLetters; ++i)
  {
    container->children[i] = (nbgl_obj_t*)createButton("B", 1, 1);
  }

  return container;
}

nbgl_container_t* createSet(int nbTries, int nbLetters) {
  nbgl_container_t *container = nbgl_objPoolGet(CONTAINER, 0);

  container->width = SCREEN_WIDTH;
  container->height = 44 * nbTries;
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
  container->nbChildren = 3; // letter set conatiner + guess button + keyboard
  container->children = (nbgl_obj_t**)nbgl_containerPoolGet(container->nbChildren, 0);
  
  container->children[0] = (nbgl_obj_t*)createSet(nbTries, nbLetters);

  nbgl_button_t *guessButton = nbgl_objPoolGet(BUTTON, 0);
  guessButton->text = "Guess";
  guessButton->innerColor = BLACK;
  guessButton->borderColor = BLACK;
  guessButton->foregroundColor = WHITE;
  
  guessButton->width = 128;
  guessButton->height = 64;
  guessButton->radius = 4;
  guessButton->alignment = CENTER;
  //guessButton->alignmentMarginY = 300;
  
  container->children[1] = (nbgl_obj_t*)guessButton;

  return container;
}
