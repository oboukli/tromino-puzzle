/*
Copyright (c) 2025 Omar Boukli-Hacene. All rights reserved.

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

#ifndef TROMINO_CORE_TROMINO_H_
#define TROMINO_CORE_TROMINO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void (*trmn_add_tromino_func_t)(
    int px, int py, int fx, int fy, void* state
);

void trmn_solve_puzzle(
    int order, int mx, int my, trmn_add_tromino_func_t add_tromino, void* state
);

void trmn_request_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TROMINO_CORE_TROMINO_H_ */
