// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// @ts-check

"use strict";

;(async function(window, document, createTrmnPzzlAlgMod, trmnjs) {
  let trominoImgSrc;
  let canvasElement;
  let orderElement;
  let orderIndicatorElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;

  let instancePromise;
  let emModulePromise;

  window.addEventListener("load", () => {
    instancePromise = initWasmAsync();
    emModulePromise = initEmscriptenModuleAsync();

    initElements();

    solveButtonElement.addEventListener("click", startSolveAsync, false);
  });

  function initElements() {
    trominoImgSrc = "images/tromino.svg"; // TODO: Path

    canvasElement = document.getElementById("boardCanvas");
    canvasElement.addEventListener("contextmenu", e => {
      e.preventDefault();
    });

    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");

    orderIndicatorElement = document.getElementById("orderIndicator");
    orderElement = document.getElementById("order");
    orderElement.addEventListener("input", (event) => {
      const order = calcOrder(parseInt(event.target.value));

      orderIndicatorElement.value = order;

      setInputValueBounds(order - 1);
    });

    setInputValueBounds(calcOrder(parseInt(orderElement.value)) - 1);

    solveButtonElement = document.getElementById("solveButton");
  }

  function initWasmAsync() {
    const importObject = {
      env: {
        'memory': new WebAssembly.Memory({initial: 256, maximum: 256}), // TODO:
      }
    };

    return WebAssembly.instantiateStreaming(
      fetch('scripts/tromino-puzzle-alg-wasm.wasm'), // TODO: Path
      importObject
    );
  }

  async function initEmscriptenModuleAsync() {
    return await createTrmnPzzlAlgMod(/* optional default settings */);
  }

  /**
   * @param {number} n
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

  async function startSolveAsync() {
    const order = 2 << parseInt(orderElement.value);
    const mark = { x: parseInt(markXElement.value), y: parseInt(markYElement.value) };

    const delayBase = 68; // TODO:

    const options = {
      baseColor: "#4E7DA6",
      altColor: "#012340",
      markColor: "#8C1B1B"
    };

    const context = canvasElement.getContext("2d");

    const boardPromise = trmnjs.createBoardAsync(context, trominoImgSrc, order, mark, options);

    const [_, board, emModule] = await Promise.all([instancePromise, boardPromise, emModulePromise]);

    trmnjs.drawBoard(board);
    trmnjs.drawMark(board);

    const puzzle = {
      order,
      mark: [mark.x, mark.y]
    };
    let placed = 0;
    trmnjs.solveTromino(emModule, puzzle, (/** @type {{ x: number; y: number; }} */ position, /** @type {number} */ angle) => {

      // TODO: That's too many calls. Delay at the source?
      setTimeout(trmnjs.drawTromino, delayBase * placed, board, position.x, position.y , angle);
      placed += 1;
    });
  }
})(window, document, createTrmnPzzlAlgMod, trmnjs);

;(async function(window, document) {
  let orderElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;
  let module;

  window.addEventListener("load", async () => {
    module = await createTrmnPzzlGfx2dMod(/* optional default settings */);
    module.canvas = (function() {
      return document.getElementById("canvas");
    })();

    initElements();

    solveButtonElement.addEventListener("click", playTrominoAsync, false);
  });

  function initElements() {
    solveButtonElement = document.getElementById("solveButton");

    orderElement = document.getElementById("order");
    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");
  }

  /**
   * @param {number} n
   */
  function calcOrder(n) {
    return 2 << n;
  }

  async function playTrominoAsync() {
    const order = calcOrder(parseInt(orderElement.value));
    const markX = parseInt(markXElement.value);
    const markY = parseInt(markYElement.value);

    module._playTromino(order, markX, markY);
  }
})(window, document);
