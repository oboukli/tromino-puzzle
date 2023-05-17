# Tromino Puzzle

[![Azure Pipelines build status](https://dev.azure.com/omarboukli/tromino-puzzle/_apis/build/status/oboukli.tromino-puzzle?branchName=main)](https://dev.azure.com/omarboukli/tromino-puzzle/_build/latest?definitionId=2&branchName=main)
[![DevSkim](https://github.com/oboukli/tromino-puzzle/actions/workflows/devskim-analysis.yml/badge.svg?branch=main)](https://github.com/oboukli/tromino-puzzle/actions/workflows/devskim-analysis.yml?query=branch%3Amain)
[![CodeQL](https://github.com/oboukli/tromino-puzzle/actions/workflows/codeql-analysis.yml/badge.svg?branch=main)](https://github.com/oboukli/tromino-puzzle/actions/workflows/codeql-analysis.yml?query=branch%3Amain)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=oboukli_tromino-puzzle&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=oboukli_tromino-puzzle)
[![CodeFactor](https://www.codefactor.io/repository/github/oboukli/tromino-puzzle/badge)](https://www.codefactor.io/repository/github/oboukli/tromino-puzzle)
[![Codacy](https://app.codacy.com/project/badge/Grade/8395b4fbd3b34c72907b0e65fe0b5f35)](https://www.codacy.com/gh/oboukli/tromino-puzzle/dashboard)

This is a C library (see `src/libtromino`) implementing a divide-and-conquer O(n)
algorithm, and a collection of apps, to solve the tromino puzzle,
over-engineered for the joy of learning by doing.

A tromino puzzle consists of a checkered
$2^n \times 2^n : n \in \mathbb{N} \land n > 0$ (chess-like) board, where
exactly one of the board's squares is marked. The goal is to tile the entire
board, except for the marked square, with L-shaped tiles. A tile is a right
tromino, in the shape of an L formed by three board squares. Each tile has four
possible rotations.

![Tromino puzzle](content/puzzle-8x8.gif)

## Background

The developer (@oboukli) was first introduced to the tromino puzzle in early
2006, via Anany Levitin's book _Introduction to the Design and Analysis of
Algorithms_, published in 2003 by Addison-Wesley. Anany Levitin mentions
Solomon W. Golomb's second edition _Polyominoes: Puzzles, Patterns, Problems,
and Packings_, published in 1994 by Princeton University Press, as a reference
to the puzzle.

The realization of the recursive solution was such a beautiful epiphany to the
developer.

## Command line app

The command line app is supported on Linux, macOS, and Windows. See the
[_Desktop app_](#desktop-app) section for build instruction.

### Virtual terminal mode

The virtual terminal (VT-100) mode should work on any system with POSIX
support, including supported versions of macOS and Windows.

For basic ASCII drawings, which may be useful for writing to text files,
define `TROMINO_USE_ASCII` before building. The following is an example
output for a $4 \times 4$ puzzle marked at $(1, 1)$:

```text
+--+
|X||
|-+|
+--+
```

### Windows Console Host (WCH) mode

On Windows, a native legacy Windows Console Host (WCH) renderer, which uses DOS
box-drawing characters
(code page 437), is included.

## Desktop app

### Building for macOS with Xcode

The desktop app is currently actively supported on macOS. See the `xcode`
directory for the Xcode 13 project files.

The Xcode projects are configured to use vcpkg paths. To install the build
dependencies with vcpkg:

```shell
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
./vcpkg/vcpkg install sdl2 --triplet x64-osx-dynamic
./vcpkg/vcpkg install sdl2 --triplet arm64-osx-dynamic
```

Boost Test is required for building the the unit tests:

```shell
./vcpkg/vcpkg install boost-test
```

Homebrew can also be used. However, the Xcode projects must be manually
reconfigured. The same applies for manual or custom SDL2 installation.

To install the build dependencies with Homebrew:

```shell
brew install boost sdl2
```

### Building for Unix and GNU/Linux with GNU Autotools

For Linux, and possibly any platform on which GNU Autotools are
supported:

```shell
./autogen.sh
mkdir build
cd build
../configure
make
```

Optional steps:

```shell
make check
make install
```

### Building for Windows with MSBuild

For Windows, MSBuild files are provided which can be built with
Visual Studio 2022, or from the command line:

```powershell
msbuild -maxCpuCount -property:Configuration=release -property:Platform=x64 msbuild\TrominoPuzzle.sln
```

### Dependencies

The SDL2 library is required to build the desktop app.

> Tip: The Debian and Ubuntu development package for SDL2 is `libsdl2-dev`.

```shell
sudo apt install libsdl2-dev
```

### Headless app

For an experimental headless tromino2d app, define `TROMINO_2D_HEADLESS` before
building the tromino2d app.

## Web app

The web app makes use of WebAssembly and requires Emscripten to build.

```shell
cd emscripten
emmake make
```

### Building and running the web app on Docker

The web app can be built using the Emscripten SDK Docker image:

```shell
docker pull emscripten/emsdk
docker run --rm --volume=$(pwd):/src --workdir=/src/emscripten \
emscripten/emsdk emmake make
```

To run the web app:

```shell
docker pull nginx
docker run --detach --rm --publish=8080:80 \
--volume=$(pwd)/dist/web:/usr/share/nginx/html:ro --name tromino-puzzle nginx
```

## Technical showcases

The following is a partial list of standards, practices, software,
and ideas leveraged by this project:

- C (C89)
- C++ (standard C++17)
- C++ STL
- No C++ inheritance
- No C++ exceptions
- No C++ RTTI
- `const` and `constexpr` where applicable--except members
- SDL2
- VT-100
- Windows API
- Boost Test
- vcpkg
- Clang Format
- Emscripten
- JavaScript (ECMAScript 2016+ - vanilla)
- Web Workers
- TypeScript JSDoc type annotations
- ESLint
- HTMLHint
- Prettier
- Conventional Commits
- Xcode
- MSBuild
- GNU Make
- GNU Autotools
- Azure Pipelines
- GitHub Actions
- GitHub Pages
- Docker
- Code test coverage
- CodeQL
- DevSkim
- OpenSSF Scorecard
- EditorConfig
- Markdown
- Markdownlint
- SonarScanner
- Strongly-typed approach
- HTML5
- CSS
- SVG

## License

This software is released under an [MIT-style license](LICENSE).
Copyright © 2021-2023 Omar Boukli-Hacene.

SPDX license identifier: MIT.

---

Made for the joy of it 🐳
