#include "ai.h"

#define MAX_SCORE 100

int get_board_score(board_ptr board, player_t player);

int get_weight(player_t aiPlayer, player_t currentPlayer);

void make_move(board_ptr board, tile_t *tileStack, player_t *currentPlayer, tile_t *tile, uint_fast8_t *depth, uint_fast8_t *maxDepth);

void undo_move(board_ptr board, const tile_t *tileStack, tile_t *tile, uint_fast8_t *depth);

bool is_not_end_state(board_ptr board, int score);

tile_t get_first_free_tile(board_ptr board, tile_t start);

bool is_high_score(player_t aiPlayer, const int *depthScores, player_t currentPlayer, uint_fast8_t depth, int score);

tile_t get_optimal_move(int *depthScores, tile_t *optimalMoves, uint_fast8_t depth);

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
    tile_t optimalMoves[BOARD_SIZE + 1] = {-1};
    tile_t tile = 0;
    player_t currentPlayer = aiPlayer;
    uint_fast8_t maxDepth = 0;
    uint_fast8_t depth = 0;

    while (true) {
        int score = get_board_score(board, currentPlayer);

        if (is_not_end_state(board, score)) {
            tile = get_first_free_tile(board, tile);
            if (tile < BOARD_SIZE) {
                make_move(board, tileStack, &currentPlayer, &tile, &depth, &maxDepth);
                goto END_TURN;
            }
        }
        else {
            if (is_high_score(aiPlayer, depthScores, currentPlayer, depth, score)) {
                depthScores[depth] = score;
                optimalMoves[depth] = tileStack[depth - 1];
            }
        }

        if (depth == 0) break;
        undo_move(board, tileStack, &tile, &depth);

        END_TURN:
        currentPlayer = get_other_player(currentPlayer);
    }

    return get_optimal_move(depthScores, optimalMoves, maxDepth);
}

tile_t get_optimal_move(int *depthScores, tile_t *optimalMoves, uint_fast8_t depth) {
    // TODO Fix method
    printf("\n");
    for(int i = 0; i < depth; i++)
        printf("%d ", depthScores[i]);
    printf("\n");

    int maximizing = depth % 2 == 0;
    while (depth > 0) {
        int prev = depth - 1;
        int diff = depthScores[depth] - depthScores[prev];
        if (maximizing) {
            if (diff >= 0) {
                depthScores[prev] = depthScores[depth];
                optimalMoves[prev] = optimalMoves[depth];
            }
        }
        else {
            if (diff <= 0) {
                depthScores[prev] = depthScores[depth];
                optimalMoves[prev] = optimalMoves[depth];
            }
        }
        depth--;
    }

    for(int i = 0; i < BOARD_SIZE; i++)
        printf("%d", depthScores[i]);
    printf("\n");
    return optimalMoves[0];
}

bool is_high_score(player_t aiPlayer, const int *depthScores, player_t currentPlayer, uint_fast8_t depth, int score) {
    bool maximizing = currentPlayer == aiPlayer;
    if (maximizing) {
        return score >= depthScores[depth];
    }
    else {
        return score <= depthScores[depth];
    }
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

void make_move(board_ptr board, tile_t *tileStack, player_t *currentPlayer, tile_t *tile, uint_fast8_t *depth, uint_fast8_t *maxDepth) {
    take_tile(board, (*tile), (*currentPlayer));
    tileStack[(*depth)++] = (*tile);
    (*tile) = 0;
    if ((*depth) > (*maxDepth))
        (*maxDepth) = (*depth);
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