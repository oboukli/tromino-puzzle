# Tromino Puzzle

[![Open in Visual Studio Code](https://open.vscode.dev/badges/open-in-vscode.svg)](https://open.vscode.dev/oboukli/tromino-puzzle)
[![Azure Pipelines build status](https://dev.azure.com/omarboukli/tromino-puzzle/_apis/build/status/oboukli.tromino-puzzle?branchName=develop)](https://dev.azure.com/omarboukli/tromino-puzzle/_build/latest?definitionId=2&branchName=develop)

## Virtual terminal app

For basic ASCII drawing, useful for writing to text files, define `TROMINO_USE_ASCII`.

## Web app

The web app makes use of WebAssembly and requires Emscripten to build.

```shell
cd emscripten
emmake make
```

### Docker

```shell
docker pull emscripten/emsdk
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) --workdir="/src/emscripten" \
  emscripten/emsdk emmake make
```

```shell
docker pull nginx
docker run -it --rm -d -p 8080:80 -v $(pwd)/dist/web:/usr/share/nginx/html --name tromino-puzzle nginx
```

## License

This software is released under an [MIT-style license](LICENSE). Copyright © 2021 Omar Boukli-Hacene.

---

Made for the joy of it 🐳
