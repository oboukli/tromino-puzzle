// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_vt.hpp"
#include "wrapper.hpp"

#include <array>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <thread>

namespace tromino::cli::vt {

namespace {

inline void
draw_at(int const x, int const y, char const c, std::ostream& os) noexcept {
    os << CSI << y << ";" << x << "H" << c;
}

} // namespace

void draw_board(board_t const& board, std::ostream& os) noexcept {
    int const order{board.order};
    for (int i{0}; i < order; ++i) { // Rows
        os << CSI << 1 + i << ";" << 1 << "H";
        for (int j{0}; j < order; ++j) { // Columns
            os << board.board_matrix[calc_index(j, i, order)];
        }
    }
}

void add_tromino(
    int const pos_x, int const pos_y, int const flip_x, int const flip_y,
    graph_state_t* const graph_state) noexcept {
    static constexpr std::chrono::milliseconds const DELAY_AFTER{68};

    std::ostream& os{graph_state->os};
    board_t const& board{graph_state->board};
    char* const board_matrix{board.board_matrix.get()};
    int const order{board.order};
    auto const sprite{get_sprite<
        NEUTRAL, EMPTY, MARK, HORIZONTAL, VERTICAL, TOP_LEFT, TOP_RIGHT,
        BOTTOM_LEFT, BOTTOM_RIGHT>(flip_x, flip_y)};

    char px{};
    for (int i{0}; i < 2; ++i) {
        for (int j{0}; j < 2; ++j) {
            px = sprite[calc_index(j, i, 2)];
            if (px != NEUTRAL) {
                // clang-format off
                assert(
                    (board_matrix[calc_index(pos_x + j, pos_y + i, order)]
                        == EMPTY)
                    && "Error: Invalid placement.");
                // clang-format on

                board_matrix[calc_index(pos_x + j, pos_y + i, order)] = px;

                draw_at(1 + pos_x + j, 1 + pos_y + i, px, os);
            }
        }
    }

#ifdef _WINDOWS
    DWORD dwMode{};
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
    HANDLE const hStdout{::GetStdHandle(STD_OUTPUT_HANDLE)};

    DWORD dwConsoleOriginalMode{};
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

    using std::string_literals::operator""s;
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

    draw_at(tromino_board.mark_x + 1, tromino_board.mark_y + 1, MARK, os);

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

    SolverState<graph_state_t> solver_state{
        .state = &graph_state, .callback = add_tromino};
    ::trmn_solve_puzzle(
        tromino_board.order, tromino_board.mark_x, tromino_board.mark_y,
        ::solve_puzzle_cb, static_cast<void*>(&solver_state));

    std::cin.get();

    // clang-format off
    os <<
        // Switch back VT100 Special graphics characters
        ESC + "0)"s +

        // Reset to initial state (RIS)
        ESC + "c"s +

        // Exit the alternate buffer
        CSI + "?1049l"s;
    // clang-format on

    os << std::flush;

#ifdef _WINDOWS
    assert(dwConsoleOriginalMode != 0);
    ::SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WINDOWS
}

} // namespace tromino::cli::vt
