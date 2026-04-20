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

import { createEditor } from "./editor.mjs";
import * as litro from "./litro/litro.mjs";
import * as trmn from "./trmn/trmn.mjs";

/**
 * @typedef {import("./editor.mjs").EditorChangeEvent} EditorChangeEvent
 */

/**
 * @typedef {import("./editor.mjs").EditorSolveEvent} EditorSolveEvent
 */

const editor = createEditor();

litro.init({
  altColor: "#012340",
  baseColor: "#4e7da6",
  markColor: "#8c1b1b",
  trominoColor: "#d9933d",
  trominoOutlineColor: "#d93636",
});

try {
  await trmn.initAsync();
} catch (err) {
  console.error(err);
}

editor.addEventListener("change", (event) => {
  const detail = /** @type {CustomEvent<EditorChangeEvent>} */ (event).detail;
  litro.change(detail.order, detail.markX, detail.markY);
});

editor.addEventListener("solve", (event) => {
  const detail = /** @type {CustomEvent<EditorSolveEvent>} */ (event).detail;
  litro.play(detail.order, detail.markX, detail.markY);
});

editor.addEventListener("solve", (event) => {
  const detail = /** @type {CustomEvent<EditorSolveEvent>} */ (event).detail;
  trmn.play(detail.order, detail.markX, detail.markY);
});
