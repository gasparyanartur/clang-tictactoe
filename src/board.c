#include "board.h"
#include "stdio.h"
#include "stdbool.h"

/*
 * Public Methods
 */
void print_board(board_ptr board) {
    printf("===========\n|  %d %d %d  |\n|  %d %d %d  |\n|  %d %d %d  |\n",
           board->tiles[0], board->tiles[1], board->tiles[2],
           board->tiles[3], board->tiles[4], board->tiles[5],
           board->tiles[6], board->tiles[7], board->tiles[8]);
}

void take_tile(board_ptr board, tile_t tile, player_t player) {
    if (!is_player_t(player)) {
        printf("Attempted to interpret value '%d' as a player type.\n", player);
        return;
    }

    if (!tile_in_board(tile)) {
        printf("Attempted to reference illegal tile %d.\n", tile);
        return;
    }

    if (!is_tile_empty(board, tile)) {
        printf("Player %d attempted to take taken tile at %d containing value %d\n", player, tile, get_tile(board, tile));
        return;
    }

    board->tiles[tile] = player;
    board->remainingTiles--;
}

void clear_tile(board_ptr board, tile_t tile) {
    if(!tile_in_board(tile)) {
        printf("Attempted to reference illegal tile %d.\n", tile);
        return;
    }

    if (is_tile_empty(board, tile)) {
        printf("Attempted to clear empty tile at position %d.\n", tile);
        return;
    }

    board->tiles[tile] = NO_PLAYER;
    board->remainingTiles++;
}

player_t get_tile(board_ptr board, tile_t tile) {
    if (!tile_in_board(tile)) {
        printf("Attempted to reference illegal tile index %d.\n", tile);
        return NO_PLAYER;
    }

    return board->tiles[tile];
}

bool tile_in_board(tile_t tile) {
    return tile < BOARD_SIZE;
}

bool is_tile_empty(board_ptr board, tile_t tile) {
    return get_tile(board, tile) == NO_PLAYER;
}

bool is_winner(board_ptr board, player_t tile) {
    return 0;
}
