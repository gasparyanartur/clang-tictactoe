#include "ai.h"

#define MAX_SCORE 100

int get_board_score(board_ptr board, player_t player);

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
     *          elif weight * score > high score at depth * weight:
     *              high score at depth = score * weight
     *              if maximizing:
     *                  optimal tile = tile
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

        if (score == 0 && !is_board_full(board)) {
            while (!is_tile_empty(board, tile) && tile < BOARD_SIZE)
                tile++;

            if (tile >= BOARD_SIZE) {
                if (depth == 0)
                    break;
                tile = tileStack[--depth];
                continue;
            }

            take_tile(board, tile, currentPlayer);
            tileStack[depth++] = tile;
            weight = -weight;
            currentPlayer = get_other_player(currentPlayer);
            tile = 0;
        }
        else {
            if (score * weight >= depthScores[depth] * weight) {
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