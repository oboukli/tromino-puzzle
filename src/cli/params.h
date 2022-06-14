// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef PARAMS_H
#define PARAMS_H

namespace tromino::cli::params {

constexpr int REQUIRED_ARG_COUNT{4};

constexpr int ORDER_ARG_IDX{1};
constexpr int MARKX_ARG_IDX{2};
constexpr int MARKY_ARG_IDX{3};

#ifdef _WINDOWS
constexpr int USE_WCH_ARG_IDX{4};
#endif

} // namespace tromino::cli::params

#endif // PARAMS_H
