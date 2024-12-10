// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GUI_PARAMS_HPP_
#define GUI_PARAMS_HPP_

#include <cstddef>

namespace tromino::tromino2d::params {

constexpr int const CANVAS_WIDTH{512};

constexpr std::size_t const REQUIRED_ARG_COUNT{4U};

#ifdef __APPLE__
constexpr int const MAX_SUPPORTED_ORDER{512};
#elif __linux__
constexpr int const MAX_SUPPORTED_ORDER{32};
#elif _WIN64
constexpr int const MAX_SUPPORTED_ORDER{64};
#else
constexpr int const MAX_SUPPORTED_ORDER{32};
#endif

constexpr std::size_t const ORDER_ARG_IDX{1U};
constexpr std::size_t const MARKX_ARG_IDX{2U};
constexpr std::size_t const MARKY_ARG_IDX{3U};
constexpr std::size_t const FORCE_ARG_IDX{4U};

constexpr std::size_t const FORCE_OPTION_STR_SIZE{2U};

} // namespace tromino::tromino2d::params

#endif // GUI_PARAMS_HPP_
