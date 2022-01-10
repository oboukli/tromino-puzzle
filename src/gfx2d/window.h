// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

class Window final
{
public:
    Window(int width);

    ~Window();

    void Init() noexcept;
    void Dispose() noexcept;

    [[nodiscard]] ::SDL_Window * GetSdlWindow() const noexcept;

private:
    ::SDL_Window * _window;
    int _width;
    bool _isInitialized;
};

} // namespace tromino::gfx2d

#endif // WINDOW_H_
