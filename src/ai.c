#include "ai.h"

#define MAX_SCORE 100

void undoMove(board_ptr board, const tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile);

void makeMove(board_ptr board, tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile);

void init_move_score(int * scores, int len) {
    int i;
    for(i = 0; i < len; i += 2)
        scores[i] = -MAX_SCORE;
    for(i = 1; i < len; i += 2)
        scores[i] = MAX_SCORE;
}

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer) {
    /* Implemented using the minimax algorithm with a loop
     * Assumes board starts off non-full and without a winner.
     */
    tile_t move_stack[BOARD_SIZE];
    int move_scores[BOARD_SIZE];
    init_move_score(move_scores, board->remainingTiles);

    // TODO Implement remaining moves using linked list to remove unnecessary looping over taken values

    int depth = 0;
    player_t currentPlayer = aiPlayer;
    tile_t tile = 0;
    while (tile < BOARD_SIZE) {
        player_t winner = get_winner(board);
        if (winner == NO_PLAYER) {
            if (board->remainingTiles == 0) {
                undoMove(board, move_stack, &depth, &currentPlayer, &tile);
            }

            while (++tile < BOARD_SIZE) {
                if (is_tile_empty(board, tile)) {
                    makeMove(board, move_stack, &depth, &currentPlayer, &tile);
                }
            }
        }
        else if (winner == aiPlayer) {
            move_scores[depth] = MAX_SCORE;
            undoMove(board, move_stack, &depth, &currentPlayer, &tile);
        }
        else {
            move_scores[depth] = -MAX_SCORE;
            undoMove(board, move_stack, &depth, &currentPlayer, &tile);
        }


    }


    return 0;
}

void makeMove(board_ptr board, tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile) {
    move_stack[(*depth)++] = (*tile);
    take_tile(board, (*tile), (*currentPlayer));
    (*currentPlayer) = get_other_player((*currentPlayer));
    (*tile) = 0;
}

void undoMove(board_ptr board, const tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile) {
    (*tile) = move_stack[(*depth)--];
    clear_tile(board, (*tile)++);
    (*currentPlayer) = get_other_player((*currentPlayer));
}
