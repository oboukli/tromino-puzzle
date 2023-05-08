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

// @ts-check

"use strict";

(async function (window, editorFactory, litro, trmn) {
  window.addEventListener(
    "DOMContentLoaded",
    () => {
      (async () => {
        const editor = editorFactory.create();

        litro.init();
        await trmn.initAsync();

        editor.addEventListener("change", (e) => {
          litro.change(e.detail.order, e.detail.markX, e.detail.markY);
        });

        editor.addEventListener("solve", (e) => {
          litro.play(e.detail.order, e.detail.markX, e.detail.markY);
        });

        editor.addEventListener("solve", (e) => {
          trmn.play(e.detail.order, e.detail.markX, e.detail.markY);
        });
      })().catch(console.error);
    },
    { capture: false, once: true, passive: true }
  );
})(
  window,
  /* global editorFactory */ editorFactory,
  /* global litro */ litro,
  /* global trmn */ trmn
);
