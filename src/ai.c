#include "ai.h"

#define INF_SCORE 10
#define WIN_SCORE 1

int get_board_score(board_ptr board, player_t player);

tile_t minimax_tile(board_ptr board, player_t aiPlayer);

int maximize_score(board_ptr board, tile_t tile, player_t aiPlayer);

int minimize_score(board_ptr board, tile_t tile, player_t aiPlayer);

bool is_terminal_state(board_ptr board, int score);

tile_t next_free_tile(board_ptr board, tile_t t);

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer) {
    return minimax_tile(board, aiPlayer);
}

tile_t minimax_tile(board_ptr board, const player_t aiPlayer) {
    tile_t maxTile = -1;
    int maxScore = -INF_SCORE;

    for (tile_t t = next_free_tile(board, 0); t < BOARD_SIZE; t = next_free_tile(board, ++t)) {
        int score = minimize_score(board, t, aiPlayer);
        if (score > maxScore) {
            maxScore = score;
            maxTile = t;
        }
        if (score == WIN_SCORE)
            return maxTile;
    }

    return maxTile;
}

int maximize_score(board_ptr board, tile_t tile, const player_t aiPlayer) {
    player_t opponent = get_other_player(aiPlayer);
    take_tile(board, tile, opponent);
    int score = get_board_score(board, opponent);
    if (is_terminal_state(board, score)) {
        clear_tile(board, tile);
        return -score;
    }

    int maxScore = -INF_SCORE;
    for (tile_t t = next_free_tile(board, 0); t < BOARD_SIZE; t = next_free_tile(board, ++t)) {
        score = minimize_score(board, t, aiPlayer);
        if (score > maxScore)
            maxScore = score;
        if (score == WIN_SCORE)
            break;
    }

    clear_tile(board, tile);
    return maxScore;
}

int minimize_score(board_ptr board, tile_t tile, const player_t aiPlayer) {
    take_tile(board, tile, aiPlayer);
    int score = get_board_score(board, aiPlayer);
    if (is_terminal_state(board, score)) {
        clear_tile(board, tile);
        return score;
    }

    int minScore = INF_SCORE;
    for (tile_t t = next_free_tile(board, 0); t < BOARD_SIZE; t = next_free_tile(board, ++t)) {
        score = maximize_score(board, t, aiPlayer);
        if (score < minScore)
            minScore = score;
        if (score == -WIN_SCORE)
            break;
    }

    clear_tile(board, tile);
    return minScore;
}

tile_t next_free_tile(board_ptr board, tile_t t) {
    while (t < BOARD_SIZE) {
        if (is_tile_empty(board, t))
            return t;
        t++;
    }
    return t;
}

bool is_terminal_state(board_ptr board, int score) { return score != 0 || is_board_full(board); }

int get_board_score(board_ptr board, player_t player) {
    if (is_winner(board, player))
        return WIN_SCORE;
    return 0;
}