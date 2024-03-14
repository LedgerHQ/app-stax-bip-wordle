#pragma once

#ifndef _SHARED_CONTEXT_H_
#define _SHARED_CONTEXT_H_

#include <stdint.h>
#include "os_pic.h"

typedef struct internal_storage_t {
    int initialized;
    int userScore;
    //int16_t words[8];
} internal_storage_t;

#define N_storage (*(volatile internal_storage_t *) PIC(&N_storage_real))

extern const internal_storage_t N_storage_real;

#endif  // _SHARED_CONTEXT_H_
