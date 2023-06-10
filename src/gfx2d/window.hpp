// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef GFX2D_WINDOW_HPP
#define GFX2D_WINDOW_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <string>

namespace tromino::gfx2d {

class Window final {
public:
    Window() noexcept = delete;

    explicit Window(std::string const& title, int const width) noexcept;

    ~Window() noexcept;

    [[nodiscard]] ::SDL_Window* GetSdlWindow() const noexcept;

private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _window;
};

} // namespace tromino::gfx2d

#endif // GFX2D_WINDOW_HPP