# Tromino Puzzle

[![Open in Visual Studio Code](https://open.vscode.dev/badges/open-in-vscode.svg)](https://open.vscode.dev/oboukli/tromino-puzzle)
[![Azure Pipelines build status](https://dev.azure.com/omarboukli/tromino-puzzle/_apis/build/status/oboukli.tromino-puzzle?branchName=development)](https://dev.azure.com/omarboukli/tromino-puzzle/_build/latest?definitionId=2&branchName=development)

This is a C library implementing a divide-and-conquer O(n) algorithm, and a collection of apps, to solve the tromino puzzle, over-engineered for the joy of it.

A tromino puzzle consists of a checkered 2^n × 2^n (chess-like) board, where exactly one of the board's squares is marked. The goal is to tile the entire board, except for the marked square, with L-shaped tiles. A tile is a right tromino, in the shape of an L formed by three board squares. Each tile has four possible rotations.

## Background

The developer (@oboukli) was first introduced to the tromino puzzle in early 2006, via Anany Levitin's book _Introduction to the Design and Analysis of Algorithms_, published in 2003 by Addison-Wesley. Anany Levitin mentions Solomon W. Golomb's second edition _Polyominoes: Puzzles, Patterns, Problems, and Packings_, published in 1994 by Princeton University Press, as a reference to the puzzle.

The realization of the recursive solution was such a beautiful epiphany to the developer.

## Building the web app

The web app makes use of WebAssembly and requires Emscripten to build.

```shell
cd emscripten
emmake make
```

### Building and running the web app on Docker

To build the web app:

```shell
docker pull emscripten/emsdk
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) --workdir="/src/emscripten" \
  emscripten/emsdk emmake make
```

To run the web app:

```shell
docker pull nginx
docker run -it --rm -d -p 8080:80 -v $(pwd)/dist/web:/usr/share/nginx/html --name tromino-puzzle nginx
```

## Building the command line app

### Virtual terminal mode

The virtual terminal (VT-100) mode should work on any system with POSIX support, including supported versions of macOS and Windows.

For basic ASCII drawings, which may be useful for writing to text files, define `TROMINO_USE_ASCII` before building.

### Windows Console Host mode

On Windows, a native legacy Windows Console Host (WCH) renderer, which uses DOS box-drawing characters ([code page 437](https://en.wikipedia.org/wiki/Code_page_437)), is included.

## License

This software is released under an [MIT-style license](LICENSE). Copyright © 2021 Omar Boukli-Hacene.

---

Made for the joy of it 🐳
