#ifndef CLANG_TICTACTOE_BOARD_H
#define CLANG_TICTACTOE_BOARD_H

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE 9

typedef struct {
    int tiles[BOARD_WIDTH * BOARD_HEIGHT];
    int remainingTiles;
} t_board;

void print_board(t_board *board);

#endif //CLANG_TICTACTOE_BOARD_H
