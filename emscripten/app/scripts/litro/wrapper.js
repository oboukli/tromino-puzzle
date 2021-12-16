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

// SPDX-License-Identifier: MIT

// @ts-check

"use strict";

/**
 * @param {object} emModule
 * @param {number} order
 * @param {number} markX
 * @param {number} markY
 * @param {function} cb
 * @returns {void}
 */
// eslint-disable-next-line no-unused-vars
function solveTromino(emModule, order, markX, markY, cb) {
  const markArr = new Uint8Array(new Int32Array([markX, markY]).buffer);

  let stackPtr = emModule.stackSave();

  let markPtr = emModule.allocate(markArr, emModule.ALLOC_STACK);

  let funcPtr = emModule.addFunction(function (positionPtr, angle) {
    const position = {
      x: emModule.getValue(positionPtr, "i32"),
      y: emModule.getValue(positionPtr + 4, "i32")
    };

    cb(position, angle);
  }, "vid");

  emModule.ccall(
    "solve",
    "void",
    ["number", "number", "number", "number"],
    [order, markPtr, funcPtr]
  );

  emModule.removeFunction(funcPtr);
  funcPtr = 0;

  emModule.stackRestore(stackPtr);
  stackPtr = 0;
}