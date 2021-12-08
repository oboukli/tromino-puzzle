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

// eslint-disable-next-line no-unused-vars
const ltrGfx = (function () {
  /**
   * @typedef {object} Mark
   * @property {number} x
   * @property {number} y
   */

  /**
   * @typedef {object} Options
   * @property {string} altColor
   * @property {string} baseColor
   * @property {string} markColor
   */

  /**
   * @typedef {object} Board
   * @property {CanvasRenderingContext2D} context
   * @property {HTMLImageElement} trominoImg
   * @property {Options} options
   * @property {number} order
   * @property {Mark} mark
   * @property {number} numTrominos
   * @property {number} blockWidth
   */

  /**
   * @param {CanvasRenderingContext2D} context
   * @param {HTMLImageElement} trominoImg
   * @param {number} order
   * @param {Mark} mark
   * @param {Options} options
   * @returns {Board}
  */
  function createBoard(context, trominoImg, order, mark, options) {
    return {
      context,
      trominoImg,
      order,
      mark,
      options,
      numTrominos: ((order ** 2) - 1) * 0.3333333333333333,
      blockWidth: context.canvas.clientWidth / order
    };
  }

  /**
   * @param {Board} board
   * @returns {void}
   */
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

  /**
   * @param {object} board
   * @returns {void}
   */
  function drawMark(board) {
    const context = board.context;
    const x = board.mark.x;
    const y = board.mark.y;
    const blockWidth = board.blockWidth;
    const color = board.options.markColor;

    context.fillStyle = color;
    context.fillRect(x * blockWidth, y * blockWidth, blockWidth, blockWidth);
  }

  /**
   * @param {Board} board
   * @param {number} x
   * @param {number} y
   * @param {number} angle
   * @returns {void}
   */
  function drawTromino(board, x, y, angle) {
    const context = board.context;
    const trominoImg = board.trominoImg;
    const blockWidth = board.blockWidth;
    const rx = ((x * blockWidth) + blockWidth);
    const ry = ((y * blockWidth) + blockWidth);

    context.translate(rx, ry);
    context.rotate(angle);
    context.drawImage(trominoImg, -blockWidth, -blockWidth, blockWidth * 2, blockWidth * 2);
    context.rotate(-angle);
    context.translate(-rx, -ry);
  }

  return {
    createBoard,
    drawBoard,
    drawMark,
    drawTromino
  };
}());
