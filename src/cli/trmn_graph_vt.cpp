// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_vt.h"

#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <thread>

namespace tromino::cli::vt {

namespace {

inline void draw_at(
    const int x, const int y, const char c, std::ostream& os) noexcept {
    os << CSI << y << ";" << x << "H" << c;
}

} // namespace

void draw_board(const board_t& board, std::ostream& os) noexcept {
    const int order = board.order;
    for (int i = 0; i < order; ++i) { // Rows
        os << CSI << 1 + i << ";" << 1 << "H";
        for (int j = 0; j < order; ++j) { // Columns
            os << board.board_matrix[calc_index(j, i, order)];
        }
    }
}

void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    constexpr std::chrono::milliseconds DELAY_AFTER(68);

    const graph_state_t* const graph_state = static_cast<graph_state_t*>(state);
    std::ostream& os = graph_state->os;
    const board_t& board = graph_state->board;
    char* const board_matrix = board.board_matrix.get();
    const int order = board.order;
    const auto sprite = get_sprite<
        neutral, empty, mark, horizontal, vertical, top_left, top_right,
        bottom_left, bottom_right>(flip_x, flip_y);

    char px;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            px = sprite[calc_index(j, i, 2)];
            if (neutral == px) {
                continue;
            }

            assert(
                (empty == board_matrix[calc_index(pos_x + j, pos_y + i, order)])
                && "Error: Invalid placement.");

            board_matrix[calc_index(pos_x + j, pos_y + i, order)] = px;

            draw_at(1 + pos_x + j, 1 + pos_y + i, px, os);
        }
    }

#ifdef _WINDOWS
    DWORD dwMode;
    ::GetConsoleMode(graph_state->hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    ::SetConsoleMode(graph_state->hOutput, dwMode);
#endif // _WINDOWS

    draw_at(order, order, '\0', os);

    os << std::flush;

    std::this_thread::sleep_for(DELAY_AFTER);
}

void use_vt(board_t& tromino_board, std::ostream& os) noexcept {
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
    // clang-format off
    os << ""s +
        // Set icon and window title
        ESC + "]0;"s + "Tromino Puzzle"s + BEL +

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

    draw_board(tromino_board, os);

    // clang-format off
    os <<
        // Set bold mode
        CSI + "1m"s +

        // Set mark background color
        CSI + "48;5;"s + MARK_BACKGROUND_COLOR + "m"s +

        // Set mark foreground color
        CSI + "38;5;"s + MARK_FOREGROUND_COLOR + "m"s;
    // clang-format on

    draw_at(tromino_board.mark_x + 1, tromino_board.mark_y + 1, mark, os);

    // clang-format off
    os <<
        // Set tromino background color
        CSI + "48;5;"s + TROMINO_BACKGROUND_COLOR + "m"s +

        // Set tromino foreground color
        CSI + "38;5;"s + TROMINO_FOREGROUND_COLOR + "m"s;
    // clang-format on

#ifndef TROMINO_USE_ASCII
    // Use VT100 Special graphics characters
    os << ESC + "(0"s;
#endif // !TROMINO_USE_ASCII

    os << std::flush;

    graph_state_t graph_state{.os = os, .board = tromino_board};

    ::trmn_solve_puzzle(
        tromino_board.order, tromino_board.mark_x, tromino_board.mark_y,
        add_tromino, &graph_state);

    std::cin.get();

    // clang-format off
    os <<
        // Switch back VT100 Special graphics chararters
        ESC + "0)"s +

        // Reset to initial state (RIS)
        ESC + "c"s +

        // Exit the alternate buffer
        CSI + "?1049l"s;
    // clang-format on

    os << std::flush;

#ifdef _WINDOWS
    assert(0 != dwConsoleOriginalMode);
    ::SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WINDOWS
}

} // namespace tromino::cli::vt
