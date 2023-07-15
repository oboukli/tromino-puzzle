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

#include "validation.h"

#include <limits.h>
#include <stddef.h>

bool trmn_is_valid_order(int const order) {
    return (order > 1) && (order < 32769) && ((order & (order - 1)) == 0);
}

bool trmn_is_valid_coordinate(int const c, int const order) {
    return c >= 0 && c < order;
}

bool trmn_is_order_overflow_safe(int const order) {
    size_t volatile o = ((size_t)order * (size_t)order);

    return order > 0 && o <= INT_MAX;
}

bool trmn_is_valid_config(int const order, int const x, int const y) {
    return trmn_is_order_overflow_safe(order) && trmn_is_valid_order(order)
        && trmn_is_valid_coordinate(x, order)
        && trmn_is_valid_coordinate(y, order);
}
