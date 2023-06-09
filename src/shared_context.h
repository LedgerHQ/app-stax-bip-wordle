#pragma once

#ifndef _SHARED_CONTEXT_H_
#define _SHARED_CONTEXT_H_

#include <stdint.h>
#include "os_pic.h"

typedef struct internalStorage_t {
    int initialized;
    int userScore;
    //int16_t words[8];
} internalStorage_t;

#define N_storage (*(volatile internalStorage_t *) PIC(&N_storage_real))

extern const internalStorage_t N_storage_real;

#endif  // _SHARED_CONTEXT_H_