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

// SPDX-License-Identifier: MIT

// @ts-check

/* exported solveTromino */

"use strict";

/**
 * @typedef {object} EmModule
 * @property {function(number, number, number, number): void} _solve
 * @property {function(function, string): number} addFunction
 * @property {function(number): void} removeFunction
 */

/**
 * @callback TrominoStepCallback
 * @param {number} x
 * @param {number} y
 * @param {number} flipX
 * @param {number} flipY
 * @returns {void}
 */

/**
 * @param {EmModule} emModule
 * @param {number} order
 * @param {number} markX
 * @param {number} markY
 * @param {TrominoStepCallback} cb
 * @returns {void}
 */
function solveTromino(emModule, order, markX, markY, cb) {
  const funcPtr = emModule.addFunction(cb, "viiii");

  emModule._solve(order, markX, markY, funcPtr);

  emModule.removeFunction(funcPtr);
}
