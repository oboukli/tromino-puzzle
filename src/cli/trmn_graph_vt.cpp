// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_vt.h"

#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

namespace tromino::cli::vt {

static constexpr std::size_t SPRITE_SIZE{4};

static std::array<char, SPRITE_SIZE> get_sprite(
    const trmn_flip_t& flip) noexcept {
    assert(-1 == flip.x || 1 == flip.x);
    assert(-1 == flip.y || 1 == flip.y);

    switch (flip.x) {
    case -1:
        switch (flip.y) {
        case -1:
            // -1, -1
            // X |
            // - +
            return {neutral, vertical, horizontal, bottom_right};

        case 1:
            [[fallthrough]];
        default:
            // -1, 1
            // - +
            // X |
            return {horizontal, top_right, neutral, vertical};
        };

    case 1:
        [[fallthrough]];
    default:
        switch (flip.y) {
        case -1:
            // 1, -1
            // | X
            // + -
            return {vertical, neutral, bottom_left, horizontal};

        case 1:
            [[fallthrough]];
        default:
            // 1, 1
            // + -
            // | X
            return {top_left, horizontal, vertical, neutral};
        };
    };
}

static inline void draw_at(const int x, const int y, const char c) noexcept {
    std::cout << CSI << y << ";" << x << "H" << c;
}

static inline void flush() noexcept {
    std::cout << std::flush;
}

void draw_board(const board_t& board) noexcept {
    const int order = board.order;
    for (int i = 0; i < order; ++i) { // Rows
        std::cout << CSI << 1 + i << ";" << 1 << "H";
        for (int j = 0; j < order; ++j) { // Columns
            std::cout << board.board_matrix[calc_index(j, i, order)];
        }
    }
}

void add_tromino(
    const trmn_position_t pos, const trmn_flip_t flip,
    void* const state) noexcept {
    constexpr std::chrono::milliseconds DELAY_AFTER(68);

    const graph_state_t* const graph_state = static_cast<graph_state_t*>(state);
    const board_t& board = graph_state->board;
    char* const board_matrix = board.board_matrix.get();
    const int order = board.order;
    const auto sprite = get_sprite(flip);

    char px;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            px = sprite[calc_index(j, i, 2)];
            if (neutral == px) {
                continue;
            }

            assert(
                (empty == board_matrix[calc_index(pos.x + j, pos.y + i, order)])
                && "Error: Invalid placement.");

            board_matrix[calc_index(pos.x + j, pos.y + i, order)] = px;

            draw_at(1 + pos.x + j, 1 + pos.y + i, px);
        }
    }

#ifdef _WINDOWS
    DWORD dwMode;
    ::GetConsoleMode(graph_state->hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    ::SetConsoleMode(graph_state->hOutput, dwMode);
#endif // _WINDOWS

    draw_at(order, order, '\0');

    flush();

    std::this_thread::sleep_for(DELAY_AFTER);
}

void use_vt(board_t& tromino_board) noexcept {
#ifdef _WINDOWS
    const HANDLE hStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwConsoleOriginalMode{0};
    DWORD dwConsoleModeRequiredFlags{
        ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING};
    DWORD dwConsoleModifiedMode;
    ::GetConsoleMode(hStdout, &dwConsoleOriginalMode);

    if ((dwConsoleOriginalMode & dwConsoleModeRequiredFlags)
        != dwConsoleModeRequiredFlags) {
        dwConsoleModifiedMode
            = dwConsoleOriginalMode | dwConsoleModeRequiredFlags;
        ::SetConsoleMode(hStdout, dwConsoleModifiedMode);
    }
#endif // _WINDOWS

    init_board(tromino_board);

    using namespace std::string_literals;
    std::cout << ""s +
            // clang-format off

        // Set icon and window title
        ESC + "]0;" "Tromino Puzzle"s + BEL +

        // Advanced video option (AVO)
        CSI + "?1;2c"s +

        // Column mode: 120 * 132 Col
        CSI + "?3h"s +

        // Enter the alternate buffer
        CSI + "?1049h"s +

        // Mode 320 * 200 color (256-color graphics)
        CSI + "=19h"s +

        // Make cursor invisible
        CSI + "?25l"s +

        // Disable line wrapping
        CSI + "=7l"s +

        // Relative origin mode
        CSI + "?6h"s +

        // Resize the window
        CSI + "8;132;132t"s +

        // Clears the entire screen
        CSI + "2J"s +

        // Set board background color
        CSI + "48;5;"s +
        BOARD_BACKGROUND_COLOR + "m"s;
    // clang-format on

    draw_board(tromino_board);
    flush();

    std::cout <<
        // clang-format off

        // Set bold mode
        CSI + "1m"s +

        // Set mark background color
        CSI + "48;5;"s + MARK_BACKGROUND_COLOR + "m"s +

        // Set mark foreground color
        CSI + "38;5;"s + MARK_FOREGROUND_COLOR + "m"s;
    // clang-format on

    draw_at(tromino_board.mark.x + 1, tromino_board.mark.y + 1, mark);

    std::cout <<
        // clang-format off

        // Set tromino background color
        CSI + "48;5;"s + TROMINO_BACKGROUND_COLOR + "m"s +

        // Set tromino foreground color
        CSI + "38;5;"s + TROMINO_FOREGROUND_COLOR + "m"s;
    // clang-format on

#ifndef TROMINO_USE_ASCII
    // Use VT100 Special graphics chararters
    std::cout << ESC + "(0"s;
#endif // !TROMINO_USE_ASCII

    flush();

    graph_state_t graph_state{.board = tromino_board};

    ::trmn_solve_puzzle(
        tromino_board.order, tromino_board.mark, add_tromino, &graph_state);

    std::cin.get();

    std::cout <<
        // clang-format off

        // Switch back VT100 Special graphics chararters
        ESC + "0)"s +

        // Reset to initial state (RIS)
        ESC + "c"s +

        // Exit the alternate buffer
        CSI + "?1049l"s;
    // clang-format on

    flush();

#ifdef _WINDOWS
    assert(0 != dwConsoleOriginalMode);
    ::SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WINDOWS
}

} // namespace tromino::cli::vt
