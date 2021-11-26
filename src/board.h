#ifndef CLANG_TICTACTOE_BOARD_H
#define CLANG_TICTACTOE_BOARD_H

#include "player.h"
#include "stdint.h"

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE 9

typedef uint_fast8_t tile_t;

typedef struct {
    tile_t tiles[BOARD_WIDTH * BOARD_HEIGHT];
    int remainingTiles;
} brd_t;

void print_board(brd_t *board);
void set_tile(brd_t *board, uint_fast8_t x, uint_fast8_t y, player_t player);

#endif //CLANG_TICTACTOE_BOARD_H
