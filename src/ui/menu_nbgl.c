
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

#include "shared_context.h"
#include "os.h"
#include "glyphs.h"
#include "../globals.h"
#include "menu.h"
#include "nbgl_fonts.h"
#include "nbgl_front.h"
#include "nbgl_debug.h"
#include "nbgl_page.h"
#include "nbgl_use_case.h"

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

/**********************
 *  STATIC PROTOTYPES
 **********************/

void app_quit(void) {
    PRINTF("EXIT\n");
    // exit app here
    os_sched_exit(0);
}

void ui_menu_main(void) {
    PRINTF("app_main()\\\\n");
  nbgl_useCaseHomeExt("BIP Wordle", &C_icon_32, "Wordle game on BIP-39\ndictionnary", false, "Start", N_storage.initialized == 0x01 && N_storage.userScore > 0 ? onStart : preambule, NULL, app_quit);
}

// 'About' menu
static const char* const INFO_TYPES[] = {"Version", "Developer"};
static const char* const INFO_CONTENTS[] = {APPVERSION, "Ledger HK7 - Game on Stax"};

static bool nav_callback(uint8_t page, nbgl_pageContent_t* content) {
    UNUSED(page);
    content->type = INFOS_LIST;
    content->infosList.nbInfos = 2;
    content->infosList.infoTypes = (const char**) INFO_TYPES;
    content->infosList.infoContents = (const char**) INFO_CONTENTS;
    return true;
}

void ui_menu_about() {
    nbgl_useCaseSettings(APPNAME, 0, 1, false, ui_menu_main, nav_callback, NULL);
}

#endif
