#ifndef CLANG_TICTACTOE_PLAYER_H
#define CLANG_TICTACTOE_PLAYER_H

#include "stdint.h"
#include "stdbool.h"

typedef enum {
    NO_PLAYER = (uint_fast8_t) 0,
    PLAYER_X = (uint_fast8_t) 1,
    PLAYER_O = (uint_fast8_t) 2
} player_t;

player_t get_other_player(player_t player);
bool is_player_t(player_t player);

#endif //CLANG_TICTACTOE_PLAYER_H
