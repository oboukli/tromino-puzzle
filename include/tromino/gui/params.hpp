// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_PARAMS_HPP
#define GUI_PARAMS_HPP

namespace tromino::tromino2d::params {

constexpr int const CANVAS_WIDTH{512};

constexpr int const REQUIRED_ARG_COUNT{4};

#ifdef __APPLE__
constexpr int const MAX_SUPPORTED_ORDER{512};
#elif __linux__
constexpr int const MAX_SUPPORTED_ORDER{32};
#elif _WIN64
constexpr int const MAX_SUPPORTED_ORDER{64};
#else
constexpr int const MAX_SUPPORTED_ORDER{32};
#endif

constexpr int const ORDER_ARG_IDX{1};
constexpr int const MARKX_ARG_IDX{2};
constexpr int const MARKY_ARG_IDX{3};
constexpr int const FORCE_ARG_IDX{4};

} // namespace tromino::tromino2d::params

#endif // GUI_PARAMS_HPP
