// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#ifndef init_h
#define init_h

#include <cassert>

#include "trimino.h"
#include "trmn_graph.h"
#include "trmn_graph_vt.h"

#ifdef _WINDOWS
#include "trmn_graph_windows.h"
#endif // _WINDOWS

void init(int size, int x, int y);

#endif // init_h
