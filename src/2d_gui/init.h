#ifndef init_h
#define init_h

#include <cstddef>

#include "tromino.h"

struct board_t {
    std::size_t size;
    int order;
    position_t mark;
};

int init(const board_t& board);

#endif /* init_h */
