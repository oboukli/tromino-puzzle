// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef TROMINO_GFX2D_WINDOW_HPP_
#define TROMINO_GFX2D_WINDOW_HPP_

#include <SDL2/SDL_video.h>

#include <memory>
#include <optional>
#include <string>

namespace tromino::gfx2d {

class [[nodiscard]] Window final {
public:
    explicit Window(
        std::optional<std::string const> const& title, int width
    ) noexcept;

    Window(Window const&) = delete;

    Window(Window&&) = delete;

    ~Window() noexcept = default;

    Window& operator=(Window const&) = delete;

    Window& operator=(Window&&) = delete;

    [[nodiscard]] ::SDL_Window* GetSdlWindow() const noexcept;

private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _window;
};

} // namespace tromino::gfx2d

#endif // TROMINO_GFX2D_WINDOW_HPP_
