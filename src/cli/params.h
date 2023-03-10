// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef CLI_PARAMS_H
#define CLI_PARAMS_H

namespace tromino::cli::params {

constexpr const int REQUIRED_ARG_COUNT{4};

constexpr const int ORDER_ARG_IDX{1};
constexpr const int MARKX_ARG_IDX{2};
constexpr const int MARKY_ARG_IDX{3};

#ifdef _WINDOWS
constexpr const int USE_WCH_ARG_IDX{4};
#endif

} // namespace tromino::cli::params

#endif // CLI_PARAMS_H
