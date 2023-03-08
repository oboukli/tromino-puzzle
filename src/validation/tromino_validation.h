/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.

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

#ifndef VALIDATION_TROMINO_VALIDATION_H
#define VALIDATION_TROMINO_VALIDATION_H

#include <stdbool.h>

#ifdef __cplusplus

extern "C" {
#endif /* __cplusplus */

bool trmn_is_valid_order(const int order);

bool trmn_is_valid_coordinate(const int c, const int order);

bool trmn_is_order_overflow_safe(const int order);

bool trmn_is_valid_config(const int order, const int x, const int y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VALIDATION_TROMINO_VALIDATION_H */
