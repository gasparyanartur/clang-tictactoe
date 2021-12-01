#include "ai.h"

#define MAX_SCORE 100
#define MIN_SCORE -100

void undoMove(board_ptr board, const tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile);

void makeMove(board_ptr board, tile_t *move_stack, int *depth, player_t *currentPlayer, tile_t *tile);

int get_board_score(board_ptr board, player_t player);

void init_move_score(int * scores, int len) {
    int i;
    for(i = 0; i < len; i += 2)
        scores[i] = -MAX_SCORE;
    for(i = 1; i < len; i += 2)
        scores[i] = MAX_SCORE;
}

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer) {
    /*  Implemented using the minimax algorithm with a loop
     *  Assumes board starts off non-full and without a winner.
     *
     *  Minimax algorithm:
     *      for each tile:
     *          calculate score
     *
     *          if no winner and tile is empty:
     *              take tile
     *              restart tile query
     *
     *          elif score > high score at depth * weight:
     *              high score at depth = score * weight
     *
     *          restore tile
     *
     *      return high_score * weight
     */
    tile_t tileStack[BOARD_SIZE] = {0};
    int depthScores[BOARD_SIZE] = {-1, 1, -1, 1, -1, 1, -1, 1, -1};
    tile_t optimalTile = -1;
    tile_t tile = 0;
    player_t currentPlayer = aiPlayer;
    uint_fast8_t depth = 0;
    int weight = 1;

    while (tile < BOARD_SIZE) {
        int score = get_board_score(board, currentPlayer);

        if (score == 0) {
            if (is_tile_empty(board, tile)) {
                printf("depth: %d\n", depth);
                take_tile(board, tile, currentPlayer);
                tileStack[depth++] = tile;
                weight = -weight;
                currentPlayer = get_other_player(currentPlayer);
                tile = 0;
            }
            else {
                tile++;
            }
        }
        else {
            printf("Score: %d, Depth: %d, Weight: %d, hiScoreAtDepth: %d\n", score, depth, weight, depthScores[depth]);
            if (score >= depthScores[depth] * weight) {
                printf("Optimal move at depth %d is %d\n", depth, tileStack[depth-1]);
                depthScores[depth] = score * weight;
                optimalTile = tileStack[depth - 1];
            }

            if (depth == 0)
                break;

            // TODO Fix bug where it does not set the move correctly

            tile = tileStack[--depth];
            clear_tile(board, tile);
            weight = -weight;
            currentPlayer = get_other_player(currentPlayer);
            tile++;
        }
    }

    return optimalTile;
}

int get_board_score(board_ptr board, player_t player) {
    player_t winner = get_winner(board);

    if (winner == player)
        return 1;
    else if (winner == NO_PLAYER)
        return 0;
    else
        return -1;
}