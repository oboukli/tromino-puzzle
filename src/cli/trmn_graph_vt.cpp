// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "trmn_graph_vt.h"

namespace tromino::vt {

    static std::array<char, sprite_size> get_sprite(flip_t flip) {
        assert(-1 == flip.x || 1 == flip.x);
        assert(-1 == flip.y || 1 == flip.y);

        switch (flip.x) {
        case -1:
            switch (flip.y) {
            case -1:
                // -1, -1
                // X |
                // - +
                return { neutral, vertical, horizontal, bottom_right };
                break;

            case 1:
            default:
                // -1, 1
                // - +
                // X |
                return { horizontal, top_right, neutral, vertical };
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
                return { vertical, neutral, bottom_left, horizontal };
                break;

            case 1:
            default:
                // 1, 1
                // + -
                // | X
                return { top_left, horizontal, vertical, neutral };
                break;
            };
            break;
        };
    }

    static inline void draw_at(int x, int y, char c) {
        std::cout << CSI << y << ";" << x << "H" << c;
    }

    inline void flush() {
        std::cout << std::flush;
    }

    void draw_board(const tromino::board_t& board) {
        int order = board.order;
        for (int i = 0; i < order; ++i) { // Rows
            std::cout << CSI << 1 + i << ";" << 1 << "H";
            for (int j = 0; j < order; ++j) { // Columns
                std::cout << board.board_matrix[tromino::calc_index(j, i, order)];
            }
        }
    }

    void add_tromino(position_t abspos, flip_t flip, void* state) {
        graph_state_t* graph_state = static_cast<graph_state_t*>(state);
        board_t& board = graph_state->board;
        char* board_matrix = board.board_matrix.get();
        int order = board.order;
        auto sprite = get_sprite(flip);

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                auto px = sprite[calc_index(j, i, 2)];
                if (neutral == px) {
                    continue;
                }

                assert((empty == board_matrix[calc_index(abspos.x + j, abspos.y + i, order)])
                    && "Error: Invalid placement.");

                board_matrix[calc_index(abspos.x + j, abspos.y + i, order)] = px;

                draw_at(1 + abspos.x + j, 1 + abspos.y + i, px);
            }
        }

#ifdef _WINDOWS
        DWORD dwMode;
        GetConsoleMode(graph_state->hOutput, &dwMode);
        dwMode |=
            ENABLE_PROCESSED_OUTPUT
            | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(graph_state->hOutput, dwMode);
#endif // _WINDOWS

        draw_at(order, order, '\0');

        flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // TODO: Add options to state
    }

    void use_vt(tromino::board_t& tromino_board) {
#ifdef _WINDOWS
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        DWORD dwConsoleOriginalMode = 0;
        DWORD dwConsoleModifiedMode;
        GetConsoleMode(hStdout, &dwConsoleOriginalMode);

        // TODO: if

        dwConsoleModifiedMode =
            dwConsoleOriginalMode
            | ENABLE_PROCESSED_OUTPUT
            | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hStdout, dwConsoleModifiedMode);
#endif // _WINDOWS

        tromino::vt::init_board(tromino_board);

        std::cout <<

            // Set icon and window title
            ESC "]0;" "Tromino Puzzle" BEL

            // Advanced video option (AVO)
            CSI "?1;2c"

            // Column mode: 120 * 132 Col
            CSI "?3h"

            // Enter the alternate buffer
            CSI "?1049h"

            // Mode 320 * 200 color (256-color graphics)
            CSI "=19h"

            // Make cursor invisible
            CSI "?25l"

            // Disable line wrapping
            CSI "=7l"

            // Relative origin mode
            CSI "?6h"

            // Resize the window
            CSI "8;132;132t"

            // Clears the entire screen
            CSI "2J";

        std::cout <<
            // Set board background color.
            CSI "48;5;" BOARD_BACKGROUND_COLOR "m";
        tromino::vt::draw_board(tromino_board);

        flush();

        std::cout <<
            // Set bold mode
            CSI "1m"

            // Set mark background color
            CSI "48;5;" MARK_BACKGROUND_COLOR "m"

            // Set mark foreground color
            CSI "38;5;" MARK_FOREGROUND_COLOR "m";

        tromino::vt::draw_at(tromino_board.mark.x + 1, tromino_board.mark.y + 1, tromino::vt::mark);

        std::cout <<

            // Set tromino background color
            CSI "48;5;" TROMINO_BACKGROUND_COLOR "m"

            // Set tromino foreground color
            CSI "38;5;" TROMINO_FOREGROUND_COLOR "m";

#ifndef TROMINO_USE_ASCII
        // Use VT100 Special graphics chararters
        std::cout <<
            ESC "(0";
#endif // !TROMINO_USE_ASCII

        flush();

        tromino::graph_state_t graph_state{
            .board = tromino_board
        };

        solve_tromino_puzzle(tromino_board.order, tromino_board.mark, tromino::vt::add_tromino, &graph_state);

        std::cin.get();

        std::cout <<

            // Switch back VT100 Special graphics chararters
            ESC "0)"

            // Reset to initial state (RIS)
            ESC "c"

            // Exit the alternate buffer
            CSI "?1049l";

        flush();

#ifdef _WINDOWS
        assert(0 != dwConsoleOriginalMode);
        SetConsoleMode(hStdout, dwConsoleOriginalMode);
#endif // _WINDOWS
    }

} // namespace tromino::vt
