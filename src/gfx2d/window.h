// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <memory>
#include <string>

namespace tromino::gfx2d {

class Window final {
public:
    explicit Window(const std::string& title, const int width) noexcept;

    ~Window() noexcept;

    [[nodiscard]] ::SDL_Window* GetSdlWindow() const noexcept;

private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _window;
};

} // namespace tromino::gfx2d

#endif // WINDOW_H
