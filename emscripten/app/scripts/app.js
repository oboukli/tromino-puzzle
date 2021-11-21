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

(async function (window, document, createTrmnPzzlAlgMod, trmnjs) {
  const delayBase = 68; // TODO:
  const trominoImgSrc = "images/tromino.svg"; // TODO: Path;

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

  let instancePromise;
  let emModulePromise;

  let emModule;
  let boardViewModel;

  let animationFrameRequestId;

  function initWasmAsync() {
    const importObject = {
      env: {
        "memory": new WebAssembly.Memory({ initial: 1, maximum: 1 })
      }
    };

    return WebAssembly.instantiateStreaming(
      fetch("scripts/tromino-puzzle-alg-wasm.wasm"), // TODO: Path
      importObject
    );
  }

  async function initEmscriptenModuleAsync() {
    return await createTrmnPzzlAlgMod(/* optional default settings */);
  }

  /**
   * @param {number} n
   * @returns {number}
   */
  function calcOrder(n) {
    return 2 << n;
  }

  /**
   * @param {number} max
   */
  function setInputValueBounds(max) {
    markXElement.max = max;
    markYElement.max = max;
  }

  function drawInitial() {
    trmnjs.drawBoard(boardViewModel);
    trmnjs.drawMark(boardViewModel);
  }

  function updateBoard() {
    cancelAnimationFrame(animationFrameRequestId);
    animationFrameRequestId = 0;

    orderIndicatorElement.textContent = order;

    setInputValueBounds(order - 1);

    markX = Math.min(markXElement.max, markX);
    markY = Math.min(markYElement.max, markY);

    markXElement.value = markX;
    markYElement.value = markY;

    trmnjs.updateBoard(boardViewModel, order, { x: markX, y: markY });
    drawInitial();
  }

  function startSolveAsync() {
    if (animationFrameRequestId !== 0) {
      cancelAnimationFrame(animationFrameRequestId);
      animationFrameRequestId = 0;
      drawInitial();
    }

    let stepIdx = 0;
    let start = performance.now();

    const numTrominos = boardViewModel.numTrominos;
    const trominos = new Array(numTrominos);
    const trominosIterator = trominos[Symbol.iterator]();

    /**
     * @param {number} timestamp
     */
    function step(timestamp) {
      const elapsed = timestamp - start;
      if (stepIdx < numTrominos) {
        if (elapsed > stepIdx * delayBase) {
          stepIdx += 1;
          let { x, y, angle } = trominosIterator.next().value;
          trmnjs.drawTromino(boardViewModel, x, y, angle);
        }

        animationFrameRequestId = window.requestAnimationFrame(step);
      }
    }

    const puzzle = {
      order,
      mark: [markX, markY]
    };
    let placedIdx = 0;

    trmnjs.solveTromino(emModule, puzzle, (/** @type {{ x: number; y: number; }} */ position, /** @type {number} */ angle) => {
      trominos[placedIdx] = { x: position.x, y: position.y, angle };
      placedIdx += 1;
    });

    animationFrameRequestId = window.requestAnimationFrame(step);
  }

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
      updateBoard();
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

  async function initBoard() {
    const options = {
      baseColor: "#4e7da6",
      altColor: "#012340",
      markColor: "#8c1b1b"
    };

    const boardPromise = trmnjs.createBoardAsync(context, trominoImgSrc, order, { x: markX, y: markY }, options);

    let _;
    [_, boardViewModel, emModule] = await Promise.all([instancePromise, boardPromise, emModulePromise]);
  }

  window.addEventListener("load", async () => {
    instancePromise = initWasmAsync();
    emModulePromise = initEmscriptenModuleAsync();

    initElements();
    await initBoard();

    drawInitial();

    solveButtonElement.addEventListener("click", startSolveAsync, false);
  });
})(window, document, createTrmnPzzlAlgMod, trmnjs);

(async function (window, document) {
  let orderElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;
  let module;

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

  async function playTrominoAsync() {
    const order = calcOrder(parseInt(orderElement.value, 10));
    const markX = parseInt(markXElement.value, 10);
    const markY = parseInt(markYElement.value, 10);

    module._playTromino(order, markX, markY);
  }

  window.addEventListener("load", async () => {
    module = await createTrmnPzzlGfx2dMod(/* optional default settings */);
    module.canvas = (function () {
      return document.getElementById("canvas");
    })();

    initElements();

    solveButtonElement.addEventListener("click", playTrominoAsync, false);
  });
})(window, document);
