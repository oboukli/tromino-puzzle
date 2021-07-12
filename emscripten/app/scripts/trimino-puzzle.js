// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

"use strict";

// TODO: Module

async function createBoardAsync(context, triminoImgSrc, order, mark, options) {
  order = order || 2;
  mark = mark || {};
  options = options || {};

  const renderedWidth = context.canvas.clientWidth;

  const triminoImg = new Image();
  triminoImg.src = triminoImgSrc;

  await triminoImg.decode();

  return {
    mark: {
      x: mark.x || 0,
      y: mark.y || 0,
    },
    context,
    order,
    numNeededTriminos: ((order * order) - 1) / 3,
    blockWidth: renderedWidth / order,
    renderedWidth,
    triminoImg,
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

  for (var i = 0; i < order; ++i) {
    for (var j = 0, col = order >> 1; j < col; ++j) {
      context.rect(2 * j * blockWidth + (i % 2 ? 0 : blockWidth), i * blockWidth, blockWidth, blockWidth);
    }
  }

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

function drawTrimino(board, x, y, angle) {
  const context = board.context;
  const triminoImg = board.triminoImg;
  const blockWidth = board.blockWidth;
  const rx = ((x * blockWidth)+ blockWidth);
  const ry = ((y * blockWidth) + blockWidth);

  context.translate(rx, ry);
  context.rotate(angle);
  context.drawImage(triminoImg, -blockWidth, -blockWidth, blockWidth * 2 , blockWidth * 2);
  context.rotate(-angle);
  context.translate(-rx, -ry);
}

function solveTrimino(puzzle, cb) {
  const mark = new Uint8Array(new Int32Array(puzzle.mark).buffer);

  let stackPtr = Module.stackSave();

  let markPtr = Module.allocate(mark, Module.ALLOC_STACK);

  let funcPtr = Module.addFunction(function (positionPtr, angle) {

    const position = {
      x: Module.getValue(positionPtr, "i32"),
      y: Module.getValue(positionPtr + 4, "i32")
    };

    cb(position, angle);
  }, "vid");

  Module.ccall(
    "solve",
    "void",
    ["number", "number", "number", "number"],
    [puzzle.order, markPtr, funcPtr]
  );

  Module.removeFunction(funcPtr);
  funcPtr = 0;

  Module.stackRestore(stackPtr);
  stackPtr = 0;
}
