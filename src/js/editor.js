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

/**
 * @param {Document} document
 */
// eslint-disable-next-line no-unused-vars
const editorFactory = (function (document) {
  const editor = new EventTarget();
  let order = 32;
  let markX = 11;
  let markY = 17;

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
   */
  function setInputValueBounds(max) {
    markXElement.max = max.toString();
    markYElement.max = max.toString();
  }

  function changePuzzle() {
    orderIndicatorElement.value = order.toString();

    setInputValueBounds(order - 1);

    markX = Math.min(parseInt(markXElement.max, 10), markX);
    markY = Math.min(parseInt(markYElement.max, 10), markY);

    markXElement.value = markX.toString();
    markYElement.value = markY.toString();

    editor.dispatchEvent(new CustomEvent("change", {
      detail: {
        order,
        markX,
        markY
      }
    }));
  }

  /**
   * @returns {void}
   */
  function initElements() {
    markXElement = document.getElementById("markX");
    markYElement = document.getElementById("markY");
    orderElement = document.getElementById("order");
    orderIndicatorElement = document.getElementById("orderIndicator");
    puzzleEditorFormElement = document.getElementById("puzzleEditorForm");
    solveButtonElement = document.getElementById("solveButton");

    orderElement.min = "0";
    orderElement.max = "6";
    orderElement.value = (Math.log2(order) - 1).toString();

    orderIndicatorElement.value = order.toString();

    markXElement.value = markX.toString();
    markXElement.min = "0";

    markYElement.value = markY.toString();
    markYElement.min = "0";

    puzzleEditorFormElement.addEventListener("input", () => changePuzzle(),
      { capture: false, passive: true });

    orderElement.addEventListener("input", (event) => {
      order = calcOrder(parseInt(event.target.value, 10));
    }, { capture: false, passive: true });

    markXElement.addEventListener("input", (event) => {
      markX = parseInt(event.target.value, 10);
    }, { capture: false, passive: true });

    markYElement.addEventListener("input", (event) => {
      markY = parseInt(event.target.value, 10);
    }, { capture: false, passive: true });
  }

  /**
   * @returns {EventTarget}
   */
  function create() {
    initElements();

    solveButtonElement.addEventListener("click", () => {
      editor.dispatchEvent(new CustomEvent("solve", {
        detail: {
          order,
          markX,
          markY
        }
      }));
    }, { capture: false, passive: true });

    solveButtonElement.disabled = false;

    return editor;
  }

  return {
    create
  };
}(document));
