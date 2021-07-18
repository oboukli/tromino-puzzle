// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

"use strict";
;(async function(window, document) {
  let trominoImgSrc;
  let canvasElement;
  let orderElement;
  let markXElement;
  let markYElement;
  let solveButtonElement;

  let instancePromise;

  window.addEventListener('load', () => {
    instancePromise = initWasmAsync();

    initElements();

    solveButtonElement.addEventListener("click", startSolveAsync, false);
  });

  function initElements() {
    trominoImgSrc = "images/tromino.svg"; // TODO: Path

    canvasElement = document.getElementById("boardCanvas");

    solveButtonElement = document.getElementById("solveButton");

    orderElement = document.getElementById("order");
    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");
  }

  function initWasmAsync() {
    const importObject = {
      env: {
        memory: new WebAssembly.Memory({initial: 256, maximum: 256}) // TODO:
      }
    };

    return WebAssembly.instantiateStreaming(
      fetch('scripts/tromino-puzzle-wasm.wasm'), // TODO: Path
      importObject
    );
  }

  async function startSolveAsync() {
    const order = orderElement.value;
    const mark = { x: markXElement.value, y: markYElement.value };

    const delayBase = 17; // TODO:

    const options = {
      baseColor: "#012340",
      altColor: "#4E7DA6",
      markColor: "#8C1B1B"
    };

    const context = canvasElement.getContext("2d");

    const boardPromise = createBoardAsync(context, trominoImgSrc, order, mark, options);

    const [_, board] = await Promise.all([instancePromise, boardPromise]);

    drawBoard(board);
    drawMark(board);

    const puzzle = {
      order,
      mark: [mark.x, mark.y]
    };
    let placed = 0;
    solveTromino(puzzle, (position, angle) => {

      // TODO: That's too many calls. Delay at the source?
      setTimeout(drawTromino, delayBase * placed, board, position.x, position.y , angle);
      placed += 1;
    });
  }
})(window, document);
