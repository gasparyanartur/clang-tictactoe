#include "ai.h"

#define MAX_SCORE 100

int get_board_score(board_ptr board, player_t player);

int get_weight(player_t aiPlayer, player_t currentPlayer);

void make_move(board_ptr board, tile_t *tileStack, player_t *currentPlayer, tile_t *tile, uint_fast8_t *depth);

void undo_move(board_ptr board, const tile_t *tileStack, tile_t *tile, uint_fast8_t *depth);

bool is_not_end_state(board_ptr board, int score);

tile_t get_first_free_tile(board_ptr board, tile_t start);

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer) {
    /*  Implemented using the minimax algorithm with a loop.
     *  Assumes board starts off non-full, without a winner, and on the AIs turn.
     *
     *  Minimax algorithm:
     *      for each tile:
     *          calculate score
     *          if no winner and no draw:
     *              if no available tile:
     *                  undo move if moves exist in history
     *                  else finish search
     *
     *              take first available tile
     *              restart tile query
     *              end turn
     *
     *          else:
     *              if current move gives high score:
     *                  high score at depth = current score
     *                  optimal move = current move
     *
     *              undo move
     *              restore tile query to previous depth
     *              end turn
     *
     *      return optimal move
     */
    tile_t tileStack[BOARD_SIZE + 1] = {0};
    int depthScores[BOARD_SIZE + 1] = {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1};
    tile_t optimalTile = -1;
    tile_t tile = 0;
    player_t currentPlayer = aiPlayer;
    uint_fast8_t depth = 0;

    while (tile < BOARD_SIZE) {
        int score = get_board_score(board, currentPlayer);

        if (is_not_end_state(board, score)) {
            tile = get_first_free_tile(board, tile);
            if (tile < BOARD_SIZE) {
                make_move(board, tileStack, &currentPlayer, &tile, &depth);
                goto END_TURN;
            }
        }
        else {
            int weight = get_weight(aiPlayer, currentPlayer);
            if (score * weight >= depthScores[depth] * weight) {
                depthScores[depth] = score * weight;
                optimalTile = tileStack[depth - 1];
            }
        }

        if (depth == 0) break;
        undo_move(board, tileStack, &tile, &depth);

        END_TURN:
        currentPlayer = get_other_player(currentPlayer);
    }

    return optimalTile;
}

tile_t get_first_free_tile(board_ptr board, tile_t start) {
    for (tile_t t = start; t < BOARD_SIZE; t++)
        if (is_tile_empty(board, t))
            return t;
    return -1;
}

bool is_not_end_state(board_ptr board, int score) { return score == 0 && !is_board_full(board); }

void undo_move(board_ptr board, const tile_t *tileStack, tile_t *tile, uint_fast8_t *depth) {
    (*tile) = tileStack[--(*depth)];
    clear_tile(board, (*tile));
    (*tile)++;
}

void make_move(board_ptr board, tile_t *tileStack, player_t *currentPlayer, tile_t *tile, uint_fast8_t *depth) {
    take_tile(board, (*tile), (*currentPlayer));
    tileStack[(*depth)++] = (*tile);
    (*tile) = 0;
}

int get_weight(player_t aiPlayer, player_t currentPlayer) {
    return (aiPlayer == currentPlayer) ? 1:-1;
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