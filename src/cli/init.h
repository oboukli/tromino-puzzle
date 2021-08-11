// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#ifndef init_h
#define init_h

#include <cassert>

#include "tromino.h"
#include "trmn_graph.h"
#include "trmn_graph_vt.h"

#ifdef _WINDOWS
#include "trmn_graph_windows.h"
#endif // _WINDOWS

enum class emulation_mode {
    vt_100 = 0,
    windows_console_host = 1
};

void init(int size, int x, int y, emulation_mode emulation_mode);

#endif // init_h
