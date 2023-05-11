
/*****************************************************************************
 *   Ledger App Hello-World.
 *   (c) 2023 Ledger SAS.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#ifdef HAVE_NBGL

/*********************
 *      INCLUDES
 *********************/
#include "menu.h"
#include "nbgl_debug.h"
#include "nbgl_use_case.h"
#include "glyphs.h"
// #include "../globals.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *      VARIABLES
 **********************/

static const int NB_PAGES = 3;

static const char STORY_1[] = 
    "Hi, my name is Elodie\n"
    "Brown. I'm afraid not\n"
    "being able to access\n"
    "all my cryptos due to\n"
    "mismanagement of my\n"
    "private key.\n"
    "A weirdo-hacker made a \n"
    "system to let me retrieve it,\n"
    "but I need your help!"
;
static const char STORY_2[] = 
    "If you accept, I’ll tell\n"
    "you about the risks of\n"
    "today’s world and the\n"
    "importance of proper money\n"
    "storage.\n"
    "\n"
    "Oh... Why did I leave my\n"
    "funds at SCB, that untrustworthy bank..\n"
    "Anyway, this hacker, hear what\\n"
    "he told me:\n"
    "All your 24 words are belong to us!"

;
// static const char STORY_2[] = 
    // "Oh... Why did I leave my funds at SCB, that untrustworthy bank.."
    // "Anyway, this hacker, hear what he told me:\n"
    // "All your 24 words are belong to us!\n"
// ;
static const char STORY_3[] = 
    "You know what it means, right? It’s my secret recovery phrase that I need you to find!"
    "Ok, I’ll assist you along this quest, just tap the “info” icon if needed."
    "Guess each word in 6 tries. Each guess must be a valid BIP-39 word. Tiles shade change to show guess proximity. Good luck!"
;

static const char SKIP[] = "Skip the story, let's play !";

/**********************
 *  STATIC PROTOTYPES
 **********************/

static bool displayStory(uint8_t page, nbgl_pageContent_t *content) {
    PRINTF("displayStory()\n");
    content->type = CENTERED_INFO;
    content->centeredInfo.icon = NULL;
    content->centeredInfo.text2 = NULL;
    content->centeredInfo.text3 = NULL;
    content->centeredInfo.style = NORMAL_INFO;
    content->centeredInfo.offsetY = 0;
    content->centeredInfo.onTop = false;
    if (page == 0) {
        content->centeredInfo.text1 = STORY_1;
    } else if (page == 1) {
        content->centeredInfo.text1 = STORY_2;
    } else if (page == 2) {
        content->centeredInfo.text1 = STORY_3;
    } else {
        return false;
    }
  // valid page so return true
  return true;
}

void preambule(void) {
    PRINTF("preambule()\n");
    // nbgl_useCaseReviewStart(NULL, STORY_1, NULL, SKIP, onStart, onStart);
    nbgl_useCaseRegularReview(0, NB_PAGES, SKIP, onStart, displayStory, onStart);
}

#endif
