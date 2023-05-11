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

static int strpos(const char *str, char search) {
	int i = 0;
	if (str != NULL) {
		while (str[i]) {
			if (str[i] == search) {
				return i;
			}
			++i;
		}
	}
	return -1;
}

bool compareWords(nbgl_obj_t **screenChildren, int lineNumber, char *guessWord, char *wordToFind) {
  nbgl_container_t* screen = (nbgl_container_t*)screenChildren[0];
  nbgl_container_t* letterSet = screen->children[0];
  nbgl_container_t* letterLine = letterSet->children[lineNumber];

  int i = 0;
  int pos = -1;
  PRINTF("guess %s, to find %s\n", guessWord, wordToFind);
  while (guessWord[i]) {
    if (guessWord[i] == wordToFind[i]) {
      //Character found and position correct
      //Set letter innerColor to BLACK and foregroundColor to WHITE
      PRINTF("Character found and position correct %d\n", i);
      nbgl_button_t* letterButton = letterLine->children[i];
      letterButton->innerColor = BLACK;
      letterButton->foregroundColor = WHITE;
      letterButton->radius = 0;
    } 
    ++i;
  }
  i = 0;
  while (guessWord[i]) {
    pos = strpos(wordToFind, guessWord[i]);
    //Char must exist but do not overwrite a good guess
    if (pos >= 0 && guessWord[i] != wordToFind[i]) {
      //Character found and position incorrect
      //Set letter innerColor to DARK_GRAY
      PRINTF("Character found and position not correct %d\n", i);
      nbgl_button_t* letterButton = letterLine->children[i];
      letterButton->borderColor = BLACK;
      letterButton->fontId = BAGL_FONT_INTER_SEMIBOLD_24px;
      //letterButton->innerColor = LIGHT_GRAY;
    }
    ++i;
  }
  nbgl_screenRedraw();
  if (strcmp(guessWord, wordToFind) == 0) {
    return true;
  }
  return false;
}