#include <vcruntime_string.h>
#include "board.h"
#include "stdio.h"

void print_board(t_board *board) {
    printf("%d %d %d\n%d %d %d\n%d %d %d",
           board->tiles[0], board->tiles[1], board->tiles[2],
           board->tiles[3], board->tiles[4], board->tiles[5],
           board->tiles[6], board->tiles[7], board->tiles[8]);
}
