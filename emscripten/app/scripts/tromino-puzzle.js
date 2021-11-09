// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// @ts-check

"use strict";

;var trmnjs = (function() {
  async function createBoardAsync(context, trominoImgSrc, order, mark, options) {
    order = order || 2;
    mark = mark || {};
    options = options || {};

    const renderedWidth = context.canvas.clientWidth;

    const trominoImg = new Image();
    trominoImg.src = trominoImgSrc;

    await trominoImg.decode();

    return {
      mark: {
        x: mark.x || 0,
        y: mark.y || 0,
      },
      context,
      order,
      numNeededTrominos: ((order * order) - 1) / 3,
      blockWidth: renderedWidth / order,
      renderedWidth,
      trominoImg,
      options: {
        baseColor: options.baseColor || "#fff",
        altColor: options.altColor || "#000",
        markColor: options.markColor || "#0f0"
      }
    };
  }

  function drawBoard(board) {
    const context = board.context;
    const order = board.order;
    const blockWidth = board.blockWidth;
    const options = board.options;

    const canvasSize = context.canvas.clientWidth;

    context.fillStyle = options.baseColor;
    context.fillRect(0, 0, canvasSize, canvasSize);

    context.beginPath();
    for (var i = 0; i < order; ++i) {
      for (var j = 0, col = order >> 1; j < col; ++j) {
        context.rect(2 * j * blockWidth + (i % 2 ? 0 : blockWidth), i * blockWidth, blockWidth, blockWidth);
      }
    }
    context.closePath();

    context.fillStyle = options.altColor;
    context.fill();
  }

  function drawMark(board) {
    const context = board.context;
    const x = board.mark.x;
    const y = board.mark.y;
    const blockWidth = board.blockWidth;
    const color = board.options.markColor;

    context.fillStyle = color;
    context.fillRect(x * blockWidth, y * blockWidth, blockWidth, blockWidth);
  }

  function drawTromino(board, x, y, angle) {
    const context = board.context;
    const trominoImg = board.trominoImg;
    const blockWidth = board.blockWidth;
    const rx = ((x * blockWidth)+ blockWidth);
    const ry = ((y * blockWidth) + blockWidth);

    context.translate(rx, ry);
    context.rotate(angle);
    context.drawImage(trominoImg, -blockWidth, -blockWidth, blockWidth * 2 , blockWidth * 2);
    context.rotate(-angle);
    context.translate(-rx, -ry);
  }

  function solveTromino(emModule, puzzle, cb) {
    const mark = new Uint8Array(new Int32Array(puzzle.mark).buffer);

    let stackPtr = emModule.stackSave();

    let markPtr = emModule.allocate(mark, emModule.ALLOC_STACK);

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
      [puzzle.order, markPtr, funcPtr]
    );

    emModule.removeFunction(funcPtr);
    funcPtr = 0;

    emModule.stackRestore(stackPtr);
    stackPtr = 0;
  }

  return {
    createBoardAsync,
    drawBoard,
    drawMark,
    drawTromino,
    solveTromino
  };
})();
