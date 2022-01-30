// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef INIT_H_
#define INIT_H_

#include <cassert>

#include "tromino.h"

#include "cli_models.h"
#include "trmn_graph.h"
#include "trmn_graph_vt.h"

#ifdef _WINDOWS
#include "trmn_graph_windows.h"
#endif // _WINDOWS

namespace tromino::cli::app {

void init(
    const int size, const int x, const int y,
    const emulation_mode_type emulation_mode) noexcept;

} // namespace tromino::cli::app

#endif // INIT_H_
