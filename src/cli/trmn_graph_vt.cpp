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
draw_at(int const x, int const y, char const c, std::ostream& os) noexcept
{
    os << CSI << y << ";" << x << "H" << c;
}

} // namespace

void draw_board(board_t const& board, std::ostream& os) noexcept
{
    int const order{board.order};
    for (int i{0}; i < order; ++i)
    {
        os << CSI << 1 + i << ";" << 1 << "H";
        for (int j{0}; j < order; ++j)
        {
            os << board.board_matrix[calc_index(j, i, order)];
        }
    }
}

void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    graph_state_t* const graph_state) noexcept
{
    static constexpr std::chrono::milliseconds const DELAY_AFTER{68};

    std::ostream& os{graph_state->os};
    board_t const& board{graph_state->board};
    char* const board_matrix{board.board_matrix.get()};
    int const order{board.order};
    auto const sprite{get_sprite<
        NEUTRAL,
        EMPTY,
        MARK,
        HORIZONTAL,
        VERTICAL,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT>(flip_x, flip_y)};

    char px{};
    for (int i{0}; i < 2; ++i)
    {
        for (int j{0}; j < 2; ++j)
        {
            px = sprite[calc_index(j, i, 2)];
            if (px != NEUTRAL)
            {
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

#ifdef _WIN64
    ::DWORD dwMode{};
    ::GetConsoleMode(graph_state->hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    ::SetConsoleMode(graph_state->hOutput, dwMode);
#endif // _WIN64

    draw_at(order, order, '\0', os);

    os << std::flush;

    std::this_thread::sleep_for(DELAY_AFTER);
}

void use_vt(board_t& tromino_board, std::ostream& os) noexcept
{
#ifdef _WIN64
    ::HANDLE const hStdout{::GetStdHandle(STD_OUTPUT_HANDLE)};

    ::DWORD dwConsoleOriginalMode{};
    ::GetConsoleMode(hStdout, &dwConsoleOriginalMode);

    ::DWORD dwConsoleModeRequiredFlags{
        ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING};
    if ((dwConsoleOriginalMode & dwConsoleModeRequiredFlags)
        != dwConsoleModeRequiredFlags)
    {
        ::DWORD dwConsoleModifiedMode{
            dwConsoleOriginalMode | dwConsoleModeRequiredFlags};
        ::SetConsoleMode(hStdout, dwConsoleModifiedMode);
    }
#endif // _WIN64

    init_board(tromino_board);

    // clang-format off
    os
        // Set icon and window title
        << ESC << "]0;" << TITLE << BEL

        // Advanced video option (AVO)
        << CSI << "?1;2c"

        // Column mode: 120 * 132 Col
        << CSI << "?3h"

        // Enter the alternate buffer
        << CSI << "?1049h"

        // Mode 320 * 200 color (256-color graphics)
        << CSI << "=19h"

        // Make cursor invisible
        << CSI << "?25l"

        // Disable line wrapping
        << CSI << "=7l"

        // Relative origin mode
        << CSI << "?6h"

        // Resize the window
        << CSI << "8;132;132t"

        // Clears the entire screen
        << CSI << "2J"

        // Set board background color
        << CSI << "48;5;" << BOARD_BACKGROUND_COLOR << "m";
    // clang-format on

    draw_board(tromino_board, os);

    // clang-format off
    os
        // Set bold mode
        << CSI << "1m"

        // Set mark background color
        << CSI << "48;5;" << MARK_BACKGROUND_COLOR << "m"

        // Set mark foreground color
        << CSI << "38;5;" << MARK_FOREGROUND_COLOR << "m"

        ;
    // clang-format on

    draw_at(tromino_board.mark_x + 1, tromino_board.mark_y + 1, MARK, os);

    // clang-format off
    os
        // Set tromino background color
        << CSI << "48;5;" << TROMINO_BACKGROUND_COLOR << "m"

        // Set tromino foreground color
        << CSI << "38;5;" << TROMINO_FOREGROUND_COLOR << "m"

#ifndef TROMINO_USE_ASCII
        // Use VT100 Special graphics characters
        << ESC << "(0"
#endif // not TROMINO_USE_ASCII

        ;
    // clang-format on

    os << std::flush;

    graph_state_t graph_state{.os = os, .board = tromino_board};

    SolverState<graph_state_t> solver_state{
        .state = &graph_state, .callback = add_tromino};
    int const stop_flag{0};
    ::trmn_solve_puzzle(
        tromino_board.order,
        tromino_board.mark_x,
        tromino_board.mark_y,
        ::solve_puzzle_cb,
        static_cast<void*>(&solver_state),
        &stop_flag);

    std::cin.get();

    // clang-format off
    os
        // Switch back VT100 Special graphics characters
        << ESC << "0)"

        // Reset to initial state (RIS)
        << ESC << "c"

        // Exit the alternate buffer
        << CSI << "?1049l"

    ;
    // clang-format on

    os << std::flush;

#ifdef _WIN64
    assert(dwConsoleOriginalMode != 0);
    ::SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WIN64
}

} // namespace tromino::cli::vt
