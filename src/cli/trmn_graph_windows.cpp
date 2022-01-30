// Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "trmn_graph_windows.h"

namespace tromino::cli::windows {

static std::array<char, sprite_size> get_sprite(trmn_flip_t flip) {
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
            break;

        case 1:
        default:
            // -1, 1
            // - +
            // X |
            return {horizontal, top_right, neutral, vertical};
            break;
        };
        break;

    case 1:
    default:
        switch (flip.y) {
        case -1:
            // 1, -1
            // | X
            // + -
            return {vertical, neutral, bottom_left, horizontal};
            break;

        case 1:
        default:
            // 1, 1
            // + -
            // | X
            return {top_left, horizontal, vertical, neutral};
            break;
        };
        break;
    };
}

inline void draw_at(int x, int y, char c) {
    std::cout << c;
}

inline void draw_at(int x, int y, char c, HANDLE hOutput) {
    COORD coord{
        .X{static_cast<SHORT>(x)},
        .Y{static_cast<SHORT>(y)},
    };

    SetConsoleCursorPosition(hOutput, coord);

    draw_at(x, y, c);
}

void draw_board(const board_t& board) {
    int order = board.order;
    for (int i = 0; i < order; ++i) { // Rows
        for (int j = 0; j < order; ++j) { // Columns
            std::cout << board.board_matrix[calc_index(j, i, order)];
        }

        std::cout << std::endl;
    }
}

void add_tromino(trmn_position_t pos, trmn_flip_t flip, void* state) {
    graph_state_t* graph_state = static_cast<graph_state_t*>(state);
    board_t& board = graph_state->board;
    char* board_matrix = board.board_matrix.get();
    int order = board.order;
    auto sprite = get_sprite(flip);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto px = sprite[calc_index(j, i, 2)];
            if (px == neutral) {
                continue;
            }

            assert(
                (board_matrix[calc_index(pos.x + j, pos.y + i, order)] == empty)
                && "Error: Invalid placement.");

            board_matrix[calc_index(pos.x + j, pos.y + i, order)] = px;

            draw_at(pos.x + j, pos.y + i, px, graph_state->hOutput);
        }
    }

    COORD coord{
        .X = static_cast<SHORT>(order) - 1,
        .Y = static_cast<SHORT>(order) - 1,
    };
    SetConsoleCursorPosition(graph_state->hOutput, coord);

    std::cout << std::endl;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(250)); // TODO: Add options to state
}

static void ensure_success(BOOL is_success, const std::string& msg) {
    if (!is_success) {
        auto error = GetLastError();
        // clang-format off
        std::cerr
            << "Windows API error: " << error
            << "Message: " << msg
            << std::endl;
        // clang-format on

        ExitProcess(EXIT_FAILURE);
    }
}

void use_wch(board_t& tromino_board) {
    SetConsoleTitle(TEXT("Tromino Puzzle")); // TODO:

    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    graph_state_t graph_state{
        .board = tromino_board,
        .hOutput = hConsoleOutput,
    };
    init_board(tromino_board);

    CONSOLE_SCREEN_BUFFER_INFO originalConsoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &originalConsoleScreenBufferInfo);

    SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
    draw_board(tromino_board);

    SetConsoleTextAttribute(
        hConsoleOutput,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    // clang-format off
    COORD coordMark = {
        .X = static_cast<short>(tromino_board.mark.x),
        .Y = static_cast<short>(tromino_board.mark.y)
    };
    // clang-format on
    SetConsoleCursorPosition(hConsoleOutput, coordMark);
    std::cout << mark;

    SetConsoleTextAttribute(
        hConsoleOutput,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    ::trmn_solve_puzzle(
        tromino_board.order, tromino_board.mark, add_tromino, &graph_state);

    SetConsoleTextAttribute(
        hConsoleOutput, originalConsoleScreenBufferInfo.wAttributes);
}

} // namespace tromino::cli::windows
