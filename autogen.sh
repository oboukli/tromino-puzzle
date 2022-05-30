#!/bin/sh

export LC_ALL=C

set -e

mkdir m4
mkdir src/config

autoreconf --install --force --verbose --warnings=all
