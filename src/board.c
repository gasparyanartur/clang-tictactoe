#include "board.h"
#include "stdio.h"
#include "stdbool.h"

/*
 * Private Structures
 */
#define N_WIN_CONS 8
#define WIN_PATTERN_LEN 3

const tile_t WIN_CONDITIONS[N_WIN_CONS][WIN_PATTERN_LEN] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
};

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

player_t get_winner(board_ptr board) {
    for (int i = 0; i < N_WIN_CONS; i++) {
        int score[2] = {0};
        for (int j = 0; j < WIN_PATTERN_LEN; j++) {
            int tile = WIN_CONDITIONS[i][j];
            int value = get_tile(board, tile);
            if (value != NO_PLAYER)
                score[value - 1]++;
        }

        if (score[PLAYER_X - 1] == WIN_PATTERN_LEN)
            return PLAYER_X;
        else if (score[PLAYER_O - 1] == WIN_PATTERN_LEN)
            return PLAYER_O;
    }
    return NO_PLAYER;
}

