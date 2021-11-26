#include <stdio.h>

#include "src/board.h"
#include "src/engine.h"

void test_board();

int main() {
    run_game();
    //test_board();
    return 0;
}

void test_board() {
    printf("Starting program.\n");

    board_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    board_t *boardPtr = &board;

    print_board(boardPtr);

    take_tile(boardPtr, 1, CROSS);
    print_board(boardPtr);

    take_tile(boardPtr, 4, NAUGHT);
    print_board(boardPtr);

    take_tile(boardPtr, 9, CROSS);
    take_tile(boardPtr, -1, CROSS);
    print_board(boardPtr);

    clear_tile(boardPtr, 1);
    print_board(boardPtr);

    clear_tile(boardPtr, 1);
    print_board(boardPtr);

    printf("Value at position %d = %d\n", 4, get_tile(boardPtr, 4));
    printf("Value at position %d = %d\n", -1, get_tile(boardPtr, -1));
}
