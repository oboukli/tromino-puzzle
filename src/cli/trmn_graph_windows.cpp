// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "trmn_graph_windows.h"

namespace trimino::windows {

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
                // -1, 1
                // - +
                // X |
                return { horizontal, top_right, neutral, vertical };
                break;
            };
            break;

        case 1:
            switch (rot.y) {
            case -1:
                // 1, -1
                // | X
                // + -
                return { vertical, neutral, bottom_left, horizontal };
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

    inline void draw_at(int x, int y, char c) {
        std::cout << c; // TODO: Do not assume we are writing to STDOUT
    }

    inline void draw_at(int x, int y, char c, HANDLE hOutput) {
        COORD coord{
            .X { (SHORT)x },
            .Y { (SHORT)y },
        };

        SetConsoleCursorPosition(hOutput, coord);

        draw_at(x, y, c);
    }

    void draw_board(const board* board) {
        int order = board->order;
        for (int i = 0; i < order; ++i) { // Rows
            for (int j = 0; j < order; ++j) { // Columns
                std::cout << board->board_matrix[calc_index(j, i, order)];
            }

            std::cout << std::endl;
        }
    }

    void add_trimino(position abspos, rotation rot, void* state) {
        graph_state* s = static_cast<graph_state*>(state); // TODO: Rename
        board* board = s->board;
        char* board_matrix = board->board_matrix.get();
        int order = board->order;
        auto sprite = get_sprite(rot);

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                auto px = sprite[calc_index(j, i, 2)];
                if (px == neutral) {
                    continue;
                }

                assert((board_matrix[calc_index(abspos.x + j, abspos.y + i, order)] == empty) && "Error: Invalid placement.");

                board_matrix[calc_index(abspos.x + j, abspos.y + i, order)] = px;

                draw_at(abspos.x + j, abspos.y + i, px, s->hOutput);
            }
        }

        COORD coord{
            .X = (SHORT)order - 1,
            .Y = (SHORT)order - 1,
        };
        SetConsoleCursorPosition(s->hOutput, coord);

        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // TODO: Add options to state
    }

} // namespace trimino::windows
