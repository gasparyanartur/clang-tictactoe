#include <stdio.h>

#include <memory.h>
#include "src/board.h"

int main() {
    printf("Starting program.\n");

    brd_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    brd_t *board_ptr = &board;

    print_board(board_ptr);

    set_tile(board_ptr, 2, 1, CROSS);
    print_board(board_ptr);

    set_tile(board_ptr, 0, 0, NAUGHT);
    print_board(board_ptr);

    set_tile(board_ptr, 2, 3, CROSS);
    set_tile(board_ptr, -1, 1, CROSS);
    print_board(board_ptr);

    return 0;
}
