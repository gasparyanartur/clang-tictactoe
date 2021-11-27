#ifndef CLANG_TICTACTOE_AI_H
#define CLANG_TICTACTOE_AI_H

#include "board.h"
#include "engine.h"

tile_t calculate_optimal_move(board_ptr board, uint_fast8_t ai_turn, uint_fast8_t current_turn);

#endif //CLANG_TICTACTOE_AI_H
