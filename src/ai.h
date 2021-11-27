#ifndef CLANG_TICTACTOE_AI_H
#define CLANG_TICTACTOE_AI_H

#include "board.h"
#include "engine.h"

tile_t calculate_optimal_move(board_ptr board, player_t aiPlayer);

#endif //CLANG_TICTACTOE_AI_H
