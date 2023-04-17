// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_windows.h"

#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

namespace tromino::cli::windows {

namespace {

inline void draw_at(const int x, const int y, const char c) noexcept {
    std::cout << c;
}

inline void draw_at(
    const int x, const int y, const char c, const HANDLE hOutput) noexcept {
    const COORD coord{
        .X{static_cast<SHORT>(x)},
        .Y{static_cast<SHORT>(y)},
    };

    ::SetConsoleCursorPosition(hOutput, coord);

    draw_at(x, y, c);
}

void ensure_success(const BOOL is_success, const std::string& msg) noexcept {
    if (!is_success) {
        const auto error{::GetLastError()};
        // clang-format off
        std::cerr
            << "Windows API error: " << error
            << "Message: " << msg
            << std::endl;
        // clang-format on

        ::ExitProcess(EXIT_FAILURE);
    }
}

} // namespace

void draw_board(const board_t& board) noexcept {
    const int order{board.order};
    for (int i = 0; i < order; ++i) { // Rows
        for (int j = 0; j < order; ++j) { // Columns
            std::cout << board.board_matrix[calc_index(j, i, order)];
        }

        std::cout << std::endl;
    }
}

void add_tromino(
    const int pos_x, const int pos_y, const int flip_x, const int flip_y,
    void* const state) noexcept {
    constexpr const std::chrono::milliseconds DELAY_AFTER{68};

    const graph_state_t* graph_state{static_cast<graph_state_t*>(state)};
    const board_t& board{graph_state->board};
    char* const board_matrix{board.board_matrix.get()};
    const int order{board.order};
    const auto sprite{get_sprite<
        neutral, empty, mark, horizontal, vertical, top_left, top_right,
        bottom_left, bottom_right>(flip_x, flip_y)};

    char px{};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            px = sprite[calc_index(j, i, 2)];
            if (px == neutral) {
                continue;
            }

            assert(
                (board_matrix[calc_index(pos_x + j, pos_y + i, order)] == empty)
                && "Error: Invalid placement.");

            board_matrix[calc_index(pos_x + j, pos_y + i, order)] = px;

            draw_at(pos_x + j, pos_y + i, px, graph_state->hOutput);
        }
    }

    const COORD coord{
        .X = static_cast<SHORT>(order) - 1,
        .Y = static_cast<SHORT>(order) - 1,
    };
    ::SetConsoleCursorPosition(graph_state->hOutput, coord);

    std::cout << std::endl;
    std::this_thread::sleep_for(DELAY_AFTER);
}

void use_wch(board_t& tromino_board, std::ostream& os) noexcept {
    ::SetConsoleTitle(TEXT("Tromino Puzzle"));

    const HANDLE hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
    graph_state_t graph_state{
        .os = os,
        .board = tromino_board,
        .hOutput = hConsoleOutput,
    };
    init_board(tromino_board);

    CONSOLE_SCREEN_BUFFER_INFO originalConsoleScreenBufferInfo;
    ::GetConsoleScreenBufferInfo(
        ::GetStdHandle(STD_OUTPUT_HANDLE), &originalConsoleScreenBufferInfo);

    ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
    draw_board(tromino_board);

    ::SetConsoleTextAttribute(
        hConsoleOutput,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    // clang-format off
    const COORD coordMark{
        .X = static_cast<SHORT>(tromino_board.mark_x),
        .Y = static_cast<SHORT>(tromino_board.mark_y)
    };
    // clang-format on
    ::SetConsoleCursorPosition(hConsoleOutput, coordMark);
    std::cout << mark;

    ::SetConsoleTextAttribute(
        hConsoleOutput,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    ::trmn_solve_puzzle(
        tromino_board.order, tromino_board.mark_x, tromino_board.mark_y,
        add_tromino, &graph_state);

    ::SetConsoleTextAttribute(
        hConsoleOutput, originalConsoleScreenBufferInfo.wAttributes);
}

} // namespace tromino::cli::windows
