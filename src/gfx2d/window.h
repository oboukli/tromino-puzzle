// Copyright (c) Omar Boukli-Hacene 2022. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>

#include <memory>

namespace tromino::gfx2d {

class Window final
{
public:
    Window(const char * title, int width) noexcept;

    ~Window() noexcept;

    [[nodiscard]] ::SDL_Window * GetSdlWindow() const noexcept;

private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _window;
};

} // namespace tromino::gfx2d

#endif // WINDOW_H_
