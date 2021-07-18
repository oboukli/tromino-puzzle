/*
 * Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
 *
 * Distributed under an MIT-style license that can be
 * found in the LICENSE file.
 */

#ifndef tromino_h
#define tromino_h

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

typedef void (*add_tromino_func)(position abspos, rotation rot, void * state);

void solve_tromino_puzzle(int order, position mark, add_tromino_func add_tromino, void * state);

#ifdef __cplusplus
}
#endif

#endif /* tromino_h */
