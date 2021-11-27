#ifndef CLANG_TICTACTOE_BOARD_H
#define CLANG_TICTACTOE_BOARD_H

#include "player.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

#define BOARD_SIZE 9

typedef uint_fast8_t tile_t;

typedef struct {
    tile_t tiles[BOARD_SIZE];
    int remainingTiles;
} board_t;

typedef board_t* board_ptr;

void print_board(board_ptr board);
void take_tile(board_ptr board, tile_t tile, player_t player);
void clear_tile(board_ptr board, tile_t tile);
player_t get_tile(board_ptr board, tile_t tile);

bool tile_in_board(tile_t tile);
bool is_tile_empty(board_ptr board, tile_t tile);


#endif //CLANG_TICTACTOE_BOARD_H
