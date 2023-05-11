
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
#include "glyphs.h"

// Index of the word to find in the wordList, generated randomly.
uint32_t wordIdx = 0;
static nbgl_obj_t **screenChildren;
static nbgl_text_area_t *text1;
static char * counter = "1";

void pickWord() {
  wordIdx = cx_rng_u32_range(0, WORDS_NB);
  PRINTF("Word to find: '%s' idx:%u length:%u\n", wordList[wordIdx], wordIdx,
      strlen(wordList[wordIdx]));
}

void touchCallback(nbgl_obj_t *obj, nbgl_touchType_t eventType) {
    static char * test = "42";
    char *ptr = counter;

    ptr[0] = ptr[0] + 1;
    //malloc(100);
    PRINTF("touchCallback: eventType = %d\n", eventType);
    nbgl_text_area_t *obj2 = (nbgl_text_area_t *)obj;
    //obj2->text[0]++;
    text1->alignmentMarginX++;
    PRINTF("touchCallback: eventType2 = %d\n", text1->alignmentMarginX);
    PRINTF("touchCallback: eventType3 = %s\n", &obj2->text);

      //counter[0]++;
                nbgl_redrawObject((nbgl_obj_t *)text1, NULL ,true);

  nbgl_screenRedraw();
      nbgl_refreshSpecial(BLACK_AND_WHITE_FAST_REFRESH);

  //nbgl_refresh();

    return;
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
  //stringa1 = ( char* )calloc( 100 + 1, sizeof( char ) );
  //sprintf(str, "%f", 42);   //make the number into string using sprintf function


  nbgl_screenSet(&screenChildren, 2, NULL, (nbgl_touchCallback_t)touchCallback);

  // screenChildren[0] = (nbgl_obj_t*)createGame(6);

  // nbgl_layoutDescription_t layoutDescription = {};
  // nbgl_layout_t *layout = nbgl_layoutGet(&layoutDescription);

  // nbgl_layoutKbd_t kbdInfo = {
  //   .lettersOnly = true,
  //   .casing = LOCKED_UPPER_CASE,
  //   .mode = MODE_LETTERS,
  //   .callback = selectLetterCb,
  // };
  // nbgl_layoutAddKeyboard(layout, &kbdInfo);
  // nbgl_layoutDraw(layout);

  nbgl_image_t *image = nbgl_objPoolGet(IMAGE, 0);
  image->foregroundColor = BLACK;
  image->buffer = &C_cookie;
  image->bpp = NBGL_BPP_1;
  image->alignment = BOTTOM_LEFT;
  image->width = C_cookie.width;
  image->height = C_cookie.height;
  image->alignmentMarginX = 200;
    image->alignmentMarginY = 100;
      image->touchMask = (1<<TOUCHED);
  screenChildren[1] = image;

  text1 = (nbgl_text_area_t*)nbgl_objPoolGet(TEXT_AREA, 0);
  text1->text = counter;
  text1->width = 100;
  text1->alignmentMarginX = 200;
    text1->alignmentMarginY = 100;
  screenChildren[0] = text1;
  PRINTF("touchCallback: eventType4 = %s\n", text1->text);

  nbgl_screenRedraw();
  nbgl_refresh();
}
