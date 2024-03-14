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
#include "nbgl_layout.h"
#include "nbgl_use_case.h"
#include "glyphs.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct GamerIdContext_s {
    nbgl_layoutTagValue_t tagValuePair;
    nbgl_layout_t         modalLayout;
} GamerIdContext_t;

/**********************
 *      MACROS
 **********************/

/**********************
 *      VARIABLES
 **********************/
static const char GAMER_ID_URL[] = "http://localhost:3000/";
static const char GAME_ID_URL[] = "http://localhost:3000/";
static const char SCORE_URL[] = "http://localhost:3000/data?gameId=Wordle&trials=15&success=true";
static GamerIdContext_t gamerIdContext;

/**********************
 *  STATIC PROTOTYPES
 **********************/

void ui_qrcode_gamer_id(void) {
    PRINTF("ui_qrcode_gamer_id")
    // display the address as QR Code
    nbgl_layoutDescription_t layoutDescription = {.modal            = true,
                                                  .withLeftBorder   = true,
                                                  .onActionCallback = NULL,
                                                  // .onActionCallback = &addressLayoutTouchCallbackQR,
                                                  .tapActionText    = NULL};

    gamerIdContext.modalLayout = nbgl_layoutGet(&layoutDescription);
    nbgl_layoutQRCode_t qrCode
        = {.url      = SCORE_URL,
           .text1    = NULL,
           .text2    = SCORE_URL,  // display as gray text
           };
        // = {.url      = gamerIdContext.tagValuePair.value,
        //    .text1    = NULL,
        //    .text2    = gamerIdContext.tagValuePair.value,  // display as gray text
        //    };
           // .centered = true,
           // .offsetY  = 0};
    nbgl_layoutAddQRCode(gamerIdContext.modalLayout, &qrCode);

// #ifdef TARGET_STAX
    // nbgl_layoutAddBottomButton(
    //     gamerIdContext.modalLayout, &CLOSE_ICON, 0, false, TUNE_TAP_CASUAL);
// #else   // TARGET_STAX
    nbgl_layoutAddFooter(gamerIdContext.modalLayout, "Close", 0, TUNE_TAP_CASUAL);
// #endif  // TARGET_STAX
    nbgl_layoutDraw(gamerIdContext.modalLayout);
    nbgl_refresh();
}

void ui_qrcode_app_id(void) {

}

void ui_qrcode_data(void) {

}

#endif
