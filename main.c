#include <stdio.h>

#include "src/board.h"

int main() {
    printf("Starting program.\n");

    board_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    board_t *board_ptr = &board;

    print_board(board_ptr);

    take_tile(board_ptr, 2, 1, CROSS);
    print_board(board_ptr);

    take_tile(board_ptr, 1, 2, NAUGHT);
    print_board(board_ptr);

    take_tile(board_ptr, 2, 3, CROSS);
    take_tile(board_ptr, -1, 1, CROSS);
    print_board(board_ptr);

    clear_tile(board_ptr, 2, 1);
    print_board(board_ptr);

    return 0;
}
