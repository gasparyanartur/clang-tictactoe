#include "board.h"
#include "stdio.h"
#include "stdbool.h"

uint_fast8_t coord_to_index(uint_fast8_t x, uint_fast8_t y);
bool coord_in_board(uint_fast8_t x, uint_fast8_t y);
tile_ptr get_tile_ptr(board_ptr board, uint_fast8_t x, uint_fast8_t y);

/*
 * Public Methods
 */

void print_board(board_ptr board) {
    printf("===========\n|  %d %d %d  |\n|  %d %d %d  |\n|  %d %d %d  |\n",
           board->tiles[0], board->tiles[1], board->tiles[2],
           board->tiles[3], board->tiles[4], board->tiles[5],
           board->tiles[6], board->tiles[7], board->tiles[8]);
}

void take_tile(board_ptr board, uint_fast8_t x, uint_fast8_t y, player_t player) {
    if (!is_player_t(player)) {
        printf("Attempted to interpret value '%d' as a player type.\n", player);
        return;
    }

    if (!coord_in_board(x, y)) {
        printf("Attempted to reference illegal board coordinate (%d,%d).\n", x, y);
        return;
    }

    tile_ptr t = get_tile_ptr(board, x, y);
    if (*t != NO_PLAYER) {
        printf("Player %d attempted to take taken tile at position (%d,%d) containing value %d\n", player, x, y, *t);
        return;
    }

    *t = player;
    board->remainingTiles--;
}

void clear_tile(board_ptr board, uint_fast8_t x, uint_fast8_t y) {
    if (!coord_in_board(x, y)) {
        printf("Attempted to reference illegal board coordinate (%d,%d).\n", x, y);
        return;
    }

    tile_ptr t = get_tile_ptr(board, x, y);
    if (*t == NO_PLAYER) {
        printf("Attempted to clear empty tile at position (%d,%d)\n", x, y);
        return;
    }

    *t = NO_PLAYER;
    board->remainingTiles++;
}

player_t get_tile(board_ptr board, uint_fast8_t x, uint_fast8_t y) {
    if (!coord_in_board(x, y)) {
        printf("Attempted to reference illegal board coordinate (%d,%d).\n", x, y);
        return NO_PLAYER;
    }

    return *get_tile_ptr(board, x, y);
}

/*
 * Private Methods
 */

uint_fast8_t coord_to_index(uint_fast8_t x, uint_fast8_t y) {
    return y * BOARD_WIDTH + x;
}

tile_ptr get_tile_ptr(board_ptr board, uint_fast8_t x, uint_fast8_t y) {
    return &board->tiles[coord_to_index(x, y)];
}

bool coord_in_board(uint_fast8_t x, uint_fast8_t y) {
    return x < BOARD_WIDTH && y < BOARD_HEIGHT;
}
