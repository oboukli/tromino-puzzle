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

"use strict";

// eslint-disable-next-line no-unused-vars
const litro = (function (window, document, ltrGfx) {
  /**
   * @typedef {object} Tromino
   * @property {number} x
   * @property {number} y
   * @property {number} angle
   */

  const delayBase = 67;
  const trominoImgSrc = "images/tromino.svg";

  /** @type {CanvasRenderingContext2D} */
  let context;
  /** @type {Worker} */
  let solverWebWorker;
  /** @type {number} */
  let animationFrameRequestId;
  /** @type {HTMLImageElement} */
  let trominoImg;

  let options;
  let boardModel;
  /** @type {Tromino[]} */
  let trominos;

  /** @type {number} */
  let stepIdx;
  /** @type {number} */
  let start;

  /**
   * @param {MessageEvent} e
   * @returns {void}
   */
  function handleSolverMessage(e) {
    if (e.origin !== "" || e.source !== null) {
      return;
    }

    trominos.push(e.data);
  }

  /**
   * @returns {void}
   */
  function initSolver() {
    if (solverWebWorker) {
      solverWebWorker.terminate();
    }

    solverWebWorker = new Worker("scripts/litro/worker.js");

    solverWebWorker.addEventListener("message", handleSolverMessage,
      { capture: false, passive: true });
  }

  /**
   * @returns {void}
   */
  function initOptions() {
    options = {
      baseColor: "#4e7da6",
      altColor: "#012340",
      markColor: "#8c1b1b"
    };
  }

  /**
   * @returns {Promise}
   */
  function initResourcesAsync() {
    trominoImg = new Image();
    trominoImg.src = trominoImgSrc;

    return trominoImg.decode();
  }

  /**
   * @param {number} order
   * @param {number} markX
   * @param {number} markY
   * @returns {void}
   */
  function drawNewPuzzle(order, markX, markY) {
    boardModel = ltrGfx.createBoard(context, trominoImg, order, { x: markX, y: markY }, options);
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
    cancelAnimationFrame(animationFrameRequestId);
    initSolver();

    boardModel = ltrGfx.createBoard(context, trominoImg, order, { x: markX, y: markY }, options);

    drawNewPuzzle(order, markX, markY);
  }

  /**
   * @param {number} timestamp
   * @returns {void}
   */
  function step(timestamp) {
    const elapsed = timestamp - start;
    if (Array.isArray(trominos) && trominos.length > 0) {
      if (elapsed > stepIdx * delayBase) {
        stepIdx += 1;
        let { x, y, angle } = trominos.shift();
        ltrGfx.drawTromino(boardModel, x, y, angle);
      }
    }

    animationFrameRequestId = window.requestAnimationFrame(step);
  }

  /**
   * @param {number} order
   * @param {number} markX
   * @param {number} markY
   * @returns {void}
   */
  function play(order, markX, markY) {
    if (animationFrameRequestId !== 0) {
      cancelAnimationFrame(animationFrameRequestId);
      animationFrameRequestId = 0;
      drawNewPuzzle(order, markX, markY);
    }

    trominos = new Array();

    stepIdx = 0;
    start = performance.now();

    solverWebWorker.postMessage({ cmd: "solve", payload: { order, markX, markY } });

    animationFrameRequestId = window.requestAnimationFrame(step);
  }

  /**
   * @returns {Promise}
   */
  async function initAsync() {
    /** @type {HTMLCanvasElement} */
    const litroCanvasElement = document.getElementById("litroCanvas");

    context = litroCanvasElement.getContext("2d");
    initSolver();
    initOptions();
    await initResourcesAsync();
  }

  return {
    initAsync,
    play,
    change
  };
}(window, document, /* global ltrGfx */ ltrGfx));
