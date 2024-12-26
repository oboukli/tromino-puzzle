// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_WINDOW_HPP
#define TROMINO_GFX2D_WINDOW_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <optional>
#include <string>

namespace tromino::gfx2d {

class [[nodiscard]] Window final {
public:
    Window() noexcept = delete;

    explicit Window(
        std::optional<std::string const> const& title, int width
    ) noexcept;

    Window(Window const&) noexcept = delete;

    Window(Window&&) noexcept = delete;

    ~Window() noexcept = default;

    Window& operator=(Window const&) noexcept = delete;

    Window& operator=(Window&&) noexcept = delete;

    [[nodiscard]] ::SDL_Window* GetSdlWindow() const noexcept;

private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _window;
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_WINDOW_HPP
