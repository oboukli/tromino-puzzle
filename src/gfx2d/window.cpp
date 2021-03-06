// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "window.h"

namespace tromino::gfx2d {

#ifdef __EMSCRIPTEN__
constexpr auto WINDOW_FLAGS{0};
#else
constexpr auto WINDOW_FLAGS = ::SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI
    | ::SDL_WindowFlags::SDL_WINDOW_SHOWN;
#endif // __EMSCRIPTEN__

Window::Window(const std::string& title, const int width) noexcept :
    _window(
        ::SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, width, WINDOW_FLAGS),
        &::SDL_DestroyWindow) {
}

Window::~Window() noexcept = default;

[[nodiscard]] ::SDL_Window* Window::GetSdlWindow() const noexcept {
    return _window.get();
}

} // namespace tromino::gfx2d
