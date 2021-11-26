#ifndef CLANG_TICTACTOE_PLAYER_H
#define CLANG_TICTACTOE_PLAYER_H

typedef enum {
    NO_PLAYER = 0,
    CROSS = 1,
    NAUGHT = 2
} Player;

Player get_other_player(Player player);

#endif //CLANG_TICTACTOE_PLAYER_H
