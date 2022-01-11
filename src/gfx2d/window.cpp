// Copyright (c) Omar Boukli-Hacene 2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "window.h"

namespace tromino::gfx2d {

Window::Window(const char * title, int width) noexcept:
    _window(nullptr, ::SDL_DestroyWindow) {
    _window.reset(::SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        width,
        ::SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI));
}

Window::~Window() noexcept {
}

[[nodiscard]] ::SDL_Window * Window::GetSdlWindow() const noexcept {
    return _window.get();
}

} // namespace tromino::gfx2d
