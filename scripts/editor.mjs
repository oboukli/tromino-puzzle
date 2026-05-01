/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.

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

/**
 * @typedef {Object} EditorChangeEvent
 * @property {number} order
 * @property {number} markX
 * @property {number} markY
 */

/**
 * @typedef {Object} EditorSolveEvent
 * @property {number} order
 * @property {number} markX
 * @property {number} markY
 */

const editor = new EventTarget();

let order = 16;
let markX = 11;
let markY = 5;

/** @type {HTMLFormElement} */
let puzzleEditorFormElement;

/** @type {HTMLInputElement} */
let orderElement;
/** @type {HTMLInputElement} */
let orderIndicatorElement;
/** @type {HTMLInputElement} */
let markXElement;
/** @type {HTMLInputElement} */
let markYElement;

/** @type {HTMLButtonElement} */
let solveButtonElement;

/**
 * @param {number} n
 * @returns {number}
 */
function calcOrder(n) {
  return 2 << n;
}

/**
 * @param {number} max
 * @returns {void}
 */
function setInputValueBounds(max) {
  markXElement.max = max.toString();
  markYElement.max = max.toString();
}

/**
 * @returns {void}
 */
function changePuzzle() {
  orderIndicatorElement.value = order.toString();

  setInputValueBounds(order - 1);

  markX = Math.min(Number.parseInt(markXElement.max, 10), markX);
  markY = Math.min(Number.parseInt(markYElement.max, 10), markY);

  markXElement.value = markX.toString();
  markYElement.value = markY.toString();

  editor.dispatchEvent(
    new CustomEvent("change", {
      detail: {
        order,
        markX,
        markY,
      },
    }),
  );
}

/**
 * @returns {void}
 */
function initElements() {
  // @ts-ignore
  markXElement = document.getElementById("markX");
  // @ts-ignore
  markYElement = document.getElementById("markY");
  // @ts-ignore
  orderElement = document.getElementById("order");
  // @ts-ignore
  orderIndicatorElement = document.getElementById("orderIndicator");
  // @ts-ignore
  puzzleEditorFormElement = document.getElementById("puzzleEditorForm");
  // @ts-ignore
  solveButtonElement = document.getElementById("solveButton");

  orderElement.min = "0";
  orderElement.max = "6";
  orderElement.value = (Math.log2(order) - 1).toString();

  orderIndicatorElement.value = order.toString();

  markXElement.value = markX.toString();
  markXElement.min = "0";

  markYElement.value = markY.toString();
  markYElement.min = "0";

  puzzleEditorFormElement.addEventListener("input", () => changePuzzle(), {
    capture: false,
    passive: true,
  });

  orderElement.addEventListener(
    "input",
    (event) => {
      // @ts-ignore
      order = calcOrder(Number.parseInt(event.target.value, 10));
    },
    { capture: false, passive: true },
  );

  markXElement.addEventListener(
    "input",
    (event) => {
      // @ts-ignore
      markX = Number.parseInt(event.target.value, 10);
    },
    { capture: false, passive: true },
  );

  markYElement.addEventListener(
    "input",
    (event) => {
      // @ts-ignore
      markY = Number.parseInt(event.target.value, 10);
    },
    { capture: false, passive: true },
  );
}

/**
 * @returns {EventTarget}
 */
function createEditor() {
  initElements();

  solveButtonElement.addEventListener(
    "click",
    () => {
      editor.dispatchEvent(
        new CustomEvent("solve", {
          detail: {
            order,
            markX,
            markY,
          },
        }),
      );
    },
    { capture: false, passive: true },
  );

  solveButtonElement.disabled = false;

  return editor;
}

export { createEditor };
