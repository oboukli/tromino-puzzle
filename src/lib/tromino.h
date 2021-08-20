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

typedef struct position_struct {
    int x;
    int y;
} position_t;

typedef struct flip_struct {
    int x;
    int y;
} flip_t;

typedef void (*add_tromino_func)(position_t abspos, flip_t flip, void * state);

void solve_tromino_puzzle(int order, position_t mark, add_tromino_func add_tromino, void * state);

#ifdef __cplusplus
}
#endif

#endif /* tromino_h */
