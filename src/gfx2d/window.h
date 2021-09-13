// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef window_h
#define window_h

#include <SDL2/SDL.h>

namespace tromino::gfx2d {

class Window
{
public:
    Window(int width);
    ~Window();
    
    void Init() noexcept;
    void Dispose() noexcept;
    
    SDL_Window* GetSdlWindow() const noexcept;

private:
    int _width;
    bool _isInitialized;
    SDL_Window* _window;
};

} // namespace tromino::gfx2d

#endif // window_h
