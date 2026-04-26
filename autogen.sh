#!/bin/sh

export LC_ALL=C

set -e

mkdir m4
mkdir src/config

wget https://raw.githubusercontent.com/autoconf-archive/autoconf-archive/master/m4/ax_cxx_compile_stdcxx.m4
mv ax_cxx_compile_stdcxx.m4 m4/

autoreconf --install --force --verbose --warnings=all
