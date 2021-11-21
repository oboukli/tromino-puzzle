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

var trmnjs = (function() {
  function updateBoard(board, order, mark) {
    board.mark = mark;
    board.order = order;
    board.numTrominos = ((order ** 2) - 1) * 0.3333333333333333;
    board.blockWidth = board.context.canvas.clientWidth / order;
  }

  async function createBoardAsync(context, trominoImgSrc, order, mark, options) {

    const trominoImg = new Image();
    trominoImg.src = trominoImgSrc;

    await trominoImg.decode();

    const board = {
      context,
      trominoImg,
      options
    };

    updateBoard(board, order, mark);

    return board;
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
        context.rect(2 * j * blockWidth + ((i & 1) === 1 ? 0 : blockWidth), i * blockWidth, blockWidth, blockWidth);
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
    updateBoard,
    solveTromino
  };
})();
