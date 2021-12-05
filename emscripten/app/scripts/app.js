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

(async function (window, document, ltrGfx) {
  /**
   * @typedef {object} Tromino
   * @property {number} x
   * @property {number} y
   * @property {number} angle
   */

  const delayBase = 68;
  const trominoImgSrc = "images/tromino.svg";

  let order = 32;
  let markX = 11;
  let markY = 17;

  let puzzleEditorFormElement;
  let canvasElement;
  let orderElement;
  let orderIndicatorElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;

  let context;
  let solverWebWorker;
  let animationFrameRequestId;
  let trominoImg;

  let options;
  let boardModel;
  let trominos;

  let stepIdx;
  let start;

  /**
   * @param {number} n
   * @returns {number}
   */
  function calcOrder(n) {
    return 2 << n;
  }

  /**
   * @param {Tromino} tromino
   * @returns {void}
   */
  function handleSolverMessage(tromino) {
    trominos.push(tromino);
  }

  /**
   * @returns {void}
   */
  function drawNewPuzzle() {
    boardModel = ltrGfx.createBoard(context, trominoImg, order, { x: markX, y: markY }, options);
    ltrGfx.drawBoard(boardModel);
    ltrGfx.drawMark(boardModel);
  }

  /**
   * @param {number} max
   */
  function setInputValueBounds(max) {
    markXElement.max = max.toString();
    markYElement.max = max.toString();
  }

  /**
   * @returns {void}
   */
  function initSolver() {
    if (solverWebWorker) {
      solverWebWorker.terminate();
    }

    solverWebWorker = new Worker("scripts/litro/worker.js");

    solverWebWorker.addEventListener("message", (e) => {
      handleSolverMessage(e.data);
    }, false);
  }

  /**
   * @returns {void}
   */
  function changePuzzle() {
    cancelAnimationFrame(animationFrameRequestId);
    initSolver();

    orderIndicatorElement.textContent = order.toString();

    setInputValueBounds(order - 1);

    markX = Math.min(parseInt(markXElement.max, 10), markX);
    markY = Math.min(parseInt(markYElement.max, 10), markY);

    markXElement.value = markX.toString();
    markYElement.value = markY.toString();

    boardModel = ltrGfx.createBoard(context, trominoImg, order, { x: markX, y: markY }, options);

    drawNewPuzzle();
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
   * @returns {void}
   */
  function startSolveAsync() {
    if (animationFrameRequestId !== 0) {
      cancelAnimationFrame(animationFrameRequestId);
      animationFrameRequestId = 0;
      drawNewPuzzle();
    }

    trominos = new Array();

    stepIdx = 0;
    start = performance.now();

    solverWebWorker.postMessage({ cmd: "solve", payload: { order, markX, markY } });

    animationFrameRequestId = window.requestAnimationFrame(step);
  }

  /**
   * @returns {void}
   */
  function initElements() {
    canvasElement = document.getElementById("boardCanvas");
    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");
    orderElement = document.getElementById("order");
    orderIndicatorElement = document.getElementById("orderIndicator");
    puzzleEditorFormElement = document.getElementById("puzzleEditorForm");
    solveButtonElement = document.getElementById("solveButton");

    orderElement.min = "0";
    orderElement.max = "8";
    orderElement.value = (Math.log2(order) - 1).toString();

    orderIndicatorElement.textContent = order.toString();

    markXElement.value = markX.toString();
    markXElement.min = "0";

    markYElement.value = markY.toString();
    markYElement.min = "0";

    canvasElement.addEventListener("contextmenu", (e) => {
      e.preventDefault();
    });
    context = canvasElement.getContext("2d");

    puzzleEditorFormElement.addEventListener("input", () => {
      changePuzzle();
    });

    orderElement.addEventListener("input", (event) => {
      order = calcOrder(parseInt(event.target.value, 10));
    });

    markXElement.addEventListener("input", (event) => {
      markX = parseInt(event.target.value, 10);
    });

    markYElement.addEventListener("input", (event) => {
      markY = parseInt(event.target.value, 10);
    });
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
  async function initAppAsync() {
    initElements();
    initSolver();
    initOptions();
    await initResourcesAsync();

    solveButtonElement.disabled = false;
    solveButtonElement.addEventListener("click", startSolveAsync, false);
  }

  window.addEventListener("load", async () => {
    await initAppAsync();
  });
}(window, document, ltrGfx));

(async function (window, document) {
  let orderElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;
  let module;

  /**
   * @returns {void}
   */
  function initElements() {
    solveButtonElement = document.getElementById("solveButton");

    orderElement = document.getElementById("order");
    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");
  }

  /**
   * @param {number} n
   * @returns {number}
   */
  function calcOrder(n) {
    return 2 << n;
  }

  /**
   * @returns {Promise}
   */
  async function playTrominoAsync() {
    const order = calcOrder(parseInt(orderElement.value, 10));
    const markX = parseInt(markXElement.value, 10);
    const markY = parseInt(markYElement.value, 10);

    module._playTromino(order, markX, markY);
  }

  window.addEventListener("load", async () => {
    module = await createTrmnMod(/* optional default settings */);
    module.canvas = (function () {
      return document.getElementById("canvas");
    }());

    initElements();

    solveButtonElement.addEventListener("click", playTrominoAsync, false);
  });
}(window, document));
