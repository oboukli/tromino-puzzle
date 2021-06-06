// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "trimino.h"
#include "trmn_graph.h"

namespace trimino {

std::array<char, sprite_size> get_sprite(rotation rot) {
    switch (rot.x) {
        case -1:
            switch (rot.y) {
                case -1:
                    // -1, -1
                    // X |
                    // - +
                    return { neutral, vertical, horizontal, bottom_right };
                    break;

                case 1:
                    // 1, -1
                    // | X
                    // + -
                    return { vertical, neutral, bottom_left, horizontal };
                    break;
            };
            break;

        case 1:
            switch (rot.y) {
                case -1:
                    // -1, 1
                    // - +
                    // X |
                    return { horizontal, top_right, neutral, vertical };
                    break;

                case 1:
                    // 1, 1
                    // + -
                    // | X
                    return { top_left, horizontal, vertical, neutral };
                    break;
            };
            break;
    };

    return { neutral, neutral, neutral, neutral };
}

void draw_at(int x, int y, char c) {
#ifdef _WINDOWS
    COORD coord {
        .X { (SHORT)x },
        .Y { (SHORT)y },
    };

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hStdout, coord);

    std::cout << c;
#else
    std::cout << "\e[" << y << ";" << x << "H" << c;
#endif
}

void draw_board(const trimino_board * board) {
    int order = board->order;
    for (int i = 0; i < order; ++i) { // Rows
        for (int j = 0; j < order; ++j) { // Columns
            std::cout << board->board[calc_index(j, i, order)];
        }

        std::cout << std::endl;
    }
}

void add_trimino(position abspos, rotation rot, void * state) {
    trimino_board * boardstate = static_cast<trimino_board*>(state);
    char * board = boardstate->board.get();
    int order = boardstate->order;
    auto sprite = trimino::get_sprite(rot);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto px = sprite[calc_index(j, i, 2)];
            if (px == trimino::neutral) {
                continue;
            }

            assert((board[calc_index(abspos.y + j, abspos.x + i, order)] == trimino::empty) && "Error: Invalid placement.");

            board[calc_index(abspos.y + j, abspos.x + i, order)] = px;
            draw_at(abspos.y + j, abspos.x + i, px);
        }
    }

    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(250)); // TODO: Add options to state
}

} // namespace trimino
