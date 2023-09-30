#!/bin/bash

TRMN_LIBSDL2_DIR=$BUILD_DIR/libSDL2
TRMN_LIBSDL2_PATH=$TRMN_LIBSDL2_DIR/libSDL2-2.0.0.dylib
if [[ ! -f $TRMN_LIBSDL2_PATH ]]
then
    mkdir -p $TRMN_LIBSDL2_DIR
    lipo -create \
    ../../vcpkg/installed/arm64-osx-dynamic/lib/libSDL2-2.0.dylib \
    ../../vcpkg/installed/x64-osx-dynamic/lib/libSDL2-2.0.dylib \
    -output $TRMN_LIBSDL2_PATH
fi
