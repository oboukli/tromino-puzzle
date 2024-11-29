// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_windows.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <thread>

#include <tromino/core/tromino.h>

namespace tromino::cli::windows {

namespace {

constexpr char const neutral{'N'};
constexpr char const empty{'\xB0'};

constexpr char const mark{'\xFE'};
constexpr char const horizontal{'\xCD'};
constexpr char const vertical{'\xBA'};
constexpr char const top_left{'\xC9'};
constexpr char const top_right{'\xBB'};
constexpr char const bottom_left{'\xC8'};
constexpr char const bottom_right{'\xBC'};

void add_tromino(int pos_x, int pos_y, int flip_x, int flip_y, void* state);

void ensure_success(::BOOL is_success, std::string const& msg);

void draw_board(board_t const& board);

void init_board(board_t const& board) noexcept
{
    std::fill_n(board.board_matrix.get(), board.size, empty);

    board.board_matrix[calc_index(board.mark_x, board.mark_y, board.order)]
        = mark;
}

void draw_at(int const x, int const y, char const c)
{
    std::cout << c;
}

void draw_at(int const x, int const y, char const c, ::HANDLE const hOutput)
{
    ::COORD const coord{
        .X{static_cast<::SHORT>(x)},
        .Y{static_cast<::SHORT>(y)},
    };

    ::SetConsoleCursorPosition(hOutput, coord);

    draw_at(x, y, c);
}

void ensure_success(::BOOL const is_success, std::string const& msg)
{
    if (!is_success)
    {
        auto const error{::GetLastError()};
        // clang-format off
        std::cerr
            << "Windows API error: " << error
            << "Message: " << msg
            << std::endl;
        // clang-format on

        ::ExitProcess(EXIT_FAILURE);
    }
}

void draw_board(board_t const& board)
{
    int const order{board.order};
    for (int i{0}; i < order; ++i)
    {
        for (int j{0}; j < order; ++j)
        {
            std::cout << board.board_matrix[calc_index(j, i, order)];
        }

        std::cout << std::endl;
    }
}

void add_tromino(
    int const pos_x,
    int const pos_y,
    int const flip_x,
    int const flip_y,
    void* const state
)
{
    static constexpr std::chrono::milliseconds const DELAY_AFTER{68};

    graph_state_t const* graph_state{static_cast<graph_state_t*>(state)};
    board_t const& board{graph_state->board};
    char* const board_matrix{board.board_matrix.get()};
    int const order{board.order};
    auto const sprite{get_sprite<
        neutral,
        empty,
        mark,
        horizontal,
        vertical,
        top_left,
        top_right,
        bottom_left,
        bottom_right>(flip_x, flip_y)};

    char px{};
    for (int i{0}; i < 2; ++i)
    {
        for (int j{0}; j < 2; ++j)
        {
            px = sprite[calc_index(j, i, 2)];
            if (px != neutral)
            {
                // clang-format off
                assert(
                    (board_matrix[calc_index(pos_x + j, pos_y + i, order)]
                        == empty)
                    && "Error: Invalid placement.");
                // clang-format on

                board_matrix[calc_index(pos_x + j, pos_y + i, order)] = px;

                draw_at(pos_x + j, pos_y + i, px, graph_state->hOutput);
            }
        }
    }

    ::COORD const coord{
        .X = static_cast<::SHORT>(order) - short{1},
        .Y = static_cast<::SHORT>(order) - short{1},
    };
    ::SetConsoleCursorPosition(graph_state->hOutput, coord);

    std::cout << std::endl;
    std::this_thread::sleep_for(DELAY_AFTER);
}

} // namespace

void use_wch(board_t& tromino_board, std::ostream& os)
{
    ::SetConsoleTitle(TEXT("Tromino Puzzle"));

    ::HANDLE const hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
    graph_state_t graph_state{
        .os = os,
        .board = tromino_board,
        .hOutput = hConsoleOutput,
    };
    init_board(tromino_board);

    ::CONSOLE_SCREEN_BUFFER_INFO originalConsoleScreenBufferInfo{};
    ::GetConsoleScreenBufferInfo(
        ::GetStdHandle(STD_OUTPUT_HANDLE), &originalConsoleScreenBufferInfo
    );

    ::SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
    draw_board(tromino_board);

    ::SetConsoleTextAttribute(
        hConsoleOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
    );
    ::COORD const coordMark{
        .X = static_cast<::SHORT>(tromino_board.mark_x),
        .Y = static_cast<::SHORT>(tromino_board.mark_y)
    };
    ::SetConsoleCursorPosition(hConsoleOutput, coordMark);
    std::cout << mark;

    ::SetConsoleTextAttribute(
        hConsoleOutput,
        FOREGROUND_RED
            | FOREGROUND_GREEN
            | FOREGROUND_INTENSITY
            | BACKGROUND_BLUE
            | BACKGROUND_INTENSITY
    );

    int const stop_flag{0};

    ::trmn_solve_puzzle(
        tromino_board.order,
        tromino_board.mark_x,
        tromino_board.mark_y,
        add_tromino,
        &graph_state,
        &stop_flag
    );

    ::SetConsoleTextAttribute(
        hConsoleOutput, originalConsoleScreenBufferInfo.wAttributes
    );
}

} // namespace tromino::cli::windows
