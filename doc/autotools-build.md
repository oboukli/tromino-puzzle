# Autotools build

```shell
autoreconf --install --force --verbose --warnings=all
mkdir build && cd build
../configure #--prefix <absolute path>
make
make install
```

## Using Docker

```shell
docker pull gcc

docker run --rm -v $(pwd):/tromino -u $(id -u):$(id -g) --workdir="/tromino" gcc autoreconf --install --force --verbose --warnings=all

mkdir build

docker run --rm -v $(pwd):/tromino -u $(id -u):$(id -g) --workdir="/tromino" gcc bash -c "cd build && ../configure"

docker run --rm -v $(pwd):/tromino -u $(id -u):$(id -g) --workdir="/tromino" gcc bash -c "cd build && make"

docker run --rm -v $(pwd):/tromino -u $(id -u):$(id -g) --workdir="/tromino" gcc bash -c "cd build/src/cli && ./tromino"
```
