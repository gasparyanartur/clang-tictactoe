#include "board.h"
#include "stdio.h"
#include "stdbool.h"

uint_fast8_t coord_to_index(uint_fast8_t x, uint_fast8_t y);
tile_t *get_tile_ptr(brd_t *board, uint_fast8_t x, uint_fast8_t y);
bool coords_in_board(uint_fast8_t x, uint_fast8_t y);

void print_board(brd_t *board) {
    printf("===========\n|  %d %d %d  |\n|  %d %d %d  |\n|  %d %d %d  |\n",
           board->tiles[0], board->tiles[1], board->tiles[2],
           board->tiles[3], board->tiles[4], board->tiles[5],
           board->tiles[6], board->tiles[7], board->tiles[8]);
}

void set_tile(brd_t *board, uint_fast8_t x, uint_fast8_t y, player_t player) {
    if (!is_player_t(player)) {
        printf("Attempted to interpret value '%d' as a player type.\n", player);
        return;
    }

    if (!coords_in_board(x, y)) {
        printf("Attempted to reference illegal board coordinate (%d,%d).\n", x, y);
        return;
    }

    *get_tile_ptr(board, x, y) = player;
}

tile_t *get_tile_ptr(brd_t *board, uint_fast8_t x, uint_fast8_t y) {
    int index = coord_to_index(x, y);
    return &board->tiles[index];
}

uint_fast8_t coord_to_index(uint_fast8_t x, uint_fast8_t y) {
    return y * BOARD_WIDTH + x;
}

bool coords_in_board(uint_fast8_t x, uint_fast8_t y) {
    return x < BOARD_WIDTH && y < BOARD_HEIGHT;
}
