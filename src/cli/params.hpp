// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_PARAMS_HPP
#define CLI_PARAMS_HPP

namespace tromino::cli::params {

constexpr int const REQUIRED_ARG_COUNT{4};

constexpr int const ORDER_ARG_IDX{1};
constexpr int const MARKX_ARG_IDX{2};
constexpr int const MARKY_ARG_IDX{3};

#ifdef _WINDOWS
constexpr int const USE_WCH_ARG_IDX{4};
#endif

} // namespace tromino::cli::params

#endif // CLI_PARAMS_HPP
