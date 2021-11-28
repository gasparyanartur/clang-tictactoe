#include "ai.h"

#define MAX_SCORE 100
#define MIN_SCORE -100

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

    /* Minimax Algorithm
     *  For each entry tile:
     *      if tile not empty:
     *          continue
     *
     *      make move tile
     *      if maximizing
     *          if ai wins
     *              score at depth = max
     *              undo move tile
     *          elif draw
     *              score at depth = 0
     *              undo move tile
     *          else
     *              for each tile from entry tile + 1:
     *                  if tile empty:
     *                      make move tile
     *      else
     *          if ai loses
                    score at depth = min
                    undo move tile
                elif draw
                    score at depth = 0
                    undo move tile
     *          continue
     *      if
     */
    tile_t move_stack[BOARD_SIZE];
    int move_scores[BOARD_SIZE];
    init_move_score(move_scores, board->remainingTiles);

    // TODO Implement remaining moves using linked list to remove unnecessary looping over taken values

    int depth = 0;
    bool maximizing = true;
    player_t enemyPlayer = get_other_player(aiPlayer);

    tile_t tile = 0;
    while (tile < BOARD_SIZE) {
        if (!is_tile_empty(board, tile)) {
            tile++;
            continue;
        }

        if (maximizing) {
            player_t winner = get_winner(board);
            if (winner == aiPlayer) {
                move_scores[depth] = MAX_SCORE;
                maximizing = false;
                tile = move_stack[depth--] + 1;
            }
            else {  // Guaranteed no winner since opponent can't win on AI's turn.
                if (is_board_full(board)) {
                    if (move_scores[depth] < 0)
                        move_scores[depth] = 0;
                    maximizing = false;
                    tile = move_stack[depth--] + 1;
                }
                else {  // Make move on empty tile
                    move_stack[depth++] = tile;
                    take_tile(board, tile, aiPlayer);
                    maximizing = false;
                    tile = 0;
                }
            }
        }
        else {
            player_t winner = get_winner(board);
            if (winner == enemyPlayer) {
                move_scores[depth] = MIN_SCORE;
                maximizing = true;
                tile = move_stack[depth--] + 1;
            }
            else {  // Guaranteed no winner since AI can't win on opponent's turn
                if (is_board_full(board)) {
                    if (move_scores[depth] > 0)
                        move_scores[depth] = 0;
                    maximizing = true;
                    tile = move_stack[depth--] + 1;
                }
                else {  // Make move on empty tile
                    move_stack[depth++] = tile;
                    take_tile(board, tile, enemyPlayer);
                    maximizing = true;
                    tile = 0;
                }
            }
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
