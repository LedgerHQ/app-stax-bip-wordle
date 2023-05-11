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

static const char WIN[] = "You win !";

/**********************
 *  STATIC PROTOTYPES
 **********************/

void win(void) {
    PRINTF("win()\n");
    nbgl_useCaseStatus(WIN, true, ui_menu_main);
}

#endif
