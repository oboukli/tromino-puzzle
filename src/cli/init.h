// Copyright (c) Omar Boukli-Hacene 2021-2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef INIT_H_
#define INIT_H_

#include <cassert>

#include "tromino.h"

#include "trmn_graph.h"
#include "trmn_graph_vt.h"

#ifdef _WINDOWS
#include "trmn_graph_windows.h"
#endif // _WINDOWS

// clang-format off
enum class emulation_mode {
    vt_100 = 0,
    windows_console_host = 1
};
// clang-format on

void init(
    const int size, const int x, const int y,
    const emulation_mode emulation_mode) noexcept;

#endif // INIT_H_
