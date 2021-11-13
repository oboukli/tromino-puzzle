// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// @ts-check

"use strict";

(async function (window, document, createTrmnPzzlAlgMod, trmnjs) {
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
        "memory": new WebAssembly.Memory({ initial: 256, maximum: 256 }), // TODO:
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

    const delayBase = 68; // TODO:
    let drawIndex = 0;
    let start = performance.now();

    const numTrominos = boardViewModel.numTrominos;
    let placed = 0;
    const solutionModel = new Array(numTrominos);

    function step(timestamp) {
      const elapsed = timestamp - start;

      if (drawIndex < numTrominos) {
        if (elapsed > drawIndex * delayBase) {
          let { x, y, angle } = solutionModel[drawIndex];
          drawIndex += 1;
          trmnjs.drawTromino(boardViewModel, x, y, angle);
        }

        animationFrameRequestId = window.requestAnimationFrame(step);
      }
    }

    const puzzle = {
      order,
      mark: [markX, markY]
    };

    trmnjs.solveTromino(emModule, puzzle, (/** @type {{ x: number; y: number; }} */ position, /** @type {number} */ angle) => {
      solutionModel[placed] = { x: position.x, y: position.y, angle };
      placed += 1;
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
