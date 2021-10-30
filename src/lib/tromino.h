/*
Copyright (c) 2021 Omar Boukli-Hacene. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* SPDX-License-Identifier: MIT */

#ifndef TROMINO_H
#define TROMINO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct trmn_position_struct {
    int x;
    int y;
} trmn_position_t;

typedef struct trmn_flip_struct {
    int x;
    int y;
} trmn_flip_t;

typedef void (*trmn_add_tromino_func)(trmn_position_t abspos, trmn_flip_t flip, void * state);

void trmn_solve_puzzle(int order, trmn_position_t mark, trmn_add_tromino_func add_tromino, void * state);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TROMINO_H */
