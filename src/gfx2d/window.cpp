// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "window.h"

namespace tromino::gfx2d {

Window::Window(int width):
    _window(nullptr),
    _width(width),
    _isInitialized(false) {
}

Window::~Window() {
    Dispose();
}

void Window::Init() noexcept {
    _window = ::SDL_CreateWindow("Tromino Puzzle", // TODO:
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width,
        _width,
        ::SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI);

    _isInitialized = true; // TODO: Check for errors
}

[[nodiscard]] ::SDL_Window * Window::GetSdlWindow() const noexcept {
    return _window;
}

void Window::Dispose() noexcept {
    if (_window) {
        ::SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    _isInitialized = false; // TODO: Check for errors
}

} // namespace tromino::gfx2d
