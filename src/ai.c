#include "ai.h"

#define INF_SCORE 100

typedef struct {
    tile_t tile;
    int score;
} minimax_result_t;

int get_board_score(board_ptr board, player_t player);

minimax_result_t minimax(board_ptr board, player_t aiPlayer);

minimax_result_t pack_result(tile_t tile, int score);

minimax_result_t maximize_result(board_ptr board, tile_t tile, player_t aiPlayer, player_t currentPlayer);

minimax_result_t minimize_result(board_ptr board, tile_t tile, player_t aiPlayer, player_t currentPlayer);

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer) {
    minimax_result_t result = minimax(board, aiPlayer);
    return result.tile;
}

minimax_result_t minimax(board_ptr board, const player_t aiPlayer) {
    return maximize_result(board, 0, aiPlayer, aiPlayer);
}

minimax_result_t maximize_result(board_ptr board, tile_t tile, const player_t aiPlayer, const player_t currentPlayer) {
    int score = get_board_score(board, aiPlayer);
    if (score != 0 || is_board_full(board))
        return pack_result(tile, -score);

    minimax_result_t maxResult = {.score=-INF_SCORE, .tile=-1};
    for(tile_t t = 0; t < BOARD_SIZE; t++) {
        if (is_tile_empty(board, t)) {
            take_tile(board, t, (aiPlayer));
            minimax_result_t tempResult = minimize_result(board, t, aiPlayer, get_other_player(currentPlayer));
            clear_tile(board, t);
            if (tempResult.score >= maxResult.score)
                maxResult = tempResult;
        }
    }
    return maxResult;
}

minimax_result_t minimize_result(board_ptr board, tile_t tile, const player_t aiPlayer, const player_t currentPlayer) {
    int score = get_board_score(board, aiPlayer);
    if (score != 0 || board->remainingTiles == 0)
        return pack_result(tile, -score);

    minimax_result_t minResult = {.score=INF_SCORE, .tile=-1};
    for(tile_t t = 0; t < BOARD_SIZE; t++) {
        if (is_tile_empty(board, t)) {
            take_tile(board, t, get_other_player(aiPlayer));
            minimax_result_t tempResult = maximize_result(board, t, aiPlayer, get_other_player(currentPlayer));
            clear_tile(board, t);
            if (tempResult.score <= minResult.score)
                minResult = tempResult;
        }
    }
    return minResult;
}

minimax_result_t pack_result(tile_t tile, int score) {
    minimax_result_t result = {.tile = tile, .score = score};
    return result;
}

int get_board_score(board_ptr board, player_t player) {
    player_t winner = get_winner(board);

    if (winner == NO_PLAYER)
        return 0;
    else if (winner == player)
        return 1;
    else
        return -1;
}