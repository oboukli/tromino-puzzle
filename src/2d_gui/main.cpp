#include "init.h"

int main(int argc, const char * argv[]) {
    int order = 32;
    size_t size = order * order;
    board_t board{
        .size = size,
        .order = order,
        .mark = {
            .x = 11,
            .y = 17
        }
    };

    return init(board);
}
