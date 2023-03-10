// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_PARAMS_H
#define GUI_PARAMS_H

namespace tromino::tromino2d::params {

constexpr const int CANVAS_WIDTH{512};

constexpr const int REQUIRED_ARG_COUNT{4};

#ifdef __APPLE__
constexpr const int MAX_SUPPORTED_ORDER{512};
#elif __linux__
constexpr const int MAX_SUPPORTED_ORDER{32};
#elif _WINDOWS
constexpr const int MAX_SUPPORTED_ORDER{64};
#else
constexpr const int MAX_SUPPORTED_ORDER{32};
#endif

constexpr const int ORDER_ARG_IDX{1};
constexpr const int MARKX_ARG_IDX{2};
constexpr const int MARKY_ARG_IDX{3};
constexpr const int FORCE_ARG_IDX{4};

} // namespace tromino::tromino2d::params

#endif // GUI_PARAMS_H
