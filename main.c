#include <stdio.h>

#include <memory.h>
#include "src/board.h"

int main() {
    printf("Starting program.\n");

    t_board board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    print_board(&board);

    return 0;
}
