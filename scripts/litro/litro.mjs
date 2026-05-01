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

import * as ltrGfx from "./gfx.mjs";

/**
 * @typedef {import("./gfx.mjs").Board} Board
 * @typedef {import("./gfx.mjs").ColorOptions} ColorOptions
 */

/**
 * @typedef {object} Tromino
 * @property {number} x
 * @property {number} y
 * @property {number} flipX
 * @property {number} flipY
 */

const dt = 125;

/** @type {number} */
let prevTimestamp;
let accumulator = 0;

/** @type {CanvasRenderingContext2D} */
let context;
/** @type {Worker} */
let solverWebWorker;
/** @type {number | null} */
let animationFrameRequestId;

/** @type {ColorOptions} */
let colorOptions = {
  altColor: "#000000",
  baseColor: "#ffffff",
  markColor: "#ff0000",
  trominoColor: "#00ff00",
  trominoOutlineColor: "#0000ff",
};
/** @type {Board} */
let boardModel;
/** @type {Array<Tromino>} */
let trominos;

let numPlacedTrominos = 0;
let trominoIdx = 0;

/**
 * @param {number} order
 * @returns {number}
 */
function calculateTrominoCount(order) {
  return (order ** 2 - 1) * 0.3333333333333333;
}

/**
 * @param {MessageEvent} e
 * @returns {void}
 */
function handleSolverMessage(e) {
  if (e.origin !== "" || e.source !== null) {
    return;
  }

  trominos[numPlacedTrominos] = e.data;
  numPlacedTrominos += 1;
}

/**
 * @returns {void}
 */
function initSolver() {
  if (solverWebWorker) {
    solverWebWorker.terminate();
  }

  solverWebWorker = new Worker(new URL("worker.mjs", import.meta.url), {
    type: "module",
  });

  solverWebWorker.addEventListener("message", handleSolverMessage, {
    capture: false,
    passive: true,
  });
}

/**
 * @returns {void}
 */
function cancelAnimation() {
  if (animationFrameRequestId !== null) {
    cancelAnimationFrame(animationFrameRequestId);
    animationFrameRequestId = null;
  }
}

/**
 * @param {number} order
 * @param {number} markX
 * @param {number} markY
 * @returns {void}
 */
function drawNewPuzzle(order, markX, markY) {
  boardModel = ltrGfx.createBoard(
    context,
    order,
    { x: markX, y: markY },
    colorOptions,
  );
  ltrGfx.drawBoard(boardModel);
  ltrGfx.drawMark(boardModel);
}

/**
 * @param {number} order
 * @param {number} markX
 * @param {number} markY
 * @returns {void}
 */
function change(order, markX, markY) {
  cancelAnimation();

  initSolver();

  boardModel = ltrGfx.createBoard(
    context,
    order,
    { x: markX, y: markY },
    colorOptions,
  );

  drawNewPuzzle(order, markX, markY);
}

/**
 * @param {number} timestamp
 * @returns {void}
 */
function step(timestamp) {
  const frameTime = timestamp - prevTimestamp;
  prevTimestamp = timestamp;

  accumulator += frameTime;

  if (accumulator >= dt) {
    accumulator -= dt;
    if (numPlacedTrominos > trominoIdx) {
      const { x, y, flipX, flipY } = /** @type {Tromino} */ (
        trominos[trominoIdx]
      );
      trominoIdx += 1;
      ltrGfx.drawTromino(boardModel, x, y, flipX, flipY);
    }
  }

  animationFrameRequestId = requestAnimationFrame(step);
}

/**
 * @param {number} order
 * @param {number} markX
 * @param {number} markY
 * @returns {void}
 */
function play(order, markX, markY) {
  cancelAnimation();

  drawNewPuzzle(order, markX, markY);

  const numTrominos = calculateTrominoCount(order);
  if (!Array.isArray(trominos) || numTrominos !== trominos.length) {
    trominos = new Array(numTrominos);
  }

  numPlacedTrominos = 0;
  trominoIdx = 0;

  solverWebWorker.postMessage({
    cmd: "solve",
    payload: { order, markX, markY },
  });

  prevTimestamp = performance.now();
  animationFrameRequestId = requestAnimationFrame(step);
}

/**
 * @param {ColorOptions?} options
 * @returns {void}
 */
function init(options) {
  if (options != null) {
    colorOptions = options;
  }

  const litroCanvasElement = /** @type {HTMLCanvasElement} */ (
    document.getElementById("litroCanvas")
  );

  const ctx = litroCanvasElement.getContext("2d");
  if (ctx === null) {
    throw new Error("Could not get 2D context.");
  }
  context = ctx;

  initSolver();
}

export { init, play, change };
