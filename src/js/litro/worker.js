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

"use strict";

/// <reference path="wrapper.js" />

/**
 * @typedef {object} TrominoPuzzle
 * @property {number} order
 * @property {number} markX
 * @property {number} markY
 */

let _isSolverReady = false;

/** @type {EmModule} */
let _emModule;
/** @type {PromiseLike<object>} */
let instancePromise;
/** @type {Promise<EmModule>} */
let emModulePromise;

importScripts("litro-wasm.js", "wrapper.js");

/**
 * @returns {PromiseLike<object>}
 */
function initWasmAsync() {
  return WebAssembly.instantiateStreaming(fetch("litro-wasm.wasm"), {
    env: {
      memory: new WebAssembly.Memory({ initial: 1, maximum: 1 }),
    },
  });
}

/**
 * @returns {Promise<EmModule>}
 */
function initEmscriptenModuleAsync() {
  /* global createLitroMod */
  return createLitroMod(/* optional default settings */);
}

/**
 * @param {TrominoPuzzle} tromino
 * @returns {Promise<void>}
 */
async function handleSolveAsync({ order, markX, markY }) {
  if (!_isSolverReady) {
    const [, emModule] = await Promise.all([instancePromise, emModulePromise]);
    _emModule = emModule;
    _isSolverReady = true;
  }

  /* global solveTromino */
  solveTromino(_emModule, order, markX, markY, (x, y, flipX, flipY) => {
    self.postMessage({ x, y, flipX, flipY });
  });
}

/**
 * @param {"solve"} cmd
 * @param {TrominoPuzzle} payload
 * @returns {Promise<void>}
 */
async function handleCommandAsync(cmd, payload) {
  if (cmd === "solve") {
    await handleSolveAsync(payload);
  }

  return Promise.resolve();
}

instancePromise = initWasmAsync();
emModulePromise = initEmscriptenModuleAsync();

self.addEventListener(
  "message",
  (event) => {
    if (event.origin !== "" || event.source !== null) {
      return;
    }
    (async (e) => {
      await handleCommandAsync(e.data.cmd, e.data.payload);
    })(event).catch(console.error);
  },
  false
);
