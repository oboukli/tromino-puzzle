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
   * @property {string} trominoColor
   * @property {string} trominoOutlineColor
   */

  /**
   * @typedef {object} Board
   * @property {CanvasRenderingContext2D} context
   * @property {CanvasRenderingContext2D} trominoContext
   * @property {Options} options
   * @property {number} order
   * @property {Mark} mark
   * @property {number} numTrominos
   * @property {number} blockWidth
   */

  /**
   * @param {CanvasRenderingContext2D} context
   * @param {number} order
   * @param {Mark} mark
   * @param {Options} options
   * @returns {Board}
  */
  function createBoard(context, order, mark, options) {
    const blockWidth = context.canvas.clientWidth / order;

    const trominoCanvas = document.createElement("canvas");
    const wl = blockWidth * 2;
    trominoCanvas.width = wl;
    trominoCanvas.height = wl;
    const trominoContext = trominoCanvas.getContext("2d");

    initSprite(trominoContext, blockWidth, blockWidth * 0.125, options);

    return {
      context,
      trominoContext,
      order,
      mark,
      options,
      numTrominos: ((order ** 2) - 1) * 0.3333333333333333,
      blockWidth
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
   * @param {CanvasRenderingContext2D} trominoContext
   * @param {number} blockWidth
   * @param {number} thickness
   * @param {Options} options
   */
  function initSprite(trominoContext, blockWidth, thickness, options) {
    trominoContext.fillStyle = options.trominoColor;
    trominoContext.fillRect(0, 0, blockWidth * 2, blockWidth);
    trominoContext.fillRect(0, blockWidth, blockWidth, blockWidth);

    trominoContext.fillStyle = options.trominoOutlineColor;
    trominoContext.fillRect(0, 0, blockWidth * 2, thickness);
    trominoContext.fillRect((blockWidth * 2) - thickness, thickness, thickness, blockWidth - thickness);
    trominoContext.fillRect(blockWidth - thickness, blockWidth - thickness, (blockWidth * 2) - thickness, thickness);
    trominoContext.fillRect(blockWidth - thickness, blockWidth, thickness, blockWidth - thickness);
    trominoContext.fillRect(0, (blockWidth * 2) - thickness, blockWidth, thickness);
    trominoContext.fillRect(0, thickness, thickness, (blockWidth * 2) - thickness);
  }

  /**
   * @param {Board} board
   * @param {number} x
   * @param {number} y
   * @param {number} flipX
   * @param {number} flipY
   * @returns {void}
   */
  function drawTromino(board, x, y, flipX, flipY) {
    const context = board.context;
    const blockWidth = board.blockWidth;
    const rx = ((x * blockWidth) + blockWidth);
    const ry = ((y * blockWidth) + blockWidth);

    context.translate(rx, ry);
    context.scale(flipX, flipY);
    context.drawImage(board.trominoContext.canvas, -blockWidth, -blockWidth);
    context.scale(flipX, flipY);
    context.translate(-rx, -ry);
  }

  return {
    createBoard,
    drawBoard,
    drawMark,
    drawTromino
  };
}());
