// Copyright (c) Omar Boukli-Hacene 2021. All Rights Reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

#include "trmn_graph_windows.h"

namespace tromino::windows {

    static std::array<char, sprite_size> get_sprite(rotation_t rot) {
        assert(-1 == rot.x || 1 == rot.x);
        assert(-1 == rot.y || 1 == rot.y);

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
            switch (rot.y) {
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

    void draw_board(const tromino::board_t& board) {
        int order = board.order;
        for (int i = 0; i < order; ++i) { // Rows
            for (int j = 0; j < order; ++j) { // Columns
                std::cout << board.board_matrix[calc_index(j, i, order)];
            }

            std::cout << std::endl;
        }
    }

    void add_tromino(position_t abspos, rotation_t rot, void* state) {
        graph_state_t* graph_state = static_cast<graph_state_t*>(state);
        board_t& board = graph_state->board;
        char* board_matrix = board.board_matrix.get();
        int order = board.order;
        auto sprite = get_sprite(rot);

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                auto px = sprite[calc_index(j, i, 2)];
                if (px == neutral) {
                    continue;
                }

                assert((board_matrix[calc_index(abspos.x + j, abspos.y + i, order)] == empty)
                    && "Error: Invalid placement.");

                board_matrix[calc_index(abspos.x + j, abspos.y + i, order)] = px;

                draw_at(abspos.x + j, abspos.y + i, px, graph_state->hOutput);
            }
        }

        COORD coord{
            .X = (SHORT)order - 1,
            .Y = (SHORT)order - 1,
        };
        SetConsoleCursorPosition(graph_state->hOutput, coord);

        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // TODO: Add options to state
    }

    static void ensure_success(BOOL is_success, const std::string& msg) {
        if (!is_success) {
            auto error = GetLastError();
            std::cerr
                << "Windows API error: " << error
                << "Message: " << msg
                << std::endl;

            ExitProcess(EXIT_FAILURE);
        }
    }

    void use_wch(tromino::board_t& tromino_board) {
        SetConsoleTitle(TEXT("Tromino Puzzle")); // TODO:

        HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        tromino::graph_state_t graph_state{
            .board = tromino_board,
            .hOutput = hConsoleOutput,
        };
        tromino::windows::init_board(tromino_board);

        CONSOLE_SCREEN_BUFFER_INFO originalConsoleScreenBufferInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &originalConsoleScreenBufferInfo);

        SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE);
        tromino::windows::draw_board(tromino_board);

        SetConsoleTextAttribute(hConsoleOutput,
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
        );
        COORD coordMark = {
            .X = (short)tromino_board.mark.x,
            .Y = (short)tromino_board.mark.y
        };
        SetConsoleCursorPosition(hConsoleOutput, coordMark);
        std::cout << tromino::windows::mark;

        SetConsoleTextAttribute(hConsoleOutput,
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            | BACKGROUND_BLUE | BACKGROUND_INTENSITY
        );

        solve_tromino_puzzle(tromino_board.order, tromino_board.mark, tromino::windows::add_tromino, &graph_state);

        SetConsoleTextAttribute(hConsoleOutput, originalConsoleScreenBufferInfo.wAttributes);
    }

} // namespace tromino::windows
