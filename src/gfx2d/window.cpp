// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "window.hpp"

namespace tromino::gfx2d {

namespace {

#ifdef __EMSCRIPTEN__
constexpr ::Uint32 const WINDOW_FLAGS{0};
#else
constexpr ::Uint32 const WINDOW_FLAGS{
    ::SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI
    | ::SDL_WindowFlags::SDL_WINDOW_SHOWN};
#endif // __EMSCRIPTEN__

} // namespace

Window::Window(std::string const& title, int const width) noexcept :
    _window{
        ::SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, width, WINDOW_FLAGS),
        &::SDL_DestroyWindow} {
}

[[nodiscard]] ::SDL_Window* Window::GetSdlWindow() const noexcept {
    return _window.get();
}

} // namespace tromino::gfx2d
