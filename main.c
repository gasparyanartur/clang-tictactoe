#include <stdio.h>

#include "src/board.h"
#include "src/engine.h"

void test_board();

int main() {
    run_game();
    return 0;
}

void test_board() {
    printf("Starting program.\n");

    board_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    board_t *boardPtr = &board;

    print_board(boardPtr);

    take_tile(boardPtr, 2, 1, CROSS);
    print_board(boardPtr);

    take_tile(boardPtr, 1, 2, NAUGHT);
    print_board(boardPtr);

    take_tile(boardPtr, 2, 3, CROSS);
    take_tile(boardPtr, -1, 1, CROSS);
    print_board(boardPtr);

    clear_tile(boardPtr, 2, 1);
    print_board(boardPtr);

    clear_tile(boardPtr, 2, 1);
    print_board(boardPtr);

    printf("Value at position (%d,%d) = %d\n", 1, 2, get_tile(boardPtr, 1, 2));
    printf("Value at position (%d,%d) = %d\n", -1, 2, get_tile(boardPtr, -1, 2));
}
