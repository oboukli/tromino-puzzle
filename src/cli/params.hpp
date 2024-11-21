// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_PARAMS_HPP
#define CLI_PARAMS_HPP

#include <cstddef>

namespace tromino::cli::params {

constexpr int const REQUIRED_ARG_COUNT{4};

constexpr std::size_t const ORDER_ARG_IDX{1U};
constexpr std::size_t const MARKX_ARG_IDX{2U};
constexpr std::size_t const MARKY_ARG_IDX{3U};

#ifdef _WIN64
constexpr std::size_t const USE_WCH_ARG_IDX{4U};
#endif // _WIN64

} // namespace tromino::cli::params

#endif // CLI_PARAMS_HPP
