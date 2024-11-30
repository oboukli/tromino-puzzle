// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "window.hpp"

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <optional>
#include <string>

namespace tromino::gfx2d {

namespace {

#ifdef __EMSCRIPTEN__
constexpr ::Uint32 const WINDOW_FLAGS{0};
#else
constexpr ::Uint32 const WINDOW_FLAGS{
    ::SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI
    | ::SDL_WindowFlags::SDL_WINDOW_SHOWN
};
#endif // __EMSCRIPTEN__

} // namespace

Window::Window(
    std::optional<std::string const> const& title, int const width
) noexcept :
    _window{
        ::SDL_CreateWindow(
            title ? title.value().c_str() : nullptr,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            width,
            WINDOW_FLAGS
        ),
        &::SDL_DestroyWindow
    }
{
}

[[nodiscard]] ::SDL_Window* Window::GetSdlWindow() const noexcept
{
    return _window.get();
}

} // namespace tromino::gfx2d
