/*
Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.

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

/**
 * @typedef {object} TrominoPuzzle
 * @property {number} order
 * @property {number} markX
 * @property {number} markY
 */

"use strict";

var _isSolverReady = false;
var _emModule;
var instancePromise;
var emModulePromise;

importScripts("litro-wasm.js", "wrapper.js");

/**
 * @returns {Promise}
 */
function initWasmAsync() {
  return WebAssembly.instantiateStreaming(
    fetch("litro-wasm.wasm"),
    {
      env: {
        "memory": new WebAssembly.Memory({ initial: 1, maximum: 1 })
      }
    }
  );
}

/**
 * @returns {Promise<object>}
 */
async function initEmscriptenModuleAsync() {
  /* global createLitroMod */
  return createLitroMod(/* optional default settings */);
}

/**
 * @param {TrominoPuzzle} tromino
 * @returns {Promise}
 */
async function handleSolveAsync({ order, markX, markY }) {
  if (!_isSolverReady) {
    const [, emModule] = await Promise.all([instancePromise, emModulePromise]);
    _emModule = emModule;
    _isSolverReady = true;
  }

  /* global solveTromino */
  solveTromino(
    _emModule,
    order,
    markX,
    markY,
    (/** @type {number} */ positionX,/** @type {number} */ positionY, /** @type {number} */ angle) => {
      self.postMessage({ x: positionX, y: positionY, angle });
    }
  );
}

/**
 * @param {"solve"} cmd
 * @param {TrominoPuzzle} payload
 * @returns {Promise}
 */
async function handleCommandAsync(cmd, payload) {
  if (cmd === "solve") {
    handleSolveAsync(payload);
  }
}

instancePromise = initWasmAsync();
emModulePromise = initEmscriptenModuleAsync();

self.addEventListener("message", async (e) => {
  if (e.origin !== "" || e.source !== null) {
    return;
  }

  await handleCommandAsync(e.data.cmd, e.data.payload);
}, false);
