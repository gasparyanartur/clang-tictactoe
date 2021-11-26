#include <stdio.h>

#include <memory.h>
#include "src/board.h"

int main() {
    printf("Starting program.\n");

    brd_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    print_board(&board);

    set_tile(&board, 2, 1, CROSS);
    print_board(&board);

    set_tile(&board, 2, 3, CROSS);
    set_tile(&board, -1, 1, CROSS);
    print_board(&board);

    return 0;
}
