/*
 * Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
 *
 * Distributed under an MIT-style license that can be
 * found in the LICENSE file.
 */

#ifndef trimino_h
#define trimino_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct position_struct {
    int x;
    int y;
} position;

typedef struct rotation_struct {
    int x;
    int y;
} rotation;

typedef void (*add_trimino_func)(position abspos, rotation rot, void * state);

void solve_trimino_puzzle(int order, position mark, add_trimino_func add_trimino, void * state);

#ifdef __cplusplus
}
#endif

#endif /* trimino_h */
