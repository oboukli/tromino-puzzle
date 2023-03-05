// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef PARAMS_H
#define PARAMS_H

namespace tromino::tromino2d::params {

constexpr int CANVAS_WIDTH{512};

constexpr int REQUIRED_ARG_COUNT{4};

#ifdef __APPLE__
constexpr int MAX_SUPPORTED_ORDER{512};
#elif __linux__
constexpr int MAX_SUPPORTED_ORDER{32};
#elif _WINDOWS
constexpr int MAX_SUPPORTED_ORDER{64};
#else
constexpr int MAX_SUPPORTED_ORDER{32};
#endif

constexpr int ORDER_ARG_IDX{1};
constexpr int MARKX_ARG_IDX{2};
constexpr int MARKY_ARG_IDX{3};
constexpr int FORCE_ARG_IDX{4};

} // namespace tromino::tromino2d::params

#endif // PARAMS_H
